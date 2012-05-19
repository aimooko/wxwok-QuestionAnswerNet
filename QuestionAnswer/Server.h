/*
 * Server.h
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "AccountClient.h"
#include "Server_sm.h"

namespace QAS {
class Server  : public AccountClient {
public:
	Server();
	virtual ~Server();

private:
	ServerContext m_stateContext;
};
}
#endif /* SERVER_H_ */
