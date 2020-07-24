// -*- C++ -*-
//
// Package:     FindLambdas
// Module:      FindLambdas
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun  9 12:50:13 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FindLambdas/FindLambdas.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "CleoDB/DBEventHeader.h"
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.FindLambdas" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FindLambdas::FindLambdas( void )               // anal1
   : Processor( "FindLambdas" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FindLambdas::event,    Stream::kEvent );
   //bind( &FindLambdas::beginRun, Stream::kBeginRun );
   //bind( &FindLambdas::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FindLambdas::~FindLambdas()                    // anal5
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
void
FindLambdas::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FindLambdas::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FindLambdas::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "run", "event",
      "v1x", "v1y", "v1z", "v1px", "v1py", "v1pz", "v1pm", "v1nx", "v1ny", "v1nz", "v1nm", "v1protsign", "ml1",
      "v2x", "v2y", "v2z", "v2px", "v2py", "v2pz", "v2pm", "v2nx", "v2ny", "v2nz", "v2nm", "v2protsign", "ml2"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FindLambdas::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> header;
   extract(iFrame.record(Stream::kEvent), header);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   if ( tracks.size() != 4 ) return ActionBase::kFailed;

   FATable<NavTrack>::const_iterator pos1(tracks_end);
   FATable<NavTrack>::const_iterator neg1(tracks_end);
   FATable<NavTrack>::const_iterator pos2(tracks_end);
   FATable<NavTrack>::const_iterator neg2(tracks_end);

   int event_charge(0);
   for ( FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	 track_iter != tracks_end;
	 ++track_iter ) {
      if ( track_iter->pionHelix()->curvature() > 0. ) {
	 event_charge++;

	 if ( pos1 == tracks_end ) {
	    pos1 = track_iter;
	 } else {
	    pos2 = track_iter;
	 }
      } else {
	 event_charge--;

	 if ( neg1 == tracks_end ) {
	    neg1 = track_iter;
	 } else {
	    neg2 = track_iter;
	 }
      } // end if negative
   }

   if ( event_charge != 0 ) return ActionBase::kFailed;

   KTHelix pos1_helix(*pos1->pionHelix());
   KTHelix neg1_helix(*neg1->pionHelix());
   KTHelix pos2_helix(*pos2->pionHelix());
   KTHelix neg2_helix(*neg2->pionHelix());

   double v11qual(1000.), v22qual(1000.), v12qual(1000.), v21qual(1000.);
   HepPoint3D v11(0.,0.,0.), v22(0.,0.,0.), v12(0.,0.,0.), v21(0.,0.,0.);

   double x, y, z, sig2z, zsep;
   if ( calc_intersection(x, y, z, sig2z, zsep, pos1_helix, neg1_helix) ) {
      v11 = HepPoint3D(x, y, z);
      v11qual = sqrt(sig2z + zsep*zsep);
   }
   if ( calc_intersection(x, y, z, sig2z, zsep, pos2_helix, neg2_helix) ) {
      v22 = HepPoint3D(x, y, z);
      v22qual = sqrt(sig2z + zsep*zsep);
   }
   if ( calc_intersection(x, y, z, sig2z, zsep, pos1_helix, neg2_helix) ) {
      v12 = HepPoint3D(x, y, z);
      v12qual = sqrt(sig2z + zsep*zsep);
   }
   if ( calc_intersection(x, y, z, sig2z, zsep, pos2_helix, neg1_helix) ) {
      v21 = HepPoint3D(x, y, z);
      v21qual = sqrt(sig2z + zsep*zsep);
   }

   HepPoint3D v1(0.,0.,0.), v2(0.,0.,0.);
   FATable<NavTrack>::const_iterator v1pos(tracks_end);
   FATable<NavTrack>::const_iterator v1neg(tracks_end);
   FATable<NavTrack>::const_iterator v2pos(tracks_end);
   FATable<NavTrack>::const_iterator v2neg(tracks_end);

   if ( v11qual < 0.003  &&  v22qual < 0.003 ) {
      v1 = v11;
      v2 = v22;
      v1pos = pos1;
      v1neg = neg1;
      v2pos = pos2;
      v2neg = neg2;
   }
   else if ( v12qual < 0.003  &&  v21qual < 0.003 ) {
      v1 = v12;
      v2 = v21;
      v1pos = pos1;
      v1neg = neg2;
      v2pos = pos2;
      v2neg = neg1;
   }
   else { return ActionBase::kFailed; }

   if ( v1.perp() < 0.01  &&  fabs(v1.z()) < 0.04 ) return ActionBase::kFailed;
   if ( v2.perp() < 0.01  &&  fabs(v2.z()) < 0.04 ) return ActionBase::kFailed;

   float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) {v[i] = 0.;}
   v[kRun] = header->run();
   v[kEvent] = header->number();

   double lambda1_assignment1(sqrt(sqr(v1pos->protonFit()->energy() + v1neg->pionFit()->energy()) -
				   (v1pos->protonFit()->momentum() + v1neg->pionFit()->momentum()).mag2()));
   double lambda2_assignment1(sqrt(sqr(v2pos->pionFit()->energy() + v2neg->protonFit()->energy()) -
				   (v2pos->pionFit()->momentum() + v2neg->protonFit()->momentum()).mag2()));

   double lambda1_assignment2(sqrt(sqr(v1pos->pionFit()->energy() + v1neg->protonFit()->energy()) -
				   (v1pos->pionFit()->momentum() + v1neg->protonFit()->momentum()).mag2()));
   double lambda2_assignment2(sqrt(sqr(v2pos->protonFit()->energy() + v2neg->pionFit()->energy()) -
				   (v2pos->protonFit()->momentum() + v2neg->pionFit()->momentum()).mag2()));

   const double lambdaMass = 1.115683;
   if ( sqr(lambda1_assignment1 - lambdaMass) + sqr(lambda2_assignment1 - lambdaMass) <
	sqr(lambda1_assignment2 - lambdaMass) + sqr(lambda2_assignment2 - lambdaMass)   ) {
      // assignment 1 is better

      v[kV1X] = v1.x();
      v[kV1Y] = v1.y();
      v[kV1Z] = v1.z();
      v[kV1Px] = v1pos->protonFit()->momentum().x();
      v[kV1Py] = v1pos->protonFit()->momentum().y();
      v[kV1Pz] = v1pos->protonFit()->momentum().z();
      v[kV1Pm] = v1pos->protonFit()->mass();
      v[kV1Nx] = v1neg->pionFit()->momentum().x();
      v[kV1Ny] = v1neg->pionFit()->momentum().y();
      v[kV1Nz] = v1neg->pionFit()->momentum().z();
      v[kV1Nm] = v1neg->pionFit()->mass();
      v[kV1ProtonSign] = 1.;
      v[kMassLambda1] = lambda1_assignment1;

      v[kV2X] = v2.x();
      v[kV2Y] = v2.y();
      v[kV2Z] = v2.z();
      v[kV2Px] = v2pos->pionFit()->momentum().x();
      v[kV2Py] = v2pos->pionFit()->momentum().y();
      v[kV2Pz] = v2pos->pionFit()->momentum().z();
      v[kV2Pm] = v2pos->pionFit()->mass();
      v[kV2Nx] = v2neg->protonFit()->momentum().x();
      v[kV2Ny] = v2neg->protonFit()->momentum().y();
      v[kV2Nz] = v2neg->protonFit()->momentum().z();
      v[kV2Nm] = v2neg->protonFit()->mass();
      v[kV2ProtonSign] = -1.;
      v[kMassLambda2] = lambda2_assignment1;
	 
   } else {
      // assignment 2 is better

      v[kV1X] = v1.x();
      v[kV1Y] = v1.y();
      v[kV1Z] = v1.z();
      v[kV1Px] = v1pos->pionFit()->momentum().x();
      v[kV1Py] = v1pos->pionFit()->momentum().y();
      v[kV1Pz] = v1pos->pionFit()->momentum().z();
      v[kV1Pm] = v1pos->pionFit()->mass();
      v[kV1Nx] = v1neg->protonFit()->momentum().x();
      v[kV1Ny] = v1neg->protonFit()->momentum().y();
      v[kV1Nz] = v1neg->protonFit()->momentum().z();
      v[kV1Nm] = v1neg->protonFit()->mass();
      v[kV1ProtonSign] = -1.;
      v[kMassLambda1] = lambda1_assignment2;

      v[kV2X] = v2.x();
      v[kV2Y] = v2.y();
      v[kV2Z] = v2.z();
      v[kV2Px] = v2pos->protonFit()->momentum().x();
      v[kV2Py] = v2pos->protonFit()->momentum().y();
      v[kV2Pz] = v2pos->protonFit()->momentum().z();
      v[kV2Pm] = v2pos->protonFit()->mass();
      v[kV2Nx] = v2neg->pionFit()->momentum().x();
      v[kV2Ny] = v2neg->pionFit()->momentum().y();
      v[kV2Nz] = v2neg->pionFit()->momentum().z();
      v[kV2Nm] = v2neg->pionFit()->mass();
      v[kV2ProtonSign] = 1.;
      v[kMassLambda2] = lambda2_assignment2;

   }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
FindLambdas::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FindLambdas::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean FindLambdas::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
					       KTHelix& a, KTHelix& b )
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( fabs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	fabs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( fabs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	fabs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = az - bz;

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean FindLambdas::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./fabs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./fabs(b.curvature()) );
}
