// -*- C++ -*-
//
// Package:     LCProc
// Module:      LCProc
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
#include "LCProc/LCProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "LCDRootAccess/Vector.h"

#include "LCDTrack.h"
#include "LCDMcPart.h"
#include "LCDCluster.h"
#include "LCDBeam.h"
#include "LCDJetFinder.h"
#include "LCDPyj2McPart.h"

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "LCDstdHEPfuncs.h"

#include "LCDMatching/LCDMatchTrack.h"
#include "LCDMatching/LCDIsolateCluster.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"


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
static const char* const kFacilityString = "Processor.LCProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.35 2004/03/08 02:40:17 cdj Exp $";
static const char* const kTagString = "$Name: v06_09_00 $";

//
// static data member definitions
//
float nLeptons   = 0;
float nEvents2Leptons = 0;
float nEventsOnly2Leptons = 0;
float nEvents2Jets = 0;
float nTracks = 0;

double GetParticleMass(int particleID)
{
   double pmass = -1;
   if(particleID == 11) // electron
      pmass = .00051;
   if(particleID == 13) // muon 
      pmass = .106;
   if(particleID == 15) // tau
      pmass = 1.777;
   if(particleID == 22) // photon
      pmass = 0.0;
   if(particleID == 23) // Z
      pmass = 91.187;
   if(particleID == 24) // W
      pmass = 80.41;
   if(particleID == 111) // pi
      pmass = .135;
   if(particleID == 211) // pi
      pmass = .139;
   if(particleID == 221) // eta
      pmass = .547;
   if(particleID == 113 || particleID == 213) // rho
      pmass = .770;
   if(particleID == 321)  // K
	 pmass = .494;
   if(particleID == 2212) // p/n
      pmass = .938;
   if(pmass != -1) return pmass;
}
string GetParticleName(int particleID)
{
   
   if(particleID == 11) // electron
      return "E-";
   if(particleID == -11)
      return "E+";
   if(particleID == 13) // muon 
      return "MU-";
   if(particleID == -13)
      return "MU+";
   if(particleID == 15) // tau
      return "TAU+";
   if(particleID == -15) 
      return "TAU-";
   if(particleID == 22) // photon
      return "GAMM";
   if(particleID == 23) // Z
      return "Z";
   if(particleID == 24) // W
      return "W";
   if(particleID == 111) // pi
      return "PI";
   if(particleID == 211) // pi
      return "PI";
   if(particleID == 221) // eta
      return "ETA";
   if(particleID == 113 || particleID == 213) // rho
      return "RHO";
   if(particleID == 321)  // K
      return "K";
   if(particleID == 2212) // p/n
      return "P";
   return "no name for id ";
}



//
// constructors and destructor
//
LCProc::LCProc( void )               // anal1
   : Processor( "LCProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LCProc::event,    Stream::kEvent );
   //bind( &LCProc::beginRun, Stream::kBeginRun );
   //bind( &LCProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)
   

}

LCProc::~LCProc()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   cout<<"Number of Events with 2 leptons "<<nEvents2Leptons<<endl;
   cout<<"Number of Events only 2 leptons "<<nEventsOnly2Leptons<<endl;
   cout<<"Number of Events with 2 jets    "<<nEvents2Jets<<endl;

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
LCProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LCProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
   
}


// ---------------- standard place to book histograms ---------------
enum { kNumTrk, kME, kEJ, kEL, kNumL, kNumJ, kClsE, kID1, kPID1, kChg1, kE1, kP1x, kP1y, kP1z, kID2, kPID2, kChg2, kE2, kP2x, kP2y, kP2z,
       kBigp, kBigem, kBighad, kSecp, kSecem, kSechad, kEsumiso, kEsumtrk,
       kNumVars};
