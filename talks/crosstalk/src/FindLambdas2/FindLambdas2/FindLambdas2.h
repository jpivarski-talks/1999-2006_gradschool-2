// -*- C++ -*-
#if !defined(FINDLAMBDAS2_FINDLAMBDAS2_H)
#define FINDLAMBDAS2_FINDLAMBDAS2_H
//
// Package:     <FindLambdas2>
// Module:      FindLambdas2
//
/**\class FindLambdas2 FindLambdas2.h FindLambdas2/FindLambdas2.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jun 10 12:13:57 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "KinematicTrajectory/KTHelix.h"
#include "HistogramInterface/HINtuple.h"

// forward declarations

class FindLambdas2 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kRun,
	 kEvent,
	 kQual,
	 kX,
	 kY,
	 kZ,
	 kPx,
	 kPy,
	 kPz,
	 kNx,
	 kNy,
	 kNz,
	 kSign,
	 kMLambda,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      FindLambdas2( void );                      // anal1 
      virtual ~FindLambdas2();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      FindLambdas2( const FindLambdas2& );

      // ------------ assignment operator(s) ---------------------
      const FindLambdas2& operator=( const FindLambdas2& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindLambdas2::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      DABoolean calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
				   KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FINDLAMBDAS2_FINDLAMBDAS2_H */
