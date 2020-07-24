// -*- C++ -*-
#if !defined(MYFOURTHPROC_MYFOURTHPROC_H)
#define MYFOURTHPROC_MYFOURTHPROC_H
//
// Package:     <MyFourthProc>
// Module:      MyFourthProc
//
/**\class MyFourthProc MyFourthProc.h MyFourthProc/MyFourthProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  6 18:44:36 EDT 2005
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

class MyFourthProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MyFourthProc( void );                      // anal1 
      virtual ~MyFourthProc();                   // anal5 

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
      MyFourthProc( const MyFourthProc& );

      // ------------ assignment operator(s) ---------------------
      const MyFourthProc& operator=( const MyFourthProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MyFourthProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist2D* m_d0vsphi;
      HIHistProf* m_d0vsphi_prof;
      HIHist1D* m_showerEnergy;
      HIHist1D* m_showerEnergy_closeup;
      HIHist1D* m_costhetaPosBhabha;
      HIHist1D* m_costhetaNegBhabha;
      HIHist1D* m_costhetaPosMupair;
      HIHist1D* m_costhetaNegMupair;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MYFOURTHPROC_MYFOURTHPROC_H */
