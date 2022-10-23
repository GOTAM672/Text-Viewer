/* text-viewer-window.c
 *
 * Copyright 2022 gotam gorabh
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
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "text-viewer-window.h"

struct _TextViewerWindow
{
  AdwApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkTextView         *main_text_view;
  GtkButton           *open_button;
};

G_DEFINE_FINAL_TYPE (TextViewerWindow, text_viewer_window, ADW_TYPE_APPLICATION_WINDOW)


static void
text_viewer_window__open_clicked (GtkButton *button,
                                 gpointer   user_data)
{

  TextViewerWindow *self = user_data;
  g_print ("open button clicked!");

}

static void
text_viewer_window_class_init (TextViewerWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/com/example/TextViewer/text-viewer-window.ui");
  gtk_widget_class_bind_template_child (widget_class, TextViewerWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, TextViewerWindow, main_text_view);
  gtk_widget_class_bind_template_child (widget_class, TextViewerWindow, open_button);
}

static void
text_viewer_window_init (TextViewerWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_signal_connect (self->open_button, "clicked", G_CALLBACK (text_viewer_window__open_clicked), self);
}
