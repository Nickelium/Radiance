#pragma once

#ifdef GPU_NVIDIA
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif
#ifdef GPU_AMD
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif


#ifdef MEMORYLEAK_CHECK

#if RAD_DEBUG
#include <vld.h>
#endif

#endif
