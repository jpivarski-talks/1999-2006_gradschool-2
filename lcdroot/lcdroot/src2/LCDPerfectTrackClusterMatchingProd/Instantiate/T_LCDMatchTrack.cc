// -*- C++ -*-
//
// Package:     LCDPerfectTrackClusterMatchingProd
// Module:      T_LCDMatchTrack
// 
// Description: Instantiate Classes for LCDMatchTrack
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
#include "LCDMatching/LCDMatchTrack.h"

#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_MANY( LCDMatchTrack )
//Use the following if 'LCDMatchTrack' contains a ','
// also make sure there are no blank spaces within 'LCDMatchTrack'
/* INSTANTIATE_MANY_1_COMMA( LCDMatchTrack ) */

//Uncomment the following if LCDMatchTrack ::Identifier is not
// some type of unsigned integer
//#define INSTANTIATE_FATABLE_MAP
#include "FrameAccess/instantiate_many.h"
