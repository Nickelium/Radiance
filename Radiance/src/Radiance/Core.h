#pragma once
// MACROS & STUFF
#ifdef RAD_PLATFORM_WINDOWS
	#ifdef RAD_BUILD_DLL
		#define RAD_API __declspec(dllexport)
	#else
		#define RAD_API __declspec(dllimport)
	#endif
#else
	#error Radiance currently only support Windows
#endif