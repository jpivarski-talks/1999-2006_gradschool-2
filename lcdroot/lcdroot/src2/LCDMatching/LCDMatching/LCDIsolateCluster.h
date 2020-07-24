#if !defined(LCDMATCHING_LCDISOLATECLUSTER_H)
#define LCDMATCHING_LCDISOLATECLUSTER_H
// -*- C++ -*-
//
// Package:     <LCDMatching>
// Module:      LCDIsolateCluster
// 
/**\class LCDIsolateCluster LCDIsolateCluster.h LCDMatching/LCDIsolateCluster.h

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

class LCDIsolateCluster
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef int Identifier;

      // ---------- Constructors and destructor ----------------
      LCDIsolateCluster();
      LCDIsolateCluster(Identifier id, const LCDCluster* iCluster);
      virtual ~LCDIsolateCluster();

      // ---------- member functions ---------------------------

      Identifier identifier() const;
      const LCDCluster* cluster() const;
      const vector<const LCDTrack*>& track() const;
      const vector<double>& distance() const;
      double closest() const;

      void addTrack(const LCDTrack* iTrack, double iDistance);

      // ---------- const member functions ---------------------
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      LCDIsolateCluster( const LCDIsolateCluster& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LCDIsolateCluster& operator=( const LCDIsolateCluster& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      Identifier m_identifier;
      const LCDCluster* m_cluster;
      vector<const LCDTrack*> m_track;
      vector<double> m_distance;
      double m_closest;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "LCDMatching/Template/LCDIsolateCluster.cc"
//#endif

#endif /* LCDMATCHING_LCDISOLATECLUSTER_H */
