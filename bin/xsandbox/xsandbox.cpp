#include "xsandbox.h"
#include "xinterface.h"
#include "graphics.h"
#include "sand_water.h"
#include <string.h>

//// main() /////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
   // Set default values
   GlobalParams par;

   par.position_window = false;
   par.window_x = 0;
   par.window_y = 0;
   par.window_width = 400;
   par.window_height = 300;

   par.use_water = true;
   par.water_pixelation = 4;
   par.water_coupling = 0.45;
   par.water_dissipation = 0.05;

   par.update_time = 100;

   par.use_hill = true;
   par.use_bumps = true;

   par.ocean_amplitude = 1.;
   par.ocean_period = 30.;

   // parse commandline arguments
   if ( ! x_args( &argc, &argv )  ||  ! my_args( argc, argv, &par ) )
   {
      usage_string();
      return -1;
   }

   srand( 234251345 );  // I actually don't care

   graphics_init( par );
   sand_water_init( par );
   x_init( par, "xsandbox" );
   graphics_draw( 0, 0, get_width(), get_height() );

   x_loop();

   sand_water_cleanup();
   graphics_cleanup();
   x_cleanup();

   return 0;
}

//// usage_string() /////////////////////////////////////////////////////

void usage_string()
{
   fprintf( stderr, "usage: xsandbox [-geom|--geometry +x+y|wXh[+x+y]]  # window placement (400x300)\n");
   fprintf( stderr, "                [-nw|--no-water]                   # just sand\n");
   fprintf( stderr, "                [-wp|--water-pixelation int]       # size of water pixels (3)\n");
   fprintf( stderr, "                [-wc|--water-coupling float]       # wave coupling const (0.45)\n");
   fprintf( stderr, "                [-wd|--water-dissipation float]    # energy loss (0.05)\n");
   fprintf( stderr, "                [-u|--update-time int]             # milliseconds between redraws (100)\n");
   fprintf( stderr, "                [-nh|--no-hill]                    # start with level ground\n");
   fprintf( stderr, "                [-nb|--no-bumps]                   # start with no anisotropies\n");
   fprintf( stderr, "                [-amp|--ocean-amplitude float]     # strength of ocean waves (1.0)\n");
   fprintf( stderr, "                [-per|--ocean-period float]        # seconds between crests (30.0)\n");
   fprintf( stderr, "       # standard gtk options:\n");
   fprintf( stderr, "                [--gtk-module] [--g-fatal-warnings] [--gtk-debug]\n");
   fprintf( stderr, "                [--gtk-no-debug] [--gdk-debug] [--gdk-no-debug]\n");
   fprintf( stderr, "                [--display] [--sync] [--no-xshm] [--name] [--class]\n");
}

//// my_args() //////////////////////////////////////////////////////////

bool my_args( int argc, char** argv, GlobalParams* p_par )
{
   // no arguments is fine
   if ( argc == 1 )
      return true;

   for( int i = 1;  i < argc;  i++ )
      if ( strcmp( argv[ i ], "-geom" ) == 0       ||
	   strcmp( argv[ i ], "--geometry" ) == 0      )
      {
	 if ( ++i == argc  ||  ! arg_geometry( argv[ i ], p_par ) )
	    return false;
      }
      else if ( strcmp( argv[ i ], "-nw" ) == 0          ||
		strcmp( argv[ i ], "--no-water" ) == 0       )
      {
	 p_par->use_water = false;
      }
      else if ( strcmp( argv[ i ], "-wp" ) == 0                 ||
		strcmp( argv[ i ], "--water-pixelation" ) == 0       )
      {
	 int water_pixelation;
	 if ( ++i == argc  ||  ! arg_int( argv[ i ], &water_pixelation ) )
	    return false;
	 p_par->water_pixelation = water_pixelation;
      }
      else if ( strcmp( argv[ i ], "-wc" ) == 0                ||
		strcmp( argv[ i ], "--water-coupling" ) == 0       )
      {
	 float water_coupling;
	 if ( ++i == argc  ||  ! arg_float( argv[ i ], &water_coupling ) )
	    return false;
	 p_par->water_coupling = water_coupling;
      }
      else if ( strcmp( argv[ i ], "-wd" ) == 0                  ||
		strcmp( argv[ i ], "--water-dissipation" ) == 0       )
      {
	 float water_dissipation;
	 if ( ++i == argc  ||  ! arg_float( argv[ i ], &water_dissipation ) )
	    return false;
	 p_par->water_dissipation = water_dissipation;
      }
      else if ( strcmp( argv[ i ], "-u" ) == 0              ||
		strcmp( argv[ i ], "--update-time" ) == 0       )
      {
	 int update_time;
	 if ( ++i == argc  ||  ! arg_int( argv[ i ], &update_time ) )
	    return false;
	 p_par->update_time = update_time;
      }
      else if ( strcmp( argv[ i ], "-nh" ) == 0        ||
		strcmp( argv[ i ], "--no-hill" ) == 0       )
      {
	 p_par->use_hill = false;
      }
      else if ( strcmp( argv[ i ], "-nb" ) == 0         ||
		strcmp( argv[ i ], "--no-bumps" ) == 0       )
      {
	 p_par->use_bumps = false;
      }
      else if ( strcmp( argv[ i ], "-amp" ) == 0                ||
		strcmp( argv[ i ], "--ocean-amplitude" ) == 0       )
      {
	 float ocean_amplitude;
	 if ( ++i == argc  ||  ! arg_float( argv[ i ], &ocean_amplitude ) )
	    return false;
	 p_par->ocean_amplitude = ocean_amplitude;
      }
      else if ( strcmp( argv[ i ], "-per" ) == 0             ||
		strcmp( argv[ i ], "--ocean-period" ) == 0       )
      {
	 float ocean_period;
	 if ( ++i == argc  ||  ! arg_float( argv[ i ], &ocean_period ) )
	    return false;
	 p_par->ocean_period = ocean_period;
      }
      else
	 return false;
}

