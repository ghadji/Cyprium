/*
	Based on the tutorial videos by The Cherno
	Link: https://www.youtube.com/watch?v=YZKEjaCnsjU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
*/

#pragma once

#include <memory>

#ifdef CP_PLATFORM_WINDOWS
	#if CP_DYNAMIC_LINK
		#ifdef CP_BUILD_DLL
			#define CYPRIUM_API __declspec(dllexport)
		#else
			#define CYPRIUM_API __declspec(dllimport)
		#endif // CP_BUILD_DLL
	#else
		#define CYPRIUM_API
	#endif
#else
	#error Cyprium only supports Windows!
#endif // CP_PLATFORM_WINDOWS

#ifdef CP_DEBUG
	#define CP_ENABLE_ASSERTS
#endif

#ifdef CP_ENABLE_ASSERTS
	#define CP_ASSERT(x, ...) { if (!(x)) { CP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CP_CORE_ASSERT(x, ...) { if (!(x)) { CP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CP_ASSERT(x, ...)
	#define CP_CORE_ASSERT(x, ...)
#endif // CP_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define CP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Cyprium
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}