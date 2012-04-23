/*
 * Account.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

namespace QAS {

class AccountClient {
public:
	AccountClient();
	virtual ~AccountClient();

	void onLogin();
	void onLogout();
};

} /* namespace QAS */
#endif /* ACCOUNT_H_ */
