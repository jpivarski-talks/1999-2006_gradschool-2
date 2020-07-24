// -*- C++ -*-
#if !defined(LCDEXAMPLEPROC_LCDEXAMPLEPROC_H)
#define LCDEXAMPLEPROC_LCDEXAMPLEPROC_H
//
// Package:     <LCDExampleProc>
// Module:      LCDExampleProc
//
/**\class LCDExampleProc LCDExampleProc.h LCDExampleProc/LCDExampleProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Fri Apr 16 19:44:18 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"
#include "HistogramInterface/HINtuple.h"

// forward declarations

class LCDExampleProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

//       enum {
// 	 kD0,
// 	 kPhi0,
// 	 kOmega,
// 	 kZ0,
// 	 kTanL,
// 	 kMomentum,
// 	 kPPerp,
// 	 kChi2,
// 	 kDof,
// 	 kNumTrackEntries
//       };

//       enum {
// 	 kDist,
// 	 kE,
// 	 kP,
// 	 kTCSystem,
// 	 kTCBarEnd,
// 	 kNumTrackClusterEntries
//       };

//       enum {
// 	 kEnergy,
// 	 kR,
// 	 kPhi,
// 	 kTheta,
// 	 kSystem,
// 	 kBarEnd,
// 	 kNumClusterEntries
//       };

//       enum {
// 	 kPartSM,
// 	 kPartSUSY,
// 	 kPxSM,
// 	 kPySM,
// 	 kPzSM,
// 	 kPxSUSY,
// 	 kPySUSY,
// 	 kPzSUSY,
// 	 kESM,
// 	 kESUSY,
// 	 kNumEventEntries
//       };

      enum {
// 	 k_j1E,
// 	 k_j1px,
// 	 k_j1py,
// 	 k_j1pz,
// 	 k_j2E,
// 	 k_j2px,
// 	 k_j2py,
// 	 k_j2pz,
// 	 k_llE,
// 	 k_llpx,
// 	 k_llpy,
// 	 k_llpz,
// //	 k_survive,
// 	 k_chipE,
// 	 k_chippx,
// 	 k_chippy,
// 	 k_chippz,
// 	 k_chimE,
// 	 k_chimpx,
// 	 k_chimpy,
// 	 k_chimpz,
// // 	 k_wpE,
// // 	 k_wppx,
// // 	 k_wppy,
// // 	 k_wppz,
// // 	 k_wmE,
// // 	 k_wmpx,
// // 	 k_wmpy,
// // 	 k_wmpz,
// 	 k_jj1e,
// 	 k_jj1px,
// 	 k_jj1py,
// 	 k_jj1pz,
// 	 k_jj2e,
// 	 k_jj2px,
// 	 k_jj2py,
// 	 k_jj2pz,
// 	 k_gluee,
// 	 k_gluepx,
// 	 k_gluepy,
// 	 k_gluepz,

	 k_eve,
	 k_evpx,
	 k_evpy,
	 k_evpz,
	 k_isoe,
	 k_isopx,
	 k_isopy,
	 k_isopz,
	 k_scale,
	 k_jets,
	 k_glue,
	 k_mcfile,
	 k_ct,
	 k_jct,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      LCDExampleProc( void );                      // anal1 
      virtual ~LCDExampleProc();                   // anal5 

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
      LCDExampleProc( const LCDExampleProc& );

      // ------------ assignment operator(s) ---------------------
      const LCDExampleProc& operator=( const LCDExampleProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LCDExampleProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_mcfile;

//       HINtuple* m_tracks;
//       HINtuple* m_trackclusters;
//       HINtuple* m_clusters;
//       HINtuple* m_events;
      HINtuple* m_ntuple;

      int m_all_events;
      int m_only_winners;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LCDEXAMPLEPROC_LCDEXAMPLEPROC_H */
