#include "sand_water.h"
#include "xinterface.h"
#include "graphics.h"

int sand_width = 400;
int sand_height = 300;

int water_width = 134;
int water_height = 100;

int water_pixelation = 3;
float water_coupling = 0.45;
float water_dissipation = 0.05;

int update_time = 100;

bool use_hill = true;
bool use_bumps = true;

float ocean_amplitude = 1.0;
float ocean_period = 20.0;

float* sand = NULL;
float* water = NULL;
float* h_current = NULL;
float* v_current = NULL;

// these two are different in that they are only used in sand_water_update()
float* blocksand = NULL;
float* watercopy = NULL;

//// sand_water_init() //////////////////////////////////////////////////

void sand_water_init( GlobalParams par )
{
   sand_width = ( par.window_width + 1 );
   sand_height = ( par.window_height + 1 );

   water_pixelation = par.water_pixelation;

   water_width = int( ceil( float( sand_width ) / float( water_pixelation ) ) );
   water_height = int( ceil( float( sand_height ) / float( water_pixelation ) ) );

   water_coupling = par.water_coupling;
   water_dissipation = par.water_dissipation;

   update_time = par.update_time;

   use_hill = par.use_hill;
   use_bumps = par.use_bumps;

   ocean_amplitude = par.ocean_amplitude;
   ocean_period = par.ocean_period;

   sand = (float*) malloc( sizeof( float ) * sand_width * sand_height );
   water = (float*) malloc( sizeof( float ) * water_width * water_height );
   h_current = (float*) malloc( sizeof( float ) * water_width * water_height );
   v_current = (float*) malloc( sizeof( float ) * water_width * water_height );

   blocksand = (float *) malloc( sizeof( float ) * water_width * water_height );
   watercopy = (float *) malloc( sizeof( float ) * water_width * water_height );

   ASSERT( sand );
   ASSERT( water );
   ASSERT( h_current );
   ASSERT( v_current );

   ASSERT( blocksand );
   ASSERT( watercopy );

   const float min_depth = -200.;
   const float max_depth = 200.;
   if ( use_hill )
      for ( int y = 0;  y < sand_height;  y++ )
	 for ( int x = 0;  x < sand_width;  x++ )
	    sand[ SANDINDEX( x, y ) ] =
	       max_depth - ( ( max_depth - min_depth ) /
			     ( sand_height + 1 ) * y );
   else
      for ( int y = 0;  y < sand_height;  y++ )
	 for ( int x = 0;  x < sand_width;  x++ )
	    sand[ SANDINDEX( x, y ) ] = 0.;

   update_blocksand( 0, 0, water_width, water_height );

   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
      {
	 water[ WATERINDEX( x, y ) ] = 0.;
	 h_current[ WATERINDEX( x, y ) ] = 0.;
	 v_current[ WATERINDEX( x, y ) ] = 0.;
      }

   if ( use_bumps )
      random_sand_brush( sand_width, sand_height, 0, 0 );
}

//// sand_water_resize() ////////////////////////////////////////////////

