#pragma once

#if defined(_WIN32)
  #if defined(PLUGIN_BUILD)
    #define PLUGIN_API __declspec(dllexport)
  #else
    #define PLUGIN_API __declspec(dllimport)
  #endif
#elif defined(__GNUC__) || defined(__clang__)
  #define PLUGIN_API __attribute__((visibility("default")))
#else
  #define PLUGIN_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_API const char* plugin_name(void);
PLUGIN_API int plugin_entry(void);

#ifdef __cplusplus
}
#endif
