#include "xinterface.h"
#include "graphics.h"
#include "sand_water.h"
#include <string.h>

static GtkWidget* window;
static GtkWidget* vbox;
static GtkWidget* drawing_area;
static bool use_water = true;
static bool paused = false;
static int update_time = 100;
static int updater = 0;

//// x_args() ///////////////////////////////////////////////////////////

bool x_args( int* p_argc, char*** p_argv )
{
   return gtk_init_check( p_argc, p_argv );
}

//// x_init() ///////////////////////////////////////////////////////////

void x_init( GlobalParams par, char* window_title )
{
   // allows arbitrary RGB value setting in the drawing area
   gdk_rgb_init();

   // create and name the window
   window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
   gtk_widget_set_name( window, window_title );

   // for closing and killing the window, respectively
   gtk_signal_connect( GTK_OBJECT( window ), "delete_event",
		       GTK_SIGNAL_FUNC( my_delete_event ), NULL );
   gtk_signal_connect( GTK_OBJECT( window ), "destroy",
		       GTK_SIGNAL_FUNC( my_destroy ), NULL );

   // vertical packing box with only one object: the drawing area
   // could maybe add a toolbar, using all the gtk stuff
   vbox = gtk_vbox_new( false, 0 );
   gtk_container_add( GTK_CONTAINER( window ), vbox );
   gtk_widget_show( vbox );

   // the drawing area where everything happens (also, a (technically)
   // undocumented feature of GTK--- fun, huh?)
   drawing_area = gtk_drawing_area_new();
   gtk_drawing_area_size( GTK_DRAWING_AREA( drawing_area ),
			  par.window_width, par.window_height );
   gtk_box_pack_start( GTK_BOX( vbox ), drawing_area, true, true, 0 );
   gtk_widget_show( drawing_area );

   // connect some signals to the drawing area
   gtk_signal_connect( GTK_OBJECT( drawing_area ), "expose_event",
		       (GtkSignalFunc) my_expose_event, NULL );
   gtk_signal_connect( GTK_OBJECT( drawing_area ), "configure_event",
		       (GtkSignalFunc) my_configure_event, NULL );
   gtk_signal_connect( GTK_OBJECT( drawing_area ), "motion_notify_event",
		       (GtkSignalFunc) my_motion_notify_event, NULL );
   gtk_signal_connect( GTK_OBJECT( drawing_area ), "button_press_event",
		       (GtkSignalFunc) my_button_press_event, NULL );
   gtk_signal_connect( GTK_OBJECT( drawing_area ), "key_press_event",
		       GTK_SIGNAL_FUNC( my_key_press_event ), NULL );
   // and set the masks so that we get the events
   gtk_widget_set_events( drawing_area, ( GDK_EXPOSURE_MASK            |
					  GDK_LEAVE_NOTIFY_MASK        |
					  GDK_BUTTON_PRESS_MASK        |
					  GDK_POINTER_MOTION_MASK      |
					  GDK_POINTER_MOTION_HINT_MASK |
					  GDK_KEY_PRESS_MASK             ) );
   // need to set a focus flag for drawing_area to recieve key_press_event
   GTK_WIDGET_SET_FLAGS( drawing_area, GTK_CAN_FOCUS );
   gtk_window_set_focus( GTK_WINDOW( window ), drawing_area );

   // if we're not using water, there's no need to do anything with an
   // updater
   use_water = par.use_water;
   if ( use_water )
   {
      update_time = par.update_time;
      updater = gtk_timeout_add( update_time, (GtkFunction) my_update_idle,
				 gpointer( drawing_area ) );
   }
   
   // (this doesn't work yet, I don't know why... some GTK thing)
   if ( par.position_window )
      gdk_window_move( drawing_area->window, par.window_x, par.window_y );

   // now that everything is set up, we can show the window
   gtk_widget_show( window );
}

//// x_loop() ///////////////////////////////////////////////////////////

void x_loop()
{
   gtk_main();
}

