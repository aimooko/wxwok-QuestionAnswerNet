/*
 * TestPidginPluginPreference.cpp
 *
 *  Created on: Apr 27, 2012
 *      Author: xuewen
 */
#include <glib.h>
/* Purple headers */
#include <debug.h>
#include <plugin.h>
#include <version.h>
#include "Test.h"
#include "TestPidginPluginPreference.h"
#include "pluginpref.h"
#define _(String) ((const char*)String)
namespace QAS {

#define PREF_PREFIX		"/plugins/core/" PLUGIN_ID
#define PREF_PATH		PREF_PREFIX "/path"
#define PREF_STRANGER	PREF_PREFIX "/stranger"
#define PREF_NOTIFY		PREF_PREFIX "/notify"
#define PREF_NEWDIR     PREF_PREFIX "/newdir"
#define PREF_ESCAPE     PREF_PREFIX "/escape"

#define PREF_STRANGER_OLD PREF_PREFIX "/reject_stranger"

typedef enum
{
	FT_ASK,
	FT_ACCEPT,
	FT_REJECT
} AutoAcceptSetting;


PurplePluginPrefFrame *
get_plugin_pref_frame(PurplePlugin *plugin)
{
	PurplePluginPrefFrame *frame;
	PurplePluginPref *ppref;

	frame = purple_plugin_pref_frame_new();

	ppref = purple_plugin_pref_new_with_label("boolean");
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
									"/plugins/core/pluginpref_example/bool",
									"boolean pref");
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_label("integer");
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
									"/plugins/core/pluginpref_example/int",
									"integer pref");
	purple_plugin_pref_set_bounds(ppref, 0, 255);
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
									"/plugins/core/pluginpref_example/int_choice",
									"integer choice");
	purple_plugin_pref_set_type(ppref, PURPLE_PLUGIN_PREF_CHOICE);
	purple_plugin_pref_add_choice(ppref, "One", GINT_TO_POINTER(1));
	purple_plugin_pref_add_choice(ppref, "Two", GINT_TO_POINTER(2));
	purple_plugin_pref_add_choice(ppref, "Four", GINT_TO_POINTER(4));
	purple_plugin_pref_add_choice(ppref, "Eight", GINT_TO_POINTER(8));
	purple_plugin_pref_add_choice(ppref, "Sixteen", GINT_TO_POINTER(16));
	purple_plugin_pref_add_choice(ppref, "Thirty Two", GINT_TO_POINTER(32));
	purple_plugin_pref_add_choice(ppref, "Sixty Four", GINT_TO_POINTER(64));
	purple_plugin_pref_add_choice(ppref, "One Hundred Twenty Eight", GINT_TO_POINTER(128));
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_label("string");
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
								"/plugins/core/pluginpref_example/string",
								"string pref");
	purple_plugin_pref_set_format_type(ppref, PURPLE_STRING_FORMAT_TYPE_MULTILINE);
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
								"/plugins/core/pluginpref_example/masked_string",
								"masked string");
	purple_plugin_pref_set_masked(ppref, TRUE);
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
							"/plugins/core/pluginpref_example/max_string",
							"string pref\n(max length of 16)");
	purple_plugin_pref_set_max_length(ppref, 16);
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
							"/plugins/core/pluginpref_example/string_choice",
							"string choice");
	purple_plugin_pref_set_type(ppref, PURPLE_PLUGIN_PREF_CHOICE);
	purple_plugin_pref_add_choice(ppref, "red", (gpointer)"red");
	purple_plugin_pref_add_choice(ppref, "orange", (gpointer)"orange");
	purple_plugin_pref_add_choice(ppref, "yellow", (gpointer)"yellow");
	purple_plugin_pref_add_choice(ppref, "green", (gpointer)"green");
	purple_plugin_pref_add_choice(ppref, "blue", (gpointer)"blue");
	purple_plugin_pref_add_choice(ppref, "purple", (gpointer)"purple");
	purple_plugin_pref_frame_add(frame, ppref);

	ppref = purple_plugin_pref_new_with_name_and_label(
									"/plugins/core/pluginpref_example/string_list",
									"String list");
	purple_plugin_pref_set_type(ppref, PURPLE_PLUGIN_PREF_CHOICE);
	purple_plugin_pref_frame_add(frame, ppref);

	return frame;
}

PurplePluginUiInfo prefs_info = {
	get_plugin_pref_frame,
	0,
	NULL,

	/* padding */
	NULL,
	NULL,
	NULL,
	NULL
};

void pref_cb(const char *name, PurplePrefType type,	gconstpointer val, gpointer data)
{
	purple_debug_misc("The preference %s, type:%d has been changed to %s.\n", name, type, val);
}

void init_test_plugin(PurplePlugin *plugin)
{
	purple_prefs_add_none("/plugins/core/pluginpref_example");
	purple_prefs_add_bool("/plugins/core/pluginpref_example/bool", TRUE);
	purple_prefs_add_int("/plugins/core/pluginpref_example/int", 0);
	purple_prefs_add_int("/plugins/core/pluginpref_example/int_choice", 1);
	purple_prefs_add_string("/plugins/core/pluginpref_example/string",
							"string");
	purple_prefs_add_string("/plugins/core/pluginpref_example/max_string",
							"max length string");
	purple_prefs_add_string("/plugins/core/pluginpref_example/masked_string", "masked");
	purple_prefs_add_string("/plugins/core/pluginpref_example/string_choice", "red");
	GList* list = g_list_alloc();
	g_list_append(list, (gpointer)"string list 1");
	g_list_append(list, (gpointer)"string list 2");
	g_list_append(list, (gpointer)"string list 3");
	g_list_append(list, (gpointer)"string list 4");
	g_list_append(list, (gpointer)"string list 5");
	purple_prefs_add_string_list("/plugins/core/pluginpref_example/string_list", list);
	purple_prefs_connect_callback(purple_plugins_get_handle(),
			"/plugins/core/pluginpref_example/string_choice",
			pref_cb,
			0);
	g_list_free(list);
}

TestPidginPluginPreference::TestPidginPluginPreference() {
	// TODO Auto-generated constructor stub

}

TestPidginPluginPreference::~TestPidginPluginPreference() {
	// TODO Auto-generated destructor stub
}

} /* namespace QAS */
