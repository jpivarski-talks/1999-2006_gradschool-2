// -*- C++ -*-
//
// Package:     LCDExampleProc
// Module:      LCDExampleProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Fri Apr 16 19:44:18 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LCDExampleProc/LCDExampleProc.h"
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
#include "MCFunctions/MCFunctions.h"
#include "LCDJetFinder.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzRotation.h"

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
static const char* const kFacilityString = "Processor.LCDExampleProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.35 2004/03/08 02:40:17 cdj Exp $";
static const char* const kTagString = "$Name: v06_09_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
LCDExampleProc::LCDExampleProc( void )               // anal1
   : Processor( "LCDExampleProc" )
   , m_mcfile("mcfile", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LCDExampleProc::event,    Stream::kEvent );
   //bind( &LCDExampleProc::beginRun, Stream::kBeginRun );
   //bind( &LCDExampleProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_all_events = 0;
   m_only_winners = 0;
}

LCDExampleProc::~LCDExampleProc()                    // anal5
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
LCDExampleProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LCDExampleProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   cout << "We saw " << m_only_winners << " good events out of " << m_all_events << endl;

}


// ---------------- standard place to book histograms ---------------
void
LCDExampleProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

//    const char* lab_tracks[kNumTrackEntries] = {
//       "d0", "phi0", "omega", "z0", "tanl", "momentum", "pperp", "chi2", "dof"};
//    m_tracks = iHistoManager.ntuple("tracks", kNumTrackEntries, 262144, lab_tracks);

//    const char* lab_trackclusters[kNumTrackClusterEntries] = {
//       "dist", "e", "p", "system", "barend"};
//    m_trackclusters = iHistoManager.ntuple("trcl", kNumTrackClusterEntries, 262144, lab_trackclusters);

//    const char* lab_clusters[kNumClusterEntries] = {
//       "energy", "r", "phi", "theta", "system", "barend"};
//    m_clusters = iHistoManager.ntuple("clusters", kNumClusterEntries, 262144, lab_clusters);

//    const char* lab_event[kNumEventEntries] = {
//       "sm", "susy", "pxsm", "pysm", "pzsm", "pxsu", "pysu", "pzsu", "esm", "esu"};
//    m_events = iHistoManager.ntuple("events", kNumEventEntries, 262144, lab_event);

//    const char* labels[kNumEntries] = {
//       "j1e", "j1px", "j1py", "j1pz",
//       "j2e", "j2px", "j2py", "j2pz",
//       "lle", "llpx", "llpy", "llpz",
//       "chipe", "chippx", "chippy", "chippz",
//       "chime", "chimpx", "chimpy", "chimpz",
// //       , "wpe", "wppx", "wppy", "wppz",
// //       "wme", "wmpx", "wmpy", "wmpz"
//       "jj1e", "jj1px", "jj1py", "jj1pz",
//       "jj2e", "jj2px", "jj2py", "jj2pz",
//       "gluee", "gluepx", "gluepy", "gluepz"
//    };
//    m_ntuple = iHistoManager.ntuple("ntuple", kNumEntries, 262144, labels);

   const char* labels[kNumEntries] = {
      "eve", "evpx", "evpy", "evpz", "isoe", "isopx", "isopy", "isopz", "scale", "jets", "glue", "mcfile", "ct", "jct"
   };
   m_ntuple = iHistoManager.ntuple("ntuple", kNumEntries, 262144, labels);

}

double sqr(double x) {return x*x;}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LCDExampleProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   
   //Extract information from the frame
   Vector<LCDMcPart> mcparticles;
   extract( iFrame.record(Stream::kEvent), mcparticles );
   Vector<LCDTrack> tracks;
   extract( iFrame.record(Stream::kEvent), tracks);
   Vector<LCDCluster> clusters;
   extract( iFrame.record(Stream::kEvent), clusters);
   FATable< LCDMatchTrack> matchedtracks;
   extract( iFrame.record(Stream::kEvent), matchedtracks);
   FATable< LCDIsolateCluster> isoclusts;
   extract( iFrame.record(Stream::kEvent), isoclusts);

//    //Here is a list of SUSY particle IDs
//    int n1ID = 1000022; //ID of Neutralino 1 (LSP)
//    int n2ID = 1000023; //ID of Neutralino 2
//    int n3ID = 1000025; //ID of Neutralino 3
//    int c1ID = 1000024; //ID of Chargino 1
//    int c2ID = 1000037; //ID of Chargino 2
//    int EID  = 11; //electron ID
//    int MUID = 13; //muon ID
//    int TAUID = 15; //Tau ID
//    int wID = 24; // not 80;
//    int glueID = 21;

//    TLorentzVector j1p, j2p, ll, chip, chim;
//    TLorentzVector glue(-1., 0., 0., 0.);

//    int which = 1;
//    int total_ll = 0;
//    bool survive_cuts = false;
//    bool negative_lepton = false;

//    int j1parent = 0;
//    int j2parent = 0;
//    int llparent = 0;

//    int lspcount = 0;

//    int current_idx=0;
//    //Okay, lets loop through the mcparticles and get all this shit.
//    Vector<LCDMcPart>::const_iterator partBegin = mcparticles.begin();
//    Vector<LCDMcPart>::const_iterator partEnd = mcparticles.end();
//    for(Vector<LCDMcPart>::const_iterator partItr = partBegin;
//        partItr != partEnd;
//        partItr++)
//    {
//       int id = (*partItr).GetParticleID();

//       if (id == glueID  &&
// 	  partItr->GetParentIdx() >= 0  &&  partItr->GetParentIdx() < mcparticles.size()  &&
// 	  abs(mcparticles[partItr->GetParentIdx()].GetParticleID()) == c1ID) {
// 	 glue = partItr->Get4Momentum();
//       }

//       if (id == n1ID  &&  mcparticles[partItr->GetParentIdx()].GetParticleID() != n1ID) {
// 	 lspcount++;
//       }

//       if (id == c1ID  &&
// 	  !(partItr->GetParentIdx() >= 0  &&  partItr->GetParentIdx() < mcparticles.size()  &&
// 	    mcparticles[partItr->GetParentIdx()].GetParticleID() == c1ID))
// 	 chip = partItr->Get4Momentum();
//       if (id == -c1ID  &&
// 	  !(partItr->GetParentIdx() >= 0  &&  partItr->GetParentIdx() < mcparticles.size()  &&
// 	    mcparticles[partItr->GetParentIdx()].GetParticleID() == -c1ID))
// 	 chim = partItr->Get4Momentum();
      
//       if (abs(id) > 0  &&  abs(id) < 7) {
// 	 if (which == 1) {
// 	    j1p = partItr->Get4Momentum();
// 	    j1parent = partItr->GetParentIdx();
// 	 }
// 	 else if (which == 2) {
// 	    j2p = partItr->Get4Momentum();
// 	    j2parent = partItr->GetParentIdx();
// 	 }
// 	 which++;
//       }
//       else if (abs(id) == EID  ||  abs(id) == MUID  ||  abs(id) == TAUID) {
// 	 if (id == -EID  ||  id == -MUID  ||  id == -TAUID) negative_lepton = true;	    
// 	 ll = partItr->Get4Momentum();
// 	 total_ll++;

