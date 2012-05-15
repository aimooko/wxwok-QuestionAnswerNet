/*
 * TestPidginPluginPreference.h
 *
 *  Created on: Apr 27, 2012
 *      Author: xuewen
 */

#ifndef TESTPIDGINPLUGINPREFERENCE_H_
#define TESTPIDGINPLUGINPREFERENCE_H_
#include "plugin.h"

namespace QAS {

class TestPidginPluginPreference {
public:
	TestPidginPluginPreference();
	virtual ~TestPidginPluginPreference();
};

extern PurplePluginUiInfo prefs_info;
void init_test_plugin(PurplePlugin *plugin);
} /* namespace QAS */
#endif /* TESTPIDGINPLUGINPREFERENCE_H_ */
