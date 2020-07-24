// -*- C++ -*-
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDTrackShowerMatchingProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed May  5 11:17:21 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LCDTrackShowerMatchingProd/LCDTrackShowerMatchingProd.h"
#include "LCDTrackShowerMatchingProd/LCDMatchedProxy.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "LCDTrackShowerMatchingProd.LCDTrackShowerMatchingProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDTrackShowerMatchingProd::LCDTrackShowerMatchingProd( void )               // anal1
   : Producer( "LCDTrackShowerMatchingProd" )
   , m_EMmatchingDistanceCmCut("EMmatchingDistanceCmCut", this, 0.10)
   , m_EMmatchingErrorCmCut("EMmatchingErrorCmCut", this, 0.10)
   , m_EMmatchingDistanceSigmasCut("EMmatchingDistanceSigmasCut", this, 5.0)
   , m_HADmatchingDistanceCmCut("HADmatchingDistanceCmCut", this, 0.10)
   , m_HADmatchingErrorCmCut("HADmatchingErrorCmCut", this, 0.10)
   , m_HADmatchingDistanceSigmasCut("HADmatchingDistanceSigmasCut", this, 5.0)
   , m_EMisolatedDistanceCmCut("EMisolatedDistanceCmCut", this, 0.10)
   , m_EMisolatedErrorCmCut("EMisolatedErrorCmCut", this, 0.10)
   , m_EMisolatedDistanceSigmasCut("EMisolatedDistanceSigmasCut", this, 5.0)
   , m_HADisolatedDistanceCmCut("HADisolatedDistanceCmCut", this, 0.10)
   , m_HADisolatedErrorCmCut("HADisolatedErrorCmCut", this, 0.10)
   , m_HADisolatedDistanceSigmasCut("HADisolatedDistanceSigmasCut", this, 5.0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ----- register proxy factories ------------------
   // (Please see the "ProxyExample" library for examples!)
   //
   // Two steps: 1) use "registerProxyFactory" to register
   //            2) instantiate ProxyFactory/Function
   //               (if you're using the standard templated factories;
   //                you may of course roll your own!)

   // Proxy Registration Step 1:
   // either
   //    register default-ctor proxy
#if 0
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MyProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
#endif
   // or
   //    register non-default-ctor proxy 
   //       (don't forget to write "LCDTrackShowerMatchingProd::makeMyProxy()")

   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< LCDTrackShowerMatchingProd, LCDMatchedProxy >( *this, 
						     &LCDTrackShowerMatchingProd::makeMyProxy ),
      UsageTag() );    // or UsageTag( "MyUsage" )

}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#if 0
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< MyProxy >;
#endif
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< LCDTrackShowerMatchingProd, LCDMatchedProxy >;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)
ProxyBase*
LCDTrackShowerMatchingProd::makeMyProxy()
{ 
   return new LCDMatchedProxy(
      m_EMmatchingDistanceCmCut.value(),
      m_EMmatchingErrorCmCut.value(),
      m_EMmatchingDistanceSigmasCut.value(),
      m_HADmatchingDistanceCmCut.value(),
      m_HADmatchingErrorCmCut.value(),
      m_HADmatchingDistanceSigmasCut.value());
}

// LCDTrackShowerMatchingProd::LCDTrackShowerMatchingProd( const LCDTrackShowerMatchingProd& iLCDTrackShowerMatchingProd )
// {
//    *this = iLCDTrackShowerMatchingProd;
// }

LCDTrackShowerMatchingProd::~LCDTrackShowerMatchingProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const LCDTrackShowerMatchingProd& LCDTrackShowerMatchingProd::operator=( const LCDTrackShowerMatchingProd& iLCDTrackShowerMatchingProd )
// {
//   if( this != &iLCDTrackShowerMatchingProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iLCDTrackShowerMatchingProd );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
LCDTrackShowerMatchingProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LCDTrackShowerMatchingProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
LCDTrackShowerMatchingProd::hist_book( HIHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
