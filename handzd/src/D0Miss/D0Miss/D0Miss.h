// -*- C++ -*-
#if !defined(D0MISS_D0MISS_H)
#define D0MISS_D0MISS_H
//
// Package:     <D0Miss>
// Module:      D0Miss
//
/**\class D0Miss D0Miss.h D0Miss/D0Miss.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Dec  1 13:10:54 EST 2003
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

class D0Miss : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      D0Miss( void );                      // anal1 
      virtual ~D0Miss();                   // anal5 

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
      D0Miss( const D0Miss& );

      // ------------ assignment operator(s) ---------------------
      const D0Miss& operator=( const D0Miss& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (D0Miss::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

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

      HIHist1D*   m_chi2diff;
      HIHist1D*   m_err_cc;
      HIHist1D*   m_err_cp;
      HIHist1D*   m_err_cd;
      HIHist1D*   m_err_ct;
      HIHist1D*   m_err_cz;
      HIHist1D*   m_err_pp;
      HIHist1D*   m_err_pd;
      HIHist1D*   m_err_pt;
      HIHist1D*   m_err_pz;
      HIHist1D*   m_err_dd;
      HIHist1D*   m_err_dt;
      HIHist1D*   m_err_dz;
      HIHist1D*   m_err_tt;
      HIHist1D*   m_err_tz;
      HIHist1D*   m_err_zz;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* D0MISS_D0MISS_H */
