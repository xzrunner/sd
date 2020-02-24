#pragma once

#include "sd/Node.h"

#include <SM_Vector.h>

namespace sd
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

#define PARM_FILEPATH "sd/node/PerlinNoise.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // PerlinNoise

}
}