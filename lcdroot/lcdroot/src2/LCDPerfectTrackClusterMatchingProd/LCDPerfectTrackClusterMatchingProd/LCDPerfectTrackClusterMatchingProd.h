// -*- C++ -*-
#if !defined(LCDPERFECTTRACKCLUSTERMATCHINGPROD_LCDPERFECTTRACKCLUSTERMATCHINGPROD_H)
#define LCDPERFECTTRACKCLUSTERMATCHINGPROD_LCDPERFECTTRACKCLUSTERMATCHINGPROD_H
//
// Package:     <LCDPerfectTrackClusterMatchingProd>
// Module:      LCDPerfectTrackClusterMatchingProd
//
/**\class LCDPerfectTrackClusterMatchingProd LCDPerfectTrackClusterMatchingProd.h LCDPerfectTrackClusterMatchingProd/LCDPerfectTrackClusterMatchingProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed Jun 16 11:48:32 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class LCDPerfectTrackClusterMatchingProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      LCDPerfectTrackClusterMatchingProd( void );                      // anal1 
      virtual ~LCDPerfectTrackClusterMatchingProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      LCDPerfectTrackClusterMatchingProd( const LCDPerfectTrackClusterMatchingProd& );

      // ------------ assignment operator(s) ----------------------
      const LCDPerfectTrackClusterMatchingProd& operator=( const LCDPerfectTrackClusterMatchingProd& );

      // ------------ private member functions --------------------

      ProxyBase* makeLCDPerfectMatchTrackProxy();
      ProxyBase* makeLCDPerfectIsolateClusterProxy();

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* LCDPERFECTTRACKCLUSTERMATCHINGPROD_LCDPERFECTTRACKCLUSTERMATCHINGPROD_H */
