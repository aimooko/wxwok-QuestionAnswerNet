/*
 * PluginPreferences.h
 *
 *  Created on: May 5, 2012
 *      Author: xuewen
 */

#ifndef PLUGINPREFERENCES_H_
#define PLUGINPREFERENCES_H_
#include <string>
#include <set>
#include "plugin.h"
#include "pluginpref.h"
#include "AccountClient.h"

using namespace std;

namespace QAS {

class PluginPreferences {
public:
	PluginPreferences();
	virtual ~PluginPreferences();

	void initPreferences(PurplePlugin * plugin);
	static PurplePluginPrefFrame* createPurplePrefFrame(PurplePlugin *plugin);
	static PurplePluginUiInfo s_info;
	static void preferenceChanged(const char *name, PurplePrefType type,
			const void* val, void* data);

	set<string>& getAnswerers();
	void setAnswerers(const set<string>& answerers);
	bool isAnswerer(const string& name);
	set<string>& getAskers();
	void setAskers(const set<string>& askers);
	bool isAsker(const string& name);
	set<string>& getServers();
	void setServers(const set<string>& servers);
	bool isServer(const string& name);

	AccountClient::AccountType clientType(const string& name);

private:
	static const string s_askersPrefName;
	static const string s_answerersPrefName;
	static const string s_serversPrefName;

	static const string s_prefKeyRoot;
	static const string s_keyNameAskers;
	static const string s_keyNameAnswers;
	static const string s_keyNameServers;

	set<string> m_askers;
	set<string> m_answerers;
	set<string> m_servers;
};

} /* namespace QAS */
#endif /* PLUGINPREFERENCES_H_ */
