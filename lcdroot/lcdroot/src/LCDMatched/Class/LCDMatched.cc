// -*- C++ -*-
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDMatched
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed May  5 13:40:21 EDT 2004
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
//#include "Experiment/report.h"
#include "LCDMatched/LCDMatched.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "LCDTrackShowerMatchingProd.LCDMatched" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDMatched::LCDMatched()
   : m_identifier(0)
   , m_track(0)
   , m_EMclusters2(0)
   , m_HADclusters2(0)
   , m_EMenergy(0.0)
   , m_HADenergy(0.0)
{
   assert(false);
}

LCDMatched::LCDMatched(Identifier id, LCDTrack* track)
   : m_identifier(id)
   , m_track(track)
   , m_EMclusters2(0)
   , m_HADclusters2(0)
   , m_EMenergy(0.0)
   , m_HADenergy(0.0)
{
}

// LCDMatched::LCDMatched( const LCDMatched& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

LCDMatched::~LCDMatched()
{
   if (m_EMclusters2 != 0) delete m_EMclusters2;
   if (m_HADclusters2 != 0) delete m_HADclusters2;
}

void LCDMatched::addEMcluster(LCDCluster* cluster, double distance, double error)
{
   assert(cluster->GetSystem() == 0);

   m_EMclusters.push_back(cluster);
   m_EMdistances.push_back(distance);
   m_EMerrors.push_back(error);
   m_EMsigmas.push_back(error > 0. ? distance/error : 0.);

   m_EMenergy += cluster->GetEnergy();
}

void LCDMatched::addHADcluster(LCDCluster* cluster, double distance, double error)
{
   assert(cluster->GetSystem() == 1);

   m_HADclusters.push_back(cluster);
   m_HADdistances.push_back(distance);
   m_HADerrors.push_back(error);
   m_HADsigmas.push_back(error > 0. ? distance/error : 0.);

   m_HADenergy += cluster->GetEnergy();
}

Vector<LCDCluster>& LCDMatched::emClusters()
{
   if (m_EMclusters2 != 0) delete m_EMclusters2;
   m_EMclusters2 = new Vector<LCDCluster>(&m_EMclusters);
   return *m_EMclusters2;
}

Vector<LCDCluster>& LCDMatched::hadClusters()
{
   if (m_HADclusters2 != 0) delete m_HADclusters2;
   m_HADclusters2 = new Vector<LCDCluster>(&m_HADclusters);
   return *m_HADclusters2;
}

//
// assignment operators
//
// const LCDMatched& LCDMatched::operator=( const LCDMatched& rhs )
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

//
// const member functions
//

//
// static member functions
//
