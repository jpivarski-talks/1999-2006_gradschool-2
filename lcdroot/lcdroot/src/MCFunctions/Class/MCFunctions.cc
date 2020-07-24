// -*- C++ -*-
//
// Package:     MCFunctions
// Module:      MCFunctions
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Richard Gray
// Created:     Fri Jun 25 15:33:38 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MCFunctions/MCFunctions.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "LCDRootAccess/Vector.h"

#include "LCDTrack.h"
#include "LCDMcPart.h"
#include "LCDCluster.h"
#include "LCDJetFinder.h"

#include "HistogramInterface/HINtupleVarNames.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzRotation.h"

//This is for Jim's Match Tracks
#include "LCDMatching/LCDMatchTrack.h"
#include "LCDMatching/LCDIsolateCluster.h"

//Stuff needed for event shape
#include "KinematicTrajectory/KTKinematicData.h"
#include "EventShape/EventShape.h"

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
static const char* const kFacilityString = "Processor.MCFunctions" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

static
DABoolean
isChargedLeptonID( int mcid )
{

   int id = abs(mcid);
   if( (id == 11) || (id == 13) || (id == 15) || (id == 17) )
      return true;
   return false;
}

static
DABoolean
isNeutrino( int mcid )
{
 
   int id = abs(mcid);
   if( (id == 12) || (id == 14) || (id == 16) || (id == 18))
      return true;
   return false;
}


static 
DABoolean
isLeptonID( int mcid ) 
{
   if( isNeutrino(mcid) || isChargedLeptonID(mcid))
      return true;
   return false;

}



DABoolean
isSNeutrino( int mcid )
{
   int id = abs(mcid);

   if( (id == 1000012) || 
       (id == 1000014) ||
       (id == 1000016) ||
       (id == 1000017))
      return true;
   return false;
}


static
DABoolean
isNeutralino( int mcid)
{
   int id=abs(mcid);
   if( id == 1000022 ) return true;
   if( id == 1000023 ) return true;
   if( id == 1000025 ) return true;
   if( id == 1000035 ) return true;

   return false;

}


int
MCFunctions::IsIsolatedLepton(int mcidx)
{

   //This is whether or not particle was measured
   int ismeas = isMeasured(mcidx);

   //Just end it here if it isn't even measured.
   if(ismeas == 0 ) return 0;


   LCDMcPart Part = GetParticleByIdx(mcidx);
   //This is the mcid of the current particle
   int mcid = Part.GetParticleID();
   //Get the 4vector
   TLorentzVector the4vec = Get4VectorByMCIdx(mcidx);
   double mcE = the4vec.E();
   //Get Energy enclosed around it in cone of half angle m_IsoLep_Deg
   double Eenc = GetEEnclosed(mcidx,m_IsolLep_Deg);
   //Now return 1 if it passes the cuts
   int iselectron = 0;
   int ismuon = 0 ;
   

   if(abs(mcid) == 11 ) iselectron = 1;
   if(abs(mcid) == 13 ) ismuon = 1;


   if( (iselectron == 1 || ismuon == 1) &&
       (mcE > m_IsolLep_Ecut) &&
       (mcE < m_IsolLep_Emax) &&
       (Eenc < m_IsolLep_Eenc) &&
       (ismeas == 1)) 
   {
      return 1;
   }
   
   return 0;
}




//Given the idx of the parent particle, give a vector of the idx values
//for all of the children of the parent particle.

void 
MCFunctions::getIdxVectorOfChildren( int parent_idx,
		vector<int>& mcChildrenIdx)
{
   int present_idx = 0;
   //loop over mcparticles and make vector of all idx that have 
   //parent idx of parent_idx
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();
   
   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
   {
      if( (*mcpartItr).GetParentIdx() == parent_idx ) 
      {
	 //If this particle had the parent we want, then 
	 //add its idx to our vector of mcChildrenIdx
	 mcChildrenIdx.insert(mcChildrenIdx.end(),present_idx);
      }
      
      present_idx=present_idx+1;
   }
   

return;
}



//Return the LCDMcPart that has the idx value of particle_idx
LCDMcPart
MCFunctions::GetParticleByIdx(int particle_idx)
{

   LCDMcPart Particle;

   int present_idx = 0;
   //attempting to loop over mcparticles
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();

   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
  {
     if( present_idx == particle_idx ) 
     {
	Particle = (*mcpartItr);
	//Now that we found what we're looking for, return true and get
	//out of here
	return Particle;
     }

     present_idx=present_idx+1;
  }

   return Particle;
}





//This function will fill an idx vector of isolated leptons
void 
MCFunctions::getIdxVectorOfIsolatedLepton( vector<int>& isoLep)
{
   int present_idx = 0;
   //loop over mcparticles and make vector of all stable leptons that pass
   //our isolation cuts.
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();
   
   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
   {

      if( IsIsolatedLepton(present_idx) == 1)
      {
	 //particle is an isolated lepton, or passes the cuts anyway
	 isoLep.insert(isoLep.end(),present_idx);
      } 
      present_idx=present_idx+1;
   }

return;
}


//This function will fill an idx vector of all of the quarks and gluons
void 
MCFunctions::getIdxVectorOfJets( vector<int>& mcJetsIdx)
{
   int present_idx = 0;
   //loop over mcparticles and make vector of all idx that are a quark
   //or a gluon
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();
   
   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
   {

      //This is the mcid of the current particle
      int mcid = (*mcpartItr).GetParticleID();
      //If current particle is a quark or gluon then we will say
      //it is the sire of a jet.
      mcid=abs(mcid);
      if( (mcid > 0 && mcid < 7 ) || mcid == 21 ) 
      {
	 //particle was a quark or a gluon, we will call these
	 //our jets
	 mcJetsIdx.insert(mcJetsIdx.end(),present_idx);
      }
      present_idx=present_idx+1;
   }

return;
}



