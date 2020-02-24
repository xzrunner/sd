#pragma once

#include "sd/typedef.h"
#include "sd/NodeVarType.h"

#include <dag/Node.h>

namespace sd
{

class Image;

class Node : public dag::Node<NodeVarType>
{
public:
    Node() { }

    virtual void Execute() = 0;

    auto GetImage() const { return m_img; }

protected:
    std::shared_ptr<Image> m_img = nullptr;

    RTTR_ENABLE(dag::Node<NodeVarType>)

}; // Node

}