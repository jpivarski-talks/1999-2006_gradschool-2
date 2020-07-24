// -*- C++ -*-
#if !defined(MYSECONDPROC_MYSECONDPROC_H)
#define MYSECONDPROC_MYSECONDPROC_H
//
// Package:     <MySecondProc>
// Module:      MySecondProc
//
/**\class MySecondProc MySecondProc.h MySecondProc/MySecondProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  6 18:44:25 EDT 2005
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

class MySecondProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MySecondProc( void );                      // anal1 
      virtual ~MySecondProc();                   // anal5 

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
      MySecondProc( const MySecondProc& );

      // ------------ assignment operator(s) ---------------------
      const MySecondProc& operator=( const MySecondProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MySecondProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HIHist1D* m_momentum;
      HIHist1D* m_costheta;
      HIHist1D* m_phi;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MYSECONDPROC_MYSECONDPROC_H */