//This is a function to return vector of idx's of all stable decendants
//of a given particle.
void 
MCFunctions::getIdxVectorOfStableDescendants( int parent_idx,
		vector<int>& mcStableDescendIdx)
{
   vector<int> idxList;
   getIdxVectorOfChildren(parent_idx,idxList);
   int NChildren=idxList.size();

   while ( NChildren > 0 )
   {
      vector<int> NewIdxList;

      vector<int>::const_iterator ListBegin = idxList.begin();
      vector<int>::const_iterator ListEnd = idxList.end();
      
      for ( vector<int>::const_iterator ListItr = ListBegin;
	    ListItr !=ListEnd;
	    ++ListItr)
      {
	 //The the idx of current child
	 int present_idx=(*ListItr);
	 //Now get the MCParticle so we can see if it is stable or not
	 LCDMcPart ThePart=GetParticleByIdx(present_idx);
	 //If the Particle is stable, add it to mcStableDescendIdx
	 if( ThePart.GetStatus() == 1)
	 {
	    mcStableDescendIdx.insert(mcStableDescendIdx.end(),present_idx);
	 }
	 
	 //Add the children of this idx to the idxList
	 getIdxVectorOfChildren(present_idx,NewIdxList);
	 //Update what the end of the list is
	 //ListEnd=idxList.end();
      }
   
      //Now, make idxList equal to the children of the children,
      //And continue to swim through mcparticles until we've hit the end
      idxList=NewIdxList;
      NChildren=idxList.size();
   }

   return;
}

TLorentzVector
MCFunctions::MCJetTotalTLorentzVector(int jetid)
{
   
   vector<int> JetPartsIdx;
   //Get all of the stable particles that descended from 
   //this quark or gluon.
   getIdxVectorOfStableDescendants(jetid,JetPartsIdx);   
   
   TLorentzVector Total(0,0,0,0);
   vector<int>::const_iterator partBegin = JetPartsIdx.begin();
   vector<int>::const_iterator partEnd   = JetPartsIdx.end();
   for(vector<int>::const_iterator partItr = partBegin;
       partItr != partEnd;
       ++partItr)
   {
      //Get the LCDMcPart of this particle
      int mcidx=(*partItr);
      LCDMcPart Part = GetParticleByIdx(mcidx);
      //Get the 4 Momentum of this particle
      TLorentzVector mc4vec = Part.Get4Momentum();
      //Add up the total 4 Momentum of this jet
      Total = Total+mc4vec;
   }


   return Total;
}


TLorentzVector
MCFunctions::MCJetMeasuredTLorentzVector(int jetid)
{
   
   vector<int> JetPartsIdx;
   //Get all of the stable particles that descended from 
   //this quark or gluon.
   getIdxVectorOfStableDescendants(jetid,JetPartsIdx);   
   
   TLorentzVector Total(0,0,0,0);
   vector<int>::const_iterator partBegin = JetPartsIdx.begin();
   vector<int>::const_iterator partEnd   = JetPartsIdx.end();
   for(vector<int>::const_iterator partItr = partBegin;
       partItr != partEnd;
       ++partItr)
   {
      //Get the LCDMcPart of this particle
      int mcidx=(*partItr);
      //LCDMcPart Part = GetParticleByIdx(mcidx);
      
      //Add up the total 4 Momentum of this jet only if the stable particle
      //is charged

      if(isMeasured(mcidx) == 1 )
      {
	 //Get the 4 Momentum of this particle
	 TLorentzVector mc4vec = Get4VectorByMCIdx(mcidx);

	 Total = Total+mc4vec;
      }
   }


   return Total;
}


int
MCFunctions::MCJetNParts(int jetid)
{
   
   vector<int> JetPartsIdx;
   //Get all of the stable particles that descended from 
   //this quark or gluon.
   getIdxVectorOfStableDescendants(jetid,JetPartsIdx);   

   int nparts = JetPartsIdx.size();

   return nparts;
}



int
MCFunctions::MCJetNTracks(int jetid)
{
   
   vector<int> JetPartsIdx;
   //Get all of the stable particles that descended from 
   //this quark or gluon.
   getIdxVectorOfStableDescendants(jetid,JetPartsIdx);   
   int NTracks = 0;
   vector<int>::const_iterator partBegin = JetPartsIdx.begin();
   vector<int>::const_iterator partEnd   = JetPartsIdx.end();
   for(vector<int>::const_iterator partItr = partBegin;
       partItr != partEnd;
       ++partItr)
   {
      //Get the LCDMcPart of this particle
      int mcidx=(*partItr);
      LCDMcPart Part = GetParticleByIdx(mcidx);
      //check if it is charged
      double Charge = Part.GetCharge();
      if(fabs(Charge) > 0.01 )
      {
	 NTracks=NTracks+1;
      }
   }


   return NTracks;
}



      
      
      
      
 
//This is a function to look and see if there is a certain type of 
//SUSY decay in an event. Give it the SUSY parent you're looking for,
//the SUSY Child you're looking for, then it will return a code to
//tell you whether to decay is there, and what the other children were
//The code will be
// 0 : No Decay with that Parent and that Child
// 10+n+3nt : Decay exists. The other Children are leptons. n is the number of
//        electrons or muons, and nt is the number of Taus
//        example 12 is leptons that are both charged.
// 200+10*n+g : Decay exist. The other Children are quarks and gluons.
//              n is the number of uptype quarks (if 2 or 0 from a z decay)
//              g is the number of gluons.


int
MCFunctions::LookForSusyDecay(int ParentID, int ChildID)
{
   int present_idx = 0;
   //attempting to loop over mcparticles
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();

   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
  {

     int mcid=(*mcpartItr).GetParticleID();
     if( abs(mcid) == ParentID )
     {
	//We found the parent we're looking for, now see if they have the
	//correct children.
	
	//Now get a vector of children Idx
	vector<int> mcChildrenIdx;
	getIdxVectorOfChildren(present_idx, mcChildrenIdx);
	//Now loop over the children and see what they are
	int nlep = 0;
	int ntarget = 0;
	int nclep = 0;
	int nquark = 0;
	int ngluon = 0;
	int nuquark = 0;
	int ntau = 0;
	vector<int>::const_iterator childBegin =mcChildrenIdx.begin();
	vector<int>::const_iterator childEnd = mcChildrenIdx.end();
	for (vector<int>::const_iterator childItr = childBegin;
	     childItr != childEnd;
	     ++childItr)
	{
	   int childIdx = (*childItr);
	   LCDMcPart ChildPart = GetParticleByIdx(childIdx);
	   int childID = ChildPart.GetParticleID();
	   if( abs(childID) == ChildID ) ntarget=ntarget+1;
	   if( isLeptonID(childID) ) nlep=nlep+1;
	   // ntau is the number of tau leptons
	   if( abs(childID) == 15 ) ntau=ntau+1;
	   //nclep is the number of muons or electrons
	   if( abs(childID) == 11 || abs(childID) == 13 ) nclep=nclep+1;
	   if( abs(childID) > 0 && abs(childID) < 7 ) 
	   {
	      nquark=nquark+1;
	   }
	   if( (abs(childID) == 2 ) || (abs(childID) == 4 ) || 
	       (abs(childID) == 6) )
	      nuquark=nuquark+1;
	   if( childID == 21 || childID == 9 ) ngluon=ngluon+1;
	} //Loop over children finished
	if( (ntarget == 1) && (nlep == 2) && (nquark == 0) )
	{
	   int code=10+nclep+3*ntau;
	   //We found it, return the code
	   return code;
	}
	if( (ntarget == 1) && (nlep == 0) && (nquark == 2) )
	{
	   int code = 200 + 10*nuquark + ngluon;
	   //We found it, return the code
	   return code;
	}

     }


     present_idx=present_idx+1;
  }


   return 0;
}


