// -*- C++ -*-
//
// Package:     ZDAlignmentMod
// Module:      STL_vectorOfvectorOfdouble
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 17:27:28 EST 2003
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

// STL classes
#include <vector>


typedef vector<double>* _vector_contents_;

#include "STLUtility/instantiate_vector.h"

