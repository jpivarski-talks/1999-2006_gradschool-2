// -*- C++ -*-
#if !defined(ORDINARY_ORDINARY_H)
#define ORDINARY_ORDINARY_H
//
// Package:     <Ordinary>
// Module:      Ordinary
//
/**\class Ordinary Ordinary.h Ordinary/Ordinary.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Nov 18 14:26:47 EST 2003
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

class Ordinary : public Processor
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
	 kDCA,
	 kDrift,
	 kResidual,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Ordinary( void );                      // anal1 
      virtual ~Ordinary();                   // anal5 

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
      Ordinary( const Ordinary& );

      // ------------ assignment operator(s) ---------------------
      const Ordinary& operator=( const Ordinary& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Ordinary::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ORDINARY_ORDINARY_H */