int
MCFunctions::isMeasured(int mcidx)
{


   int MEASURED = 1;
   int NOTMEASURED = 0;
   Vector<LCDTrack>::const_iterator trackBegin =m_tracks.begin();
   Vector<LCDTrack>::const_iterator trackEnd = m_tracks.end();
   for (Vector<LCDTrack>::const_iterator trackItr = trackBegin;
	trackItr != trackEnd;
	++trackItr)
   {
      //Get the mcidx of the mcparticle that the track is tagged to
      int tagged_mcidx = (*trackItr).GetParticle();
      if( tagged_mcidx == mcidx) return MEASURED;
   }

   Vector<LCDCluster>::const_iterator clustBegin = m_clusters.begin();
   Vector<LCDCluster>::const_iterator clustEnd   = m_clusters.end();
   for(Vector<LCDCluster>::const_iterator clustItr = clustBegin;
       clustItr != clustEnd;
       ++clustItr)
   {
      int nentries = (*clustItr).GetMcListEntries();
      for(int npart=0; npart<nentries; npart++)
      {
	 int tagged_mcidx = (*clustItr).GetMcList()[npart];
	 if ( tagged_mcidx == mcidx) return MEASURED;
      }
   }


   return NOTMEASURED;

}     
      

//Give an mcidx number and the radial angle (in degrees) of a cone around
//the 4vector of this mcparticle, and it will return the total energy of
//other 4vectors in this cone.

double
MCFunctions::GetEEnclosed(int mcidx, double theta)
{

   double rads=theta/57.3;

   double ctheta=cos(rads);

   double Eenc=0.0;

   LCDMcPart Part1=GetParticleByIdx(mcidx);

   int current_idx=0;
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();
   for( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	mcpartItr != mcpartEnd;
	++mcpartItr)
   {
      if( mcidx != current_idx)
      {
	 if( isMeasured(current_idx) == 1)
	 {
	    //okay, so we found a particle, that is measured by the detector
	    //i.e. it either left a track, and or energy in the clusters
	    //Now lets find the cosine between them.
	    LCDMcPart Part2=(*mcpartItr);
//	    TLorentzVector mc4vec1=Part1.Get4Momentum();
//	    TLorentzVector mc4vec2=Part2.Get4Momentum();

	    //Now use measured 4 vec if requested.
	    TLorentzVector mc4vec1=Get4VectorByMCIdx(mcidx);
	    TLorentzVector mc4vec2=Get4VectorByMCIdx(current_idx);
	    
	    double Mag1 = sqrt( mc4vec1.Px()*mc4vec1.Px() +
				mc4vec1.Py()*mc4vec1.Py() +
				mc4vec1.Pz()*mc4vec1.Pz() );
	    double Mag2 = sqrt( mc4vec2.Px()*mc4vec2.Px() +
				mc4vec2.Py()*mc4vec2.Py() +
				mc4vec2.Pz()*mc4vec2.Pz() );
	    
	    double dotprod12 =  mc4vec2.Px()*mc4vec1.Px() +
	       mc4vec2.Py()*mc4vec1.Py() +
	       mc4vec2.Pz()*mc4vec1.Pz();
	    //Make sure both magnitudes are nonzero
	    if( Mag1 > 0.0 && Mag2 > 0.0 )
	    {
	       double cos12 = dotprod12/(Mag1*Mag2);
	       double e2=mc4vec2.E();
	       if( cos12 > ctheta) Eenc=Eenc+e2;
	    }

	 }
      }
      current_idx=current_idx+1;
   }


   return Eenc;

}


//This will return the measured 4 momentum of the entire event
//You can check for Energy conservation and missing momentum
TLorentzVector
MCFunctions::GetEventMeasured4Momentum()
{

   int current_idx=0;
   TLorentzVector Total4vec(0.0,0.0,0.0,0.0);
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();
   for( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	mcpartItr != mcpartEnd;
	++mcpartItr)
   {
      
      if( isMeasured(current_idx) == 1)
      {
	
//	 LCDMcPart Part=(*mcpartItr);
	 TLorentzVector the4vec = Get4VectorByMCIdx(current_idx);
	 Total4vec=Total4vec+the4vec;
      }      
      
      current_idx=current_idx+1;
   }


   return Total4vec;

}


//The point of this function is to do the DURHAM jet finding algorithm
//with all the measured 4 vectors, excluding isolated leptons, and then 
//to return vector of vector<int> that will contain the mcidx values
//for all of the particles in a particular jet. 

