/*
 * PluginPreferences.h
 *
 *  Created on: May 5, 2012
 *      Author: xuewen
 */

#ifndef PLUGINPREFERENCES_H_
#define PLUGINPREFERENCES_H_
#include <string>
#include <vector>
#include "plugin.h"
#include "pluginpref.h"

using std::string;
using std::vector;

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

	vector<string>& getAnswerers();
	void setAnswerers(const vector<string>& answerers);
	vector<string>& getAskers();
	void setAskers(const vector<string>& askers);
	vector<string>& getServers();
	void setServers(const vector<string>& servers);


private:
	static const string s_askersPrefName;
	static const string s_answerersPrefName;
	static const string s_serversPrefName;

	static const string s_prefKeyRoot;
	static const string s_keyNameAskers;
	static const string s_keyNameAnswers;
	static const string s_keyNameServers;

	vector<string> m_askers;
	vector<string> m_answerers;
	vector<string> m_servers;
};

} /* namespace QAS */
#endif /* PLUGINPREFERENCES_H_ */
