// -*- C++ -*-
#if !defined(ZDHITSTUDY_ZDHITSTUDY_H)
#define ZDHITSTUDY_ZDHITSTUDY_H
//
// Package:     <ZDHitStudy>
// Module:      ZDHitStudy
//
/**\class ZDHitStudy ZDHitStudy.h ZDHitStudy/ZDHitStudy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Nov 21 16:09:43 EST 2003
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

class ZDHitStudy : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

//       enum {
// 	 kPPerp,
// 	 kPZ,
// 	 kCurv,
// 	 kPhi0,
// 	 kD0,
// 	 kCotTheta,
// 	 kZ0,
// 	 kLayer,
// 	 kWire,
// 	 kRefX,
// 	 kRefY,
// 	 kRefZ,
// 	 kHelixPhi,
// 	 kHelixZ,
// 	 kWireX,
// 	 kWireY,
// 	 kWireZ,
// 	 kDCA,
// 	 kDrift,
// 	 kDualChi2,

// 	 kNumEntries
//       };

      enum {
	 kChi2,
	 
	 kD0,
	 kZ0,
	 kPX,
	 kPY,
	 kPZ,

	 kED0,
	 kEZ0,
	 kEPX,
	 kEPY,
	 kEPZ,

	 kAD0,
	 kAZ0,
	 kAPX,
	 kAPY,
	 kAPZ,

	 kNumEventEntries
      };

      // ------------ Constructors and destructor ----------------
      ZDHitStudy( void );                      // anal1 
      virtual ~ZDHitStudy();                   // anal5 

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
      ZDHitStudy( const ZDHitStudy& );

      // ------------ assignment operator(s) ---------------------
      const ZDHitStudy& operator=( const ZDHitStudy& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ZDHitStudy::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_correctD0;

      HINtuple*   m_ntuple;
      HINtuple*   m_eventntuple;
      HIHistProf* m_00;
      HIHistProf* m_01;
      HIHistProf* m_02;
      HIHistProf* m_03;
      HIHistProf* m_04;
      HIHistProf* m_05;
      HIHistProf* m_06;
      HIHistProf* m_07;
      HIHistProf* m_08;
      HIHistProf* m_09;
      HIHistProf* m_10;
      HIHistProf* m_11;
      HIHistProf* m_12;
      HIHistProf* m_13;
      HIHistProf* m_14;
      HIHistProf* m_15;
      HIHistProf* m_16;
      HIHistProf* m_17;
      HIHistProf* m_18;
      HIHistProf* m_19;
      HIHist1D*   m_ct_00;
      HIHist1D*   m_ct_01;
      HIHist1D*   m_ct_02;
      HIHist1D*   m_ct_03;
      HIHist1D*   m_ct_04;
      HIHist1D*   m_ct_05;
      HIHist1D*   m_ct_06;
      HIHist1D*   m_ct_07;
      HIHist1D*   m_ct_08;
      HIHist1D*   m_ct_09;
      HIHist1D*   m_ct_10;
      HIHist1D*   m_ct_11;
      HIHist1D*   m_ct_12;
      HIHist1D*   m_ct_13;
      HIHist1D*   m_ct_14;
      HIHist1D*   m_ct_15;
      HIHist1D*   m_ct_16;
      HIHist1D*   m_ct_17;
      HIHist1D*   m_ct_18;
      HIHist1D*   m_ct_19;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ZDHITSTUDY_ZDHITSTUDY_H */
