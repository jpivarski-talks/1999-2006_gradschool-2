// -*- C++ -*-
//
// Package:     MyThirdProc
// Module:      MyThirdProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun  6 18:44:31 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MyThirdProc/MyThirdProc.h"
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

#include "HistogramInterface/HIHist1D.h"
#include "CleoDB/DBEventHeader.h"

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
static const char* const kFacilityString = "Processor.MyThirdProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.40 2005/02/10 16:03:57 chengp Exp $";
static const char* const kTagString = "$Name: v07_02_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
MyThirdProc::MyThirdProc( void )               // anal1
   : Processor( "MyThirdProc" )
   , m_wantCosmics("wantCosmics", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &MyThirdProc::event,    Stream::kEvent );
   //bind( &MyThirdProc::beginRun, Stream::kBeginRun );
   //bind( &MyThirdProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

MyThirdProc::~MyThirdProc()                    // anal5
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
MyThirdProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MyThirdProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
MyThirdProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
MyThirdProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   // Initialize the closest track to a nothing (end of the list is "nothingness")
   FATable< NavTrack >::const_iterator closestTrack = trackTable.end();

   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackTable.begin();
         trackItr != trackTable.end();
         ++trackItr )
   {
      if (closestTrack == trackTable.end()  ||
	  fabs(closestTrack->pionHelix()->d0()) >
	  fabs(trackItr->pionHelix()->d0()))
      {
	 closestTrack = trackItr;
      }
   }

   // Return value depends on where the closest track is
   if (closestTrack == trackTable.end())
   {
      return ActionBase::kFailed;
   }

   if (m_wantCosmics.value())
   {
      if (fabs(closestTrack->pionHelix()->d0()) > 0.008) // that's 8 mm
      {
	 return ActionBase::kPassed;
      }
      else
      {
	 return ActionBase::kFailed;
      }
   }
   else // we DON'T want cosmics
   {
      if (fabs(closestTrack->pionHelix()->d0()) < 0.003) // that's 3 mm
      {
	 return ActionBase::kPassed;
      }
      else
      {
	 return ActionBase::kFailed;
      }
   }
}

/*
ActionBase::ActionResult
MyThirdProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
MyThirdProc::endRun( Frame& iFrame )         // anal4 equiv.
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
