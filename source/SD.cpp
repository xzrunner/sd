#include "sd/SD.h"

namespace sd
{

CU_SINGLETON_DEFINITION(SD);

extern void regist_rttr();

SD::SD()
{
	regist_rttr();
}

}