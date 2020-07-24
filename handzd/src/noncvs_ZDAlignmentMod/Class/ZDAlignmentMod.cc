// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentMod
// 
// Description: Allows global minimization of the ZD via minuit "set par" commands, or automatically via "mini"
//
// Implementation:
//     When you first type "iterator go", this module opens a
//     HistogramViewer window with seven key plots for alignment.  Arrange
//     these plots nicely, because this is the last chance you will have
//     to interact with the HistogramViewer window.  Once you press
//     "Continue," the module will load the tracks and hits you created
//     with ZDAlignmentBhabhaFilterProc (or recreate them, if you select
//     CalibratedZDHitProd in your tcl script) and store them in memory
//     for fast access.  It will then start Minuit interactive mode, and
//     you are free to fix, release, change, and optimize the parameters.
//     When you do give Minuit a "mini" command to optimize some set of
//     parameters, Minuit minimizes the root mean square of all residuals
//     shown in the plots.  (The value of "FCN" is in millimeters.)  The
//     plots are redrawn each time the function is evaluated (and only
//     when the plots are evaluated--- sorry! you might have to turn off
//     your screensaver!).
// 
//     HOW TO USE THIS MODULE AND WHAT PLOTS/PARAMETERS MEAN
// 
//     The point is that Minuit does what it does best: optimization, and
//     you do what you do best: recognizing obvious trends in the data.
// 
//     Here's how to interpret the plots:
//        0. The vertical axes for all profile plots are residuals *in
//     millimeters* (because all those zeros take up precious screen
//     space).
//        1. V ndrift: "V" is for "versus" implying "residual versus".
//     This plot shows ZD hit residuals versus normalized drift distance
//     (+/-1 are the edges of the cell).  It is cut at hit-loading time to
//     choose the best part of the drift cell; the inner and outer cuts
//     are configurable by parameters (minDrift, maxDrift).  A gap between
//     negative and positive drift distances indicates a global T0
//     problem.
//        2. V layer: residual versus layer.  For now, hits in layers 1
//     and 6 are dropped, so these two bins will be zero unless you change
//     the code.  This cut is made at hit-loading time.  A gap between
//     layers 1,2,3 and layers 4,5,6 indicates a Z offset.
//        3. V cotTheta: residual versus cotTheta, or, the length of the
//     wire.  I don't know how to interpret the slope that I see in this
//     plot: could it have something to do with getting the time of flight
//     or signal propogation corrections wrong?  There is a slight bowing
//     in timelike residuals VS cotTheta (not plotted by this module)
//     which could be accounted for by this effect.
//        4. V phi (-theta): residual versus phi for -2.0 < cotTheta < -1.4.
//        5. V phi (0theta): residual versus phi for -1.4 < cotTheta <  1.4.
//        6. V phi (+theta): residual versus phi for  1.4 < cotTheta <  2.0.
//     Sine and cosine curves in these plots indicate x, y, phix, and phiy
//     misalignments.  If all three show the same sine (cosine) curve, you
//     need to shift x (y).  If the siGn of the curve flips from -theta to
//     +theta, it is a phiy (phix) tilt.  In general, these will be a
//     linear combination of misalignments.  But an orthogonal basis, at
//     least!
//        7. resid: This is a 1D histogram of residuals, because it's
//     always a good idea to keep an eye on this.  (Do those residuals
//     come from tails or a wide distribution?)
// 
//     Here's how to interpret the parameters:
//        1. x, y, z: global translations in millimeters (the
//     ZDGeomAlignment file expresses them in meters).  Z is the beamline,
//     Y is the sky.
//        2. rotx, roty, rotz: rotations around the x, y, and z axes,
//     respectively, all in milliradians (the ZDGeomAlignment file
//     expresses them in radians).  Rotz is perhaps the most significant;
//     it corresponds to a roll of the detector.  If this weren't
//     interactive, you'd have to worry about the order in which these are
//     applied.
//        3. t0, drift: IF you use the non-default parameter
//     fakeDriftFunction, all time-to-drift relations are replaced by a
//     linear function with offset "t0" and slope "drift".  "t0" is in
//     nanoseconds and "drift" is in microns per nanosecond.  This is just
//     provided as a way to be sure that you're not being fooled by a bug
//     in the drift functions.
//       4. radius, del_rad_45: A slope in residual versus cotTheta (such
//     as the one I don't understand) can be corrected by shifting the
//     radii of all wires in the ZD.  Don't do this.  "del_rad_45" allows
//     you to shift the radii of U layers differently from V layers.
//     Don't do this either.
//       5. sagx, sagy: wires can sag down gravitationally and in other
//     directions with a little more imagination.  Dan says that this
//     effect will be too small to see.
//       6. twistWest: this parameter will allow you to twist the west
//     endplate independently of the east endplate, in case there's a
//     little of internal alignment to do.  (This was also motivated by
//     the residual versus cotTheta slope.)  Don't do this, either.
//
//     This module does a few little things to help you recover from a
//     crash (it writes its own will): every time the function is
//     evaluated, it writes out two files, state.zdgeomalignment (the
//     alignment currently being tested) and state.pars (the values of all
//     parameters currently being tested.  If you crash and want to pick
//     up where you left off, set the parameter "geom" to
//     "state.zdgeomalignment", and if you've been playing with the other
//     parameters (which you shouldn't), paste the contents of
//     "state.pars" into your Minuit commandline.
// 
//     Better yet, whenever this module sees an alignment which is better
//     than any it has seen in its life, it will write
//     best.zdgeomalignment and best.pars, so that you can start from a
//     nearly optimized point, rather than the wild set of parameters that
//     probably caused Minuit to crash in the first place.
//
//     One last thing for the Usage Section: as should be explained in the
//     CBX (which should exist by the time you're reading this... who
//     knows) tracks for ZD alignment are fitted with a chi^2 fit and
//     constrained to be back-to-back by a dual track constraint.  The
//     dual track constraint depends on beam energy and crossing angle; if
//     either changes, you will need to pass the new value (in terms of
//     the momentum components of the virtual photon, after collision)
//     into both ZDAlignmentMod and ZDAlignmentBhabhaFilterProc by
//     parameter.  You will know that you inserted the right crossing
//     angle when the "tracks momentum phi" histogram in
//     ZDAlignmentBhabhaFilterProc is flat: no sine or cosine terms.
//
//     I thought using Minuit was a pretty clever way to avoid writing an
//     interface, and get the ability to automatically optimize for free.
//     The down-side of this is that you have to know Minuit commands to
//     use this module.  The up-side of this is that I don't have to
//     document them.  Here's a link:
//
//        http://wwwasdoc.web.cern.ch/wwwasdoc/WWW/minuit/minmain/chapter2_8.html
//
//     These are the commands you will find most useful:
//        1. "show par" shows current parameter values AND the function
//     value, so you can use it as a way to invoke
//     ZDAlignmentFcn::iterate().
//        2. "set par N value" Parameters are numbered by N.  This is the
//     command you would use for a purely manual alignment.
//        3. "fix N" for when you don't want a parameter to be used in an
//     optimization.
//        4. "rel N" to release it and allow it to be optimized.
//        5. "mini" to sit back and watch the ZD get aligned.
//
//     NOTES ON INTERNALS OF THE CODE
//
//     I don't expect this module to be perfect as-is: I expect you to
//     make modifications as alignment mysteries get solved.  So here's a
//     quick walk through the code.
//
//     There are three classes:
//        1. ZDAlignmentMod (this one): where tracks and hits are loaded
//     from the PDS files, most cuts are performed, and Minuit is invoked.
//        2. ZDAlignmentDualTrackConstraint: where the point and momentum
//     constraints for two tracks are defined.  This is similar to
//     HIDualTrackConstraint in HelixIntersection, but this also
//     constrains pz1 + pz2 (or, roughly, theta1 == -theta2).
//        3. ZDAlignmentFcn: this is the class that gets filled with
//     tracks and hits, opens windows, defines histograms, calculates the
//     RMS residual for Minuit, fills the histograms, and writes out
//     state.* and best.*.
//
//     Don't be confused by the fact that ZDAlignmentMod and
//     ZDAlignmentFcn both have ::iterate() methods.
//     ZDAlignmentMod::iterate() is what gets called when you "iterator
//     go", and ZDAlignmentFcn::iterate() is what gets called by Minuit.
//     They are completely different and have nothing to do with one
//     another.
//
//     Some essential steps in the process might seem to be missing, this
//     is because they are done by code elsewhere in suez (through the
//     miracle of object orientation):
//        1. ZDAlignmentDualTrackConstraint only defines its own
//     constraints and the derivatives of those constraints with respect
//     to track parameters.  The application of the constraint happens in
//     its superclass when the inherited applyConstraint() method is
//     called.
//        2. The function minimization is done by a package called Minuit,
//     which I have been assuming that you knew all this time.
//     ZDAlignmentFcn is a subclass of MIFcn, so I only need to define the
//     iterate() function and, when invoked, Minuit will call that
//     iteratively to minimize its output.  Its output is therefore the
//     RMS residual.
//        3. Whenever you change constants using CLEOConstantsModifiable,
//     the whole suez world needs to be made aware of the update.  Because
//     the author of the iterator module object was expecting me to
//     re-extract tracks and hits from the Frame after making a constants
//     change, the suez world is updated only when you set a
//     FIFrameIterator using the "=" operator.  Therefore,
//     AZDSenseWireStore and HelixIntersection become aware of the changed
//     constants at the "FIFrameIterator itFrame = *m_frame;" line in
//     ZDAlignmentFcn::iterate().  It seems like a meaningless line and
//     can easily be missed, but it is a crucial line of code.
//
//     Now for that walk I promised!  You start suez with the "align.tcl"
//     script (or one inspired by it).  All the producers are loaded, this
//     module is loaded, iterator go is iterator gone, and you enter
//     ZDAlignmentMod::iterate().  Since this is the first time, two
//     geometry files are loaded: ZDGeomAlignment (where all the global
//     translations and rotations are defined) and AZDGeomLayer (a hack to
//     allow you to change wire positions; don't do it!).  ZDAlignmentFcn
//     acquired all of its parameters in its constructor (which is called
//     in ZDAlignmentMod's constructor), and now those parameters are set
//     to the values given in the ZDGeomAlignment file.  m_first_time is
//     set to false.
//
//     ZDAlignmentFcn::reset() is called: this deletes any memory-resident
//     tracks and hits so that it will be ready for a new set.  The
//     FIFrameIterator iBegin is passed so that ZDAlignmentFcn will have a
//     pointer to it, with which it can execute its all-important line and
//     notify the suez world of constants changes.
//
//     We begin a loop over FIFrameIterators.  If you're new to iterator
//     modules, this is a for-loop over events: a level of control you
//     wouldn't have with a processor.  The first thing that happens is
//     that ZDAlignmentFcn::book() is called.
//
//     ZDAlignmentFcn::book() does a number of miscellaneous things.  It
//     tells ZDAlignmentFcn about any changes to the parameters
//     "showPlots" and "fakeDriftFunction", so it can respond to user
//     changes in these parameters between "iterator go" calls.  IF THIS
//     IS THE FIRST CALL TO ZDAlignmentFcn::book(), it will do the
//     following initializations:
//        1. Keep track of the original wire radii for each layer, which
//     you shouldn't use to specify radius shifts.
//        2. Book the seven histograms that I talked about in the above
//     section.
//        3. Initialize Qt and the HistogramViewer window.  At this point,
//     control is given to the user to open all of those windows (because
//     I don't know how to make it automatic).  The program will wait
//     indefinitely until the user presses "Continue."  "Interact" and
//     "UpdateFrequency" have no meaning here, they are meant for
//     HistogramViewerProc, which *isn't* a hack.
//
//     After ZDAlignmentFcn::book(), we extract a few things from the
//     Frame (ultimately from the PDS file prepared by
//     ZDAlignmentBhabhaFilterProc): NavTracks, CalibratedZDHits, and a
//     MagneticField.  The program will crash if there are more or less
//     than two tracks, or if they have different reference points
//     (assertions are in ZDAlignmentDualTrackConstraint::constraint()).
//     We set up a vector of two HIFitHelix pointers (which is what
//     HIFitConstraint wants) and create the constraint object on the
//     stack.  Five constraints are applied: d01 + d02 == 0,
//     z01 - z02 == 0 and (px,py,pz) = (-15 MeV, 0, 0).  The last
//     constraint is not (0,0,0) because the crossing angle of the two
//     beams introduces a small virtual photon momentum.  The array
//     indexes are complicated because I wanted to provide the possibility
//     of using the point contraint, the momentum constraint, or both.
//     (I've only tested the code using both constraints.)  Also be aware
//     that the constraints go into a HepVector, referenced by square
//     brackets, starting from zero.  The constraint derivatives go into a
//     HepMatrix, referenced by parentheses, starting from one.  I tried
//     to make all this index stuff clear by including an explicit offset.
//
//     ZDAlignmentDualTrackConstraint is the only object that needs a
//     MagneticField: it's to convert curvatures into momenta.  (I cribbed
//     the conversion constant from KTHelix.cc.)  If it weren't for the
//     crossing angle, I could drop the Bz-dependence and make the module
//     easier to load.  As I said in the Usage section, you must be sure
//     to give this constraint the right crossing angle.  I've seen at
//     least three different definitions of this angle, so I ask for it in
//     terms of the virtual photon momentum after collision (the expected
//     total momentum of the event), which is easiest to measure.
//     Unfortunately, this introduces an implicit beam energy dependence.
//
//     Next I make some event-level cuts: first, the reduced dualchi^2
//     (chi^2 of the dual-track constraint, not the track fit) must be
//     less than 20.  This cuts out ISR-radiative bhabhas.  Second, the
//     bhabha angle must be greater than 22.5 degrees from beam axis.
//     (Cutting both positron and electron cotThetas guarantees symmetry.
//     Who cares if it might be redundant?)
//
//     After that, I loop over hit links, keeping track of the average
//     charge on the track and the signs of the drift distances.  I make
//     some hit-level cuts and fill vectors on the stack with all relevant
//     information for this track.  When I am done and have some hits left
//     after cuts, I fill ZDAlignmentFcn with a function reminiscent of
//     histogram filling.  ZDAlignmentFcn::fill() COPIES this information
//     into its memory-resident lists, and we let the temporary vectors
//     die when the stack is popped.  (By "stack" I mean the computer's
//     machine-level stack, as opposed to the heap.  I'm not using the
//     vectors like stacks: "push_back" is just a convenient way of
//     filling them.)
//
//     This is the information that ZDAlignmentFcn::fill() stores for
//     each track:
//        1. its helix (dual-constrained)
//        2. its average charge (because HelixIntersection seems to want
//     that... could it be a problem that I average charge over ZD hits
//     alone, and don't include DR hits in the average?  Changing this
//     would be a major ordeal.)
//       3. a set of hits
//       4. a set of drift distances (with signs assigned by doit)
//
//     You will notice that ZDAlignmentFcn::fill() contains some hairy
//     expressions involving vectors of pointers to vectors of pointers,
//     as well as iterators over them.  I could have hidden this
//     complexity by making a lot of typedefs, but I always find that MORE
//     confusing.  At least you can see the types of objects that you're
//     looking at, so solving the problem of how to use them only requires
//     logic, not searching for definitions in some other file somewhere.
//
//     This comes to the end of ZDAlignmentMod::iterate(): all that's left
//     is to fix the Minuit parameters you're not supposed to touch, and
//     call interact().  (Or runMigrad(), if you've chosen to do this as a
//     batch job.  I haven't tested it and I don't recommend it: it would
//     be irresponsible not to look at the plots.)
//
//     All the histogram-filling, state-outputting, and even window
//     redrawing happens in ZDAlignmentFcn::iterate(), which is called
//     whenever and only when Minuit feels like it.  (So be careful not to
//     drag anything across your plot window or you'll have to regenerate
//     it.)  Minuit calls ZDAlignmentFcn::iterate() when you view the
//     function value for the first time or after any parameter has
//     changed.  Luckily for you, this is true even if you set a parameter
//     to the value it previously had.  (E.g. x == 0, but you want to
//     redraw the plots, so you explicitly set x to 0 and call a "show
//     par".)  Minuit will also call ZDAlignmentFcn::iterate() when you
//     exit interactive mode, but you don't need to wait for this if you
//     have your favorite alignment constants saved to
//     best.zdgeomalignment.  Control-c quits more quickly.
//
//     Here's a run-through of ZDAlignmentFcn::iterate():
//        1. The CLEOConstantsModifiable m_geometry is set to the
//     alignment that you or Minuit would like to test.
//        2. m_geomlayer is set based on the original wire radii and the
//     "radius" parameter that you're not supposed to use.
//        3. One line of text describing the new alignment is printed to
//     the screen, and state.* are updated as well.
//        4. "FIFrameIterator itFrame = *m_frame;":  constants are
//     reloaded and geometry objects are recreated using the new values.
//     Arguably the most important line in the entire program.
//        5. A ZD hitcorrector, wire geometry object, and zdgas material
//     description are loaded from the newly reset Frame.  Note that we
//     never ask for anything event-dependent, because we're not actually
//     looping over events.
//        6. The histograms are reset: there is a bug in Oct15_03_MC and
//     earlier that causes this step to crash.  If you must use
//     Oct15_03_MC (which I do: HistogramViewer is more managable in this
//     release), compile HbookHistogram and HbookHistogramModule in your
//     local area (in that order) and "module sel
//     your/HbookHistogramModule".
//        7. Loop over tracks and hits.  Arguably, these should be
//     for-loops, not while-loops, but I need to loop over synchronized
//     lists, which I do just by trusting them to be in the same order.
//     (They ought to be--- I created them in that order.)  The ++iterator
//     commands are at the bottoms of the while loops, where you can't
//     see them so easily.  I remind you that they're important by doing
//     assertions on them at the top of the loop.
//        8. In the hit loop, I immediately give up on bad wires, as
//     supplied by Karl Ecklund.  Karl has picked these wires out for
//     being tugged by bushing material, shifting their endpoint position
//     on one end of the chamber.
//        9. Next I create a surface by hand (without HIZDSurfaceFactory,
//     which makes reference to the event's Frame), passing it the signed
//     drift distance, ZD hit corrector, and average charge on the track.
//       10. I move the track's reference point (the track, by the way, is
//     a local copy) to a point near the wire.  This is what
//     HISingleWireCylinder expects, since it is usually used in track
//     fits, where the the reference point is at the previous hit--- not
//     far from the current hit.  In ZDAlignmentFcn, if we call
//     swimToCurrentSurface() with the default reference point (0,0,0),
//     the surface will linearly extrapolate the wire from z=0, which
//     could be a long way from the actual hit.  I have since learned that
//     no wire sag is implemented, so the wire really is a straight line
//     (in 3D), but you can never be too careful.
//       11. intersector.swimToCurrentSurface() tells the surface to find
//     the point of closest approach between the wire (represented as a 3D
//     linear extrapolation) and the helix.  I don't know what kinds of
//     iterating goes on in this call.
//       12. applyTrackCorrections() tells the surface to invoke the ZD
//     hit corrector to apply all the track-dependent corrections that the
//     ZD is supposed to have.  Karl recommended only signal propogation
//     and time of flight for the time being; these are selected in the
//     tcl script as parameters to ZDHitCorrectorProd.
//       13. Now I have my helix at point of closest approach, and I can
//     calculate a bunch of things, including the residual.  Then I fill
//     histograms.
//       14. Remember to delete the surface!  It was created on the heap!
//       15. After the loops, the Qt application is updated.  The
//     HistogramViewer object redraws the screen objects from the
//     histograms and Qt is run for as little time as possible--- just
//     enough to get the updates to the screen.  I don't think you'd want
//     to press "Continue" every time Minuit iterates.
//       16. If this alignment is the best we've seen, we write that out
//     to best.*.
//       17. In any case, we exit, returning the RMS residual to Minuit,
//     so it can try to minimize that value.  Incidentally, it's very
//     important that the residual be reported in millimeters, because
//     Minuit is accustomed to minimizing chi^2 functions, in which the
//     tolerance is defined relative to 1.0.  The RMS residual is going to
//     be a number on the order of 1.0 (hopefully as small as 0.1), but
//     Minuit would give up too soon if all the values it's getting are
//     0.0001.  One could set the Minuit tolerance by command, but this
//     was needlessly complicated by factors of up and epsilong and tens
//     that might not have been documented.  I gave up trying to
//     understand how Minuit tolerance is defined.  Millimeters are a good
//     unit for residuals, anyway.
// 
//     DOCUMENTATION OF CHANGES BY THE PERSON AFTER ME
// 
//     Please keep this up to date!  Unless, of course, the ZD is
//     perfectly aligned and you'll never, ever need to align it again.
//     In that case, throw this code away!
// 
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:40:29 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdio.h>
#include <fstream.h>
#include <iostream.h>

