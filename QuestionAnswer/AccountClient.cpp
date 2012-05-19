/*
 * Account.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#include "AccountClient.h"
namespace QAS {

AccountClient::AccountClient() :
	m_purpleAccount(0)
	, m_type(AccountClient::OtherType)

{
}

AccountClient::AccountClient(PurpleAccount* account, AccountType type) :
	m_purpleAccount(account)
	, m_type(type)
{
}

AccountClient::~AccountClient() {
}

} /* namespace QAS */
