/*
 * Hello World Plugin
 *
 * Copyright (C) 2004, Gary Kramlich <grim@guifications.org>,
 *               2007, John Bailey <rekkanoryo@cpw.pidgin.im>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02111-1301, USA.
 *
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* config.h may define PURPLE_PLUGINS; protect the definition here so that we
 * don't get complaints about redefinition when it's not necessary. */
#ifndef PURPLE_PLUGINS
# define PURPLE_PLUGINS
#endif

#include <glib.h>

/* This will prevent compiler errors in some instances and is better explained in the
 * how-to documents on the wiki */
#ifndef G_GNUC_NULL_TERMINATED
# if __GNUC__ >= 4
#  define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
# else
#  define G_GNUC_NULL_TERMINATED
# endif
#endif

#include <cmds.h>
#include <debug.h>
#include <notify.h>
#include <plugin.h>
#include <string.h>
#include <version.h>
#include <xmlnode.h>

#define PLUGIN_ID "question_answer_client"


/* we're adding this here and assigning it in plugin_load because we need
 * a valid plugin handle for our call to purple_notify_message() in the
 * plugin_action_test_cb() callback function */
PurplePlugin *question_and_answer_plugin = NULL;

/* This function is the callback for the plugin action we added. All we're
 * doing here is displaying a message. When the user selects the plugin
 * action, this function is called. */
static void
plugin_action_test_cb (PurplePluginAction * action)
{
	purple_notify_message (question_and_answer_plugin, PURPLE_NOTIFY_MSG_INFO,
		"Question & Answer client", "This is a plugin of Question and Answer client", NULL, NULL,
		NULL);
}

/* The next four functions and the calls within them should cause dialog boxes to appear
 * when you select the plugin action from the Tools->Notify Example menu */
static void
notify_error_cb(PurplePluginAction *action)
{
    purple_notify_error(question_and_answer_plugin, "Test Notification", "Test Notification",
        "This is a test error notification");
}

static void
notify_info_cb(PurplePluginAction *action)
{
    purple_notify_info(question_and_answer_plugin, "Test Notification", "Test Notification",
        "This is a test informative notification");
}

static void
notify_warn_cb(PurplePluginAction *action)
{
    purple_notify_warning(question_and_answer_plugin, "Test Notification", "Test Notification",
        "This is a test warning notification");
}

static void
notify_format_cb(PurplePluginAction *action)
{
    purple_notify_formatted(question_and_answer_plugin, "Test Notification", "Test Notification",
        "Test Notification",
        "<I>This is a test notification with formatted text.</I>", NULL, NULL);
}

static void
notify_uri_cb(PurplePluginAction *action)
{
    /* This one should open your web browser of choice. */
    purple_notify_uri(question_and_answer_plugin, "http://www.pidgin.im/");
}

const char* msg =
		"<message type='chat'"
		" to='test@localhost'>"
		"<active xmlns='http://jabber.org/protocol/chatstates'/>"
		"<body>test</body>"
		"</message>";
static void
notify_test_jabber_send_cb(PurplePluginAction *action)
{
	xmlnode* message;
	xmlnode* body;
	message = xmlnode_new("message");
 	xmlnode_set_attrib(message, "from", "xuewen@localhost/develop");
 	xmlnode_set_attrib(message, "to", "test@localhost");
 	xmlnode_set_attrib(message, "type", "chat");

 	body = xmlnode_new_child(message, "body");
 	const char* body_data = "this is a test stanza";
 	body->data = (char*)body_data;
 	body->data_sz = strlen(body_data);

 	// get a connection and emit it
 	GList* connections = purple_connections_get_all();
 	GList* connection = g_list_first(connections);
	PurpleConnection * gc_xuewen = 0;
 	while(connection) {
 		PurpleConnection * gc = (PurpleConnection*) connection->data;
 		if (strcmp(gc->display_name, "xuewen@localhost/develop") == 0)
 			gc_xuewen = gc;
 		connection = g_list_next(connection);
 	}
/*
 	const gchar* id = purple_plugin_get_id(gc_xuewen->prpl);
 	if (strcmp(id, prpl-jabber) == 0) {

 	}
*/
 	PurplePlugin* plugin = purple_connection_get_prpl(gc_xuewen);
 	PurplePluginProtocolInfo* info = PURPLE_PLUGIN_PROTOCOL_INFO(plugin);
 	info->send_raw(gc_xuewen, msg, strlen(msg));
 	//serv_send_im(gc_xuewen, "test@localhost", "this is a test", PURPLE_MESSAGE_SEND);
}

/* we tell libpurple in the PurplePluginInfo struct to call this function to
 * get a list of plugin actions to use for the plugin.  This function gives
 * libpurple that list of actions. */
static GList *
plugin_actions (PurplePlugin * plugin, gpointer context)
{
	/* some C89 (a.k.a. ANSI C) compilers will warn if any variable declaration
	 * includes an initilization that calls a function.  To avoid that, we
	 * generally initialize our variables first with constant values like NULL
	 * or 0 and assign to them with function calls later */
	GList *list = NULL;
	PurplePluginAction *action = NULL;

	/* The action gets created by specifying a name to show in the UI and a
	 * callback function to call. */
	action = purple_plugin_action_new ("Questions & Answers", plugin_action_test_cb);

	/* libpurple requires a GList of plugin actions, even if there is only one
	 * action in the list.  We append the action to a GList here. */
	list = g_list_append (list, action);

    /* Here we take advantage of return values to avoid the need for a temp variable */
    list = g_list_prepend(list,
        purple_plugin_action_new("Show Error Notification", notify_error_cb));

    list = g_list_prepend(list,
        purple_plugin_action_new("Show Info Notification", notify_info_cb));

    list = g_list_prepend(list,
        purple_plugin_action_new("Show Warning Notification", notify_warn_cb));

    list = g_list_prepend(list,
        purple_plugin_action_new("Show Formatted Notification", notify_format_cb));

    list = g_list_prepend(list,
        purple_plugin_action_new("Show URI Notification", notify_uri_cb));

    list = g_list_prepend(list, purple_plugin_action_new("Test Send IQ to test", notify_test_jabber_send_cb));

    /* Once the list is complete, we send it to libpurple. */
	return g_list_reverse(list);
}

