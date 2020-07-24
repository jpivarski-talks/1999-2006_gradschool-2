// g++ minuit.cpp -I/nfs/cleo3/Offline/rel/current/other_sources/python/include/python2.4/ -I/cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2 /cdat/daf9/mccann/software/src/minuit/Minuit-1_5_2/src/*.o -shared -o _minuit.so

#include <Python.h>
#include <vector>
// #include "Minuit/FunctionMinimum.h"
// #include "Minuit/MnMigrad.h"
// #include "Minuit/MnUserParameters.h"

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
   PyObject *fcn;                     // objective function fcn
   int npar;                          // number of parameters in fcn
   double up;                         // 1 for chi^2, 0.5 for loglike
   PyObject *p_name;
   std::vector<const char*> name;     // names of the parameters
   PyObject *p_start;
   std::vector<double> start;         // starting values of the parameters
   PyObject *p_step;
   std::vector<double> step;          // initial step size of the parameters
   PyObject *p_fixed;
   std::vector<double> fixed;         // which parameters are to be held fixed

   if (!PyArg_ParseTuple(args, "OidOOOO", &fcn, &npar, &up, &p_name, &p_start, &p_step, &p_fixed))
      return NULL;

   if (!PyCallable_Check(fcn)) {
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

   printf("%d %g\n", npar, up);
   for (int i = 0;  i < npar;  i++) {
      printf("%d %5s %5g %5g %s\n", i, name[i], start[i], step[i], (fixed[i] ? "fixed" : "free"));
   }

//    double res = -1000.;
//    std::vector<double> par;
//    for (int i = 0;  i < npar;  i++) par.push_back(double(i));
//    if (!docall(fcn, npar, par, res)) return NULL;  // if calling function results in an exception, pass it on...
 
   return Py_BuildValue("d", 0.);
}

static PyMethodDef MinuitMethods[] = {
   {"domini", domini, METH_VARARGS, "Pass a lot of variables, do a minimization, and the pass a lot of results back."},
   {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_minuit()
{
   (void) Py_InitModule("_minuit", MinuitMethods);
}
