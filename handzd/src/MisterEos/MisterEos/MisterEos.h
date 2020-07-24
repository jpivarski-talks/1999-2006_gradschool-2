// -*- C++ -*-
#if !defined(MISTEREOS_MISTEREOS_H)
#define MISTEREOS_MISTEREOS_H
//
// Package:     <MisterEos>
// Module:      MisterEos
//
/**\class MisterEos MisterEos.h MisterEos/MisterEos.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Nov 14 14:12:01 EST 2003
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

// forward declarations

class MisterEos : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kCurv,
	 kPhi0,
	 kD0,
	 kCotTheta,
	 kZ0,
	 kLayer,
	 kWire,
	 kPhi,
	 kZ,
	 kDCA,
	 kDrift,
	 kNumDRHits,
	 kPPerp,
	 kPZ,
	 kEbeam,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      MisterEos( void );                      // anal1 
      virtual ~MisterEos();                   // anal5 

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
      MisterEos( const MisterEos& );

      // ------------ assignment operator(s) ---------------------
      const MisterEos& operator=( const MisterEos& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MisterEos::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple*   m_ntuple;
      HIHistProf* m_z0missVcotTheta;
      HIHistProf* m_z0missVcotTheta_morebins;
      HIHistProf* m_residualVz;
      HIHist2D*   m_residualVz_2d;
      HIHist1D*   m_bunchmargin;
      HIHist1D*   m_cotTheta;
      HIHist1D*   m_numberHits;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MISTEREOS_MISTEREOS_H */
