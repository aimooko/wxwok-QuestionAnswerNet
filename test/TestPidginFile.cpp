/*
 * TestPidginFile.cpp
 *
 *  Created on: May 21, 2012
 *      Author: xuewen
 */

#include "TestPidginFile.h"
#include "ft.h"
#include "account.h"
#include "assert.h"
#include "debug.h"
#include "connection.h"

namespace QAS {

TestPidginFile::TestPidginFile() {
	// TODO Auto-generated constructor stub

}

TestPidginFile::~TestPidginFile() {
	// TODO Auto-generated destructor stub
}

void TestPidginFile::run()
{
	const char* fromName = "xuewen.ok@gmail.com/QAS";
	const char* toName = "wangxuewen.ok@gmail.com";
	const char* protocol = "prpl-jabber";
	PurpleAccount * account = purple_accounts_find(fromName, protocol);
	if (!account) {
		purple_debug_info("TestQAS Test file", "find accout faile");
		return;
	}

	PurpleConnection * conn = purple_account_get_connection(account);
	PurplePluginProtocolInfo * prpl = PURPLE_PLUGIN_PROTOCOL_INFO(purple_connection_get_prpl(conn));
	prpl->send_file(conn, toName, "/tmp/tmp.txt");
	prpl->send_im(conn, toName, "/tmp/tmp.txt", PURPLE_MESSAGE_NICK);

}
} /* namespace QAS */
