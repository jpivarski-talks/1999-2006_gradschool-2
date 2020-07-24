// -*- C++ -*-
//
// Package:     FindMuPairs
// Module:      FindMuPairs
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Jun 10 14:07:03 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FindMuPairs/FindMuPairs.h"
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

#include "C3Mu/MuTrack.h"

#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"

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
static const char* const kFacilityString = "Processor.FindMuPairs" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FindMuPairs::FindMuPairs( void )               // anal1
   : Processor( "FindMuPairs" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FindMuPairs::event,    Stream::kEvent );
   //bind( &FindMuPairs::beginRun, Stream::kBeginRun );
   //bind( &FindMuPairs::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FindMuPairs::~FindMuPairs()                    // anal5
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
FindMuPairs::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FindMuPairs::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FindMuPairs::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "pcurv", "pphi0", "pd0", "pz0", "pcotTh",
      "ncurv", "nphi0", "nd0", "nz0", "ncotTh",
      "margin"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FindMuPairs::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   if (tracks.size() != 2) return ActionBase::kFailed;

   FATable<NavTrack>::const_iterator track_one = tracks.begin();
   FATable<NavTrack>::const_iterator track_two = tracks.begin();  ++track_two;

   FATable<NavTrack>::const_iterator pos, neg;
   if (track_one->pionHelix()->curvature() > 0.) {
      pos = track_one;
      neg = track_two;
   }
   else {
      neg = track_one;
      pos = track_two;
   }

   FAItem<TrackletBunchDecision> decision;
   extract(iFrame.record(Stream::kEvent), decision);

   if (decision->numberOfTestedBunches() < 1) return ActionBase::kFailed;

   double best(decision->bestBunchInfo().bweight());
   double runnerup(decision->bunchInfo(1).bweight());

   if (best <= 0.) return ActionBase::kFailed;

   float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) v[i] = 0.;
   v[kPosCurv] = pos->pionHelix()->curvature();
   v[kPosPhi0] = pos->pionHelix()->phi0();
   v[kPosD0] = pos->pionHelix()->d0();
   v[kPosZ0] = pos->pionHelix()->z0();
   v[kPosCotTheta] = pos->pionHelix()->cotTheta();
   v[kNegCurv] = neg->pionHelix()->curvature();
   v[kNegPhi0] = neg->pionHelix()->phi0();
   v[kNegD0] = neg->pionHelix()->d0();
   v[kNegZ0] = neg->pionHelix()->z0();
   v[kNegCotTheta] = neg->pionHelix()->cotTheta();
   v[kMargin] = (best-runnerup)/best;

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
FindMuPairs::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FindMuPairs::endRun( Frame& iFrame )         // anal4 equiv.
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
