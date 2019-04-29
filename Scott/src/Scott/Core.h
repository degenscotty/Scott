#pragma once

#ifdef SC_PLATFORM_WINDOWS
	#ifdef SC_BUILD_DLL
		#define SCOTT_API __declspec(dllexport)
	#else
		#define SCOTT_API __declspec(dllimport)
	#endif
#else
	#error Scott only supports Windows!
#endif 


#define BIT(x) (1 << x)
