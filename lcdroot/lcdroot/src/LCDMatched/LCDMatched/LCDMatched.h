#if !defined(LCDTRACKSHOWERMATCHINGPROD_LCDMATCHED_H)
#define LCDTRACKSHOWERMATCHINGPROD_LCDMATCHED_H
// -*- C++ -*-
//
// Package:     <LCDTrackShowerMatchingProd>
// Module:      LCDMatched
// 
/**\class LCDMatched LCDMatched.h LCDTrackShowerMatchingProd/LCDMatched.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed May  5 13:40:24 EDT 2004
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

using LCDRootAccess::Vector;

// forward declarations

class LCDMatched
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      typedef int Identifier;

      // ---------- Constructors and destructor ----------------
      LCDMatched();
      LCDMatched(Identifier id, LCDTrack* track);
      virtual ~LCDMatched();

      // ---------- member functions ---------------------------

      void addEMcluster(LCDCluster* cluster, double distance, double error);
      void addHADcluster(LCDCluster* cluster, double distance, double error);
      Vector<LCDCluster>& emClusters();
      Vector<LCDCluster>& hadClusters();

      // ---------- const member functions ---------------------

      Identifier identifier() const {return m_identifier;}
      const LCDTrack& t() const {return *m_track;}

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      LCDMatched( const LCDMatched& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LCDMatched& operator=( const LCDMatched& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      Identifier m_identifier;
      LCDTrack* m_track;
      vector<const LCDCluster*> m_EMclusters;
      vector<const LCDCluster*> m_HADclusters;
      Vector<LCDCluster>* m_EMclusters2;
      Vector<LCDCluster>* m_HADclusters2;
      vector<double> m_EMdistances;
      vector<double> m_EMerrors;
      vector<double> m_EMsigmas;
      vector<double> m_HADdistances;
      vector<double> m_HADerrors;
      vector<double> m_HADsigmas;
      double m_EMenergy;
      double m_HADenergy;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "LCDTrackShowerMatchingProd/Template/LCDMatched.cc"
//#endif

#endif /* LCDTRACKSHOWERMATCHINGPROD_LCDMATCHED_H */