/**
 * Used to hold a handle to the commands we register. Holding this handle
 * allows us to unregister the commands at a later time.
 */
static PurpleCmdId log_command_id, notify_command_id;

/**
 * The callback function for our /log command. This function simply prints
 * whatever was entered as the argument to the debug command into the debug
 * log.
 *
 * @param conv The conversation that the command occurred in
 * @param cmd The exact command that was entered
 * @param args The args that were passed with the command
 * @param error ?Any errors that occurred?
 * @param data Any special user-defined data that was assigned during
 *             cmd_register
 */
static PurpleCmdRet
log_cb(PurpleConversation *conv, const gchar *cmd, gchar **args, gchar **error, void *data)
{
  purple_debug_misc(PLUGIN_ID, "log_cb called\n");
  purple_debug_misc(PLUGIN_ID, "message = %s\n", args[0]);

  return PURPLE_CMD_RET_OK;

}

/**
 * The callback function for our /notify command. This function simply pops up
 * a notification with the word entered as the argument to the command
 *
 * @param conv The conversation that the command occurred in
 * @param cmd The exact command that was entered
 * @param args The args that were passed with the command
 * @param error ?Any errors that occurred?
 * @param data Any special user-defined data that was assigned during
 *             cmd_register
 */
static PurpleCmdRet
notify_cb(PurpleConversation *conv, const gchar *cmd, gchar **args, gchar **error, void *data)
{

  purple_notify_info(question_and_answer_plugin,
                     "Notify Notification Title",
                     "Notify Notification Primary Text",
                     args[0]);   /* Secondary text is the word entered */

  return PURPLE_CMD_RET_OK;

}

static void register_commands(PurplePlugin * plugin)
{
	  // Declare all vars up front. Avoids warnings on some compilers
	  gchar *log_help = NULL;
	  gchar *notify_help = NULL;
	  // Help message for log command, in the correct format
	   log_help = (gchar*) "log &lt;log message here&gt;:  Prints a message to the debug log.";

	   // Register a command to allow a user to enter /log some message and have
	   // that message stored to the log. This command runs with default priority,
	   // can only be used in a standard chat message, not while in group chat
	   // mode
	   log_command_id = purple_cmd_register
	     ("log",                         /* command name */
	      "s",                           /* command argument format */
	      PURPLE_CMD_P_DEFAULT,          /* command priority flags */
	      PURPLE_CMD_FLAG_IM,            /* command usage flags */
	      PLUGIN_ID,                     /* Plugin ID */
	      log_cb,                        /* Name of the callback function */
	      log_help,                      /* Help message */
	      NULL                           /* Any special user-defined data */
	      );


	   // Help message for notify command, in the correct format
	   notify_help = (gchar*) "notify &lt;notify word here&gt;:  Pops up a notification with the word you enter.";

	   // Register a command to allow a user to enter /notify some word and have
	   // that word notified back to them. This command runs with high priority,
	   // and can be used in both group and standard chat messages
	   notify_command_id = purple_cmd_register
	     ("notify",                      /* command name */
	      "w",                           /* command argument format */
	      PURPLE_CMD_P_HIGH,             /* command priority flags */
	      (PurpleCmdFlag)(PURPLE_CMD_FLAG_IM |
	        PURPLE_CMD_FLAG_CHAT),        /* command usage flags */
	      PLUGIN_ID,                     /* Plugin ID */
	      notify_cb,                     /* Callback function */
	      notify_help,                   /* Help message */
	      NULL                           /* Any special user-defined data */
	      );
}

static void unregister_commands()
{
	  purple_cmd_unregister(log_command_id);
	  purple_cmd_unregister(notify_command_id);
}

static void testIqSignle(PurplePlugin * plugin)
{
//purple_signal_connect(purple_plugins_get_handle(), "jabber-receiving-iq", PURPLE_CALLBACK(iq_cb), NULL);
}

static gboolean
plugin_load (PurplePlugin * plugin)
{
	purple_notify_message (plugin, PURPLE_NOTIFY_MSG_INFO, "Questions & Answers!",
		"This is Questions & Answers! plugin :)", NULL, NULL,
		NULL);

	question_and_answer_plugin = plugin; /* assign this here so we have a valid handle later */

	register_commands(question_and_answer_plugin);

	testIqSignle(plugin);

	return TRUE;
}

/**
 * Because we added a pointer to this function in the unload section of our
 * PurplePluginInfo, this function is called when the plugin unloads.
 * Here we're using it to show off the capabilities of the
 * command API by unregistering a few commands. We return TRUE to tell libpurple
 * it's safe to continue unloading.
 */
static gboolean
plugin_unload(PurplePlugin *plugin)
{

	unregister_commands();
  /* Just return true to tell libpurple to finish unloading. */
  return TRUE;
}

/* For specific notes on the meanings of each of these members, consult the C Plugin Howto
 * on the website. */
static PurplePluginInfo info = {
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

static void
init_plugin (PurplePlugin * plugin)
{
}
extern "C" {
PURPLE_INIT_PLUGIN (hello_world, init_plugin, info)
}
