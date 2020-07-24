// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentFcn
// 
// Description: see ZDAlignmentMod.cc
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 15:26:49 EST 2003
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"
#include "ZDAlignmentMod/ZDAlignmentFcn.h"
#include "DataHandler/Stream.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/extract.h"
#include "DataHandler/Frame.h"

#include "DetectorGeometry/DGDetectorStore.h"
#include "DetectorGeometry/DGPath.h"
#include "DetectorGeometry/DGConstVolumePtr.h"
#include "DetectorGeometry/DGVolume.h"
#include "DetectorGeometry/DGConstPlacedVolumePtr.h"
#include "DetectorGeometry/DGPlacedVolume.h"
#include "DetectorGeometry/DGMaterialStore.h"
#include "MaterialDelivery/material_identifiers.h"

#include "HelixIntersection/HIZDSurfaceFactory.h"
#include "HelixIntersection/HIWireLayerCylinder.h"
#include "HelixIntersection/HISingleWireCylinder.h"
#include "HelixIntersection/HIMultiWireCylinder.h"
#include "HelixIntersection/HIZBoundaryCondition.h"
#include "HelixIntersection/HIHelixIntersector.h"
#include "HelixIntersection/HIIntersectionSurface.h"
#include "HelixIntersection/HICalibratedWireHit.h"
#include "HelixIntersection/HICalibratedWireHit.h"

#include "JobControl/JobControl.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <stdio.h>
#include <fstream.h>
#include <iostream.h>

// user include files
//#include "Experiment/report.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "ZDAlignmentMod.ZDAlignmentFcn" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

static int argc = 1;
static char* argv[] = {"HistogramViewer"};

//
// constructors and destructor
//
ZDAlignmentFcn::ZDAlignmentFcn(CLEOConstantsModifiable<DBZDGeomAlignment>* geometry,
			       CLEOConstantsModifiable<DBAZDGeomLayer>* geomlayer)
   : MIFcn()
   , m_geometry(geometry)
   , m_geomlayer(geomlayer)
   , m_histman(NULL)
   , m_qapplication(NULL)
   , m_hvp_window(NULL)
   , m_best_yet(1000.)
{
   addInitialParameter("x", 0., 0.1, -10., 10.);              // from best.zdgeomalignment
   addInitialParameter("y", 0., 0.1, -10., 10.);              // from best.zdgeomalignment
   addInitialParameter("z", 0., 0.1, -10., 10.);              // from best.zdgeomalignment
   addInitialParameter("rotx", 0., 0.1, -10., 10.);           // from best.zdgeomalignment
   addInitialParameter("roty", 0., 0.1, -10., 10.);           // from best.zdgeomalignment
   addInitialParameter("rotz", 0., 0.1, -10., 10.);           // from best.zdgeomalignment
   addInitialParameter("t0", 1.7168, 1., -100., 100.);
   addInitialParameter("drift", 29.920, 1., 0., 150.);
   addInitialParameter("radius", 0., 0.01, -1., 1.);
   addInitialParameter("del_rad_45", 0., 0.001, -1., 1.);
   addInitialParameter("sagx", 0., 10., -1000., 1000.);
   addInitialParameter("sagy", 0., 10., -1000., 1000.);       // sorta-optimized was 90.8272 um
   addInitialParameter("twistWest", 0., 0.1, -10., 10.);      // from best.zdgeomalignment
}

// ZDAlignmentFcn::ZDAlignmentFcn( const ZDAlignmentFcn& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ZDAlignmentFcn::~ZDAlignmentFcn()
{
}

//
// assignment operators
//
// const ZDAlignmentFcn& ZDAlignmentFcn::operator=( const ZDAlignmentFcn& rhs )
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