void
MCFunctions::RCGFindJets( vector< vector<int> >& jets )
{

   //Okay, lets attempt to setup the jetfinder.
   report(DEBUG,kFacilityString)<<"I am in RCGFindJets"<<endl;

   LCDJetFinder jetfind(m_DURHAM_YCUT);
   TClonesArray veclist("TLorentzVector", 1000);
   veclist.Delete(); //clean up veclist, this will hold all of the 4 vectors
   
   vector<int> MCIdxList; //Get a list of particles to include

   //Okay, now lets fill up the MCIdxList and the veclist
   //for the jet finding.
   int current_idx=0;
   int ntrk= 0;
//   report(NOTICE,kFacilityString)<<"I am about to loop through the mc "
//				 <<" particles "<<endl;
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd   = m_mcparticles.end();
   for( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	mcpartItr != mcpartEnd;
	++mcpartItr)
   {
      
      if ( isMeasured(current_idx) == 1) 
      {
//	 TLorentzVector mc4vec = (*mcpartItr).Get4Momentum();
	 //Get The Measured 4 vector instead
	 TLorentzVector mc4vec = Get4VectorByMCIdx(current_idx);
	 double mcE = mc4vec.E();
	 //int mcid = (*mcpartItr).GetParticleID();
	 //double Eenc = GetEEnclosed(current_idx,m_IsolLep_Deg);
	 //If it is not an isolated electron or muon, then add it
	 //to the jet list of 4 vectors
	 if( IsIsolatedLepton(current_idx) != 1)
	 {
	    
	    MCIdxList.insert(MCIdxList.end(),current_idx);
	    TLorentzVector* vec4 = new(veclist[ntrk]) TLorentzVector;
	    (*vec4).SetXYZT(mc4vec.Px(),mc4vec.Py(),mc4vec.Pz(),mc4vec.E());
	    ntrk=ntrk+1;
	    
	 } //If it is not an isolated electron or muon

      }//If it is measured

      current_idx=current_idx+1;
   }

   //If there are only two 4 vectors, then return with doing nothing
   if( MCIdxList.size() < 2 ) return;

   //Okay, now we have a vector of ints for the mcidx values, and in the
   //same order we have the corresponding 4 vectors ready to send to the
   //jetfinder. So, send it to the jetfinder


   jetfind.SetPartList(&veclist); //Filling in the 4vector list
   jetfind.SetDURHAM(); //setting fitting algorithm to DURHAM
   jetfind.SetYCut(m_DURHAM_YCUT); //Setting Ycut to 0.004
   jetfind.doFindJets(); //Finding jets
   int NJets = jetfind.njets();

   //Okay, we found the jets, now we have to pull out the list of
   //4vectors that went int each jet. This will be tricky.

   if(NJets < 1 || NJets > 100) return;
   for (int iJet=0; iJet < NJets; iJet++) //Loop over the jets
   {
      //Now loop through mcidx values
      int ipart=0;
      vector<int> ThisJetMcIdxList;
      //ThisJetMcIdxList.delete();

      vector<int>::const_iterator listBegin = MCIdxList.begin();
      vector<int>::const_iterator listEnd   = MCIdxList.end();
      for(vector<int>::const_iterator listItr = listBegin;
	  listItr != listEnd;
	  listItr++)
      {
	 if( jetfind.GetPartIndexAt(ipart) == iJet) //this part is in iJet
	 {
	    int theidx = (*listItr);
//	    report(NOTICE,kFacilityString)<<"Adding theidx "<<theidx
//					  <<" to "<<iJet<<endl;

	    ThisJetMcIdxList.insert(ThisJetMcIdxList.end(),theidx);

	 }

	 ipart=ipart+1; //increment the particle list identifier
      }

      //Now add this list to the jets list of vector<int>.
      jets.insert(jets.end(),ThisJetMcIdxList);

   }

   //Horray, we should now have a vector of vector<int>, where each
   //vector<int> contains the mcidx numbers for the particles included
   //in the jet.

   return;

}

//Given a vector<int> of mcidx's, sum up the total 4momentum

TLorentzVector
MCFunctions::GetTotal4Momentum(vector<int>& McIdxList )
{

   TLorentzVector Total4vec(0.0,0.0,0.0,0.0);
   vector<int>::const_iterator listBegin = McIdxList.begin();
   vector<int>::const_iterator listEnd   = McIdxList.end();
   for(vector<int>::const_iterator listItr = listBegin;
       listItr != listEnd;
       listItr++)
   {
      int theidx=(*listItr);
      if( isMeasured(theidx) == 1)
      {
//	 LCDMcPart Part = GetParticleByIdx(theidx);
	 TLorentzVector the4vec = Get4VectorByMCIdx(theidx);
	 Total4vec=Total4vec+the4vec;
      }
   }

   return Total4vec;
}


double
MCFunctions::GetTotalCharge(vector<int>& McIdxList )
{

   double TotalCharge;
   vector<int>::const_iterator listBegin = McIdxList.begin();
   vector<int>::const_iterator listEnd   = McIdxList.end();
   for(vector<int>::const_iterator listItr = listBegin;
       listItr != listEnd;
       listItr++)
   {
      int theidx=(*listItr);
      LCDMcPart Part = GetParticleByIdx(theidx);
      TotalCharge=TotalCharge+Part.GetCharge();
   }

   return TotalCharge;
}


int
MCFunctions::GetNumberOfTracksInList(vector<int>& McIdxList )
{

   int NTracks=0;
   vector<int>::const_iterator listBegin = McIdxList.begin();
   vector<int>::const_iterator listEnd   = McIdxList.end();
   for(vector<int>::const_iterator listItr = listBegin;
       listItr != listEnd;
       listItr++)
   {
      int theidx=(*listItr);
      LCDMcPart Part = GetParticleByIdx(theidx);
      int ismeas = isMeasured(theidx);
      if(ismeas == 1 && fabs(Part.GetCharge()) > 0.1) NTracks=NTracks+1;
   }

   return NTracks;
}


//Returns a number describing how well the particle content of IdxList1
//matches IdxList2. If the number is 1, it is a perfect match. If
//the number is -1 they have nothing in common. The closer to 1 you get
//the better the match.

