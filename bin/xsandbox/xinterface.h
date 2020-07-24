#ifndef XINTERFACE_H
#define XINTERFACE_H

#include <gtk/gtk.h>
#include "xsandbox.h"

bool x_args( int* p_argc, char*** p_argv );
void x_init( GlobalParams par, char* window_title );
void x_loop();
void x_cleanup();

static gint my_delete_event( GtkWidget* widget, GdkEvent* event, gpointer data );
static gint my_destroy( GtkWidget* widget, gpointer data );
static gint my_expose_event( GtkWidget* widget, GdkEventExpose* event,
			     gpointer data );
static gint my_configure_event( GtkWidget* widget, GdkEventConfigure* event,
				gpointer data );
static gint my_motion_notify_event( GtkWidget* widget, GdkEventMotion* event,
				    gpointer data );
static gint my_button_press_event( GtkWidget* widget, GdkEventButton* event,
				   gpointer data );
static gint my_key_press_event( GtkWidget* widget, GdkEventKey* event,
				gpointer data );
static gint my_update_idle( gpointer data );

void x_expose( int x, int y, int box_width, int box_height );

#endif // ! X_INTERFACE_H
