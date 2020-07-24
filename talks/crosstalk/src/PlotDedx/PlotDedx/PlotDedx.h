// -*- C++ -*-
#if !defined(PLOTDEDX_PLOTDEDX_H)
#define PLOTDEDX_PLOTDEDX_H
//
// Package:     <PlotDedx>
// Module:      PlotDedx
//
/**\class PlotDedx PlotDedx.h PlotDedx/PlotDedx.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Jun 12 10:27:38 EDT 2003
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

class PlotDedx : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kPPerp,
	 kPz,
	 kDedx,
	 kHitsUsed,
	 kHits,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      PlotDedx( void );                      // anal1 
      virtual ~PlotDedx();                   // anal5 

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
      PlotDedx( const PlotDedx& );

      // ------------ assignment operator(s) ---------------------
      const PlotDedx& operator=( const PlotDedx& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PlotDedx::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PLOTDEDX_PLOTDEDX_H */