double
MCFunctions::MatchQuality(vector<int>& IdxList1, vector<int>& IdxList2)
{


   //Get start and finish of list 1
   vector<int>::const_iterator list1Begin = IdxList1.begin();
   vector<int>::const_iterator list1End   = IdxList1.end();

   //Get start and finish of list 2
   vector<int>::const_iterator list2Begin = IdxList2.begin();
   vector<int>::const_iterator list2End   = IdxList2.end();


   //Now get the total energy of list 1
   double E1 = (GetTotal4Momentum(IdxList1)).E();


   //Now get the total energy of list 2
   double E2 = (GetTotal4Momentum(IdxList2)).E();


   //Now things start to get ugly. Get the energy of particles 
   //that are in list1, but NOT in list2.
   double E1n2=0.0;
   for(vector<int>::const_iterator list1Itr=list1Begin;
       list1Itr != list1End;
       list1Itr++)
   {
      int mcidx1 = (*list1Itr);
      int IsIn2  = 0;
      for(vector<int>::const_iterator list2Itr=list2Begin;
	  list2Itr !=list2End;
	  list2Itr++)
      {
	 int mcidx2 = (*list2Itr);
	 if( mcidx1 == mcidx2) IsIn2 = 1;
      }
      if(IsIn2 == 0)
      {
	 LCDMcPart Part = GetParticleByIdx(mcidx1);
	 E1n2=E1n2+Part.Get4Momentum().E();
      }
   }


   //Keep going. Now get the energy of particles 
   //that are in list2, but NOT in list1.
   double E2n1=0.0;
   for(vector<int>::const_iterator list2Itr=list2Begin;
       list2Itr != list2End;
       list2Itr++)
   {
      int mcidx2 = (*list2Itr);
      int IsIn1  = 0;
      for(vector<int>::const_iterator list1Itr=list1Begin;
	  list1Itr !=list1End;
	  list1Itr++)
      {
	 int mcidx1 = (*list1Itr);
	 if( mcidx2 == mcidx1) IsIn1 = 1;
      }
      if(IsIn1 == 0)
      {
	 LCDMcPart Part = GetParticleByIdx(mcidx2);
	 E2n1=E2n1+Part.Get4Momentum().E();
      }
   }



//Okay, one more, now we need the energy from particles that are in
//both lists.

   double E1a2=0.0;
   for(vector<int>::const_iterator list2Itr=list2Begin;
       list2Itr != list2End;
       list2Itr++)
   {
      int mcidx2 = (*list2Itr);
      int IsIn1  = 0;
      for(vector<int>::const_iterator list1Itr=list1Begin;
	  list1Itr !=list1End;
	  list1Itr++)
      {
	 int mcidx1 = (*list1Itr);
	 if( mcidx2 == mcidx1) IsIn1 = 1;
      }
      if(IsIn1 == 1)
      {
	 LCDMcPart Part = GetParticleByIdx(mcidx2);
	 E1a2=E1a2+Part.Get4Momentum().E();
      }
   }



   //Okay, now we everything we need.
   //Just double check that E1 and E2 are non-zero
   if( ! ((E1>0.0) && (E2>0.0))) return -500.0;

   //Okay, now calculate the match quality.
   //I have defined the match quality as
   // (2*E1a2-E1n2-E2n1)/(E1+E2)
   //Or, on other words, ( 2.0*(Energy in both lists) - (Energy in 1 not2)
   //                        -(Energy in 2 not 1))/((E in 1)+(E in 2))
   //If the lists are identical the matchqual will be 1
   //If the lists are completely different the matchqual will be -1
   //The closer to 1 the matchqual is, the more closely related the 
   //two lists are.

   double matchqual = (2.0*E1a2-E1n2-E2n1)/(E1+E2);

   return matchqual;

}

//Get the 4 vector of particle by it's mcidx. Only use on stable particles
//Will return either Generator level 4 vector or Measured 4 vector 
//depending on value of m_USE_GEN_LEVEL_4VEC
TLorentzVector 
MCFunctions::Get4VectorByMCIdx(int mcidx)
{
   TLorentzVector Return4Vec(0.0,0.0,0.0,0.0);

   //This will only return a non zero value if the particle is measured
   if(isMeasured(mcidx) != 1)
   {
      return Return4Vec;
   }
  
   //Now check and see whether they want the Generator Level 4 vector
   //or the measured 4 vector. Return different values depending on 
   //what they choose

   LCDMcPart Part = GetParticleByIdx(mcidx);


   if(m_USE_GEN_LEVEL_4VEC == 1 )
   {
      Return4Vec = Part.Get4Momentum();
      return Return4Vec;
   } // if m_USE_GEN_LEVEL_4VEC == 1
   else
   {
      //If you are in these brackets it means that they want the 
      //measured 4 vector, not the generator level one.

      
      Vector<LCDTrack>::const_iterator trackBegin =m_tracks.begin();
      Vector<LCDTrack>::const_iterator trackEnd = m_tracks.end();
      for (Vector<LCDTrack>::const_iterator trackItr = trackBegin;
	   trackItr != trackEnd;
	   ++trackItr)
      {
	 //Get the mcidx of the mcparticle that the track is tagged to
	 int tagged_mcidx = (*trackItr).GetParticle();
	 if( tagged_mcidx == mcidx) 
	 {
	    //We found a track tagged to our particle. 
	    //the most likely mass is the pion mass.
	    double pimass = 0.13957018;
	    double px = (*trackItr).GetMomentumPx(0.);
	    double py = (*trackItr).GetMomentumPy(0.);
	    double pz = (*trackItr).GetMomentumPz(0.);
	    //calculate the energy using the mass of the pion
	    double Energy = sqrt(pimass*pimass +
				 px*px +
				 py*py + 
				 pz*pz);
	    
	    TLorentzVector Hold4Vec(px,py,pz,Energy);
	    Return4Vec = Hold4Vec;
	    return Return4Vec;
	 } // if tagged_mcidx == mcidx
      } //for track loop
      
      
      //If you have gotten to this point, then it means that 
      //it was not tagged to a track. So in order
      //for it to have been measured, it must be in one of the clusters.


      //Leave open the possibility that the energy come from more
      //than one cluster.
      double energy = 0.0;
      double px = 0.0;
      double py = 0.0;
      double pz = 0.0;


      Vector<LCDCluster>::const_iterator clustBegin = m_clusters.begin();
      Vector<LCDCluster>::const_iterator clustEnd   = m_clusters.end();
      for(Vector<LCDCluster>::const_iterator clustItr = clustBegin;
	  clustItr != clustEnd;
	  ++clustItr)
      {
	 int nentries = (*clustItr).GetMcListEntries();
	 for(int npart=0; npart<nentries; npart++)
	 {
	    //For now, ignore the possibility of more than one 
	    //particles affecting a cluster.

	    int tagged_mcidx = (*clustItr).GetMcList()[npart];
	    if ( tagged_mcidx == mcidx) 
	    {

	       double Energy = (*clustItr).GetEnergy();
	       double theta  = (*clustItr).GetEnergyTheta();
	       double phi    = (*clustItr).GetEnergyPhi();
	       
	       //I'm going to try to get the momentum out using 
	       // E = mag(p) and theta phi to be that of momentum vector.
	       double Px = Energy*sin(theta)*cos(phi);
	       double Py = Energy*sin(theta)*sin(phi);
	       double Pz = Energy*cos(theta);
	       //Add up contributions from all clusters
	       energy=energy+Energy;
	       px=px+Px;
	       py=py+Py;
	       pz=pz+Pz;
	       
	    } //if tagged mcidx == mcidx
	 } //for loop over entries
      } //loop over cluster iterators

      TLorentzVector Hold4Vec(px,py,pz,energy);
      return Hold4Vec;
   } // else to m_USE_GEN_LEVEL_4VEC == 1


   return Return4Vec;
}


