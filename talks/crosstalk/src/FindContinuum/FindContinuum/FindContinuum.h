// -*- C++ -*-
#if !defined(FINDCONTINUUM_FINDCONTINUUM_H)
#define FINDCONTINUUM_FINDCONTINUUM_H
//
// Package:     <FindContinuum>
// Module:      FindContinuum
//
/**\class FindContinuum FindContinuum.h FindContinuum/FindContinuum.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun 16 14:42:52 EDT 2003
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

class FindContinuum : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FindContinuum( void );                      // anal1 
      virtual ~FindContinuum();                   // anal5 

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
      FindContinuum( const FindContinuum& );

      // ------------ assignment operator(s) ---------------------
      const FindContinuum& operator=( const FindContinuum& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindContinuum::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FINDCONTINUUM_FINDCONTINUUM_H */
