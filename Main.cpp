//#ifdef HAVE_CONFIG_H
# include <config.h>
//#endif

#define PURPLE_PLUGINS
#include <plugin.h>

#define IS_TEST 0
#if IS_TEST
#include "Test.h"
#include "TestPidginPluginPreference.h"
using namespace QAS;
static void
init_plugin (PurplePlugin * plugin)
{
	init_test_plugin(plugin);
}
extern "C" {
PURPLE_INIT_PLUGIN (hello_world, init_plugin, g_testPluginInfo)
}

#else
#include "QASPlugin.h"
using namespace QAS;
extern "C" {
PURPLE_INIT_PLUGIN (QuestionAnswer, QASPlugin::init_plugin, QASPlugin::s_pluginInfo);
}
#endif