//Set the minimum energy of the isolated leptons
void
MCFunctions::Set_IsolLep_Ecut(double set)
{
   m_IsolLep_Ecut = set;
   return;
}

//Get the total Energy of the tracks
double
MCFunctions::GetTotalEnergyOfTracks()
{
      
   
   double Etracks = 0.0;

   Vector<LCDTrack>::const_iterator trackBegin =m_tracks.begin();
   Vector<LCDTrack>::const_iterator trackEnd = m_tracks.end();
   for (Vector<LCDTrack>::const_iterator trackItr = trackBegin;
	trackItr != trackEnd;
	++trackItr)
   {

      //the most likely mass is the pion mass.
      double pimass = 0.13957018;
      double px = (*trackItr).GetMomentumPx(0.);
      double py = (*trackItr).GetMomentumPy(0.);
      double pz = (*trackItr).GetMomentumPz(0.);
      //calculate the energy using the mass of the pion
      double Energy = sqrt(pimass*pimass +
			   px*px +
			   py*py + 
			   pz*pz);
      Etracks = Etracks + Energy;
      
   } //for track loop
   
   return Etracks;
   
}


//Get the total Energy of the isolated clusters
double
MCFunctions::GetTotalEnergyOfIsolatedClusters()
{
   //This will behave differently depending on what is available for
   //us to use.

   if(m_ISOLATED_CLUSTERS_LOADED == 1 )
   {
      double Energy = 0.0;

      FATable<LCDIsolateCluster>::const_iterator clustBegin = 
	 m_IsolateCluster.begin();
      FATable<LCDIsolateCluster>::const_iterator clustEnd =
	 m_IsolateCluster.end();
      for(FATable<LCDIsolateCluster>::const_iterator clustItr = clustBegin;
	  clustItr != clustEnd;
	  clustItr++)
      {
	 LCDCluster theclust = *((*clustItr).cluster());
	 Energy = Energy+theclust.GetEnergy();
      }

      return Energy;

   }
   else
   {
      //In this case, you haven't loaded the isolated clusters. So,
      //we will get the total energy, the energy of the tracks, and 
      //then subtract them.
      double Etrck = GetTotalEnergyOfTracks();
      TLorentzVector event4vec = GetEventMeasured4Momentum();
      double Eevent = event4vec.E();
      double Eisoclust = Eevent - Etrck;
      return Eisoclust;
   }
   //Problem
   return -100.0;
}

//Fill the EventShape variables
void
MCFunctions::FillEventShape()
{
   // create a vector to put all of the jets/tracks/clusters in
   // in this case, just two jets
   STL_VECTOR( KTKinematicData ) tracksForEventShape;
   

   int current_idx=0;
   int nvec=0;
   //Fill in a KTKinematicData for each measured 4 vector
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd   = m_mcparticles.end();
   for( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	mcpartItr != mcpartEnd;
	++mcpartItr)
   {
	 
      
      if ( isMeasured(current_idx) == 1) 
      {
	 //Get The Measured 4 vector
	 TLorentzVector mc4vec = Get4VectorByMCIdx(current_idx);
	 double mcE = mc4vec.E();
	 
	 //const HepVector3D& momentum1 = (mc4vec.Px(), mc4vec.Py(), mc4vec.Pz());
	 double holdx=mc4vec.Px();
	 double holdy=mc4vec.Py();
	 double holdz=mc4vec.Pz();
	 HepVector3D momentum1 = HepVector3D(holdx,holdy,holdz);

//	 const HepPoint3D& position1 = (0.0, 0.0, 0.0, 0.0);
	 const HepPoint3D& position1 = (0.0, 0.0, 0.0);
	 const double mass1 = mc4vec.M();
//	 report(NOTICE,kFacilityString)<<"holdx "<<holdx<<" holdy "<<holdy<<" holdz "<<holdz<<endl;
//	 report(NOTICE,kFacilityString)<<"momentum1 "<<momentum1<<" mass "<<mass1<<endl;
	 double holdx2=momentum1.x();
	 double holdy2=momentum1.y();
	 double holdz2=momentum1.z();
//	 report(NOTICE,kFacilityString)<<"holdx2 "<<holdx2<<" holdy2 "<<holdy2<<" holdz2 "<<holdz2<<endl;
	 const double jcharge1 = 1.0;
	 KTKinematicData ktKinematicData1(momentum1, position1, mass1, jcharge1);
	 // make a list of the stuff we want in the event shape
	 tracksForEventShape.push_back( ktKinematicData1 );
	 nvec=nvec+1;
	 
      }

      current_idx=current_idx+1;
   }


   //Okay, now lets test the KTKinematicData
   
   STL_VECTOR(KTKinematicData)::const_iterator itPart1;
  
   Hep3Vector pt(0.,0.,0.);
   for ( itPart1 = tracksForEventShape.begin(); 
	 itPart1 != tracksForEventShape.end(); ++itPart1 )
   {  
//      report(NOTICE,kFacilityString)<<"RCG24:Running sum of pt "<<pt<<endl;
      pt += itPart1->momentum();
   }
   

   if(nvec>1)
   {
      //Now Pass the list to EventShape
      float beamenergy = 500.0;
      EventShape eventShape( beamenergy, tracksForEventShape.begin(), 
			     tracksForEventShape.end() ); 
      
      
      //Now fill our event shape variables.
      
      m_fw0 = eventShape.nthFoxWolframMoment(0);
      m_fw1 = eventShape.nthFoxWolframMoment(1);
      m_fw2 = eventShape.nthFoxWolframMoment(2);
      m_fw3 = eventShape.nthFoxWolframMoment(3);
      m_fw4 = eventShape.nthFoxWolframMoment(4);
      m_planarity = eventShape.planarity();
      m_sphericity = eventShape.sphericity();
//DUH!!!! the magnitude is always 1. Get z for the cosine of the vector
//      m_spherocity = eventShape.spherocity().mag();
//      m_thrust = eventShape.thrust().mag();
      m_spherocity = eventShape.spherocity().z();
      m_thrust = eventShape.thrust().z();
//      report(NOTICE,kFacilityString)<<"nvec is "<<nvec<<endl;
//      report(NOTICE,kFacilityString)<<"Thrust is "<<eventShape.thrust()<<endl;
//      report(NOTICE,kFacilityString)<<"Thrust z() is "<<eventShape.thrust().z()<<endl;
   }

   return;

}


