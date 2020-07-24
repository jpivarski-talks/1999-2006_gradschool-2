// -*- C++ -*-
#if !defined(LCDTRACKCLUSTERMATCHINGPROD_LCDTRACKCLUSTERMATCHINGPROD_H)
#define LCDTRACKCLUSTERMATCHINGPROD_LCDTRACKCLUSTERMATCHINGPROD_H
//
// Package:     <LCDTrackClusterMatchingProd>
// Module:      LCDTrackClusterMatchingProd
//
/**\class LCDTrackClusterMatchingProd LCDTrackClusterMatchingProd.h LCDTrackClusterMatchingProd/LCDTrackClusterMatchingProd.h
 
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
#include "CommandPattern/Parameter.h"

// forward declarations

class LCDTrackClusterMatchingProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      LCDTrackClusterMatchingProd( void );                      // anal1 
      virtual ~LCDTrackClusterMatchingProd();                   // anal5 

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
      LCDTrackClusterMatchingProd( const LCDTrackClusterMatchingProd& );

      // ------------ assignment operator(s) ----------------------
      const LCDTrackClusterMatchingProd& operator=( const LCDTrackClusterMatchingProd& );

      // ------------ private member functions --------------------

      ProxyBase* makeLCDMatchTrackProxy();
      ProxyBase* makeLCDIsolateClusterProxy();

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      Parameter<double> m_trackMatchDistCM;
      Parameter<double> m_clusterIsolateDistCM;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* LCDTRACKCLUSTERMATCHINGPROD_LCDTRACKCLUSTERMATCHINGPROD_H */