enum {lTrkMom, lEenergy, lHenergy, lTrkJetAng, lid, lpid, lNumVars};
void
LCProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   m_trackMom = iHistoManager.histogram("track Momentum, mag ",100,0,20);
   m_totalTrackMom = iHistoManager.histogram("track Mom per event",100,0,100);
   m_trackEnergy = iHistoManager.histogram("track energy ", 100,0,100);
   m_totalTrackEnergy = iHistoManager.histogram("total track energy",100,0,500);

   m_clusterEnergy = iHistoManager.histogram("cluster energy, mag ",100,0,100);
   m_totalClusterEnergy = iHistoManager.histogram("cluster per event",100,0,500);
   m_missEnergy = iHistoManager.histogram("missing energy",100,0,500);
   m_totalLeptonEnergy = iHistoManager.histogram("combined energy of 2 leptons",100,0,500);
   m_leptonEnergy = iHistoManager.histogram("energy of leptons in events with missing energy", 100,0,200);
   m_leptonEnergy2lEvt = iHistoManager.histogram("energy of leptons in events with 2 l and miss eng",100,0,200);
   m_nJets = iHistoManager.histogram("number of jets in each event",10,0,10);
   m_JetP  = iHistoManager.histogram("jet momentum", 100,0,300);
   m_JetP2JEvts = iHistoManager.histogram("jet momentum, 2J events",100,0,300);
   m_JetPhi =iHistoManager.histogram("jet phi",100,0, 6.29);
   m_JetCosTh=iHistoManager.histogram("jet cos theta",100,-1,1);

   HINtupleVarNames varnames(kNumVars);
   varnames.addVar(kNumTrk, "numtrks");
   varnames.addVar(kME, "misseng" );
   varnames.addVar(kEJ, "jeteng" );
   varnames.addVar(kEL, "lepeng" );
   varnames.addVar(kNumL, "numleps");
   varnames.addVar(kNumJ, "numjets");
   varnames.addVar(kClsE, "clsEng");
   varnames.addVar(kID1, "id1");
   varnames.addVar(kPID1,"pid1");
   varnames.addVar(kChg1,"chg1");
   varnames.addVar(kE1, "e1" );
   varnames.addVar(kP1x, "p1x" );
   varnames.addVar(kP1y, "p1y" );
   varnames.addVar(kP1z, "p1z" );
   varnames.addVar(kID2, "id2");
   varnames.addVar(kPID2,"pid2");
   varnames.addVar(kChg2,"chg2");
   varnames.addVar(kE2, "e2" );
   varnames.addVar(kP2x, "p2x" );
   varnames.addVar(kP2y, "p2y" );
   varnames.addVar(kP2z, "p2z" );

   varnames.addVar(kBigp   , "bigp");         
   varnames.addVar(kBigem  , "bigem");	      
   varnames.addVar(kBighad , "bighad");	      
   varnames.addVar(kSecp   , "secp");	      
   varnames.addVar(kSecem  , "secem");	      
   varnames.addVar(kSechad , "sechad");	      
   varnames.addVar(kEsumiso, "esumiso");
   varnames.addVar(kEsumtrk, "esumtrk");

   m_2lntuple = iHistoManager.ntuple(1000, "leptons", kNumVars, 500000, varnames.names());
   HINtupleVarNames lvarnames(lNumVars);
   lvarnames.addVar(lTrkMom, "trkmom");
   lvarnames.addVar(lEenergy, "em");
   lvarnames.addVar(lHenergy, "had");
   lvarnames.addVar(lTrkJetAng, "tjang");
   lvarnames.addVar(lid, "id");
   lvarnames.addVar(lpid, "pid");
   m_tjntuple = iHistoManager.ntuple(2000,"lepton id", lNumVars, 500000, lvarnames.names());
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LCProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // initialize some variables for the event
   int nLeptonsEvt = 0;
   float eLeptons   = 0;
   TVector3 totalTrackMom; 
   for(int i = 0; i<3;i++)
      totalTrackMom[i]=0;
   Double_t totalTrackEnergy = 0;
   Double_t totalLeptonEnergy = 0;
   int numNonLeps = 0;
   Double_t totalClusterEnergy = 0;

   // Get the tracks
   Vector<LCDTrack> tracks;
   extract( iFrame.record(Stream::kEvent), tracks);

   // Get the clusters
   Vector<LCDCluster> clusters;
   extract( iFrame.record(Stream::kEvent), clusters);
   
   // Get the MCParticles
   Vector<LCDMcPart> mcparticles;
   extract( iFrame.record(Stream::kEvent), mcparticles );

   /*
   // look for particles with both em and had clusters
   for(Int_t nmc=0;nmc<mcparticles.size();nmc++)
   {
      
      bool emMatch = 0; bool hadMatch = 0;
      for (Int_t ncls=0; ncls<clusters.size(); ncls++) 
      {
	 LCDCluster cls = clusters[ncls];
	 
	 for(Int_t npart=0; npart<cls.GetMcListEntries(); npart++)
	 {
	    if(cls.GetMcList()[npart] == nmc)
	    {
	       if(cls.GetSystem() == 0)
	       {
		  emMatch = 1;
		  	       }
	       if(cls.GetSystem() == 1)
	       {
		  hadMatch = 1;
	       }
	    }
	 }
      }
      if(emMatch && hadMatch) cout<<"had and em match!!!"<<endl;

   }
   */

