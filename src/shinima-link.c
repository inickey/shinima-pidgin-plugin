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

#include <glib.h>
#include <libsoup/soup.h>
#include <conversation.h>
#include <debug.h>
#include "shinima-globals.h"
#include "shinima-link.h"

static ShinimaLink*
shinima_link_new(void)
{
	ShinimaLink *link = g_malloc(sizeof(ShinimaLink));

	purple_debug_info(PLUGIN_ID, "shinima_link_new()\n");

	g_return_val_if_fail((link != NULL), NULL);

	link->url = NULL;
	link->response_code = -1;
	link->load_success = FALSE;
	link->content_type = NULL;
	link->is_image = FALSE;
	link->data = NULL;
	link->size = 0;

	return link;
}

ShinimaLink*
shinima_link_get(const gchar *url)
{
	ShinimaLink *link = shinima_link_new();
	SoupSession *session = NULL;
	SoupMessage *msg = NULL;

	purple_debug_info(PLUGIN_ID, "shinima_link_get()\n");

	g_return_val_if_fail((link != NULL), NULL);

	link->url = url;
	session = soup_session_sync_new();
	msg = soup_message_new("GET", url);
	
	if(session != NULL && msg != NULL)
	{
		purple_debug_info(PLUGIN_ID, "Sending SOUP message\n");
		soup_session_send_message(session, msg);
		purple_debug_info(PLUGIN_ID,
						  "Message sent, filling link structure\n");
		link->response_code = msg->status_code;
		link->load_success = link->response_code == 200;
		link->content_type = 
			g_strdup(soup_message_headers_get_content_type(
						 msg->response_headers, NULL));
		link->is_image = g_str_has_prefix(link->content_type, "image/");
		link->data = g_memdup(msg->response_body->data,
							  msg->response_body->length);
		link->size = msg->response_body->length;
		purple_debug_info(PLUGIN_ID, "Done filling\n");
	}

	g_object_unref(msg);
	g_object_unref(session);

	purple_debug_info(PLUGIN_ID, "Returning from shinima_link_get\n");

	return link;
}

void
shinima_link_debug_describe(ShinimaLink *link)
{
	g_return_if_fail(link != NULL);
	purple_debug_info(PLUGIN_ID, "=== LINK INFO ===\n");
	purple_debug_info(PLUGIN_ID, "URL: %s\n", link->url);
	purple_debug_info(PLUGIN_ID, "Response code: %d\n",
					  link->response_code);
	purple_debug_info(PLUGIN_ID, "Load success: %s\n",
					  (link->load_success) ? "TRUE" : "FALSE");
	purple_debug_info(PLUGIN_ID, "Content type: %s\n",
					  link->content_type);
	purple_debug_info(PLUGIN_ID, "Is image: %s\n",
					  (link->is_image) ? "TRUE" : "FALSE");
	purple_debug_info(PLUGIN_ID, "Data: %s\n",
					  (link->data != NULL) ? "Exist" : "Empty");
	purple_debug_info(PLUGIN_ID, "Size: %d\n", link->size);
	purple_debug_info(PLUGIN_ID, "=================\n");
	return;
}

gint
shinima_link_store_image(ShinimaLink *link)
{
	gint id = -1;
	gpointer data = NULL;

	purple_debug_info(PLUGIN_ID, "shinima_link_store_image()\n");
	g_return_val_if_fail((link != NULL &&
						  link->is_image &&
						  link->size > 0), -1);

	data = g_memdup(link->data, link->size);
	id = purple_imgstore_add_with_id(data, link->size, NULL);
	if(id <= 0) g_free(data);

	purple_debug_info(PLUGIN_ID,
					  "Image added to store with id=%d\n", id);
	return id;
}

void
shinima_link_free(ShinimaLink *link)
{
	purple_debug_info(PLUGIN_ID, "shinima_link_free()\n");
	g_return_if_fail(link != NULL);
	g_free(link->content_type);
	g_free(link->data);
	g_free(link);
}
