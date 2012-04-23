/*
 * TestPidginAction.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef TESTPIDGINACTION_H_
#define TESTPIDGINACTION_H_
#include <glib.h>
#include <plugin.h>
namespace QAS {
GList * plugin_actions (PurplePlugin * plugin, gpointer context);
} /* namespace QAS */
#endif /* TESTPIDGINACTION_H_ */
