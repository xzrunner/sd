#define EXE_FILEPATH "texgraph/node_include_gen.h"
#include "texgraph/node_regist_cfg.h"
#undef EXE_FILEPATH

#include <rttr/registration>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<dag::Node<texgraph::NodeVarType>::Port>("texgraph::Node::Port")
	.property("var", &dag::Node<texgraph::NodeVarType>::Port::var)
;

rttr::registration::class_<texgraph::Node>("texgraph::Node")
	.method("GetImports", &texgraph::Node::GetImports)
	.method("GetExports", &texgraph::Node::GetExports)
;

#define EXE_FILEPATH "texgraph/node_rttr_gen.h"
#include "texgraph/node_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace texgraph
{

void regist_rttr()
{
}

}