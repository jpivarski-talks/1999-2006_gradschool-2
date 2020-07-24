#include "graphics.h"
#include "sand_water.h"

int width = 400;
int height = 300;

float light_angle = 150. * 3.14 / 180.;
float lightx = cos( light_angle );
float lighty = sin( light_angle );
const float lightz = 5.;

bool contours = true;

unsigned char* buffer = NULL;
float* sand_speckle = NULL;

//// graphics_init() ////////////////////////////////////////////////////

void graphics_init( GlobalParams par )
{
   width = par.window_width;
   height = par.window_height;

   buffer = (unsigned char*) malloc( 3 * sizeof( unsigned char ) * width * height );
   sand_speckle = (float*) malloc( sizeof( float ) * width * height );

   ASSERT( buffer );
   ASSERT( sand_speckle );

   for ( int y = 0;  y < height;  y++ )
      for( int x = 0;  x < width;  x++ )
      {
	 // red, green and blue
	 buffer[ BUFINDEX( x, y ) + 0 ] = 0;
	 buffer[ BUFINDEX( x, y ) + 1 ] = 0;
	 buffer[ BUFINDEX( x, y ) + 2 ] = 0;

	 sand_speckle[ SPECKINDEX( x, y ) ] = generate_sand_speckle();
      }
}

//// graphics_resize() //////////////////////////////////////////////////

void graphics_resize( int new_width, int new_height )
{
   unsigned char* new_buffer = (unsigned char*) malloc( 3 * sizeof( unsigned char ) *
							new_width * new_height );
   float* new_sand_speckle = (float*) malloc( sizeof( float ) * new_width * new_height );

   ASSERT( new_buffer );
   ASSERT( new_sand_speckle );

   // Looks crappy.  :(
//
//    for ( int y = 0;  y < new_height;  y++ )
//       for( int x = 0;  x < new_width;  x++ )
// 	 if ( x < width  &&  y < height )
// 	 {
// 	    // red, green and blue
// 	    new_buffer[ NEWINDEX( x, y ) + 0 ] = buffer[ BUFINDEX( x, y ) + 0 ];
// 	    new_buffer[ NEWINDEX( x, y ) + 1 ] = buffer[ BUFINDEX( x, y ) + 1 ];
// 	    new_buffer[ NEWINDEX( x, y ) + 2 ] = buffer[ BUFINDEX( x, y ) + 2 ];

// 	    new_sand_speckle[ NEWSPECKINDEX( x, y ) ] =
// 	       sand_speckle[ SPECKINDEX( x, y ) ];
// 	 }
// 	 else
// 	 {
// 	    // red, green and blue
// 	    new_buffer[ NEWINDEX( x, y ) + 0 ] = 0;
// 	    new_buffer[ NEWINDEX( x, y ) + 1 ] = 0;
// 	    new_buffer[ NEWINDEX( x, y ) + 2 ] = 0;

// 	    new_sand_speckle[ NEWSPECKINDEX( x, y ) ] = generate_sand_speckle();
// 	 }
   for ( int y = 0;  y < new_height;  y++ )
      for( int x = 0;  x < new_width;  x++ )
      {
	 // red, green and blue
	 new_buffer[ NEWINDEX( x, y ) + 0 ] = 0;
	 new_buffer[ NEWINDEX( x, y ) + 1 ] = 0;
	 new_buffer[ NEWINDEX( x, y ) + 2 ] = 0;

	 new_sand_speckle[ NEWSPECKINDEX( x, y ) ] = generate_sand_speckle();
      }

   free( buffer );
   free( sand_speckle );

   buffer = new_buffer;
   sand_speckle = new_sand_speckle;

   width = new_width;
   height = new_height;
}

//// graphics_cleanup() /////////////////////////////////////////////////

void graphics_cleanup()
{
   free( buffer );
}

//// change_light_angle() ///////////////////////////////////////////////

void change_light_angle( float delta )
{
   light_angle += delta;
   lightx = cos( light_angle );
   lighty = sin( light_angle );
}

//// toggle_contours() //////////////////////////////////////////////////

void toggle_contours()
{
   contours = ( ! contours );
}

//// generate_sand_speckle() ////////////////////////////////////////////

float generate_sand_speckle()
{
   // Get gaussian deviates by the elimination method
   float rx, ry;
   do {
      rx = ( float( rand() ) / float( RAND_MAX ) ) * 6. - 3.;
      ry = ( float( rand() ) / float( RAND_MAX ) );
   } while( ry > exp( -( rx * rx / 2. ) ) );
	 
   return 1. + rx / 10.;
}

//// graphics_draw() ////////////////////////////////////////////////////

void graphics_draw( int x, int y, int box_width, int box_height )
{
   int xbegin = ( x < 0 ? 0 : x );
   int ybegin = ( y < 0 ? 0 : y );
   int xend = x + box_width;
   int yend = y + box_height;
   if ( xend >= width ) xend = width;
   if ( yend >= height ) yend = height;

   for( int y_ = y;  y_ < yend;  y_++ )
      for( int x_ = x;  x_ < xend;  x_++ )
	 pixel_draw( x_, y_ );
}

