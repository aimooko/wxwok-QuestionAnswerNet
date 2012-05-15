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
#include "StateMachines/Asker_sm.h"
namespace QAS {
class Asker {
public:
	Asker();
	virtual ~Asker();

	virtual void ask() = 0;
	virtual void answerReceived() = 0;
	virtual void replyAnswerRight(bool) = 0;

	virtual void getCredits() = 0;
	virtual void creditsReceived() = 0;

};
}
#endif /* ASKER_H_ */
