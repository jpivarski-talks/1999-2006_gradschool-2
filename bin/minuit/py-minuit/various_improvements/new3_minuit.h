#include <Python.h>
#include "Minuit/FCNBase.h"
#include "Minuit/FCNGradientBase.h"

#include <vector>

bool docall(PyObject *fcn, int npar, const std::vector<double>& par, double &res);
bool docallgrad(PyObject *fcn, int npar, const std::vector<double>& par, std::vector<double> &res);
PyObject* domini(PyObject *self, PyObject *args);
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC init_minuit();

class ExceptionDuringMinimization {
   public:
      ExceptionDuringMinimization() {}
      ~ExceptionDuringMinimization() {}
};

class ExceptionDuringGradient {
   public:
      ExceptionDuringGradient() {}
      ~ExceptionDuringGradient() {}
};

class MyFCN : public FCNBase {
   public:
      MyFCN(PyObject *p_fcn, int npar, double up) : m_p_fcn(p_fcn), m_npar(npar), m_up(up), m_calls(0) {}
      ~MyFCN() {}

      double operator()(const std::vector<double>& par) const {
	 double res;

	 if (docall(m_p_fcn, m_npar, par, res)) {
//	    m_calls++;
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
      int m_calls;
};

class MyGradient : public FCNGradientBase {
   public:
      MyGradient(PyObject *p_fcn, PyObject *p_grad, int npar, double up, bool check) : m_p_fcn(p_fcn), m_p_grad(p_grad), m_npar(npar), m_up(up), m_check(check), m_calls(0), m_gradcalls(0) {}
      ~MyGradient() {}

      double operator()(const std::vector<double>& par) const {
	 double res;

	 if (docall(m_p_fcn, m_npar, par, res)) {
//	    m_calls++;
	    return res;
	 }
	 else {
	    throw ExceptionDuringMinimization();
	 }
      }

      double up() const {return m_up;}

      std::vector<double> gradient(const std::vector<double>& par) const {
	 std::vector<double> res;

	 if (docallgrad(m_p_grad, m_npar, par, res)) {
//	    m_gradcalls++;
	    return res;
	 }
	 else {
	    throw ExceptionDuringGradient();
	 }
      }

      bool checkGradient() const {return m_check;}
      int calls() const {return m_calls;}
      int gradcalls() const {return m_gradcalls;}

   private:
      PyObject *m_p_fcn;
      PyObject *m_p_grad;
      int m_npar;
      double m_up;
      bool m_check;
      int m_calls;
      int m_gradcalls;
};

typedef struct {
      PyObject_HEAD
      FunctionMinimum *m_min;
} minuit_FunctionMinimum;
