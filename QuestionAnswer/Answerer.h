/*
 * Answerer.h
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

#ifndef ANSWERER_H_
#define ANSWERER_H_
#include "AccountClient.h"
#include "Answerer_sm.h"
namespace QAS {
class Answerer  : public AccountClient {
public:
	Answerer();
	virtual ~Answerer();
private:
	AnswererContext m_stateContext;
};
}
#endif /* ANSWERER_H_ */
