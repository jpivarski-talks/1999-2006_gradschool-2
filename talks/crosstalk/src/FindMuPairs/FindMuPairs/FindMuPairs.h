// -*- C++ -*-
#if !defined(FINDMUPAIRS_FINDMUPAIRS_H)
#define FINDMUPAIRS_FINDMUPAIRS_H
//
// Package:     <FindMuPairs>
// Module:      FindMuPairs
//
/**\class FindMuPairs FindMuPairs.h FindMuPairs/FindMuPairs.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jun 10 14:07:03 EDT 2003
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

class FindMuPairs : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kPosCurv,
	 kPosPhi0,
	 kPosD0,
	 kPosZ0,
	 kPosCotTheta,
	 kNegCurv,
	 kNegPhi0,
	 kNegD0,
	 kNegZ0,
	 kNegCotTheta,
	 kMargin,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      FindMuPairs( void );                      // anal1 
      virtual ~FindMuPairs();                   // anal5 

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
      FindMuPairs( const FindMuPairs& );

      // ------------ assignment operator(s) ---------------------
      const FindMuPairs& operator=( const FindMuPairs& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindMuPairs::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FINDMUPAIRS_FINDMUPAIRS_H */
