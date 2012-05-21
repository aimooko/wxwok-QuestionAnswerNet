/*
 * PidginPlugin.h
 *
 *  Created on: May 5, 2012
 *      Author: xuewen
 */

#ifndef PIDGINPLUGIN_H_
#define PIDGINPLUGIN_H_

#include <vector>
#include <string>
using namespace std;

#include "AccountClientManager.h"
#include "glib.h"
#include "plugin.h"
#include "account.h"
#include "cmds.h"

#include "PluginPreferences.h"
namespace QAS {

class QASPlugin {
public:
	static void init_plugin(PurplePlugin * plugin);
	static PurplePluginInfo s_pluginInfo;
	static QASPlugin* instance() { return s_instance ? s_instance : 0; }
	const PurplePlugin* plugin() const { return m_plugin; }

private:
	QASPlugin(PurplePlugin* plugin);
	~QASPlugin();
	static QASPlugin* s_instance;
	static QASPlugin* instance(PurplePlugin* plugin);
	static gboolean plugin_load(PurplePlugin * plugin);
	static gboolean plugin_unload(PurplePlugin *plugin);
	static void pluginLoadHandler(PurplePlugin *plugin);
	static void pluginUnloadHandler(PurplePlugin *plugin);
	static void accountSignonHandler(PurpleAccount *account);
	static void accountSignoffHandler(PurpleAccount *account);
	static PurpleCmdRet  onAskCommand(PurpleConversation *, const gchar *cmd,
            gchar **args, gchar **error, void *data);

	PurplePlugin* m_plugin;
	AccountClientManager m_accoutManager;
	PluginPreferences m_preference;
	PurpleCmdId m_qas_askCmdId;
};
} /* namespace QAS */
#endif /* PIDGINPLUGIN_H_ */
