#ifndef SAND_WATER_H
#define SAND_WATER_H

#include "xsandbox.h"

#define SQR(x) ( ( x ) * ( x ) )

#define SANDINDEX(x,y) ( ( y ) * sand_width + ( x ) )
#define WATERINDEX(x,y) ( ( y ) * water_width + ( x ) )
#define NEWSANDINDEX(x,y) ( ( y ) * new_sand_width + ( x ) )
#define NEWWATERINDEX(x,y) ( ( y ) * new_water_width + ( x ) )
#define HEAPINDEX(x,y) ( ( y - top ) * width + ( x - left ) )
#define WATERGIVENSAND(x,y) WATERINDEX( int( floor( x / water_pixelation ) ),      \
					int( floor( y / water_pixelation ) )  )
#define NEWWATERGIVENSAND(x,y) NEWWATERINDEX( int( floor( x / water_pixelation ) ),      \
					      int( floor( y / water_pixelation ) )  )

const float brush_strength = 5.;
const float move_strength = 15.;
const float move_distance = 20.;
const float brush_radius = 15.;
const float nail_radius_factor2 = 2.;
const int brush_range = int( ceil( 2.6 * brush_radius ) );

void sand_water_init( GlobalParams par );
void sand_water_resize( int new_width, int new_height );
void sand_water_cleanup();
void sand_water_update();

void sand_brush( int x, int y, int button, bool starting );
void sand_brush_region( int x, int y,
			int* left, int* top, int* width, int* height );
void random_sand_brush( int include_width, int include_height,
			int exclude_width, int exclude_height );

// these are water coordinates
void update_blocksand( int left, int top, int right, int bottom );

extern float* sand;
extern float* blocksand;
extern float* water;
extern int sand_width;
extern int sand_height;
extern int water_width;
extern int water_height;
extern int water_pixelation;

//// sand_pixel() ///////////////////////////////////////////////////////

inline float sand_pixel( int x, int y )
{
   return sand[ SANDINDEX( x, y ) ];
}

//// blocksand_pixel() //////////////////////////////////////////////////

inline float blocksand_pixel( int x, int y )
{
   return blocksand[ WATERGIVENSAND( x, y ) ];
}

//// water_pixel() //////////////////////////////////////////////////////

inline float water_pixel( int x, int y )
{
   return water[ WATERGIVENSAND( x, y ) ];
}

#endif // ! SAND_WATER_H
