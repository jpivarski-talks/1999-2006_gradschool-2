// -*- C++ -*-
//
// Package:     Clean
// Module:      Clean
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Thu Mar  3 14:17:35 EST 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Clean/Clean.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "LCDRootAccess/Vector.h"
#include "KinematicTrajectory/KTKinematicData.h"

#include "LCDTrack.h"
#include "LCDMcPart.h"
#include "LCDCluster.h"

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
static const char* const kFacilityString = "Processor.Clean" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Clean::Clean( void )               // anal1
   : Processor( "Clean" )
   , m_mcfile("mcfile", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Clean::event,    Stream::kEvent );
   //bind( &Clean::beginRun, Stream::kBeginRun );
   //bind( &Clean::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Clean::~Clean()                    // anal5
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
Clean::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Clean::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Clean::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "ismode", "minsep", "mspx", "mspy", "mspz", "mse", "msdist",
      "hade", "eme", "te", "tpx", "tpy", "tpz", "cpx", "cpy", "cpz",
      "c2px", "c2py", "c2pz", "c5px", "c5py", "c5pz", "c10px", "c10py", "c10pz",
      "banda", "bandb", "bandc", "bandd", "bande",
      "tracks", "scale",
      "le", "lpx", "lpy", "lpz", "we", "wpx", "wpy", "wpz"};
   m_ntuple = iHistoManager.ntuple("ntuple", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Clean::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   Vector<LCDMcPart> mcparticles;
   extract(iFrame.record(Stream::kEvent), mcparticles);
   Vector<LCDTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   Vector<LCDCluster> clusters;
   extract(iFrame.record(Stream::kEvent), clusters);
   Vector<LCDCluster>::const_iterator clusters_end = clusters.end();

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   v[k_tracks] = tracks.size();

   v[k_ismode] = 0.;
   int index_chip = -1, index_chim = -1;
   v[k_scale] = 1.;
   for (int i = 0;  i < mcparticles.size();  i++) {
      if (mcparticles[i].GetParticleID() == 1000024) index_chip = i;
      else if (mcparticles[i].GetParticleID() == -1000024) index_chim = i;
      
      if (mcparticles[i].GetStatus() == 908070) v[k_scale] = mcparticles[i].Get4Momentum().E();
   }
   if (index_chip != -1  &&  index_chim != -1) {
      v[k_ismode] = 1.;
      int quarks = 0, gluons = 0, electrons = 0, muons = 0, taus = 0;
      TLorentzVector lep(0.,0.,0.,0.), w(0.,0.,0.,0.);
      for (int i = 0;  i < mcparticles.size();  i++) {
	 if (mcparticles[i].GetParentIdx() == index_chip  ||
	     mcparticles[i].GetParentIdx() == index_chim    ) {
	    switch (abs(mcparticles[i].GetParticleID())) {
	       case 1: case 2: case 3: case 4: case 5: case 6:
		  quarks++;
		  w += mcparticles[i].Get4Momentum();
		  break;
	       case 21:
		  gluons++;
		  w += mcparticles[i].Get4Momentum();
		  break;
	       case 11:
		  electrons++;
		  lep += mcparticles[i].Get4Momentum();
		  break;
	       case 13:
		  muons++;
		  lep += mcparticles[i].Get4Momentum();
		  break;
	       case 15:
		  taus++;
		  lep += mcparticles[i].Get4Momentum();
		  break;
	    }
	 }
      }
      if (quarks == 2  &&  gluons == 0  &&  electrons+muons+taus == 1) {
	 if (electrons == 1) v[k_ismode] = 2.;
	 if (muons == 1) v[k_ismode] = 3.;
	 if (taus == 1) v[k_ismode] = 4.;
      }
      else if (quarks == 2  &&  gluons > 0  &&  electrons+muons+taus == 1) {
	 if (electrons == 1) v[k_ismode] = 12.;
	 if (muons == 1) v[k_ismode] = 13.;
	 if (taus == 1) v[k_ismode] = 14.;
      }

      if (quarks == 2  &&  electrons+muons+taus == 1) {
	 v[k_le] = lep.E();
	 v[k_lpx] = lep.Px();
	 v[k_lpy] = lep.Py();
	 v[k_lpz] = lep.Pz();
	 v[k_we] = w.E();
	 v[k_wpx] = w.Px();
	 v[k_wpy] = w.Py();
	 v[k_wpz] = w.Pz();
      }
   }

   Vector<LCDTrack>::const_iterator most_isolated = tracks.end(), tracks_end = tracks.end();
   TVector3 most_isolated_p;
   double furthest_isolation = 2.;
   v[k_te] = v[k_tpx] = v[k_tpy] = v[k_tpz] = 0.;
   double most_isolated_energy, most_isolated_distance;
   for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      const TVector3 track_p = track_iter->GetMomentumVector(0.);
      v[k_te] += track_p.Mag();
      v[k_tpx] += track_p.x();
      v[k_tpy] += track_p.y();
      v[k_tpz] += track_p.z();

      double closest_energy, closest_dist = 100000.;
      for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
	   cluster_iter != clusters_end;  ++cluster_iter) {
	 if (cluster_iter->GetSystem() == 0) {
	    const double r = cluster_iter->GetEnergyR();
	    const double theta = cluster_iter->GetEnergyTheta();
	    const double phi = cluster_iter->GetEnergyPhi();
	    const TVector3 cluster_point = TVector3(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
	    const double energy = cluster_iter->GetEnergy();

	    const double dist = track_iter->GetDistance(cluster_point);
	    if (dist < 1. /* cm */ && dist < closest_dist) {
	       closest_dist = dist;
	       closest_energy = energy;
	    }
	 }
      }

      double closest_other = -2.;
      if (closest_dist != 100000.  &&  abs(closest_energy / track_p.Mag() - 1) < 0.2) {
	 for (Vector<LCDTrack>::const_iterator other_iter = tracks.begin();
	      other_iter != tracks_end;  ++other_iter) {
	    if (other_iter != track_iter) {
	       const TVector3 other_p = other_iter->GetMomentumVector(0.);
	       const double dot = (track_p).Dot(other_p) / track_p.Mag() / other_p.Mag();
	       
	       if (dot > closest_other) closest_other = dot;
	    }
	 }
      }
      if (closest_other != -2.  &&  closest_other <= furthest_isolation) {
	 furthest_isolation = closest_other;
	 most_isolated = track_iter;
	 most_isolated_p = track_p;
	 most_isolated_energy = closest_energy;
	 most_isolated_distance = closest_dist;
      }
   }

   v[k_minsep] = acos(furthest_isolation);
   v[k_mspx] = most_isolated_p.x();
   v[k_mspy] = most_isolated_p.y();
   v[k_mspz] = most_isolated_p.z();
   v[k_mse] = most_isolated_energy;
   v[k_msdist] = most_isolated_distance;
   
   v[k_hade] = v[k_eme] = 0.;
   v[k_banda] = v[k_bandb] = v[k_bandc] = v[k_bandd] = v[k_bande] = 0.;
   v[k_cpx] = v[k_cpy] = v[k_cpz] = 0.;
   for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
	cluster_iter != clusters_end;  ++cluster_iter) {
      const double r = cluster_iter->GetEnergyR();
      const double theta = cluster_iter->GetEnergyTheta();
      const double phi = cluster_iter->GetEnergyPhi();
      const TVector3 cluster_point = TVector3(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
      const double energy = cluster_iter->GetEnergy();
         
      if (cluster_iter->GetSystem() == 1) v[k_hade] += energy;
      if (cluster_iter->GetSystem() == 0) v[k_eme] += energy;

      const double abscostheta = abs(cos(theta));
      if (abscostheta < 0.7) v[k_banda] += energy;
      else if (abscostheta < 0.8) v[k_bandb] += energy;
      else if (abscostheta < 0.9) v[k_bandc] += energy;
      else if (abscostheta < 0.95) v[k_bandd] += energy;
      else v[k_bande] += energy;

      const TVector3 momentum = energy * TVector3(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
      double closest = 100000.;
      for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
	   track_iter != tracks_end;  ++track_iter) {
	 const double dist = track_iter->GetDistance(cluster_point);
	 if (dist < closest) closest = dist;
      }
      v[k_cpx] += momentum.x();
      v[k_cpy] += momentum.y();
      v[k_cpz] += momentum.z();
      if (closest > 2. /* cm */) {
	 v[k_c2px] += momentum.x();
	 v[k_c2py] += momentum.y();
	 v[k_c2pz] += momentum.z();
      }
      if (closest > 5. /* cm */) {
	 v[k_c5px] += momentum.x();
	 v[k_c5py] += momentum.y();
	 v[k_c5pz] += momentum.z();
      }
      if (closest > 10. /* cm */) {
	 v[k_c10px] += momentum.x();
	 v[k_c10py] += momentum.y();
	 v[k_c10pz] += momentum.z();
      }
   }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Clean::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Clean::endRun( Frame& iFrame )         // anal4 equiv.
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
