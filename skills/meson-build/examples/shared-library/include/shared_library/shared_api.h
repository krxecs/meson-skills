#pragma once

#if defined(_WIN32)
  #if defined(SHARED_LIBRARY_BUILD)
    #define SHARED_LIBRARY_API __declspec(dllexport)
  #elif defined(SHARED_LIBRARY_USE)
    #define SHARED_LIBRARY_API __declspec(dllimport)
  #else
    #define SHARED_LIBRARY_API
  #endif
#elif defined(__GNUC__) || defined(__clang__)
  #define SHARED_LIBRARY_API __attribute__((visibility("default")))
#else
  #define SHARED_LIBRARY_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

SHARED_LIBRARY_API int shared_library_add(int left, int right);

#ifdef __cplusplus
}
#endif
