#if !defined(LCDMATCHING_LCDMATCHTRACK_H)
#define LCDMATCHING_LCDMATCHTRACK_H
// -*- C++ -*-
//
// Package:     <LCDMatching>
// Module:      LCDMatchTrack
// 
/**\class LCDMatchTrack LCDMatchTrack.h LCDMatching/LCDMatchTrack.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed Jun 16 11:14:48 EDT 2004
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

#include "LCDRootAccess/Vector.h"
#include "LCDTrack.h"
#include "LCDCluster.h"

// forward declarations

class LCDMatchTrack
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef int Identifier;

      // ---------- Constructors and destructor ----------------
      LCDMatchTrack();
      LCDMatchTrack(Identifier id, const LCDTrack* iTrack);
      virtual ~LCDMatchTrack();

      // ---------- member functions ---------------------------

      Identifier identifier() const;
      const LCDTrack* track() const;
      const vector<const LCDCluster*>& cluster() const;
      const vector<double>& distance() const;
      double emEnergy() const;
      double hadEnergy() const;

      void addCluster(const LCDCluster* iCluster, double iDistance);

      // ---------- const member functions ---------------------
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      LCDMatchTrack( const LCDMatchTrack& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LCDMatchTrack& operator=( const LCDMatchTrack& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      Identifier m_identifier;
      const LCDTrack* m_track;
      vector<const LCDCluster*> m_cluster;
      vector<double> m_distance;
      double m_emEnergy;
      double m_hadEnergy;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "LCDMatching/Template/LCDMatchTrack.cc"
//#endif

#endif /* LCDMATCHING_LCDMATCHTRACK_H */
