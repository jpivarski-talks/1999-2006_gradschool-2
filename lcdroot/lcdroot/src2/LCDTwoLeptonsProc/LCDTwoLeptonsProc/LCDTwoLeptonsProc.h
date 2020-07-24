// -*- C++ -*-
#if !defined(LCDTWOLEPTONSPROC_LCDTWOLEPTONSPROC_H)
#define LCDTWOLEPTONSPROC_LCDTWOLEPTONSPROC_H
//
// Package:     <LCDTwoLeptonsProc>
// Module:      LCDTwoLeptonsProc
//
/**\class LCDTwoLeptonsProc LCDTwoLeptonsProc.h LCDTwoLeptonsProc/LCDTwoLeptonsProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed Jun 16 13:52:46 EDT 2004
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

class LCDTwoLeptonsProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LCDTwoLeptonsProc( void );                      // anal1 
      virtual ~LCDTwoLeptonsProc();                   // anal5 

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
      LCDTwoLeptonsProc( const LCDTwoLeptonsProc& );

      // ------------ assignment operator(s) ---------------------
      const LCDTwoLeptonsProc& operator=( const LCDTwoLeptonsProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LCDTwoLeptonsProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_dist;
      HIHist1D* m_dist50;
      HIHist1D* m_dist100;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LCDTWOLEPTONSPROC_LCDTWOLEPTONSPROC_H */
