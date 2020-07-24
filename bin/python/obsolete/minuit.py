import _minuit

def machineprecision():
  """Returns the precision of this computer."""
  return _minuit.machineprecision()

def eigenvalues(covariance):
  """Given a covariance matrix, returns the eigenvalues."""
  npar = len(covariance)
  return _minuit.calceigen(covariance, npar)

class Minuit:
  def __init__(self, f, up=1, start=None, step=None, fixed=None, limits=None, raise_exceptions = False, verbose=True, eps=0., maxcalls=0, tol=0., strategy=1, covariance=None, gradient=None, checkgrad=None):
    """Create a Minuit minimizer object.

    Arguments are:
        f                   callable (function) to be minimized (anything that accepts arguments: f(x))
        up                  definition of 1 sigma (1 for chi^2, 0.5 for -loglikelihood)
        start               starting values (henceforth accessed as .values)
        step                starting stepsize (henceforth accessed as .errors)
        fixed               list of booleans indicating which parameters are NOT to be used in minimization
                            (can be changed with .fix(parameter) and .release(parameter))
        limits              list of None or [lower, upper] limits on parameters
        raise_exceptions    if True, a failed minimization raises an exception; by default False
        verbose             print-outs from the python side (I can't control MINUIT's print-outs)
        eps                 value of epsilon (assumed machineprecision); default is 0. (MINUIT uses its own)
        maxcalls            (approximate) maximum number of MINUIT calls; default is 0 (unlimited)
        tol                 tolerated EDM before declaring success; default is 0. (MINUIT chooses its own)
        strategy            0 is fast, 1 is default, 2 is thorough
        covariance          covariance matrix as a list of lists
        gradient            callable that returns a tuple representing the gradient of the function
                            (this is broken: MINUIT refuses to use it for some C++ overloading reason)
        checkgrad           if True, ask MINUIT to check your gradient a few times before using it

    C++ MINUIT comes from the SEAL package by Fred James and Matthias Winkler
    http://seal.web.cern.ch/seal/snapshot/work-packages/mathlibs/minuit/index.html

    I'm told they wrote their own python wrapper, but I haven't been able to find it.
    """

    import inspect
    self.names, dummy1, dummy2, dummy3 = inspect.getargspec(f)
    self.npar = len(self.names)
    if start == None: start = [0.] * self.npar
    if step == None: step = [0.1] * self.npar
    if fixed == None: fixed = [False] * self.npar
    if limits == None: limits = [None] * self.npar

    self.f = f
    self.up = up
    self.values = start
    self.errors = step
    self.fixed = fixed
    self.limits = limits
    self.raise_exceptions = raise_exceptions
    self.verbose = verbose
    self.eps = eps
    self.maxcalls = maxcalls
    self.tol = tol
    self.strategy = strategy
    self.covariance = covariance
    self.gradient = gradient
    self.checkgrad = checkgrad
    self.ncalls = 0              # a.k.a. NFCN
    self.fminobj = None

    self.valid = False
    self.why = None
    self.whystring = "Minuit has not been executed."
    self.fval = None
    self.edm = None

    self.hesse_valid = False
    self.hesse_whystring = "Hesse has not been executed."

    self.minos_valid = False
    self.minos_why = [(None, None)] * self.npar
    self.minos_whystring = "Minos has not been executed."
    self.minos_errors = [(None, None)] * self.npar

  def findpar(self, s):
    """Given a name, return the parameter index."""
    for i, n in enumerate(self.names):
      if s == n: return i
    return None

  def fix(self, which):
    """Fix parameters so that they are not varied in the fit.

    Accepts a parameter index, name, or a tuple of such things.
    """
    if isinstance(which, int):
      which = (which,)
    elif isinstance(which, str):
      w = self.findpar(which)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      which = (w,)
    else:
      try: iter(which)  # to find out if which is any kind of iterable
      except TypeError:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

    tmp = []
    for i in which:
      if isinstance(i, str):
        w = self.findpar(i)
        if i == None:
          raise ValueError, "I don't recognize "+i+" as a parameter."
        if w not in tmp: tmp.append(w)
      elif isinstance(i, int):
        if not 0 <= i < self.npar:
          raise ValueError, "Parameter index "+str(i)+" is out of range."
        if i not in tmp: tmp.append(i)
      else:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

      self.fixed = list(self.fixed)
      for i in tmp:
        self.fixed[i] = True
    return None

  def release(self, which):
    """Release parameters so that they are varied in the fit.

    Accepts a parameter index, name, or a tuple of such things.
    """
    if isinstance(which, int):
      which = (which,)
    elif isinstance(which, str):
      w = self.findpar(which)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      which = (w,)
    else:
      try: iter(which)  # to find out if which is any kind of iterable
      except TypeError:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

    tmp = []
    for i in which:
      if isinstance(i, str):
        w = self.findpar(i)
        if i == None:
          raise ValueError, "I don't recognize "+i+" as a parameter."
        if w not in tmp: tmp.append(w)
      elif isinstance(i, int):
        if not 0 <= i < self.npar:
          raise ValueError, "Parameter index "+str(i)+" is out of range."
        if i not in tmp: tmp.append(i)
      else:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

      self.fixed = list(self.fixed)
      for i in tmp:
        self.fixed[i] = False
    return None

  def limit(self, which=None, low=None, high=None):
    """Limit a parameter so that only a range of values can be considered in a fit.

    Arguement list:
        which      a parameter index, name, or a tuple of such things,
                   or None for all of them
        low        the lower limit (or None, for unlimited variation)
        high       the upper limit (or None, for unlimited variation)

    Note that .limit() will release all limits, so it is aliased to .unlimit()
    """
    if which == None:
      which = range(self.npar)
    elif isinstance(which, int):
      which = (which,)
    elif isinstance(which, str):
      w = self.findpar(which)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      which = (w,)
    else:
      try: iter(which)  # to find out if which is any kind of iterable
      except TypeError:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

    tmp = []
    for i in which:
      if isinstance(i, str):
        w = self.findpar(i)
        if i == None:
          raise ValueError, "I don't recognize "+i+" as a parameter."
        if w not in tmp: tmp.append(w)
      elif isinstance(i, int):
        if not 0 <= i < self.npar:
          raise ValueError, "Parameter index "+str(i)+" is out of range."
        if i not in tmp: tmp.append(i)
      else:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

      if self.limits == None:
        self.limits = [None] * self.npar

      for i in tmp:
        self.limits[i] = [low, high]
    return None

  def unlimit(self, which=None):
    """Remove limits from a parameter.

    Accepts a parameter index, name, or a tuple of such things, or
    None to unlimit all parameters.
    """
    self.limit(which)

  def internal_beforeminimization(self):
    """Don't call this."""
    self.valid = False
    self.why = None
    self.whystring = "Exception thrown before minimization completed."
    self.fval = None
    self.edm = None

  def internal_afterminimization(self, values, errors, ncalls):
    """Don't call this."""
    whystrings = []
    if not self.why[0]: whystrings += ["covariance is not accurate"]
    if not self.why[1]: whystrings += ["covariance is not positive definite"]
    if not self.why[1] and not self.why[2]: whystrings += ["covariance couldn't be made positive definite"]
    if     self.why[3]: whystrings += ["Minuit failed to calculate the Hessian"]
    if not self.why[4]: whystrings += ["there is no covariance matrix"]
    if     self.why[5]: whystrings += ["the function is above maximum EDM"]
    if     self.why[6]: whystrings += ["Minuit reached maximum call limit"]
    if len(whystrings) == 0:
      if self.valid: self.whystring = "Minuit succeeded."
      else: self.whystring = "Minuit failed for unknown reasons."
    else:
      if self.valid: self.whystring = "Minuit succeeded, but "
      else: self.whystring = "Minuit failed because "
      for i, s in enumerate(whystrings):
        if i == len(whystrings)-1 and len(whystrings) != 1:
          self.whystring += "and "
        self.whystring += s
        if i != len(whystrings)-1:
          self.whystring += ", "
        else:
          self.whystring += "."

    if values is not None: self.values = values
    if errors is not None: self.errors = errors
    self.ncalls += ncalls

    if self.raise_exceptions and not self.valid:
      raise _minuit.MinuitError, self.whystring

    if self.verbose: print self.whystring
            
  def scan_minimize(self):
    """Use MINUIT's `SCAN' to minimize the function.

    This is probably not what you want: it steps through function
    values and picks the best one.  You could have done that yourself.

    Creates no covariance matrix, because no error estimation has been
    performed.
    """
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 0, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return None

  def simplex(self):
    """Use MINUIT's `SIMPLEX' to minimize the function.

    This is the cute algorithm described in section 10.4 of Numerical
    Recipies (Nealer and Mead).  It's probably not what you want.

    Creates no covariance matrix, because no error estimation has been
    performed.
    """
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 1, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return None

  def migrad(self):
    """Use MINUIT's `MIGRAD' to minimize the function.

    This is what you want.
    """
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 2, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return None

  def minimize(self):
    """Use MINUIT's `MINIMIZE' to minimize the function.

    This tries `MIGRAD' first, then `SIMPLEX' if that fails.
    """
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 3, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return None

  def hesse(self):
    """Run `HESSE' to get accurate error estimates.

    It doesn't put the sqrt diagonal elements into errors, yet, but it ought to."""

    if self.covariance == None:
      self.covariance = []
      for i in range(self.npar):
        row = []
        for j in range(self.npar):
          if i == j:
            row.append(self.errors[i]**2)
          else:
            row.append(0.)
        self.covariance.append(row)

    self.hesse_valid, self.covariance, self.fval, self.edm, ncalls = _minuit.dohesse(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, self.strategy, self.covariance, self.maxcalls)

    if self.hesse_valid:
      self.hesse_whystring = "Hesse succeeded."
    else:
      self.hesse_whystring = "Hesse failed."

    if self.raise_exceptions and not self.hesse_valid:
      raise _minuit.MinuitError, self.hesse_whystring

    if self.verbose: print self.hesse_whystring

    self.ncalls += ncalls
    return None

  def minos(self, which=None, lower=True, upper=True):
    """Use MINUIT's `MINOS' to get accurate non-linear errors.

    You must minimize the function first.

    Arguments are:
        which       a parameter index, name, or a tuple of such things
        lower       find the lower error (True by default)
        upper       find the upper error (True by default)
    """
    if self.fminobj == None:
      raise _minuit.MinuitError, "You must minimize the function before calling 'minos'."

    if which == None:
      which = range(self.npar)
    elif isinstance(which, int):
      which = (which,)
    elif isinstance(which, str):
      w = self.findpar(which)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      which = (w,)
    else:
      try: iter(which)  # to find out if which is any kind of iterable
      except TypeError:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."

    okay = True
    tmp = []
    for i in which:
      if isinstance(i, str):
        w = self.findpar(i)
        if i == None:
          raise ValueError, "I don't recognize "+i+" as a parameter."
        if w not in tmp: tmp.append(w)
      elif isinstance(i, int):
        if not 0 <= i < self.npar:
          raise ValueError, "Parameter index "+str(i)+" is out of range."
        if i not in tmp: tmp.append(i)
      else:
        raise TypeError, "Argument 'which' must be a parameter index, a parameter name, or a sequence of such things."
    which = tmp

    self.minos_valid = False
    self.minos_why = [(None, None)] * self.npar
    self.minos_whystring = "Exception thrown before Minos completed."
    self.minos_errors = [(None, None)] * self.npar
    tmpvalid = True

    for i in range(self.npar):
      if self.fixed[i] or i not in which:
        self.minos_why[i] = (None, None)
        self.minos_errors[i] = (None, None)
      else:
        (loerr, hierr), (lowhy, hiwhy), ncalls = _minuit.dominos(self.f, self.npar, self.up, self.fminobj, self.maxcalls, self.strategy, \
                                                                 lower, upper, i, self.gradient, self.checkgrad)
        if not lower: loerr = None
        if not upper: hierr = None
        if not lowhy[0]:
          tmpvalid = False
          loerr = None
        if not hiwhy[0]:
          tmpvalid = False
          hierr = None
        self.minos_why[i] = (lowhy, hiwhy)
        self.minos_errors[i] = (loerr, hierr)
        self.ncalls += ncalls

    self.minos_valid = tmpvalid
    whystrings = []
    for i in which:
      if not self.fixed[i]:
        if self.minos_why[i][0][1]: whystrings += ["lower "+self.names[i]+" reached physical limit"]
        if self.minos_why[i][1][1]: whystrings += ["upper "+self.names[i]+" reached physical limit"]
        if self.minos_why[i][0][2]: whystrings += ["lower "+self.names[i]+" reached maxcall limit"]
        if self.minos_why[i][1][2]: whystrings += ["upper "+self.names[i]+" reached maxcall limit"]
        if self.minos_why[i][0][3]: whystrings += ["lower "+self.names[i]+" found a new minimum"]
        if self.minos_why[i][1][3]: whystrings += ["upper "+self.names[i]+" found a new minimum"]

    if len(whystrings) == 0:
      if self.valid: self.minos_whystring = "Minos succeeded."
      else: self.minos_whystring = "Minos failed for unknown reasons."
    else:
      if self.valid: self.minos_whystring = "Minos succeeded, but "
      else: self.minos_whystring = "Minos failed because "
      for i, s in enumerate(whystrings):
        if i == len(whystrings)-1 and len(whystrings) != 1:
          self.minos_whystring += "and "
        self.minos_whystring += s
        if i != len(whystrings)-1:
          self.minos_whystring += ", "
        else:
          self.minos_whystring += "."

    if self.raise_exceptions and not self.valid:
      raise _minuit.MinuitError, self.minos_whystring

    if self.verbose: print self.minos_whystring

    return None

  def contours(self, parx, pary, up=None, npoints=20):
    """Get a contour curve around the minimum.

    You must minimize the function first.

    Arguments are:
        parx       which parameter will be treated as the x value in the plot
        pary       which parameter will be treated as the y value in the plot
        up         how far above the minimum to start drawing; self.up by default
        npoints    approximately how many points to use

    Returns (xlist, ylist) of x and y values.  Use `zip' to make them
    a single list of (x,y) points.
    """
    if self.fminobj == None:
      raise _minuit.MinuitError, "You must minimize the function before calling 'contours'."

    if up == None: up = self.up

    if isinstance(parx, int):
      if not 0 <= parx < self.npar:
        raise ValueError, "Parameter index "+str(parx)+" is out of range."
    elif isinstance(parx, str):
      w = self.findpar(parx)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      parx = w
    else:
      raise TypeError, "Argument 'parx' must be a parameter index or a parameter name."

    if isinstance(pary, int):
      if not 0 <= pary < self.npar:
        raise ValueError, "Parameter index "+str(pary)+" is out of range."
    elif isinstance(pary, str):
      w = self.findpar(pary)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      pary = w
    else:
      raise TypeError, "Argument 'pary' must be a parameter index or a parameter name."

    contx, conty, (xerr_lower, xerr_upper), (yerr_lower, yerr_upper), ncalls = \
           _minuit.docontours(self.f, self.npar, up, self.fminobj, self.maxcalls, self.strategy, parx, pary, npoints, self.gradient, self.checkgrad)
    self.ncalls += ncalls
    # I don't know what to do with the pseudo-minos errors, so I drop them

    return contx, conty
      
  def scan(self, par, low=None, high=None, npoints=41, sort=True):
    """Scan across the minimum to see how steeply the function rises.

    You must minimize the function first.

    Arguments are:
        par       which parameter to scan across
        low       the lower bound on the scan; -2 sigma by default
        high      the upper bound on the scan; +2 sigma by default
        npoints   approximately how many points to use
        sort      True (by default) if you want the points in order
                  (for plotting).  MINUIT's natural order seems to be
                  minimum first, then the other points in order.

    Returns (xlist, zlist) of parameter values and function values.
    Use `zip' to make them a single list of (x, z) points.
    """
    if isinstance(par, int):
      if not 0 <= par < self.npar:
        raise ValueError, "Parameter index "+str(par)+" is out of range."
    elif isinstance(par, str):
      w = self.findpar(par)
      if w == None:
        raise ValueError, "I don't recognize "+which+" as a parameter."
      par = w
    else:
      raise TypeError, "Argument 'par' must be a parameter index or a parameter name."

    if low == None or high == None: low, high = 0., 0.

    xlist, zlist =  _minuit.doscan(self.f, self.npar, self.names, self.values, self.errors, self.fixed, self.limits, self.eps, npoints, \
                                   self.strategy, self.covariance, par, low, high)
    self.ncalls += npoints

    if (sort):
      combined = zip(xlist, zlist)
      combined.sort(lambda a, b: cmp(a[0], b[0]))  # sort by x entries, not y
      xlist, zlist = zip(*combined)

    return xlist, zlist

  def globalCC(self):
    if self.covariance == None: return None
    gcc = []
    import math
    for i in range(self.npar):
      row = []
      for j in range(self.npar):
        if self.covariance[i][i] != 0. and self.covariance[j][j] != 0.:
          row.append(self.covariance[i][j] / math.sqrt(self.covariance[i][i] * self.covariance[j][j]))
        else:
          row.append(0.)
      gcc.append(row)
    return gcc

  def __repr__(self):
    retval = "f("
    for i, n in enumerate(self.names):
      retval += n
      if i != self.npar-1: retval += ", "
    retval += ") is "+str(self.f)+", with up = "+str(self.up)
    if self.gradient != None:
      retval += ", and gradient is "+str(self.gradient)

    retval += "\n\n"+self.whystring+"\n"+self.hesse_whystring+"\n"+self.minos_whystring+"\n\n"

    if self.valid:
      retval += "fval = "+str(self.fval)+", edm = "+str(self.edm)+", ncalls = "+str(self.ncalls)+"\n\n"

    for i in range(self.npar):
      retval += "    "+self.names[i]+" = "+str(self.values[i])+" +/- "+str(self.errors[i])
      if self.minos_valid and self.minos_errors[i] != (None, None):
        if self.minos_errors[i][0] != None:
          retval += " - "+str(abs(self.minos_errors[i][0]))
        else:
          retval += " - ???"
        if self.minos_errors[i][1] != None:
          retval += " + "+str(self.minos_errors[i][1])
        else:
          retval += " + ???"
      if self.limits[i] == None or self.limits[i] == [None, None]:
        retval += ", no limits"
      else:
        if self.limits[i][0] == None:
          retval += ", no lower limit"
        else:
          retval += ", "+str(self.limits[i][0])
        if self.limits[i][1] == None:
          retval += ", no upper limit"
        else:
          retval += ", "+str(self.limits[i][1])
      if i != self.npar-1:
        retval += "\n"

    if self.covariance != None:
      retval += "\n\nCovariance matrix:\n\n"
      for i in range(self.npar):
        for j in range(i+1):
          retval += "%15g" % self.covariance[i][j]
          if j != i:
            retval += "  "
        if i != self.npar-1:
          retval += "\n"

    if self.covariance != None:
      retval += "\n\nGlobal correlation coefficients:\n\n"
      gcc = self.globalCC()
      for i in range(self.npar):
        for j in range(i+1):
          retval += "%15g" % gcc[i][j]
          if j != i:
            retval += "  "
        if i != self.npar-1:
          retval += "\n"

    if self.eps != 0. or self.maxcalls != 0 or self.tol != 0.:
      retval += "\n\n"

    if self.eps != 0.:
      retval += "eps = "+str(self.eps)
      if self.maxcalls != 0 or self.tol != 0.:
        retval += ", "

    if self.maxcalls != 0:
      retval += "maxcalls = "+str(self.maxcalls)
      if self.tol != 0.:
        retval += ", "

    if self.tol != 0.:
      retval += "tol = "+str(self.tol)

    return retval
