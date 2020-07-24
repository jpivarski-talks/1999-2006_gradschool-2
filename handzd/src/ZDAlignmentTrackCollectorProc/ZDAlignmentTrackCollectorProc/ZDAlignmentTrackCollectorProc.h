// -*- C++ -*-
#if !defined(ZDALIGNMENTTRACKCOLLECTORPROC_ZDALIGNMENTTRACKCOLLECTORPROC_H)
#define ZDALIGNMENTTRACKCOLLECTORPROC_ZDALIGNMENTTRACKCOLLECTORPROC_H
//
// Package:     <ZDAlignmentTrackCollectorProc>
// Module:      ZDAlignmentTrackCollectorProc
//
/**\class ZDAlignmentTrackCollectorProc ZDAlignmentTrackCollectorProc.h ZDAlignmentTrackCollectorProc/ZDAlignmentTrackCollectorProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:41:29 EST 2003
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

class ZDAlignmentTrackCollectorProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ZDAlignmentTrackCollectorProc( void );                      // anal1 
      virtual ~ZDAlignmentTrackCollectorProc();                   // anal5 

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
      ZDAlignmentTrackCollectorProc( const ZDAlignmentTrackCollectorProc& );

      // ------------ assignment operator(s) ---------------------
      const ZDAlignmentTrackCollectorProc& operator=( const ZDAlignmentTrackCollectorProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ZDAlignmentTrackCollectorProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_bunchmargin;
      HIHist1D* m_nextbig_shower;
      HIHist1D* m_colinearity;
      HIHist1D* m_ntracks;
      HIHist1D* m_curvature_sign;
      HIHist1D* m_fitted;
      HIHist1D* m_momentum;
      HIHist1D* m_d0;
      HIHist1D* m_d0miss;
      HIHist1D* m_z0;
      HIHist1D* m_pmag;
      HIHist1D* m_pperp;
      HIHist1D* m_pz;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ZDALIGNMENTTRACKCOLLECTORPROC_ZDALIGNMENTTRACKCOLLECTORPROC_H */
