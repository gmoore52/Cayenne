#ifndef CAYENNE_CORE_H
#define CAYENNE_CORE_H

#ifdef CY_PLATFORM_WINDOWS
    #ifdef CAYENNE_BUILD_STATIC
        #define CY_API
    #else
        #ifdef CY_BUILD_DLL
            #define CY_API __declspec(dllexport)
        #else
            #define CY_API __declspec(dllimport)
        #endif
    #endif
#else
    #error "Currently only windows support for Cayenne"
#endif

#ifdef CY_ENABLE_ASSERTS
    #define CY_ASSERT(x, ...) { if(!(x)) { CY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CY_CORE_ASSERT(x, ...) { if(!(x)) { CY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define CY_ASSERT(x, ...)
    #define CY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif //CAYENNE_CORE_H

