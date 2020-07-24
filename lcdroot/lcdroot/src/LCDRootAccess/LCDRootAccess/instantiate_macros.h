#if !defined(LCDROOTACCESS_INSTANTIATE_MACROS_H)
#define LCDROOTACCESS_INSTANTIATE_MACROS_H
// -*- C++ -*-
//
// Package:     LCDRootAccess
// Module:      instantiate_macros
// 
// Description: cpp macros useful for instantiating Vector
//
// Usage:
//    These macros facilitate the manual instantiation of all the 
//   templates needed to 'insert' and 'extract' data from the 
//   Data Access System.
//
// Author:      Chris D. Jones
// Created:     Mon Sep 28 16:36:08 EDT 1998
// $Id: instantiate_macros.h,v 1.4 2002/06/12 20:27:41 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_macros.h,v $
//

// system include files

// user include files
#include "HeteroContainer/HCTypeTagTemplate.h"

// forward declerations
class DataKey;
namespace LCDRootAccess {
template< class T > class Vector;
}

#define INSTANTIATE_VECTOR( _instantiate_many_type_ ) \
typedef _instantiate_many_type_ _vmany_element_ ; \
typedef vector<const _vmany_element_*> _one_element_ ; \
template<> \
const char* \
HCTypeTagTemplate< vector< const _instantiate_many_type_* > , DataKey >::className() \
{ return "RLAVector<" #_instantiate_many_type_ ">" ; }

#endif /* LCDROOTACCESS_INSTANTIATE_MACROS_H */
