// -*- C++ -*-
//
// Package:     ZDAlignmentBhabhaFilterProc
// Module:      ZDAlignmentBhabhaFilterProc_DONT_TOUCH2
// 
// Description: DONT TOUCH THIS FILE!
//
//              Factory method to create processor ZDAlignmentBhabhaFilterProc:
//              creates a new ZDAlignmentBhabhaFilterProc instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Jim Pivarski
// Created:     Fri Dec  5 12:08:39 EST 2003
// $Id: ZDAlignmentBhabhaFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2003/12/05 17:54:58 mccann Exp $
//
// Revision history
//
// $Log: ZDAlignmentBhabhaFilterProc_DONT_TOUCH2.cc,v $
// Revision 1.1.1.1  2003/12/05 17:54:58  mccann
// imported ZDAlignmentBhabhaFilterProc sources
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             

// user include files
#include "ZDAlignmentBhabhaFilterProc/ZDAlignmentBhabhaFilterProc.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ZDAlignmentBhabhaFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2003/12/05 17:54:58 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" {
   Processor* makeProcessor( void );
   const char* versionString( void );
}

Processor*
makeProcessor( void )
{
   return new ZDAlignmentBhabhaFilterProc;
}

const char*
versionString( void )
{
   return kTagString;
}

