// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentMod_DONT_TOUCH.cc
// 
// Description: factory function to create ZDAlignmentMod
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Nov 25 09:31:42 EST 2003
// $Id: ZDAlignmentMod_DONT_TOUCH.cc,v 1.1.1.1 2003/12/05 23:20:01 mccann Exp $
//
// Revision history
//
// $Log: ZDAlignmentMod_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2003/12/05 23:20:01  mccann
// imported ZDAlignmentMod sources
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ZDAlignmentMod/ZDAlignmentMod.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: ZDAlignmentMod_DONT_TOUCH.cc,v 1.1.1.1 2003/12/05 23:20:01 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" { 
   Module* makeModule( void ); 
   const char* versionString( void );
}

Module*
makeModule( void )
{
   return new ZDAlignmentMod;
}

const char*
versionString( void )
{
   return kTagString;
}
