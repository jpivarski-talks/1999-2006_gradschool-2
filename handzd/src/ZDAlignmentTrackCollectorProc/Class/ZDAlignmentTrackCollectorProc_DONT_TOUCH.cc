// -*- C++ -*-
//
// Package:     ZDAlignmentTrackCollectorProc
// Module:      ZDAlignmentTrackCollectorProc_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Definition of bind action
//
// Implementation:
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:41:29 EST 2003
// $Id$
//
// Revision history
//
// $Log$
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "ZDAlignmentTrackCollectorProc/ZDAlignmentTrackCollectorProc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor_DONT_TOUCH.cc,v 1.5 1998/12/01 21:11:58 mkl Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// function definitions
//

//
// static data member definitions
//

//
// member functions
//
// ---------------- binding method to stream -------------------
void
ZDAlignmentTrackCollectorProc::bind(
   ActionBase::ActionResult (ZDAlignmentTrackCollectorProc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<ZDAlignmentTrackCollectorProc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
