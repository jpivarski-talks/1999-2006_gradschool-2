// -*- C++ -*-
//
// Package:     <package>
// Module:      HbookHistProf
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Marc Soussa
// Created:     Sat Dec  5 18:17:20 EST 1998
// $Id: HbookHistProf.cc,v 1.12 2003/11/03 20:40:25 mccann Exp $
//
// Revision history
//
// $Log: HbookHistProf.cc,v $
// Revision 1.12  2003/11/03 20:40:25  mccann
// Made hreset_() length-of-string argument (3rd arg) explicit, correcting a suez-crashing/rzn-mangling bug
//
// Revision 1.11  2003/01/17 20:35:35  cdj
// use namespace to match HistogramInterface
//
// Revision 1.10  2002/07/23 18:55:54  cdj
// fixed reset method which passed a empty string instead of a blank string to hreset_
//
// Revision 1.9  2002/05/06 17:47:40  mccann
// added weighted profiles and the HIHistProf option kWeightedError
//
// Revision 1.8  2002/03/26 19:37:17  cdj
// reset method now makes sure it is in the correct directory
//
// Revision 1.7  2001/09/21 03:21:36  mccann
// Finally implemented reset for histograms (1d,2d,prof)
//
// Revision 1.6  2001/08/03 17:29:17  bkh
// Implement value and error fuctionality
//
// Revision 1.5  2000/07/11 20:48:20  bkh
// Set directory before fortran HBOOK calls
//
// Revision 1.4  2000/06/19 18:18:12  bkh
// Implement new pure virtual functions from HistogramInterface
//
// Revision 1.3  1999/12/23 23:34:46  cdj
// updated to new histogram interface (for arithmetic operations)
//
// Revision 1.2  1999/09/29 17:55:47  cdj
// added histogram directories
//
// Revision 1.1.1.1  1999/09/06 22:02:30  mkl
// imported HbookHistogram source
//
// Revision 1.1.1.1  1999/02/23 22:00:59  cdj
// imported HbookHistogram source
//
#include <string.h>
#include <math.h>
#include <assert.h>
#include "Experiment/Experiment.h"
#include "HbookHistogram/hbook_functions.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "HbookHistogram/HbookHistProf.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "HbookHistogram.HbookHistProf" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: HbookHistProf.cc,v 1.12 2003/11/03 20:40:25 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
HbookHistProf::HbookHistProf( HbookHistDir* iParent,
                              Count          iId,
			      const string&  iTitle,
			      unsigned int   iNChannels,
			      float          iLowEdgeX,
			      float          iHighEdgeX,
			      float          iLowEdgeY,
			      float          iHighEdgeY,
			      HIHistProf::DisplayErrorsAs iDisplayErrorsAs ) :
  HIHistProf(
	      iId,
	      iTitle,
	      iNChannels,
	      iLowEdgeX,
	      iHighEdgeX,
	      iLowEdgeY,
	      iHighEdgeY,
	      iDisplayErrorsAs ),
  HbookDirContents( iParent )
{
  hbookinit_();
  FInteger ID = id() ;
  FInteger NX = nChannels() ;

  if ( ( hexist_( &ID ) & 0x1 ) )
    return;

  FChar* ERROR ;

  switch( iDisplayErrorsAs ) {
    case HIHistProf::kSpread : ERROR = "S" ; 
      break ;

    case HIHistProf::kErrorOnMean : ERROR = " " ;
      break ;
  }

  if ( iDisplayErrorsAs == kWeightedError ) {
     // for my error handling, I'll need a 1D histogram as a dummy
     float bitsPerChannel( 0. );
     hbook1_( &ID,
	      iTitle.c_str(),
	      &NX,
	      &iLowEdgeX,
	      &iHighEdgeX,
	      &bitsPerChannel,
	      iTitle.size() );

     m_numerator = new double[ iNChannels ];
     m_denominator = new double[ iNChannels ];
     
     for ( int i = 0;  i < iNChannels;  i++ ) {
	m_numerator[i] = 0.;
	m_denominator[i] = 0.;
     }

  } else { // normal displayError values get sent to hbook

     hbprof_( &ID,
	      iTitle.c_str(),
	      &NX,
	      &iLowEdgeX,
	      &iHighEdgeX,
	      &iLowEdgeY,
	      &iHighEdgeY,
	      ERROR,
	      iTitle.size(),
	      strlen( ERROR ) );

     m_numerator = NULL;
     m_denominator = NULL;

  } // end if iDisplayErrorAs...

  m_hbookUpdated = true;
  return;
}

