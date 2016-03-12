/* Shinima - Pidgin plugin for showing inline images
 * Copyright (C) 2016 Nickey <i@nickey.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define PURPLE_PLUGINS

#include <glib.h>
#include <notify.h>
#include <plugin.h>
#include <version.h>
#include <debug.h>

#include "shinima-globals.h"
#include "shinima-callbacks.h"

PurplePlugin *shinima_pidgin_plugin = NULL;

static gboolean
plugin_load(PurplePlugin *plugin)
{
	void *conv_handle = purple_conversations_get_handle();
	shinima_pidgin_plugin = plugin;

	purple_debug_info(PLUGIN_ID, "Loading Plugin\n");

	purple_signal_connect(conv_handle, "receiving-im-msg", plugin,
						  PURPLE_CALLBACK(shinima_receiving_im_msg),
						  NULL);

	return TRUE;
}

static void
init_plugin(PurplePlugin *plugin)
{
	return;
}

static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,
	NULL,
	0,
	NULL,
	PURPLE_PRIORITY_DEFAULT,
	PLUGIN_ID,
	PLUGIN_NAME,
	PLUGIN_VERSION,
	PLUGIN_SUMMARY,
	PLUGIN_DESCRIPTION,
	PLUGIN_AUTHOR,
	PLUGIN_HOMEPAGE,
	plugin_load,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

PURPLE_INIT_PLUGIN(shinima_pidgin_plugin, init_plugin, info);
