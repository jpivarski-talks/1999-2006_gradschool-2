// -*- C++ -*-
//
// Package:     MyFourthProc
// Module:      MyFourthProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun  6 18:44:36 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MyFourthProc/MyFourthProc.h"
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
#include "HistogramInterface/HIHist2D.h"
#include "HistogramInterface/HIHistProf.h"
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
static const char* const kFacilityString = "Processor.MyFourthProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.40 2005/02/10 16:03:57 chengp Exp $";
static const char* const kTagString = "$Name: v07_02_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
MyFourthProc::MyFourthProc( void )               // anal1
   : Processor( "MyFourthProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &MyFourthProc::event,    Stream::kEvent );
   //bind( &MyFourthProc::beginRun, Stream::kBeginRun );
   //bind( &MyFourthProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

MyFourthProc::~MyFourthProc()                    // anal5
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
MyFourthProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MyFourthProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
MyFourthProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_d0vsphi = iHistoManager.histogram("1 d0 vs phi", 30, 0., 2.*M_PI, 20, -0.001, 0.001);
   m_d0vsphi_prof = iHistoManager.profile("2 d0 vs phi", 60, 0., 2.*M_PI, -0.003, 0.003, HIHistProf::kErrorOnMean);
   m_showerEnergy = iHistoManager.histogram("3 shower energy (GeV)", 100, 0., 6.);
   m_showerEnergy_closeup = iHistoManager.histogram("4 shower energy (GeV)", 100, 0., 3.);
   m_costhetaPosBhabha = iHistoManager.histogram("5 costheta pos bhabha", 100, -1., 1.);
   m_costhetaNegBhabha = iHistoManager.histogram("6 costheta neg bhabha", 100, -1., 1.);
   m_costhetaPosMupair = iHistoManager.histogram("7 costheta pos mupair", 100, -1., 1.);
   m_costhetaNegMupair = iHistoManager.histogram("8 costheta neg mupair", 100, -1., 1.);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
MyFourthProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   // First cut: we want two tracks
   if (trackTable.size() != 2)
   {
      return ActionBase::kFailed;
   }

   FATable< NavTrack >::const_iterator closestTrack = trackTable.end();
   FATable< NavTrack >::const_iterator biggestPosTrack = trackTable.end();
   FATable< NavTrack >::const_iterator biggestNegTrack = trackTable.end();

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

      if (trackItr->pionHelix()->curvature() > 0.) // positive curvature means positive charge
      {
	 if (biggestPosTrack == trackTable.end()  ||
	     fabs(biggestPosTrack->pionFit()->momentum().mag()) <
	     fabs(trackItr->pionFit()->momentum().mag()))
	 {
	    biggestPosTrack = trackItr;
	 }
      }
      else // negative curvature means negative charge
      {
	 if (biggestNegTrack == trackTable.end()  ||
	     fabs(biggestNegTrack->pionFit()->momentum().mag()) <
	     fabs(trackItr->pionFit()->momentum().mag()))
	 {
	    biggestNegTrack = trackItr;
	 }
      }
   }

   // Second cut: we want the two tracks to be oppositely-charged
   if (biggestPosTrack == trackTable.end()  ||
       biggestNegTrack == trackTable.end())
   {
      return ActionBase::kFailed;
   }

   // Third cut: we want the two tracks to have high energy
   if (biggestPosTrack->pionFit()->momentum().mag() < 1.5  ||
       biggestNegTrack->pionFit()->momentum().mag() < 1.5)     // that's 1.5 GeV
   {
      return ActionBase::kFailed;
   }

   // Fourth cut: we don't want cosmic rays
   if (fabs(closestTrack->pionHelix()->d0()) > 0.003) // that 3 mm
   {
      return ActionBase::kFailed;
   }

   // Let's get some shower information, too
   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable );

   double totalEnergy = 0.;

   for (FATable< NavShower >::const_iterator showerItr = showerTable.begin(); 
        showerItr != showerTable.end() ;
	++showerItr )
   {
      totalEnergy += showerItr->attributes().energy();
   }

   // Fill the histograms!
   m_d0vsphi->fill(biggestPosTrack->pionHelix()->phi0(),
		   biggestPosTrack->pionHelix()->d0());
   m_d0vsphi_prof->fill(biggestPosTrack->pionHelix()->phi0(),
			biggestPosTrack->pionHelix()->d0());

   m_showerEnergy->fill(totalEnergy);
   m_showerEnergy_closeup->fill(totalEnergy);

   double costhetaPos = biggestPosTrack->pionHelix()->cotTheta() /
      sqrt(1. + sqr(biggestPosTrack->pionHelix()->cotTheta()));
   double costhetaNeg = biggestNegTrack->pionHelix()->cotTheta() /
      sqrt(1. + sqr(biggestNegTrack->pionHelix()->cotTheta()));

   if (totalEnergy > 3.) // that's 3 GeV
   {
      m_costhetaPosBhabha->fill(costhetaPos);
      m_costhetaNegBhabha->fill(costhetaNeg);
   }
   else // low shower energies
   {
      m_costhetaPosMupair->fill(costhetaPos);
      m_costhetaNegMupair->fill(costhetaNeg);
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
MyFourthProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
MyFourthProc::endRun( Frame& iFrame )         // anal4 equiv.
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