// 	 llparent = partItr->GetParentIdx();
//       }

//    }

//    report(SYSTEM, kFacilityString)
//       << "which == " << which << " total_ll == " << total_ll << " lspcount == " << lspcount << endl
//       << "j1parent == " << j1parent << " j2parent == " << j2parent << " llparent == " << llparent << endl
//       << "mcparticles[j1parent].GetParticleID() == " << mcparticles[j1parent].GetParticleID() << endl
//       << "mcparticles[j2parent].GetParticleID() == " << mcparticles[j2parent].GetParticleID() << endl
//       << "mcparticles[llparent].GetParticleID() == " << mcparticles[llparent].GetParticleID() << endl;
   
//    if (!(which == 3  &&  total_ll == 1  &&  lspcount == 2  &&  j1parent == j2parent  &&  j1parent != llparent  &&
// 	 mcparticles[j1parent].GetParticleID() == c1ID * (negative_lepton ? -1 : 1)  &&
// 	 mcparticles[llparent].GetParticleID() == c1ID * (negative_lepton ? 1 : -1)    ))
//       return ActionBase::kFailed;

//    cout << "good" << endl;


//    cout << "CHI+:" << endl;
//    for(Vector<LCDMcPart>::const_iterator partItr = partBegin;
//        partItr != partEnd;
//        partItr++)
//    {
//       if (partItr->GetParticleID() == c1ID)
// 	 cout << "    "
// 	      << partItr->Get4Momentum().E() << " "
// 	      << partItr->Get4Momentum().Px() << " "
// 	      << partItr->Get4Momentum().Py() << " "
// 	      << partItr->Get4Momentum().Pz() << endl;
//    }
//    cout << "CHI-:" << endl;
//    for(Vector<LCDMcPart>::const_iterator partItr = partBegin;
//        partItr != partEnd;
//        partItr++)
//    {
//       if (partItr->GetParticleID() == -c1ID)
// 	 cout << "    "
// 	      << partItr->Get4Momentum().E() << " "
// 	      << partItr->Get4Momentum().Px() << " "
// 	      << partItr->Get4Momentum().Py() << " "
// 	      << partItr->Get4Momentum().Pz() << endl;
//    }







//    //Get number of tracks
   int NTracks = tracks.size();
//    //Make an instance of the MCFunctions class and initialize everything
//    //---------------------------------------------------------------------
// //NOTE: There are 4 ways to initialize MCFunctions class.
// // 1.You must load mcparticles,tracks,clusters
// // 2.In addition you can load matchedtracks
// // 3.Or, in addition you can load isoclusts
// // 4.Or, you can add both matchedtracks and isoclusts
// //   MCFunctions MCFuncs(mcparticles,tracks,clusters); 
// //   MCFunctions MCFuncs(mcparticles,tracks,clusters,matchedtracks); 
// //   MCFunctions MCFuncs(mcparticles,tracks,clusters,isoclusts); 
   MCFunctions MCFuncs(mcparticles,tracks,clusters,matchedtracks,isoclusts); 
   MCFuncs.Set_IsolLep_Ecut(10.0); //Minimum energy of isolated lepton (default == 10)
   MCFuncs.Set_IsolLep_Emax(500.0); //Maximum energy of isolated  lepton
   MCFuncs.Set_IsolLep_Deg(20.0); //Half Angle (degree) around isolated lep
   MCFuncs.Set_IsolLep_Eenc(2.0); //Maximum energy allowed in cone around lep
   MCFuncs.Set_DURHAM_YCUT(0.004); //YCUT used in Jet finding algorithm   
   MCFuncs.Set_USE_GEN_LEVEL_4VEC(0); //0= use measured 4v, 1 = use gen 4v (default == 1)
//     //---------------------------------------------------------------------

//    //Find the isolated Leptons
   vector<int> isoLepIdx;
   MCFuncs.getIdxVectorOfIsolatedLepton(isoLepIdx);
   vector<int>::const_iterator isolepBegin = isoLepIdx.begin();
   vector<int>::const_iterator isolepEnd   = isoLepIdx.end();
//    //Find the MCJets
   vector<int> MCJetsIdx;
   MCFuncs.getIdxVectorOfJets(MCJetsIdx);
   vector<int>::const_iterator mcjetBegin = MCJetsIdx.begin();
   vector<int>::const_iterator mcjetEnd   = MCJetsIdx.end();
//    //Find Jets using Jet finder
   vector< vector<int> > FoundJets;
   MCFuncs.RCGFindJets(FoundJets);
   vector< vector<int> >::const_iterator fjetBegin = FoundJets.begin();
   vector< vector<int> >::const_iterator fjetEnd   = FoundJets.end();
//    //Get the Measurable 4Momentum of this event
   TLorentzVector Event4vec = MCFuncs.GetEventMeasured4Momentum();
//    //Get the truth out about what is actually in event
//    int Chi20Code = MCFuncs.LookForSusyDecay(1000023, 1000022);
//    int Chi30Code = MCFuncs.LookForSusyDecay(1000025, 1000022);
//    double Eisoclust = MCFuncs.GetTotalEnergyOfIsolatedClusters();
//    //Get the scale factor for this file, this is 1.0 for all files
//    //except for those backgrounds that we recieved from slac
   double ScaleFactor = MCFuncs.GetScaleFactor();


//    //Okay, now lets get the EventShape variables
//    MCFuncs.FillEventShape();
//    double fw1=MCFuncs.get_EventShape_fw1();
//    double fw2=MCFuncs.get_EventShape_fw2();
//    double fw3=MCFuncs.get_EventShape_fw3();
//    double fw4=MCFuncs.get_EventShape_fw4();
//    double planarity=MCFuncs.get_EventShape_planarity();
//    double sphericity=MCFuncs.get_EventShape_sphericity();
//    double spherocity=MCFuncs.get_EventShape_spherocity();
//    double thrust=MCFuncs.get_EventShape_thrust();

   
   m_all_events++;
   if (isoLepIdx.size() == 1  && FoundJets.size() >= 2) {
      m_only_winners++;

      int isolep_index = *(isoLepIdx.begin());
      LCDMcPart isolep = MCFuncs.GetParticleByIdx(isolep_index);
      TLorentzVector isolep4 = isolep.Get4Momentum();
      
      double glueenergy = 0.;
      Vector<LCDMcPart>::const_iterator partBegin = mcparticles.begin();
      Vector<LCDMcPart>::const_iterator partEnd = mcparticles.end();
      for(Vector<LCDMcPart>::const_iterator partItr = partBegin; partItr != partEnd; partItr++) {
	 if (partItr->GetParticleID() == 21  &&
	     partItr->GetParentIdx() >= 0  &&
	     partItr->GetParentIdx() < mcparticles.size()  &&
	     abs(mcparticles[partItr->GetParentIdx()].GetParticleID()) >= 1000022)
	    glueenergy += partItr->Get4Momentum().E();
      }

      double maxcostheta = 0;
      Vector<LCDTrack>::const_iterator tracks_end = tracks.end();
      for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
	   track_iter != tracks_end;  ++track_iter) {
	 double ct = abs(track_iter->GetMomentumVector(0.0).CosTheta());
	 if (ct > maxcostheta) maxcostheta = ct;
      }

      double maxjetcostheta = 0;
      vector< vector<int> >::const_iterator fjetItr = FoundJets.begin();
      vector< vector<int> >::const_iterator fjetEnd = FoundJets.end();
      for (; fjetItr != fjetEnd;  ++fjetItr) {
	 vector<int> jet = (*fjetItr);
	 TLorentzVector j4vec = MCFuncs.GetTotal4Momentum(jet);
	 double ct = abs(j4vec.Pz()/sqrt(sqr(j4vec.Px()) + sqr(j4vec.Py()) + sqr(j4vec.Pz())));
	 if (ct > maxjetcostheta) maxjetcostheta = ct;
      }

      float v[kNumEntries];
      v[k_eve] = Event4vec.E();
      v[k_evpx] = Event4vec.Px();
      v[k_evpy] = Event4vec.Py();
      v[k_evpz] = Event4vec.Pz();
      v[k_isoe] = isolep4.E();
      v[k_isopx] = isolep4.Px();
      v[k_isopy] = isolep4.Py();
      v[k_isopz] = isolep4.Pz();
      v[k_scale] = ScaleFactor;
      v[k_jets] = FoundJets.size();
      v[k_glue] = glueenergy;
      v[k_mcfile] = m_mcfile.value();
      v[k_ct] = maxcostheta;
      v[k_jct] = maxjetcostheta;

      m_ntuple->fill(v);
   }
   if (m_all_events % 1000 == 0)
      cout << "fraction passing = " << double(m_only_winners)/double(m_all_events) << endl;



