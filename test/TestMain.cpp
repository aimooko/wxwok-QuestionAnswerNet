//#ifdef HAVE_CONFIG_H
# include <config.h>
//#endif

#define PURPLE_PLUGINS
#include <plugin.h>

#include "Test.h"
#include "TestPidginPluginPreference.h"
using namespace QAS;
static void
init_plugin (PurplePlugin * plugin)
{
	init_test_plugin(plugin);
}
extern "C" {
PURPLE_INIT_PLUGIN (QuestionAnswerTest, init_plugin, g_testPluginInfo)
}
