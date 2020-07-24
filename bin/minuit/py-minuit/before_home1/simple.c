// gcc -c simple.c -I/nfs/cleo3/Offline/rel/current/other_sources/python/include/python2.4/ && ld -shared simple.o -o simple.so

#include <Python.h>

static PyObject *my_func = NULL;

static PyObject* simple_set_func(dummy, args)
  PyObject *dummy, *args;
{
  PyObject *result = NULL;
  PyObject *temp;

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }
    Py_XINCREF(temp);    // add a reference to the new callback
    Py_XDECREF(my_func); // dispose of previous callback
    my_func = temp;
    
    Py_INCREF(Py_None);
    result = Py_None;
  }
  return result;
}

static PyObject* simple_callit(PyObject *self, PyObject *args)
{
  int arg, res;
  PyObject *arglist, *result;
  
  arg = 2;

  arglist = Py_BuildValue("(i)", arg);
  result = PyEval_CallObject(my_func, arglist);
  Py_DECREF(arglist);

  if (result == NULL) return NULL;  // for exceptions in the function

  if (!PyArg_Parse(result, "i", &res)) {
    PyErr_SetString(PyExc_TypeError, "callable function must return an integer");
    return NULL;
  }
  Py_DECREF(result);  // we're not passing the result on, so we should close this memory leak
    
  res *= -1;
  return Py_BuildValue("i", res);
}

static PyObject* simple_plusone(PyObject *self, PyObject *args)
{
  int input;
  int output;

  if (!PyArg_ParseTuple(args, "i", &input))
    return NULL;
  output = input + 1;
  
  return Py_BuildValue("i", output);
}

static PyMethodDef SimpleMethods[] = {
  {"plusone", simple_plusone, METH_VARARGS},
  {"set_func", simple_set_func, METH_VARARGS},
  {"callit", simple_callit, METH_VARARGS},
  {NULL, NULL}
};

void initsimple()
{
  (void) Py_InitModule("simple", SimpleMethods);
}