//    report(DEBUG,kFacilityString)<<"The number of Jets is "
// 				 <<FoundJets.size()
// 				 <<endl;
//    report(DEBUG,kFacilityString)<<"The number of isolated leptons is "
// 				 <<isoLepIdx.size()
// 				 <<endl;
//    report(DEBUG,kFacilityString)<<"The number of tracks "
// 				 <<tracks.size()
// 				 <<endl;


// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // First part done:



// // Do 2L mode:
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
//    //Check the topology, 2 tracks, both isolated leptons, no jets
//    if(isoLepIdx.size() == 2 &&
//       FoundJets.size() == 0 &&
//       NTracks          == 2)
//    {
//       //First of all, get the mcidx of the two leptons
//       vector<int>::const_iterator isolepItr = isolepBegin;
//       int idx1 = (*isolepItr);
//       isolepItr++;
//       int idx2 = (*isolepItr);

//       //Now get the mcparticles of each
//       LCDMcPart Lep1 = MCFuncs.GetParticleByIdx(idx1);
//       LCDMcPart Lep2 = MCFuncs.GetParticleByIdx(idx2);
//       //Now get the mcid
//       int id1 = Lep1.GetParticleID();
//       int id2 = Lep2.GetParticleID();
//       int isOpposite = 0;
//       //Check to make sure these id's are actually opposite, otherwise 
//       //they don't count
      
//       double q1 = Lep1.GetCharge();
//       double q2 = Lep2.GetCharge();
      
//       //If one of them is a muon, then use the mc ID
//       if( id1 == -id2 ) isOpposite = 1;
//       //If neither one is a muon, then we can't use id anymore
//       //they could just be tracks that passed electron id cuts.
//       //if( abs(id1) != 13 && abs(id2) != 13 && q1*q2<0.0 ) isOpposite = 1;


//       //Okay, this next thing I'm adding because I want the positve charge 
//       //one to always go to lepton 2 and the negative charge one to always go
//       //to lepton 1
//       if( isOpposite == 1)
//       {
// 	 //Save the 2 values to holding variables
// 	 int holdidx = idx2;
// 	 int holdid = id2;
// 	 double holdq = q2;
// 	 LCDMcPart holdLep = Lep2;
// 	 //id2 should always be less then zero.
// 	 if( q1 > 0 ) //If charge of Lepton1 is greater than zero then swap.
// 	 {
// 	    //put 1 values into 2
// 	    id2=id1;
// 	    idx2=idx1;
// 	    Lep2 = Lep1;
// 	    q2 = q1;
// 	    //put 2 values into 1
// 	    id1 = holdid;
// 	    idx1 = holdidx;
// 	    Lep1 = holdLep;
// 	    q1 = holdq;
// 	 }
//       }

//       //Make sure that they are acutally leptons (e or mu)

//       int isLepton = 0;
//       if( (abs(id1) == 11) || (abs(id2) == 13) ) isLepton = 1;
//       //Take above cut out, this is redundant
//       //int isLepton = 1;

//       //Now get the real parent id
//       int pidx1 = Lep1.GetParentIdx();
//       LCDMcPart PLep1 = MCFuncs.GetParticleByIdx(pidx1);
//       int pid1 = PLep1.GetParticleID();
//       int pidx2 = Lep2.GetParentIdx();
//       LCDMcPart PLep2 = MCFuncs.GetParticleByIdx(pidx2);
//       int pid2 = PLep2.GetParticleID();
//       //Now calculate the invariant mass of the two leptons 
// //      TLorentzVector LepVec = Lep1.Get4Momentum()+Lep2.Get4Momentum();
//       TLorentzVector LepVec = MCFuncs.Get4VectorByMCIdx(idx1)+
// 	 MCFuncs.Get4VectorByMCIdx(idx2);
//       double invMass = sqrt( LepVec.E()*LepVec.E()
// 			     -LepVec.Px()*LepVec.Px()
// 			     -LepVec.Py()*LepVec.Py()
// 			     -LepVec.Pz()*LepVec.Pz() );

//       //Okay, now lets write EVERYTHING out about this event.
//       if( isLepton == 1 && isOpposite == 1)
//       {



// // 	 report(NOTICE,kFacilityString)<<"Writting out 2L to Ntuple"<<endl;
// // 	 m_2LModeNT->fill(tuple);




//       } //If islepton and they are particle antiparticle
//    } //If there are no jets, 2 isolated leptons, and 2 tracks
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // 2L mode done.



// // Do the 4 Lepton mode now:
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
//    //Check the topology, 4 tracks, all isolated leptons, no jets
//    if(isoLepIdx.size() == 4 &&
//       FoundJets.size() == 0 &&
//       NTracks          == 4)
//    {
//       //This one is going to be trickier than the 2L mode, we can 
//       //only do this if 2 of them are electrons and 2 of them are muons,
//       //otherwise we won't be able to tell which pair of leptons to find
//       //the invariant mass between. This restriction will cut our signal
//       //right in half.
//       //If it is 4 identical leptons, then we just can't do this mode.


//       //Set the idx values to -10 to start with
//       int EPlusIdx = -10;
//       int EMinusIdx = -10;
//       int MuPlusIdx = -10;
//       int MuMinusIdx = -10;
//       //Now loop through the isoLep and fill in the idx values (if you can)
//       for(vector<int>::const_iterator isolepItr = isolepBegin;
// 	  isolepItr != isolepEnd;
// 	  isolepItr++)
//       {
// 	 int mcidx = (*isolepItr);
// 	 LCDMcPart Part = MCFuncs.GetParticleByIdx(mcidx);
// 	 int mcid = Part.GetParticleID();
// 	 double q = Part.GetCharge();
// 	 if(mcid == 11 ) EMinusIdx = mcidx;
// 	 if(mcid == -11 ) EPlusIdx = mcidx;
// 	 if(mcid == 13 ) MuMinusIdx = mcidx;
// 	 if(mcid == -13) MuPlusIdx = mcidx;

