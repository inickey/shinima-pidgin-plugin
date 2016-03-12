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
#include <glib/gprintf.h>
#include <debug.h>

#include "shinima-globals.h"
#include "shinima-message.h"
#include "shinima-link.h"

static void
shinima_message_link_to_img(xmlnode *a,
							const gchar *href,
							gchar **message,
							gboolean *changed,
							gpointer user_data)
{
	ShinimaLink *link = NULL;

	purple_debug_info(PLUGIN_ID, "Found link %s\n", href);

	link = shinima_link_get(href);
	if(link && link->load_success)
	{
		// Here's useless check for I want to replace
		// non-image links with html title tag contents on the
		// future...
		if(link->is_image && link->data != NULL)
		{
			gint id = -1;
			id = shinima_link_store_image(link);
			if(id > 0)
			{
				gchar *idstr = g_strdup_printf("%d", id);
				xmlnode *img = xmlnode_new("img");

				img->next = a->next;
				img->parent = a->parent;
				a->next = img;

				xmlnode_set_attrib(img, "id", idstr);
				g_free(idstr);
				*changed = TRUE;
			}
		}
		shinima_link_debug_describe(link);
	}

	shinima_link_free(link);

	return;
}

static void
shinima_message_links_foreach(gchar **message,
							  void(*foreach_func)(xmlnode*,
												  const gchar*,
												  gchar**,
												  gboolean*,
												  gpointer),
							  gboolean *_changed,
							  gpointer *user_data)
{
	xmlnode *root, *a;
	gboolean *changed =
		(_changed != NULL) ? changed : g_malloc(sizeof(gboolean));

	g_return_if_fail(foreach_func != NULL);

	root = xmlnode_from_str(*message, -1);

	for(a=xmlnode_get_child(root, "a"); a; a=xmlnode_get_next_twin(a))
	{
		const gchar *href = xmlnode_get_attrib(a, "href");
		if(href) foreach_func(a, href, message, changed, user_data);
	}

	if(changed)
	{
		g_free(*message);
		*message = xmlnode_to_str(root, NULL);
	}

	if(_changed == NULL) g_free(changed);

	xmlnode_free(root);
}

void
shinima_message_proceed(gchar **message)
{
	shinima_message_links_foreach(message,
								  shinima_message_link_to_img,
								  NULL, NULL);
	return;
}
