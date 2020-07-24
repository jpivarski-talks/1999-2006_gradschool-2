// -*- C++ -*-
//
// Package:     Mysterious
// Module:      Mysterious
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Nov 14 14:12:01 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Mysterious/Mysterious.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "AZDGeom/AZDSenseWireStore.h"
#include "CalibratedData/CalibratedZDHit.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Parameter.h"
#include "DataHandler/Frame.h"
#include "DataHandler/Record.h"
#include "DataHandler/Stream.h"
#include "DetectorGeometry/DGConstMaterialPtr.h"
#include "DetectorGeometry/DGConstPlacedVolumePtr.h"
#include "DetectorGeometry/DGConstVolumePtr.h"
#include "DetectorGeometry/DGDetectorStore.h"
#include "DetectorGeometry/DGMaterialStore.h"
#include "DetectorGeometry/DGPath.h"
#include "DetectorGeometry/DGPlacedVolume.h"
#include "DetectorGeometry/DGVolume.h"
#include "Experiment/report.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameIterate/FIHolder.h"
#include "FrameIterate/FrameIteratorModuleBase.h"
#include <fstream.h>
#include "HelixIntersection/HICalibratedWireHit.h"
#include "HelixIntersection/HIHelix.h"
#include "HelixIntersection/HIHelixIntersector.h"
#include "HelixIntersection/HIIntersectionSurface.h"
#include "HelixIntersection/HIMultiWireCylinder.h"
#include "HelixIntersection/HISingleWireCylinder.h"
#include "HelixIntersection/HIWireLayerCylinder.h"
#include "HelixIntersection/HIZBoundaryCondition.h"
#include "HelixIntersection/HIZDSurfaceFactory.h"
#include <iostream.h>
#include "JobControl/JobControl.h"
#include "MaterialDelivery/material_identifiers.h"
#include "MinuitInterface/MIFcn.h"
#include "MinuitInterface/MinuitInterface.h"
#include "Navigation/NavTrack.h"
#include <stdio.h>
#include "ToolBox/HistogramPackage.h"
#include "TrackFinder/SeedZDHitLink.h"
#include "ZDHitCorrectorProd/ZDHitCorrector.h"
#include "DRHitCorrectorProd/HitCorrector.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "BeamEnergy/BeamEnergy.h"

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
static const char* const kFacilityString = "Processor.Mysterious" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Mysterious::Mysterious( void )               // anal1
   : Processor( "Mysterious" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Mysterious::event,    Stream::kEvent );
   //bind( &Mysterious::beginRun, Stream::kBeginRun );
   //bind( &Mysterious::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Mysterious::~Mysterious()                    // anal5
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
Mysterious::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Mysterious::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Mysterious::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "curv", "phi0", "d0", "cT", "z0",
      "layer", "wire", "phi", "z", "drift", "dca",
      "bestb", "nextb", "drhits", "pperp", "pz"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

   m_z0missVcotTheta = iHistoManager.profile(
      10, "z0miss VS cotTheta", 10, -3., 3., -0.05, 0.05, HIHistProf::kErrorOnMean);
   m_z0missVcotTheta_morebins = iHistoManager.profile(
      11, "z0miss VS cotTheta", 60, -3., 3., -0.05, 0.05, HIHistProf::kErrorOnMean);

   m_residualVz = iHistoManager.profile(
      20, "ZD resid VS z", 10, -0.3, 0.3, -0.003, 0.003, HIHistProf::kErrorOnMean);
   m_residualVz_2d = iHistoManager.histogram(
      21, "ZD resid VS z", 10, -0.3, 0.3, 10, -0.003, 0.003);

   m_bunchmargin = iHistoManager.histogram(
      30, "bunch margin (best-next)/best", 50, 0., 1.);

   m_cotTheta = iHistoManager.histogram(
      40, "cotTheta", 50, -3., 3.);

   m_numberHits = iHistoManager.histogram(
      50, "number of DR hits", 61, -0.5, 60.5);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Mysterious::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<BeamEnergy> beam_energy;
   extract(iFrame.record(Stream::kStartRun), beam_energy);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();
   
   FATable<CalibratedDRHit> drhits;
   extract(iFrame.record(Stream::kEvent), drhits);
   FATable<CalibratedDRHit>::const_iterator drhits_end = drhits.end();
   FATable<CalibratedZDHit> zdhits;
   extract(iFrame.record(Stream::kEvent), zdhits);