//       }

//       //Now only do more stuff if all of the Idx values are greater than 1
//       if( (EPlusIdx > 1) && (EMinusIdx > 1) && 
// 	  (MuPlusIdx > 1) && (MuMinusIdx > 1) )
//       {
// 	 //Okay! So we have an event that is just e+ e- mu+ mu- and nothing
// 	 //else. 
// 	 LCDMcPart EP = MCFuncs.GetParticleByIdx(EPlusIdx);
// 	 LCDMcPart EM = MCFuncs.GetParticleByIdx(EMinusIdx);
// 	 LCDMcPart MuP = MCFuncs.GetParticleByIdx(MuPlusIdx);
// 	 LCDMcPart MuM = MCFuncs.GetParticleByIdx(MuMinusIdx);

// //Swap Generator level 4 vectors for measured 4 vectors	 
// //	 TLorentzVector EP4vec = EP.Get4Momentum();
// 	 TLorentzVector EP4vec = MCFuncs.Get4VectorByMCIdx(EPlusIdx);
// //	 TLorentzVector EM4vec = EM.Get4Momentum();
// 	 TLorentzVector EM4vec = MCFuncs.Get4VectorByMCIdx(EMinusIdx);
// //	 TLorentzVector MuP4vec = MuP.Get4Momentum();
// 	 TLorentzVector MuP4vec = MCFuncs.Get4VectorByMCIdx(MuPlusIdx);
// //	 TLorentzVector MuM4vec = MuM.Get4Momentum();
// 	 TLorentzVector MuM4vec = MCFuncs.Get4VectorByMCIdx(MuMinusIdx);

// 	 TLorentzVector Mu4vec = MuP4vec+MuM4vec;
// 	 TLorentzVector E4vec  = EP4vec + EM4vec;

// 	 double MuInvM = sqrt(Mu4vec.E()*Mu4vec.E()
// 			      -Mu4vec.Px()*Mu4vec.Px()
// 			      -Mu4vec.Py()*Mu4vec.Py()
// 			      -Mu4vec.Pz()*Mu4vec.Pz() );

// 	 double EInvM = sqrt(E4vec.E()*E4vec.E()
// 			     -E4vec.Px()*E4vec.Px()
// 			     -E4vec.Py()*E4vec.Py()
// 			     -E4vec.Pz()*E4vec.Pz() );

// 	 //Now lets get the parent ID's for each particle
// 	 int pEpIdx = EP.GetParentIdx();
// 	 int pEmIdx = EM.GetParentIdx();
// 	 int pMUpIdx = MuP.GetParentIdx();
// 	 int pMUmIdx = MuM.GetParentIdx();
	 
// 	 LCDMcPart Parent;
// 	 Parent = MCFuncs.GetParticleByIdx(pEpIdx);
// 	 int pEpID = Parent.GetParticleID();
// 	 Parent = MCFuncs.GetParticleByIdx(pEmIdx);
// 	 int pEmID = Parent.GetParticleID();
// 	 Parent = MCFuncs.GetParticleByIdx(pMUpIdx);
// 	 int pMUpID = Parent.GetParticleID();
// 	 Parent = MCFuncs.GetParticleByIdx(pMUmIdx);
// 	 int pMUmID = Parent.GetParticleID();

// 	 //Okay, now we have everything we need, lets write out an ntuple

// // 	 report(NOTICE,kFacilityString)<<"Writting out 4L to Ntuple"<<endl;
// // 	 m_4LModeNT->fill(tuple);


//       } // If there are e+ e- mu+ mu-
//    } //If we have 4 isolated leps, and 4 tracks (the leps) and nothing else
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // 4L mode done:


// // Now do the 2J mode
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////

//    //Require that there are 2 jets, that there are no isolated leptons
//    //and that the number of tracks is greater than 3.
//    if( FoundJets.size() == 2 &&
//        isoLepIdx.size() == 0 &&
//        NTracks > 3 )
//    {

     

//       vector< vector<int> >::const_iterator fjetItr = fjetBegin;
      
//       vector<int> jet1 = (*fjetItr);
//       fjetItr++;
//       vector<int> jet2 = (*fjetItr);

//       int ntrk1 = MCFuncs.GetNumberOfTracksInList(jet1);
//       int ntrk2 = MCFuncs.GetNumberOfTracksInList(jet2);
//       double charge1 = MCFuncs.GetTotalCharge(jet1);
//       double charge2 = MCFuncs.GetTotalCharge(jet2);
//       //Now check that every track is accounted for by the jets
//       if( (ntrk1+ntrk2) == NTracks )
//       {

// 	 TLorentzVector j14vec = MCFuncs.GetTotal4Momentum(jet1);
// 	 TLorentzVector j24vec = MCFuncs.GetTotal4Momentum(jet2);
// 	 TLorentzVector j4vec = j14vec+j24vec;
// 	 double JInvM = sqrt(j4vec.E()*j4vec.E()
// 			     -j4vec.Px()*j4vec.Px()
// 			     -j4vec.Py()*j4vec.Py()
// 			     -j4vec.Pz()*j4vec.Pz() );

// 	 //Now, for the sake of knowing what the heck is going into this,
// 	 //We need to try and match these two jets to an MC jet
// 	 int NMCJets = MCJetsIdx.size();
// 	 //-------------------------------------------------------------
// 	 //The following are variables of the MCJet match to be found
// 	 //-------------------------------------------------------------
// 	 double max_match1 = -500.0;
// 	 double max_match2 = -500.0;
// 	 TLorentzVector m14vec(0.0,0.0,0.0,0.0);
// 	 TLorentzVector m24vec(0.0,0.0,0.0,0.0);
// 	 int m1NTrack = 0;
// 	 int m2NTrack = 0;
// 	 int m1NPart = 0;
// 	 int m2NPart = 0;
// 	 int m1idx  = 0;
// 	 int m2idx  = 0;
// 	 int m1ID = 0;
// 	 int m2ID = 0;
// 	 double m1charge = 0.0;
// 	 double m2charge = 0.0;
// 	 //-------------------------------------------------------------
// 	 //Now lets loop over the mcjets and find the best match
// 	 for(vector<int>::const_iterator mcjetItr = mcjetBegin;
// 	     mcjetItr != mcjetEnd;
// 	     mcjetItr++)
// 	 {
// 	    int jetidx = (*mcjetItr);
// 	    vector<int> mcjetparts;
// 	    MCFuncs.getIdxVectorOfStableDescendants(jetidx,mcjetparts);
// 	    double matchqual1 = MCFuncs.MatchQuality(jet1,mcjetparts);
// 	    double matchqual2 = MCFuncs.MatchQuality(jet2,mcjetparts);

