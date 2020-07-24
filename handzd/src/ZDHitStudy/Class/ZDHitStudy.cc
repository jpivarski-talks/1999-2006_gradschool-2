// -*- C++ -*-
//
// Package:     ZDHitStudy
// Module:      ZDHitStudy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Nov 21 16:09:44 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ZDHitStudy/ZDHitStudy.h"
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
#include "MagField/MagneticField.h"
#include "HelixIntersection/HIMagField.h"
#include "ZDHitStudy/MyDualTrackConstraint.h"
#include "HelixIntersection/HIFitHelix.h"

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
static const char* const kFacilityString = "Processor.ZDHitStudy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ZDHitStudy::ZDHitStudy( void )               // anal1
   : Processor( "ZDHitStudy" )
   , m_correctD0("correctD0", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ZDHitStudy::event,    Stream::kEvent );
   //bind( &ZDHitStudy::beginRun, Stream::kBeginRun );
   //bind( &ZDHitStudy::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ZDHitStudy::~ZDHitStudy()                    // anal5
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
ZDHitStudy::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ZDHitStudy::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ZDHitStudy::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

//    const char* label[kNumEntries] = {
//       "pperp", "pz", "curv", "phi0", "d0", "cotTheta", "z0",
//       "layer", "wire", "refx", "refy", "refz",
//       "hphi", "hz", "wirex", "wirey", "wirez", "dca", "drift",
//       "dualchi2"};
//    m_ntuple = iHistoManager.ntuple(
//       1, "vars", kNumEntries, 262144, label);

   const char* eventlabel[kNumEventEntries] = {
      "dualchi2",
      "d0", "z0", "px", "py", "pz",
      "ed0", "ez0", "epx", "epy", "epz",
      "ad0", "az0", "apx", "apy", "apz"};
   m_eventntuple = iHistoManager.ntuple(
      2, "vars", kNumEventEntries, 262144, eventlabel);

   m_00 = iHistoManager.profile(
      101, "(-2.0,-1.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_01 = iHistoManager.profile(
      102, "(-1.8,-1.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_02 = iHistoManager.profile(
      103, "(-1.6,-1.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_03 = iHistoManager.profile(
      104, "(-1.4,-1.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_04 = iHistoManager.profile(
      105, "(-1.2,-1.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_05 = iHistoManager.profile(
      106, "(-1.0,-0.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_06 = iHistoManager.profile(
      107, "(-0.8,-0.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_07 = iHistoManager.profile(
      108, "(-0.6,-0.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_08 = iHistoManager.profile(
      109, "(-0.4,-0.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_09 = iHistoManager.profile(
      110, "(-0.2, 0.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_10 = iHistoManager.profile(
      111, "( 0.0, 0.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_11 = iHistoManager.profile(
      112, "( 0.2, 0.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_12 = iHistoManager.profile(
      113, "( 0.4, 0.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_13 = iHistoManager.profile(
      114, "( 0.6, 0.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_14 = iHistoManager.profile(
      115, "( 0.8, 1.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_15 = iHistoManager.profile(
      116, "( 1.0, 1.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_16 = iHistoManager.profile(
      117, "( 1.2, 1.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_17 = iHistoManager.profile(
      118, "( 1.4, 1.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_18 = iHistoManager.profile(
      119, "( 1.6, 1.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_19 = iHistoManager.profile(
      120, "( 1.8, 2.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);

   m_ct_00 = iHistoManager.histogram(121, "(-2.0,-1.8)", 500, -2., 2.);
   m_ct_01 = iHistoManager.histogram(122, "(-1.8,-1.6)", 500, -2., 2.);
   m_ct_02 = iHistoManager.histogram(123, "(-1.6,-1.4)", 500, -2., 2.);
   m_ct_03 = iHistoManager.histogram(124, "(-1.4,-1.2)", 500, -2., 2.);
   m_ct_04 = iHistoManager.histogram(125, "(-1.2,-1.0)", 500, -2., 2.);
   m_ct_05 = iHistoManager.histogram(126, "(-1.0,-0.8)", 500, -2., 2.);
   m_ct_06 = iHistoManager.histogram(127, "(-0.8,-0.6)", 500, -2., 2.);
   m_ct_07 = iHistoManager.histogram(128, "(-0.6,-0.4)", 500, -2., 2.);
   m_ct_08 = iHistoManager.histogram(129, "(-0.4,-0.2)", 500, -2., 2.);
   m_ct_09 = iHistoManager.histogram(130, "(-0.2, 0.0)", 500, -2., 2.);
   m_ct_10 = iHistoManager.histogram(131, "( 0.0, 0.2)", 500, -2., 2.);
   m_ct_11 = iHistoManager.histogram(132, "( 0.2, 0.4)", 500, -2., 2.);
   m_ct_12 = iHistoManager.histogram(133, "( 0.4, 0.6)", 500, -2., 2.);
   m_ct_13 = iHistoManager.histogram(134, "( 0.6, 0.8)", 500, -2., 2.);
   m_ct_14 = iHistoManager.histogram(135, "( 0.8, 1.0)", 500, -2., 2.);
   m_ct_15 = iHistoManager.histogram(136, "( 1.0, 1.2)", 500, -2., 2.);
   m_ct_16 = iHistoManager.histogram(137, "( 1.2, 1.4)", 500, -2., 2.);
   m_ct_17 = iHistoManager.histogram(138, "( 1.4, 1.6)", 500, -2., 2.);
   m_ct_18 = iHistoManager.histogram(139, "( 1.6, 1.8)", 500, -2., 2.);
   m_ct_19 = iHistoManager.histogram(140, "( 1.8, 2.0)", 500, -2., 2.);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ZDHitStudy::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<CalibratedZDHit> zdhits;
   extract(iFrame.record(Stream::kEvent), zdhits);

   FAItem<ZDHitCorrector> zdcorrector;
   extract(iFrame.record(Stream::kStartRun), zdcorrector);

   FAItem<AZDSenseWireStore> zdstore;
   extract(iFrame.record(Stream::kZDAlignment), zdstore);

   DGMaterialStore materials;
   extract(iFrame.record(Stream::kMaterial), materials);
   const DGConstMaterialPtr& zdGas = materials[kZDGasWireVaporMatID];

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();

   HepVector3D tracks_momentum(0.015, 0., 0.);
   for (; track_iter != track_end;  ++track_iter) {
      tracks_momentum += track_iter->pionFit()->momentum();
   }

   FAItem<MagneticField>  magnetic_field;
   extract(iFrame.record(Stream::kStartRun), magnetic_field);
   HIMagField::instance()->setBfield(magnetic_field->BField().z());

//    FAItem<BeamEnergy> beam_energy;
//    extract(iFrame.record(Stream::kStartRun), beam_energy);

   assert(tracks.size() == 2);
   FATable<NavTrack>::const_iterator positive, negative;
   positive = tracks.begin();
   if (positive->pionHelix()->curvature() < 0.) {
      ++positive;
      negative = tracks.begin();
   }
   else {
      negative = tracks.begin();
      ++negative;
   }
   assert(positive->pionHelix()->curvature() > 0.);
   assert(negative->pionHelix()->curvature() < 0.);

   HIFitHelix helix_pos(*(positive->pionHelix()));
   HIFitHelix helix_neg(*(negative->pionHelix()));
   helix_pos.setIdentifier(positive->identifier());
   helix_neg.setIdentifier(negative->identifier());
   vector<HIFitHelix*> helix_vector;
   helix_vector.push_back(&helix_pos);
   helix_vector.push_back(&helix_neg);

   if (m_correctD0.value()) {
      helix_pos.setD0(helix_pos.d0() -
		      (-0.0000155735
		       - 0.0000275939*helix_pos.cotTheta()
		       - 9.06903E-6*sqr(helix_pos.cotTheta())
		       - 6.00561E-6*pow(helix_pos.cotTheta(), 3.))
		      * sin(2.*helix_pos.phi0())/2.);
      helix_neg.setD0(helix_neg.d0() -
		      (-0.0000155735
		       + 0.0000275939*helix_neg.cotTheta()
		       - 9.06903E-6*sqr(helix_neg.cotTheta())
		       + 6.00561E-6*pow(helix_neg.cotTheta(), 3.))
		      * sin(2.*helix_neg.phi0())/2.);
   }

   double phipos = helix_pos.phi0();
   double cTpos = helix_pos.cotTheta();
   double d0miss = helix_pos.d0() + helix_neg.d0();

   if (cTpos < -2.0) ;
   else if (cTpos < -1.8) { m_00->fill(phipos, d0miss);  m_ct_00->fill(cTpos); }
   else if (cTpos < -1.6) { m_01->fill(phipos, d0miss);  m_ct_01->fill(cTpos); }
   else if (cTpos < -1.4) { m_02->fill(phipos, d0miss);  m_ct_02->fill(cTpos); }
   else if (cTpos < -1.2) { m_03->fill(phipos, d0miss);  m_ct_03->fill(cTpos); }
   else if (cTpos < -1.0) { m_04->fill(phipos, d0miss);  m_ct_04->fill(cTpos); }
   else if (cTpos < -0.8) { m_05->fill(phipos, d0miss);  m_ct_05->fill(cTpos); }
   else if (cTpos < -0.6) { m_06->fill(phipos, d0miss);  m_ct_06->fill(cTpos); }
   else if (cTpos < -0.4) { m_07->fill(phipos, d0miss);  m_ct_07->fill(cTpos); }
   else if (cTpos < -0.2) { m_08->fill(phipos, d0miss);  m_ct_08->fill(cTpos); }
   else if (cTpos <  0.0) { m_09->fill(phipos, d0miss);  m_ct_09->fill(cTpos); }
   else if (cTpos <  0.2) { m_10->fill(phipos, d0miss);  m_ct_10->fill(cTpos); }
   else if (cTpos <  0.4) { m_11->fill(phipos, d0miss);  m_ct_11->fill(cTpos); }
   else if (cTpos <  0.6) { m_12->fill(phipos, d0miss);  m_ct_12->fill(cTpos); }
   else if (cTpos <  0.8) { m_13->fill(phipos, d0miss);  m_ct_13->fill(cTpos); }
   else if (cTpos <  1.0) { m_14->fill(phipos, d0miss);  m_ct_14->fill(cTpos); }
   else if (cTpos <  1.2) { m_15->fill(phipos, d0miss);  m_ct_15->fill(cTpos); }
   else if (cTpos <  1.4) { m_16->fill(phipos, d0miss);  m_ct_16->fill(cTpos); }
   else if (cTpos <  1.6) { m_17->fill(phipos, d0miss);  m_ct_17->fill(cTpos); }
   else if (cTpos <  1.8) { m_18->fill(phipos, d0miss);  m_ct_18->fill(cTpos); }
   else if (cTpos <  2.0) { m_19->fill(phipos, d0miss);  m_ct_19->fill(cTpos); }

   MyDualTrackConstraint constraint(true,
				    true,
				    magnetic_field->BField().z(),
 				    HepVector3D(-0.015, 0., 0.));
   HepVector equations = constraint.constraint(helix_vector);
   HepMatrix derivatives = constraint.constraintDerivatives(helix_vector);
   HepMatrix errorMatrix(2*HIHelix::kNTrackParameters, 2*HIHelix::kNTrackParameters, 0);
   errorMatrix.sub(1,                            1,                            helix_pos.errorMatrix());
   errorMatrix.sub(1+HIHelix::kNTrackParameters, 1+HIHelix::kNTrackParameters, helix_neg.errorMatrix());

   float u[kNumEventEntries];
   u[kD0] = equations[0 + MyDualTrackConstraint::kD0];
   u[kZ0] = equations[0 + MyDualTrackConstraint::kZ0];
   u[kPX] = equations[2 + MyDualTrackConstraint::kPx];
   u[kPY] = equations[2 + MyDualTrackConstraint::kPy];
   u[kPZ] = equations[2 + MyDualTrackConstraint::kPz];

   HepMatrix d0derivs = derivatives.sub(1, 2*HIHelix::kNTrackParameters, 1 + MyDualTrackConstraint::kD0, 1 + MyDualTrackConstraint::kD0);
   HepMatrix z0derivs = derivatives.sub(1, 2*HIHelix::kNTrackParameters, 1 + MyDualTrackConstraint::kZ0, 1 + MyDualTrackConstraint::kZ0);
   HepMatrix pxderivs = derivatives.sub(1, 2*HIHelix::kNTrackParameters, 3 + MyDualTrackConstraint::kPx, 3 + MyDualTrackConstraint::kPx);
   HepMatrix pyderivs = derivatives.sub(1, 2*HIHelix::kNTrackParameters, 3 + MyDualTrackConstraint::kPy, 3 + MyDualTrackConstraint::kPy);
   HepMatrix pzderivs = derivatives.sub(1, 2*HIHelix::kNTrackParameters, 3 + MyDualTrackConstraint::kPz, 3 + MyDualTrackConstraint::kPz);

   u[kED0] = (d0derivs.T() * errorMatrix * d0derivs)(1,1);
   u[kEZ0] = (z0derivs.T() * errorMatrix * z0derivs)(1,1);
   u[kEPX] = (pxderivs.T() * errorMatrix * pxderivs)(1,1);
   u[kEPY] = (pyderivs.T() * errorMatrix * pyderivs)(1,1);
   u[kEPZ] = (pzderivs.T() * errorMatrix * pzderivs)(1,1);

   HIFitConstraint::Results results = constraint.applyConstraint(helix_vector);
   HepVector newequations = constraint.constraint(helix_vector);

//    double dualchi2 = results.chisq()/results.ndof();
   u[kChi2] = results.chisq()/results.ndof();

   u[kAD0] = newequations[0 + MyDualTrackConstraint::kD0];
   u[kAZ0] = newequations[0 + MyDualTrackConstraint::kZ0];
   u[kAPX] = newequations[2 + MyDualTrackConstraint::kPx];
   u[kAPY] = newequations[2 + MyDualTrackConstraint::kPy];
   u[kAPZ] = newequations[2 + MyDualTrackConstraint::kPz];

   m_eventntuple->fill(u);

//    for (vector<HIFitHelix*>::const_iterator dual_iter = helix_vector.begin();
// 	dual_iter != helix_vector.end();
// 	++dual_iter) {
//       track_iter = tracks.find((**dual_iter).identifier());
//       HIHelix helix(**dual_iter);

//       double curv = helix.curvature();
//       double phi0 = helix.phi0();
//       double d0 = helix.d0();
//       double cotTheta = helix.cotTheta();
//       double z0 = helix.z0();

//       const NavTrack::SeedZDHitLinkTable* zdlinks = track_iter->seedZDHitLinks();
//       NavTrack::SeedZDHitLinkTable::const_iterator zdlink_iter = zdlinks->begin();
//       NavTrack::SeedZDHitLinkTable::const_iterator zdlink_end = zdlinks->end();

//       double zdcharge_sum = 0;
//       unsigned int zdcharge_N = 0;
//       for (; zdlink_iter != zdlink_end;  ++zdlink_iter) {
// 	 if ((**zdlink_iter).linkData().fitFlag() == SeedZDHitLink::kFITTABLE) {
// 	    assert(*(**zdlink_iter).rightID());
// 	    FATable<CalibratedZDHit>::const_iterator zdhit_iter = zdhits.find(*(**zdlink_iter).rightID());
// 	    zdcharge_sum += zdhit_iter->charge();
// 	    zdcharge_N++;
// 	 }
//       }

//       for (zdlink_iter = zdlinks->begin();  zdlink_iter != zdlink_end;  ++zdlink_iter) {
// 	 if ((**zdlink_iter).linkData().fitFlag() != SeedZDHitLink::kFITTABLE) continue;

// 	 assert(*(**zdlink_iter).rightID());
// 	 FATable<CalibratedZDHit>::const_iterator zdhit_iter = zdhits.find(*(**zdlink_iter).rightID());
	    
// 	 const AEWireLayerCylindrical& ae_layer = zdstore->layer(zdhit_iter->layer());
// 	 const AEWireInfo& ae_wire = ae_layer.wire(zdhit_iter->wireInLyr());

// 	 vector<HIIntersectionSurface*> surface;
// 	 surface.push_back(new HISingleWireCylinder(
// 			      zdGas, zdGas,
// 			      ae_layer,
// 			      zdhit_iter->layer(),
// 			      DGTransform::Identity,
// 			      NULL, NULL,
// 			      &*zdhit_iter,
// 			      (**zdlink_iter).linkData().signedDriftDistance(),
// 			      &*zdcorrector,
// 			      false,
// 			      zdcharge_sum / double(zdcharge_N)
// 			      ));
// // 	 (**surface.begin()).setPrintDiagnostics(true);
// 	 helix.moveToRadius(zdstore->layer(zdhit_iter->layer()).radius());
// 	 HIHelixIntersector intersector(surface,
// 					HIHelixIntersector::kOrderAsGiven,
// 					&helix);
// 	 HIHelixIntersector::IntersectionStatus status =
// 	    intersector.swimToCurrentSurface(KTMoveControl::kDirectionEither);
// 	 if (status != HIHelixIntersector::kIntersectionOK) {
// 	    report(WARNING, kFacilityString)
// 	       << "Wire swimmin' failed with " << status << " ("
// 	       << HIHelixIntersector::kHelixTransportError << "=kHelixTransportError, "
// 	       << HIHelixIntersector::kGlobalOperationError << "=kGlobalOperationError, " 
// 	       << HIHelixIntersector::kSurfaceOperationError << "=kSurfaceOperationError, " 
// 	       << HIHelixIntersector::kNoIntersection << "=kNoIntersection, " 
// 	       << HIHelixIntersector::kNoMoreSurfaces << "=kNoMoreSurfaces)" << endl;
// 	    continue;
// 	 }
// 	 intersector.currentSurface()->hiCalibratedHit()->applyTrackCorrections(helix);
	 
// 	 float v[kNumEntries];
// 	 v[kPPerp] = tracks_momentum.perp();
// 	 v[kPZ] = tracks_momentum.z();
// 	 v[kCurv] = curv;
// 	 v[kPhi0] = phi0;
// 	 v[kD0] = d0;
// 	 v[kCotTheta] = cotTheta;
// 	 v[kZ0] = z0;
// 	 v[kLayer] = zdhit_iter->layer();
// 	 v[kWire] = zdhit_iter->wireInLyr();
// 	 v[kRefX] = helix.position().x();
// 	 v[kRefY] = helix.position().y();
// 	 v[kRefZ] = helix.position().z();
// 	 v[kHelixPhi] = helix.phi0();
// 	 v[kHelixZ] = helix.z0();
// 	 v[kDualChi2] = dualchi2;

// 	 if (true) {
// 	    AEWireInfo::WireDirZ pointW = ae_wire.zPoint(helix.position().z());
// 	    double xP = helix.position().x();
// 	    double yP = helix.position().y();
// 	    double zP = helix.position().z();
// 	    double xw = pointW.first.x();
// 	    double yw = pointW.first.y();
// 	    double zw = pointW.first.z();
// 	    double dirx=pointW.second.x();
// 	    double diry=pointW.second.y();
// 	    double dirz=pointW.second.z();

// 	    double zmin = (dirx*(xP-xw) + diry*(yP-yw))*dirz +zP;
// 	    double xmin = xw +dirx*(zmin-zw)/dirz;
// 	    double ymin = yw +diry*(zmin-zw)/dirz;

// 	    v[kWireX] = xmin;
// 	    v[kWireY] = ymin;
// 	    v[kWireZ] = zmin;
// 	 }

// 	 v[kDCA] = intersector.currentSurface()->dca(helix);
// 	 v[kDrift] = ((HICalibratedWireHit*)
// 		      intersector.currentSurface()->hiCalibratedHit())->signedDriftDistance();
// 	 m_ntuple->fill(v);

// 	 delete *surface.begin();
//       } // end ZD hit link loop
//    } // end track loop

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ZDHitStudy::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ZDHitStudy::endRun( Frame& iFrame )         // anal4 equiv.
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
