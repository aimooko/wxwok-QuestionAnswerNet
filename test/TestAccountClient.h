/*
 * AccountClientTest.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef ACCOUNTCLIENTTEST_H_
#define ACCOUNTCLIENTTEST_H_

namespace QAS {

class TestAccountClient {
public:
	TestAccountClient();
	virtual ~TestAccountClient();
};
void testRegisterLoginHandler(PurplePlugin* plugin);
} /* namespace QAS */
#endif /* ACCOUNTCLIENTTEST_H_ */
