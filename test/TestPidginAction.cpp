/*
 * TestPidginAction.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */
#include <cmds.h>
#include <debug.h>
#include <notify.h>
#include <plugin.h>
#include <string.h>
#include <version.h>
#include <xmlnode.h>

#include "TestPidginAction.h"
#include "TestPidginBuddyList.h"

#include "TestPidginFile.h"
#include "TestPidginIm.h"
namespace QAS {
/* This function is the callback for the plugin action we added. All we're
 * doing here is displaying a message. When the user selects the plugin
 * action, this function is called. */
static PurplePlugin* question_and_answer_plugin = NULL;
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

static void
notify_test_buddy_cb(PurplePluginAction *action)
{
	TestPidginBuddyList::testBuddy();
}


static void
notify_test_file_cb(PurplePluginAction *action)
{
	TestPidginFile::run();
}

static const char* msg =
               "<message type='chat'"
               " to='xuewen@localhost'>"
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
               if (strcmp(gc->display_name, "test@localhost/QAS") == 0)
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
GList *
plugin_actions (PurplePlugin * plugin, gpointer context)
{
	question_and_answer_plugin = plugin;
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

    list = g_list_prepend(list,
        purple_plugin_action_new("Test Buddy", notify_test_buddy_cb));

    list = g_list_prepend(list,
    		purple_plugin_action_new("Test file", notify_test_file_cb));

    list = g_list_prepend(list,
    		purple_plugin_action_new("Test jabber Send", notify_test_jabber_send_cb));

    list = TestPidginIm::initTest(plugin, context, list);

    /* Once the list is complete, we send it to libpurple. */
	return g_list_reverse(list);
}


} /* namespace QAS */
