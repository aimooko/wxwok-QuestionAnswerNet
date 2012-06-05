/*
 * PidginPlugin.cpp
 *
 *  Created on: May 5, 2012
 *      Author: xuewen
 */

#include "QASPlugin.h"

#include <assert.h>
#include "plugin.h"
#include "signals.h"
#include "version.h"
#include "debug.h"
#include "conversation.h"
#include <string>
using namespace std;

#include "Asker.h"

namespace QAS {
PurplePluginInfo QASPlugin::s_pluginInfo = { PURPLE_PLUGIN_MAGIC,
		PURPLE_MAJOR_VERSION, PURPLE_MINOR_VERSION, PURPLE_PLUGIN_STANDARD,
		NULL, 0, NULL, PURPLE_PRIORITY_DEFAULT,

		"question_answer_client", // PLUGIN_ID
		"Question & Answer client", // name
		"1.0", // version

		"答题系统", // char *summary;
		"接受问题，通过网络分发。接受答案，通过网络传回。记录成绩。", // char *description;
		"Sean Wang xuewen.ok@gmail.com", /* correct author */ // char *author;
		"http://www.wxwok.com", // char *homepage;

		QASPlugin::plugin_load, QASPlugin::plugin_unload, NULL,

		NULL, NULL, &PluginPreferences::s_info,

		QASPlugin::actionCallback,

		NULL, NULL, NULL, NULL };

QASPlugin* QASPlugin::s_instance = 0;

QASPlugin* QASPlugin::instance(PurplePlugin* plugin) {
	if (!s_instance)
		s_instance = new QASPlugin(plugin);
	else
		assert(QASPlugin::s_instance->m_plugin == plugin);
	return s_instance;
}

void QASPlugin::init_plugin(PurplePlugin * plugin) {
	instance(plugin)->m_preference.initPreferences(plugin);
}

gboolean QASPlugin::plugin_load(PurplePlugin * plugin) {
	assert(instance());
/*
	purple_signal_connect(purple_plugins_get_handle(), "plugin-load",
			plugin, PURPLE_CALLBACK(pluginLoadHandler), instance());
	purple_signal_connect(purple_plugins_get_handle(), "plugin-unload",
			plugin, PURPLE_CALLBACK(pluginUnloadHandler), instance());
*/
	// connect account signals
	purple_signal_connect(purple_accounts_get_handle(), "account-signed-on",
			plugin, PURPLE_CALLBACK(accountSignonHandler), instance());
	purple_signal_connect(purple_accounts_get_handle(), "account-signed-off",
			plugin, PURPLE_CALLBACK(accountSignoffHandler), instance());

	// register qas_ask command
	instance()->m_qas_askCmdId = purple_cmd_register("qas_ask", "s",
			PURPLE_CMD_P_DEFAULT, PURPLE_CMD_FLAG_IM, plugin->info->id,
			onAskCommand, "Ask for verification code from picture file",
			instance());

	return TRUE;
}

gboolean QASPlugin::plugin_unload(PurplePlugin *plugin) {
/*
	purple_signal_disconnect(purple_plugins_get_handle(), "plugin-load",
			plugin, PURPLE_CALLBACK(pluginUnloadHandler));
	purple_signal_disconnect(purple_plugins_get_handle(), "plugin-unload",
			plugin, PURPLE_CALLBACK(pluginUnloadHandler));
*/
	// disconnect account signals
	purple_signal_disconnect(purple_accounts_get_handle(), "account-signed-on",
			plugin, PURPLE_CALLBACK(accountSignonHandler));
	purple_signal_disconnect(purple_accounts_get_handle(), "account-signed-off",
			plugin, PURPLE_CALLBACK(accountSignoffHandler));

	purple_cmd_unregister(instance()->m_qas_askCmdId);
	delete s_instance;
	s_instance = 0;
	return TRUE;
}

PurpleCmdRet QASPlugin::onAskCommand(PurpleConversation * conv, const gchar *cmd,
		gchar **args, gchar **error, void *data) {
	gchar* path = args[0];
	assert(path);
	purple_debug_info("QASPlugin", "OnAskCommand: path= %s\n", args[0]);
	if (shared_ptr<Asker> asker = instance()->m_accoutManager.getBestAsker()) {
		asker->ask(path);
		switch (conv->type) {
		case PURPLE_CONV_TYPE_IM:
			purple_conv_im_send_with_flags(conv->u.im,
					(string("Question sent, path: ") + path).c_str(),
					PURPLE_MESSAGE_SYSTEM);
			break;
		case PURPLE_CONV_TYPE_CHAT:
			purple_conv_chat_send_with_flags(conv->u.chat,
					(string("Question sent, path: ") + path).c_str(),
					PURPLE_MESSAGE_SYSTEM);
			break;
		}
		return PURPLE_CMD_RET_OK;
	} else {
		purple_debug_info("QASPlugin", "Ask failed\n");
		switch (conv->type) {
		case PURPLE_CONV_TYPE_IM:
			purple_conv_im_send_with_flags(conv->u.im,
					(string("Didn't find a asker, path: ") + path).c_str(),
					PURPLE_MESSAGE_NOTIFY);
			break;
		case PURPLE_CONV_TYPE_CHAT:
			purple_conv_chat_send_with_flags(conv->u.chat,
					(string("Didn't find a asker, path: ") + path).c_str(),
					PURPLE_MESSAGE_NOTIFY);
			break;
		}
		return PURPLE_CMD_RET_FAILED;
	}
}

void QASPlugin::accountSignonHandler(PurpleAccount *account) {
	purple_debug_info("QASPlugin", "On account login: %s, \n", account->username);
	if (account) {
		QASPlugin* plugin = instance();
		shared_ptr<AccountClient> ac = plugin->m_accoutManager.addClient(
				account, plugin->m_preference.clientType(account->username));
		if (ac)
			ac->onLogin();
		purple_debug_info("QASPlugin", "Account added in to manager: %s", account->username);
	}
}

void QASPlugin::accountSignoffHandler(PurpleAccount *account) {
	purple_debug_info("QASPlugin", "On account logout: %s\n", account->username);
	if (account) {
		purple_debug_info("QASPlugin", "account removed %s\n", account->username);
		shared_ptr<AccountClient> ac = instance()->m_accoutManager.getClient(account);
		if (!ac)
			return;
		ac->onLogout();
		instance()->m_accoutManager.removeClient(ac);
	}
}

void QASPlugin::pluginLoadHandler(PurplePlugin *plugin)
{
	purple_debug_info("QASPlugin", " on Plugin load: %s\n", plugin->info->id);
	return;
	if (!instance())
		return;
}

void QASPlugin::pluginUnloadHandler(PurplePlugin *plugin)
{
	purple_debug_info("QASPlugin", "on Plugin unload: %s\n", plugin->info->id);
	return;
	if (!instance())
		return;
}

GList * QASPlugin::actionCallback(PurplePlugin * plugin, gpointer context)
{
	GList* list = 0;
	list = g_list_prepend(list,
	        purple_plugin_action_new("QASPlugin Test", QASPlugin::onTest));
	return list;
}

void QASPlugin::onTest(PurplePluginAction* action)
{
	const char* fromName = "test@localhost/QAS";
	const char* toName = "xuewen@localhost/winxp";
	const char* protocol = "prpl-jabber";
	PurpleAccount * account = purple_accounts_find(fromName, protocol);
	if (!account) {
		purple_debug_info("TestQAS Test file", "find accout faile");
		return;
	}

	PurpleConnection * conn = purple_account_get_connection(account);
	PurplePluginProtocolInfo * prpl = PURPLE_PLUGIN_PROTOCOL_INFO(purple_connection_get_prpl(conn));
	prpl->send_im(conn, toName, "/tmp/tmp.txt", PURPLE_MESSAGE_INVISIBLE);
}

QASPlugin::QASPlugin(PurplePlugin* plugin) :
	m_plugin(plugin)
	, m_qas_askCmdId(0)
{
}

QASPlugin::~QASPlugin() {
}

} /* namespace QAS */
