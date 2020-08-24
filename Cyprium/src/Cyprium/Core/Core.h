/*
	Based on the tutorial videos by The Cherno
	Link: https://www.youtube.com/watch?v=YZKEjaCnsjU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT
*/

#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define CP_PLATFORM_WINDOWS
	#else
		#error "x86 Build are not supported
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define CP_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define CP_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
* since android is based on the linux kernel
* it has __linux__ defined */
#elif defined(__ANDROID__)
	#define CP_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define CP_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

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
	#error "Cyprium only supports Windows!"
#endif // End of DLL Support

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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}