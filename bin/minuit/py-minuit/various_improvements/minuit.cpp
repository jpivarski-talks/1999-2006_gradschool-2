// g++ minuit.cpp -I/nfs/cleo3/Offline/rel/current/other_sources/python/include/python2.4/ -I/cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2 /cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2/src/*.o -shared -o _minuit.so
// g++ minuit.cpp -I/usr/include/python2.3 -I/root/src/Minuit-1_5_2/ /root/src/Minuit-1_5_2/src/*.o -shared -o _minuit.so

#include <Python.h>
#include "Minuit/MnUserParameters.h"
#include "Minuit/MnMigrad.h"
#include "Minuit/FunctionMinimum.h"
#include <vector>
#include "minuit.h"

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
   int minimizer;                     // which minimizer? 0,1,2 = simplex, migrad, minimize

   if (!PyArg_ParseTuple(args, "OidOOOOOdidiOi", &p_fcn, &npar, &up, &p_name, &p_start, &p_step, &p_fixed, &p_limits, &eps, &maxcalls, &tol, &strategy, &p_covariance, &minimizer)) {
      PyErr_SetString(PyExc_TypeError, "calling format must be: FCN, npar(i), up(f), names(l), start(l), step(l), fixed(l), limits(l), eps(f), maxcalls(i), tol(f), strategy(i), covariance(l), minimizer(i)");
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

   if (PyList_Size(p_fixed) != npar) {
      PyErr_SetString(PyExc_TypeError, "list fixed must have length npar");
      return NULL;
   }
   for (int i = 0;  i < npar;  i++) {
      PyObject *obj = PyList_GetItem(p_fixed, i);
      if (obj == NULL) return NULL;
      if (!PyBool_Check(obj)) {
	 PyErr_SetString(PyExc_TypeError, "fixeds must be booleans");
	 return NULL;
      }
      if (PyInt_AsLong(obj)) fixed.push_back(true);
      else fixed.push_back(false);
   }

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
	 PyErr_SetString(PyExc_TypeError, "limits must be None or (number, number) or (number, None) or (None, number)");
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
	    PyErr_SetString(PyExc_TypeError, "limits must be None or (number, number) or (number, None) or (None, number)");
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
	    PyErr_SetString(PyExc_TypeError, "limits must be None or (number, number) or (number, None) or (None, number)");
	    return NULL;
	 }
      }
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

   // simplex minimization
   if (minimizer == 0) {

   }

   // migrad minimization
   else if (minimizer == 1) {
      MnMigrad* migrad = NULL;
      if (has_covariance) {
	 std::vector<double> cov;
	 for (int i = 0;  i < npar;  i++) {
	    for (int j = i;  j < npar;  j++) {
	       cov.push_back(covariance[i][j]);
	    }
	 }
	 migrad = new MnMigrad(fcn, MnUserParameterState(upar, MnUserCovariance(cov, npar)), MnStrategy(strategy));
      }
      else { // no covariance
	 migrad = new MnMigrad(fcn, upar, strategy);
      }

      if (maxcalls <= 0) maxcalls = 0;
      if (tol <= 0.) tol = 0.1;
      if (eps > 0.) migrad->setPrecision(eps);

      FunctionMinimum *min = NULL;
      try {
	 min = new FunctionMinimum((*migrad)(maxcalls, tol));
      }
      catch (ExceptionDuringMinimization theException) {
	 // Python exception during Minuit minimization
	 delete min;
	 delete migrad;
	 return NULL;
      }

      PyObject *p_valid = Py_True;
      if (!min->isValid()) p_valid = Py_False;
      double fval = min->fval();
      double edm = min->edm();
      int ncalls = min->nfcn();

      MnUserParameters new_parameters = min->userParameters();
      PyObject *p_values = PyList_New(npar);
      if (p_values == NULL) return NULL;
      for (int i = 0;  i < npar;  i++) {
	 PyObject *obj = PyFloat_FromDouble(new_parameters.value(i));
	 if (obj == NULL  ||  PyList_SetItem(p_values, i, obj) != 0) {
	    Py_DECREF(p_values);
	    return NULL;
	 }
      }

      MnUserCovariance new_covariance = min->userCovariance();
      PyObject *p_new_covariance = PyList_New(npar);
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

      delete min;
      delete migrad;

      PyObject *output = Py_BuildValue("(OddiOO)", p_valid, fval, edm, ncalls, p_values, p_new_covariance);
      Py_DECREF(p_values);
      Py_DECREF(p_new_covariance);
      return output;
   }

   // minimum minimization
   else if (minimizer == 2) {

   }

   // error
   else {
      PyErr_SetString(PyExc_TypeError, "minimizer can only be 0,1,2 (== simplex, migrad, minimize)");
      return NULL;
   }

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

static PyMethodDef MinuitMethods[] = {
   {"domini", domini, METH_VARARGS, "Pass a lot of variables, do a minimization, and the pass a lot of results back."},
   {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_minuit()
{
   (void) Py_InitModule("_minuit", MinuitMethods);
}
