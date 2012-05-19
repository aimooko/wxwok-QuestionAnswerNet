/*
 * AccountManager.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */


/*
 *
 *            AccountClient* getAccountByName()
 * QASPlugin ---------------------------> AccountClientManager
 *     :                         /-----+---------------+---------------/
 *     \----> AccountClient <|--/  @-Asker----\   @-Answerer----\ @-Server ----\
 *            + login              \-Asker_sm |   \-Answerer_sm | \-Server_sm  |
 *            + logout               Game <---/     agent <-----/   Database <-/
 *            +v bool onMessage
 *            + sendMessage
 *
 *     ask, answer, request, response ......
 */



#include "AccountClientManager.h"
#include "AccountClient.h"
#include "assert.h"
#include "Asker.h"
#include "Answerer.h"
#include "Server.h"

namespace QAS {
AccountClientManager::AccountClientManager() {
}

void AccountClientManager::addClient(shared_ptr<AccountClient> account) {
	m_accounts[account->getPurpleAccount()->username] = account;
}

shared_ptr<AccountClient> AccountClientManager::addClient(
		PurpleAccount* account) {
	shared_ptr<AccountClient> ac(new AccountClient(account, AccountClient::OtherType));
	m_accounts[account->username] = ac;
	return ac;
}

bool AccountClientManager::removeClient(shared_ptr<AccountClient> account) {
	return removeClient(account->getPurpleAccount());
}

bool AccountClientManager::removeClient(PurpleAccount* account) {
	AccountMap::iterator ac = m_accounts.find(account->username);
	if (ac != m_accounts.end()) {
		m_accounts.erase(ac);
		return true;
	} else
		return false;
}
shared_ptr<AccountClient> AccountClientManager::getClient(
		PurpleAccount* account) {
	AccountMap::iterator ac = m_accounts.find(account->username);
	return ac != m_accounts.end() ?
			ac->second :
			shared_ptr<AccountClient>(static_cast<AccountClient*>(0));
}

shared_ptr<AccountClient> AccountClientManager::addClient(
		PurpleAccount* account, AccountClient::AccountType type) {
	assert(type != AccountClient::OtherType);
	shared_ptr<AccountClient> ac;
	switch (type) {
	case AccountClient::AskerType:
		ac.reset(new Asker());
		break;
	case AccountClient::AnswererType:
		ac.reset(new Answerer());
		break;
	case AccountClient::ServerType:
		ac.reset(new Server());
		break;
	case AccountClient::OtherType:
		break;
	}

	if (ac) {
		ac->setPurpleAccount(account);
		ac->setType(type);
		addClient(ac);
	}
	return ac;
}

AccountClientManager::~AccountClientManager() {
}
}