// 	    //See if this matches jet1
// 	    if(matchqual1 > max_match1)
// 	    {
// 	       max_match1=matchqual1;
// 	       m14vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m1NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m1NPart = mcjetparts.size();
// 	       m1idx = jetidx;
// 	       m1charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }

// 	    //See if this matches jet2
// 	    if(matchqual2 > max_match2)
// 	    {
// 	       max_match2=matchqual2;
// 	       m24vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m2NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m2NPart = mcjetparts.size();
// 	       m2idx = jetidx;
// 	       m2charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }
// 	 } //Looping through MCJets

// 	 //Okay, we found our jetmatches, so lets get the partcle ID
// 	 if(max_match1 > -2.0)
// 	 {
// 	    LCDMcPart Jet1Part = MCFuncs.GetParticleByIdx(m1idx);
// 	    m1ID = Jet1Part.GetParticleID();
// 	 }
// 	 if(max_match2 > -2.0)
// 	 {
// 	    LCDMcPart Jet2Part = MCFuncs.GetParticleByIdx(m2idx);
// 	    m2ID = Jet2Part.GetParticleID();
// 	 }



// 	 //Okay boys and girls, lets write all of this SUSY stuff out!!

// // 	 report(NOTICE,kFacilityString)<<"Writting out 2J to Ntuple"<<endl;
// // 	 m_2JModeNT->fill(tuple);



//       } //If the number of tracks in the jets equals the number of tracks
//       // In the event.
//    }//If we have no isolated leptons, 2 jets, and at least 4 tracks
       
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // 2J mode done.




// // Okay Boys and Girls, 2J2L Mode:
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////

   
//    //Require that there are 2 jets, that there are 2 isolated leptons
//    //and that the number of tracks is greater than 5. So, 1 track for 
//    //each lepton and at least 2 tracks for each jet
//    if( FoundJets.size() == 2 &&
//        isoLepIdx.size() == 2 &&
//        NTracks > 5 )
//    {

//       //----------------- Initial Jet Stuff ------------------------
//       vector< vector<int> >::const_iterator fjetItr = fjetBegin;
//       vector<int> jet1 = (*fjetItr);
//       fjetItr++;
//       vector<int> jet2 = (*fjetItr);
//       int ntrk1 = MCFuncs.GetNumberOfTracksInList(jet1);
//       int ntrk2 = MCFuncs.GetNumberOfTracksInList(jet2);
//       double charge1 = MCFuncs.GetTotalCharge(jet1);
//       double charge2 = MCFuncs.GetTotalCharge(jet2);
//       //-------------- DONE: Initial Jet Stuff ---------------------


//       //--------------- Initial Lepton Stuff -----------------------
//       //This is mostly just copied and pasted from the 2L mode
//       //First of all, get the mcidx of the two leptons
//       vector<int>::const_iterator isolepItr = isolepBegin;
//       int idx1 = (*isolepItr);
//       isolepItr++;
//       int idx2 = (*isolepItr);
//       //Now get the mcparticles of each
//       LCDMcPart Lep1 = MCFuncs.GetParticleByIdx(idx1);
//       LCDMcPart Lep2 = MCFuncs.GetParticleByIdx(idx2);
//       //Now get the mcid
//       int id1 = Lep1.GetParticleID();
//       int id2 = Lep2.GetParticleID();
//       int isOpposite = 0;
//       //Check to make sure these id's are actually opposite, otherwise 
//       //they don't count
//       double q1 = Lep1.GetCharge();
//       double q2 = Lep2.GetCharge();
      
//       //If one of them is a muon, then use the mc ID
//       if( id1 == -id2 ) isOpposite = 1;
//       //If neither one is a muon, then we can't use id anymore
//       //they could just be tracks that passed electron id cuts.
//       //if( abs(id1) != 13 && abs(id2) != 13 && q1*q2<0.0 ) isOpposite = 1;


//       //Okay, this next thing I'm adding because I want the positve charge 
//       //one to always go to lepton 2 and the negative charge one to always go
//       //to lepton 1
//       if( isOpposite == 1)
//       {
// 	 //Save the 2 values to holding variables
// 	 int holdidx = idx2;
// 	 int holdid = id2;
// 	 double holdq = q2;
// 	 LCDMcPart holdLep = Lep2;
// 	 //id2 should always be less then zero.
// 	 if( id2 > 0 ) //If id2 is greater than zero, then swap them.
// 	 {
// 	    //put 1 values into 2
// 	    id2=id1;
// 	    idx2=idx1;
// 	    q2 = q1;
// 	    Lep2 = Lep1;
// 	    //put 2 values into 1
// 	    id1 = holdid;
// 	    idx1 = holdidx;
// 	    Lep1 = holdLep;
// 	    q1 = holdq;
// 	 }
//       }
      
      
      
//       //Make sure that they are acutally leptons (e or mu)
//       int isLepton = 0;
//       if( (abs(id1) == 11) || (abs(id2) == 13) ) isLepton = 1;
//       //


//       //Now get the real parent id
//       int pidx1 = Lep1.GetParentIdx();
//       LCDMcPart PLep1 = MCFuncs.GetParticleByIdx(pidx1);
//       int pid1 = PLep1.GetParticleID();
//       int pidx2 = Lep2.GetParentIdx();
//       LCDMcPart PLep2 = MCFuncs.GetParticleByIdx(pidx2);
//       int pid2 = PLep2.GetParticleID();
//       //Now calculate the invariant mass of the two leptons 
// //      TLorentzVector LepVec = Lep1.Get4Momentum()+Lep2.Get4Momentum();
//       TLorentzVector LepVec = MCFuncs.Get4VectorByMCIdx(idx1) + 
// 	 MCFuncs.Get4VectorByMCIdx(idx2);
//       double invMass = sqrt( LepVec.E()*LepVec.E()
// 			     -LepVec.Px()*LepVec.Px()
// 			     -LepVec.Py()*LepVec.Py()
// 			     -LepVec.Pz()*LepVec.Pz() );
      
      

//       //------------- DONE: Initial Lepton Stuff ---------------------



//       if( (isOpposite == 1) && (isLepton == 1) &&
// 	  ((ntrk1+ntrk2+2) == NTracks) )
//       {

// 	 //---------------- The Rest of the Jet Stuff --------------------
// 	 TLorentzVector j14vec = MCFuncs.GetTotal4Momentum(jet1);
// 	 TLorentzVector j24vec = MCFuncs.GetTotal4Momentum(jet2);
// 	 TLorentzVector j4vec = j14vec+j24vec;
// 	 double JInvM = sqrt(j4vec.E()*j4vec.E()
// 			     -j4vec.Px()*j4vec.Px()
// 			     -j4vec.Py()*j4vec.Py()
// 			     -j4vec.Pz()*j4vec.Pz() );
	 
