// -*- C++ -*-
//
// Package:     <LCDPerfectTrackClusterMatchingProd>
// Module:      LCDPerfectIsolateClusterProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed Jun 16 12:24:42 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAAutoEraseAllPtr.h"

#include "LCDPerfectTrackClusterMatchingProd/LCDPerfectIsolateClusterProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "LCDRootAccess/Vector.h"
#include "LCDTrack.h"
#include "LCDCluster.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

using LCDRootAccess::Vector;

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "LCDPerfectTrackClusterMatchingProd.LCDPerfectIsolateClusterProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxymany.cc,v 1.14 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDPerfectIsolateClusterProxy::LCDPerfectIsolateClusterProxy()
   : m_ptrTable( new value_type )
{

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &LCDPerfectIsolateClusterProxy::boundMethod, Stream::kBeginRun );
}

// LCDPerfectIsolateClusterProxy::LCDPerfectIsolateClusterProxy( const LCDPerfectIsolateClusterProxy& iproxy )
// {
//   *this = iproxy;
// }

LCDPerfectIsolateClusterProxy::~LCDPerfectIsolateClusterProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const LCDPerfectIsolateClusterProxy& LCDPerfectIsolateClusterProxy::operator=( const LCDPerfectIsolateClusterProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
LCDPerfectIsolateClusterProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const LCDPerfectIsolateClusterProxy::value_type*
LCDPerfectIsolateClusterProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   //If an exception is thrown in this routine, m_ptrTable will be
   // automatically emptied (which is the proper behavior).
   // Use ptrTable just like you would use m_ptrTable
   FAAutoEraseAllPtr<LCDIsolateCluster> ptrTable( m_ptrTable );

   Vector<LCDTrack> tracks;
   extract(iRecord, tracks);
   Vector<LCDTrack>::const_iterator tracks_end = tracks.end();

   Vector<LCDCluster> clusters;
   extract(iRecord, clusters);
   Vector<LCDCluster>::const_iterator clusters_end = clusters.end();
   
   LCDIsolateCluster::Identifier id = 0;
   for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
	cluster_iter != clusters_end;  ++cluster_iter) {
      LCDIsolateCluster* pointer;
      ptrTable->insert(pointer = new LCDIsolateCluster(++id, &*cluster_iter));

      bool clusterIsMatched = false;
      LCDCluster cls = *cluster_iter;
      for (Int_t npart=0; npart<cls.GetMcListEntries(); npart++) {
	 for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
	      track_iter != tracks_end;  ++track_iter) {
	    if (track_iter->GetParticle() == cls.GetMcList()[npart]) {
	       clusterIsMatched = true;

               //calculate the distance between the track and the cluster
               //this requires converting the shower position from cylindrical coords
               double clsR = cls.GetEnergyR();
               double clsTheta = cls.GetEnergyTheta();
               double clsPhi = cls.GetEnergyPhi();
               double distance = 
                  track_iter->GetDistance(TVector3(clsR*sin(clsTheta)*cos(clsPhi),
						   clsR*sin(clsTheta)*sin(clsPhi),
						   clsR*cos(clsTheta)));

	       pointer->addTrack(&*track_iter, distance);
	    } // if this is matched
	 } // end loop over tracks
      } // end loop over MC particles
   } // end loop over clusters

   //The release returns m_ptrTable and stops ptrTable from erasing the 
   // contents of m_ptrTable.
   return ( ptrTable.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//LCDPerfectIsolateClusterProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< LCDIsolateCluster > >;

PROXY_BIND_METHOD( LCDPerfectIsolateClusterProxy )
//-----------------------------------------------


