/*
 * TestPidginCommand.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef TESTPIDGINCOMMAND_H_
#define TESTPIDGINCOMMAND_H_
#include <plugin.h>

namespace QAS {

void register_commands(PurplePlugin * plugin);
void unregister_commands();
} /* namespace QAS */
#endif /* TESTPIDGINCOMMAND_H_ */