void ZDAlignmentFcn::book(bool show_plots, bool fake_driftfunction)
{
   m_show_plots = show_plots;
   m_fake_driftfunction = fake_driftfunction;

   if (m_histman == NULL) {
      for (int i = 0;  i < 6;  i++) {
	 m_original_radius[i] = (*m_geomlayer)[i].get_RadiusEndCapCM();
      }

      JobControl* job_control = JobControl::instance();
      m_histman = job_control->histogramManagerP();

      m_resid_Vdrift = m_histman->profile  (1, "V ndrift", 30, -1.0, 1.0, -3., 3., HIHistProf::kErrorOnMean);
      m_resid_Vlayer = m_histman->profile  (2, "V layer", 6, 0.5, 6.5, -3., 3., HIHistProf::kErrorOnMean);
      m_resid_Vcotth = m_histman->profile  (3, "V cotTheta", 50, -2., 2., -3., 3., HIHistProf::kErrorOnMean);
      m_resid_Vphi_m = m_histman->profile  (4, "V phi (-theta)", 8, 0., 2.*M_PI, -3., 3., HIHistProf::kErrorOnMean);
      m_resid_Vphi_z = m_histman->profile  (5, "V phi (0theta)", 8, 0., 2.*M_PI, -3., 3., HIHistProf::kErrorOnMean);
      m_resid_Vphi_p = m_histman->profile  (6, "V phi (+theta)", 8, 0., 2.*M_PI, -3., 3., HIHistProf::kErrorOnMean);
      m_resid = m_histman->histogram(7, "resid", 100, -3., 3.);

      if (m_show_plots) {
	 m_qapplication = new QApplication(argc, &(argv[0]));
	 m_hvp_window = new HVPWindow(m_histman);

	 if (m_qapplication->mainWidget() == NULL) {
	    m_qapplication->setMainWidget(m_hvp_window);
	    m_hvp_window->show();
	 }
	 m_qapplication->exec();
	 m_hvp_window->updateInfo();
	 QTimer::singleShot(0, m_qapplication, SLOT(quit()));
	 m_qapplication->exec();
      } // end if show plots
   } // end if this is the first time through
}

void ZDAlignmentFcn::reset(const FIFrameIterator& frame)
{
   m_frame = &frame;

   vector<HIHelix*>::const_iterator track_end = m_track.end();
   for (vector<HIHelix*>::const_iterator track_iter = m_track.begin();
	track_iter != track_end;
	++track_iter) {
      delete *track_iter;
   }
   m_track.clear();

   m_charge.clear();

   vector<vector<CalibratedZDHit*>*>::const_iterator vect_end = m_vect.end();
   for (vector<vector<CalibratedZDHit*>*>::const_iterator vect_iter = m_vect.begin();
	vect_iter != vect_end;
	++vect_iter) {
      vector<CalibratedZDHit*>::const_iterator hit_end = (**vect_iter).end();
      for (vector<CalibratedZDHit*>::const_iterator hit_iter = (**vect_iter).begin();
	   hit_iter != hit_end;
	   ++hit_iter) {
	 delete *hit_iter;
      }

      delete *vect_iter;
   }
   m_vect.clear();

   vector<vector<double>*>::const_iterator drifts_end = m_drifts.end();
   for (vector<vector<double>*>::const_iterator drifts_iter = m_drifts.begin();
	drifts_iter != drifts_end;
	++drifts_iter) {
      delete *drifts_iter;
   }
   m_drifts.clear();
}

bool ZDAlignmentFcn::fill(const KTHelix& track, const double charge, const vector<const CalibratedZDHit*>& hits, const vector<double>& drifts)
{
   assert(hits.size() == drifts.size());

   HIHelix* p_track = new HIHelix(track);
   if (p_track == NULL) return false;

   vector<CalibratedZDHit*>* p_vect = new vector<CalibratedZDHit*>;
   if (p_vect == NULL) return false;

   vector<const CalibratedZDHit*>::const_iterator hits_end = hits.end();
   for (vector<const CalibratedZDHit*>::const_iterator hits_iter = hits.begin();
	hits_iter != hits_end;
	++hits_iter) {

      CalibratedZDHit* p_hit = new CalibratedZDHit(**hits_iter);
      if (p_hit == NULL) return false;

      p_vect->push_back(p_hit);
   }

   vector<double>* p_drifts = new vector<double>;
   if (p_drifts == NULL) return false;

   vector<double>::const_iterator drifts_end = drifts.end();
   for (vector<double>::const_iterator drifts_iter = drifts.begin();
	drifts_iter != drifts_end;
	++drifts_iter) {
      p_drifts->push_back(*drifts_iter);
   }

   m_track.push_back(p_track);
   m_charge.push_back(charge);
   m_vect.push_back(p_vect);
   m_drifts.push_back(p_drifts);

   return true;
}

