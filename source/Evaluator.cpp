#include "sd/Evaluator.h"
#include "sd/Node.h"
#include "sd/typedef.h"

#include <dag/Evaluator.h>

namespace sd
{

void Evaluator::ComponentChaged(const NodePtr& node)
{
    dag::Evaluator::SetTreeDirty<NodeVarType>(node);

    m_dirty = true;
}

void Evaluator::AddComponent(const NodePtr& node)
{
    auto name = node->GetName();
    while (name.empty() || m_node_map.find(name) != m_node_map.end())
    {
        if (node->GetName().empty()) {
            name = "node" + std::to_string(m_next_id++);
        } else {
            name = node->GetName() + std::to_string(m_next_id++);
        }
    }
    node->SetName(name);

    m_node_map.insert({ name, node });

    m_dirty = true;
}

void Evaluator::RemoveComponent(const NodePtr& node)
{
    if (m_node_map.empty()) {
        return;
    }

    auto itr = m_node_map.find(node->GetName());
    if (itr == m_node_map.end()) {
        return;
    }

    dag::Evaluator::SetTreeDirty<NodeVarType>(node);

    m_node_map.erase(itr);

    m_dirty = true;
}

void Evaluator::ClearAllComponents()
{
    if (m_node_map.empty()) {
        return;
    }

    m_node_map.clear();

    m_dirty = true;
}

void Evaluator::PropChanged(const NodePtr& node)
{
    dag::Evaluator::SetTreeDirty<NodeVarType>(node);

    m_dirty = true;
}

void Evaluator::Connect(const dag::Node<NodeVarType>::PortAddr& from, const dag::Node<NodeVarType>::PortAddr& to)
{
    dag::make_connecting<NodeVarType>(from, to);

    auto node = to.node.lock();
    assert(node && node->get_type().is_derived_from<Node>());
    dag::Evaluator::SetTreeDirty<NodeVarType>(std::static_pointer_cast<Node>(node));

    m_dirty = true;
}

void Evaluator::Disconnect(const dag::Node<NodeVarType>::PortAddr& from, const dag::Node<NodeVarType>::PortAddr& to)
{
    dag::disconnect<NodeVarType>(from, to);

    auto node = to.node.lock();
    assert(node && node->get_type().is_derived_from<Node>());
    dag::Evaluator::SetTreeDirty<NodeVarType>(std::static_pointer_cast<Node>(node));

    m_dirty = true;
}

void Evaluator::RebuildConnections(const std::vector<std::pair<dag::Node<NodeVarType>::PortAddr, dag::Node<NodeVarType>::PortAddr>>& conns)
{
    // update dirty
    for (auto itr : m_node_map) {
        if (dag::Evaluator::HasNodeConns<NodeVarType>(itr.second)) {
            dag::Evaluator::SetTreeDirty<NodeVarType>(itr.second);
        }
    }

    // remove conns
    for (auto itr : m_node_map) {
        itr.second->ClearConnections();
    }

    // add conns
    for (auto& conn : conns)
    {
        auto node = conn.second.node.lock();
        assert(node && node->get_type().is_derived_from<Node>());
        dag::Evaluator::SetTreeDirty<NodeVarType>(std::static_pointer_cast<Node>(node));
        dag::make_connecting<NodeVarType>(conn.first, conn.second);
    }

    m_dirty = true;
}

void Evaluator::MakeDirty()
{
    m_dirty = true;

    for (auto& itr : m_node_map) {
        itr.second->SetDirty(true);
    }
}

void Evaluator::Update()
{
    if (m_node_map.empty()) {
        return;
    }

    std::vector<std::shared_ptr<dag::Node<NodeVarType>>> devices;
    devices.reserve(m_node_map.size());
    for (auto itr : m_node_map) {
        devices.push_back(itr.second);
    }
    auto sorted_idx = dag::Evaluator::TopologicalSorting(devices);

    for (auto& idx : sorted_idx)
    {
        auto node = devices[idx];
        if (node->IsDirty()) {
            std::static_pointer_cast<Node>(node)->Execute();
            node->SetDirty(false);
        }
    }
}

}