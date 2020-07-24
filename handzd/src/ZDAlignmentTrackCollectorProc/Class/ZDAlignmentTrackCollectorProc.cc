// -*- C++ -*-
//
// Package:     ZDAlignmentTrackCollectorProc
// Module:      ZDAlignmentTrackCollectorProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:41:29 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ZDAlignmentTrackCollectorProc/ZDAlignmentTrackCollectorProc.h"
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

#include "CleoDB/DBEventHeader.h"
#include "Navigation/NavTrack.h"
#include "BeamEnergy/BeamEnergy.h"
#include "MagField/MagneticField.h"
#include "C3cc/CcShowerAttributes.h"
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
static const char* const kFacilityString = "Processor.ZDAlignmentTrackCollectorProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ZDAlignmentTrackCollectorProc::ZDAlignmentTrackCollectorProc( void )               // anal1
   : Processor( "ZDAlignmentTrackCollectorProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ZDAlignmentTrackCollectorProc::event,    Stream::kEvent );
   //bind( &ZDAlignmentTrackCollectorProc::beginRun, Stream::kBeginRun );
   //bind( &ZDAlignmentTrackCollectorProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ZDAlignmentTrackCollectorProc::~ZDAlignmentTrackCollectorProc()                    // anal5
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
ZDAlignmentTrackCollectorProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ZDAlignmentTrackCollectorProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ZDAlignmentTrackCollectorProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_bunchmargin = iHistoManager.histogram(
      10, "bunch margin (best-next)/best", 100, 0., 1.);
   m_nextbig_shower = iHistoManager.histogram(
      20, "second-biggest shower / eBeam", 120, 0., 1.2);
   m_colinearity = iHistoManager.histogram(
      30, "colinearity scaled by B/eBeam", 120, 0., 30.);
   m_ntracks = iHistoManager.histogram(
      40, "number of seed tracks", 7, -0.5, 6.5);
   m_curvature_sign = iHistoManager.histogram(
      50, "[k]?1! * [k]?2! sign", 3, -1.5, 1.5);
   m_fitted = iHistoManager.histogram(
      60, "Kalman fit FAILED", 2, -0.5, 1.5);
   m_momentum = iHistoManager.histogram(
      70, "Track momentum / eBeam", 120, 0., 1.2);
   m_d0 = iHistoManager.histogram(
      80, "d?0!", 100, -0.02, 0.02);
   m_d0miss = iHistoManager.histogram(
      90, "d?0!^track 1! + d?0!^track 2!", 100, -0.004, 0.004);
   m_z0 = iHistoManager.histogram(
      100, "z?0!", 100, -0.20, 0.20);
   m_pmag = iHistoManager.histogram(
      110, "(p^track 1! + p^track 2!)?magnitude! / eBeam", 100, 0., 0.2);
   m_pperp = iHistoManager.histogram(
      120, "(p^track 1! + p^track 2!)?perp! / eBeam", 100, 0., 0.2);
   m_pz = iHistoManager.histogram(
      130, "(p^track 1! + p^track 2!)?z! / eBeam", 100, -0.2, 0.2);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ZDAlignmentTrackCollectorProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TrackletBunchDecision> bunch_decision;
   extract(iFrame.record(Stream::kEvent), bunch_decision);

   if (bunch_decision->numberOfTestedBunches() < 2) return ActionBase::kFailed;
   double bestbunch = bunch_decision->bestBunchInfo().bweight();
   if (bestbunch <= 0.) return ActionBase::kFailed;
   double nextbunch = bunch_decision->bunchInfo(1).bweight();
   m_bunchmargin->fill((bestbunch-nextbunch)/bestbunch);
   if ((bestbunch-nextbunch)/bestbunch < 0.4) return ActionBase::kFailed;

   FAItem<BeamEnergy> beam_energy;
   extract(iFrame.record(Stream::kStartRun), beam_energy);

   FAItem<MagneticField> magnetic_field;
   extract(iFrame.record(Stream::kStartRun), magnetic_field);

   // This extraction fails on the second time for some reason...
   FATable<CcShowerAttributes> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<CcShowerAttributes>::const_iterator shower_iter = showers.begin();
   FATable<CcShowerAttributes>::const_iterator shower_end = showers.end();

   double biggest_energy = 0.;
   double nextbig_energy = 0.;
   FATable<CcShowerAttributes>::const_iterator biggest;
   FATable<CcShowerAttributes>::const_iterator nextbig;

   for (; shower_iter != shower_end;  ++shower_iter) {
      if (shower_iter->hot()) continue;

      if (shower_iter->energy() > biggest_energy) {
	 biggest_energy = shower_iter->energy();
	 biggest = shower_iter;
      }
      else if (shower_iter->energy() > nextbig_energy) {
	 nextbig_energy = shower_iter->energy();
	 nextbig = shower_iter;
      }
   }

   m_nextbig_shower->fill(nextbig_energy/beam_energy->value());
   if (nextbig_energy < 0.5 * beam_energy->value()) return ActionBase::kFailed;

   double lowcut  = 2.3 * ((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.;
   double highcut = 15. * ((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.;
   double colinearity = fabs(M_PI - fabs(biggest->phi() - nextbig->phi()));

   m_colinearity->fill(colinearity / ((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.);
   if (colinearity < lowcut  ||  colinearity > highcut) return ActionBase::kFailed;

   FATable<TRSeedTrack> seeds;
   extract(iFrame.record(Stream::kEvent), seeds);
   m_ntracks->fill(seeds.size());
   if (seeds.size() != 2 ) return ActionBase::kFailed;

   FAItem<SeedTrackDRHitLattice> drlattice;
   extract(iFrame.record(Stream::kEvent), drlattice);
   FAItem<SeedTrackZDHitLattice> zdlattice;
   extract(iFrame.record(Stream::kEvent), zdlattice);
   for (FATable<TRSeedTrack>::const_iterator seed_iter = seeds.begin();
	seed_iter != seeds.end();
	++seed_iter) {
//       const SeedTrackDRHitLattice::VectorRightID* vect_drhits =
// 	 drlattice->vRightGivenLeft(seed_iter->identifier());
//       if (vect_drhits == NULL  ||  vect_drhits->size() < 42) return ActionBase::kFailed;
      const SeedTrackZDHitLattice::VectorRightID* vect_zdhits =
	 zdlattice->vRightGivenLeft(seed_iter->identifier());
      if (vect_zdhits == NULL  ||  vect_zdhits->size() < 1) return ActionBase::kFailed;
   }

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);

   FATable<NavTrack>::const_iterator first = tracks.begin();
   FATable<NavTrack>::const_iterator second = first;  ++second;

   m_curvature_sign->fill(first->pionHelix()->curvature() * second->pionHelix()->curvature() > 0.? 1. : -1.);
   if (first->pionHelix()->curvature() * second->pionHelix()->curvature() > 0.) return ActionBase::kFailed;

   m_fitted->fill(!first->pionQuality()->fit()  ||  first->pionQuality()->fitAbort() ? 0. : 1.);
   if (!first->pionQuality()->fit()  ||  first->pionQuality()->fitAbort()) return ActionBase::kFailed;
   m_fitted->fill(!second->pionQuality()->fit()  ||  second->pionQuality()->fitAbort() ? 0. : 1.);
   if (!second->pionQuality()->fit()  ||  second->pionQuality()->fitAbort()) return ActionBase::kFailed;

   m_momentum->fill(first->pionFit()->momentum().mag() / beam_energy->value());
   if (first->pionFit()->momentum().mag() < 0.8 * beam_energy->value()) return ActionBase::kFailed;
   m_momentum->fill(second->pionFit()->momentum().mag() / beam_energy->value());
   if (second->pionFit()->momentum().mag() < 0.8 * beam_energy->value()) return ActionBase::kFailed;

   m_d0->fill(first->pionHelix()->d0());
   if (fabs(first->pionHelix()->d0()) > 0.01) return ActionBase::kFailed;
   m_d0->fill(second->pionHelix()->d0());
   if (fabs(second->pionHelix()->d0()) > 0.01) return ActionBase::kFailed;

   m_d0miss->fill(first->pionHelix()->d0() + second->pionHelix()->d0());
   if (fabs(first->pionHelix()->d0() + second->pionHelix()->d0()) > 0.002) return ActionBase::kFailed;

   m_z0->fill(first->pionHelix()->z0());
   if (fabs(first->pionHelix()->z0()) > 0.10) return ActionBase::kFailed;
   m_z0->fill(second->pionHelix()->z0());
   if (fabs(second->pionHelix()->z0()) > 0.10) return ActionBase::kFailed;

   HepVector3D total_momentum(first->pionFit()->momentum() + second->pionFit()->momentum() +
			      HepVector3D(0.013 * beam_energy->value()/5.29, 0, 0));

   m_pmag->fill(total_momentum.mag() / beam_energy->value());
//    if (total_momentum.mag() > 0.548 * beam_energy->value()/5.29) return ActionBase::kFailed;

   m_pperp->fill(total_momentum.perp() / beam_energy->value());
   m_pz->fill(total_momentum.z() / beam_energy->value());

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ZDAlignmentTrackCollectorProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ZDAlignmentTrackCollectorProc::endRun( Frame& iFrame )         // anal4 equiv.
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
