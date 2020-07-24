// -*- C++ -*-
#if !defined(FINDTAUS_FINDTAUS_H)
#define FINDTAUS_FINDTAUS_H
//
// Package:     <FindTaus>
// Module:      FindTaus
//
/**\class FindTaus FindTaus.h FindTaus/FindTaus.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Jun 13 17:21:46 EDT 2003
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

class FindTaus : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FindTaus( void );                      // anal1 
      virtual ~FindTaus();                   // anal5 

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
      FindTaus( const FindTaus& );

      // ------------ assignment operator(s) ---------------------
      const FindTaus& operator=( const FindTaus& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindTaus::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FINDTAUS_FINDTAUS_H */
