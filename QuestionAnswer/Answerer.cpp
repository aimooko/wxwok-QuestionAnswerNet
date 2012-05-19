/*
 * Answerer.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

#include "Answerer.h"
#include "AccountClient.h"

namespace QAS {
Answerer::Answerer() :
	//m_type(AccountClient::AnswererType)
	m_stateContext(*this)
	{
	// TODO Auto-generated constructor stub
	m_type = AccountClient::AnswererType;

}

Answerer::~Answerer() {
	// TODO Auto-generated destructor stub
}
}