//    double drhitsInTime = 0;
//    for (FATable<CalibratedDRHit>::const_iterator drhit_iter = drhits.begin();
// 	drhit_iter != drhits_end;
// 	++drhit_iter) {
//       if (-100000. < drhit_iter->time()  &&  drhit_iter->time() < 500000.) drhitsInTime++;
//    }
//    if (!(70 <= drhitsInTime  &&  drhitsInTime <= 118)) return ActionBase::kFailed;

   FAItem<HitCorrector> drcorrector;
   extract(iFrame.record(Stream::kStartRun), drcorrector);
   FAItem<ZDHitCorrector> zdcorrector;
   extract(iFrame.record(Stream::kStartRun), zdcorrector);

   FAItem<AZDSenseWireStore> zdstore;
   extract(iFrame.record(Stream::kZDAlignment), zdstore);
   FAItem<ADRSenseWireStore> drstore;
   extract(iFrame.record(Stream::kDRAlignment), drstore);

   DGMaterialStore materials;
   extract(iFrame.record(Stream::kMaterial), materials);
   const DGConstMaterialPtr& zdGas = materials[kZDGasWireVaporMatID];
   const DGConstMaterialPtr& drGas = materials[kGasWireVaporMatID];

   FAItem<TrackletBunchDecision> bunch_decision;
   extract(iFrame.record(Stream::kEvent), bunch_decision);

   double bestbunch, nextbunch;
   if (bunch_decision->numberOfTestedBunches() >= 2) {
      bestbunch = bunch_decision->bestBunchInfo().bweight();
      nextbunch = bunch_decision->bunchInfo(1).bweight();
   }
   else {
      bestbunch = 0.0001;
      nextbunch = 0.0001;
   }
   if (bestbunch == 0.) {
      bestbunch = 0.0001;
      nextbunch = 0.0001;
   }

   m_bunchmargin->fill((bestbunch-nextbunch)/bestbunch);

   if (tracks.size() == 2) {
      FATable<NavTrack>::const_iterator positive;
      FATable<NavTrack>::const_iterator negative;
      for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	   track_iter != tracks.end();
	   ++track_iter) {
	 if (track_iter->pionHelix()->curvature() > 0.) positive = track_iter;
	 else negative = track_iter;
      }

      m_z0missVcotTheta->fill(positive->pionHelix()->cotTheta(),
			      positive->pionHelix()->z0() - negative->pionHelix()->z0());
      m_z0missVcotTheta_morebins->fill(positive->pionHelix()->cotTheta(),
				       positive->pionHelix()->z0() - negative->pionHelix()->z0());
   }

   HepVector3D tracks_momentum(0.013 * beam_energy->value()/5.29, 0., 0.);
   for (; track_iter != track_end;  ++track_iter) {
      tracks_momentum += track_iter->pionFit()->momentum();
   }
   double pperp = tracks_momentum.perp();
   double pz = tracks_momentum.z();

   for (track_iter = tracks.begin();  track_iter != track_end;  ++track_iter) {
      double curvature = track_iter->pionHelix()->curvature();
      double phi0 = track_iter->pionHelix()->phi0();
      double d0 = track_iter->pionHelix()->d0();
      double cotTheta = track_iter->pionHelix()->cotTheta();
      double z0 = track_iter->pionHelix()->z0();

      m_cotTheta->fill(cotTheta);

      const NavTrack::SeedZDHitLinkTable* zdlinks = track_iter->seedZDHitLinks();
//       const NavTrack::SeedDRHitLinkTable* drlinks = track_iter->seedDRHitLinks();

      int numdrhits = track_iter->pionQuality()->numberSubdetectorHits(TRSubdetectorLists::kDR3Axial) +
	 track_iter->pionQuality()->numberSubdetectorHits(TRSubdetectorLists::kDR3Stereo);
      m_numberHits->fill(numdrhits);

      NavTrack::SeedZDHitLinkTable::const_iterator zdlink_iter = zdlinks->begin();
      NavTrack::SeedZDHitLinkTable::const_iterator zdlink_end = zdlinks->end();
//       NavTrack::SeedDRHitLinkTable::const_iterator drlink_iter = drlinks->begin();
//       NavTrack::SeedDRHitLinkTable::const_iterator drlink_end = drlinks->end();

      double zdcharge_sum = 0;
      unsigned int zdcharge_N = 0;
      for (; zdlink_iter != zdlink_end;  ++zdlink_iter) {
	 if ((**zdlink_iter).linkData().fitFlag() == SeedZDHitLink::kFITTABLE) {
	    assert(*(**zdlink_iter).rightID());
	    FATable<CalibratedZDHit>::const_iterator zdhit_iter = zdhits.find(*(**zdlink_iter).rightID());
	    zdcharge_sum += zdhit_iter->charge();
	    zdcharge_N++;
	 }
      }

//       double drcharge_sum = 0;
//       unsigned int drcharge_N = 0;
//       for (; drlink_iter != drlink_end;  ++drlink_iter) {
// 	 if ((**drlink_iter).linkData().fitFlag() == SeedZDHitLink::kFITTABLE) {
// 	    assert(*(**drlink_iter).rightID());
// 	    FATable<CalibratedDRHit>::const_iterator drhit_iter = drhits.find(*(**drlink_iter).rightID());
// 	    drcharge_sum += drhit_iter->charge();
// 	    drcharge_N++;
// 	 }
//       }

      HIHelix helix(*track_iter->pionHelix());

      for (zdlink_iter = zdlinks->begin();  zdlink_iter != zdlink_end;  ++zdlink_iter) {
	 if ((**zdlink_iter).linkData().fitFlag() != SeedZDHitLink::kFITTABLE) continue;

	 assert(*(**zdlink_iter).rightID());
	 FATable<CalibratedZDHit>::const_iterator zdhit_iter = zdhits.find(*(**zdlink_iter).rightID());
	    
	 vector<HIIntersectionSurface*> surface;
	 surface.push_back(new HISingleWireCylinder(
			      zdGas, zdGas,
			      zdstore->layer(zdhit_iter->layer()),
			      zdhit_iter->layer(),
			      DGTransform::Identity,
			      NULL, NULL,
			      &*zdhit_iter,
			      (**zdlink_iter).linkData().signedDriftDistance(),
			      &*zdcorrector,
			      false,
			      zdcharge_sum / double(zdcharge_N)
			      ));
	 helix.moveToRadius(zdstore->layer(zdhit_iter->layer()).radius());
	 HIHelixIntersector intersector(surface,
					HIHelixIntersector::kOrderAsGiven,
					&helix);
	 intersector.swimToCurrentSurface(KTMoveControl::kDirectionEither);
	 intersector.currentSurface()->hiCalibratedHit()->applyTrackCorrections(helix);

	 float v[kNumEntries];
	 v[kCurv] = curvature;
	 v[kPhi0] = phi0;
	 v[kD0] = d0;
	 v[kCotTheta] = cotTheta;
	 v[kZ0] = z0;
	 v[kLayer] = zdhit_iter->layer();
	 v[kWire] = zdhit_iter->wireInLyr();
	 v[kPhi] = helix.phi0();
	 v[kZ] = helix.position().z();
	 v[kDCA] = intersector.currentSurface()->dca(helix);
	 v[kDrift] = ((HICalibratedWireHit*)
		      intersector.currentSurface()->hiCalibratedHit())->signedDriftDistance();

	 v[kBestBunch] = bestbunch;
	 v[kNextBunch] = nextbunch;

	 v[kNumDRHits] = numdrhits;
	 v[kPPerp] = pperp;
	 v[kPZ] = pz;

	 m_ntuple->fill(v);

	 m_residualVz->fill(v[kZ], v[kDCA] - v[kDrift]);
	 m_residualVz_2d->fill(v[kZ], v[kDCA] - v[kDrift]);

	 delete *surface.begin();
      } // end ZD hit link loop

//       for (drlink_iter = drlinks->begin();  drlink_iter != drlink_end;  ++drlink_iter) {
// 	 if ((**drlink_iter).linkData().fitFlag() != SeedZDHitLink::kFITTABLE) continue;

// 	 assert(*(**drlink_iter).rightID());
// 	 FATable<CalibratedDRHit>::const_iterator drhit_iter = drhits.find(*(**drlink_iter).rightID());
	    
// // 	 if (drhit_iter->layer() > 3) continue;

// 	 vector<HIIntersectionSurface*> surface;
// 	 surface.push_back(new HISingleWireCylinder(
// 			      drGas, drGas,
// 			      drstore->layer(drhit_iter->layer()),
// 			      drhit_iter->layer(),
// 			      DGTransform::Identity,
// 			      NULL, NULL,
// 			      &*drhit_iter,
// 			      (**drlink_iter).linkData().signedDriftDistance(),
// 			      &*drcorrector,
// 			      false,
// 			      drcharge_sum / double(drcharge_N)
// 			      ));
// 	 helix.moveToRadius(drstore->layer(drhit_iter->layer()).radius());
// 	 HIHelixIntersector intersector(surface,
// 					HIHelixIntersector::kOrderAsGiven,
// 					&helix);
// 	 intersector.swimToCurrentSurface(KTMoveControl::kDirectionEither);
// 	 intersector.currentSurface()->hiCalibratedHit()->applyTrackCorrections(helix);

// 	 float v[kNumEntries];
// 	 v[kCurv] = curvature;
// 	 v[kPhi0] = phi0;
// 	 v[kD0] = d0;
// 	 v[kCotTheta] = cotTheta;
// 	 v[kZ0] = z0;
// 	 v[kLayer] = drhit_iter->layer() + 6;
// 	 v[kWire] = drhit_iter->wireInLyr();
// 	 v[kPhi] = helix.phi0();
// 	 v[kZ] = helix.position().z();
// 	 v[kDCA] = intersector.currentSurface()->dca(helix);
// 	 v[kDrift] = ((HICalibratedWireHit*)
// 		      intersector.currentSurface()->hiCalibratedHit())->signedDriftDistance();
// 	 m_ntuple->fill(v);

// 	 delete *surface.begin();
//       } // end DR hit link loop

   } // end track loop

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Mysterious::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Mysterious::endRun( Frame& iFrame )         // anal4 equiv.
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
