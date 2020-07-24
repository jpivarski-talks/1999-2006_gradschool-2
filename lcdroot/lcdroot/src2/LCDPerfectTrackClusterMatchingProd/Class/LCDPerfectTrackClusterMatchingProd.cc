// -*- C++ -*-
//
// Package:     <LCDPerfectTrackClusterMatchingProd>
// Module:      LCDPerfectTrackClusterMatchingProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed Jun 16 11:48:32 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LCDPerfectTrackClusterMatchingProd/LCDPerfectTrackClusterMatchingProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

#include "LCDPerfectTrackClusterMatchingProd/LCDPerfectMatchTrackProxy.h"
#include "LCDPerfectTrackClusterMatchingProd/LCDPerfectIsolateClusterProxy.h"

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
static const char* const kFacilityString = "LCDPerfectTrackClusterMatchingProd.LCDPerfectTrackClusterMatchingProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDPerfectTrackClusterMatchingProd::LCDPerfectTrackClusterMatchingProd( void )               // anal1
   : Producer( "LCDPerfectTrackClusterMatchingProd" )
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
   //       (don't forget to write "LCDPerfectTrackClusterMatchingProd::makeMyProxy()")

   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< LCDPerfectTrackClusterMatchingProd, LCDPerfectMatchTrackProxy >( *this, 
	  &LCDPerfectTrackClusterMatchingProd::makeLCDPerfectMatchTrackProxy ),
      UsageTag() );    // or UsageTag( "MyUsage" )

   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< LCDPerfectTrackClusterMatchingProd, LCDPerfectIsolateClusterProxy >( *this, 
	  &LCDPerfectTrackClusterMatchingProd::makeLCDPerfectIsolateClusterProxy ),
      UsageTag() );    // or UsageTag( "MyUsage" )

}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#if 0
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< MyProxy >;
#endif
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< LCDPerfectTrackClusterMatchingProd, LCDPerfectMatchTrackProxy >;
template class ProxyFactoryFunction< LCDPerfectTrackClusterMatchingProd, LCDPerfectIsolateClusterProxy >;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)

ProxyBase*
LCDPerfectTrackClusterMatchingProd::makeLCDPerfectMatchTrackProxy()
{ 
   return new LCDPerfectMatchTrackProxy();
}

ProxyBase*
LCDPerfectTrackClusterMatchingProd::makeLCDPerfectIsolateClusterProxy()
{ 
   return new LCDPerfectIsolateClusterProxy();
}


// LCDPerfectTrackClusterMatchingProd::LCDPerfectTrackClusterMatchingProd( const LCDPerfectTrackClusterMatchingProd& iLCDPerfectTrackClusterMatchingProd )
// {
//    *this = iLCDPerfectTrackClusterMatchingProd;
// }

LCDPerfectTrackClusterMatchingProd::~LCDPerfectTrackClusterMatchingProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const LCDPerfectTrackClusterMatchingProd& LCDPerfectTrackClusterMatchingProd::operator=( const LCDPerfectTrackClusterMatchingProd& iLCDPerfectTrackClusterMatchingProd )
// {
//   if( this != &iLCDPerfectTrackClusterMatchingProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iLCDPerfectTrackClusterMatchingProd );
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
LCDPerfectTrackClusterMatchingProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LCDPerfectTrackClusterMatchingProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
LCDPerfectTrackClusterMatchingProd::hist_book( HIHistoManager& )
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