double 
MCFunctions::get_EventShape_fw1()
{
   return m_fw1;
}


double 
MCFunctions::get_EventShape_fw2()
{
   return m_fw2;
}


double 
MCFunctions::get_EventShape_fw3()
{
   return m_fw3;
}


double 
MCFunctions::get_EventShape_fw4()
{
   return m_fw4;
}

double
MCFunctions::get_EventShape_planarity()
{
   return m_planarity;
}

double
MCFunctions::get_EventShape_sphericity()
{
   return m_sphericity;
}

double
MCFunctions::get_EventShape_spherocity()
{
   return m_spherocity;
}

double
MCFunctions::get_EventShape_thrust()
{
   return m_thrust;
}






//Set the maximum energy of the isolated leptons
void
MCFunctions::Set_IsolLep_Emax(double set)
{
   m_IsolLep_Emax = set;
   return;
}

//Set the maximum deviation of E/p from 1.0 in lepton finding.
void
MCFunctions::Set_IsolLep_EoP(double set)
{
   m_IsolLep_EoP = set;
   return;
}

//Set the half angle (in degrees) of the cone around the lepton that we
//test for isolation
void
MCFunctions::Set_IsolLep_Deg(double set)
{
   m_IsolLep_Deg = set;
   return;
}

//Set the maxium amount of energy that can be found in the cone around
//the isolated lepton
void
MCFunctions::Set_IsolLep_Eenc(double set)
{
   m_IsolLep_Eenc = set;
   return;
}

//Set the value of the YCUT variable used in jetfinding algorithm
void
MCFunctions::Set_DURHAM_YCUT(double set)
{
   m_DURHAM_YCUT = set;
   return;
}


//Set whether or not to use generator level 4 vectors
void
MCFunctions::Set_USE_GEN_LEVEL_4VEC(int set)
{
   m_USE_GEN_LEVEL_4VEC = set;
   return;
}

//void
//MCFunctions::Load_LCDMatchTrack(FATable<LCDMatchTrack>& matchedtracks)
//{
//   m_TrckClustMatches = matchedtracks;
//   m_MATCHED_TRACKS_LOADED = 1;
//   return;
//}



//
// constructors and destructor
//
//MCFunctions::MCFunctions( void )               // anal1
MCFunctions::MCFunctions( Vector<LCDMcPart>& mcparts, 
			  Vector<LCDTrack>& tracks,
			  Vector<LCDCluster>& clusters)               // anal1
   : m_mcparticles( mcparts ),
     m_tracks( tracks),
     m_clusters( clusters)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   //Initialize the lepton isolation cut variables
   m_IsolLep_Ecut = 10.0;//GeV
   m_IsolLep_Emax =500.0; //GeV
   m_IsolLep_Deg  = 20.0;//Degree
   m_IsolLep_Eenc =  2.0;//GeV
   m_IsolLep_EoP = 0.075;//Maximum deviation of E/p from 1.0 for lepton.
   //Initialize the jetfinding YCUT variable
   m_DURHAM_YCUT = 0.004; //unitless
   //Initialize whether or not to use Generator level 4vectors
   m_USE_GEN_LEVEL_4VEC = 1; //1 means yes, 0 means no

   //set this to 0
   m_MATCHED_TRACKS_LOADED = 0; //0 means no, 1 means yes.
   //set this to 0
   m_ISOLATED_CLUSTERS_LOADED = 0; //0 means no, 1 means yes

   //Initialize the EventShapeVariables to some ridiculous values
   m_fw1=-1000000.0;
   m_fw2=-1000000.0;
   m_fw3=-1000000.0;
   m_fw4=-1000000.0;
   m_planarity=-1000000.0;
   m_sphericity=-1000000.0;
   m_spherocity=-1000000.0;
   m_thrust=-1000000.0;

}




MCFunctions::MCFunctions( Vector<LCDMcPart>& mcparts, 
			  Vector<LCDTrack>& tracks,
			  Vector<LCDCluster>& clusters,
			  FATable<LCDMatchTrack>& matchedtracks)               // anal1
   : m_mcparticles( mcparts ),
     m_tracks( tracks),
     m_clusters( clusters),
     m_TrckClustMatches(matchedtracks)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   //Initialize the lepton isolation cut variables
   m_IsolLep_Ecut = 10.0;//GeV
   m_IsolLep_Emax =500.0; //GeV
   m_IsolLep_Deg  = 20.0;//Degree
   m_IsolLep_Eenc =  2.0;//GeV
   m_IsolLep_EoP = 0.075;//Maximum deviation of E/p from 1.0 for lepton.
   //Initialize the jetfinding YCUT variable
   m_DURHAM_YCUT = 0.004; //unitless
   //Initialize whether or not to use Generator level 4vectors
   m_USE_GEN_LEVEL_4VEC = 1; //1 means yes, 0 means no
   //Initialize this to 0
   m_MATCHED_TRACKS_LOADED = 1; //0 means no, 1 means yes.
   //Initialize this to 0
   m_ISOLATED_CLUSTERS_LOADED = 0; //0 means no, 1 means yes


   //Initialize the EventShapeVariables to some ridiculous values
   m_fw1=-1000000.0;
   m_fw2=-1000000.0;
   m_fw3=-1000000.0;
   m_fw4=-1000000.0;
   m_planarity=-1000000.0;
   m_sphericity=-1000000.0;
   m_spherocity=-1000000.0;
   m_thrust=-1000000.0;

}



MCFunctions::MCFunctions( Vector<LCDMcPart>& mcparts, 
			  Vector<LCDTrack>& tracks,
			  Vector<LCDCluster>& clusters,
			  FATable<LCDIsolateCluster>& isoclusts)               // anal1
   : m_mcparticles( mcparts ),
     m_tracks( tracks),
     m_clusters( clusters),
     m_IsolateCluster(isoclusts)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   //Initialize the lepton isolation cut variables
   m_IsolLep_Ecut = 10.0;//GeV
   m_IsolLep_Emax =500.0; //GeV
   m_IsolLep_Deg  = 20.0;//Degree
   m_IsolLep_Eenc =  2.0;//GeV
   m_IsolLep_EoP = 0.075;//Maximum deviation of E/p from 1.0 for lepton.
   //Initialize the jetfinding YCUT variable
   m_DURHAM_YCUT = 0.004; //unitless
   //Initialize whether or not to use Generator level 4vectors
   m_USE_GEN_LEVEL_4VEC = 1; //1 means yes, 0 means no
   //Initialize this to 0
   m_MATCHED_TRACKS_LOADED = 0; //0 means no, 1 means yes.
   m_ISOLATED_CLUSTERS_LOADED = 1; //0 means no, 1 means yes


   //Initialize the EventShapeVariables to some ridiculous values
   m_fw1=-1000000.0;
   m_fw2=-1000000.0;
   m_fw3=-1000000.0;
   m_fw4=-1000000.0;
   m_planarity=-1000000.0;
   m_sphericity=-1000000.0;
   m_spherocity=-1000000.0;
   m_thrust=-1000000.0;

}


