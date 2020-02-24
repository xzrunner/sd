#pragma once

#include "sd/typedef.h"
#include "sd/NodeVarType.h"

#include <dag/Node.h>

#include <map>

namespace sd
{

class Evaluator
{
public:
    // update node
    void ComponentChaged(const NodePtr& node);

    // update devices
    void AddComponent(const NodePtr& node);
    void RemoveComponent(const NodePtr& node);
    void ClearAllComponents();

    // update node prop
    void PropChanged(const NodePtr& node);

    // update node conn
    void Connect(const dag::Node<NodeVarType>::PortAddr& from, const dag::Node<NodeVarType>::PortAddr& to);
    void Disconnect(const dag::Node<NodeVarType>::PortAddr& from, const dag::Node<NodeVarType>::PortAddr& to);
    void RebuildConnections(const std::vector<std::pair<dag::Node<NodeVarType>::PortAddr, dag::Node<NodeVarType>::PortAddr>>& conns);

    void MakeDirty();

    void Update();

    auto& GetAllNodes () const { return m_node_map; }

private:
    std::map<std::string, NodePtr> m_node_map;

    bool m_dirty = false;

    size_t m_next_id = 0;

}; // Evaluator

}