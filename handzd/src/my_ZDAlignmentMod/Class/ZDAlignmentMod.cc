// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentMod
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:40:29 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdio.h>
#include <fstream.h>
#include <iostream.h>

// user include files
#include "Experiment/report.h"
#include "ZDAlignmentMod/ZDAlignmentMod.h"
#include "ZDAlignmentMod/ZDAlignmentFcn.h"
#include "DataHandler/Stream.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/extract.h"
#include "DataHandler/Frame.h"
#include "Navigation/NavTrack.h"
#include "TrackFinder/SeedZDHitLink.h"

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
static const char* const kFacilityString = "ZDAlignmentMod.ZDAlignmentMod" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: fimodule.cc,v 1.2 2000/12/04 19:11:05 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
ZDAlignmentMod::ZDAlignmentMod()
   : FrameIteratorModuleBase( "ZDAlignmentMod", "No, this is the awesomest module." )
   , m_geometry(new DBZDGeomAlignment[3], 3)
   , m_geometry_holder(&m_geometry)
   , m_geomlayer(new DBAZDGeomLayer[6], 6)
   , m_geomlayer_holder(&m_geomlayer)
   , m_first_time(true)
   , m_geomName("geom", this, "best.zdgeomalignment")
   , m_geomLayerName("geomLayer", this, "normal.azdgeomlayer")
   , m_minDrift("minDrift", this, 1.5)  // these are in mm, of course
   , m_maxDrift("maxDrift", this, 3.8)
   , m_showPlots("showPlots", this, true)
   , m_interactive("interactive", this, true)
   , m_ntuple("ntuple", this, false)
   , m_fakeDriftFunction("fakeDriftFunction", this, false)
   , m_twoD("twoD", this, false)
   , m_fcn(&m_geometry, &m_geomlayer)
   , m_minuit(MinuitInterface::instance())
{
   registerProxyFactory(Stream::kZDAlignment,
			m_geometry_holder.makeFactory(),
			UsageTag());
   registerProxyFactory(Stream::kBaseGeometry,
			m_geomlayer_holder.makeFactory(),
			UsageTag());

   //You must set what streams you which to iterate over
   //  that is, what events should the Frames be stopped on
   iterateOver(Stream::kEvent);

   m_minuit->loadFcn(m_fcn);
}

// ZDAlignmentMod::ZDAlignmentMod( const ZDAlignmentMod& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ZDAlignmentMod::~ZDAlignmentMod()
{
}

//
// assignment operators
//
// const ZDAlignmentMod& ZDAlignmentMod::operator=( const ZDAlignmentMod& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
void
ZDAlignmentMod::iterate( const FIFrameIterator& iBegin,
			 const FIFrameIterator& iEnd )
{
   if (m_first_time) {
      ifstream geometry_file(m_geomName.value().c_str());
      if (! m_geometry.readFromStream(geometry_file)) assert(false);

      ifstream geomlayer_file(m_geomLayerName.value().c_str());
      if (! m_geomlayer.readFromStream(geomlayer_file)) assert(false);

      m_minuit->changeParameterStart(ZDAlignmentFcn::kX, m_geometry[0].get_deltaX()*25.4);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kY, m_geometry[0].get_deltaY()*25.4);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kZ, m_geometry[0].get_deltaZ()*25.4);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotX, m_geometry[0].get_rotX()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotY, m_geometry[0].get_rotY()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotZ, m_geometry[0].get_rotZ()*1000.);

      m_minuit->changeParameterStart(ZDAlignmentFcn::kTwistWest, m_geometry[2].get_rotZ()*1000.);

      m_first_time = false;
   }

   m_fcn.reset(iBegin);

   for(FIFrameIterator itFrame = iBegin;  itFrame != iEnd;  ++itFrame) {
      m_fcn.book(m_showPlots.value(), m_fakeDriftFunction.value(), m_twoD.value(), m_ntuple.value());

      FATable<NavTrack> tracks;
      extract(itFrame->record(Stream::kEvent), tracks);
      FATable<NavTrack>::const_iterator tracks_end = tracks.end();

      FATable<CalibratedZDHit> allhits;
      extract(itFrame->record(Stream::kEvent), allhits);

      for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	   track_iter != tracks_end;
	   ++track_iter) {
// 	 const NavTrack::ZDHitLinkTable* pionLinks = track_iter->pionZDHitLinks();
// 	 NavTrack::ZDHitLinkTable::const_iterator pionLink_end = pionLinks->end();
// 	 for (NavTrack::ZDHitLinkTable::const_iterator pionLink_iter = pionLinks->begin();
// 	      pionLink_iter != pionLink_end;
// 	      ++pionLink_iter) {
// 	    cout <<  "FITTER SAYS " << (**pionLink_iter).linkData().signedDriftDistance() << " "
// 		 << (**pionLink_iter).linkData().signedDcaToWire() << " "
// 		 << (**pionLink_iter).linkData().residual() << endl;
// 	 }

 	 const KTHelix& track = *track_iter->pionHelix();
	 const NavTrack::SeedZDHitLinkTable* links = track_iter->seedZDHitLinks();
	 NavTrack::SeedZDHitLinkTable::const_iterator link_end = links->end();

	 if (fabs(track.cotTheta()) > 2.) continue;

	 double charge_sum = 0.;
	 unsigned int charge_N = 0;
	 vector<const CalibratedZDHit*> hits;
	 vector<double> drifts;

	 for (NavTrack::SeedZDHitLinkTable::const_iterator link_iter = links->begin();
	      link_iter != link_end;
	      ++link_iter) {

	    if ((**link_iter).linkData().fitFlag() == SeedZDHitLink::kFITTABLE) {
	       assert(*(**link_iter).rightID());
	       FATable<CalibratedZDHit>::const_iterator hit_iter = allhits.find(*(**link_iter).rightID());

	       charge_sum += hit_iter->charge();  charge_N++;

	       if (fabs(hit_iter->distance()) > m_minDrift.value()/1000. &&
		   fabs(hit_iter->distance()) < m_maxDrift.value()/1000.   ) {
		  hits.push_back(&*hit_iter);
		  drifts.push_back((**link_iter).linkData().signedDriftDistance());
	       }

	    } // end if hit is kFITTABLE
	 } // end loop over hit links

	 if (!hits.empty()) m_fcn.fill(track, charge_sum/double(charge_N), hits, drifts);
      } // end loop over tracks
   } // end loop over events

   if (m_interactive.value()) {
      m_minuit->setDiagLevel(MinuitInterface::kMute);
      for (int i = 0;  i < ZDAlignmentFcn::kNumParams;  i++) m_minuit->fixParameter(i);
      m_minuit->setDiagLevel(MinuitInterface::kNormal);
      m_minuit->interact();
   }
   else {
      double v[ZDAlignmentFcn::kNumParams];
      for (int i = 0;  i < ZDAlignmentFcn::kNumParams;  i++) v[i] = m_minuit->parameter(i).start();
      m_fcn.iterate(v);
   }
}

//
// static member functions
//
