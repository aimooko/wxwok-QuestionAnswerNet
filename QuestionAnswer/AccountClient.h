/*
 * Account.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_


#include "account.h"
#include <boost/shared_ptr.hpp>
#include <string>

namespace QAS {
class Asker;
class Answerer;
class Server;
class AccountClient {
public:
	enum AccountType {AskerType, AnswererType, ServerType, OtherType};
	AccountClient();
	AccountClient(PurpleAccount* account, AccountType type);
	virtual ~AccountClient();

	void onLogin();
	void onLogout();

	void onMessage();
	void sendMessage();

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

	bool isAsker() const { return m_type == AskerType; }
	boost::shared_ptr<Asker> toAsker();
	bool isAnswerer() const { return m_type == AnswererType; }
	boost::shared_ptr<Answerer> toAnswerer();
	bool isServer() const { return m_type == ServerType; }
	boost::shared_ptr<Server> toServer();
	bool isOther() const { return m_type == OtherType; }
protected:
	PurpleAccount* m_purpleAccount;
	AccountType m_type;
};

} /* namespace QAS */
#endif /* ACCOUNT_H_ */