//// x_cleanup() ////////////////////////////////////////////////////////

void x_cleanup()
{
   if ( use_water )
      gtk_timeout_remove( updater );
}

//// my_delete_event() //////////////////////////////////////////////////

static gint my_delete_event( GtkWidget* widget, GdkEvent* event,
			     gpointer data )
{
   return false;
}

//// my_destroy() ///////////////////////////////////////////////////////

static gint my_destroy( GtkWidget* widget, gpointer data )
{
   gtk_main_quit();
}

//// my_expose_event() //////////////////////////////////////////////////

static gint my_expose_event( GtkWidget* widget, GdkEventExpose* event,
			     gpointer data )
{
   x_expose( event->area.x, event->area.y, event->area.width, event->area.height );
   return false;
}

//// my_configure_event() ///////////////////////////////////////////////

static gint my_configure_event( GtkWidget* widget, GdkEventConfigure* event,
				gpointer data )
{
   if ( use_water  &&  ! paused )
      gtk_timeout_remove( updater );

   int old_width = get_width();
   int old_height = get_height();

   if ( widget->allocation.width != old_width   ||
	widget->allocation.height != old_height   )
   {
      graphics_resize( widget->allocation.width, widget->allocation.height );

      sand_water_resize( widget->allocation.width, widget->allocation.height );

      // Looks crappy :(
//
//       if ( get_width() > old_width  &&  get_height() > old_height )
//       {
// 	 graphics_draw( old_width, 0, get_width() - old_width, old_height );
// 	 graphics_draw( 0, old_height, get_width(), get_height() - old_height );
//       }
//       else if ( get_height() > old_height )
// 	 graphics_draw( 0, old_height, get_width(), get_height() - old_height );
//       else if ( get_width() > old_width )
// 	 graphics_draw( old_width, 0, get_width() - old_width, get_height() );

      graphics_draw(0, 0, get_width(), get_height());
   }

   if ( use_water  &&  ! paused )
      updater = gtk_timeout_add( update_time, (GtkFunction) my_update_idle,
				 gpointer( drawing_area ) );
   return true;
}

//// my_motion_notify_event() ///////////////////////////////////////////

static gint my_motion_notify_event( GtkWidget* widget, GdkEventMotion* event,
				    gpointer data )
{
   int x, y;
   GdkModifierType state;

   if ( event->is_hint )
      gdk_window_get_pointer( event->window, &x, &y, &state );
   else
   {
      x = int( event->x );
      y = int( event->y );
      state = GdkModifierType( event->state );
   }

   if ( ( state & GDK_BUTTON1_MASK ) )
      sand_brush( x, y, 1, false );
   else if ( ( state & GDK_BUTTON2_MASK ) )
      sand_brush( x, y, 2, false );
   else if ( ( state & GDK_BUTTON3_MASK ) )
      sand_brush( x, y, 3, false );

   if ( state & ( GDK_BUTTON1_MASK | GDK_BUTTON2_MASK | GDK_BUTTON3_MASK ) )
   {
      int left, top, width, height;
      sand_brush_region( x, y, &left, &top, &width, &height );

      graphics_draw( left, top, width, height  );

      gdk_draw_rgb_image( widget->window,
			  widget->style->fg_gc[ GTK_STATE_NORMAL ],
			  left, top, width, height,
			  GDK_RGB_DITHER_NORMAL,
			  (guchar *) get_buffer( left, top ),
			  get_linesize() );
   }

   return true;
}

//// my_button_press_event() ////////////////////////////////////////////

static gint my_button_press_event( GtkWidget* widget, GdkEventButton* event,
				   gpointer data )
{
   sand_brush( int( event->x ), int( event->y ), event->button, true );

   int left, top, width, height;
   sand_brush_region( int( event->x ), int( event->y ),
		      &left, &top, &width, &height );

   graphics_draw( left, top, width, height  );

   gdk_draw_rgb_image( widget->window,
		       widget->style->fg_gc[ GTK_STATE_NORMAL ],
		       left, top, width, height,
		       GDK_RGB_DITHER_NORMAL,
		       (guchar *) get_buffer( left, top ),
		       get_linesize() );

   return true;
}

