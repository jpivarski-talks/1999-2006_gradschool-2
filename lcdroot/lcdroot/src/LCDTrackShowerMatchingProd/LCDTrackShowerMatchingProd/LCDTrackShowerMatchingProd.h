// -*- C++ -*-
#if !defined(LCDTRACKSHOWERMATCHINGPROD_LCDTRACKSHOWERMATCHINGPROD_H)
#define LCDTRACKSHOWERMATCHINGPROD_LCDTRACKSHOWERMATCHINGPROD_H
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDTrackShowerMatchingProd
//
/**\class LCDTrackShowerMatchingProd LCDTrackShowerMatchingProd.h LCDTrackShowerMatchingProd/LCDTrackShowerMatchingProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed May  5 11:17:21 EDT 2004
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

class LCDTrackShowerMatchingProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      LCDTrackShowerMatchingProd( void );                      // anal1 
      virtual ~LCDTrackShowerMatchingProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      ProxyBase* makeMyProxy();

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      LCDTrackShowerMatchingProd( const LCDTrackShowerMatchingProd& );

      // ------------ assignment operator(s) ----------------------
      const LCDTrackShowerMatchingProd& operator=( const LCDTrackShowerMatchingProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      Parameter<double> m_EMmatchingDistanceCmCut;
      Parameter<double> m_EMmatchingErrorCmCut;
      Parameter<double> m_EMmatchingDistanceSigmasCut;

      Parameter<double> m_HADmatchingDistanceCmCut;
      Parameter<double> m_HADmatchingErrorCmCut;
      Parameter<double> m_HADmatchingDistanceSigmasCut;

      Parameter<double> m_EMisolatedDistanceCmCut;
      Parameter<double> m_EMisolatedErrorCmCut;
      Parameter<double> m_EMisolatedDistanceSigmasCut;

      Parameter<double> m_HADisolatedDistanceCmCut;
      Parameter<double> m_HADisolatedErrorCmCut;
      Parameter<double> m_HADisolatedDistanceSigmasCut;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* LCDTRACKSHOWERMATCHINGPROD_LCDTRACKSHOWERMATCHINGPROD_H */
