// -*- C++ -*-
#if !defined(MCFUNCTIONS_MCFUNCTIONS_H)
#define MCFUNCTIONS_MCFUNCTIONS_H
//
// Package:     <MCFunctions>
// Module:      MCFunctions
//
/**\class MCFunctions MCFunctions.h MCFunctions/MCFunctions.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Richard Gray
// Created:     Fri Jun 25 15:33:37 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
//#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "LCDRootAccess/Vector.h"


#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
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

using LCDRootAccess::Vector;

// forward declarations

class MCFunctions// : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
//      MCFunctions( void );                      // anal1 
      MCFunctions( Vector<LCDMcPart>& mcparts, Vector<LCDTrack>& tracks, 
		   Vector<LCDCluster>& clusters);                      // anal1 
      //Overload for loading in TrackMatches too
      MCFunctions( Vector<LCDMcPart>& mcparts, Vector<LCDTrack>& tracks, 
		   Vector<LCDCluster>& clusters,
		   FATable<LCDMatchTrack>& matchedtracks);                     

      //Overload for loading IsolatedClusters
      MCFunctions( Vector<LCDMcPart>& mcparts, Vector<LCDTrack>& tracks, 
		   Vector<LCDCluster>& clusters,
		   FATable<LCDIsolateCluster>& isoclusts);     
      //Overload for loading both matchedtracks and isolated clusters
      MCFunctions( Vector<LCDMcPart>& mcparts, Vector<LCDTrack>& tracks, 
		   Vector<LCDCluster>& clusters,
		   FATable<LCDMatchTrack>& matchedtracks,
		   FATable<LCDIsolateCluster>& isoclusts);           


 // anal1 
      virtual ~MCFunctions();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      //virtual void init( Vector<LCDMcPart>& m_mcparticles  );// anal1 "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      //virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      //virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      //---------------------------------------------------------------
      //Given the idx in the mcparticles list, it will return the LCDMcPart
      //of that particle
      LCDMcPart GetParticleByIdx(int particle_idx);	 
      //---------------------------------------------------------------

      //---------------------------------------------------------------
      //Get an int vector of the idx values of the children of a parent
      //with idx value parent_idx
      void getIdxVectorOfChildren( int parent_idx, vector<int>& mcChildrenIdx);
      //---------------------------------------------------------------

      //---------------------------------------------------------------
      //Get the idx values of the quarks and gluons in the event, these
      //will be the sires of the jets
      void getIdxVectorOfJets( vector<int>& mcJetsIdx);
      //---------------------------------------------------------------

      //---------------------------------------------------------------
      //Get a list of all of the stable descendants of a given particle.
      //This will be important for the jets
      void getIdxVectorOfStableDescendants( int parent_idx,
					    vector<int>& mcStableDescendIdx);
      //---------------------------------------------------------------

      
      //---------------------------------------------------------------
      // Get a 4 vector of the total 4vector of the jet
      TLorentzVector MCJetTotalTLorentzVector(int jetid);
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      // Get a 4 vector of just the charged tracks in the jet
      TLorentzVector MCJetMeasuredTLorentzVector(int jetid);
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      // Returns the number of stable particles in the jet
      int MCJetNParts(int jetid);
      //---------------------------------------------------------------



      //---------------------------------------------------------------
      // Returns the number of stable tracks in the jet
      int MCJetNTracks(int jetid);
      //---------------------------------------------------------------

      //---------------------------------------------------------------
      // Returns a code for whether or not we had a decay of a parent
      // of ID ParentID going to a child of ID ChildID plus other stuff.
      // It is zero if it did not occur in this event.
      // It is a numerical code to let you know what the other stuff was
      // if it did occur.
      //
      // If the other stuff is 2 leptons the return code is
      // 10 + Number of E or MU + 3*(Number of Tau)
      // i.e. if it is an e+ e- or mu+ mu- the code is 12
      // i.e. if it is NUE NUEB or NUMU NUMUB or NUTAU NUTAUB the code is 10
      // i.e. if it is Tau+ Tau- the code is 16
      //
      // If the other stuff is 2 quarks with possible gluons the code is
      // 200 + 10*(Number of uptype quarks) + (Number of gluons)
      // i.e. 200 is either d dbar, s sbar, b bbar
      // i.e. 220 is either u ubar, c cbar, or t tbar
      // i.e. 201 and 221 produced 2 quarks and 1 gluon
      int LookForSusyDecay(int ParentID, int ChildID);
      //---------------------------------------------------------------

      //---------------------------------------------------------------
      //Given an mcidx, return 1 if either a track or a cluster is 
      //tagged to this mcparticle, and zero otherwise.
      int isMeasured(int mcidx);
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      //This is a function that will return the energy of all measured
      //particles that are within a cone of half angle theta (degrees)
      //around the particle with mcidx idx.
      double GetEEnclosed(int mcidx, double theta);
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      //Given a list of mcidx values in a vector<int>, it will return 
      //the total 4momentum of those mcparticles.
      TLorentzVector GetTotal4Momentum(vector<int>& McIdxList );
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      //Given a list of mcidx values in a vector<int>, it will return 
      //the total 4momentum of those mcparticles.
      double GetTotalCharge(vector<int>& McIdxList );
      //---------------------------------------------------------------


      //---------------------------------------------------------------
      //It will run the JetFinder DURHAM algorithm to find jets.
      //using all measureable 4 vectors that do not pass isolated lepton
      //cuts. Then, it will output a vector of vector<int> where 
      //each vector<int> is the list of mcidx of particles that were
      //put into that jet. This can be more useful than what was given 
      //to us by the JetFinder
      void RCGFindJets( vector< vector<int> >& jets );
      //---------------------------------------------------------------


      //----------------------------------------------------------------
      //This will return a number telling you how closely one list
      //of mcidx is to another list of mcidx. It should return 1 if they
      //are perfectly matched, and it should return -1 if they are perfectly
      //mismatched, and it will return -500 if one of the lists is 
      //empty.
      double MatchQuality(vector<int>& IdxList1, vector<int>& IdxList2);
      //----------------------------------------------------------------


      //----------------------------------------------------------------
      //This will get the total energy of all unmatched showers in the event
      //It will work faster if you have loaded isolated clusters
      double GetTotalEnergyOfIsolatedClusters();
      //----------------------------------------------------------------


      //----------------------------------------------------------------
      // Added by Laura Fields
      // This will function takes a vector of TLorenzVectors and returns
      // an EventShape object
      //----------------------------------------------------------------
      void FillEventShape();
      //---------------------------------------------------------------


      //----------------------------------------------------------------
      //This will get the total energy of all of the tracks in the event
      double GetTotalEnergyOfTracks();
      //----------------------------------------------------------------

      


      //----------------------------------------------------------------
      //Get an idx Vector of Isolated Leptons, or leptons that pass 
      //the isolation cuts we made up.
      void getIdxVectorOfIsolatedLepton( vector<int>& isoLep);
      //----------------------------------------------------------------


      //----------------------------------------------------------------
      //Get the total 4 Momentum of all of the particles measured either
      //as a track or in a cluster.
      TLorentzVector GetEventMeasured4Momentum();
      //----------------------------------------------------------------


      //----------------------------------------------------------------
      //Get the 4 vector of the particle by mcidx vale. 
      //Depending on value of USE_GEN_LEVEL_4VEC it will either
      //Return the Generator level 4 vector, or the 4 vector reconstructed
      //by the Fast Monte Carlo
      TLorentzVector Get4VectorByMCIdx(int mcidx);
      //----------------------------------------------------------------



      //----------------------------------------------------------------
      int GetNumberOfTracksInList(vector<int>& McIdxList);
      //----------------------------------------------------------------


      //----------------------------------------------------------------
      //Given the mcidx value it will return 1 if it passes cuts for
      //and isolated e or mu, and 0 otherwise.
      int IsIsolatedLepton(int mcidx);
      //----------------------------------------------------------------
      
      


      //----------------------------------------------------------------
      //Functions for setting Lepton isolation parameters
      //and jet finding parameters
      void Set_IsolLep_Ecut(double set);
      void Set_IsolLep_Emax(double set);
      void Set_IsolLep_Deg(double set);
      void Set_IsolLep_Eenc(double set);
      void Set_IsolLep_EoP(double set);
      void Set_DURHAM_YCUT(double set);
      void Set_USE_GEN_LEVEL_4VEC(int set);
      //void Load_LCDMatchTrack(FATable< LCDMatchTrack>& matchedtracks);
      //----------------------------------------------------------------


      //---------------------------------------------------------------
      //Functions for getting at event shape variables.
      double get_EventShape_fw1();
      double get_EventShape_fw2();
      double get_EventShape_fw3();
      double get_EventShape_fw4();
      double get_EventShape_planarity();
      double get_EventShape_sphericity();
      double get_EventShape_spherocity();
      double get_EventShape_thrust();
      //----------------------------------------------------------------

      //----------------------------------------------------------------
      // Function for getting out the scale factor
      double GetScaleFactor();
      //----------------------------------------------------------------


      Vector<LCDMcPart>& m_mcparticles;
      Vector<LCDTrack>& m_tracks;
      Vector<LCDCluster>& m_clusters;
      FATable< LCDMatchTrack > m_TrckClustMatches;
      FATable< LCDIsolateCluster > m_IsolateCluster;


      //This is the minimum energy of an isolated lepton
      double m_IsolLep_Ecut;
      //This is the maximum energy of an isolated lepton
      double m_IsolLep_Emax;
      //This is the half angle of the cone around the lepton
      double m_IsolLep_Deg;
      //This is the maxium energy that can be enclose in the cone (GeV)
      double m_IsolLep_Eenc;
      //This is the distance from 1.0 that E(emCal)/P can be for it to
      //be an isolated lepton
      double m_IsolLep_EoP;
      //This is the YCUT value for the jet finder
      double m_DURHAM_YCUT;
      //This is an integer, 1 for use Measured 4 vector of particles
      //and 0 for using 4vector from tracking/calorimeter
      int    m_USE_GEN_LEVEL_4VEC;
      //This is 1 if a table of track shower matches has been loaded, 0
      //otherwise
      int m_MATCHED_TRACKS_LOADED;
      //This is 1 if a table of isolated shower matches have been loaded, 0
      //otherwise
      int m_ISOLATED_CLUSTERS_LOADED;

      //-------------------------------------------------------------
      //These are event shape variables. I can't figure out how to pass
      //an event shape object. (???)
      double m_fw0;
      double m_fw1;
      double m_fw2;
      double m_fw3;
      double m_fw4;
      double m_planarity;
      double m_sphericity;
      double m_spherocity;
      double m_thrust;
      //-------------------------------------------------------------

      


      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      MCFunctions( const MCFunctions& );

      // ------------ assignment operator(s) ---------------------
      const MCFunctions& operator=( const MCFunctions& );

      // ------------ private member functions -------------------
//      void bind( 
//         ActionBase::ActionResult (MCFunctions::*iMethod)( Frame& ),
//	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      double test_num;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MCFUNCTIONS_MCFUNCTIONS_H */






