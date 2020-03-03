#pragma once

#include "texgraph/Node.h"

#include <SM_Vector.h>

namespace texgraph
{
namespace node
{

class PerlinNoise : public Node
{
public:
    PerlinNoise()
        : Node()
    {
        m_exports = {
            {{ NodeVarType::Image, "out" }},
        };
    }

    virtual void Execute() override;

    RTTR_ENABLE(Node)

#define PARM_FILEPATH "texgraph/node/PerlinNoise.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // PerlinNoise

}
}