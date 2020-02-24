#include "sd/NodeHelper.h"
#include "sd/Node.h"

namespace sd
{

NodePtr NodeHelper::GetInputNode(const Node& node, size_t idx)
{
    auto& imports = node.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto in_comp = imports[idx].conns[0].node.lock();
    assert(in_comp->get_type().is_derived_from<Node>());
    return std::static_pointer_cast<Node>(in_comp);
}

std::shared_ptr<Image>
NodeHelper::GetInputImage(const Node& node, size_t idx)
{
    auto prev_node = GetInputNode(node, idx);
    if (prev_node) {
        return prev_node->GetImage();
    } else {
        return nullptr;
    }
}

}