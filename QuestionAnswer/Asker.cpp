/*
 * Asker.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: xuewen
 */

#include "Asker.h"
#include <boost/shared_ptr.hpp>

#include "Asker_sm.h"

namespace QAS {
Asker::Asker() :
    m_stateContext(*this)
	{
	// TODO Auto-generated constructor stub
	m_type = AccountClient::AskerType;

}

Asker::~Asker() {
	// TODO Auto-generated destructor stub
}

/*
 * workaround: ask the first non-blocked and available buddy
 */
void Asker::ask(const std::string& picturePath) {

}
void Asker::getBestAnswerer()
{
//GSList *purple_find_buddies(PurpleAccount *account, const char *name);

}
}
