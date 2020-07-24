// -*- C++ -*-
//
// Package:     ZDAlignmentMod
// Module:      STL_vectorOfCalibratedHits
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 18:10:40 EST 2003
// $Id: 
//
// Revision history
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes
#include <vector>


// class CalibratedHit ;
// class TrackFitDRHitLink ;
// template class pair< const CalibratedHit*, TrackFitDRHitLink* > ;

// typedef pair< const CalibratedHit*, TrackFitDRHitLink* >
// _vector_contents_;

#include "HelixIntersection/HIFitHelix.h"
typedef HIFitHelix::HitAndLinkData _vector_contents_ ;
#include "STLUtility/instantiate_vector.h"

