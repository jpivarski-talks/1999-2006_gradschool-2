#ifndef XSANDBOX_H
#define XSANDBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

extern "C" void* malloc( unsigned int );
extern "C" void* realloc( void*, unsigned int );
extern "C" void free( void* );

// #define ASSERT( x ) assert( x )
#define ASSERT( x ) 1

struct GlobalParams
{
      bool position_window;
      int window_x;
      int window_y;
      int window_width;
      int window_height;
      
      bool use_water;
      int water_pixelation;
      float water_coupling;
      float water_dissipation;

      int update_time;

      bool use_hill;
      bool use_bumps;

      float ocean_amplitude;
      float ocean_period;
};

int main( int argc, char** argv );
void usage_string();
bool my_args( int argc, char** argv, GlobalParams* p_par );
char* read_int( char* str, int* val );
bool arg_int( char* arg, int* val );
bool arg_float( char* arg, float* val );
bool arg_geometry( char* arg, GlobalParams* p_par );

#endif // ! XSANDBOX_H
