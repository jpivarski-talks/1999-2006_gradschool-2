// -*- C++ -*-
#if !defined(SIMPLETHINGS_SIMPLETHINGS_H)
#define SIMPLETHINGS_SIMPLETHINGS_H
//
// Package:     <SimpleThings>
// Module:      SimpleThings
//
/**\class SimpleThings SimpleThings.h SimpleThings/SimpleThings.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Nov 17 09:34:09 EST 2003
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

// forward declarations

class SimpleThings : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      SimpleThings( void );                      // anal1 
      virtual ~SimpleThings();                   // anal5 

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
      SimpleThings( const SimpleThings& );

      // ------------ assignment operator(s) ---------------------
      const SimpleThings& operator=( const SimpleThings& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (SimpleThings::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_z0miss;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SIMPLETHINGS_SIMPLETHINGS_H */
