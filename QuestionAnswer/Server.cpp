/*
 * Server.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

#include "Server.h"
#include "AccountClient.h"
namespace QAS {
Server::Server() :
	m_stateContext(*this)
{
	// TODO Auto-generated constructor stub
	m_type = AccountClient::ServerType;

}

Server::~Server() {
	// TODO Auto-generated destructor stub
}
}
