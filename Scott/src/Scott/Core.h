#pragma once

#ifdef SC_PLATFORM_WINDOWS
#if SC_DYNAMIC_LINK
	#ifdef SC_BUILD_DLL
		#define SCOTT_API __declspec(dllexport)
	#else
		#define SCOTT_API __declspec(dllimport)
	#endif
#else
	#define SCOTT_API
#endif
#else
	#error Scott only supports Windows!
#endif

#ifdef SC_ENABLE_ASSERTS
#define SC_ASSERT(x, ...) { if(!(x)) { SC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SC_CORE_ASSERT(x, ...) { if(!(x)) { SC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SC_ASSERT(x, ...)
#define SC_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

template<class T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}
