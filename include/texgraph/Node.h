#pragma once

#include "texgraph/typedef.h"
#include "texgraph/NodeVarType.h"

#include <dag/Node.h>

namespace texgraph
{

class Image;

class Node : public dag::Node<NodeVarType>
{
public:
    Node() { }

    auto GetImage() const { return m_img; }

protected:
    std::shared_ptr<Image> m_img = nullptr;

    RTTR_ENABLE(dag::Node<NodeVarType>)

}; // Node

}