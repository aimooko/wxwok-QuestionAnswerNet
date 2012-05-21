/*
 * Asker.h
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

/*
 *  AccountClientManager @----------\
 *                                  :
 *                *m_account        :
 *         Asker @----------- AccountClient {sendFile(); sendMessage(); receiveMessage()};
 *           |                      :
 *          \+/                     :
 *  AccountClientListener <---------/
 */


#ifndef ASKER_H_
#define ASKER_H_
#include "Asker.h"
#include <boost/shared_ptr.hpp>
#include "Asker_sm.h"
#include "AccountClient.h"

namespace QAS {

class Asker : public AccountClient {
public:
	Asker();
	virtual ~Asker();

	void ask(const std::string& picturePath);
	virtual void answerReceived() {}
	virtual void replyAnswerRight(bool) {}

	virtual void getCredits() {}
	virtual void creditsReceived() {}

	void getBestAnswerer();

private:
	AskerContext m_stateContext;
};
}
#endif /* ASKER_H_ */
