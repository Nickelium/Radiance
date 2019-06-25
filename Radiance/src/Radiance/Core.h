#pragma once
// MACROS & STUFF
//#ifdef RAD_PLATFORM_WINDOWS
//	#ifdef RAD_EXPORT
//		#define RAD_API __declspec(dllexport)
//	#else
//		#define RAD_API __declspec(dllimport)
//	#endif
//#else
//	#error Radiance currently only support Windows
//#endif


#ifdef RAD_DEBUG
	#define RAD_ENABLE_ASSERTS
#endif

#ifdef RAD_ENABLE_ASSERTS
#define RAD_ASSERT(x, ...) { if(!(x)) { RAD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RAD_CORE_ASSERT(x, ...) { if(!(x)) { RAD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define RAD_ASSERT(x, ...)
#define RAD_CORE_ASSERT(x, ...)
#endif

//#define BIND_FN(Func) [&](auto& _param){ return Func(_param);}
#define BIND_FN(Func) std::bind(&Func, this, std::placeholders::_1)

#define BIT(X) (1 << X)

#include <stdint.h>
using ID = uint32_t;