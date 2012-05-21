/*
 * Account.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#include "AccountClient.h"
#include <boost/shared_ptr.hpp>
#include "Asker.h"
#include "Answerer.h"
#include "Server.h"

using namespace boost;
namespace QAS {

AccountClient::AccountClient() :
		m_purpleAccount(0), m_type(AccountClient::OtherType)

{
}

AccountClient::AccountClient(PurpleAccount* account, AccountType type) :
		m_purpleAccount(account), m_type(type) {
}

AccountClient::~AccountClient() {
}

void AccountClient::onLogin() {
}

void AccountClient::onLogout() {
}

void AccountClient::onMessage() {
}

void AccountClient::sendMessage() {
}

shared_ptr<Asker> AccountClient::toAsker() {
	if (isAsker())
		return shared_ptr<Asker>(static_cast<Asker*>(this));
	else
		return shared_ptr<Asker>();
}
shared_ptr<Answerer> AccountClient::toAnswerer() {
	if (isAnswerer())
		return shared_ptr<Answerer>(static_cast<Answerer*>(this));
	else
		return shared_ptr<Answerer>();
}
shared_ptr<Server> AccountClient::toServer() {
	if (isServer())
		return shared_ptr<Server>(static_cast<Server*>(this));
	else
		return shared_ptr<Server>();
}

} /* namespace QAS */
