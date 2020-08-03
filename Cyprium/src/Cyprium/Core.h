#pragma once

#ifdef CP_PLATFORM_WINDOWS
	#ifdef CP_BUILD_DLL
		#define CYPRIUM_API __declspec(dllexport)
	#else
		#define CYPRIUM_API __declspec(dllimport)
	#endif // CP_BUILD_DLL
#else
	#error Cyprium only supports Windows!
#endif // CP_PLATFORM_WINDOWS

#define BIT(x) (1 << x)