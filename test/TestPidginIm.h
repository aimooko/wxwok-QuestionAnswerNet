/*
 * TestPidginIm.h
 *
 *  Created on: May 22, 2012
 *      Author: xuewen
 */

#ifndef TESTPIDGINIM_H_
#define TESTPIDGINIM_H_
#include "plugin.h"
#include "glib.h"

namespace QAS {

class TestPidginIm {
public:
	TestPidginIm();
	virtual ~TestPidginIm();
	static void testSendIQ(PurplePluginAction* action);
	static void testReceivceIQ(PurplePluginAction* action);
	static void testSendNotification(PurplePluginAction* action);
	static GList* initTest(PurplePlugin * plugin, gpointer context, GList* list);
};

} /* namespace QAS */
#endif /* TESTPIDGINIM_H_ */
