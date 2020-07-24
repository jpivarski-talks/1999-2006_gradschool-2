// g++ minuit.cpp -I/nfs/cleo3/Offline/rel/current/other_sources/python/include/python2.4/ -I/cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2 /cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2/src/*.o -shared -o _minuit.so
// g++ minuit.cpp -I/usr/include/python2.3 -I/root/src/Minuit-1_5_2/ /root/src/Minuit-1_5_2/src/*.o -shared -o _minuit.so

#include <Python.h>
#include "Minuit/MnUserParameters.h"
#include "Minuit/MnScan.h"
#include "Minuit/MnSimplex.h"
#include "Minuit/MnMigrad.h"
#include "Minuit/MnMinimize.h"
#include "Minuit/FunctionMinimum.h"
#include "Minuit/MnMinos.h"
#include "Minuit/MnCross.h"
#include "Minuit/MnContours.h"
#include "Minuit/ContoursError.h"
#include "Minuit/MnEigen.h"
#include "Minuit/MnMachinePrecision.h"
#include <vector>
#include "minuit.h"

static PyObject *PyExc_MinuitError;

static int minuit_FunctionMinimum_init(minuit_FunctionMinimum* self, PyObject *args, PyObject *kwds) {
   self->m_min = NULL;
   return 0;
}

static void minuit_FunctionMinimum_dealloc(minuit_FunctionMinimum* self) {
   if (self->m_min != NULL) delete self->m_min;
}

static PyTypeObject minuit_FunctionMinimumType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "_minuit.FunctionMinimum",
   sizeof(minuit_FunctionMinimum),
   0,
   (destructor)minuit_FunctionMinimum_dealloc,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   Py_TPFLAGS_DEFAULT,
   "Minuit state at minimum",
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   (initproc)minuit_FunctionMinimum_init
};

bool docall(PyObject *fcn, int npar, const std::vector<double>& par, double &res)
{
   PyObject *arglist, *result;

   arglist = PyTuple_New(npar);
   if (arglist == NULL) return false;

   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyFloat_FromDouble(par[i]);
      if (obj == NULL  ||  PyTuple_SetItem(arglist, i, obj) != 0) {
	 Py_DECREF(arglist);
	 return false;
      }
   }

   result = PyEval_CallObject(fcn, arglist);
   Py_DECREF(arglist);

   if (result == NULL) return false;  // python function suffered an exception

   if (!PyArg_Parse(result, "d", &res)) {
      PyErr_SetString(PyExc_TypeError, "objective function FCN must return a number");
      Py_DECREF(result);
      return false;
   }

   Py_DECREF(result);
   return true;
}

bool docallgrad(PyObject *fcn, int npar, const std::vector<double>& par, std::vector<double> &res)
{
   PyObject *arglist, *result;

   arglist = PyTuple_New(npar);
   if (arglist == NULL) return false;

   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyFloat_FromDouble(par[i]);
      if (obj == NULL  ||  PyTuple_SetItem(arglist, i, obj) != 0) {
	 Py_DECREF(arglist);
	 return false;
      }
   }

   result = PyEval_CallObject(fcn, arglist);
   Py_DECREF(arglist);

   if (result == NULL) return false;  // python function suffered an exception

   if (!PyTuple_Check(result)  ||  PyTuple_Size(result) != npar) {
      PyErr_SetString(PyExc_TypeError, "gradient function must return a tuple of numbers with length npar");
      Py_DECREF(result);
      return false;
   }

   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyTuple_GetItem(result, i);
      if (obj == NULL) return false;
      if (!PyFloat_Check(obj)  &&  !PyInt_Check(obj)) {
	 PyErr_SetString(PyExc_TypeError, "gradient function must return a tuple of numbers with length npar");
	 return false;
      }
      res.push_back(PyFloat_AsDouble(obj));
   }

   Py_DECREF(result);
   return true;
}

