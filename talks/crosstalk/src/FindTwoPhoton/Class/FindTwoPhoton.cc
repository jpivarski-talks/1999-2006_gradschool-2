// -*- C++ -*-
//
// Package:     FindTwoPhoton
// Module:      FindTwoPhoton
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun 16 21:55:05 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FindTwoPhoton/FindTwoPhoton.h"
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
static const char* const kFacilityString = "Processor.FindTwoPhoton" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FindTwoPhoton::FindTwoPhoton( void )               // anal1
   : Processor( "FindTwoPhoton" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FindTwoPhoton::event,    Stream::kEvent );
   //bind( &FindTwoPhoton::beginRun, Stream::kBeginRun );
   //bind( &FindTwoPhoton::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FindTwoPhoton::~FindTwoPhoton()                    // anal5
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
FindTwoPhoton::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FindTwoPhoton::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FindTwoPhoton::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FindTwoPhoton::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   double total_energy(0.);
   Hep3Vector total_momentum(0.,0.,0.);

   int num_showers(0);
   double biggest_shower(0.);

   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;
	++shower_iter) {
      if (!shower_iter->attributes().hot()  &&
	  shower_iter->attributes().energy() > 0.010  &&
	  shower_iter->noTrackMatch()  &&
	  shower_iter->noTrackMatchConReg()  &&
	  (!shower_iter->bremTrack().valid()  ||
	   (shower_iter->bremTrack()->trackShowerMatch().valid()  &&
	    shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5))) {
	 total_energy += shower_iter->attributes().energy();
	 total_momentum += shower_iter->attributes().momentum();

	 num_showers++;
	 if (shower_iter->attributes().energy() > biggest_shower) {
	    biggest_shower = shower_iter->attributes().energy();
	 }

      }
   }
   if (num_showers == 2) return ActionBase::kFailed;
   if (biggest_shower > 4.) return ActionBase::kFailed;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks, "TrkmanApproved");
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   int num_tracks(0);
   int num_anytracks(0);
   int event_charge(0);
   double biggest_track(0.);

   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;
	++track_iter) {
      if (track_iter->pionQuality()->fit()  &&
	  !track_iter->pionQuality()->fitAbort() ) {
	 report(INFO, kFacilityString) << "TkmanApproved: " << track_iter->identifier() << endl;

	 num_tracks++;
	 event_charge += (track_iter->pionHelix()->curvature() > 0. ? 1 : -1);
	 total_energy += track_iter->pionFit()->energy();
	 total_momentum += track_iter->pionFit()->momentum();
	 
	 if (track_iter->pionFit()->momentum().mag() > biggest_track) {
	    biggest_track = track_iter->pionFit()->momentum().mag();
	 }
      }
   }

   FATable<NavTrack> anytracks;
   extract(iFrame.record(Stream::kEvent), anytracks);
   tracks_end = anytracks.end();
   for (FATable<NavTrack>::const_iterator any_iter = anytracks.begin();
	any_iter != tracks_end;
	++any_iter) {
      num_anytracks++;
   }
   if (num_anytracks == 2) return ActionBase::kFailed;

   if (num_anytracks == 0  ||  num_tracks == 0) return ActionBase::kFailed;

   report(INFO, kFacilityString) << "event_charge " << event_charge
				 << " total_energy " << total_energy
				 << " total_momentum " << total_momentum
				 << " biggest_shower " << biggest_shower
				 << " biggest_track " << biggest_track << endl;

   if (num_tracks == 2) return ActionBase::kFailed;
   if (event_charge != 0) return ActionBase::kFailed;
   if (total_energy > 6.) return ActionBase::kFailed;
   if (total_momentum.perp() > 0.6) return ActionBase::kFailed;
   if (biggest_track > 4.) return ActionBase::kFailed;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
FindTwoPhoton::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FindTwoPhoton::endRun( Frame& iFrame )         // anal4 equiv.
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
