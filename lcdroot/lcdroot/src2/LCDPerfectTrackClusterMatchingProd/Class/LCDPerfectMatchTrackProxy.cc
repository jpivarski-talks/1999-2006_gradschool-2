// -*- C++ -*-
//
// Package:     <LCDPerfectTrackClusterMatchingProd>
// Module:      LCDPerfectMatchTrackProxy
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

#include "LCDPerfectTrackClusterMatchingProd/LCDPerfectMatchTrackProxy.h"
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
static const char* const kFacilityString = "LCDPerfectTrackClusterMatchingProd.LCDPerfectMatchTrackProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxymany.cc,v 1.14 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDPerfectMatchTrackProxy::LCDPerfectMatchTrackProxy()
   : m_ptrTable( new value_type )
{

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &LCDPerfectMatchTrackProxy::boundMethod, Stream::kBeginRun );
}

// LCDPerfectMatchTrackProxy::LCDPerfectMatchTrackProxy( const LCDPerfectMatchTrackProxy& iproxy )
// {
//   *this = iproxy;
// }

LCDPerfectMatchTrackProxy::~LCDPerfectMatchTrackProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const LCDPerfectMatchTrackProxy& LCDPerfectMatchTrackProxy::operator=( const LCDPerfectMatchTrackProxy& iproxy )
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
LCDPerfectMatchTrackProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const LCDPerfectMatchTrackProxy::value_type*
LCDPerfectMatchTrackProxy::faultHandler( const Record& iRecord,
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
   
   // loop over all tracks
   // if it is matched to a shower, make an object LCDMatched 
   int LCDMatchedID = 0; // identifier of LCDMatched
   for (Int_t ntrk=0; ntrk<tracks.size(); ntrk++) 
   {
      LCDTrack trk = tracks[ntrk];
      bool trackIsMatched = 0;
      LCDMatchTrack* trackMatches;
      ptrTable->insert(trackMatches = new LCDMatchTrack(++LCDMatchedID, &trk));
      // loop over all clusters
      for (Int_t ncls=0; ncls<clusters.size(); ncls++) 
      {
         const LCDCluster& cls = clusters[ncls];
         // loop over all particles matched to clusters
         for(Int_t npart=0; npart<cls.GetMcListEntries(); npart++)
         {
            if(trk.GetParticle() == cls.GetMcList()[npart])
            {
               trackIsMatched = 1;
               //calculate the distance between the track and the cluster
               //this requires converting the shower position from cylindrical coords
               double clsR = cls.GetEnergyR();
               double clsTheta = cls.GetEnergyTheta();
               double clsPhi = cls.GetEnergyPhi();
               double distance = 
                  trk.GetDistance(TVector3(clsR*sin(clsTheta)*cos(clsPhi),
                                           clsR*sin(clsTheta)*sin(clsPhi),
                                           clsR*cos(clsTheta)));

	       trackMatches->addCluster(&cls, distance);
            }
               
         }
      }// loop over clusters
   }

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
//LCDPerfectMatchTrackProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< LCDMatchTrack > >;

PROXY_BIND_METHOD( LCDPerfectMatchTrackProxy )
//-----------------------------------------------