// 	 //Now, for the sake of knowing what the heck is going into this,
// 	 //We need to try and match these two jets to an MC jet
// 	 int NMCJets = MCJetsIdx.size();
// 	 //-------------------------------------------------------------
// 	 //The following are variables of the MCJet match to be found
// 	 //-------------------------------------------------------------
// 	 double max_match1 = -500.0;
// 	 double max_match2 = -500.0;
// 	 TLorentzVector m14vec(0.0,0.0,0.0,0.0);
// 	 TLorentzVector m24vec(0.0,0.0,0.0,0.0);
// 	 int m1NTrack = 0;
// 	 int m2NTrack = 0;
// 	 int m1NPart = 0;
// 	 int m2NPart = 0;
// 	 int m1idx  = 0;
// 	 int m1ID = 0;
// 	 int m2idx  = 0;
// 	 int m2ID = 0;
// 	 double m1charge = 0.0;
// 	 double m2charge = 0.0;
// 	 //-------------------------------------------------------------
// 	 //Now lets loop over the mcjets and find the best match
// 	 for(vector<int>::const_iterator mcjetItr = mcjetBegin;
// 	     mcjetItr != mcjetEnd;
// 	     mcjetItr++)
// 	 {
// 	    int jetidx = (*mcjetItr);
// 	    vector<int> mcjetparts;
// 	    MCFuncs.getIdxVectorOfStableDescendants(jetidx,mcjetparts);
// 	    double matchqual1 = MCFuncs.MatchQuality(jet1,mcjetparts);
// 	    double matchqual2 = MCFuncs.MatchQuality(jet2,mcjetparts);
	    
// 	    //See if this matches jet1
// 	    if(matchqual1 > max_match1)
// 	    {
// 	       max_match1=matchqual1;
// 	       m14vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m1NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m1NPart = mcjetparts.size();
// 	       m1idx = jetidx;
// 	       m1charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }
	    
// 	    //See if this matches jet2
// 	    if(matchqual2 > max_match2)
// 	    {
// 	       max_match2=matchqual2;
// 	       m24vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m2NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m2NPart = mcjetparts.size();
// 	       m2idx = jetidx;
// 	       m2charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }
// 	 } //Looping through MCJets
	 

// 	 //Okay, we found our jetmatches, so lets get the partcle ID
// 	 if(max_match1 > -2.0)
// 	 {
// 	    LCDMcPart Jet1Part = MCFuncs.GetParticleByIdx(m1idx);
// 	    m1ID = Jet1Part.GetParticleID();
// 	 }
// 	 if(max_match2 > -2.0)
// 	 {
// 	    LCDMcPart Jet2Part = MCFuncs.GetParticleByIdx(m2idx);
// 	    m2ID = Jet2Part.GetParticleID();
// 	 }
	 

// 	 //---------------DONE: The Rest of the Jet Stuff ------------------


// 	 //Righty, Boys and Girls, time to write crap out to Ntuple

// // 	 report(NOTICE,kFacilityString)<<"Writting out 2J2L to Ntuple"<<endl;
// // 	 m_2J2LModeNT->fill(tuple);



//       }

//    }
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // 2J2L Mode done:






// // Okay Boys and Girls, 2J1L Mode: Note, this is not a chi20chi30 mode
// // I've just put it in here so that I could take a quick look at c1+c1-
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////

   
//    //Require that there are 2 jets, that there are 2 isolated leptons
//    //and that the number of tracks is greater than 5. So, 1 track for 
//    //each lepton and at least 2 tracks for each jet
//    if( FoundJets.size() == 2 &&
//        isoLepIdx.size() == 1 &&
//        NTracks > 4 )
//    {


//       //----------------- Initial Jet Stuff ------------------------
//       vector< vector<int> >::const_iterator fjetItr = fjetBegin;
//       vector<int> jet1 = (*fjetItr);
//       fjetItr++;
//       vector<int> jet2 = (*fjetItr);
//       int ntrk1 = MCFuncs.GetNumberOfTracksInList(jet1);
//       int ntrk2 = MCFuncs.GetNumberOfTracksInList(jet2);
//       double charge1 = MCFuncs.GetTotalCharge(jet1);
//       double charge2 = MCFuncs.GetTotalCharge(jet2);
//       //-------------- DONE: Initial Jet Stuff ---------------------


//       //--------------- Initial Lepton Stuff -----------------------
//       //This is mostly just copied and pasted from the 2L mode
//       //First of all, get the mcidx of the two leptons
//       vector<int>::const_iterator isolepItr = isolepBegin;
//       int idx1 = (*isolepItr);
//       //Now get the mcparticles of each
//       LCDMcPart Lep1 = MCFuncs.GetParticleByIdx(idx1);
//       //Now get the mcid
//       int id1 = Lep1.GetParticleID();
      
      
      
//       //Make sure that they are acutally leptons (e or mu)
//       int isLepton = 0;
//       if( (abs(id1) == 11) || (abs(id1) == 13) ) isLepton = 1;

//       //Now get the real parent id
//       int pidx1 = Lep1.GetParentIdx();
//       LCDMcPart PLep1 = MCFuncs.GetParticleByIdx(pidx1);
//       int pid1 = PLep1.GetParticleID();

//       //------------- DONE: Initial Lepton Stuff ---------------------


//       if( (isLepton == 1) &&
// 	  ((ntrk1+ntrk2+1) == NTracks) )
//       {


// 	 //---------------- The Rest of the Jet Stuff --------------------
// 	 TLorentzVector j14vec = MCFuncs.GetTotal4Momentum(jet1);
// 	 TLorentzVector j24vec = MCFuncs.GetTotal4Momentum(jet2);
// 	 TLorentzVector j4vec = j14vec+j24vec;
// 	 double JInvM = sqrt(j4vec.E()*j4vec.E()
// 			     -j4vec.Px()*j4vec.Px()
// 			     -j4vec.Py()*j4vec.Py()
// 			     -j4vec.Pz()*j4vec.Pz() );
	 
// 	 //Now, for the sake of knowing what the heck is going into this,
// 	 //We need to try and match these two jets to an MC jet
// 	 int NMCJets = MCJetsIdx.size();
// 	 //-------------------------------------------------------------
// 	 //The following are variables of the MCJet match to be found
// 	 //-------------------------------------------------------------
// 	 double max_match1 = -500.0;
// 	 double max_match2 = -500.0;
// 	 TLorentzVector m14vec(0.0,0.0,0.0,0.0);
// 	 TLorentzVector m24vec(0.0,0.0,0.0,0.0);
// 	 int m1NTrack = 0;
// 	 int m2NTrack = 0;
// 	 int m1NPart = 0;
// 	 int m2NPart = 0;
// 	 int m1idx  = 0;
// 	 int m2idx  = 0;
// 	 int m1ID = 0;
// 	 int m2ID = 0;
// 	 double m1charge = 0.0;
// 	 double m2charge = 0.0;
// 	 //-------------------------------------------------------------
// 	 //Now lets loop over the mcjets and find the best match
// 	 for(vector<int>::const_iterator mcjetItr = mcjetBegin;
// 	     mcjetItr != mcjetEnd;
// 	     mcjetItr++)
// 	 {
// 	    int jetidx = (*mcjetItr);
// 	    vector<int> mcjetparts;
// 	    MCFuncs.getIdxVectorOfStableDescendants(jetidx,mcjetparts);
// 	    double matchqual1 = MCFuncs.MatchQuality(jet1,mcjetparts);
// 	    double matchqual2 = MCFuncs.MatchQuality(jet2,mcjetparts);
	    
