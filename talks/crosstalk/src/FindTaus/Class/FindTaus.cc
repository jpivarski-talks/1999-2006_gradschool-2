// -*- C++ -*-
//
// Package:     FindTaus
// Module:      FindTaus
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Jun 13 17:21:45 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FindTaus/FindTaus.h"
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
static const char* const kFacilityString = "Processor.FindTaus" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FindTaus::FindTaus( void )               // anal1
   : Processor( "FindTaus" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FindTaus::event,    Stream::kEvent );
   //bind( &FindTaus::beginRun, Stream::kBeginRun );
   //bind( &FindTaus::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FindTaus::~FindTaus()                    // anal5
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
FindTaus::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FindTaus::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FindTaus::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FindTaus::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable );

   int num_showers(0);

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();
   for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
        showerItr != showerEnd ; ++showerItr )
   {
      if (! showerItr->attributes().hot()  &&
	  showerItr->attributes().energy() > 0.030 ) {
	 num_showers++;
      }
   }
   if (num_showers > 13) return ActionBase::kFailed;


   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "TrkmanApproved" );

   int event_charge(0);
   int num_tracks(0);

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      report(INFO, kFacilityString) << "TkmanApproved: " << trackItr->identifier() << endl;
      event_charge += (trackItr->pionHelix()->curvature() > 0. ? 1 : -1);
      num_tracks++;
   }

   if ( event_charge != 0 ) return ActionBase::kFailed;
   if ( num_tracks != 4 ) return ActionBase::kFailed;



   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
FindTaus::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FindTaus::endRun( Frame& iFrame )         // anal4 equiv.
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
