// -*- C++ -*-
//
// Package:     Ordinary
// Module:      Ordinary
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Nov 18 14:26:46 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Ordinary/Ordinary.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "CalibratedData/CalibratedZDHit.h"
#include "CalibratedData/CalibratedDRHit.h"


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
static const char* const kFacilityString = "Processor.Ordinary" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Ordinary::Ordinary( void )               // anal1
   : Processor( "Ordinary" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Ordinary::event,    Stream::kEvent );
   //bind( &Ordinary::beginRun, Stream::kBeginRun );
   //bind( &Ordinary::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Ordinary::~Ordinary()                    // anal5
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
Ordinary::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Ordinary::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Ordinary::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "curv", "phi0", "d0", "cT", "z0",
      "layer", "wire", "dca", "drift", "residual"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Ordinary::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<CalibratedDRHit> drhits;
   extract(iFrame.record(Stream::kEvent), drhits);
   FATable<CalibratedZDHit> zdhits;
   extract(iFrame.record(Stream::kEvent), zdhits);

   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks.end();
	++track_iter) {
      double curvature = track_iter->pionHelix()->curvature();
      double phi0 = track_iter->pionHelix()->phi0();
      double d0 = track_iter->pionHelix()->d0();
      double cotTheta = track_iter->pionHelix()->cotTheta();
      double z0 = track_iter->pionHelix()->z0();

      const NavTrack::ZDHitLinkTable* zdlinks = track_iter->pionZDHitLinks();
      const NavTrack::DRHitLinkTable* drlinks = track_iter->pionDRHitLinks();

      NavTrack::ZDHitLinkTable::const_iterator zdlink_iter = zdlinks->begin();
      NavTrack::ZDHitLinkTable::const_iterator zdlink_end = zdlinks->end();
      NavTrack::DRHitLinkTable::const_iterator drlink_iter = drlinks->begin();
      NavTrack::DRHitLinkTable::const_iterator drlink_end = drlinks->end();

      for (; zdlink_iter != zdlink_end;  ++zdlink_iter) {
	 assert(*(**zdlink_iter).rightID());
	 FATable<CalibratedZDHit>::const_iterator zdhit_iter = zdhits.find(*(**zdlink_iter).rightID());

	 float v[kNumEntries];
	 v[kCurv] = curvature;
	 v[kPhi0] = phi0;
	 v[kD0] = d0;
	 v[kCotTheta] = cotTheta;
	 v[kZ0] = z0;
	 v[kLayer] = zdhit_iter->layer();
	 v[kWire] = zdhit_iter->wireInLyr();
	 v[kDCA] = (**zdlink_iter).linkData().signedDcaToWire();
	 v[kDrift] = (**zdlink_iter).linkData().signedDriftDistance();
	 v[kResidual] = (**zdlink_iter).linkData().residual();
	 m_ntuple->fill(v);
      }

      for (; drlink_iter != drlink_end;  ++drlink_iter) {
	 assert(*(**drlink_iter).rightID());
	 FATable<CalibratedDRHit>::const_iterator drhit_iter = drhits.find(*(**drlink_iter).rightID());

	 float v[kNumEntries];
	 v[kCurv] = curvature;
	 v[kPhi0] = phi0;
	 v[kD0] = d0;
	 v[kCotTheta] = cotTheta;
	 v[kZ0] = z0;
	 v[kLayer] = drhit_iter->layer() + 6;
	 v[kWire] = drhit_iter->wireInLyr();
	 v[kDCA] = (**drlink_iter).linkData().signedDcaToWire();
	 v[kDrift] = (**drlink_iter).linkData().signedDriftDistance();
	 v[kResidual] = (**drlink_iter).linkData().residual();
	 m_ntuple->fill(v);
      }
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Ordinary::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Ordinary::endRun( Frame& iFrame )         // anal4 equiv.
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
