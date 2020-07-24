// -*- C++ -*-
#if !defined(PLOTCALORIMETER_PLOTCALORIMETER_H)
#define PLOTCALORIMETER_PLOTCALORIMETER_H
//
// Package:     <PlotCalorimeter>
// Module:      PlotCalorimeter
//
/**\class PlotCalorimeter PlotCalorimeter.h PlotCalorimeter/PlotCalorimeter.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Jun 12 13:26:38 EDT 2003
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

class PlotCalorimeter : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PlotCalorimeter( void );                      // anal1 
      virtual ~PlotCalorimeter();                   // anal5 

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
      PlotCalorimeter( const PlotCalorimeter& );

      // ------------ assignment operator(s) ---------------------
      const PlotCalorimeter& operator=( const PlotCalorimeter& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PlotCalorimeter::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_eOverP;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PLOTCALORIMETER_PLOTCALORIMETER_H */
