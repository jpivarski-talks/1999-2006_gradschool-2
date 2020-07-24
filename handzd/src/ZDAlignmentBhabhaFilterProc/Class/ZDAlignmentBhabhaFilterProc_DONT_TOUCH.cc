// -*- C++ -*-
//
// Package:     ZDAlignmentBhabhaFilterProc
// Module:      ZDAlignmentBhabhaFilterProc_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Definition of bind action
//
// Implementation:
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 12:08:39 EST 2003
// $Id: ZDAlignmentBhabhaFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2003/12/05 17:54:58 mccann Exp $
//
// Revision history
//
// $Log: ZDAlignmentBhabhaFilterProc_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2003/12/05 17:54:58  mccann
// imported ZDAlignmentBhabhaFilterProc sources
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "ZDAlignmentBhabhaFilterProc/ZDAlignmentBhabhaFilterProc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ZDAlignmentBhabhaFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2003/12/05 17:54:58 mccann Exp $";
static const char* const kTagString = "$Name:  $";

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
ZDAlignmentBhabhaFilterProc::bind(
   ActionBase::ActionResult (ZDAlignmentBhabhaFilterProc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<ZDAlignmentBhabhaFilterProc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
