#if !defined(ZDALIGNMENTMOD_ZDALIGNMENTFCN_H)
#define ZDALIGNMENTMOD_ZDALIGNMENTFCN_H
// -*- C++ -*-
//
// Package:     <ZDAlignmentMod>
// Module:      ZDAlignmentFcn
// 
/**\class ZDAlignmentFcn ZDAlignmentFcn.h ZDAlignmentMod/ZDAlignmentFcn.h

 Description: see ZDAlignmentMod.cc

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Nov  6 15:26:43 EST 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

#include "MinuitInterface/MinuitInterface.h"
#include "MinuitInterface/MIFcn.h"
#include "HelixIntersection/HIHelix.h"
#include "CalibratedData/CalibratedZDHit.h"
#include "FrameAccess/FAConstants.h"
#include "CLEOConstantsModifiable/CLEOConstantsModifiable.h"
#include "BDLZDclient/DBZDGeomAlignment.hh"
#include "ZDHitCorrectorProd/ZDHitCorrector.h"
#include "AZDGeom/AZDSenseWireStore.h"
#include "DetectorGeometry/DGConstMaterialPtr.h"
#include "FrameIterate/FrameIteratorModuleBase.h"
#include "FrameIterate/FIHolder.h"
#include "qapplication.h"
#include "qtimer.h"
#include "HistogramViewerProc/HVPWindow.h"
#include "ToolBox/HistogramPackage.h"
#include "BDLZDclient/DBAZDGeomLayer.hh"

// forward declarations
class HVPWindow;
class QApplication;

class ZDAlignmentFcn : public MIFcn
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      enum params {kX,
		   kY,
		   kZ,
		   kRotX,
		   kRotY,
		   kRotZ,
		   kT0,
		   kSpeed,
		   kShift,
		   kDelShiftL45,
		   kSagX,
		   kSagY,
		   kTwistWest,

		   kNumParams
      };

      // ---------- Constructors and destructor ----------------
      ZDAlignmentFcn(CLEOConstantsModifiable<DBZDGeomAlignment>* geometry,
		     CLEOConstantsModifiable<DBAZDGeomLayer>* geomlayer);
      virtual ~ZDAlignmentFcn();

      // ---------- member functions ---------------------------

      void book(bool show_plots, bool fake_driftfunction);
      void reset(const FIFrameIterator& frame);
      bool fill(const KTHelix& track,
		const double charge,
		const vector<const CalibratedZDHit*>& hits,
		const vector<double>& drifts);
      double iterate(double* v);

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ZDAlignmentFcn( const ZDAlignmentFcn& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ZDAlignmentFcn& operator=( const ZDAlignmentFcn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      CLEOConstantsModifiable<DBZDGeomAlignment>* m_geometry;
      CLEOConstantsModifiable<DBAZDGeomLayer>* m_geomlayer;

      const FIFrameIterator* m_frame;

      vector<HIHelix*> m_track;
      vector<double> m_charge;
      vector<vector<CalibratedZDHit*>*> m_vect;
      vector<vector<double>*> m_drifts;

      HIHistoManager* m_histman;
      QApplication* m_qapplication;
      HVPWindow* m_hvp_window;

      HIHistProf* m_resid_Vdrift;
      HIHistProf* m_resid_Vlayer;
      HIHistProf* m_resid_Vcotth;
      HIHistProf* m_resid_Vphi_m;
      HIHistProf* m_resid_Vphi_z;
      HIHistProf* m_resid_Vphi_p;
      HIHist1D*   m_resid;

      double m_best_yet;
      bool m_show_plots;
      bool m_fake_driftfunction;

      double m_original_radius[6];

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "ZDAlignmentMod/Template/ZDAlignmentFcn.cc"
//#endif

#endif /* ZDALIGNMENTMOD_ZDALIGNMENTFCN_H */
