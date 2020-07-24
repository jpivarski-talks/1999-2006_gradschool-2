#if !defined(LCDROOTACCESS_INSTANTIATE_MANY_H)
#define LCDROOTACCESS_INSTANTIATE_MANY_H
// -*- C++ -*-
//
// Package:     LCDRootAccess
// Module:      Instantiation
// 
// Description: Code required to explicilty instantiate a "Vector" Data element
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris Jones
// Created:     Fri Apr 16 14:32:44 EDT 2004
// $Id: instantiate_many.h,v 1.12 2002/04/03 19:08:33 cleo3 Exp $
//
// Revision history
//
// $Log: instantiate_many.h,v $
//

#include "FrameAccess/instantiate_one.h"
#include "LCDRootAccess/Vector.h"

typedef LCDRootAccess::Vector<_vmany_element_> _vector_element_;


#if defined(NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG)
template void extract< _vector_element_ >( const Record& aRecord ,
					  _vector_element_& aContainer ) ;
template void extract< _vector_element_ >( const Record& aRecord ,
					  _vector_element_& aContainer ,
					  const char* aUseLabel ) ;
template void extract< _vector_element_ >( const Record& aRecord ,
					  _vector_element_& aContainer ,
					  const char* aUseLabel ,
					  const char* aProducerLabel ) ;

#else
template void extract( const Record& aRecord ,
		       _vector_element_& aContainer ) ;
template void extract( const Record& aRecord ,
		       _vector_element_& aContainer ,
		       const char* aUseLabel ) ;
template void extract( const Record& aRecord ,
		       _vector_element_& aContainer ,
		       const char* aUseLabel ,
		       const char* aProducerLabel ) ;

#endif /* NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG */



#endif /* LCDROOTACCESS_INSTANTIATE_MANY_H */
