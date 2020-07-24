// -*- C++ -*-
//
// Package:     FindLambdas2
// Module:      FindLambdas2
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Jun 10 12:13:57 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FindLambdas2/FindLambdas2.h"
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
static const char* const kFacilityString = "Processor.FindLambdas2" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FindLambdas2::FindLambdas2( void )               // anal1
   : Processor( "FindLambdas2" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FindLambdas2::event,    Stream::kEvent );
   //bind( &FindLambdas2::beginRun, Stream::kBeginRun );
   //bind( &FindLambdas2::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FindLambdas2::~FindLambdas2()                    // anal5
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
FindLambdas2::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FindLambdas2::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FindLambdas2::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "run", "event",
      "qual",
      "x", "y", "z",
      "px", "py", "pz",
      "nx", "ny", "nz",
      "sign", "mlam"};
   m_ntuple = iHistoManager.ntuple(
      1, "lambdas", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FindLambdas2::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> header;
   extract(iFrame.record(Stream::kEvent), header);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   DABoolean found_one(false);
   for (FATable<NavTrack>::const_iterator pos = tracks.begin();
	pos != tracks_end;
	++pos) {
      if (pos->pionHelix()->curvature() > 0.) {
	 for (FATable<NavTrack>::const_iterator neg = pos;
	      neg != tracks_end;
	      ++neg) {
	    if (neg->pionHelix()->curvature() < 0.) {
	       double x, y, z, sig2z, zsep;

	       // Trial a: positive track is a proton, negative is a pi-
	       double amass(sqrt(sqr(pos->protonFit()->energy() + neg->pionFit()->energy()) -
				 (pos->protonFit()->momentum() + neg->pionFit()->momentum()).mag2()));
	       KTHelix posProton(*pos->protonHelix());
	       KTHelix negPion(*neg->pionHelix());
	       double aqual(1000.);
	       HepPoint3D avert(0.,0.,0.);

	       // Trial b: positive track is a pi+, negative is an antiproton
	       double bmass(sqrt(sqr(pos->pionFit()->energy() + neg->protonFit()->energy()) -
				 (pos->pionFit()->momentum() + neg->protonFit()->momentum()).mag2()));
	       KTHelix posPion(*pos->pionHelix());
	       KTHelix negProton(*neg->protonHelix());
	       double bqual(1000.);
	       HepPoint3D bvert(0.,0.,0.);

	       const double lambdamass = 1.115683;

	       if (fabs(amass - lambdamass) < 0.100  &&
		   calc_intersection(x, y, z, sig2z, zsep, posProton, negPion)) {
		  aqual = sqrt(sig2z + zsep*zsep);
		  avert = HepPoint3D(x, y, z);
	       }

	       if (fabs(bmass - lambdamass) < 0.100  &&
		   calc_intersection(x,y,z, sig2z, zsep, posPion, negProton)) {
		  bqual = sqrt(sig2z + zsep*zsep);
		  bvert = HepPoint3D(x, y, z);
	       }

	       char winner = '0';
	       DABoolean aokay(aqual < 0.005  &&  (avert.perp() > 0.03  ||  fabs(avert.z()) > 0.06));
	       DABoolean bokay(bqual < 0.005  &&  (bvert.perp() > 0.03  ||  fabs(bvert.z()) > 0.06));

	       if (aokay  &&  bokay) {
		  if (aqual < bqual) winner = 'a';
		  else winner = 'b';
	       }
	       else if (aokay  &&  !bokay) {
		  winner = 'a';
	       }
	       else if (!aokay  &&  bokay) {
		  winner = 'b';
	       }
	       else {
		  winner = '0';
	       }

	       if (winner == 'a') {
		  float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) v[i] = 0.;
		  v[kRun] = header->run();
		  v[kEvent] = header->number();
		  v[kQual] = aqual;
		  v[kX] = avert.x();
		  v[kY] = avert.y();
		  v[kZ] = avert.z();
		  v[kPx] = pos->protonFit()->momentum().x();
		  v[kPy] = pos->protonFit()->momentum().y();
		  v[kPz] = pos->protonFit()->momentum().z();
		  v[kNx] = neg->pionFit()->momentum().x();
		  v[kNy] = neg->pionFit()->momentum().y();
		  v[kNz] = neg->pionFit()->momentum().z();
		  v[kSign] = 1.;
		  v[kMLambda] = amass;

		  m_ntuple->fill(v);
		  found_one = true;
		  report(INFO, kFacilityString)
		     << "Proton id " << pos->identifier()
		     << " p " << pos->protonFit()->momentum()
		     << " E " << pos->protonFit()->energy() << endl
		     << "pi- id " << neg->identifier()
		     << " p " << neg->pionFit()->momentum()
		     << " E " << neg->pionFit()->energy() << endl
		     << "vertex " << avert << " qual " << aqual << endl
		     << "lambda mass " << amass << endl;
	       }
	       else if (winner == 'b') {
		  float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) v[i] = 0.;
		  v[kRun] = header->run();
		  v[kEvent] = header->number();
		  v[kQual] = bqual;
		  v[kX] = bvert.x();
		  v[kY] = bvert.y();
		  v[kZ] = bvert.z();
		  v[kPx] = pos->pionFit()->momentum().x();
		  v[kPy] = pos->pionFit()->momentum().y();
		  v[kPz] = pos->pionFit()->momentum().z();
		  v[kNx] = neg->protonFit()->momentum().x();
		  v[kNy] = neg->protonFit()->momentum().y();
		  v[kNz] = neg->protonFit()->momentum().z();
		  v[kSign] = -1.;
		  v[kMLambda] = bmass;

		  m_ntuple->fill(v);
		  found_one = true;
		  report(INFO, kFacilityString)
		     << "Antiproton id " << neg->identifier()
		     << " p " << neg->protonFit()->momentum()
		     << " E " << neg->protonFit()->energy() << endl
		     << "pi+ id " << pos->identifier()
		     << " p " << pos->pionFit()->momentum()
		     << " E " << pos->pionFit()->energy() << endl
		     << "vertex " << bvert << " qual " << bqual << endl
		     << "lambda mass " << bmass << endl;
	       }

	    } // end if neg really is negative
	 } // end loop over neg
      } // end if pos really is positive
   } // end loop over pos

   if (found_one) return ActionBase::kPassed;
   else return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
FindLambdas2::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FindLambdas2::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean FindLambdas2::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean FindLambdas2::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
