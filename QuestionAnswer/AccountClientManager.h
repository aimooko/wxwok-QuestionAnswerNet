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
	void addClient(AccountClient*);
	void addClient(PurpleAccount*);
	void removeClient(AccountClient*);
	void removeClient(PurpleAccount*);
	AccountClientManager();
	virtual ~AccountClientManager();
private:
	AccountMap m_accounts;

};
}
#endif /* ACCOUNTMANAGER_H_ */