// loop thru tracks
   for (Int_t ntrk=0; ntrk<tracks.size(); ntrk++) 
   {
      // get the track and it's momentum
      LCDTrack trk = tracks[ntrk];
      TVector3 momvec = trk.GetMomentumVector(0.0);
      const Double_t mom = momvec.Mag();
      totalTrackMom += trk.GetMomentumVector(0.0);
      
      // get the id of the particle causing this track
      Int_t particleID = abs(mcparticles[trk.GetParticle()].GetParticleID());
      
      // Get the mass of the particle 
      Double_t pmass = GetParticleMass(particleID);
      
      // see if it's a lepton
      if(particleID == 11 | particleID == 13) // e or mu
      {
	 nLeptons++;
	 nLeptonsEvt++;
	 eLeptons += sqrt(mom*mom+pmass*pmass);
	 m_leptonEnergy->fill(sqrt(mom*mom+pmass*pmass));
      }

      if(pmass == -1)
      {
	 cout<<"WARNING Track caused by particle with id "<<particleID<<endl;
	 continue;
      }
      
      // calculate track energy getting its mass from mc id 
      Double_t penergy = sqrt(mom*mom+pmass*pmass);
      totalTrackEnergy += penergy;
   }

   // loop thru clusters
   for (Int_t ncls=0; ncls<clusters.size(); ncls++) 
   {
      LCDCluster cls = clusters[ncls];
      Double_t matchedEnergy;
      // loop thru tracks to see if this is a trk-cluster match
      bool trkclsMatch = 0; 
      for (Int_t ntrk=0; ntrk<tracks.size(); ntrk++) 
      {
	 LCDTrack trk = tracks[ntrk];
	 for(Int_t npart=0; npart<cls.GetMcListEntries(); npart++)
	 {
	    if(trk.GetParticle() == cls.GetMcList()[npart])
	       matchedEnergy+=cls.GetMcListE()[npart];
	 }
      }
      // if it isn't, add it to the total cluster energy
      
      Double_t energy = cls.GetEnergy()-matchedEnergy;
      totalClusterEnergy += energy;
      
   }
   Double_t missEnergy = 500.0 - totalClusterEnergy-totalTrackEnergy;