//// read_int() /////////////////////////////////////////////////////////
//// abstracted out for arg_geometry to use as well

char* read_int( char* str, int* val )
{
   *val = 0;
   while ( *str >= '0'  &&  *str <= '9' )
   {
      *val *= 10;
      *val += ( *str - '0' );
      str++;
   }
   return str;
}

//// arg_int() //////////////////////////////////////////////////////////

bool arg_int( char* arg, int* val )
{
   arg = read_int( arg, val );
   return ( *arg == 0 );
}

//// arg_float() ////////////////////////////////////////////////////////

bool arg_float( char* arg, float* val )
{
   *val = 0.;
   bool seendot = false;
   float place = 0.1;
   while( ( *arg >= '0'  &&  *arg <= '9' )  ||  *arg == '.' )
   {
      if ( *arg == '.' )
	 seendot = true;
      else
      {
	 if ( ! seendot )
	 {
	    *val *= 10.;
	    *val += ( *arg - '0' );
	 }
	 else
	 {
	    *val += place * ( *arg - '0' );
	    place /= 10.;
	 }
      }
      arg++;
   }
   return ( *arg == 0 );
}

//// arg_geometry() /////////////////////////////////////////////////////

bool arg_geometry( char* arg, GlobalParams* p_par )
{
   int w, h, x, y;
   bool scale = false;
   bool offset = false;

   if ( *arg == '+'  ||  *arg == '-' )
   {
      offset = true;
      int xsign = ( *arg == '+' ? 1 : -1 );

      arg = read_int( ++arg, &x );
      x *= xsign;

      if ( *arg == '+'  ||  *arg == '-' )
      {
	 int ysign = ( *arg == '+' ? 1 : -1 );
	 
	 arg = read_int( ++arg, &y );
	 y *= ysign;

	 if ( *arg != 0 )  // should be done now
	    return false;
      }
      else  // had an x coordinate but not a y coordinate
	 return false;
   }

   else  // arg didn't start with a plus or minus
   {
      scale = true;
      arg = read_int( arg, &w );

      if ( *arg == 'x'  ||  *arg == 'X' )
      {
	 arg = read_int( ++arg, &h );

	 // the following is a copy of the "starts with '+' or '-' case"
	 if ( *arg == '+'  ||  *arg == '-' )
	 {
	    offset = true;
	    int xsign = ( *arg == '+' ? 1 : -1 );
	    
	    arg = read_int( ++arg, &x );
	    x *= xsign;
	    
	    if ( *arg == '+'  ||  *arg == '-' )
	    {
	       int ysign = ( *arg == '+' ? 1 : -1 );
	       
	       arg = read_int( ++arg, &y );
	       y *= ysign;
	       
	       if ( *arg != 0 )  // should be done now
		  return false;
	    }
	    else  // had an x coordinate but not a y coordinate
	       return false;
	 }
      }
      else  // had a width but not a height
	 return false;
   }

   // good geom string, fully parsed!
   p_par->position_window = offset;
   if ( offset )
   {
      p_par->window_x = x;
      p_par->window_y = y;
   }
   if ( scale )
   {
      p_par->window_width = w;
      p_par->window_height = h;
   }
   return true;
}