MCFunctions::MCFunctions( Vector<LCDMcPart>& mcparts, 
			  Vector<LCDTrack>& tracks,
			  Vector<LCDCluster>& clusters,
			  FATable<LCDMatchTrack>& matchedtracks,
			  FATable<LCDIsolateCluster>& isoclusts)               // anal1
   : m_mcparticles( mcparts ),
     m_tracks( tracks),
     m_clusters( clusters),
     m_TrckClustMatches(matchedtracks),
     m_IsolateCluster(isoclusts)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   //Initialize the lepton isolation cut variables
   m_IsolLep_Ecut = 10.0;//GeV
   m_IsolLep_Emax =110.0; //GeV
   m_IsolLep_Deg  = 20.0;//Degree
   m_IsolLep_Eenc =  2.0;//GeV
   m_IsolLep_EoP = 0.075;//Maximum deviation of E/p from 1.0 for lepton.
   //Initialize the jetfinding YCUT variable
   m_DURHAM_YCUT = 0.004; //unitless
   //Initialize whether or not to use Generator level 4vectors
   m_USE_GEN_LEVEL_4VEC = 1; //1 means yes, 0 means no
   //Initialize this to 0
   m_MATCHED_TRACKS_LOADED = 1; //0 means no, 1 means yes.
   m_ISOLATED_CLUSTERS_LOADED = 1; //0 means no, 1 means yes


   //Initialize the EventShapeVariables to some ridiculous values
   m_fw1=-1000000.0;
   m_fw2=-1000000.0;
   m_fw3=-1000000.0;
   m_fw4=-1000000.0;
   m_planarity=-1000000.0;
   m_sphericity=-1000000.0;
   m_spherocity=-1000000.0;
   m_thrust=-1000000.0;
   


}


//Return the scale factor of the file. Note, that only files from the 
//SLAC background database have these scale factors. For all other files,
//it will return 1.0
double
MCFunctions::GetScaleFactor()
{

   double scale;
   scale=1.0;
   int scale_status=908070;

   int present_idx = 0;
   //attempting to loop over mcparticles
   Vector<LCDMcPart>::const_iterator mcpartBegin = m_mcparticles.begin();
   Vector<LCDMcPart>::const_iterator mcpartEnd = m_mcparticles.end();

   for ( Vector<LCDMcPart>::const_iterator mcpartItr = mcpartBegin;
	 mcpartItr !=mcpartEnd;
	 ++mcpartItr)
  {
     
     if( (*mcpartItr).GetStatus() == scale_status ) 
     {
	scale=(*mcpartItr).Get4Momentum().E();
	return scale;
     }

     present_idx=present_idx+1;
  }

   return scale;
}







MCFunctions::~MCFunctions()                    // anal5
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
//void
//MCFunctions::init( Vector<LCDMcPart>& m_mcparticles  )          // anal1 "Interactive"
//{
//   report( DEBUG, kFacilityString ) << "here in init()" << endl;
//
//   // do any initialization here based on Parameter Input by User
//   // (e.g. run expensive algorithms that are based on parameters
//   //  specified by user at run-time)
//
//}



void
MCFunctions::init()          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;


   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

//void
//MCFunctions::set(Vector<LCDMcPart>& mcparts)
//{
//
//   m_mcparticles=mcparts;
//
//   test_num=1.2;
//}


// -------------------- terminate method ----------------------------
void
MCFunctions::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
//void
//MCFunctions::hist_book( HIHistoManager& iHistoManager )
//{
//   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;
//
//   // book your histograms here
//
//}

// --------------------- methods bound to streams -------------------
//ActionBase::ActionResult
//MCFunctions::event( Frame& iFrame )          // anal3 equiv.
//{
//   report( DEBUG, kFacilityString ) << "here in event()" << endl;
//
//
//
//
//
//   return ActionBase::kPassed;
//}

/*
ActionBase::ActionResult
MCFunctions::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
MCFunctions::endRun( Frame& iFrame )         // anal4 equiv.
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


//   if( m_USE_GEN_LEVEL_4VEC == 0 && m_MATCHED_TRACKS_LOADED == 1)
//   {
//      iselectron = 0; //set this to zero until we see otherwise
//      //Loop through the track shower matches. Try to find one 
//      //that is tagged to this mcidx
//      FATable<LCDMatchTrack>::const_iterator mtrckBegin = 
//	 m_TrckClustMatches.begin();
//      FATable<LCDMatchTrack>::const_iterator mtrckEnd = 
//	 m_TrckClustMatches.end();
//
//      double emclust = 0.0;
//      double pmag = 0.0;
//
//      for(FATable<LCDMatchTrack>::const_iterator mtrckItr = mtrckBegin;
//	  mtrckItr != mtrckEnd;
//	  mtrckItr++)
//      {
//	 LCDTrack theTrack = (*mtrckItr).track();
//	 int themcidx = theTrack.GetParticle();
//	 //If the track is matched to the particle we're looking at
//	 if( themcidx == mcidx)
//	 {
//	    emclust = (*mtrckItr).emEnergy();
//	    double px = theTrack.GetMomentumPx(0.);
//	    double py = theTrack.GetMomentumPy(0.);
//	    double pz = theTrack.GetMomentumPz(0.);
//	    pmag = sqrt(px*px+py*py+pz*pz);
//	    break; // we got what we want. get out of here.
//	 } //if themcidx = mcidx
//     } // track match loop
//     
//     if( pmag > 0.0 )
//     {
//	 double eop = emclust/pmag;
//	 if( fabs(eop-1.0) < m_IsolLep_EoP) iselectron = 1;
//	 //set iselectron to 1 if it passes the E/p cut
//     }
//  } //If use bla bla bla








