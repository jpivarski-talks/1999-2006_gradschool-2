// -*- C++ -*-
//
// Package:     D0Miss
// Module:      D0Miss
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Dec  1 13:10:54 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "D0Miss/D0Miss.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

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
static const char* const kFacilityString = "Processor.D0Miss" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
D0Miss::D0Miss( void )               // anal1
   : Processor( "D0Miss" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &D0Miss::event,    Stream::kEvent );
   //bind( &D0Miss::beginRun, Stream::kBeginRun );
   //bind( &D0Miss::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

D0Miss::~D0Miss()                    // anal5
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
D0Miss::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
D0Miss::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
D0Miss::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_00 = iHistoManager.profile(
      "(-2.0,-1.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_01 = iHistoManager.profile(
      "(-1.8,-1.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_02 = iHistoManager.profile(
      "(-1.6,-1.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_03 = iHistoManager.profile(
      "(-1.4,-1.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_04 = iHistoManager.profile(
      "(-1.2,-1.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_05 = iHistoManager.profile(
      "(-1.0,-0.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_06 = iHistoManager.profile(
      "(-0.8,-0.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_07 = iHistoManager.profile(
      "(-0.6,-0.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_08 = iHistoManager.profile(
      "(-0.4,-0.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_09 = iHistoManager.profile(
      "(-0.2, 0.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_10 = iHistoManager.profile(
      "( 0.0, 0.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_11 = iHistoManager.profile(
      "( 0.2, 0.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_12 = iHistoManager.profile(
      "( 0.4, 0.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_13 = iHistoManager.profile(
      "( 0.6, 0.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_14 = iHistoManager.profile(
      "( 0.8, 1.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_15 = iHistoManager.profile(
      "( 1.0, 1.2)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_16 = iHistoManager.profile(
      "( 1.2, 1.4)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_17 = iHistoManager.profile(
      "( 1.4, 1.6)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_18 = iHistoManager.profile(
      "( 1.6, 1.8)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);
   m_19 = iHistoManager.profile(
      "( 1.8, 2.0)", 15, 0., 2.*M_PI, -0.01, 0.01, HIHistProf::kErrorOnMean);

   m_ct_00 = iHistoManager.histogram("(-2.0,-1.8)", 500, -2., 2.);
   m_ct_01 = iHistoManager.histogram("(-1.8,-1.6)", 500, -2., 2.);
   m_ct_02 = iHistoManager.histogram("(-1.6,-1.4)", 500, -2., 2.);
   m_ct_03 = iHistoManager.histogram("(-1.4,-1.2)", 500, -2., 2.);
   m_ct_04 = iHistoManager.histogram("(-1.2,-1.0)", 500, -2., 2.);
   m_ct_05 = iHistoManager.histogram("(-1.0,-0.8)", 500, -2., 2.);
   m_ct_06 = iHistoManager.histogram("(-0.8,-0.6)", 500, -2., 2.);
   m_ct_07 = iHistoManager.histogram("(-0.6,-0.4)", 500, -2., 2.);
   m_ct_08 = iHistoManager.histogram("(-0.4,-0.2)", 500, -2., 2.);
   m_ct_09 = iHistoManager.histogram("(-0.2, 0.0)", 500, -2., 2.);
   m_ct_10 = iHistoManager.histogram("( 0.0, 0.2)", 500, -2., 2.);
   m_ct_11 = iHistoManager.histogram("( 0.2, 0.4)", 500, -2., 2.);
   m_ct_12 = iHistoManager.histogram("( 0.4, 0.6)", 500, -2., 2.);
   m_ct_13 = iHistoManager.histogram("( 0.6, 0.8)", 500, -2., 2.);
   m_ct_14 = iHistoManager.histogram("( 0.8, 1.0)", 500, -2., 2.);
   m_ct_15 = iHistoManager.histogram("( 1.0, 1.2)", 500, -2., 2.);
   m_ct_16 = iHistoManager.histogram("( 1.2, 1.4)", 500, -2., 2.);
   m_ct_17 = iHistoManager.histogram("( 1.4, 1.6)", 500, -2., 2.);
   m_ct_18 = iHistoManager.histogram("( 1.6, 1.8)", 500, -2., 2.);
   m_ct_19 = iHistoManager.histogram("( 1.8, 2.0)", 500, -2., 2.);

   m_chi2diff = iHistoManager.histogram("[h]^2!?pos! - [h]^2!?neg!", 100, -300., 300.);
   m_err_cc = iHistoManager.histogram("curv curv",     	   500, -4.2e-06, 4.2e-06);
   m_err_cp = iHistoManager.histogram("curv phi0",     	   500, -2.2e-06, 2.2e-06);
   m_err_cd = iHistoManager.histogram("curv d0",       	   500, -3.0e-07, 3.0e-07);
   m_err_ct = iHistoManager.histogram("curv cotTheta", 	   500, -5.8e-05, 5.8e-05);
   m_err_cz = iHistoManager.histogram("curv z0",       	   500, -2.2e-05, 2.2e-05);
   m_err_pp = iHistoManager.histogram("phi0 phi0",     	   500, -1.3e-06, 1.3e-06);
   m_err_pd = iHistoManager.histogram("phi0 d0",       	   500, -1.8e-07, 1.8e-07);
   m_err_pt = iHistoManager.histogram("phi0 cotTheta", 	   500, -3.0e-05, 3.0e-05);
   m_err_pz = iHistoManager.histogram("phi0 z0",       	   500, -1.2e-05, 1.2e-05);
   m_err_dd = iHistoManager.histogram("d0 d0",         	   500, -2.9e-08, 2.9e-08);
   m_err_dt = iHistoManager.histogram("d0 cotTheta",   	   500, -3.9e-06, 3.9e-06);
   m_err_dz = iHistoManager.histogram("d0 z0",         	   500, -1.5e-06, 1.5e-06);
   m_err_tt = iHistoManager.histogram("cotTheta cotTheta", 500,  -0.0013,  0.0013);
   m_err_tz = iHistoManager.histogram("cotTheta z0",       500, -0.00051, 0.00051);
   m_err_zz = iHistoManager.histogram("z0 z0",             500, -0.00020, 0.00020);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
D0Miss::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   assert(tracks.size() == 2);
   FATable<NavTrack>::const_iterator positive, negative;

   positive = tracks.begin();
   if (positive->pionHelix()->curvature() < 0.) {
      ++positive;
      negative = tracks.begin();
   }
   else {
      negative = tracks.begin();
      ++negative;
   }
   assert(positive->pionHelix()->curvature() > 0.);
   assert(negative->pionHelix()->curvature() < 0.);

   double phi = positive->pionHelix()->phi0();
   double cT = positive->pionHelix()->cotTheta();
   double half_correction = (-0.0000155735 - 0.0000275939*cT - 9.06903E-6*cT*cT - 6.00561E-6*cT*cT*cT)
      * sin(2.*phi)/2.;
   double posd0 = positive->pionHelix()->d0() - half_correction;
   double negd0 = negative->pionHelix()->d0() - half_correction;
   double d0miss = posd0 + negd0;

   if (cT < -2.0) ;
   else if (cT < -1.8) { m_00->fill(phi, d0miss);  m_ct_00->fill(cT); }
   else if (cT < -1.6) { m_01->fill(phi, d0miss);  m_ct_01->fill(cT); }
   else if (cT < -1.4) { m_02->fill(phi, d0miss);  m_ct_02->fill(cT); }
   else if (cT < -1.2) { m_03->fill(phi, d0miss);  m_ct_03->fill(cT); }
   else if (cT < -1.0) { m_04->fill(phi, d0miss);  m_ct_04->fill(cT); }
   else if (cT < -0.8) { m_05->fill(phi, d0miss);  m_ct_05->fill(cT); }
   else if (cT < -0.6) { m_06->fill(phi, d0miss);  m_ct_06->fill(cT); }
   else if (cT < -0.4) { m_07->fill(phi, d0miss);  m_ct_07->fill(cT); }
   else if (cT < -0.2) { m_08->fill(phi, d0miss);  m_ct_08->fill(cT); }
   else if (cT <  0.0) { m_09->fill(phi, d0miss);  m_ct_09->fill(cT); }
   else if (cT <  0.2) { m_10->fill(phi, d0miss);  m_ct_10->fill(cT); }
   else if (cT <  0.4) { m_11->fill(phi, d0miss);  m_ct_11->fill(cT); }
   else if (cT <  0.6) { m_12->fill(phi, d0miss);  m_ct_12->fill(cT); }
   else if (cT <  0.8) { m_13->fill(phi, d0miss);  m_ct_13->fill(cT); }
   else if (cT <  1.0) { m_14->fill(phi, d0miss);  m_ct_14->fill(cT); }
   else if (cT <  1.2) { m_15->fill(phi, d0miss);  m_ct_15->fill(cT); }
   else if (cT <  1.4) { m_16->fill(phi, d0miss);  m_ct_16->fill(cT); }
   else if (cT <  1.6) { m_17->fill(phi, d0miss);  m_ct_17->fill(cT); }
   else if (cT <  1.8) { m_18->fill(phi, d0miss);  m_ct_18->fill(cT); }
   else if (cT <  2.0) { m_19->fill(phi, d0miss);  m_ct_19->fill(cT); }

   m_chi2diff->fill(positive->pionQuality()->chiSquare() - negative->pionQuality()->chiSquare());

   HepSymMatrix poserr = positive->pionHelix()->errorMatrix();
   HepSymMatrix negerr = negative->pionHelix()->errorMatrix();
   const int c = KTHelix::kCurvature;
   const int p = KTHelix::kPhi0;
   const int d = KTHelix::kD0;
   const int t = KTHelix::kCotTheta;
   const int z = KTHelix::kZ0;

   m_err_cc->fill(poserr(c,c) - negerr(c,c));
   m_err_cp->fill(poserr(c,p) - negerr(c,p));
   m_err_cd->fill(poserr(c,d) - negerr(c,d));
   m_err_ct->fill(poserr(c,t) - negerr(c,t));
   m_err_cz->fill(poserr(c,z) - negerr(c,z));
   m_err_pp->fill(poserr(p,p) - negerr(p,p));
   m_err_pd->fill(poserr(p,d) - negerr(p,d));
   m_err_pt->fill(poserr(p,t) - negerr(p,t));
   m_err_pz->fill(poserr(p,z) - negerr(p,z));
   m_err_dd->fill(poserr(d,d) - negerr(d,d));
   m_err_dt->fill(poserr(d,t) - negerr(d,t));
   m_err_dz->fill(poserr(d,z) - negerr(d,z));
   m_err_tt->fill(poserr(t,t) - negerr(t,t));
   m_err_tz->fill(poserr(t,z) - negerr(t,z));
   m_err_zz->fill(poserr(z,z) - negerr(z,z));

//    static double cc, cp, cd, ct, cz, pp, pd, pt, pz, dd, dt, dz, tt, tz, zz;
//    static double n;
//    cc += sqr(poserr(c,c) - negerr(c,c));
//    cp += sqr(poserr(c,p) - negerr(c,p));
//    cd += sqr(poserr(c,d) - negerr(c,d));
//    ct += sqr(poserr(c,t) - negerr(c,t));
//    cz += sqr(poserr(c,z) - negerr(c,z));
//    pp += sqr(poserr(p,p) - negerr(p,p));
//    pd += sqr(poserr(p,d) - negerr(p,d));
//    pt += sqr(poserr(p,t) - negerr(p,t));
//    pz += sqr(poserr(p,z) - negerr(p,z));
//    dd += sqr(poserr(d,d) - negerr(d,d));
//    dt += sqr(poserr(d,t) - negerr(d,t));
//    dz += sqr(poserr(d,z) - negerr(d,z));
//    tt += sqr(poserr(t,t) - negerr(t,t));
//    tz += sqr(poserr(t,z) - negerr(t,z));
//    zz += sqr(poserr(z,z) - negerr(z,z));
//    n += 1.;
//    cout << "STUFF "
// 	<< sqrt(cc/n) << " " << sqrt(cp/n) << " " << sqrt(cd/n) << " "
// 	<< sqrt(ct/n) << " " << sqrt(cz/n) << " " << sqrt(pp/n) << " "
// 	<< sqrt(pd/n) << " " << sqrt(pt/n) << " " << sqrt(pz/n) << " "
// 	<< sqrt(dd/n) << " " << sqrt(dt/n) << " " << sqrt(dz/n) << " "
// 	<< sqrt(tt/n) << " " << sqrt(tz/n) << " " << sqrt(zz/n) << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
D0Miss::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
D0Miss::endRun( Frame& iFrame )         // anal4 equiv.
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
