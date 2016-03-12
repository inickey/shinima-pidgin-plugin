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

#ifndef SHINIMA_LINK_H
#define SHINIMA_LINK_H

typedef struct _ShinimaLink ShinimaLink;

struct _ShinimaLink
{
	const gchar *url;
	gint response_code;
	gboolean load_success;
	gchar *content_type;
	gboolean is_image;
	gpointer data;
	guint size;
};

ShinimaLink *shinima_link_get(const gchar*);
void shinima_link_debug_describe(ShinimaLink*);
gint shinima_link_store_image(ShinimaLink*);
void shinima_link_free(ShinimaLink*);

#endif /* SHINIMA_LINK_H */
