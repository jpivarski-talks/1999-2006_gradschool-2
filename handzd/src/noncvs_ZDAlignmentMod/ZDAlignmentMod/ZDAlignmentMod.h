// -*- C++ -*-
#if !defined(ZDALIGNMENTMOD_ZDALIGNMENTMOD_H)
#define ZDALIGNMENTMOD_ZDALIGNMENTMOD_H
//
// Package:     ZDAlignmentMod
// Module:      ZDAlignmentMod
//
/**\class ZDAlignmentMod ZDAlignmentMod.h ZDAlignmentMod/ZDAlignmentMod.h
 
 Description: see ZDAlignmentMod.cc

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 14:40:29 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "CommandPattern/Module.h"
#include "CommandPattern/Parameter.h"
#include "FrameIterate/FrameIteratorModuleBase.h"
#include "FrameIterate/FIHolder.h"
#include "ZDAlignmentMod/ZDAlignmentFcn.h"

// forward declarations

class ZDAlignmentMod : public FrameIteratorModuleBase
{
      // ---------- friend classes and functions ---------------
      friend class ZDAlignmentFcn;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ZDAlignmentMod();
      virtual ~ZDAlignmentMod();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      ///override this function to do the actual iterations
      virtual void iterate( const FIFrameIterator& iBegin,
			    const FIFrameIterator& iEnd );

      CLEOConstantsModifiable<DBZDGeomAlignment> m_geometry;
      CLEOConstantsModifiable<DBAZDGeomLayer> m_geomlayer;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ZDAlignmentMod( const ZDAlignmentMod& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ZDAlignmentMod& operator=( const ZDAlignmentMod& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      FIHolder<CLEOConstants<DBZDGeomAlignment> > m_geometry_holder;
      FIHolder<CLEOConstants<DBAZDGeomLayer> > m_geomlayer_holder;
      bool m_first_time;

      Parameter<string> m_geomName;
      Parameter<string> m_geomLayerName;
      Parameter<double> m_minDrift;
      Parameter<double> m_maxDrift;
      Parameter<DABoolean> m_showPlots;
      Parameter<DABoolean> m_interactive;
      Parameter<DABoolean> m_fakeDriftFunction;
      Parameter<double> m_crossingangle_x;
      Parameter<double> m_crossingangle_y;
      Parameter<double> m_asymmetric_beamz;

      ZDAlignmentFcn m_fcn;
      MinuitInterface* m_minuit;


      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "ZDAlignmentMod/Template/ZDAlignmentMod.cc"
//#endif

#endif /* ZDALIGNMENTMOD_ZDALIGNMENTMOD_H */