// 	    //See if this matches jet1
// 	    if(matchqual1 > max_match1)
// 	    {
// 	       max_match1=matchqual1;
// 	       m14vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m1NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m1NPart = mcjetparts.size();
// 	       m1idx = jetidx;
// 	       m1charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }
	    
// 	    //See if this matches jet2
// 	    if(matchqual2 > max_match2)
// 	    {
// 	       max_match2=matchqual2;
// 	       m24vec = MCFuncs.GetTotal4Momentum(mcjetparts);
// 	       m2NTrack = MCFuncs.GetNumberOfTracksInList(mcjetparts);
// 	       m2NPart = mcjetparts.size();
// 	       m2idx = jetidx;
// 	       m2charge=MCFuncs.GetTotalCharge(mcjetparts);
// 	    }
// 	 } //Looping through MCJets
	 


// 	 //Okay, we found our jetmatches, so lets get the partcle ID
// 	 if(max_match1 > -2.0)
// 	 {
// 	    LCDMcPart Jet1Part = MCFuncs.GetParticleByIdx(m1idx);
// 	    m1ID = Jet1Part.GetParticleID();
// 	 }
// 	 if(max_match2 > -2.0)
// 	 {
// 	    LCDMcPart Jet2Part = MCFuncs.GetParticleByIdx(m2idx);
// 	    m2ID = Jet2Part.GetParticleID();
// 	 }

// 	 //---------------DONE: The Rest of the Jet Stuff ------------------


// 	 //Righty, Boys and Girls, time to write crap out to Ntuple

// // 	 report(NOTICE,kFacilityString)<<"Writting out 2J1L to Ntuple"<<endl;
// // 	 m_2J1LModeNT->fill(tuple);

// 	 survive_cuts = true;


//       }

//    }
// ///////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////
// // 2J1L Mode done:













//    float v[kNumEntries];
//    v[k_j1E] = j1p.E();
//    v[k_j1px] = j1p.Px();
//    v[k_j1py] = j1p.Py();
//    v[k_j1pz] = j1p.Pz();
//    v[k_j2E] = j2p.E();
//    v[k_j2px] = j2p.Px();
//    v[k_j2py] = j2p.Py();
//    v[k_j2pz] = j2p.Pz();
//    v[k_llE] = ll.E() * (negative_lepton ? -1. : 1.);
//    v[k_llpx] = ll.Px();
//    v[k_llpy] = ll.Py();
//    v[k_llpz] = ll.Pz();
// //   v[k_survive] = (survive_cuts ? 1. : 0.);
//    v[k_chipE] = chip.E();
//    v[k_chippx] = chip.Px();
//    v[k_chippy] = chip.Py();
//    v[k_chippz] = chip.Pz();
//    v[k_chimE] = chim.E();
//    v[k_chimpx] = chim.Px();
//    v[k_chimpy] = chim.Py();
//    v[k_chimpz] = chim.Pz();
// //    v[k_wpE] = wp.E();
// //    v[k_wppx] = wp.Px();
// //    v[k_wppy] = wp.Py();
// //    v[k_wppz] = wp.Pz();
// //    v[k_wmE] = wm.E();
// //    v[k_wmpx] = wm.Px();
// //    v[k_wmpy] = wm.Py();
// //    v[k_wmpz] = wm.Pz();

//    v[k_jj1e] = (v[k_chimE]*v[k_j1E] - v[k_chimpx]*v[k_j1px] - v[k_chimpy]*v[k_j1py] - v[k_chimpz]*v[k_j1pz])/ (v[k_chimE]*sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))));

// //    if (v[k_llE] < 0.  &&  v[k_jj1e] < 40.) {
// //       report(SYSTEM, kFacilityString)
// // 	 << "v[k_jj1e] = " << v[k_jj1e] << endl;

// //       for(int i = 0;  i < mcparticles.size();  i++)
// //       {
// // 	 int id = mcparticles[i].GetParticleID();
// // 	 if (abs(id) == n1ID  ||
// // 	     abs(id) == c1ID  ||
// // 	     (abs(id) > 0  &&  abs(id) < 7)  ||
// // 	     abs(id) == EID  ||
// // 	     abs(id) == MUID  ||
// // 	     abs(id) == TAUID  ||
// // 	     (mcparticles[i].GetParentIdx() >= 0  &&
// // 	      mcparticles[i].GetParentIdx() < mcparticles.size()  &&
// // 	      (abs(id = mcparticles[mcparticles[i].GetParentIdx()].GetParticleID()) == n1ID  ||
// // 	       abs(id) == c1ID  ||
// // 	       (abs(id) > 0 && abs(id) < 7)  ||
// // 	       abs(id) == EID  ||
// // 	       abs(id) == MUID  ||
// // 	       abs(id) == TAUID)))

// // 	    report(SYSTEM, kFacilityString)
// // 	       << "particle " << i << " id " << mcparticles[i].GetParticleID() << " came from " << mcparticles[i].GetParentIdx()
// // 	       << " momentum " << mcparticles[i].Get4Momentum().E()
// // 	       << " " << mcparticles[i].Get4Momentum().Px()
// // 	       << " " << mcparticles[i].Get4Momentum().Py()
// // 	       << " " << mcparticles[i].Get4Momentum().Pz() << endl;
// //       }
// //    }

//    v[k_jj1px] = (v[k_chimE]*v[k_chimpx]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1E] + pow(v[k_chimpy],2)*v[k_j1px] - pow(v[k_chimE],2)* (1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1px] - v[k_chimpx]*v[k_chimpy]*v[k_j1py] + v[k_chimpz]*(v[k_chimpz]*v[k_j1px] - v[k_chimpx]*v[k_j1pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_jj1py] = (v[k_chimE]*v[k_chimpy]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1E] - v[k_chimpx]*v[k_chimpy]*v[k_j1px] + pow(v[k_chimpx],2)*v[k_j1py] - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1py] + v[k_chimpz]*(v[k_chimpz]*v[k_j1py] - v[k_chimpy]*v[k_j1pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_jj1pz] = (v[k_chimE]*v[k_chimpz]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1E] - v[k_chimpx]*v[k_chimpz]*v[k_j1px] + pow(v[k_chimpx],2)*v[k_j1pz] - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j1pz] + v[k_chimpy]*(-(v[k_chimpz]*v[k_j1py]) + v[k_chimpy]*v[k_j1pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_jj2e] = (v[k_chimE]*v[k_j2E] - v[k_chimpx]*v[k_j2px] - v[k_chimpy]*v[k_j2py] - v[k_chimpz]*v[k_j2pz])/ (v[k_chimE]*sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))));

