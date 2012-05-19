/*
 * PluginPreferences.cpp
 *
 *  Created on: May 5, 2012
 *      Author: xuewen
 */

#include "PluginPreferences.h"

#include "assert.h"
#include "prefs.h"
#include <sstream>
#include <streambuf>
#include <cstring>
using namespace std;

namespace QAS {
const string PluginPreferences::s_askersPrefName = "提问帐号名单：";
const string PluginPreferences::s_answerersPrefName = "回答帐号名单：";
const string PluginPreferences::s_serversPrefName = "服务器帐号名单：";
const string PluginPreferences::s_prefKeyRoot = "/plugins/core/question_answer";
const string PluginPreferences::s_keyNameAskers = "askers";
const string PluginPreferences::s_keyNameAnswers = "answerers";
const string PluginPreferences::s_keyNameServers = "servers";

PurplePluginUiInfo PluginPreferences::s_info = {
		createPurplePrefFrame,
		0,
		NULL,
		NULL, NULL, NULL, NULL };

PluginPreferences::PluginPreferences() {
	m_askers.insert("asker@localhost");
	m_servers.insert("server@localhost");
	m_answerers.insert("anserer@localhost");
}

PluginPreferences::~PluginPreferences() {
}

set<string>& PluginPreferences::getAnswerers() {
	return m_answerers;
}

void PluginPreferences::setAnswerers(const set<string>& answerers) {
	m_answerers = answerers;
}

set<string>& PluginPreferences::getAskers() {
	return m_askers;
}

void PluginPreferences::setAskers(const set<string>& askers) {
	m_askers = askers;
}

set<string>& PluginPreferences::getServers() {
	return m_servers;
}

void PluginPreferences::preferenceChanged(const char* name, PurplePrefType type,
		const void* val, void* pref) {
	assert(type == PURPLE_PREF_STRING);
	PluginPreferences* preference = static_cast<PluginPreferences*>(pref);
	set < string > *prefs = 0;
	string nameCmp(name);
	if (nameCmp == s_prefKeyRoot + "/" + s_keyNameAskers)
		prefs = &preference->m_askers;
	else if (nameCmp == s_prefKeyRoot + "/" + s_keyNameAskers)
		prefs = &preference->m_answerers;
	else if (nameCmp == s_prefKeyRoot + "/" + s_keyNameAskers)
		prefs = &preference->m_servers;

}
bool PluginPreferences::isAnswerer(const string& name) {
	return m_answerers.find(name) != m_answerers.end();
}

bool PluginPreferences::isAsker(const string& name) {
	return m_askers.find(name) != m_answerers.end();
}

void PluginPreferences::setServers(const set<string>& servers) {
	m_servers = servers;
}

void PluginPreferences::initPreferences(PurplePlugin* plugin) {
	purple_prefs_add_none(s_prefKeyRoot.c_str());
	purple_prefs_add_string((s_prefKeyRoot + "/" + s_keyNameAskers).c_str(),
			"");
	purple_prefs_add_string((s_prefKeyRoot + "/" + s_keyNameAnswers).c_str(),
			"");
	purple_prefs_add_string((s_prefKeyRoot + "/" + s_keyNameServers).c_str(),
			"");
	purple_prefs_connect_callback(purple_plugins_get_handle(),
			s_prefKeyRoot.c_str(), preferenceChanged, this);
}

PurplePluginPrefFrame* PluginPreferences::createPurplePrefFrame(
		PurplePlugin* plugin) {
	PurplePluginPrefFrame* frame;
	PurplePluginPref* ppref;
	frame = purple_plugin_pref_frame_new();
	ppref = purple_plugin_pref_new_with_name_and_label(
			(s_prefKeyRoot + "/" + s_keyNameAskers).c_str(),
			s_askersPrefName.c_str());
	purple_plugin_pref_frame_add(frame, ppref);
	ppref = purple_plugin_pref_new_with_name_and_label(
			(s_prefKeyRoot + "/" + s_keyNameAnswers).c_str(),
			s_answerersPrefName.c_str());
	purple_plugin_pref_frame_add(frame, ppref);
	ppref = purple_plugin_pref_new_with_name_and_label(
			(s_prefKeyRoot + "/" + s_keyNameServers).c_str(),
			s_serversPrefName.c_str());
	purple_plugin_pref_frame_add(frame, ppref);
	return frame;
}

bool PluginPreferences::isServer(const string& name) {
	return m_servers.find(name) != m_answerers.end();
}

AccountClient::AccountType PluginPreferences::clientType(const string& name) {
	if (isAsker(name))
		return AccountClient::AskerType;
	else if (isAnswerer(name))
		return AccountClient::AnswererType;
	else if (isServer(name))
		return AccountClient::ServerType;
	else
		return AccountClient::OtherType;
}

} /* namespace QAS */