double ZDAlignmentFcn::iterate(double* v)
{
   (*m_geometry)[0].set_deltaX(v[kX]/1000.);
   (*m_geometry)[0].set_deltaY(v[kY]/1000.);
   (*m_geometry)[0].set_deltaZ(v[kZ]/1000.);
   (*m_geometry)[0].set_rotX(v[kRotX]/1000.);
   (*m_geometry)[0].set_rotY(v[kRotY]/1000.);
   (*m_geometry)[0].set_rotZ(v[kRotZ]/1000.);

   (*m_geometry)[2].set_rotZ(v[kTwistWest]/1000.);

   double t0 = v[kT0];
   double speed = v[kSpeed];

   int i;
   for (i = 0;  i < 3;  i++) {
      (*m_geomlayer)[i].set_RadiusEndCapCM(m_original_radius[i] + v[kShift]);
      (*m_geomlayer)[i].set_SagXMicron(v[kSagX]);
      (*m_geomlayer)[i].set_SagYMicron(v[kSagY]);
   }
   for (i = 3;  i < 6;  i++) {
      (*m_geomlayer)[i].set_RadiusEndCapCM(m_original_radius[i] + v[kShift] + v[kDelShiftL45]);
      (*m_geomlayer)[i].set_SagXMicron(v[kSagX]);
      (*m_geomlayer)[i].set_SagYMicron(v[kSagY]);
   }
   
   cout << "TESTALIGNMENT "
	<< (*m_geometry)[0].get_deltaX()*1000. << " "
	<< (*m_geometry)[0].get_deltaY()*1000. << " "
	<< (*m_geometry)[0].get_deltaZ()*1000. << " "
	<< (*m_geometry)[0].get_rotX()*1000. << " "
	<< (*m_geometry)[0].get_rotY()*1000. << " "
	<< (*m_geometry)[0].get_rotZ()*1000. << " with ";
   if (m_fake_driftfunction) cout << " (t + " << t0 << ")ns * " << speed << "um/ns and ";
   cout << v[kShift] << "cm radial and " << v[kSagX] << "," << v[kSagY] << "um sag and "
	<< v[kTwistWest] << "mrad west twist" << endl;

   if (true) {
      ofstream state("state.zdgeomalignment");
      state << "1 0 0 0 0 0 1 5 DEFAULT" << endl;
      state << "3" << endl;
      for (int i = 0;  i < 3;  i++) {
	 state << i+1 << " "
	       << (*m_geometry)[i].get_deltaX() << " "
	       << (*m_geometry)[i].get_deltaY() << " "
	       << (*m_geometry)[i].get_deltaZ() << " "
	       << (*m_geometry)[i].get_rotX() << " "
	       << (*m_geometry)[i].get_rotY() << " "
	       << (*m_geometry)[i].get_rotZ() << endl;
      }
      ofstream pars("state.pars");
      for (int j = kT0;  j < kNumParams;  j++) pars << "set par " << j << " " << v[j] << endl;
   }

   FIFrameIterator itFrame = *m_frame;  // this is what updates the geometry
   
   FAItem<ZDHitCorrector> corrector;
   extract(itFrame->record(Stream::kStartRun), corrector);

   FAItem<AZDSenseWireStore> store;
   extract(itFrame->record(Stream::kZDAlignment), store);

   DGMaterialStore materials;
   extract(itFrame->record(Stream::kMaterial), materials);
   const DGConstMaterialPtr& zdGas = materials[kZDGasWireVaporMatID];

   vector<HIHelix*>::const_iterator track_iter = m_track.begin();
   vector<HIHelix*>::const_iterator track_end = m_track.end();
   vector<double>::const_iterator charge_iter = m_charge.begin();
   vector<double>::const_iterator charge_end = m_charge.end();
   vector<vector<CalibratedZDHit*>*>::const_iterator vect_iter = m_vect.begin();
   vector<vector<CalibratedZDHit*>*>::const_iterator vect_end = m_vect.end();
   vector<vector<double>*>::const_iterator drifts_iter = m_drifts.begin();
   vector<vector<double>*>::const_iterator drifts_end = m_drifts.end();

   m_resid_Vdrift->reset();
   m_resid_Vlayer->reset();
   m_resid_Vcotth->reset();
   m_resid_Vphi_m->reset();
   m_resid_Vphi_z->reset();
   m_resid_Vphi_p->reset();
   m_resid->reset();

   double residual2_sum = 0.;
   int residual_N = 0;

   while (track_iter != track_end) {
      assert(charge_iter != charge_end);  // these should be synchronized
      assert(vect_iter != vect_end);
      assert(drifts_iter != drifts_end);

      HIHelix helix(**track_iter);
      double cotTheta = (**track_iter).cotTheta();

      vector<CalibratedZDHit*>::const_iterator hit_iter = (**vect_iter).begin();
      vector<CalibratedZDHit*>::const_iterator hit_end = (**vect_iter).end();
      vector<double>::const_iterator drift_iter = (**drifts_iter).begin();
      vector<double>::const_iterator drift_end = (**drifts_iter).end();
      while (hit_iter != hit_end) {
	 assert(drift_iter != drift_end);  // these should be synchronized

	 int layer = (**hit_iter).layer();
	 int wire = (**hit_iter).wireInLyr();
	 if ((layer == 4  &&  (wire == 1   ||
			       wire == 5   ||
			       wire == 6   ||
			       wire == 8   ||
			       wire == 27  ||
			       wire == 31  ||
			       wire == 43    ))  ||
	     (layer == 5  &&  (wire == 19  ||
			       wire == 54    ))  ||
	     (layer == 6  &&  (wire == 11    ))    ) {
	    ++hit_iter;  ++drift_iter;
	    continue;
	 }

	 // HIHelixIntersector doesn't have much overhead: go ahead
	 // and make a new one for each hit
	 vector<HIIntersectionSurface*> surface;
	 surface.push_back(new HISingleWireCylinder(
			      zdGas, zdGas,
			      store->layer((**hit_iter).layer()),
			      (**hit_iter).layer(),
			      DGTransform::Identity,
			      NULL, NULL,
			      *hit_iter,
			      *drift_iter,
 			      &*corrector,
			      false,
			      *charge_iter
			      ));
	 helix.moveToRadius(store->layer((**hit_iter).layer()).radius());
	 HIHelixIntersector intersector(surface,
					HIHelixIntersector::kOrderAsGiven,
					&helix);
	 intersector.swimToCurrentSurface(KTMoveControl::kDirectionEither);
	 intersector.currentSurface()->hiCalibratedHit()->applyTrackCorrections(helix);

	 double phi = helix.phi0();
	 double z = helix.position().z();
	 double dca = intersector.currentSurface()->dca(helix);
	 double drift = ((HICalibratedWireHit*)
			 intersector.currentSurface()->hiCalibratedHit())->signedDriftDistance();
	 if (m_fake_driftfunction) drift = ((**hit_iter).time()/1000. + t0) * speed*1e-6;
	 double residual = 1000.*(drift - dca);  // residual is in mm

	 const double layer_cells = double(store->numberOfWiresLyr(layer));
	 const double layer_radius = store->radiusNominal(layer);
	 double norm_drift = drift * layer_cells / (M_PI * layer_radius);

	 if (fabs(cotTheta) < 2.) residual2_sum += sqr(residual);  residual_N++;

	 m_resid_Vdrift->fill(norm_drift, residual);
	 m_resid_Vlayer->fill(layer, residual);
	 m_resid_Vcotth->fill(cotTheta, residual);
	 if      (cotTheta < -2.0) ;
	 else if (cotTheta < -1.4) m_resid_Vphi_m->fill(phi, residual);
	 else if (cotTheta <  1.4) m_resid_Vphi_z->fill(phi, residual);
	 else if (cotTheta <  2.0) m_resid_Vphi_p->fill(phi, residual);
	 else                      ;
	 m_resid->fill(residual);

	 delete *surface.begin();

	 ++hit_iter;  ++drift_iter;
      } // end foreach hit
      ++track_iter;  ++charge_iter;  ++vect_iter;  ++drifts_iter;
   } // end foreach track

   if (m_show_plots) {
      if (m_qapplication->mainWidget() == NULL) {
	 m_qapplication->setMainWidget(m_hvp_window);
	 m_hvp_window->show();
      }
      m_hvp_window->updateInfo();
      QTimer::singleShot(0, m_qapplication, SLOT(quit()));
      m_qapplication->exec();
   }

   double residual_rms = 1000.;
   if (residual_N > 0) residual_rms = sqrt(residual2_sum / double(residual_N));
   if (residual_rms < m_best_yet) {
      m_best_yet = residual_rms;

      ofstream best("best.zdgeomalignment");
      best << "1 0 0 0 0 0 1 5 DEFAULT" << endl;
      best << "3" << endl;
      for (int i = 0;  i < 3;  i++) {
	 best << i+1 << " "
	      << (*m_geometry)[i].get_deltaX() << " "
	      << (*m_geometry)[i].get_deltaY() << " "
	      << (*m_geometry)[i].get_deltaZ() << " "
	      << (*m_geometry)[i].get_rotX() << " "
	      << (*m_geometry)[i].get_rotY() << " "
	      << (*m_geometry)[i].get_rotZ() << endl;
      }
      ofstream pars("best.pars");
      for (int j = 0;  j < kNumParams;  j++) pars << "set par " << j << " " << v[j] << endl;
   }

   return residual_rms;
}

//
// const member functions
//

//
// static member functions
//
