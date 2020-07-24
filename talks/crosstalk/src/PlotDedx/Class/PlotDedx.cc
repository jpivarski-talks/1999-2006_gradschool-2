// -*- C++ -*-
//
// Package:     PlotDedx
// Module:      PlotDedx
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Jun 12 10:27:37 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PlotDedx/PlotDedx.h"
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

//Dedx example
#include "DedxInfo/DedxInfo.h"


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
static const char* const kFacilityString = "Processor.PlotDedx" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PlotDedx::PlotDedx( void )               // anal1
   : Processor( "PlotDedx" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PlotDedx::event,    Stream::kEvent );
   //bind( &PlotDedx::beginRun, Stream::kBeginRun );
   //bind( &PlotDedx::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PlotDedx::~PlotDedx()                    // anal5
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
PlotDedx::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PlotDedx::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
PlotDedx::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "pperp", "pz", "dedx", "hitsused", "hits"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PlotDedx::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks, "TrkmanApproved");
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;
	++track_iter) {
      if ( track_iter->pionQuality()->ratioNumberHitsToExpected() > 0.7  &&
	   track_iter->pionQuality()->degreesOfFreedom() > 0  &&
	   (track_iter->pionQuality()->chiSquare() /
	    double(track_iter->pionQuality()->degreesOfFreedom())) < 5.  &&
	   track_iter->pionQuality()->fit()  &&  !track_iter->pionQuality()->fitAbort()  &&
	   fabs(track_iter->pionHelix()->d0()) < 0.05  &&
	   fabs(track_iter->pionHelix()->z0()) < 0.15  &&
	   sqrt(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)) < 0.05  &&
	   track_iter->dedxInfo().valid() ) {
	 float v[kNumEntries];  for (int i = 0;  i <= kNumEntries;  i++) v[i] = 0.;
	 v[kPPerp] = track_iter->pionFit()->momentum().perp();
	 v[kPz] = track_iter->pionFit()->momentum().z();
	 v[kDedx] = track_iter->dedxInfo()->truncatedMean();
	 v[kHitsUsed] = float(track_iter->dedxInfo()->numOfDedxHitsUsed());
	 v[kHits] = float(track_iter->dedxInfo()->numOfDedxHits());

	 m_ntuple->fill(v);
      }
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
PlotDedx::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
PlotDedx::endRun( Frame& iFrame )         // anal4 equiv.
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
