/*
 * TestPidginSignal.h
 *
 *  Created on: Apr 22, 2012
 *      Author: xuewen
 */

#ifndef TESTPIDGINSIGNAL_H_
#define TESTPIDGINSIGNAL_H_
#include <plugin.h>

namespace QAS {
gboolean test_signals_load(PurplePlugin *plugin);
gboolean test_signals_unload(PurplePlugin *plugin);
} /* namespace QAS */
#endif /* TESTPIDGINSIGNAL_H_ */
