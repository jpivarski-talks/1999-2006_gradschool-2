// -*- C++ -*-
#if !defined(LCDTRACKCLUSTERMATCHINGPROD_LCDMATCHTRACKPROXY_H)
#define LCDTRACKCLUSTERMATCHINGPROD_LCDMATCHTRACKPROXY_H
//
// Package:     <LCDTrackClusterMatchingProd>
// Module:      LCDMatchTrackProxy
//
/**\class LCDMatchTrackProxy LCDMatchTrackProxy.h LCDTrackClusterMatchingProd/LCDMatchTrackProxy.h
 
 Description: Proxy to "handle" LCDMatchTrack

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed Jun 16 12:24:42 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "LCDMatching/LCDMatchTrack.h"
#include "LCDMatching/LCDIsolateCluster.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class LCDMatchTrackProxy : public ProxyBindableTemplate< FAPtrTable< LCDMatchTrack > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< LCDMatchTrack > value_type ;

      // Constructors and destructor
      LCDMatchTrackProxy();
      LCDMatchTrackProxy(double iTrackMatchDistCM);
      virtual ~LCDMatchTrackProxy();

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
      LCDMatchTrackProxy( const LCDMatchTrackProxy& );

      // assignment operator(s)
      const LCDMatchTrackProxy& operator=( const LCDMatchTrackProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (LCDMatchTrackProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_ptrTable ;
      double m_trackMatchDistCM;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "LCDTrackClusterMatchingProd/Template/LCDMatchTrackProxy.cc"
//#endif

#endif /* LCDTRACKCLUSTERMATCHINGPROD_LCDMATCHTRACKPROXY_H */
