#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <glib.h>
#include <cmds.h>
#include <debug.h>
#include <notify.h>
#include <plugin.h>
#include <string.h>
#include <version.h>
#include <xmlnode.h>

#include "TestPidginCommand.h"
#include "TestPidginAction.h"
#include "TestPidginSignal.h"
#include "TestAccountClient.h"
/* This will prevent compiler errors in some instances and is better explained in the
 * how-to documents on the wiki */
#ifndef G_GNUC_NULL_TERMINATED
# if __GNUC__ >= 4
#  define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
# else
#  define G_GNUC_NULL_TERMINATED
# endif
#endif

namespace QAS {

#define PLUGIN_ID "question_answer_client"

/* we're adding this here and assigning it in plugin_load because we need
 * a valid plugin handle for our call to purple_notify_message() in the
 * plugin_action_test_cb() callback function */
PurplePlugin *question_and_answer_plugin = NULL;

gboolean
plugin_load (PurplePlugin * plugin)
{
	purple_notify_message (plugin, PURPLE_NOTIFY_MSG_INFO, "Questions & Answers!",
		"This is Questions & Answers! plugin :)", NULL, NULL,
		NULL);
	question_and_answer_plugin = plugin; /* assign this here so we have a valid handle later */
	register_commands(question_and_answer_plugin);
	//test_signals_load(plugin);
	testRegisterLoginHandler(plugin);
	return TRUE;
}

/**
 * Because we added a pointer to this function in the unload section of our
 * PurplePluginInfo, this function is called when the plugin unloads.
 * Here we're using it to show off the capabilities of the
 * command API by unregistering a few commands. We return TRUE to tell libpurple
 * it's safe to continue unloading.
 */
gboolean
plugin_unload(PurplePlugin *plugin)
{
	unregister_commands();
	//test_signals_unload(plugin);
  /* Just return true to tell libpurple to finish unloading. */
  return TRUE;
}

/* For specific notes on the meanings of each of these members, consult the C Plugin Howto
 * on the website. */
PurplePluginInfo g_testPluginInfo = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,
	NULL,
	0,
	NULL,
	PURPLE_PRIORITY_DEFAULT,

	PLUGIN_ID,
	(char*)"Question & Answer client",
	(char*)"1.0",

	(char*)"This plugin is the client of Question and Answer system.",
	(char*)"The client response to collect questions and accept answers from agents.",
	(char*)"Sean Wang xuewen.ok@gmail.com", /* correct author */
	(char*)"http://xuewenok.com",


	plugin_load,
	plugin_unload,
	NULL,

	NULL,
	NULL,
	NULL,
	plugin_actions,		/* this tells libpurple the address of the function to call
				   to get the list of plugin actions. */
	NULL,
	NULL,
	NULL,
	NULL
};

} // namespace QAS
