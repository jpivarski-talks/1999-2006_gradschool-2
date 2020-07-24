// -*- C++ -*-
#if !defined(FINDLAMBDAS_FINDLAMBDAS_H)
#define FINDLAMBDAS_FINDLAMBDAS_H
//
// Package:     <FindLambdas>
// Module:      FindLambdas
//
/**\class FindLambdas FindLambdas.h FindLambdas/FindLambdas.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  9 12:50:13 EDT 2003
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
#include "HistogramInterface/HINtuple.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class FindLambdas : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kRun,
	 kEvent,

	 kV1X,
	 kV1Y,
	 kV1Z,
	 kV1Px,
	 kV1Py,
	 kV1Pz,
	 kV1Pm,
	 kV1Nx,
	 kV1Ny,
	 kV1Nz,
	 kV1Nm,
	 kV1ProtonSign,
	 kMassLambda1,

	 kV2X,
	 kV2Y,
	 kV2Z,
	 kV2Px,
	 kV2Py,
	 kV2Pz,
	 kV2Pm,
	 kV2Nx,
	 kV2Ny,
	 kV2Nz,
	 kV2Nm,
	 kV2ProtonSign,
	 kMassLambda2,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      FindLambdas( void );                      // anal1 
      virtual ~FindLambdas();                   // anal5 

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
      FindLambdas( const FindLambdas& );

      // ------------ assignment operator(s) ---------------------
      const FindLambdas& operator=( const FindLambdas& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindLambdas::*iMethod)( Frame& ),
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

#endif /* FINDLAMBDAS_FINDLAMBDAS_H */