// user include files
#include "Experiment/report.h"
#include "ZDAlignmentMod/ZDAlignmentMod.h"
#include "ZDAlignmentMod/ZDAlignmentFcn.h"
#include "DataHandler/Stream.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/extract.h"
#include "DataHandler/Frame.h"
#include "Navigation/NavTrack.h"
#include "TrackFinder/SeedZDHitLink.h"
#include "MagField/MagneticField.h"
#include "ZDAlignmentMod/ZDAlignmentDualTrackConstraint.h"
#include "HelixIntersection/HIFitHelix.h"

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
static const char* const kFacilityString = "ZDAlignmentMod.ZDAlignmentMod" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: fimodule.cc,v 1.2 2000/12/04 19:11:05 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
ZDAlignmentMod::ZDAlignmentMod()
   : FrameIteratorModuleBase( "ZDAlignmentMod", "No, this is the awesomest module." )
   , m_geometry(new DBZDGeomAlignment[3], 3)
   , m_geometry_holder(&m_geometry)
   , m_geomlayer(new DBAZDGeomLayer[6], 6)
   , m_geomlayer_holder(&m_geomlayer)
   , m_first_time(true)
   , m_geomName("geom", this, "best.zdgeomalignment")
   , m_geomLayerName("geomLayer", this, "normal.azdgeomlayer")
   , m_minDrift("minDrift", this, 1.5)  // these are in mm, of course
   , m_maxDrift("maxDrift", this, 3.8)
   , m_showPlots("showPlots", this, true)
   , m_interactive("interactive", this, true)
   , m_fakeDriftFunction("fakeDriftFunction", this, false)
   , m_crossingangle_x("crossingAngleX", this, 0.015)  // appropriate for early cleo-c runs
   , m_crossingangle_y("crossingAngleY", this, 0.)
   , m_asymmetric_beamz("asymmetricBeamZ", this, 0.)
   , m_fcn(&m_geometry, &m_geomlayer)
   , m_minuit(MinuitInterface::instance())
{
   registerProxyFactory(Stream::kZDAlignment,
			m_geometry_holder.makeFactory(),
			UsageTag());
   registerProxyFactory(Stream::kBaseGeometry,
			m_geomlayer_holder.makeFactory(),
			UsageTag());

   //You must set what streams you which to iterate over
   //  that is, what events should the Frames be stopped on
   iterateOver(Stream::kEvent);

   m_minuit->loadFcn(m_fcn);
}

