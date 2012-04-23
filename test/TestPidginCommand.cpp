/*
 * TestPidginCommand.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#include "TestPidginCommand.h"
#include <cmds.h>
#include <debug.h>
#include <notify.h>
#include <plugin.h>
#include <string.h>
#include <version.h>
#include <xmlnode.h>

namespace QAS {

#define PLUGIN_ID "question_answer_client"
static PurplePlugin* question_and_answer_plugin;
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

void register_commands(PurplePlugin * plugin)
{
	question_and_answer_plugin = plugin;
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

void unregister_commands()
{
	  purple_cmd_unregister(log_command_id);
	  purple_cmd_unregister(notify_command_id);
}


} /* namespace QAS */
