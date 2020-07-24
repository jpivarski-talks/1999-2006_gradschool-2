// -*- C++ -*-
#if !defined(FINDTWOPHOTON_FINDTWOPHOTON_H)
#define FINDTWOPHOTON_FINDTWOPHOTON_H
//
// Package:     <FindTwoPhoton>
// Module:      FindTwoPhoton
//
/**\class FindTwoPhoton FindTwoPhoton.h FindTwoPhoton/FindTwoPhoton.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun 16 21:55:06 EDT 2003
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

class FindTwoPhoton : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FindTwoPhoton( void );                      // anal1 
      virtual ~FindTwoPhoton();                   // anal5 

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
      FindTwoPhoton( const FindTwoPhoton& );

      // ------------ assignment operator(s) ---------------------
      const FindTwoPhoton& operator=( const FindTwoPhoton& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FindTwoPhoton::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FINDTWOPHOTON_FINDTWOPHOTON_H */
