// -*- C++ -*-
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDMatchedProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Wed May  5 16:01:36 EDT 2004
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
#include "LCDRootAccess/Vector.h"

#include "LCDTrack.h"
#include "LCDMcPart.h"
#include "LCDCluster.h"


#include "LCDTrackShowerMatchingProd/LCDMatchedProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#if 0
#include "Navigation/NavTrack.h" 
#endif

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "LCDTrackShowerMatchingProd.LCDMatchedProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxymany.cc,v 1.14 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LCDMatchedProxy::LCDMatchedProxy()
   : m_ptrTable( new value_type )
   , m_EMmatchingDistanceCmCut(0.0)
   , m_EMmatchingErrorCmCut(0.0)
   , m_EMmatchingDistanceSigmasCut(0.0)
   , m_HADmatchingDistanceCmCut(0.0)
   , m_HADmatchingErrorCmCut(0.0)
   , m_HADmatchingDistanceSigmasCut(0.0)
{

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &LCDMatchedProxy::boundMethod, Stream::kBeginRun );
}

LCDMatchedProxy::LCDMatchedProxy(double iEMmatchingDistanceCmCut,
				 double iEMmatchingErrorCmCut,
				 double iEMmatchingDistanceSigmasCut,
				 double iHADmatchingDistanceCmCut,
				 double iHADmatchingErrorCmCut,
				 double iHADmatchingDistanceSigmasCut)
   : m_ptrTable( new value_type )
   , m_EMmatchingDistanceCmCut(iEMmatchingDistanceCmCut)
   , m_EMmatchingErrorCmCut(iEMmatchingErrorCmCut)
   , m_EMmatchingDistanceSigmasCut(iEMmatchingDistanceSigmasCut)
   , m_HADmatchingDistanceCmCut(iHADmatchingDistanceCmCut)
   , m_HADmatchingErrorCmCut(iHADmatchingErrorCmCut)
   , m_HADmatchingDistanceSigmasCut(iHADmatchingDistanceSigmasCut)
{
}

// LCDMatchedProxy::LCDMatchedProxy( const LCDMatchedProxy& iproxy )
// {
//   *this = iproxy;
// }

LCDMatchedProxy::~LCDMatchedProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const LCDMatchedProxy& LCDMatchedProxy::operator=( const LCDMatchedProxy& iproxy )
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
LCDMatchedProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const LCDMatchedProxy::value_type*
LCDMatchedProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   //If an exception is thrown in this routine, m_ptrTable will be
   // automatically emptied (which is the proper behavior).
   // Use ptrTable just like you would use m_ptrTable
   FAAutoEraseAllPtr<LCDMatched> ptrTable( m_ptrTable );

   Vector<LCDTrack> tracks;
   extract(iRecord, tracks);
   Vector<LCDTrack>::const_iterator tracks_end = tracks.end();

   Vector<LCDCluster> clusters;
   extract(iRecord, clusters);
   Vector<LCDCluster>::const_iterator clusters_end = clusters.end();

   for (Vector<LCDTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      for (Vector<LCDCluster>::const_iterator cluster_iter = clusters.begin();
	   cluster_iter != clusters_end;  ++cluster_iter) {

	 double r = cluster_iter->GetEnergyR();
	 double theta = cluster_iter->GetEnergyTheta();
	 double phi = cluster_iter->GetEnergyPhi();
	 
	 double distance = track_iter->GetDistance(TVector3(r*sin(theta)*cos(phi),
							    r*sin(theta)*sin(phi),
							    r*cos(theta)));
	 
	 if ((cluster_iter->GetSystem() == 0  &&  distance < m_EMmatchingDistanceCmCut)  ||
	     (cluster_iter->GetSystem() == 1  &&  distance < m_HADmatchingDistanceCmCut)) {
	    double dr = cluster_iter->GetEnergyRRMS();
	    double dtheta = cluster_iter->GetEnergyThetaRMS();
	    double dphi = cluster_iter->GetEnergyPhiRMS();

	    double dist_drdr = track_iter->GetDistance(TVector3((r+dr)*sin(theta)*cos(phi),
								(r+dr)*sin(theta)*sin(phi),
								(r+dr)*cos(theta)));
	    double dist_dtdt = track_iter->GetDistance(TVector3(r*sin(theta+dtheta)*cos(phi),
								r*sin(theta+dtheta)*sin(phi),
								r*cos(theta+dtheta)));
	    double dist_dpdp = track_iter->GetDistance(TVector3(r*sin(theta)*cos(phi+dphi),
								r*sin(theta)*sin(phi+dphi),
								r*cos(theta)));
	    double dist_drdt = track_iter->GetDistance(TVector3((r+M_SQRT2*dr)*sin(theta+M_SQRT2*dtheta)*cos(phi),
								(r+M_SQRT2*dr)*sin(theta+M_SQRT2*dtheta)*sin(phi),
								(r+M_SQRT2*dr)*cos(theta+M_SQRT2*dtheta)));
	    double dist_drdp = track_iter->GetDistance(TVector3((r+M_SQRT2*dr)*sin(theta)*cos(phi+M_SQRT2*dphi),
								(r+M_SQRT2*dr)*sin(theta)*sin(phi+M_SQRT2*dphi),
								(r+M_SQRT2*dr)*cos(theta)));
	    double dist_dtdp = track_iter->GetDistance(TVector3(r*sin(theta+M_SQRT2*dtheta)*cos(phi+M_SQRT2*dphi),
								r*sin(theta+M_SQRT2*dtheta)*sin(phi+M_SQRT2*dphi),
								r*cos(theta+M_SQRT2*dtheta)));

	    



	 } // end if passes distance cut
      } // end loop over clusters
   } // end loop over tracks





#if 0
   // ---------- sample implementation ---------------------

   // ---------- fill FAPtrTable with new items ----------------

   // this typedef here for convenience
   typedef FATable< NavTrack > NavTrackTable;

   // get the table out of the Record
   NavTrackTable table;
   extract( iRecord, table ); 

   //create LCDMatched from NavTracks
   NavTrackTable::const_iterator tableEnd( table.end() );
   for ( NavTrackTable::const_iterator item( table.begin() ) ;
         item != tableEnd ;
         ++item ) 
   {
      ptrTable->insert( new LCDMatched( (*item).identifier(),
					  *item ) ) ;
   }
#endif

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
//LCDMatchedProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< LCDMatched > >;

PROXY_BIND_METHOD( LCDMatchedProxy )
//-----------------------------------------------


