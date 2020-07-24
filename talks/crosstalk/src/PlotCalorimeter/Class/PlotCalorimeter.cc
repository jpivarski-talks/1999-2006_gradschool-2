// -*- C++ -*-
//
// Package:     PlotCalorimeter
// Module:      PlotCalorimeter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Jun 12 13:26:38 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PlotCalorimeter/PlotCalorimeter.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavTkShMatch.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.PlotCalorimeter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PlotCalorimeter::PlotCalorimeter( void )               // anal1
   : Processor( "PlotCalorimeter" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PlotCalorimeter::event,    Stream::kEvent );
   //bind( &PlotCalorimeter::beginRun, Stream::kBeginRun );
   //bind( &PlotCalorimeter::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PlotCalorimeter::~PlotCalorimeter()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
PlotCalorimeter::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PlotCalorimeter::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
PlotCalorimeter::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_eOverP = iHistoManager.histogram(100, "(Calorimeter E)/(Track P) for 2-Track Events",
				      120, 0., 1.2);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PlotCalorimeter::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );
   if ( trackTable.size() != 2 ) return ActionBase::kFailed;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();
   for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
        showerItr != showerEnd ; ++showerItr ) {
      FATable<NavTkShMatch> matches(showerItr->trackMatches());
      FATable<NavTkShMatch>::const_iterator match_end = matches.end();
      for (FATable<NavTkShMatch>::const_iterator match_iter = matches.begin();
	   match_iter != match_end;
	   ++match_iter) {
	 m_eOverP->fill(match_iter->eOverP());
      }


   }



   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
PlotCalorimeter::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
PlotCalorimeter::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
