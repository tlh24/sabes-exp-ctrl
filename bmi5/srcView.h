#ifndef __SRCVIEW_H__
#define __SRCVIEW_H__

extern gboolean open_file (GtkSourceBuffer *buffer, const gchar *filename);
extern GtkWidget* create_main_window (GtkWidget *top, GtkSourceBuffer *buffer);
#endif
