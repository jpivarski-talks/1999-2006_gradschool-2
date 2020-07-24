#if !defined(ZDHITSTUDY_HIDUALTRACKCONSTRAINT_H)
#define ZDHITSTUDY_HIDUALTRACKCONSTRAINT_H
// -*- C++ -*-
//
// Package:     <ZDHitStudy>
// Module:      MyDualTrackConstraint
// 
/**\class MyDualTrackConstraint MyDualTrackConstraint.h ZDHitStudy/MyDualTrackConstraint.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Dec  2 15:05:49 EST 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "HelixIntersection/HIFitConstraint.h"
#include "CLHEP/Geometry/Vector3D.h"

// forward declarations

class MyDualTrackConstraint : public HIFitConstraint
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

      MyDualTrackConstraint(
	 DABoolean aPointConstraint,
	 DABoolean aMomentumConstraint,
	 double aMagneticFieldZ,
	 const HepVector3D& aVirtualPhotonMomentum);
      virtual ~MyDualTrackConstraint();

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
      MyDualTrackConstraint( const MyDualTrackConstraint& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MyDualTrackConstraint& operator=( const MyDualTrackConstraint& ); // stop default

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
//# include "ZDHitStudy/Template/MyDualTrackConstraint.cc"
//#endif

#endif /* ZDHITSTUDY_HIDUALTRACKCONSTRAINT_H */