// ZDAlignmentMod::ZDAlignmentMod( const ZDAlignmentMod& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

ZDAlignmentMod::~ZDAlignmentMod()
{
}

//
// assignment operators
//
// const ZDAlignmentMod& ZDAlignmentMod::operator=( const ZDAlignmentMod& rhs )
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
void
ZDAlignmentMod::iterate( const FIFrameIterator& iBegin,
			 const FIFrameIterator& iEnd )
{
   if (m_first_time) {
      ifstream geometry_file(m_geomName.value().c_str());
      if (! m_geometry.readFromStream(geometry_file)) assert(false);

      ifstream geomlayer_file(m_geomLayerName.value().c_str());
      if (! m_geomlayer.readFromStream(geomlayer_file)) assert(false);

      m_minuit->changeParameterStart(ZDAlignmentFcn::kX, m_geometry[0].get_deltaX()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kY, m_geometry[0].get_deltaY()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kZ, m_geometry[0].get_deltaZ()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotX, m_geometry[0].get_rotX()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotY, m_geometry[0].get_rotY()*1000.);
      m_minuit->changeParameterStart(ZDAlignmentFcn::kRotZ, m_geometry[0].get_rotZ()*1000.);

      m_minuit->changeParameterStart(ZDAlignmentFcn::kTwistWest, m_geometry[2].get_rotZ()*1000.);

      m_first_time = false;
   }

   m_fcn.reset(iBegin);

   for(FIFrameIterator itFrame = iBegin;  itFrame != iEnd;  ++itFrame) {
      m_fcn.book(m_showPlots.value(), m_fakeDriftFunction.value());

      FATable<NavTrack> tracks;
      extract(itFrame->record(Stream::kEvent), tracks);

      FATable<CalibratedZDHit> allhits;
      extract(itFrame->record(Stream::kEvent), allhits);

      FAItem<MagneticField> magnetic_field;
      extract(itFrame->record(Stream::kStartRun), magnetic_field);

      FATable<NavTrack>::const_iterator one = tracks.begin();
      FATable<NavTrack>::const_iterator two = tracks.begin();  ++two;
      HIFitHelix dualone(*one->pionHelix());
      HIFitHelix dualtwo(*two->pionHelix());
      dualone.setIdentifier(one->identifier());
      dualtwo.setIdentifier(two->identifier());
      vector<HIFitHelix*> dualtracks;
      dualtracks.push_back(&dualone);
      dualtracks.push_back(&dualtwo);

      ZDAlignmentDualTrackConstraint constraint(true,
						true,
						magnetic_field->BField().z(),
						HepVector3D(m_crossingangle_x.value(),
							    m_crossingangle_y.value(),
							    m_asymmetric_beamz.value()));
      HIFitConstraint::Results results = constraint.applyConstraint(dualtracks);

      if (results.chisq()/results.ndof() > 20.) continue;
      if (fabs(dualtracks[0]->cotTheta()) > 2.) continue;
      if (fabs(dualtracks[1]->cotTheta()) > 2.) continue;

      for (int i = 0;  i < 2;  i++) {
	 const KTHelix& helix = *dualtracks[i];
	 FATable<NavTrack>::const_iterator navtrack_iter = tracks.find(dualtracks[i]->identifier());
	 const NavTrack::SeedZDHitLinkTable* links = navtrack_iter->seedZDHitLinks();
	 NavTrack::SeedZDHitLinkTable::const_iterator link_end = links->end();

	 double charge_sum = 0.;
	 unsigned int charge_N = 0;
	 vector<const CalibratedZDHit*> hits;
	 vector<double> drifts;

	 for (NavTrack::SeedZDHitLinkTable::const_iterator link_iter = links->begin();
	      link_iter != link_end;
	      ++link_iter) {

	    if ((**link_iter).linkData().fitFlag() == SeedZDHitLink::kFITTABLE) {
	       assert(*(**link_iter).rightID());
	       FATable<CalibratedZDHit>::const_iterator hit_iter = allhits.find(*(**link_iter).rightID());

	       charge_sum += hit_iter->charge();  charge_N++;

	       if (fabs(hit_iter->distance()) > m_minDrift.value()/1000. &&
		   fabs(hit_iter->distance()) < m_maxDrift.value()/1000. &&
		   hit_iter->layer() != 1                                &&
		   hit_iter->layer() != 6                                  ) {
		  hits.push_back(&*hit_iter);
		  drifts.push_back((**link_iter).linkData().signedDriftDistance());
	       }

	    } // end if hit is kFITTABLE
	 } // end loop over hit links

	 if (!hits.empty()) m_fcn.fill(helix, charge_sum/double(charge_N), hits, drifts);
      } // end loop over tracks
   } // end loop over events

   if (m_interactive.value()) {
      m_minuit->setDiagLevel(MinuitInterface::kMute);
      for (int i = ZDAlignmentFcn::kT0;  i < ZDAlignmentFcn::kNumParams;  i++) m_minuit->fixParameter(i);
      m_minuit->setDiagLevel(MinuitInterface::kNormal);
      m_minuit->interact();
   }
   else {
      m_minuit->setDiagLevel(MinuitInterface::kMax);
      for (int i = ZDAlignmentFcn::kT0;  i < ZDAlignmentFcn::kNumParams;  i++) m_minuit->fixParameter(i);
      m_minuit->runMigrad();
   }
}

//
// static member functions
//



// for comparing fitter's residuals with mine
// 	 const NavTrack::ZDHitLinkTable* pionLinks = tracks[i].pionZDHitLinks();
// 	 NavTrack::ZDHitLinkTable::const_iterator pionLink_end = pionLinks->end();
// 	 for (NavTrack::ZDHitLinkTable::const_iterator pionLink_iter = pionLinks->begin();
// 	      pionLink_iter != pionLink_end;
// 	      ++pionLink_iter) {
// 	    cout <<  "FITTER SAYS " << (**pionLink_iter).linkData().signedDriftDistance() << " "
// 		 << (**pionLink_iter).linkData().signedDcaToWire() << " "
// 		 << (**pionLink_iter).linkData().residual() << endl;
// 	 }
