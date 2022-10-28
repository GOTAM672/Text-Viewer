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
void
open_file_complete (GObject      *source_object,
                    GAsyncResult *res,
                    gpointer     user_data)
{
  g_autofree char *contents = NULL;
  gsize length = 0;
  g_autoptr (GError) error = NULL;

  gboolean res = g_file_load_contents_finish (G_FILE(source_object),
                                              res,
                                              &contents,
                                              &length,
                                              NULL,
                                              &error);

  if (error != NULL)
    {
      g_printerr ("Unable to open the file : %s\n", error->message);
      return;
    }
}


static void
open_file (TextViewerWindow   *self,
           GFile              *file)
{
  g_file_load_contents_async (file, NULL, open_file_complete, self);

}

static void
on_response (GtkNativeDialog *native,
             int              response,
             TextViewerWindow *self)
{
  if (response == GTK_RESPONSE_ACCEPT)
    {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
      g_autoptr (GFile) file = gtk_file_chooser_get_file (chooser);

      open_file (self, file);

      g_print ("Selected file : %s",g_file_peek_path (file));

    }

  g_object_unref (native);
}



static void
text_viewer_window__open_clicked (GtkButton *button G_GNUC_UNUSED,
                                 gpointer   user_data)
{

  TextViewerWindow *self = user_data;


  GtkFileChooserNative *native;
  //GtkFileChooser *chooser;
  //GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

  native = gtk_file_chooser_native_new ("Open File",
                                        GTK_WINDOW (self),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        "_Open",
                                        "_Cancel");

  g_signal_connect (native, "response", G_CALLBACK (on_response), self);
  gtk_native_dialog_show (GTK_NATIVE_DIALOG (native));


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
