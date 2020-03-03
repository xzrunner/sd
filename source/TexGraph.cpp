#include "texgraph/TexGraph.h"

namespace texgraph
{

CU_SINGLETON_DEFINITION(TexGraph);

extern void regist_rttr();

TexGraph::TexGraph()
{
	regist_rttr();
}

}