// LOOK FOR JETS
   LCDJetFinder jetfind(0.004);  // Default.. DURHAM algorithm
   
   TClonesArray veclist("TLorentzVector",10000);
   // Look at tracks. Can access them by the [] operator.
   
   // Event cut # track >= 2
   nTracks = tracks.size();
      
   veclist.Delete(); // Clean up veclist

   // Track loop    
   for (Int_t ntrk=0; ntrk<nTracks; ntrk++) 
   {
      LCDTrack trk = tracks[ntrk];
      Int_t pid = abs(mcparticles[tracks[ntrk].GetParticle()].GetParticleID());
      {
	 TVector3 tP3 = trk.GetMomentumVector(0.0);
	 Double_t E_trk = TMath::Sqrt(tP3.Mag2() + 0.1396*0.1396); 
	 // Assume pion mass
	 TLorentzVector* vec4 = new(veclist[ntrk]) TLorentzVector();
	 vec4->SetXYZT(tP3.X(),tP3.Y(),tP3.Z(),E_trk);
	 numNonLeps++;
       }
    }
   
    Int_t numjets = 0;
    TVector3 TotalJetMom(0.0,0.0,0.0);
    if(nTracks>1 && numNonLeps>1)
    {
       //  Do Jet Finding
       
       jetfind.SetPartList(&veclist); // Input particle 4-vector list
       jetfind.SetDURHAM();           // Use DURHAM algorithm
       jetfind.SetYCut(0.004);        // Set YCut value
       jetfind.doFindJets();          // JetFindig
       
       numjets = jetfind.njets();
       if(numjets == 2) nEvents2Jets++;
       
       m_nJets->fill(numjets);
       
       for(Int_t j = 0; j < numjets; j++){
	  
	  TLorentzVector* Jet_vec = jetfind.jet4vec(j);
	  TVector3        Pjet    = Jet_vec ->Vect();   // Jet 3 vector
	  
	  TotalJetMom += Pjet;
	  
	  Double_t  Jet_mom = Pjet.Mag();
	  Double_t  Jet_cos = (Pjet.Z())/Jet_mom;
	  Double_t  Jet_phi = Pjet.Phi();
       }
       
    }


    // Do some stuff to work out jet/lepton separation
    if(numjets>0)
    {
    for (Int_t ntrk=0; ntrk<nTracks; ntrk++) 
    {
       LCDTrack trk = tracks[ntrk];
       const TVector3 tP3 = trk.GetMomentumVector(0.0);
       LCDMcPart part = mcparticles[tracks[ntrk].GetParticle()];
       Int_t pid = abs(part.GetParticleID());
       // is the track a lepton?
       bool isLepton = (pid == 11 || pid == 13);
       
       // find the jet closest to the track
       Double_t TrkJetAngle = 10;
       for(Int_t j = 0; j < numjets; j++)
       {
	  
	  TLorentzVector* Jet_vec = jetfind.jet4vec(j);
	  TVector3 Pjet    = Jet_vec ->Vect();   // Jet 3 vector
	  Double_t tempAngle = (Pjet.Angle(tP3));
	  if(tempAngle<TrkJetAngle)
	     TrkJetAngle = tempAngle;
       }
    
       // loop thru clusters to find energy deposits
       Double_t Eenergy = 0;
       Double_t Henergy = 0;
       for (Int_t ncls=0; ncls<clusters.size(); ncls++) 
       {
	  LCDCluster cls = clusters[ncls];
	  //if(trk.GetParticle() == *(cls.GetMcList()))
	  for(Int_t npart=0; npart<cls.GetMcListEntries(); npart++)
	  {
	     if(trk.GetParticle() == cls.GetMcList()[npart])
	     {
		// track is matched
		if(cls.GetSystem() == 0)
		   Eenergy+=cls.GetMcListE()[npart];
		if(cls.GetSystem() == 1)
		   Henergy+=cls.GetMcListE()[npart];
	     }
	  }
       }
       // fill an ntuple with some values
       float ntupleValues[lNumVars];
       ntupleValues[lTrkMom]= tP3.Mag();
       ntupleValues[lEenergy]= Eenergy;
       ntupleValues[lHenergy]= Henergy;
       ntupleValues[lTrkJetAng]= cos(TrkJetAngle);
       ntupleValues[lid]= pid;
       ntupleValues[lpid]=mcparticles[part.GetParentIdx()].GetParticleID();
       m_tjntuple->fill(ntupleValues);
    }
    }

// //////////////////////////////////////////////////////////////////////

    double jim_biggest_p = 0.;
    double jim_biggest_em = -1000.;
    double jim_biggest_had = -1000.;
    double jim_second_p = 0.;
    double jim_second_em = -1000.;
    double jim_second_had = -1000.;

    double jim_esum_isolated = 0.;
    double jim_esum_tracks = 0.;

    if (true) {  // protect namespace

       FATable<LCDMatchTrack> matchTrack;
       extract(iFrame.record(Stream::kEvent), matchTrack);
       FATable<LCDMatchTrack>::const_iterator matchTrack_end = matchTrack.end();

       FATable<LCDMatchTrack>::const_iterator biggest = matchTrack_end;
       FATable<LCDMatchTrack>::const_iterator second = matchTrack_end;
       for (FATable<LCDMatchTrack>::const_iterator matchTrack_iter = matchTrack.begin();
	    matchTrack_iter != matchTrack_end;  ++matchTrack_iter) {
	  double momentum = matchTrack_iter->track()->GetMomentumVector(0.).Mag();
	  
	  if (momentum > jim_biggest_p) {
	     jim_second_p = jim_biggest_p;
	         second =       biggest;

	     jim_biggest_p = momentum;
	     biggest = matchTrack_iter;
	  }
	  else if (momentum > jim_second_p) {
	     jim_second_p = momentum;
	     second = matchTrack_iter;
	  }

	  jim_esum_tracks += momentum;
       } // end loop over tracks

       if (biggest != matchTrack_end  &&  second != matchTrack_end) {
	  jim_biggest_p *= (biggest->track()->GetTrackParameter(2) > 0. ? 1. : -1.);
	  jim_second_p *= (second->track()->GetTrackParameter(2) > 0. ? 1. : -1.);
	  
	  jim_biggest_em = biggest->emEnergy();
	  jim_biggest_had = biggest->hadEnergy();
	  jim_second_em = second->emEnergy();
	  jim_second_had = second->hadEnergy();
       }

       FATable<LCDIsolateCluster> isolateCluster;
       extract(iFrame.record(Stream::kEvent), isolateCluster);
       FATable<LCDIsolateCluster>::const_iterator isolateCluster_end = isolateCluster.end();

       for (FATable<LCDIsolateCluster>::const_iterator isolateCluster_iter = isolateCluster.begin();
	    isolateCluster_iter != isolateCluster_end;  ++isolateCluster_iter) {
	  jim_esum_isolated += isolateCluster_iter->cluster()->GetEnergy();
       }
    }

