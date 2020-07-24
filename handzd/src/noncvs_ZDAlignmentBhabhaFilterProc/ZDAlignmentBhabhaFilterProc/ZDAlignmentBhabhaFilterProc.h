// -*- C++ -*-
#if !defined(ZDALIGNMENTBHABHAFILTERPROC_ZDALIGNMENTBHABHAFILTERPROC_H)
#define ZDALIGNMENTBHABHAFILTERPROC_ZDALIGNMENTBHABHAFILTERPROC_H
//
// Package:     <ZDAlignmentBhabhaFilterProc>
// Module:      ZDAlignmentBhabhaFilterProc
//
/**\class ZDAlignmentBhabhaFilterProc ZDAlignmentBhabhaFilterProc.h ZDAlignmentBhabhaFilterProc/ZDAlignmentBhabhaFilterProc.h
 
 Description: Selects bhabha events for ZDAlignmentMod

 Usage:
    see Test/sample.tcl

*/
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 12:08:40 EST 2003
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

class ZDAlignmentBhabhaFilterProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ZDAlignmentBhabhaFilterProc( void );                      // anal1 
      virtual ~ZDAlignmentBhabhaFilterProc();                   // anal5 

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
      ZDAlignmentBhabhaFilterProc( const ZDAlignmentBhabhaFilterProc& );

      // ------------ assignment operator(s) ---------------------
      const ZDAlignmentBhabhaFilterProc& operator=( const ZDAlignmentBhabhaFilterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ZDAlignmentBhabhaFilterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_crossingangle_x;
      Parameter<double> m_crossingangle_y;
      Parameter<double> m_asymmetric_beamz;

      HIHist1D* m_good_tracks;
      HIHist1D* m_bad_tracks;
      HIHist1D* m_charge;
      HIHist1D* m_d0miss;
      HIHist1D* m_z0miss;
      HIHist1D* m_tracks_momentum_phi;
      HIHist1D* m_tracks_momentum_perp;
      HIHist1D* m_tracks_momentum_z;

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

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ZDALIGNMENTBHABHAFILTERPROC_ZDALIGNMENTBHABHAFILTERPROC_H */