//// my_key_press_event() ///////////////////////////////////////////////

static gint my_key_press_event( GtkWidget* widget, GdkEventKey* event,
				gpointer data )
{
   if ( event->length == 1 )
   {
      if ( strcmp( gdk_keyval_name( event->keyval ), "q" ) == 0  ||
	   strcmp( gdk_keyval_name( event->keyval ), "Q" ) == 0      )
	 gtk_main_quit();

      else if ( strcmp( gdk_keyval_name( event->keyval ), "p" ) == 0  ||
		strcmp( gdk_keyval_name( event->keyval ), "P" ) == 0      )
      {
	 paused = ( ! paused );

	 if ( use_water )
	 {
	    if ( paused )
	       gtk_timeout_remove( updater );
	    else
	       updater = gtk_timeout_add( update_time, (GtkFunction) my_update_idle,
					  gpointer( drawing_area ) );
	 }
      }

      else if ( strcmp( gdk_keyval_name( event->keyval ), "r" ) == 0  ||
		strcmp( gdk_keyval_name( event->keyval ), "R" ) == 0      )
      {
	 paused = false;

	 if ( use_water )
	 {
	    if ( paused )
	       gtk_timeout_remove( updater );
	    else
	       updater = gtk_timeout_add( update_time, (GtkFunction) my_update_idle,
					  gpointer( drawing_area ) );
	 }
      }

      else if ( strcmp( gdk_keyval_name( event->keyval ), "greater" ) == 0 )
      {
	 change_light_angle( 10. * 3.14 / 180. );
	 graphics_draw( 0, 0, get_width(), get_height() );
	 gdk_draw_rgb_image( widget->window,
			     widget->style->fg_gc[ GTK_STATE_NORMAL ],
			     0, 0, get_width(), get_height(),
			     GDK_RGB_DITHER_NORMAL, (guchar *) get_buffer( 0, 0 ),
			     get_linesize() );
      }

      else if ( strcmp( gdk_keyval_name( event->keyval ), "less" ) == 0 )
      {
	 change_light_angle( -10. * 3.14 / 180. );
	 graphics_draw( 0, 0, get_width(), get_height() );
	 gdk_draw_rgb_image( widget->window,
			     widget->style->fg_gc[ GTK_STATE_NORMAL ],
			     0, 0, get_width(), get_height(),
			     GDK_RGB_DITHER_NORMAL, (guchar *) get_buffer( 0, 0 ),
			     get_linesize() );
      }

      else if ( strcmp( gdk_keyval_name( event->keyval ), "space" ) == 0 )
      {
	 toggle_contours();
	 graphics_draw( 0, 0, get_width(), get_height() );
	 gdk_draw_rgb_image( widget->window,
			     widget->style->fg_gc[ GTK_STATE_NORMAL ],
			     0, 0, get_width(), get_height(),
			     GDK_RGB_DITHER_NORMAL, (guchar *) get_buffer( 0, 0 ),
			     get_linesize() );
      }
   }

   // I don't know what the return value should be... it doesn't seem to matter
}

//// my_update_idle() ///////////////////////////////////////////////////

static gint my_update_idle( gpointer data )
{
   sand_water_update();
   return true;
}

//// x_expose() /////////////////////////////////////////////////////////

void x_expose( int x, int y, int box_width, int box_height )
{
   // protect against water being updated during resize
   if ( box_width > 0  ||  box_height > 0 )
      gdk_draw_rgb_image( drawing_area->window,
			  drawing_area->style->fg_gc[ GTK_STATE_NORMAL ],
			  x, y, box_width, box_height,
			  GDK_RGB_DITHER_NORMAL,
			  (guchar *)( get_buffer( x, y ) ),
			  get_linesize() );
}
