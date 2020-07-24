// -*- C++ -*-
//
// Package:     LCDTwoLeptonsProc
// Module:      LCDTwoLeptonsProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed Jun 16 13:52:46 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LCDTwoLeptonsProc/LCDTwoLeptonsProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "LCDRootAccess/Vector.h"

#include "LCDTrack.h"
#include "LCDMcPart.h"
#include "LCDCluster.h"
#include "LCDMatching/LCDMatchTrack.h"
#include "LCDMatching/LCDIsolateCluster.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

using LCDRootAccess::Vector;

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.LCDTwoLeptonsProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
LCDTwoLeptonsProc::LCDTwoLeptonsProc( void )               // anal1
   : Processor( "LCDTwoLeptonsProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LCDTwoLeptonsProc::event,    Stream::kEvent );
   //bind( &LCDTwoLeptonsProc::beginRun, Stream::kBeginRun );
   //bind( &LCDTwoLeptonsProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

LCDTwoLeptonsProc::~LCDTwoLeptonsProc()                    // anal5
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
LCDTwoLeptonsProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LCDTwoLeptonsProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
LCDTwoLeptonsProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_dist = iHistoManager.histogram(
      10, "Distance to matched showers (all tracks)", 1000, 0., 15.);
   m_dist50 = iHistoManager.histogram(
      11, "Distance to matched showers (.gt.50 GeV)", 1000, 0., 15.);
   m_dist100 = iHistoManager.histogram(
      12, "Distance to matched showers (.gt.100 GeV)", 1000, 0., 15.);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LCDTwoLeptonsProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<LCDMatchTrack> matchTrack;
   extract(iFrame.record(Stream::kEvent), matchTrack);
   FATable<LCDMatchTrack>::const_iterator matchTrack_end = matchTrack.end();

//    FATable<LCDIsolateCluster> isolateCluster;
//    extract(iFrame.record(Stream::kEvent), isolateCluster);
//    FATable<LCDIsolateCluster>::const_iterator isolateCluster_end = isolateCluster.end();

   for (FATable<LCDMatchTrack>::const_iterator matchTrack_iter = matchTrack.begin();
	matchTrack_iter != matchTrack_end;  ++matchTrack_iter) {
      double momentum = matchTrack_iter->track()->GetMomentumVector(0.).Mag();

      const vector<double>& distance = matchTrack_iter->distance();
      vector<double>::const_iterator distance_end = distance.end();
      for (vector<double>::const_iterator distance_iter = distance.begin();
	   distance_iter != distance_end;  ++distance_iter) {
	 m_dist->fill(*distance_iter);
	 if (momentum > 50.) m_dist50->fill(*distance_iter);
	 if (momentum > 100.) m_dist100->fill(*distance_iter);
      } // end loop over distances

   } // end loop over tracks

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
LCDTwoLeptonsProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LCDTwoLeptonsProc::endRun( Frame& iFrame )         // anal4 equiv.
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


//       const vector<const LCDCluster*>& cluster = matchTrack_iter->cluster();
//       vector<const LCDCluster*>::const_iterator cluster_end = cluster.end();
//       for (vector<const LCDCluster*>::const_iterator cluster_iter = cluster.begin();
// 	   cluster_iter != cluster_end;  ++cluster_iter) {