//    v[k_jj2px] = (v[k_chimE]*v[k_chimpx]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2E] + pow(v[k_chimpy],2)*v[k_j2px] - pow(v[k_chimE],2)* (1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2px] - v[k_chimpx]*v[k_chimpy]*v[k_j2py] + v[k_chimpz]*(v[k_chimpz]*v[k_j2px] - v[k_chimpx]*v[k_j2pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_jj2py] = (v[k_chimE]*v[k_chimpy]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2E] - v[k_chimpx]*v[k_chimpy]*v[k_j2px] + pow(v[k_chimpx],2)*v[k_j2py] - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2py] + v[k_chimpz]*(v[k_chimpz]*v[k_j2py] - v[k_chimpy]*v[k_j2pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_jj2pz] = (v[k_chimE]*v[k_chimpz]*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2E] - v[k_chimpx]*v[k_chimpz]*v[k_j2px] + pow(v[k_chimpx],2)*v[k_j2pz] - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2))))*v[k_j2pz] + v[k_chimpy]*(-(v[k_chimpz]*v[k_j2py]) + v[k_chimpy]*v[k_j2pz]))/ (pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2) - pow(v[k_chimE],2)*(1 + sqrt(-((-pow(v[k_chimE],2) + pow(v[k_chimpx],2) + pow(v[k_chimpy],2) + pow(v[k_chimpz],2))/pow(v[k_chimE],2)))));

//    v[k_gluee] = glue.E();
//    v[k_gluepx] = glue.Px();
//    v[k_gluepy] = glue.Py();
//    v[k_gluepz] = glue.Pz();

//    m_ntuple->fill(v);


//    for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
// 	track_iter != tracks_end;  ++track_iter) {
//       float v[kNumTrackEntries];
//       v[kD0] = track_iter->GetTrackParameter(0);
//       v[kPhi0] = track_iter->GetTrackParameter(1);
//       v[kOmega] = track_iter->GetTrackParameter(2);
//       v[kZ0] = track_iter->GetTrackParameter(3);
//       v[kTanL] = track_iter->GetTrackParameter(4);
//       v[kMomentum] = track_iter->GetMomentumVector(0.0).Mag();
//       v[kPPerp] = track_iter->GetMomentumVector(0.0).Perp();
//       v[kChi2] = track_iter->GetChi2();
//       v[kDof] = track_iter->GetNdf();
//       m_tracks->fill(v);

//       for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
// 	   cluster_iter != clusters_end;  ++cluster_iter) {

// 	 double r = cluster_iter->GetEnergyR();
// 	 double theta = cluster_iter->GetEnergyTheta();
// 	 double phi = cluster_iter->GetEnergyPhi();
	 
// 	 double dist = track_iter->GetDistance(TVector3(r*sin(theta)*cos(phi),
// 							r*sin(theta)*sin(phi),
// 							r*cos(theta)));

//  	 if (abs(dist) < 10.) {
//  	    float w[kNumTrackClusterEntries];
//  	    w[kDist] = dist;
//  	    w[kE] = cluster_iter->GetEnergy();
// 	    w[kP] = track_iter->GetMomentumVector(0.0).Mag();
//  	    w[kTCSystem] = cluster_iter->GetSystem();
//  	    w[kTCBarEnd] = cluster_iter->GetBarEnd();
//  	    m_trackclusters->fill(w);
//  	 }
//       }
//    }

//    for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
// 	cluster_iter != clusters_end;  ++cluster_iter) {
//       float v[kNumClusterEntries];
//       v[kEnergy] = cluster_iter->GetEnergy();
//       v[kR] = cluster_iter->GetEnergyR();
//       v[kPhi] = cluster_iter->GetEnergyPhi();
//       v[kTheta] = cluster_iter->GetEnergyTheta();
//       v[kSystem] = cluster_iter->GetSystem();
//       v[kBarEnd] = cluster_iter->GetBarEnd();

//       m_clusters->fill(v);
//    }

//    const int smparticles[231] = {
//       6, 11, 12, 13, 14, 15, 16, 22, 23, 24, 111, 113, 115, 117, 130,
//       211, 213, 215, 217, 221, 223, 225, 227, 229, 310, 311, 313, 315,
//       317, 319, 321, 323, 325, 327, 329, 331, 333, 335, 337, 411, 413,
//       415, 421, 423, 425, 431, 433, 441, 443, 445, 511, 513, 521, 523,
//       531, 553, 555, 1112, 1114, 1116, 1118, 1212, 1214, 1216, 1218,
//       2112, 2114, 2116, 2118, 2122, 2124, 2126, 2128, 2212, 2214,
//       2216, 2218, 2222, 2224, 2226, 2228, 3112, 3114, 3116, 3118,
//       3122, 3124, 3126, 3128, 3212, 3214, 3216, 3218, 3222, 3224,
//       3226, 3228, 3312, 3314, 3322, 3324, 3334, 4112, 4122, 4132,
//       4212, 4222, 4232, 4332, 5122, 10113, 10115, 10213, 10215, 10223,
//       10311, 10313, 10315, 10321, 10323, 10325, 10423, 10433, 10441,
//       10551, 11114, 11116, 11216, 12112, 12114, 12116, 12126, 12212,
//       12214, 12216, 12224, 12226, 13112, 13114, 13116, 13122, 13124,
//       13126, 13212, 13214, 13216, 13222, 13224, 13226, 13314, 13324,
//       14122, 20113, 20213, 20223, 20313, 20315, 20323, 20325, 20333,
//       20443, 20553, 21112, 21114, 21212, 21214, 22112, 22114, 22122,
//       22124, 22212, 22214, 22222, 22224, 23112, 23114, 23122, 23124,
//       23126, 23212, 23214, 23222, 23224, 30113, 30213, 30223, 30313,
//       30323, 30443, 31114, 31214, 32112, 32114, 32124, 32212, 32214,
//       32224, 33122, 42112, 42212, 43122, 53122, 100111, 100113,
//       100211, 100213, 100221, 100223, 100313, 100323, 100333, 100335,
//       100443, 100553, 100555, 110551, 120553, 200553, 300553, 9000111,
//       9000211, 9000443, 9000553, 9010221, 9010443, 9010553, 9020221,
//       9020443, 9030221, 9050225, 9060225};

//    int particles_sm(0), particles_susy(0);
//    TVector3 p_sm(0., 0., 0.), p_susy(0., 0., 0.);
//    double e_sm(0.), e_susy(0.);
//    for (Vector<LCDMcPart>::const_iterator mc_iter = mcparticles.begin();
// 	mc_iter != mcparticles_end;  ++mc_iter) {
//       int id = mc_iter->GetParticleID();
//       bool sm = false;
//       for (int i = 0;  i < 231;  i++) if (abs(id) == smparticles[i]) sm = true;

//       if (sm) {
// 	 particles_sm++;
// 	 p_sm += mc_iter->Get4Momentum().Vect();
// 	 e_sm += mc_iter->Get4Momentum().M();
//       }
//       else {
// 	 particles_susy++;
// 	 p_susy += mc_iter->Get4Momentum().Vect();
// 	 e_susy += mc_iter->Get4Momentum().Energy();
//       }
//    }

//    float v[kNumEventEntries];
//    v[kPartSM] = particles_sm;
//    v[kPartSUSY] = particles_susy;
//    v[kPxSM] = p_sm.x();
//    v[kPySM] = p_sm.y();
//    v[kPzSM] = p_sm.z();
//    v[kPxSUSY] = p_susy.x();
//    v[kPySUSY] = p_susy.y();
//    v[kPzSUSY] = p_susy.z();
//    v[kESM] = e_sm;
//    v[kESUSY] = e_susy;
//    m_events->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
LCDExampleProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LCDExampleProc::endRun( Frame& iFrame )         // anal4 equiv.
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
