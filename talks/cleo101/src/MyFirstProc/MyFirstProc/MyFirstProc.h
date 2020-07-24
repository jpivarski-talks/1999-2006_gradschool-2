// -*- C++ -*-
#if !defined(MYFIRSTPROC_MYFIRSTPROC_H)
#define MYFIRSTPROC_MYFIRSTPROC_H
//
// Package:     <MyFirstProc>
// Module:      MyFirstProc
//
/**\class MyFirstProc MyFirstProc.h MyFirstProc/MyFirstProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jun  7 10:22:18 EDT 2005
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

class MyFirstProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MyFirstProc( void );                      // anal1 
      virtual ~MyFirstProc();                   // anal5 

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
      MyFirstProc( const MyFirstProc& );

      // ------------ assignment operator(s) ---------------------
      const MyFirstProc& operator=( const MyFirstProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MyFirstProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HIHist1D*  m_histo1;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MYFIRSTPROC_MYFIRSTPROC_H */
