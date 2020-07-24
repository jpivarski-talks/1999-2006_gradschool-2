// -*- C++ -*-
#if !defined(MYTHIRDPROC_MYTHIRDPROC_H)
#define MYTHIRDPROC_MYTHIRDPROC_H
//
// Package:     <MyThirdProc>
// Module:      MyThirdProc
//
/**\class MyThirdProc MyThirdProc.h MyThirdProc/MyThirdProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  6 18:44:31 EDT 2005
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
#include "CommandPattern/Parameter.h"

// forward declarations

class MyThirdProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MyThirdProc( void );                      // anal1 
      virtual ~MyThirdProc();                   // anal5 

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
      MyThirdProc( const MyThirdProc& );

      // ------------ assignment operator(s) ---------------------
      const MyThirdProc& operator=( const MyThirdProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MyThirdProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      Parameter<DABoolean> m_wantCosmics;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MYTHIRDPROC_MYTHIRDPROC_H */