// //////////////////////////////////////////////////////////////////////

    // if the event has two leptons, do some stuff
    if(nLeptonsEvt >= 2)
    {
       Double_t firstM = 0;
       Double_t secondM = 0;
       LCDTrack trk1;
       LCDTrack trk2;
       for (Int_t ntrk=0; ntrk<tracks.size(); ntrk++) 
       {
	  Int_t particleID = abs(mcparticles[tracks[ntrk].GetParticle()].GetParticleID());
	  LCDTrack trk = tracks[ntrk];
	  if(particleID == 11 || particleID == 13)
	  {
	     Double_t mom = trk.GetMomentumVector(0.0).Mag();
	     if(mom > firstM)
	     {
		secondM = firstM;
		trk2=trk1;
		firstM = mom;
		trk1=trk;
	     }
	     else if(mom>secondM)
	     {
		secondM = mom;
		trk2 = trk;
	     }
	  }
       }
       Int_t particleID1 = abs(mcparticles[trk1.GetParticle()].GetParticleID());
       Int_t particleID2 = abs(mcparticles[trk2.GetParticle()].GetParticleID());
       Int_t parent1 = mcparticles[mcparticles[trk1.GetParticle()].GetParentIdx()].GetParticleID();
       Int_t parent2 = mcparticles[mcparticles[trk2.GetParticle()].GetParentIdx()].GetParticleID();
       TVector3 momvec1 = trk1.GetMomentumVector(0.0);
       TVector3 momvec2 = trk2.GetMomentumVector(0.0);
       const Double_t mom1 = momvec1.Mag();
       const Double_t mom2 = momvec2.Mag();
       Double_t mass1 = GetParticleMass(particleID1); 
       Double_t mass2 = GetParticleMass(particleID2);
       Double_t Energy1 = sqrt(mass1*mass1+mom1*mom1);
       Double_t Energy2 = sqrt(mass2*mass2+mom2*mom2);
       
       Double_t combMom = (momvec1+momvec2).Mag();
       Double_t redMass = sqrt((Energy1+Energy2)*(Energy1+Energy2)+
			       (momvec1+momvec2).Mag()*(momvec1+momvec2).Mag());
       Double_t angle = 0;
       //fill an ntuple with all of these values
       float ntupleValues[kNumVars];
       ntupleValues[kNumTrk]=tracks.size();
       ntupleValues[kME] = missEnergy;
       ntupleValues[kEJ] = TotalJetMom.Mag();
       ntupleValues[kEL] = eLeptons;
       ntupleValues[kNumL]= nLeptonsEvt;
       ntupleValues[kNumJ] = numjets;
       ntupleValues[kClsE]=totalClusterEnergy;
       ntupleValues[kID1]= particleID1;
       ntupleValues[kPID1]= parent1;
       ntupleValues[kChg1]= trk1.GetCharge();
       ntupleValues[kE1]= Energy1;
       ntupleValues[kP1x]= momvec1.x();
       ntupleValues[kP1y]= momvec1.y();
       ntupleValues[kP1z]= momvec1.z();
       ntupleValues[kID2]= particleID2;
       ntupleValues[kPID2]= parent2;
       ntupleValues[kChg2]= trk2.GetCharge();
       ntupleValues[kE2]= Energy2;
       ntupleValues[kP2x]= momvec2.x();
       ntupleValues[kP2y]= momvec2.y();
       ntupleValues[kP2z]= momvec2.z();

       ntupleValues[kBigp] = jim_biggest_p;
       ntupleValues[kBigem] = jim_biggest_em;
       ntupleValues[kBighad] = jim_biggest_had;
       ntupleValues[kSecp] = jim_second_p;
       ntupleValues[kSecem] = jim_second_em;
       ntupleValues[kSechad] = jim_second_had;
       ntupleValues[kEsumiso] = jim_esum_isolated;
       ntupleValues[kEsumtrk] = jim_esum_tracks;

       m_2lntuple->fill(ntupleValues);
      
   }
    else {
       float ntupleValues[kNumVars];
       ntupleValues[kNumTrk]=tracks.size();
       ntupleValues[kME] = missEnergy;
       ntupleValues[kEJ] = TotalJetMom.Mag();
       ntupleValues[kEL] = eLeptons;
       ntupleValues[kNumL]= nLeptonsEvt;
       ntupleValues[kNumJ] = numjets;
       ntupleValues[kClsE]=totalClusterEnergy;
       ntupleValues[kID1]= -1000.; // particleID1;
       ntupleValues[kPID1]= -1000.; // parent1;
       ntupleValues[kChg1]= -1000.; // trk1.GetCharge();
       ntupleValues[kE1]= -1000.; // Energy1;
       ntupleValues[kP1x]= -1000.; // momvec1.x();
       ntupleValues[kP1y]= -1000.; // momvec1.y();
       ntupleValues[kP1z]= -1000.; // momvec1.z();
       ntupleValues[kID2]= -1000.; // particleID2;
       ntupleValues[kPID2]= -1000.; // parent2;
       ntupleValues[kChg2]= -1000.; // trk2.GetCharge();
       ntupleValues[kE2]= -1000.; // Energy2;
       ntupleValues[kP2x]= -1000.; // momvec2.x();
       ntupleValues[kP2y]= -1000.; // momvec2.y();
       ntupleValues[kP2z]= -1000.; // momvec2.z();

       ntupleValues[kBigp] = jim_biggest_p;
       ntupleValues[kBigem] = jim_biggest_em;
       ntupleValues[kBighad] = jim_biggest_had;
       ntupleValues[kSecp] = jim_second_p;
       ntupleValues[kSecem] = jim_second_em;
       ntupleValues[kSechad] = jim_second_had;
       ntupleValues[kEsumiso] = jim_esum_isolated;
       ntupleValues[kEsumtrk] = jim_esum_tracks;

       m_2lntuple->fill(ntupleValues);
    }

    // play with LCDMatched!
    int numMatchedTracks = 0;
    int numMatchedTracksCheck = 0;
