// -*- C++ -*-
//
// Package:     <LCDTrackClusterMatchingProd>
// Module:      LCDMatchTrackProxy
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

#include "LCDTrackClusterMatchingProd/LCDMatchTrackProxy.h"
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
static const char* const kFacilityString = "LCDTrackClusterMatchingProd.LCDMatchTrackProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxymany.cc,v 1.14 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDMatchTrackProxy::LCDMatchTrackProxy()
   : m_ptrTable( new value_type )
{

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &LCDMatchTrackProxy::boundMethod, Stream::kBeginRun );
}

LCDMatchTrackProxy::LCDMatchTrackProxy(double iTrackMatchDistCM)
   : m_ptrTable( new value_type )
   , m_trackMatchDistCM(iTrackMatchDistCM)
{
}

// LCDMatchTrackProxy::LCDMatchTrackProxy( const LCDMatchTrackProxy& iproxy )
// {
//   *this = iproxy;
// }

LCDMatchTrackProxy::~LCDMatchTrackProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const LCDMatchTrackProxy& LCDMatchTrackProxy::operator=( const LCDMatchTrackProxy& iproxy )
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
LCDMatchTrackProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const LCDMatchTrackProxy::value_type*
LCDMatchTrackProxy::faultHandler( const Record& iRecord,
				  const DataKey& iKey )
{

   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   //If an exception is thrown in this routine, m_ptrTable will be
   // automatically emptied (which is the proper behavior).
   // Use ptrTable just like you would use m_ptrTable
   FAAutoEraseAllPtr<LCDMatchTrack> ptrTable( m_ptrTable );

   Vector<LCDTrack> tracks;
   extract(iRecord, tracks);
   Vector<LCDTrack>::const_iterator tracks_end = tracks.end();

   Vector<LCDCluster> clusters;
   extract(iRecord, clusters);
   Vector<LCDCluster>::const_iterator clusters_end = clusters.end();

   LCDMatchTrack::Identifier id = 0;
   for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
        track_iter != tracks_end;  ++track_iter) {
      LCDMatchTrack* pointer;
      ptrTable->insert(pointer = new LCDMatchTrack(++id, &*track_iter));

      for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
           cluster_iter != clusters_end;  ++cluster_iter) {
         const double r = cluster_iter->GetEnergyR();
         const double theta = cluster_iter->GetEnergyTheta();
         const double phi = cluster_iter->GetEnergyPhi();
         
         double dist = track_iter->GetDistance(TVector3(r*sin(theta)*cos(phi),
                                                        r*sin(theta)*sin(phi),
                                                        r*cos(theta)));

	 if (dist < m_trackMatchDistCM) pointer->addCluster(&*cluster_iter, dist);
      } // end loop over clusters
   } // end loop over tracks

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
//LCDMatchTrackProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< LCDMatchTrack > >;

PROXY_BIND_METHOD( LCDMatchTrackProxy )
//-----------------------------------------------


