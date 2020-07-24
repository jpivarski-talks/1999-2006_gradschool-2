// -*- C++ -*-
#if !defined(LCPROC_LCPROC_H)
#define LCPROC_LCPROC_H
//
// Package:     <LCProc>
// Module:      LCProc
//
/**\class LCProc LCProc.h LCProc/LCProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Mon Apr 19 15:53:45 EDT 2004
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

class LCProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LCProc( void );                      // anal1 
      virtual ~LCProc();                   // anal5 

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
      LCProc( const LCProc& );

      // ------------ assignment operator(s) ---------------------
      const LCProc& operator=( const LCProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LCProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HIHist1D* m_trackMom;
      HIHist1D* m_totalTrackMom;
      HIHist1D* m_trackEnergy;
      HIHist1D* m_totalTrackEnergy;
      HIHist1D* m_clusterEnergy;
      HIHist1D* m_totalClusterEnergy;
      HIHist1D* m_missEnergy;
      HIHist1D* m_totalLeptonEnergy;
      HIHist1D* m_leptonEnergy;
      HIHist1D* m_leptonEnergy2lEvt;

      HIHist1D* m_nJets;
      HIHist1D* m_JetP;
      HIHist1D* m_JetP2JEvts;
      HIHist1D* m_JetPhi;
      HIHist1D* m_JetCosTh;
      HINtuple* m_2lntuple;
      HINtuple* m_tjntuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LCPROC_LCPROC_H */
