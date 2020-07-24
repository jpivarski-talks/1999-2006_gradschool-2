#if !defined(ZDALIGNMENTMOD_ZDALIGNMENTDUALTRACKCONSTRAINT_H)
#define ZDALIGNMENTMOD_ZDALIGNMENTDUALTRACKCONSTRAINT_H
// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentDualTrackConstraint
// 
/**\class ZDAlignmentDualTrackConstraint ZDAlignmentDualTrackConstraint.h ZDAlignmentMod/ZDAlignmentDualTrackConstraint.h

 Description: see ZDAlignmentMod.cc

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Dec  2 15:05:49 EST 2003
// $Id: ZDAlignmentDualTrackConstraint.h,v 1.1.1.1 2003/12/05 23:20:00 mccann Exp $
//
// Revision history
//
// $Log: ZDAlignmentDualTrackConstraint.h,v $
// Revision 1.1.1.1  2003/12/05 23:20:00  mccann
// imported ZDAlignmentMod sources
//

// system include files

// user include files
#include "HelixIntersection/HIFitConstraint.h"
#include "CLHEP/Geometry/Vector3D.h"

// forward declarations

class ZDAlignmentDualTrackConstraint : public HIFitConstraint
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum Constraints { kD0 = 0,
			 kZ0 = 1,

			 kPx = 0,
			 kPy = 1,
			 kPz = 2 };

      // ---------- Constructors and destructor ----------------

      ZDAlignmentDualTrackConstraint(
	 DABoolean aPointConstraint,
	 DABoolean aMomentumConstraint,
	 double aMagneticFieldZ,
	 const HepVector3D& aVirtualPhotonMomentum);
      virtual ~ZDAlignmentDualTrackConstraint();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual int numberOfConstraints() const
      { return (m_pointConstraint ? 2 : 0) + (m_momentumConstraint ? 3 : 0); }

      virtual HepVector constraint(
         const STL_VECTOR( HIFitHelix* )& aHelices ) const ;

      virtual HepMatrix constraintDerivatives( 
         const STL_VECTOR( HIFitHelix* )& aHelices ) const ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ZDAlignmentDualTrackConstraint( const ZDAlignmentDualTrackConstraint& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ZDAlignmentDualTrackConstraint& operator=( const ZDAlignmentDualTrackConstraint& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      DABoolean m_pointConstraint;
      DABoolean m_momentumConstraint;
      double m_Bz;
      HepVector3D m_Ptot;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "ZDAlignmentMod/Template/ZDAlignmentDualTrackConstraint.cc"
//#endif

#endif /* ZDALIGNMENTMOD_ZDALIGNMENTDUALTRACKCONSTRAINT_H */
