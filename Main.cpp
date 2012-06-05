# include <config.h>

#define PURPLE_PLUGINS
#include <plugin.h>

#include "QASPlugin.h"
using namespace QAS;
extern "C" {
PURPLE_INIT_PLUGIN (QuestionAnswer, QASPlugin::init_plugin, QASPlugin::s_pluginInfo);
}
