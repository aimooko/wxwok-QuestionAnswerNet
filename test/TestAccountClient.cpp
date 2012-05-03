/*
 * AccountClientTest.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#include "plugin.h"
#include "signals.h"
#include "account.h"
#include "debug.h"
#include "TestAccountClient.h"

namespace QAS {

TestAccountClient::TestAccountClient() {
	// TODO Auto-generated constructor stub

}

TestAccountClient::~TestAccountClient() {
	// TODO Auto-generated destructor stub
}

static void on_signOn(PurpleAccount *account)
{
	purple_debug_info("TestAccountClient",
	            "On account login");
}

static void on_signOff(PurpleAccount *account)
{
	purple_debug_info("TestAccountClient",
	            "On account logout");
}

// signals directorys: http://developer.pidgin.im/doxygen/2.7.11/html/pages.html
void testRegisterLoginHandler(PurplePlugin* plugin)
{
	 purple_signal_connect(purple_accounts_get_handle(), "account-signed-on", plugin, PURPLE_CALLBACK(on_signOn), NULL);
	 purple_signal_connect(purple_accounts_get_handle(), "account-signed-off", plugin, PURPLE_CALLBACK(on_signOff), NULL);
}

// Test plugin preference example: pidgin-2.10.2/libpurple/plugins/autoaccept.c

} /* namespace QAS */
