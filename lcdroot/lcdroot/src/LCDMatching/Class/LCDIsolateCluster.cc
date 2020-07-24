// -*- C++ -*-
//
// Package:     <LCDMatching>
// Module:      LCDIsolateCluster
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
#include "LCDMatching/LCDIsolateCluster.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "LCDMatching.LCDIsolateCluster" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.7 2004/02/12 02:14:38 pcs Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDIsolateCluster::LCDIsolateCluster()
   : m_cluster(NULL)
   , m_closest(100000.)
   , m_identifier(0)
{
   report(EMERGENCY, kFacilityString)
      << "LCDIsolateCluster default constructor is being called!" << endl;
}

LCDIsolateCluster::LCDIsolateCluster(Identifier id, const LCDCluster* iCluster)
   : m_cluster(iCluster)
   , m_closest(100000.)
   , m_identifier(id)
{
}

// LCDIsolateCluster::LCDIsolateCluster( const LCDIsolateCluster& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

LCDIsolateCluster::~LCDIsolateCluster()
{
}

//
// assignment operators
//
// const LCDIsolateCluster& LCDIsolateCluster::operator=( const LCDIsolateCluster& rhs )
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

LCDIsolateCluster::Identifier LCDIsolateCluster::identifier() const {
   return m_identifier;
}

const LCDCluster* LCDIsolateCluster::cluster() const {
   return m_cluster;
}

const vector<const LCDTrack*>& LCDIsolateCluster::track() const {
   return m_track;
}

const vector<double>& LCDIsolateCluster::distance() const {
   return m_distance;
}

double LCDIsolateCluster::closest() const {
   return m_closest;
}

void LCDIsolateCluster::addTrack(const LCDTrack* iTrack, double iDistance) {
   m_track.push_back(iTrack);
   m_distance.push_back(iDistance);
   if (iDistance < m_closest) m_closest = iDistance;
}

//
// const member functions
//

//
// static member functions
//
