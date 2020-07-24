// -*- C++ -*-
#if !defined(TRACSKCOLLECTOR_TRACSKCOLLECTOR_H)
#define TRACSKCOLLECTOR_TRACSKCOLLECTOR_H
//
// Package:     <TracskCollector>
// Module:      TracskCollector
//
/**\class TracskCollector TracskCollector.h TracskCollector/TracskCollector.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Nov 13 17:16:52 EST 2003
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

class TracskCollector : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TracskCollector( void );                      // anal1 
      virtual ~TracskCollector();                   // anal5 

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
      TracskCollector( const TracskCollector& );

      // ------------ assignment operator(s) ---------------------
      const TracskCollector& operator=( const TracskCollector& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TracskCollector::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_checkBunch;
      Parameter<DABoolean> m_checkMIP;
      Parameter<DABoolean> m_checkSecondBiggest;
      Parameter<DABoolean> m_checkColinearity;
      Parameter<DABoolean> m_checkNumShowers;
      Parameter<DABoolean> m_checkShowerMomentum;
      Parameter<DABoolean> m_checkMatchedShowers;
      Parameter<DABoolean> m_checkOppositeCurvature;
      Parameter<DABoolean> m_checkFitAbort;
      Parameter<DABoolean> m_checkMomentumLow;
      Parameter<DABoolean> m_checkMomentumHigh;
      Parameter<DABoolean> m_checkD0;
      Parameter<DABoolean> m_checkD0Miss;
      Parameter<DABoolean> m_checkZ0;
      Parameter<DABoolean> m_checkWeightedMiss;
      Parameter<DABoolean> m_checkPPerp;
      Parameter<DABoolean> m_checkPZ;

      HIHist1D* m_bunchmargin;
      HIHist1D* m_nextbig_shower;
      HIHist1D* m_colinearity;
      HIHist1D* m_bhabha_showers;
      HIHist1D* m_showers_momentum;
      HIHist1D* m_ntracks;
      HIHist1D* m_curvature_sign;
      HIHist1D* m_fitted;
      HIHist1D* m_momentum;
      HIHist1D* m_d0;
      HIHist1D* m_d0miss;
      HIHist1D* m_z0;
      HIHist1D* m_weighted_d0;
      HIHist1D* m_weighted_z0;
      HIHist1D* m_pmag;
      HIHist1D* m_pperp;
      HIHist1D* m_pz;

      HIHist1D* m_bunchmargin_after;
      HIHist1D* m_nextbig_shower_after;
      HIHist1D* m_colinearity_after;
      HIHist1D* m_bhabha_showers_after;
      HIHist1D* m_showers_momentum_after;
      HIHist1D* m_ntracks_after;
      HIHist1D* m_curvature_sign_after;
      HIHist1D* m_fitted_after;
      HIHist1D* m_momentum_after;
      HIHist1D* m_d0_after;
      HIHist1D* m_d0miss_after;
      HIHist1D* m_z0_after;
      HIHist1D* m_weighted_d0_after;
      HIHist1D* m_weighted_z0_after;
      HIHist1D* m_pmag_after;
      HIHist1D* m_pperp_after;
      HIHist1D* m_pz_after;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRACSKCOLLECTOR_TRACSKCOLLECTOR_H */
