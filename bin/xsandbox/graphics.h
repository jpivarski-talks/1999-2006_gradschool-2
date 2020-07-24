#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "xsandbox.h"

#define BUFINDEX(x,y) ( 3 * ( ( y ) * width + ( x ) ) )
#define NEWINDEX(x,y) ( 3 * ( ( y ) * new_width + ( x ) ) )
#define SPECKINDEX(x,y) ( ( y ) * width + ( x ) )
#define NEWSPECKINDEX(x,y) ( ( y ) * new_width + ( x ) )

const float level_zero = 1.;  // below this means just draw sand
const float level_one = 20.;
const float level_two = 60.;

void graphics_init( GlobalParams par );
void graphics_resize( int new_width, int new_height );
void graphics_cleanup();

void change_light_angle( float delta );
void toggle_contours();

float generate_sand_speckle();

void graphics_draw( int x, int y, int box_width, int box_height );
void pixel_draw( int x, int y );
void sand_color( float sand_depth, float reflection, float sand_speck,
		 unsigned char* red, unsigned char* green, unsigned char* blue );

extern unsigned char* buffer;
extern int width;
extern int height;

//// get_buffer() ///////////////////////////////////////////////////////

inline unsigned char* get_buffer( int x, int y )
{
   ASSERT( buffer );
   ASSERT( x >= 0 );
   ASSERT( x < width );
   ASSERT( y >= 0 );
   ASSERT( y < height );

   return &buffer[ BUFINDEX( x, y ) ];
}

//// get_linesize() /////////////////////////////////////////////////////

inline int get_linesize()
{
   return ( 3 * width );
}

//// get_width() ////////////////////////////////////////////////////////

inline int get_width()
{
   return width;
}

//// get_height() ///////////////////////////////////////////////////////

inline int get_height()
{
   return height;
}

#endif // ! GRAPHICS_H
