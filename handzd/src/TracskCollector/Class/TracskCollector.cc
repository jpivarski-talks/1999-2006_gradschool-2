// -*- C++ -*-
//
// Package:     TracskCollector
// Module:      TracskCollector
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Nov 13 17:16:51 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TracskCollector/TracskCollector.h"
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
#include "Navigation/NavShower.h"


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
static const char* const kFacilityString = "Processor.TracskCollector" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TracskCollector::TracskCollector( void )               // anal1
   : Processor( "TracskCollector" )
   , m_checkBunch("checkBunch", this, true)
   , m_checkMIP("checkMIP", this, true)
   , m_checkSecondBiggest("checkSecondBiggest", this, true)
   , m_checkColinearity("checkColinearity", this, true)
   , m_checkNumShowers("checkNumShowers", this, true)
   , m_checkShowerMomentum("checkShowerMomentum", this, true)
   , m_checkMatchedShowers("checkMatchedShowers", this, true)
   , m_checkOppositeCurvature("checkOppositeCurvature", this, true)
   , m_checkFitAbort("checkFitAbort", this, true)
   , m_checkMomentumLow("checkMomentumLow", this, true)
   , m_checkMomentumHigh("checkMomentumHigh", this, true)
   , m_checkD0("checkD0", this, true)
   , m_checkD0Miss("checkD0Miss", this, true)
   , m_checkZ0("checkZ0", this, true)
   , m_checkWeightedMiss("checkWeightedMiss", this, true)
   , m_checkPPerp("checkPPerp", this, true)
   , m_checkPZ("checkPZ", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TracskCollector::event,    Stream::kEvent );
   //bind( &TracskCollector::beginRun, Stream::kBeginRun );
   //bind( &TracskCollector::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TracskCollector::~TracskCollector()                    // anal5
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
TracskCollector::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TracskCollector::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TracskCollector::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_bunchmargin = iHistoManager.histogram(
      10, "bunch margin (best-next)/best", 100, 0., 1.);
   m_nextbig_shower = iHistoManager.histogram(
      20, "second-biggest shower / eBeam", 120, 0., 1.2);
   m_colinearity = iHistoManager.histogram(
      30, "colinearity scaled by eBeam/B", 100, 0., 20.);
   m_bhabha_showers = iHistoManager.histogram(
      33, "number of high-energy showers", 7, -0.5, 6.5);
   m_showers_momentum = iHistoManager.histogram(
      37, "showers momentum sum / 2*eBeam", 100, 0., 0.2);
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
   m_weighted_d0 = iHistoManager.histogram(
      103, "weighted d?0!", 100, 0., 0.006);
   m_weighted_z0 = iHistoManager.histogram(
      107, "weighted z?0!", 100, -0.06, 0.06);
   m_pmag = iHistoManager.histogram(
      110, "(p^track 1! + p^track 2!)?magnitude! / eBeam", 100, 0., 0.2);
   m_pperp = iHistoManager.histogram(
      120, "(p^track 1! + p^track 2!)?perp! / eBeam", 100, 0., 0.2);
   m_pz = iHistoManager.histogram(
      130, "(p^track 1! + p^track 2!)?z! / eBeam", 100, -0.2, 0.2);

   m_bunchmargin_after = iHistoManager.histogram(
      1010, "AFTERCUTS bunch margin (best-next)/best", 100, 0., 1.);
   m_nextbig_shower_after = iHistoManager.histogram(
      1020, "AFTERCUTS second-biggest shower / eBeam", 120, 0., 1.2);
   m_colinearity_after = iHistoManager.histogram(
      1030, "AFTERCUTS colinearity scaled by eBeam/B", 100, 0., 20.);
   m_bhabha_showers_after = iHistoManager.histogram(
      1033, "AFTERCUTS number of high-energy showers", 7, -0.5, 6.5);
   m_showers_momentum_after = iHistoManager.histogram(
      1037, "AFTERCUTS showers momentum sum / 2*eBeam", 100, 0., 0.2);
   m_ntracks_after = iHistoManager.histogram(
      1040, "AFTERCUTS number of seed tracks", 7, -0.5, 6.5);
   m_curvature_sign_after = iHistoManager.histogram(
      1050, "AFTERCUTS [k]?1! * [k]?2! sign", 3, -1.5, 1.5);
   m_fitted_after = iHistoManager.histogram(
      1060, "AFTERCUTS Kalman fit FAILED", 2, -0.5, 1.5);
   m_momentum_after = iHistoManager.histogram(
      1070, "AFTERCUTS Track momentum / eBeam", 120, 0., 1.2);
   m_d0_after = iHistoManager.histogram(
      1080, "AFTERCUTS d?0!", 100, -0.02, 0.02);
   m_d0miss_after = iHistoManager.histogram(
      1090, "AFTERCUTS d?0!^track 1! + d?0!^track 2!", 100, -0.004, 0.004);
   m_z0_after = iHistoManager.histogram(
      1100, "AFTERCUTS z?0!", 100, -0.20, 0.20);
   m_weighted_d0_after = iHistoManager.histogram(
      1103, "AFTERCUTS weighted d?0!", 100, 0., 0.006);
   m_weighted_z0_after = iHistoManager.histogram(
      1107, "AFTERCUTS weighted z?0!", 100, -0.06, 0.06);
   m_pmag_after = iHistoManager.histogram(
      1110, "AFTERCUTS (p^track 1! + p^track 2!)?magnitude! / eBeam", 100, 0., 0.2);
   m_pperp_after = iHistoManager.histogram(
      1120, "AFTERCUTS (p^track 1! + p^track 2!)?perp! / eBeam", 100, 0., 0.2);
   m_pz_after = iHistoManager.histogram(
      1130, "AFTERCUTS (p^track 1! + p^track 2!)?z! / eBeam", 100, -0.2, 0.2);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TracskCollector::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TrackletBunchDecision> bunch_decision;
   extract(iFrame.record(Stream::kEvent), bunch_decision);

   if (bunch_decision->numberOfTestedBunches() < 2) return ActionBase::kFailed;
   double bestbunch = bunch_decision->bestBunchInfo().bweight();
   if (bestbunch <= 0.) return ActionBase::kFailed;
   double nextbunch = bunch_decision->bunchInfo(1).bweight();
   m_bunchmargin->fill((bestbunch-nextbunch)/bestbunch);
   if (m_checkBunch.value()) {
      if ((bestbunch-nextbunch)/bestbunch < 0.6) return ActionBase::kFailed;
   }

   FAItem<BeamEnergy> beam_energy;
   extract(iFrame.record(Stream::kStartRun), beam_energy);

   FAItem<MagneticField> magnetic_field;
   extract(iFrame.record(Stream::kStartRun), magnetic_field);

   // This extraction fails on the second time for some reason...
   FATable<CcShowerAttributes> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<CcShowerAttributes>::const_iterator shower_iter = showers.begin();
   FATable<CcShowerAttributes>::const_iterator shower_end = showers.end();

   int bhabha_showers( 0 );
   Hep3Vector showers_momentum( 0., 0., 0. );

   double biggest_energy = 0.;
   double nextbig_energy = 0.;
   FATable<CcShowerAttributes>::const_iterator biggest;
   FATable<CcShowerAttributes>::const_iterator nextbig;

   for (; shower_iter != shower_end;  ++shower_iter) {
      if (!shower_iter->goodBarrel() &&
	  !shower_iter->goodEndcap()    ) continue;

      if (shower_iter->hot()) continue;

      if (m_checkMIP.value()) {
	 // look out: minimum-ionizing particle, could be a muon!
	 if ( 0.150 < shower_iter->energy()  &&  shower_iter->energy() < 0.270 ) return ActionBase::kFailed;
      }

      if ( 0.270 < shower_iter->energy() ) {
	 bhabha_showers++;
	 showers_momentum += shower_iter->momentum();
      }

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
   if (m_checkSecondBiggest.value()) {
      if (nextbig_energy < 0.5 * beam_energy->value()) return ActionBase::kFailed;
   }

   double lowcut  = 2.3 * ((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.;
   double highcut = 15. * ((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.;
   double colinearity = fabs(M_PI - fabs(biggest->phi() - nextbig->phi()));

   m_colinearity->fill(colinearity / (((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.));
   if (m_checkColinearity.value()) {
      if (colinearity < lowcut  ||  colinearity > highcut) return ActionBase::kFailed;
   }

   m_bhabha_showers->fill(bhabha_showers);
   if (m_checkNumShowers.value()) {
      if ( bhabha_showers != 2 ) return ActionBase::kFailed;
   }
   m_showers_momentum->fill(showers_momentum.mag()/beam_energy->value()/2.);
   if (m_checkShowerMomentum.value()) {
      if ( showers_momentum.mag()/2./beam_energy->value() > 0.1 ) return ActionBase::kFailed;
   }

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

   FATable<NavShower> navshowers;
   extract(iFrame.record(Stream::kEvent), navshowers);

   if (m_checkMatchedShowers.value()) {
      // now you have to do tracking...
      for ( FATable<NavShower>::const_iterator navshower_iter = navshowers.begin();
	    navshower_iter != navshowers.end();
	    navshower_iter++ ) {
	 if ( ! navshower_iter->attributes().hot() ) {
	    // medium-sized showers shouldn't be allowed
	    if ( 0.150 < navshower_iter->attributes().energy()  &&
		 navshower_iter->attributes().energy() < 4.6*beam_energy->value()/5.       ) {
	       return ActionBase::kFailed;
	    }
	    // huge showers shouldn't be allowed
	    else if ( 6.*beam_energy->value()/5. < navshower_iter->attributes().energy() ) {
	       return ActionBase::kFailed;
	    }
	    // little showers can exist, so long as they have no associated tracks
	    else if ( navshower_iter->attributes().energy() < 0.150 ) {
	       if ( navshower_iter->trackMatches().size() != 0 ) return ActionBase::kFailed;
	    }
	    // beam-energy showers should be from the bhabhas
	    else if ( 4.6*beam_energy->value()/5. < navshower_iter->attributes().energy()  &&
		      navshower_iter->attributes().energy() < 6.*beam_energy->value()/5. ) {
	       if ( navshower_iter->trackMatches().size() != 1 ) return ActionBase::kFailed;
	    }
	 }
	 else { // hot shower!
	 }
      }
   }

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);

   FATable<NavTrack>::const_iterator first = tracks.begin();
   FATable<NavTrack>::const_iterator second = first;  ++second;

   m_curvature_sign->fill(first->pionHelix()->curvature() * second->pionHelix()->curvature() > 0.? 1. : -1.);
   if (m_checkOppositeCurvature.value()) {
      if (first->pionHelix()->curvature() * second->pionHelix()->curvature() > 0.) return ActionBase::kFailed;
   }

   m_fitted->fill(!first->pionQuality()->fit()  ||  first->pionQuality()->fitAbort() ? 1. : 0.);
   m_fitted->fill(!second->pionQuality()->fit()  ||  second->pionQuality()->fitAbort() ? 1. : 0.);
   if (m_checkFitAbort.value()) {
      if (!first->pionQuality()->fit()  ||  first->pionQuality()->fitAbort()) return ActionBase::kFailed;
      if (!second->pionQuality()->fit()  ||  second->pionQuality()->fitAbort()) return ActionBase::kFailed;
   }

   m_momentum->fill(first->pionFit()->momentum().mag() / beam_energy->value());
   m_momentum->fill(second->pionFit()->momentum().mag() / beam_energy->value());
   if (m_checkMomentumLow.value()) {
      if (first->pionFit()->momentum().mag() < 0.8 * beam_energy->value()) return ActionBase::kFailed;
      if (second->pionFit()->momentum().mag() < 0.8 * beam_energy->value()) return ActionBase::kFailed;
   }
   if (m_checkMomentumHigh.value()) {
      if (first->pionFit()->momentum().mag() > 1.2 * beam_energy->value()) return ActionBase::kFailed;
      if (second->pionFit()->momentum().mag() > 1.2 * beam_energy->value()) return ActionBase::kFailed;
   }

   m_d0->fill(first->pionHelix()->d0());
   m_d0->fill(second->pionHelix()->d0());
   if (m_checkD0.value()) {
      if (fabs(first->pionHelix()->d0()) > 0.01) return ActionBase::kFailed;
      if (fabs(second->pionHelix()->d0()) > 0.01) return ActionBase::kFailed;
   }

   m_d0miss->fill(first->pionHelix()->d0() + second->pionHelix()->d0());
   if (m_checkD0Miss.value()) {
      if (fabs(first->pionHelix()->d0() + second->pionHelix()->d0()) > 0.002) return ActionBase::kFailed;
   }

   m_z0->fill(first->pionHelix()->z0());
   m_z0->fill(second->pionHelix()->z0());
   if (m_checkZ0.value()) {
      if (fabs(first->pionHelix()->z0()) > 0.10) return ActionBase::kFailed;
      if (fabs(second->pionHelix()->z0()) > 0.10) return ActionBase::kFailed;
   }

   if ( first->pionHelix()->hasNullErrorMatrix()  ||  second->pionHelix()->hasNullErrorMatrix()  ||
	first->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) == 0.             ||
	first->pionHelix()->errorMatrix()( KTHelix::kD0, KTHelix::kD0 ) == 0.             ||
	second->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) == 0.            ||
	second->pionHelix()->errorMatrix()( KTHelix::kD0, KTHelix::kD0 ) == 0.               )
      return ActionBase::kFailed;
   HepSymMatrix first_matrix( first->pionHelix()->errorMatrix() );
   HepSymMatrix second_matrix( first->pionHelix()->errorMatrix() );
   double d0_numer( fabs( first->pionHelix()->d0() ) / first_matrix( KTHelix::kZ0, KTHelix::kZ0 ) +
		    fabs( second->pionHelix()->d0() ) / second_matrix( KTHelix::kZ0, KTHelix::kZ0 ) );
   double d0_denom( 1. / first_matrix( KTHelix::kZ0, KTHelix::kZ0 ) +
		    1. / second_matrix( KTHelix::kZ0, KTHelix::kZ0 )  );
   double z0_numer( first->pionHelix()->z0() / first_matrix( KTHelix::kD0, KTHelix::kD0 ) +
		    second->pionHelix()->z0() / second_matrix( KTHelix::kD0, KTHelix::kD0 ) );
   double z0_denom( 1. / first_matrix( KTHelix::kD0, KTHelix::kD0 ) +
		    1. / second_matrix( KTHelix::kD0, KTHelix::kD0 )  );
   if ( d0_denom == 0.  ||  z0_denom == 0. ) return ActionBase::kFailed;
   m_weighted_d0->fill( d0_numer / d0_denom );
   m_weighted_z0->fill( z0_numer / z0_denom );

   if (m_checkWeightedMiss.value()) {
      if ( fabs( d0_numer / d0_denom ) > 0.003  ||
	   fabs( z0_numer / z0_denom ) > 0.03      ) return ActionBase::kFailed;
   }

   HepVector3D total_momentum(first->pionFit()->momentum() + second->pionFit()->momentum() +
			      HepVector3D(0.013 * beam_energy->value()/5.29, 0, 0));

   m_pmag->fill(total_momentum.mag() / beam_energy->value());
   m_pperp->fill(total_momentum.perp() / beam_energy->value());
   if (m_checkPPerp.value()) {
      if (total_momentum.perp() > 0.1 * beam_energy->value()) return ActionBase::kFailed;
   }

   m_pz->fill(total_momentum.z() / beam_energy->value());
   if (m_checkPZ.value()) {
      if (fabs(total_momentum.z()) > 0.1 * beam_energy->value()) return ActionBase::kFailed;
   }

   m_bunchmargin_after->fill((bestbunch-nextbunch)/bestbunch);
   m_nextbig_shower_after->fill(nextbig_energy/beam_energy->value());
   m_colinearity_after->fill(colinearity / (((5.29/beam_energy->value()) * (fabs(magnetic_field->BField().z())/15.)) * M_PI/180.));
   m_bhabha_showers_after->fill(bhabha_showers);
   m_showers_momentum_after->fill(showers_momentum.mag()/beam_energy->value()/2.);
   m_ntracks_after->fill(seeds.size());
   m_curvature_sign_after->fill(first->pionHelix()->curvature() * second->pionHelix()->curvature() > 0.? 1. : -1.);
   m_fitted_after->fill(!first->pionQuality()->fit()  ||  first->pionQuality()->fitAbort() ? 1. : 0.);
   m_fitted_after->fill(!second->pionQuality()->fit()  ||  second->pionQuality()->fitAbort() ? 1. : 0.);
   m_momentum_after->fill(first->pionFit()->momentum().mag() / beam_energy->value());
   m_momentum_after->fill(second->pionFit()->momentum().mag() / beam_energy->value());
   m_d0_after->fill(first->pionHelix()->d0());
   m_d0_after->fill(second->pionHelix()->d0());
   m_d0miss_after->fill(first->pionHelix()->d0() + second->pionHelix()->d0());
   m_z0_after->fill(first->pionHelix()->z0());
   m_z0_after->fill(second->pionHelix()->z0());
   m_weighted_d0_after->fill( d0_numer / d0_denom );
   m_weighted_z0_after->fill( z0_numer / z0_denom );
   m_pmag_after->fill(total_momentum.mag() / beam_energy->value());
   m_pperp_after->fill(total_momentum.perp() / beam_energy->value());
   m_pz_after->fill(total_momentum.z() / beam_energy->value());

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TracskCollector::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TracskCollector::endRun( Frame& iFrame )         // anal4 equiv.
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
