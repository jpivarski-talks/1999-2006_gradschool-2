// -*- C++ -*-
//
// Package:     ZDAlignmentMod
// Module:      STL_vectorOfCalibratedZDHit
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 17:17:12 EST 2003
// $Id: 
//
// Revision history

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CalibratedData/CalibratedZDHit.h"

// STL classes
#include <vector>


typedef CalibratedZDHit* _vector_contents_;

#include "STLUtility/instantiate_vector.h"

