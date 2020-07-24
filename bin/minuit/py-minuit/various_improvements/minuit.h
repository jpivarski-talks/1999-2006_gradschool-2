#include <Python.h>
#include "Minuit/FCNBase.h"

#include <vector>

bool docall(PyObject *fcn, int npar, const std::vector<double>& par, double &res);
PyObject* domini(PyObject *self, PyObject *args);
PyMODINIT_FUNC init_minuit();

class ExceptionDuringMinimization {
   public:
      ExceptionDuringMinimization() {}
      ~ExceptionDuringMinimization() {}
};

class MyFCN : public FCNBase {
   public:
      MyFCN(PyObject *p_fcn, int npar, double up) : m_p_fcn(p_fcn), m_npar(npar), m_up(up) {}
      ~MyFCN() {}

      double operator()(const std::vector<double>& par) const {
	 double res;
	 if (docall(m_p_fcn, m_npar, par, res)) {
	    return res;
	 }
	 else {
	    throw ExceptionDuringMinimization();
	 }
      }

      double up() const {return m_up;}

   private:
      PyObject *m_p_fcn;
      int m_npar;
      double m_up;
};