void sand_water_resize( int new_width, int new_height )
{
   int new_sand_width = ( new_width + 1 );
   int new_sand_height = ( new_height + 1 );

   int new_water_width = int( ceil( float( new_sand_width ) / float( water_pixelation ) ) );
   int new_water_height = int( ceil( float( new_sand_height ) / float( water_pixelation ) ) );

   float* new_sand = (float*) malloc( sizeof( float ) * new_sand_width * new_sand_height );
   float* new_water = (float*) malloc( sizeof( float ) * new_water_width * new_water_height );
   float* new_h_current = (float*) malloc( sizeof( float ) * new_water_width * new_water_height );
   float* new_v_current = (float*) malloc( sizeof( float ) * new_water_width * new_water_height );

   ASSERT( new_sand );
   ASSERT( new_water );
   ASSERT( new_h_current );
   ASSERT( new_v_current );

   const float min_depth = -200.;
   const float max_depth = 200.;
   // Looks crappy  :(
//
//    if ( use_hill )
//       for ( int y = 0;  y < new_sand_height;  y++ )
// 	 for ( int x = 0;  x < new_sand_width;  x++ )
// 	    if ( x < sand_width  &&  y < sand_height )
// 	       new_sand[ NEWSANDINDEX( x, y ) ] = sand[ SANDINDEX( x, y ) ];
// 	    else
// 	       new_sand[ NEWSANDINDEX( x, y ) ] =
// 		  max_depth - ( ( max_depth - min_depth ) /
// 				( new_sand_height + 1 ) * y );
//    else
//       for ( int y = 0;  y < new_sand_height;  y++ )
// 	 for ( int x = 0;  x < new_sand_width;  x++ )
// 	    if ( x < sand_width  &&  y < sand_height )
// 	       new_sand[ NEWSANDINDEX( x, y ) ] = sand[ SANDINDEX( x, y ) ];
// 	    else
// 	       new_sand[ NEWSANDINDEX( x, y ) ] = 0.;

//    for( int y = 0;  y < new_water_height;  y++ )
//       for( int x = 0;  x < new_water_width;  x++ )
//       {
// 	 if ( x < water_width  &&  y < water_height )
// 	 {
// 	    new_water[ NEWWATERINDEX( x, y ) ] = water[ WATERINDEX( x, y ) ];
// 	    new_h_current[ NEWWATERINDEX( x, y ) ] = h_current[ WATERINDEX( x, y ) ];
// 	    new_v_current[ NEWWATERINDEX( x, y ) ] = v_current[ WATERINDEX( x, y ) ];
// 	 }
// 	 else
// 	 {
// 	    new_water[ NEWWATERINDEX( x, y ) ] = 0.;
// 	    new_h_current[ NEWWATERINDEX( x, y ) ] = 0.;
// 	    new_v_current[ NEWWATERINDEX( x, y ) ] = 0.;
// 	 }
//       }
   if ( use_hill )
      for ( int y = 0;  y < new_sand_height;  y++ )
	 for ( int x = 0;  x < new_sand_width;  x++ )
	    new_sand[ NEWSANDINDEX( x, y ) ] =
	       max_depth - ( ( max_depth - min_depth ) /
			     ( sand_height + 1 ) * y );
   else
      for ( int y = 0;  y < new_sand_height;  y++ )
	 for ( int x = 0;  x < new_sand_width;  x++ )
	    new_sand[ NEWSANDINDEX( x, y ) ] = 0.;

   for ( int y = 0;  y < new_water_height;  y++ )
      for ( int x = 0;  x < new_water_width;  x++ )
      {
	 new_water[ NEWWATERINDEX( x, y ) ] = 0.;
	 new_h_current[ NEWWATERINDEX( x, y ) ] = 0.;
	 new_v_current[ NEWWATERINDEX( x, y ) ] = 0.;
      }

   free( sand );
   free( water );
   free( h_current );
   free( v_current );

   free( blocksand );
   free( watercopy );
   blocksand = (float *) malloc( sizeof( float ) * new_water_width * new_water_height );
   watercopy = (float *) malloc( sizeof( float ) * new_water_width * new_water_height );

   sand = new_sand;
   water = new_water;
   h_current = new_h_current;
   v_current = new_v_current;

   sand_width = new_sand_width;
   sand_height = new_sand_height;
   water_width = new_water_width;
   water_height = new_water_height;

   update_blocksand( 0, 0, water_width, water_height );

   if ( use_bumps )
      random_sand_brush( new_sand_width, new_sand_height, 0, 0 );
}

//// sand_water_cleanup() ///////////////////////////////////////////////

void sand_water_cleanup()
{
   free( sand );
   free( water );
   free( h_current );
   free( v_current );
   
   free( blocksand );
   free( watercopy );
}

//// sand_water_update() ////////////////////////////////////////////////

// The waves are generated by the wave equation (Laplace's) on the
// upper surface of the water (water + blocksand). This is implemented
// as a first-order equation on two fields: a scalar water height and
// a vector water current, which may be physically thought of as
// satisfying two requirements: (1&2) continuity between the water and
// the current and (4) coupling of water neighbors through the current

