// -*- C++ -*-
//
// Package:     LCDTrackShowerMatchingProd
// Module:      T_LCDMatched
// 
// Description: Instantiate Classes for LCDMatched
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

// user include files
#include "LCDMatched/LCDMatched.h"

#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_MANY( LCDMatched )
//Use the following if 'LCDMatched' contains a ','
// also make sure there are no blank spaces within 'LCDMatched'
/* INSTANTIATE_MANY_1_COMMA( LCDMatched ) */

//Uncomment the following if LCDMatched ::Identifier is not
// some type of unsigned integer
//#define INSTANTIATE_FATABLE_MAP
#include "FrameAccess/instantiate_many.h"
