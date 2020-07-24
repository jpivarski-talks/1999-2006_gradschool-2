// -*- C++ -*-
#if !defined(BHABHACUTS_BHABHACUTS_H)
#define BHABHACUTS_BHABHACUTS_H
//
// Package:     <BhabhaCuts>
// Module:      BhabhaCuts
//
/**\class BhabhaCuts BhabhaCuts.h BhabhaCuts/BhabhaCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Nov 19 15:15:09 EST 2003
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

class BhabhaCuts : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      BhabhaCuts( void );                      // anal1 
      virtual ~BhabhaCuts();                   // anal5 

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
      BhabhaCuts( const BhabhaCuts& );

      // ------------ assignment operator(s) ---------------------
      const BhabhaCuts& operator=( const BhabhaCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BhabhaCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_shortCircuit;

      HIHist1D* m_pertrack_fit;
      HIHist1D* m_pertrack_reduced_chi2;
      HIHist1D* m_pertrack_hitfraction;
      HIHist1D* m_pertrack_d0;
      HIHist1D* m_pertrack_z0;
      HIHist1D* m_pertrack_p;
      HIHist1D* m_pertrack_cotTheta;
      HIHist1D* m_pertrack_err_cT;
      HIHist1D* m_pertrack_err_z0;
      HIHist1D* m_pertrack_numzdhits;

      HIHist1D* m_good_showers;
      HIHist1D* m_bad_showers;
      HIHist1D* m_showers_momentum;
      HIHist1D* m_good_tracks;
      HIHist1D* m_bad_tracks;
      HIHist1D* m_charge;
      HIHist1D* m_d0miss;
      HIHist1D* m_z0miss;
      HIHist1D* m_tracks_momentum_phi;
      HIHist1D* m_tracks_momentum_perp;
      HIHist1D* m_tracks_momentum_z;

      HIHistProf* m_chi2dof_vphi;
      HIHistProf* m_hitfrac_vphi;
      HIHistProf* m_d0_vphi;
      HIHistProf* m_z0_vphi;
      HIHistProf* m_pmag_vphi;
      HIHistProf* m_ect_vphi;
      HIHistProf* m_ez0_vphi;
      HIHistProf* m_zdhits_vphi;
      HIHistProf* m_d0miss_vphi;
      HIHistProf* m_z0miss_vphi;
      HIHistProf* m_pperp_vphi;
      HIHistProf* m_pz_vphi;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BHABHACUTS_BHABHACUTS_H */