// The boundary conditions are periodic (topologically toroid) for
// simplicity, and the water level of the bottom line of the window is
// a driven oscillator (3)

void sand_water_update()
{
   ASSERT( watercopy );
   ASSERT( blocksand );

   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
	 watercopy[ WATERINDEX( x, y ) ] = water[ WATERINDEX( x, y ) ];

   // 1. continuity requirement for horizontal component of current
   // note that energy is lost when the current wants to draw more
   // water than exists
   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
      {
	 if ( x == 0 )
	 {
	    if( water[ WATERINDEX( water_width - 1 , y ) ] < h_current[ WATERINDEX( x, y ) ] )
	    {
	       water[ WATERINDEX( x, y ) ] += water[ WATERINDEX( water_width - 1, y ) ];
	       water[ WATERINDEX( water_width - 1, y ) ] = 0.;
	       h_current[ WATERINDEX( x, y ) ] = 0.;
	    }
	    else if( water[ WATERINDEX( x, y ) ] + h_current[ WATERINDEX( x, y ) ] < 0. )
	    {
	       water[ WATERINDEX( water_width - 1, y ) ] -= water[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] = 0.;
	       h_current[ WATERINDEX( x, y ) ] = 0.;
	    }
	    else
	    {
	       water[ WATERINDEX( water_width - 1, y ) ] -= h_current[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] += h_current[ WATERINDEX( x, y ) ];
	    }
	 }
	 else
	 {
	    if( water[ WATERINDEX( x - 1, y ) ] < h_current[ WATERINDEX( x, y ) ] )
	    {
	       water[ WATERINDEX( x, y ) ] += water[ WATERINDEX( x - 1, y ) ] ;
	       water[ WATERINDEX( x - 1, y ) ] = 0.;
	       h_current[ WATERINDEX( x, y ) ] = 0.;
	    }
	    else if( water[ WATERINDEX( x, y ) ] + h_current[ WATERINDEX( x, y ) ] < 0. )
	    {
	       water[ WATERINDEX( x - 1, y ) ] -= water[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] = 0.;
	       h_current[ WATERINDEX( x, y ) ] = 0.;	
	    }
	    else
	    {
	       water[ WATERINDEX( x - 1, y ) ] -= h_current[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] += h_current[ WATERINDEX( x, y ) ];
	    }
	 }
      }

   // 2. continuity requirement for vertical component of current
   // note that energy is lost when the current wants to draw more
   // water than exists
   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
      {
	 if ( y == 0 )
	 {
	    if( water[ WATERINDEX( x, water_height - 1 ) ] < v_current[ WATERINDEX( x, y ) ] )
	    {
	       water[ WATERINDEX( x, y ) ] += 0.5 * water[ WATERINDEX( x, water_height - 1 ) ];
	       water[ WATERINDEX( x, water_height - 1 ) ] *= 0.5;
	       v_current[ WATERINDEX( x, y ) ] *= 0.25;
	    }
	    else if( water[ WATERINDEX( x, y ) ] + v_current[ WATERINDEX( x, y ) ] < 0. )
	    {
	       water[ WATERINDEX( x, water_height - 1 ) ] -= 0.5 * water[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] *= 0.5;
	       v_current[ WATERINDEX( x, y ) ] *= 0.25;
	    }
	    else
	    {
	       water[ WATERINDEX( x, water_height - 1 ) ] -= v_current[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] += v_current[ WATERINDEX( x, y ) ];
	    }
	 }
	 else
	 {
	    if( water[ WATERINDEX( x, y - 1 ) ] < v_current[ WATERINDEX( x, y ) ] )
	    {
	       water[ WATERINDEX( x, y ) ] += 0.5 * water[ WATERINDEX( x, y - 1 ) ] ;
	       water[ WATERINDEX( x, y - 1 ) ] *= 0.5;
	       v_current[ WATERINDEX( x, y ) ] *= 0.25;
	    }
	    else if( water[ WATERINDEX( x, y ) ] + v_current[ WATERINDEX( x, y ) ] < 0. )
	    {
	       water[ WATERINDEX( x, y - 1 ) ] -= 0.5 * water[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] *= 0.5;
	       v_current[ WATERINDEX( x, y ) ] *= 0.25;
	    }
	    else
	    {
	       water[ WATERINDEX( x, y - 1 ) ] -= v_current[ WATERINDEX( x, y ) ];
	       water[ WATERINDEX( x, y ) ] += v_current[ WATERINDEX( x, y ) ];
	    }
	 }
      }

   // 3. Driving current at the bottom of the screen
   static int time_step;
   time_step++;

   float ocean_height_mean = 0. * ocean_amplitude;
   float ocean_height_amp = 130. * ocean_amplitude;
   float ocean_height = ocean_height_mean +
      ( ocean_height_amp * cos( 2 * 3.1415926 *
				time_step * update_time / 1000 / ocean_period ) );
   for ( int x = 0;  x < water_width;  x++ )
   {
      water[ WATERINDEX( x, water_height - 1 ) ] =
	 ocean_height - blocksand[ WATERINDEX( x, water_height - 1 ) ];

      if ( water[ WATERINDEX( x, water_height - 1 ) ] < 0. )
	 water[ WATERINDEX( x, water_height - 1 ) ] = 0.;
   }

   // 4. Differences in water height generate currents to try to level
   // the height (and their efficiency in doing so is the coupling)

   // also, energy is arbitrarily dissipated to keep things realistic
   // and also provide a negative feedback against extremely large
   // waves
   float dissipation_factor = ( 1. - water_dissipation );
   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
      {
	 h_current[ WATERINDEX( x, y ) ] *= dissipation_factor;
	 v_current[ WATERINDEX( x, y ) ] *= dissipation_factor;
	 
	 float height_here = water[ WATERINDEX( x, y ) ] + blocksand[ WATERINDEX( x, y ) ];

	 if ( x == 0 )
 	    h_current[ WATERINDEX( x, y ) ] += water_coupling *
 	       ( ( water[ WATERINDEX( water_width - 1, y ) ] +
		   blocksand[ WATERINDEX( water_width - 1, y ) ] ) - height_here );
 	 else
	    h_current[ WATERINDEX( x, y ) ] += water_coupling *
	       ( ( water[ WATERINDEX( x - 1, y ) ] +
		   blocksand[ WATERINDEX( x - 1, y ) ] ) - height_here );
	 
 	 if ( y == 0 )
	    v_current[ WATERINDEX( x, y ) ] += water_coupling *
 	       ( ( water[ WATERINDEX( x, water_height - 1 ) ] +
		   blocksand[ WATERINDEX( x, water_height - 1 ) ] ) - height_here );
 	 else
	    v_current[ WATERINDEX( x, y ) ] += water_coupling *
	       ( ( water[ WATERINDEX( x, y - 1 ) ] +
		   blocksand[ WATERINDEX( x, y - 1 ) ] ) - height_here );
      }

   // 5. Draw only the blocks that have changed
   for ( int y = 0;  y < water_height;  y++ )
      for ( int x = 0;  x < water_width;  x++ )
      {
	 // thresholding allows for fewer redraws
	 float w = water[ WATERINDEX( x, y ) ];
	 float wc = watercopy[ WATERINDEX( x, y ) ];
	 if ( ( w < level_zero   &&  wc >= level_zero )  ||
	      ( w >= level_zero  &&  wc < level_zero )   ||
	      ( w < level_one    &&  wc >= level_one )   ||
	      ( w >= level_one   &&  wc < level_one )    ||
	      ( w < level_two    &&  wc >= level_two )   ||
	      ( w >= level_two   &&  wc < level_two )       )
	 {
	    int left = x * water_pixelation;
	    int top = y * water_pixelation;
	    int width = water_pixelation;
	    int height = water_pixelation;

	    // graphics_draw() does the cutting to the window width,
	    // but x_expose() doesn't
	    if ( left + width > get_width() ) width = get_width() - left;
	    if ( top + height > get_height() ) height = get_height() - top;

	    if ( width > 0  &&  height > 0 )
	    {
	       // draw the pixels in the buffer
	       graphics_draw( left, top, width, height );
	       
	       // put the buffer to the screen
	       x_expose( left, top, width, height );
	    }
	 }
      }
}

