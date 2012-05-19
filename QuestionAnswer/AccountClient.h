/*
 * Account.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <boost/shared_ptr.hpp>

#include "account.h"

namespace QAS {

class AccountClient {
public:
	enum AccountType {AskerType, AnswererType, ServerType, OtherType};
	AccountClient();
	AccountClient(PurpleAccount* account, AccountType type);
	virtual ~AccountClient();

	void onLogin();
	void onLogout();

	virtual void onMessage() {}
	void sendMessage() {}

	AccountType getType() const {
		return m_type;
	}

	void setType(AccountType type) {
		m_type = type;
	}

	PurpleAccount* getPurpleAccount() const {
		return m_purpleAccount;
	}

	void setPurpleAccount(PurpleAccount* purpleAccount) {
		m_purpleAccount = purpleAccount;
	}
protected:
	PurpleAccount* m_purpleAccount;
	AccountType m_type;
};

} /* namespace QAS */
#endif /* ACCOUNT_H_ */
