/*
 * AccountManager.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_
#include "AccountClient.h"

#include "account.h"
namespace QAS {

class AccountClientManager {
public:
	AccountClientManager* instance();
	void addClient(AccountClient*);
	void removeClient(AccountClient*);
	AccountClientManager();
	static AccountClient* createAccount(PurpleAccount *account);
	virtual ~AccountClientManager();

};
}
#endif /* ACCOUNTMANAGER_H_ */