PyObject* domini(PyObject *self, PyObject *args)
{
   // parameter list:
   PyObject *p_fcn;                   // objective function p_fcn
   int npar;                          // number of parameters in p_fcn
   double up;                         // 1 for chi^2, 0.5 for loglike
   PyObject *p_name;                  // names of the parameters 
   std::vector<const char*> name;
   PyObject *p_start;                 // starting values of the parameters
   std::vector<double> start;
   PyObject *p_step;                  // initial step size of the parameters
   std::vector<double> step;
   PyObject *p_fixed;                 // which parameters are to be held fixed
   std::vector<bool> fixed;
   PyObject *p_limits;                // limits on parameters
   std::vector<bool> has_lowlimit;
   std::vector<double> lowlimit;
   std::vector<bool> has_highlimit;
   std::vector<double> highlimit;
   double eps;                        // epsilon (== machine precision if non-positive)
   int maxcalls;                      // maximum number of calls (unlimited if non-positive)
   double tol;                        // tolerence (default if non-positive)
   int strategy;                      // strategy 0,1,2 == fast through thorough
   PyObject *p_covariance;            // covariance matrix or None
   bool has_covariance;
   std::vector< std::vector<double> > covariance;
   int minimizer;                     // which minimizer? 0,1,2,3 = scan, simplex, migrad, minimize
   PyObject *p_grad;                  // gradient of objective function (or None)
   PyObject *p_checkgrad;             // if False, skip the gradient check

   if (!PyArg_ParseTuple(args, "OidOOOOOdidiOiOO", &p_fcn, &npar, &up, &p_name, &p_start, &p_step, &p_fixed, &p_limits, &eps, &maxcalls, &tol, &strategy, &p_covariance, &minimizer, &p_grad, &p_checkgrad)) {
      PyErr_SetString(PyExc_TypeError, "calling format must be: FCN(f), npar(i), up(f), names(l of s), start(l), step(l), fixed(l of b), limits(l), eps(f or 0), maxcalls(i or 0), tol(f or 0), strategy(i), covariance(l or None), minimizer(i), gradient(f or None), checkgrad(b or None)");
      return NULL;
   }

   if (!PyCallable_Check(p_fcn)) {
      PyErr_SetString(PyExc_TypeError, "objective function FCN must be callable");
      return NULL;
   }

   if (PyList_Size(p_name) != npar) {
      PyErr_SetString(PyExc_TypeError, "list name must have length npar");
      return NULL;
   }
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyList_GetItem(p_name, i);
      if (obj == NULL) return NULL;
      if (!PyString_Check(obj)) {
	 PyErr_SetString(PyExc_TypeError, "names must be strings");
	 return NULL;
      }
      name.push_back(PyString_AsString(obj));
   }

   if (PyList_Size(p_start) != npar) {
      PyErr_SetString(PyExc_TypeError, "list start must have length npar");
      return NULL;
   }
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyList_GetItem(p_start, i);
      if (obj == NULL) return NULL;
      if (!PyFloat_Check(obj)  &&  !PyInt_Check(obj)) {
	 PyErr_SetString(PyExc_TypeError, "starts must be numbers");
	 return NULL;
      }
      start.push_back(PyFloat_AsDouble(obj));
   }

   if (PyList_Size(p_step) != npar) {
      PyErr_SetString(PyExc_TypeError, "list step must have length npar");
      return NULL;
   }
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyList_GetItem(p_step, i);
      if (obj == NULL) return NULL;
      if (!PyFloat_Check(obj)  &&  !PyInt_Check(obj)) {
	 PyErr_SetString(PyExc_TypeError, "steps must be numbers");
	 return NULL;
      }
      step.push_back(PyFloat_AsDouble(obj));
   }

   if (p_fixed == Py_None) {
      for (int i = 0;  i < npar;  i++) fixed.push_back(false);
   }
   else if (PyList_Size(p_fixed) != npar) {
      PyErr_SetString(PyExc_TypeError, "list fixed must have length npar");
      return NULL;
   }
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyList_GetItem(p_fixed, i);
      if (obj == NULL) return NULL;
      if (obj == Py_True) fixed.push_back(true);
      else if (obj == Py_False) fixed.push_back(false);
      else {
	 PyErr_SetString(PyExc_TypeError, "fixeds must be booleans");
	 return NULL;
      }
   }

   if (p_limits == Py_None) {
      for (int i = 0;  i < npar;  i++) {
	 has_lowlimit.push_back(false);
	 lowlimit.push_back(0.);
	 has_highlimit.push_back(false);
	 highlimit.push_back(0.);
      }
   }
   else if (PyList_Check(p_limits)  &&  PyList_Size(p_limits) == npar) {
      for (int i = 0;  i < npar;  i++) {
	 PyObject *obj = PyList_GetItem(p_limits, i);
	 if (obj == NULL) return NULL;
	 if (obj == Py_None) {
	    has_lowlimit.push_back(false);
	    lowlimit.push_back(0.);
	    has_highlimit.push_back(false);
	    highlimit.push_back(0.);
	 }
	 else if (!PyList_Check(obj)  ||  PyList_Size(obj) != 2) {
	    PyErr_SetString(PyExc_TypeError, "limits must be None or [number, number] or [number, None] or [None, number] for each parameter");
	    return NULL;
	 }
	 else {
	    PyObject *p_low = PyList_GetItem(obj, 0);
	    PyObject *p_high = PyList_GetItem(obj, 1);

	    if (p_low == Py_None) {
	       has_lowlimit.push_back(false);
	       lowlimit.push_back(0.);
	    }
	    else if (PyInt_Check(p_low)  ||  PyFloat_Check(p_low)) {
	       has_lowlimit.push_back(true);
	       lowlimit.push_back(PyFloat_AsDouble(p_low));
	    }
	    else {
	       PyErr_SetString(PyExc_TypeError, "limits must be None or [number, number] or [number, None] or [None, number] for each parameter");
	       return NULL;
	    }

	    if (p_high == Py_None) {
	       has_highlimit.push_back(false);
	       highlimit.push_back(0.);
	    }
	    else if (PyInt_Check(p_high)  ||  PyFloat_Check(p_high)) {
	       has_highlimit.push_back(true);
	       highlimit.push_back(PyFloat_AsDouble(p_high));
	    }
	    else {
	       PyErr_SetString(PyExc_TypeError, "limits must be None or [number, number] or [number, None] or [None, number] for each parameter");
	       return NULL;
	    }
	 }
      }
   }
   else {
      PyErr_SetString(PyExc_TypeError, "limits must be None or [number, number] or [number, None] or [None, number] for each parameter");
      return NULL;
   }

   if (p_covariance == Py_None) {
      has_covariance = false;
   }
   else if (PyList_Check(p_covariance)  &&  PyList_Size(p_covariance) == npar) {
      has_covariance = true;

      for (int i = 0;  i < npar;  i++) {
	 PyObject *p_row = PyList_GetItem(p_covariance, i);
	 std::vector<double> row;

	 if (PyList_Check(p_row)  &&  PyList_Size(p_row) == npar) {
	    for (int j = 0;  j < npar;  j++) {
	       PyObject *p_elem = PyList_GetItem(p_row, j);

	       if (PyInt_Check(p_elem)  ||  PyFloat_Check(p_elem)) {
		  row.push_back(PyFloat_AsDouble(p_elem));
	       }
	       else {
		  PyErr_SetString(PyExc_TypeError, "covariance must be None or a npar by npar matrix (list of lists)");
		  return NULL;
	       }
	    }
	    covariance.push_back(row);
	 }
	 else {
	    PyErr_SetString(PyExc_TypeError, "covariance must be None or a npar by npar matrix (list of lists)");
	    return NULL;
	 }
      }

      for (int i = 0;  i < npar;  i++) {
	 for (int j = i+1;  j < npar;  j++) {
	    if (covariance[i][j] != covariance[j][i]) {
	       PyErr_SetString(PyExc_TypeError, "covariance matrix must be symmetric");
	       return NULL;
	    }}}
   }
   else {
      PyErr_SetString(PyExc_TypeError, "covariance must be None or a npar by npar matrix (list of lists)");
      return NULL;
   }

   if (p_grad != Py_None  &&  !PyCallable_Check(p_grad)) {
      PyErr_SetString(PyExc_TypeError, "gradient of FCN must be callable or None");
      return NULL;
   }

   if (p_checkgrad != Py_None  &&  p_checkgrad != Py_True  &&  p_checkgrad != Py_False) {
      PyErr_SetString(PyExc_TypeError, "checkgrad must be True, False, or None");
      return NULL;
   }

   ////////////////////////////////////////// ready to pass to minuit!

   MnUserParameters upar;
   for (int i = 0;  i < npar;  i++) {
      upar.add(name[i], start[i], step[i]);
   }
   for (int i = 0;  i < npar;  i++) {
      if (fixed[i]) upar.fix(i);
      if (has_lowlimit[i]) upar.setLowerLimit(i, lowlimit[i]);
      if (has_highlimit[i]) upar.setUpperLimit(i, highlimit[i]);
   }

   MyFCN fcn(p_fcn, npar, up);
   bool checkgrad = true;
   if (p_checkgrad == Py_False) checkgrad = false;
   MyGradient grad(p_fcn, p_grad, npar, up, checkgrad);

   MnApplication *mnapp = NULL;
   std::vector<double> cov;
   if (has_covariance) {
      for (int i = 0;  i < npar;  i++) {
	 for (int j = i;  j < npar;  j++) {
	    cov.push_back(covariance[i][j]);
	 }
      }
   }   

   // scan minimization
   if (minimizer == 0) {
      if (has_covariance) {
	 mnapp = new MnScan(fcn, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
      }
      else {
	 mnapp = new MnScan(fcn, upar, strategy);
      }
   }

   // simplex minimization
   else if (minimizer == 1) {
      if (has_covariance) {
	 mnapp = new MnSimplex(fcn, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
      }
      else {
	 mnapp = new MnSimplex(fcn, upar, strategy);
      }
   }

   // migrad minimization
   else if (minimizer == 2) {
      if (has_covariance) {
	 if (p_grad == Py_None) {
	    mnapp = new MnMigrad(fcn, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
	 }
	 else {
	    mnapp = new MnMigrad(grad, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
	 }
      }
      else {
	 if (p_grad == Py_None) {
	    mnapp = new MnMigrad(fcn, upar, strategy);
	 }
	 else {
	    mnapp = new MnMigrad(grad, upar, strategy);
	 }
      }
   }

   // minimum minimization
   else if (minimizer == 3) {
      if (has_covariance) {
	 if (p_grad == Py_None) {
	    mnapp = new MnMinimize(fcn, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
	 }
	 else {
	    mnapp = new MnMinimize(grad, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
	 }
      }
      else {
	 if (p_grad == Py_None) {
	    mnapp = new MnMinimize(fcn, upar, strategy);
	 }
	 else {
	    mnapp = new MnMinimize(grad, upar, strategy);
	 }
      }
   }

   // error
   else {
      PyErr_SetString(PyExc_TypeError, "minimizer can only be 0,1,2,3 (== scan, simplex, migrad, minimize)");
      delete mnapp;
      return NULL;
   }

   if (maxcalls <= 0) maxcalls = 0;
   if (tol <= 0.) tol = 0.1;
   if (eps > 0.) mnapp->setPrecision(eps);

   PyObject *p_min = _PyObject_New(&minuit_FunctionMinimumType);
   try {
      try {
	 ((minuit_FunctionMinimum*) p_min)->m_min = new FunctionMinimum((*mnapp)(maxcalls, tol));
      }
      catch (ExceptionDuringGradient theException) {
	 // Python exception during gradient evaluation
	 _PyObject_Del(p_min);
	 delete mnapp;
	 return NULL;
      }
   }
   catch (ExceptionDuringMinimization theException) {
      // Python exception during Minuit minimization
      _PyObject_Del(p_min);
      delete mnapp;
      return NULL;
   }

   FunctionMinimum* min = ((minuit_FunctionMinimum*) p_min)->m_min;

   PyObject *p_valid = Py_True;
   if (!min->isValid()) p_valid = Py_False;
   PyObject *p_abovemaxedm = Py_True;
   if (!min->isAboveMaxEdm()) p_abovemaxedm = Py_False;
   PyObject *p_reachedcalllimit = Py_True;
   if (!min->hasReachedCallLimit()) p_reachedcalllimit = Py_False;
   double fval = min->fval();
   double edm = min->edm();
   int ncalls = min->nfcn();
//    int ncalls = fcn.calls();
//    int ngradcalls = 0;
//    if (p_grad != Py_None) {
//       ncalls = grad.calls();
//       ngradcalls = grad.gradcalls();
//    }

   PyObject *p_values;
   if (min->hasValidParameters()) {
      p_values = PyList_New(npar);
      MnUserParameters new_parameters = min->userParameters();
      if (p_values == NULL) return NULL;
      for (int i = 0;  i < npar;  i++) {
	 PyObject *obj = PyFloat_FromDouble(new_parameters.value(i));
	 if (obj == NULL  ||  PyList_SetItem(p_values, i, obj) != 0) {
	    Py_DECREF(p_values);
	    return NULL;
	 }
      }
   }
   else {
      p_values = Py_None;
   }

   PyObject *p_new_covariance;
   if (min->hasValidCovariance()  &&  min->hasAccurateCovar()  &&  min->hasPosDefCovar()) {
      MnUserCovariance new_covariance = min->userCovariance();
      p_new_covariance = PyList_New(npar);
      if (p_new_covariance == NULL) return NULL;
      for (int i = 0;  i < npar;  i++) {
	 PyObject *p_row = PyList_New(npar);
	 if (p_row == NULL) {
	    Py_DECREF(p_new_covariance);
	    return NULL;
	 }
	 for (int j = 0;  j < npar;  j++) {
	    PyObject *p_elem = PyFloat_FromDouble(new_covariance(i,j));
	    if (p_elem == NULL  ||  PyList_SetItem(p_row, j, p_elem) != 0) {
	       Py_DECREF(p_row);
	       Py_DECREF(p_new_covariance);
	       return NULL;
	    }
	 }
	 if (PyList_SetItem(p_new_covariance, i, p_row) != 0) {
	    Py_DECREF(p_row);
	    Py_DECREF(p_new_covariance);
	    return NULL;
	 }
      }
   }
   else {
      p_new_covariance = Py_None;
   }

   delete mnapp;

   PyObject *output = Py_BuildValue("(OOOddiOOO)", p_valid, p_abovemaxedm, p_reachedcalllimit, fval, edm, ncalls, p_values, p_new_covariance, p_min);
   if (p_values != Py_None) { Py_DECREF(p_values); }
   if (p_new_covariance != Py_None) { Py_DECREF(p_new_covariance); }
   Py_DECREF(p_min);
   return output;

// Testing code
////////////////////////////////////////////////////////
//    printf("%d %g\n", npar, up);
//    for (int i = 0;  i < npar;  i++) {
//       printf("%d %5s %5g %5g %s ", i, name[i], start[i], step[i], (fixed[i] ? "fixed" : "free"));
//       if (has_lowlimit[i]) printf("%g ", lowlimit[i]);
//       else printf("None ");
//       if (has_highlimit[i]) printf("%g ", highlimit[i]);
//       else printf("None ");
//       printf("\n");
//    }
//    if (has_covariance) {
//       for (int i = 0;  i < npar;  i++) {
// 	 for (int j = 0;  j < npar;  j++) {
// 	    printf("%3g ", covariance[i][j]);
// 	 }
// 	 printf("\n");
//       }
//    }

//    double res = -1000.;
//    std::vector<double> par;
//    for (int i = 0;  i < npar;  i++) par.push_back(double(i));
//    if (!docall(fcn, npar, par, res)) return NULL;  // if calling function results in an exception, pass it on...
}

PyObject* dominos(PyObject *self, PyObject *args)
{
   // parameter list:
   PyObject *p_fcn;                   // objective function p_fcn
   int npar;                          // number of parameters in p_fcn
   double up;                         // 1 for chi^2, 0.5 for loglike
   PyObject *p_min;                   // the minimum you previously found
   int maxcalls;                      // maximum number of calls (unlimited if non-positive)
   int strategy;                      // strategy 0,1,2 == fast through thorough
   PyObject *p_dolower;               // calculate lower MINOS error
   PyObject *p_doupper;               // calculate upper MINOS error
   int parnum;                        // parameter number
   PyObject *p_grad;                  // gradient of objective function (or None)
   PyObject *p_checkgrad;             // if False, skip the gradient check

   if (!PyArg_ParseTuple(args, "OidOiiOOiOO", &p_fcn, &npar, &up, &p_min, &maxcalls, &strategy, &p_dolower, &p_doupper, &parnum, &p_grad, &p_checkgrad)) {
      PyErr_SetString(PyExc_TypeError, "calling format must be: FCN(f), npar(i), up(f), minimum(FunctionMinimum), maxcalls(i or 0), strategy(i), dolower(b), doupper(b), parnum(i), gradient(f or None), checkgrad(b or None)");
      return NULL;
   }

   if (!PyCallable_Check(p_fcn)) {
      PyErr_SetString(PyExc_TypeError, "objective function FCN must be callable");
      return NULL;
   }

   if (!PyObject_TypeCheck(p_min, &minuit_FunctionMinimumType)) {
      PyErr_SetString(PyExc_TypeError, "min must be a FunctionMinimum object, generated by a minimization");
      return NULL;
   }

   FunctionMinimum* min = ((minuit_FunctionMinimum*) p_min)->m_min;
   if (min == NULL) {
      PyErr_SetString(PyExc_TypeError, "min must be a FunctionMinimum object, generated by a minimization");
      return NULL;
   }
   
   if (!min->isValid()) {
      PyErr_SetString(PyExc_MinuitError, "Cannot run MINOS: the minimization was not valid.");
      return NULL;
   }

   if (p_dolower != Py_True  &&  p_dolower != Py_False) {
      PyErr_SetString(PyExc_TypeError, "dolower must be boolean");
      return NULL;
   }

   if (p_doupper != Py_True  &&  p_doupper != Py_False) {
      PyErr_SetString(PyExc_TypeError, "doupper must be boolean");
      return NULL;
   }

   if (parnum < 0  ||  parnum >= npar) {
      PyErr_SetString(PyExc_TypeError, "parameter number must be in (0..npar)");
      return NULL;
   }

   if (p_grad != Py_None  &&  !PyCallable_Check(p_grad)) {
      PyErr_SetString(PyExc_TypeError, "gradient of FCN must be callable or None");
      return NULL;
   }

   if (p_checkgrad != Py_None  &&  p_checkgrad != Py_True  &&  p_checkgrad != Py_False) {
      PyErr_SetString(PyExc_TypeError, "checkgrad must be True, False, or None");
      return NULL;
   }

   ////////////////////////////////////// ready to pass to minos

   MyFCN fcn(p_fcn, npar, up);
   bool checkgrad = true;
   if (p_checkgrad == Py_False) checkgrad = false;
   MyGradient grad(p_fcn, p_grad, npar, up, checkgrad);

   MnMinos *minos;
   if (p_grad == Py_None) {
      minos = new MnMinos(fcn, *min, MnStrategy(strategy));
   }
   else {
      minos = new MnMinos(grad, *min, MnStrategy(strategy));
   }
   
   if (maxcalls <= 0) maxcalls = 0;
   PyObject *p_lower = Py_None;
   PyObject *p_upper = Py_None;
   PyObject *p_lowervalid = Py_None;
   PyObject *p_uppervalid = Py_None;
   int ncalls = 0;

   if (p_dolower == Py_True) {
      MnCross crossing = minos->loval(parnum, maxcalls);
      if (crossing.isValid()) {
	 p_lower = Py_BuildValue(
	    "d", -1.*crossing.state().error(parnum)*(1. + crossing.value()));
      }
      ncalls += crossing.nfcn();
      PyObject *p_valid, *p_atlimit, *p_atmaxfcn, *p_newmin;
      if (crossing.isValid()) p_valid = Py_True; else p_valid = Py_False;
      if (crossing.atLimit()) p_atlimit = Py_True; else p_atlimit = Py_False;
      if (crossing.atMaxFcn()) p_atmaxfcn = Py_True; else p_atmaxfcn = Py_False;
      if (crossing.newMinimum()) p_newmin = Py_True; else p_newmin = Py_False;
      p_lowervalid = Py_BuildValue("(OOOO)", p_valid, p_atlimit, p_atmaxfcn, p_newmin);
   }

   if (p_doupper == Py_True) {
      MnCross crossing = minos->upval(parnum, maxcalls);
      if (crossing.isValid()) {
	 p_upper = Py_BuildValue(
	    "d", crossing.state().error(parnum)*(1. + crossing.value()));
      }
      ncalls += crossing.nfcn();
      PyObject *p_valid, *p_atlimit, *p_atmaxfcn, *p_newmin;
      if (crossing.isValid()) p_valid = Py_True; else p_valid = Py_False;
      if (crossing.atLimit()) p_atlimit = Py_True; else p_atlimit = Py_False;
      if (crossing.atMaxFcn()) p_atmaxfcn = Py_True; else p_atmaxfcn = Py_False;
      if (crossing.newMinimum()) p_newmin = Py_True; else p_newmin = Py_False;
      p_uppervalid = Py_BuildValue("(OOOO)", p_valid, p_atlimit, p_atmaxfcn, p_newmin);
   }

   delete minos;
   PyObject *output = Py_BuildValue("((OO)(OO)i)", p_lower, p_upper, p_lowervalid, p_uppervalid, ncalls);
   if (p_lower != Py_None) { Py_DECREF(p_lower); }
   if (p_upper != Py_None) { Py_DECREF(p_upper); }
   if (p_lowervalid != Py_None) { Py_DECREF(p_lowervalid); }
   if (p_uppervalid != Py_None) { Py_DECREF(p_uppervalid); }
   return output;
}

PyObject* docontours(PyObject *self, PyObject *args)
{
   // parameter list:
   PyObject *p_fcn;                   // objective function p_fcn
   int npar;                          // number of parameters in p_fcn
   double up;                         // 1 for chi^2, 0.5 for loglike
   PyObject *p_min;                   // the minimum you previously found
   int maxcalls;                      // maximum number of calls (unlimited if non-positive)
   int strategy;                      // strategy 0,1,2 == fast through thorough
   int parx;                          // "x" parameter number
   int pary;                          // "x" parameter number
   int npoints;                       // number of points (default is 20)
   PyObject *p_grad;                  // gradient of objective function (or None)
   PyObject *p_checkgrad;             // if False, skip the gradient check

   if (!PyArg_ParseTuple(args, "OidOiiiiiOO", &p_fcn, &npar, &up, &p_min, &maxcalls, &strategy, &parx, &pary, &npoints, &p_grad, &p_checkgrad)) {
      PyErr_SetString(PyExc_TypeError, "calling format must be: FCN(f), npar(i), up(f), minimum(FunctionMinimum), maxcalls(i or 0), strategy(i), parx(i), pary(i), npoints(i), gradient(f or None), checkgrad(b or None)");
      return NULL;
   }

   if (!PyCallable_Check(p_fcn)) {
      PyErr_SetString(PyExc_TypeError, "objective function FCN must be callable");
      return NULL;
   }

   if (!PyObject_TypeCheck(p_min, &minuit_FunctionMinimumType)) {
      PyErr_SetString(PyExc_TypeError, "min must be a FunctionMinimum object, generated by a minimization");
      return NULL;
   }

   FunctionMinimum* min = ((minuit_FunctionMinimum*) p_min)->m_min;
   if (min == NULL) {
      PyErr_SetString(PyExc_TypeError, "min must be a FunctionMinimum object, generated by a minimization");
      return NULL;
   }
   
   if (!min->isValid()) {
      PyErr_SetString(PyExc_MinuitError, "Cannot run CONTOURS: the minimization was not valid.");
      return NULL;
   }

   if (parx < 0  ||  parx >= npar) {
      PyErr_SetString(PyExc_TypeError, "x parameter number must be in (0..npar)");
      return NULL;
   }

   if (pary < 0  ||  pary >= npar) {
      PyErr_SetString(PyExc_TypeError, "y parameter number must be in (0..npar)");
      return NULL;
   }

   if (p_grad != Py_None  &&  !PyCallable_Check(p_grad)) {
      PyErr_SetString(PyExc_TypeError, "gradient of FCN must be callable or None");
      return NULL;
   }

   if (p_checkgrad != Py_None  &&  p_checkgrad != Py_True  &&  p_checkgrad != Py_False) {
      PyErr_SetString(PyExc_TypeError, "checkgrad must be True, False, or None");
      return NULL;
   }

   ////////////////////////////////////// ready to pass to contours

   MyFCN fcn(p_fcn, npar, up);
   bool checkgrad = true;
   if (p_checkgrad == Py_False) checkgrad = false;
   MyGradient grad(p_fcn, p_grad, npar, up, checkgrad);

   MnContours *contours;
   if (p_grad == Py_None) {
      contours = new MnContours(fcn, *min, MnStrategy(strategy));
   }
   else {
      contours = new MnContours(grad, *min, MnStrategy(strategy));
   }
   
   if (maxcalls <= 0) maxcalls = 0;
   if (npoints <= 0) npoints = 20;

   ContoursError c = contours->contour(parx, pary, npoints);
   std::pair<double,double> xerr = c.xMinos();
   std::pair<double,double> yerr = c.yMinos();
   int ncalls = c.nfcn();
   const std::vector<std::pair<double,double> > cont = c();

   PyObject *p_cont = PyList_New(npoints);
   if (p_cont == NULL) return NULL;
   for (int i = 0;  i < cont.size();  i++) {
      PyObject *obj0 = PyList_New(2);
      if (obj0 == NULL) {Py_DECREF(p_cont); return NULL;}
      PyObject *obj1 = PyFloat_FromDouble(cont[i].first);
      if (obj1 == NULL) {Py_DECREF(p_cont); return NULL;}
      PyObject *obj2 = PyFloat_FromDouble(cont[i].second);
      if (obj2 == NULL) {Py_DECREF(p_cont); return NULL;}

      if (PyList_SetItem(obj0, 0, obj1) != 0) {Py_DECREF(p_cont); return NULL;}
      if (PyList_SetItem(obj0, 1, obj2) != 0) {Py_DECREF(p_cont); return NULL;}
      if (PyList_SetItem(p_cont, i, obj0) != 0) {Py_DECREF(p_cont); return NULL;}
   }

   delete contours;
   PyObject *output = Py_BuildValue("(O(dd)(dd)i)", p_cont, xerr.first, xerr.second, yerr.first, yerr.second, ncalls);
   Py_DECREF(p_cont);
   return output;
}

PyObject* calceigen(PyObject *self, PyObject *args)
{
   // parameter list:
   PyObject *p_covariance;
   std::vector<std::vector<double> > covariance;
   int npar;

   if (!PyArg_ParseTuple(args, "Oi", &p_covariance, &npar)) {
      PyErr_SetString(PyExc_TypeError, "calling format must be: covariance(l), npar(i)");
      return NULL;
   }

   if (PyList_Check(p_covariance)  &&  PyList_Size(p_covariance) == npar) {
      for (int i = 0;  i < npar;  i++) {
	 PyObject *p_row = PyList_GetItem(p_covariance, i);
	 std::vector<double> row;

	 if (PyList_Check(p_row)  &&  PyList_Size(p_row) == npar) {
	    for (int j = 0;  j < npar;  j++) {
	       PyObject *p_elem = PyList_GetItem(p_row, j);

	       if (PyInt_Check(p_elem)  ||  PyFloat_Check(p_elem)) {
		  row.push_back(PyFloat_AsDouble(p_elem));
	       }
	       else {
		  PyErr_SetString(PyExc_TypeError, "covariance must be a npar by npar matrix (list of lists)");
		  return NULL;
	       }
	    }
	    covariance.push_back(row);
	 }
	 else {
	    PyErr_SetString(PyExc_TypeError, "covariance must be a npar by npar matrix (list of lists)");
	    return NULL;
	 }
      }

      for (int i = 0;  i < npar;  i++) {
	 for (int j = i+1;  j < npar;  j++) {
	    if (covariance[i][j] != covariance[j][i]) {
	       PyErr_SetString(PyExc_TypeError, "covariance matrix must be symmetric");
	       return NULL;
	    }}}
   }
   else {
      PyErr_SetString(PyExc_TypeError, "covariance must be a npar by npar matrix (list of lists)");
      return NULL;
   }

   std::vector<double> cov;
   for (int i = 0;  i < npar;  i++) {
      for (int j = i;  j < npar;  j++) {
	 cov.push_back(covariance[i][j]);
      }
   }

   MnEigen eigen;
   std::vector<double> v = eigen(MnUserCovariance(cov, npar));

   PyObject *p_eigen = PyList_New(npar);
   if (p_eigen == NULL) return NULL;
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyFloat_FromDouble(v[i]);
      if (obj == NULL  ||  PyList_SetItem(p_eigen, i, obj) != 0) {
	 Py_DECREF(p_eigen);
	 return NULL;
      }
   }

   PyObject *output = Py_BuildValue("O", p_eigen);
   Py_DECREF(p_eigen);
   return output;
}

PyObject* machineprecision(PyObject *self, PyObject *args)
{
   MnMachinePrecision mp;
   return Py_BuildValue("d", mp.eps());
}

static PyMethodDef MinuitMethods[] = {
   {"domini", domini, METH_VARARGS, "Pass a lot of variables, do a minimization, and the pass a lot of results back."},
   {"dominos", dominos, METH_VARARGS, "Pass the function and minimum, get back upper and/or lower errors for a given parameter."},
   {"docontours", docontours, METH_VARARGS, "Pass the function and minimum, get back contours for two given parameters."},
   {"calceigen", calceigen, METH_VARARGS, "Calculate eigenvalues of a given covariance matrix."},
   {"machineprecision", machineprecision, METH_VARARGS, "Output this computer's machine precision."},
   {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_minuit()
{
   PyObject *m;

   minuit_FunctionMinimumType.tp_new = PyType_GenericNew;
   if (PyType_Ready(&minuit_FunctionMinimumType) < 0) return;

   m = Py_InitModule3("_minuit", MinuitMethods, "Minuit function minimization from CERN");

   Py_INCREF(&minuit_FunctionMinimumType);
   PyModule_AddObject(m, "FunctionMinimum", (PyObject*)&minuit_FunctionMinimumType);

   PyExc_MinuitError = PyErr_NewException("_minuit.MinuitError", NULL, NULL);
   if (PyExc_MinuitError == NULL) return;
   Py_INCREF(PyExc_MinuitError);
   PyModule_AddObject(m, "MinuitError", PyExc_MinuitError);
}
