/*
 * AccountManager.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_
#include "AccountClient.h"

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
using namespace std;
using namespace boost;

#include "account.h"
namespace QAS {

class AccountClientManager {
public:
	typedef map<string, shared_ptr<AccountClient> > AccountMap;
	AccountClientManager();
	virtual ~AccountClientManager();

	void addClient(shared_ptr<AccountClient> account);
	shared_ptr<AccountClient> addClient(PurpleAccount*);
	shared_ptr<AccountClient> addClient(PurpleAccount* account, AccountClient::AccountType type);
	shared_ptr<AccountClient> getClient(PurpleAccount *account);
	AccountMap& accounts() { return m_accounts; }
	bool removeClient(shared_ptr<AccountClient> account);
	bool removeClient(PurpleAccount*);

	shared_ptr<Asker> getBestAsker();
private:
	AccountMap m_accounts;

};
}
#endif /* ACCOUNTMANAGER_H_ */
