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

namespace QAS {
PurplePluginInfo QASPlugin::s_pluginInfo = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,
	NULL,
	0,
	NULL,
	PURPLE_PRIORITY_DEFAULT,

	"question_answer_client", 						// PLUGIN_ID
	"Question & Answer client",				// name
	"1.0",									// version

	"答题系统",												// char *summary;
	"接受问题，通过网络分发。接受答案，通过网络传回。记录成绩。",		// char *description;
	"Sean Wang xuewen.ok@gmail.com", /* correct author */	// char *author;
	"http://www.wxwok.com",									// char *homepage;


	QASPlugin::plugin_load,
	QASPlugin::plugin_unload,
	NULL,

	NULL,
	NULL,
	&PluginPreferences::s_info,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL
};

QASPlugin* QASPlugin::s_instance = 0;

QASPlugin* QASPlugin::instance(PurplePlugin* plugin)
{
	if (!s_instance)
		s_instance = new QASPlugin(plugin);
	else
		assert(QASPlugin::s_instance->m_plugin == plugin);
	return s_instance;
}

void QASPlugin::init_plugin (PurplePlugin * plugin)
{
	instance(plugin)->m_preference.initPreferences(plugin);
}

gboolean QASPlugin::plugin_load (PurplePlugin * plugin)
{
	instance(plugin);
	return TRUE;
}

gboolean QASPlugin::plugin_unload(PurplePlugin *plugin)
{
	delete s_instance;
	s_instance = 0;
  return TRUE;
}

void QASPlugin::accountSignonHandler(PurpleAccount *account)
{
	purple_debug_info("QASPlugin", "On account login");
	if (account) {
		m_accoutManager.addClient(account);
		purple_debug_info("QASPlugin", "account added in to manager");
	}
}

void QASPlugin::accountSignoffHandler(PurpleAccount *account)
{
	purple_debug_info("QASPlugin", "On account logout");
	if (account) {
		m_accoutManager.removeClient(account);
		purple_debug_info("QASPlugin", "account removed");
	}
}

QASPlugin::QASPlugin(PurplePlugin* plugin)
: m_plugin(plugin)
{
	 purple_signal_connect(purple_accounts_get_handle(), "account-signed-on", plugin, PURPLE_CALLBACK(accountSignonHandler), this);
	 purple_signal_connect(purple_accounts_get_handle(), "account-signed-off", plugin, PURPLE_CALLBACK(accountSignoffHandler), this);
}

QASPlugin::~QASPlugin()
{
	 purple_signal_disconnect(purple_accounts_get_handle(), "account-signed-on", m_plugin, PURPLE_CALLBACK(accountSignonHandler));
	 purple_signal_disconnect(purple_accounts_get_handle(), "account-signed-off", m_plugin, PURPLE_CALLBACK(accountSignoffHandler));
}


} /* namespace QAS */