//// pixel_draw() ///////////////////////////////////////////////////////
// This is where a lot of time is spent. It is awkward because I am
// trying to optimize it...

void pixel_draw( int x, int y )
{
   unsigned char red, green, blue;

   // calculate shading from angle of illumination
   // (3-D mesh is made from triangles of sand pixels)
   float here = sand_pixel( x, y );
   float right = sand_pixel( x + 1, y );
   float down = sand_pixel( x, y + 1 );

   const float min_reflection = -20.;
   const float max_reflection =  20.;
   // This is the dot product of the normal to the surface with the
   // vector { lightx, lighty, lightz } (the normal to the surface is
   // taken to have unit z-projection (maybe this would be better if
   // normalized... but it looks all right!)
   float reflection = ( ( ( lighty * ( right - here ) +
			    lightx * ( down - here ) +
			    lightz )
			  - min_reflection )
			/ ( max_reflection - min_reflection ) );
   if ( reflection > 1. ) reflection = 1.;
   else if ( reflection < 0. ) reflection = 0.;

   float water_depth = water_pixel( x, y );  // this involves a little calculation

   const float max_sand_depth = 200.;
   const float min_sand_depth = -200.;
   float norm_sand = 0.;     // only defined for water_depth < level_one

   if ( water_depth < level_one )
   {
      norm_sand = ( here - min_sand_depth ) / ( max_sand_depth - min_sand_depth );
      if ( norm_sand > 1. ) norm_sand = 1.;
      if ( norm_sand < 0. ) norm_sand = 0.;
   }

   // Four levels of water depth: 
   if ( water_depth < level_zero )
   {
      sand_color( norm_sand, reflection, sand_speckle[ SPECKINDEX( x, y ) ],
		  &red, &green, &blue );
   }
   else if ( water_depth < level_one )
   {
      sand_color( norm_sand, reflection, sand_speckle[ SPECKINDEX( x, y ) ],
		  &red, &green, &blue );

      // first level is foam--- you can see the sand underneath but it
      // is whitened (50% translucent)
//        if ( water_depth + blocksand_pixel( x, y ) > sand_pixel( x, y ) )
//        {
	 red = (unsigned char)( ceil( ( 1. * red + 0xFF ) / 2. ) );
	 green = (unsigned char)( ceil( ( 1. * green + 0xFF ) / 2. ) );
	 blue = (unsigned char)( ceil( ( 1. * blue + 0xFF ) / 2. ) );
//        }
   }
   else if ( water_depth < level_two )
   {
      // see note about brightness in the "else" part. This one is
      // that, averaged with white (like the foam above)
      float brightness = 133.1 + 95.428 * sqrt( reflection );

      red = green = 0;
      blue = (unsigned char)( ceil( brightness ));
   }
   else
   {
      // I used to calculate the sand first and get the water
      // brightness from the sand--- but that would be nominally the
      // following:
      float brightness = 11.23 + 190.86 * sqrt( reflection );

      red = green = 0;
      blue = (unsigned char)( ceil( brightness ));
   }

   // since both contours and water shading are multiplicative
   // effects, it doesn't matter if there's water or sand here
   if ( contours )
   {
      // this contortion of code may make things faster without contour lines
      if ( water_depth >= level_one )
      {
	 norm_sand = ( here - min_sand_depth ) / ( max_sand_depth - min_sand_depth );
	 if ( norm_sand > 1. ) norm_sand = 1.;
	 if ( norm_sand < 0. ) norm_sand = 0.;
      }
      
      // the choices of 100 and 10 for modularization define contour
      // widths and spacings
      if ( int( floor( norm_sand * 100 ) ) % 10 == 5 )
      {
	 const float contour_dimming = 0.75;
	 red = (unsigned char)( ceil( red * contour_dimming ) );
	 green = (unsigned char)( ceil( green * contour_dimming ) );
	 blue = (unsigned char)( ceil( blue * contour_dimming ) );
      }
   }

   // now we have to actually draw it into the buffer!!!
   buffer[ BUFINDEX( x, y ) + 0 ] = red;
   buffer[ BUFINDEX( x, y ) + 1 ] = green;
   buffer[ BUFINDEX( x, y ) + 2 ] = blue;
}

//// sand_color() ///////////////////////////////////////////////////////
// sand color basically follows a brightness line on a nice sandy hue
// there's a little variation in color with height and speckling in green

void sand_color( float sand_depth, float reflection, float sand_speck,
		 unsigned char* red, unsigned char* green, unsigned char* blue )
{
   // physically, the intensity should be the square of the
   // wavefunction (but the square root looks better!)
   *red = (unsigned char)( ceil( sqrt( reflection ) * 0xF0 + 0x0F ) );

   // putting all the speckle in the green channel is convenient and
   // looks pretty nice
   float tmp = ceil( float( *red ) * ( 167 * sand_speck +
				       22 * sand_depth ) / 216 );
   if ( tmp > 0xFF ) tmp = float( 0xFF );
   *green = (unsigned char)( tmp );

   *blue = (unsigned char)( ceil( float( *red ) * ( 80 * sand_depth + 51 ) / 216 ) );
}