//// sand_brush() ///////////////////////////////////////////////////////

void sand_brush( int x, int y, int button, bool starting )
{
   // communication with previous calls of this function
   static int prevx, prevy;
   static float level;

   if ( prevx >= sand_width  ||  prevy >= sand_height )
   {
      prevx = prevy = 0;
      return;
   }

   if ( x >= sand_width  ||  y >= sand_height )
      return;

   if ( starting  &&  button == 2 )
      level = sand[ SANDINDEX( x, y ) ];

   // get the region
   int left, top, width, height;
   sand_brush_region( x, y, &left, &top, &width, &height );
   // this is the right thing for graphics_, but sand has an extra pixel
   width++; height++;
   int right = left + width;
   int bottom = top + height;

   // button 2 is the most complicated
   if ( ! starting  &&  button == 2  &&  !( x == prevx && y == prevy ) )
   {
      // avoid square root functions by comparing the squares of quantities
      const float brush2 = brush_radius * brush_radius;

      // 1. find out how much sand is removed from the circle (and remove it!)
      float accumulate = 0.;
      for ( int y_ = top;  y_ < bottom;  y_++ )
	 for ( int x_ = left;  x_ < right;  x_++ )
	 {
	    float rad2 = SQR( x_ - x ) + SQR( y_ - y );
	    if ( rad2 < brush2  &&  sand[ SANDINDEX( x_, y_ ) ] > level )
	    {
	       // for smooth changes (physicists hate sharp corners!)
	       // (the "skin" here doesn't correspond to a linear skin
	       // depth because I'm doing everything in
	       // squared-space... this is why it needs to be so large)
	       const float skin2 = brush2 / 1.;

	       // is erf a faster (to compute) function than inverse
	       // tangent or something? both must be interpolated
	       // tables anyway...
	       float diff = ( sand[ SANDINDEX( x_, y_ ) ] - level ) *
		  ( 0.5 - erf( ( rad2 - brush2 ) / skin2 ) / 2. );

	       accumulate += diff;
	       sand[ SANDINDEX( x_, y_ ) ] -= diff;
	    }
	 }

      // 2. develop a normalized heap function to determine how to
      // redistribute the sand (this has nothing to do with
      // random-access data structures! (even though that's where I
      // get it from...))
      // local height and width are the affected portion of the screen only
      float total_heap = 0.;
      float* heap = (float *) malloc( sizeof( float ) * height * width );
      ASSERT( heap );

      // where the fingernail ball will be centered
      float denominator = sqrt( ( x - prevx ) * ( x - prevx ) +
				( y - prevy ) * ( y - prevy )   );
      float nailx = move_distance * ( x - prevx ) / denominator + prevx;
      float naily = move_distance * ( y - prevy ) / denominator + prevy;

      for ( int y_ = top;  y_ < bottom;  y_++ )
	 for( int x_ = left;  x_ < right;  x_++ )
	 {
	    float rad2 = SQR( x_ - x ) + SQR( y_ - y );
	    float nail2 = ( SQR( x_ - nailx ) + SQR( y_ - naily ) );

	    // this is to say that the fingernail radius is
	    // sqrt( nail_radius_factor2 ) times larger than the brush
	    if ( rad2 < brush2  ||  nail2 > nail_radius_factor2 * brush2 )
	       heap[ HEAPINDEX( x_, y_ ) ] = 0.;
	    else
	       heap[ HEAPINDEX( x_, y_ ) ] = ( ( rad2 - brush2 ) *
					       ( nail_radius_factor2 * brush2 - nail2 ) );

	    total_heap += heap[ HEAPINDEX( x_, y_ ) ];
	 }

      // 3. pile up the sand that was removed from the circle
      float scale = 1. / water_pixelation / water_pixelation;
      if ( total_heap != 0. )
	 for ( int y_ = top;  y_ < bottom;  y_++ )
	    for ( int x_ = left;  x_ < right;  x_++ )
	    {
	       float change = accumulate * heap[ HEAPINDEX( x_, y_ ) ] / total_heap;

	       sand[ SANDINDEX( x_, y_ ) ] += change;
	       water[ WATERGIVENSAND( x_, y_ ) ] -= change * scale;
	       if ( water[ WATERGIVENSAND( x_, y_ ) ] < 0. )
		  water[ WATERGIVENSAND( x_, y_ ) ] = 0.;
	    }

      free( heap );
   }

   // buttons 1 and 3 are pretty similar
   else
   {
      float scale = 1. / water_pixelation / water_pixelation;
      for( int y_ = top;  y_ < bottom;  y_++ )
	 for( int x_ = left;  x_ < right;  x_++ )
	 {
	    float change = brush_strength * exp( -( SQR( x_ - x ) + SQR( y_ - y ) )
						 / 2 / SQR( brush_radius ) );
	    if ( button == 3 )
	       change = -change;

	    sand[ SANDINDEX( x_, y_ ) ] += change;

	    // only remove water if we are ADDING sand
	    if ( button == 1 )
	    {
	       water[ WATERGIVENSAND( x_, y_ ) ] -= change * scale;
	       if ( water[ WATERGIVENSAND( x_, y_ ) ] < 0. )
		  water[ WATERGIVENSAND( x_, y_ ) ] = 0.;
	    }
	 }
   }

   update_blocksand( int( floor( float( left ) / float( water_pixelation ) ) ),
 		     int( floor( float( top ) / float( water_pixelation ) ) ),
 		     int( ceil( float( right ) / float( water_pixelation ) ) ),
 		     int( ceil( float( bottom ) / float( water_pixelation ) ) )  );

   // used by button 2 to determine the direction to push the heap
   prevx = x;
   prevy = y;
}

