#define EXE_FILEPATH "sd/node_include_gen.h"
#include "sd/node_regist_cfg.h"
#undef EXE_FILEPATH

#include <rttr/registration>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<dag::Node<sd::NodeVarType>::Port>("sd::Node::Port")
	.property("var", &dag::Node<sd::NodeVarType>::Port::var)
;

rttr::registration::class_<sd::Node>("sd::Node")
	.method("GetImports", &sd::Node::GetImports)
	.method("GetExports", &sd::Node::GetExports)
;

#define EXE_FILEPATH "sd/node_rttr_gen.h"
#include "sd/node_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace sd
{

void regist_rttr()
{
}

}