// HbookHistProf::HbookHistProf( const HbookHistProf& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

HbookHistProf::~HbookHistProf()
{
   if ( errorDisplay() == kWeightedError ) {
      assert( m_numerator != NULL  &&  m_denominator != NULL );

      if ( ! m_hbookUpdated ) {
	 setDir();
	 updateAssociatedHistogram();
      }

      delete [] m_numerator;
      delete [] m_denominator;
   }
}

// Fill a profile plot
void HbookHistProf::fill ( float iXEntry,
			   float iYEntry,
			   float iWeight )
{
   if ( errorDisplay() == kWeightedError ) {
      assert( m_numerator != NULL  &&  m_denominator != NULL );

      if ( iYEntry >= lowEdgeY()  &&  iYEntry <= highEdgeY() ) {
	 int index =
	    int( floor( ( iXEntry - lowEdgeX() ) / ( highEdgeX() - lowEdgeX() )
			* double( nChannels() ) ) ) ;

	 if ( index >= 0  &&  index < nChannels() ) {
	    m_numerator[index] += iYEntry * iWeight;
	    m_denominator[index] += iWeight;

	    m_hbookUpdated = false;
	 }
	 // don't worry about recording over/underflows... hbook profile
	 // plots don't keep track of them!

      } // end if y entry is within bounds

   } else { // in case of normal uncertainty handling, pass to hbook

      setDir();
      FInteger ID = id();
      hfill_( &ID,
	      &iXEntry,
	      &iYEntry,
	      &iWeight );
   }
}


float 
HbookHistProf::sumWithinLimits() const 
{
   const_cast< HbookHistProf* >( this ) ->setDir();

   if ( ! const_cast< HbookHistProf* >( this ) ->m_hbookUpdated ) {
      const_cast< HbookHistProf* >( this ) ->updateAssociatedHistogram();
      const_cast< HbookHistProf* >( this ) ->m_hbookUpdated = true;
   }

   FInteger ID ( id() ) ;
   return hsum_( &ID ) ;
}

float 
HbookHistProf::maxValue()        const
{
   const_cast< HbookHistProf* >( this ) ->setDir();

   if ( ! const_cast< HbookHistProf* >( this ) ->m_hbookUpdated ) {
      const_cast< HbookHistProf* >( this ) ->updateAssociatedHistogram();
      const_cast< HbookHistProf* >( this ) ->m_hbookUpdated = true;
   }

   FInteger ID ( id() ) ;
   return hmax_( &ID ) ;
}

float 
HbookHistProf::minValue()        const
{
   const_cast< HbookHistProf* >( this ) ->setDir();

   if ( ! const_cast< HbookHistProf* >( this ) ->m_hbookUpdated ) {
      const_cast< HbookHistProf* >( this ) ->updateAssociatedHistogram();
      const_cast< HbookHistProf* >( this ) ->m_hbookUpdated = true;
   }

   FInteger ID ( id() ) ;
   return hmin_( &ID ) ;
}

float
HbookHistProf::channelValue( unsigned int channel ) const
{
   const_cast< HbookHistProf* >( this ) ->setDir();
   FInteger Channel = channel;
   FInteger ID = id();

   if ( ! const_cast< HbookHistProf* >( this ) ->m_hbookUpdated ) {
      const_cast< HbookHistProf* >( this ) ->updateAssociatedHistogram();
      const_cast< HbookHistProf* >( this ) ->m_hbookUpdated = true;
   }

   return hi_( &ID, &Channel );
}

float
HbookHistProf::channelError( unsigned int iChannel ) const
{
   const_cast< HbookHistProf* >( this ) ->setDir();
   FInteger ID = id();
   FInteger channel = iChannel;

   if ( ! const_cast< HbookHistProf* >( this ) ->m_hbookUpdated ) {
      const_cast< HbookHistProf* >( this ) ->updateAssociatedHistogram();
      const_cast< HbookHistProf* >( this ) ->m_hbookUpdated = true;
   }

   return hie_( &ID, &channel );
}


