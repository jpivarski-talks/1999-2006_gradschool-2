// -*- C++ -*-
#if !defined(CLEAN_CLEAN_H)
#define CLEAN_CLEAN_H
//
// Package:     <Clean>
// Module:      Clean
//
/**\class Clean Clean.h Clean/Clean.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Thu Mar  3 14:17:35 EST 2005
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
#include "HistogramInterface/HINtuple.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class Clean : public Processor
{
      // ------------ friend classes and functions --------------
      
   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_ismode,
	 k_minsep,
	 k_mspx,
	 k_mspy,
	 k_mspz,
	 k_mse,
	 k_msdist,
	 k_hade,
	 k_eme,
	 k_te,
	 k_tpx,
	 k_tpy,
	 k_tpz,
	 k_cpx,
	 k_cpy,
	 k_cpz,
	 k_c2px,
	 k_c2py,
	 k_c2pz,
	 k_c5px,
	 k_c5py,
	 k_c5pz,
	 k_c10px,
	 k_c10py,
	 k_c10pz,
	 k_banda,
	 k_bandb,
	 k_bandc,
	 k_bandd,
	 k_bande,
	 k_tracks,
	 k_scale,
	 k_le,
	 k_lpx,
	 k_lpy,
	 k_lpz,
	 k_we,
	 k_wpx,
	 k_wpy,
	 k_wpz,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Clean( void );                      // anal1 
      virtual ~Clean();                   // anal5 

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
      Clean( const Clean& );

      // ------------ assignment operator(s) ---------------------
      const Clean& operator=( const Clean& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Clean::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_mcfile;
      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CLEAN_CLEAN_H */
