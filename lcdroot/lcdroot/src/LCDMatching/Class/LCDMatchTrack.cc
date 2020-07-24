// -*- C++ -*-
//
// Package:     <LCDMatching>
// Module:      LCDMatchTrack
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed Jun 16 11:14:56 EDT 2004
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
#include "Experiment/report.h"
#include "LCDMatching/LCDMatchTrack.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "LCDMatching.LCDMatchTrack" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.7 2004/02/12 02:14:38 pcs Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDMatchTrack::LCDMatchTrack()
   : m_track(NULL)
   , m_emEnergy(0.)
   , m_hadEnergy(0.)
   , m_identifier(0)
{
   report(EMERGENCY, kFacilityString)
      << "LCDMatchTrack default constructor is being called!" << endl;
}

LCDMatchTrack::LCDMatchTrack(Identifier id, const LCDTrack* iTrack)
   : m_track(iTrack)
   , m_emEnergy(0.)
   , m_hadEnergy(0.)
   , m_identifier(id)
{
}

// LCDMatchTrack::LCDMatchTrack( const LCDMatchTrack& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

LCDMatchTrack::~LCDMatchTrack()
{
}

//
// assignment operators
//
// const LCDMatchTrack& LCDMatchTrack::operator=( const LCDMatchTrack& rhs )
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

LCDMatchTrack::Identifier LCDMatchTrack::identifier() const {
   return m_identifier;
}

const LCDTrack* LCDMatchTrack::track() const {
   return m_track;
}

const vector<const LCDCluster*>& LCDMatchTrack::cluster() const {
   return m_cluster;
}

const vector<double>& LCDMatchTrack::distance() const {
   return m_distance;
}

double LCDMatchTrack::emEnergy() const {
   return m_emEnergy;
}

double LCDMatchTrack::hadEnergy() const {
   return m_hadEnergy;
}

void LCDMatchTrack::addCluster(const LCDCluster* iCluster, double iDistance) {
   m_cluster.push_back(iCluster);
   m_distance.push_back(iDistance);
   if (iCluster->GetSystem() == 0) m_emEnergy += iCluster->GetEnergy();
   else if (iCluster->GetSystem() == 1) m_hadEnergy += iCluster->GetEnergy();
   else report(NOTICE, kFacilityString)
      << "I've never seen a " << iCluster->GetSystem() << "-system cluster before!" << endl;
}

//
// const member functions
//

//
// static member functions
//