/*  Leave this stuff out until requested
// Scale a profile plot
void HbookHistProf::scale( const float iScale )
{
   add( *this, *this, 0., iScale );
}

// Add two profile plots
void 
HbookHistProf::add ( const HIHistProf& rProf1,
		     const HIHistProf& rProf2,
		     const float iScale1,
		     const float iScale2 )
{
   const string kOper = "+";

   FInteger ID1 = rProf1.id();
   FInteger ID2 = rProf2.id();
   FInteger ID3 = id();

   // Call fortran arithmetic operation function
   hopera_( &ID1, kOper.c_str(), &ID2, &ID3, 
	    &iScale1, &iScale2, kOper.size() ); 
}


// Subtract two profile plots
void 
HbookHistProf::sub ( const HIHistProf& rProf1,
		     const HIHistProf& rProf2,
		     const float iScale1,
		     const float iScale2 )
{
   const string kOper = "-";


   FInteger ID1 = rProf1.id();
   FInteger ID2 = rProf2.id();
   FInteger ID3 = id();


   // Call fortran arithmetic operation function
   hopera_( &ID1, kOper.c_str(), &ID2, &ID3, 
	    &iScale1, &iScale2, kOper.size() );
}


// Multiply two profile plots
void 
HbookHistProf::mult ( const HIHistProf& rProf1,
		      const HIHistProf& rProf2,
		      const float iScale1,
		      const float iScale2 )
{
   const string kOper = "*";


   FInteger ID1 = rProf1.id();
   FInteger ID2 = rProf2.id();
   FInteger ID3 = id();


   // Call fortran arithmetic operation function
   hopera_( &ID1, kOper.c_str(), &ID2, &ID3, 
	    &iScale1, &iScale2, kOper.size() );
}


// Divide two profile plots
void 
HbookHistProf::div ( const HIHistProf& rProf1,
		     const HIHistProf& rProf2,
		     const float iScale1,
		     const float iScale2 )
{
   const string kOper = "/";

   FInteger ID1 = rProf1.id();
   FInteger ID2 = rProf2.id();
   FInteger ID3 = id();


   // Call fortran arithmetic operation function
   hopera_( &ID1, kOper.c_str(), &ID2, &ID3, 
	    &iScale1, &iScale2, kOper.size() );
}

// Copy a profile plot
void HbookHistProf::copy( const HIHistProf& rOriginal )
{
//  USING FORTRAN COPYROUTINE-MORE DANGEROUS!
//   const string kTitle = title();

//   FInteger ID1 = rOriginal.id();
//  FInteger ID2 = id();

//   hcopy_( &ID1, &ID2, kTitle.c_str(), kTitle.size() );


   add( *this, rOriginal, 0., 1.0 );
}
*/

//
// assignment operators
//
// const HbookHistProf& HbookHistProf::operator=( const HbookHistProf& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void HbookHistProf::reset()
{
   if ( errorDisplay() == kWeightedError ) {
      assert( m_numerator != NULL  &&  m_denominator != NULL );

      unsigned int nchan( nChannels() );
      for ( int i = 0;  i < nchan;  i++ ) {
	 m_numerator[i] = 0.;
	 m_denominator[i] = 0.;
      }
      m_hbookUpdated = true;
   }

   setDir();
   FInteger ID = id();
   FChar* CHTITL = " ";
   hreset_( &ID, CHTITL, 1 );
}
//
// const member functions
//
/*
float 
HbookHistProf::getValue( unsigned int channel ) const
{
   return 0;
}
*/ 
//
// static member functions
//

const void HbookHistProf::updateAssociatedHistogram()
{
   assert( m_numerator != NULL  &&  m_denominator != NULL );

   unsigned int nchan( nChannels() );
   FReal* valueArray = new FReal[nchan];
   FReal* errorArray = new FReal[nchan];

   for ( int i = 0;  i < nchan;  i++ )
      if ( m_denominator[i] != 0. ) {
	 valueArray[i] = m_numerator[i] / m_denominator[i];
	 errorArray[i] = sqrt( 1. / m_denominator[i] );
      } else {
	 valueArray[i] = 0.;
	 errorArray[i] = 0.;
      }

   setDir();
   FInteger ID = id();
   hpak_( &ID, valueArray );
   hpake_( &ID, errorArray );

   delete [] valueArray;
   delete [] errorArray;
}