//     FATable< LCDMatched >::const_iterator iTrack;
//     FATable< LCDMatched >::const_iterator jTrack;
    //for( iTrack = matchedTracks.begin(); iTrack != matchedTracks.end(); iTrack++ )
    //{
    // numMatchedTracks++;
       
    //}
//     numMatchedTracks = matchedTracks.size();
//     cout<<"PerfectTrackShowerMatchingProd found "<<numMatchedTracks<<" tracks."<<endl;
    
    // now test it
    for (Int_t ntrk=0; ntrk<nTracks; ntrk++) 
    {
       bool trackMatched = 0;
       LCDTrack trk = tracks[ntrk];
       for (Int_t ncls=0; ncls<clusters.size(); ncls++) 
       {
	  LCDCluster cls = clusters[ncls];
	  for(Int_t npart=0; npart<cls.GetMcListEntries(); npart++)
	  {
	     if(cls.GetMcList()[npart] == trk.GetParticle())
		trackMatched = 1;
	  }
       }
       if(trackMatched) numMatchedTracksCheck++;
    }
    cout<<"LCProc found                          "<<numMatchedTracksCheck<<" tracks."<<endl;
    cout<<"There are "<<nTracks<<" in the event "<<endl;
   return ActionBase::kPassed;
   }   

/*
ActionBase::ActionResult
LCProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LCProc::endRun( Frame& iFrame )         // anal4 equiv.
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