//// sand_brush_region() ////////////////////////////////////////////////

void sand_brush_region( int x, int y,
			int* left, int* top, int* width, int* height )
{
   *left = x - brush_range;
   *top = y - brush_range;
   *width = 2 * brush_range;
   *height = 2 * brush_range;

   if ( *left < 0 ) *left = 0;
   if ( *top < 0 ) *top = 0;
   // remember that sand has an extra pixel along the right and bottom
   if ( *left + *width > sand_width - 1 ) *width = sand_width - 1 - *left;
   if ( *top + *height > sand_height - 1 ) *height = sand_height - 1 - *top;
}

//// random_sand_brush() ////////////////////////////////////////////////

void random_sand_brush( int include_width, int include_height,
			int exclude_width, int exclude_height )
{
   for ( int y = 0;  y < include_height;  y++ )
      for ( int x = 0;  x < include_width;  x++ )
	 if ( x > exclude_width  ||  y > exclude_height )
	    if ( ( float( rand() ) / float( RAND_MAX ) ) > 0.9981 )
	    {
	       int button = ( ( rand() > ( RAND_MAX / 2 ) ) ? 1 : 3 );
	       sand_brush( x, y, button, true );
	    }
}

//// update_blocksand() /////////////////////////////////////////////////

void update_blocksand( int left, int top, int right, int bottom )
{
   for ( int y = top;  y < bottom;  y++ )
      for ( int x = left;  x < right;  x++ )
      {
	 int left_ = x * water_pixelation;
	 int right_ = ( x + 1 ) * water_pixelation;
	 int top_ = y * water_pixelation;
	 int bottom_ = ( y + 1 ) * water_pixelation;
	 if ( right_ > sand_width ) right_ = sand_width;
	 if ( bottom_ > sand_height ) bottom_ = sand_height;

	 float numerator = 0;
	 int denominator = 0;
	 for ( int y_ = top_;  y_ < bottom_;  y_++ )
	    for ( int x_ = left_;  x_ < right_;  x_++ )
	    {
	       numerator += sand[ SANDINDEX( x_, y_ ) ];
	       denominator++;
	    }

	 blocksand[ WATERINDEX( x, y ) ] = numerator / float( denominator );
      }
}

