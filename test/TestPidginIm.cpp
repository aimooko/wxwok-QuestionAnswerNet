/*
 * TestPidginIm.cpp
 *
 *  Created on: May 22, 2012
 *      Author: xuewen
 */

#include "TestPidginIm.h"
#include "prpl.h"
#include "string.h"
#include "debug.h"
namespace QAS {

TestPidginIm::TestPidginIm() {
	// TODO Auto-generated constructor stub

}

TestPidginIm::~TestPidginIm() {
	// TODO Auto-generated destructor stub
}
const char* msg =
		"<message type='chat'"
		" to='xuewen@localhost'>"
		"<body>test</body>"
		"</message>";

const char* iq =
		"<iq type='get' id=1"
		" to='xuewen@localhost'>"
		" <query>test</query>"
		"</iq>";

void TestPidginIm::testSendIQ(PurplePluginAction* action) {
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
	prpl->send_raw(conn, msg, strlen(msg));
	prpl->send_raw(conn, iq, strlen(iq));
}

void TestPidginIm::testReceivceIQ(PurplePluginAction* action) {
}

void TestPidginIm::testSendNotification(PurplePluginAction* action) {
}

GList* TestPidginIm::initTest(PurplePlugin * plugin, gpointer context, GList* list) {
	list = g_list_prepend(list,
	        purple_plugin_action_new("TestPidginIm test send IQ", testSendIQ));
	return list;
}

} /* namespace QAS */
