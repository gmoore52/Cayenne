#ifndef CAYENNE_CORE_H
#define CAYENNE_CORE_H

#ifdef CY_PLATFORM_WINDOWS
    #ifdef CY_BUILD_DLL
        #define CY_API __declspec(dllexport)
    #else
        #define CY_API __declspec(dllimport)
    #endif
#else
    #error "Currently only windows support for Cayenne"
#endif

#define BIT(x) (1 << x)

#endif //CAYENNE_CORE_H

