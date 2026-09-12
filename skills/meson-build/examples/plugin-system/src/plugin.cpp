#include "plugdemo/plugin_api.hpp"

const char* plugin_name(void) {
  return "sample_plugin";
}

int plugin_entry(void) {
  return 7;
}
