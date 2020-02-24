#pragma once

#include "sd/typedef.h"

namespace sd
{

class Image;

class NodeHelper
{
public:
    static NodePtr GetInputNode(const Node& node, size_t idx);
    static std::shared_ptr<Image>
        GetInputImage(const Node& node, size_t idx);

}; // NodeHelper

}