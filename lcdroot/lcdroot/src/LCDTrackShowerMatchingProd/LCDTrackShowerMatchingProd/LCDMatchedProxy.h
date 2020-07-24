// -*- C++ -*-
#if !defined(LCDTRACKSHOWERMATCHINGPROD_LCDMATCHEDPROXY_H)
#define LCDTRACKSHOWERMATCHINGPROD_LCDMATCHEDPROXY_H
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDMatchedProxy
//
/**\class LCDMatchedProxy LCDMatchedProxy.h LCDTrackShowerMatchingProd/LCDMatchedProxy.h
 
 Description: Proxy to "handle" LCDMatched

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed May  5 16:01:36 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "LCDMatched/LCDMatched.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class LCDMatchedProxy : public ProxyBindableTemplate< FAPtrTable< LCDMatched > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< LCDMatched > value_type ;

      // Constructors and destructor
      LCDMatchedProxy();
      LCDMatchedProxy(double iEMmatchingDistanceCmCut,
		      double iEMmatchingErrorCmCut,
		      double iEMmatchingDistanceSigmasCut,
		      double iHADmatchingDistanceCmCut,
		      double iHADmatchingErrorCmCut,
		      double iHADmatchingDistanceSigmasCut);
      virtual ~LCDMatchedProxy();




      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      LCDMatchedProxy( const LCDMatchedProxy& );

      // assignment operator(s)
      const LCDMatchedProxy& operator=( const LCDMatchedProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (LCDMatchedProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_ptrTable ;

      double m_EMmatchingDistanceCmCut;
      double m_EMmatchingErrorCmCut;
      double m_EMmatchingDistanceSigmasCut;
      double m_HADmatchingDistanceCmCut;
      double m_HADmatchingErrorCmCut;
      double m_HADmatchingDistanceSigmasCut;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "LCDTrackShowerMatchingProd/Template/LCDMatchedProxy.cc"
//#endif

#endif /* LCDTRACKSHOWERMATCHINGPROD_LCDMATCHEDPROXY_H */
