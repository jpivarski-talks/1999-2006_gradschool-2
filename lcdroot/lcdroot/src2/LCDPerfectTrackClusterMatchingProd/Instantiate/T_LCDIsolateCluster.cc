// -*- C++ -*-
//
// Package:     LCDPerfectTrackClusterMatchingProd
// Module:      T_LCDIsolateCluster
// 
// Description: Instantiate Classes for LCDIsolateCluster
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

// user include files
#include "LCDMatching/LCDIsolateCluster.h"

#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_MANY( LCDIsolateCluster )
//Use the following if 'LCDIsolateCluster' contains a ','
// also make sure there are no blank spaces within 'LCDIsolateCluster'
/* INSTANTIATE_MANY_1_COMMA( LCDIsolateCluster ) */

//Uncomment the following if LCDIsolateCluster ::Identifier is not
// some type of unsigned integer
//#define INSTANTIATE_FATABLE_MAP
#include "FrameAccess/instantiate_many.h"
