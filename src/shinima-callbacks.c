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

#include <debug.h>
#include <util.h>

#include "shinima-globals.h"
#include "shinima-callbacks.h"
#include "shinima-message.h"

gboolean
shinima_receiving_im_msg(PurpleAccount *account,
						 const char **sender,
						 gchar **message,
						 PurpleConversation *conv,
						 PurpleMessageFlags flags,
						 gpointer data)
{
	purple_debug_info(PLUGIN_ID, "Received IM Message from %s\n",
					  (gchar*)*sender);

	shinima_message_proceed(message);

	return FALSE;
}
