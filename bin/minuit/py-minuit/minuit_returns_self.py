import _minuit

def machineprecision():
  return _minuit.machineprecision()

def eigenvalues(covariance):
  npar = len(covariance)
  return _minuit.calceigen(covariance, npar)

class Minuit:
  def __init__(self, f, up=0.5, start=None, step=None, fixed=None, limits=None, raise_exceptions = False, verbose=True, eps=0., maxcalls=0, tol=0., strategy=1, covariance=None, gradient=None, checkgrad=None):
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
    for i, n in enumerate(self.names):
      if s == n: return i
    return None

  def internal_beforeminimization(self):
    self.valid = False
    self.why = None
    self.whystring = "Exception thrown before minimization completed."
    self.fval = None
    self.edm = None

  def internal_afterminimization(self, values, errors, ncalls):
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
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 0, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return self

  def simplex(self):
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 1, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return self

  def migrad(self):
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 2, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return self

  def minimize(self):
    self.internal_beforeminimization()
    self.valid, self.why, self.fval, self.edm, ncalls, values, errors, self.covariance, self.fminobj = \
                _minuit.domini(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, \
                               self.eps, self.maxcalls, self.tol, self.strategy, self.covariance, 3, self.gradient, self.checkgrad)
    self.internal_afterminimization(values, errors, ncalls)
    return self

  def hesse(self):
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

    print self.covariance, id(self.covariance), type(self.covariance)

    self.hesse_valid, self.covariance, self.fval, self.edm, ncalls = _minuit.dohesse(self.f, self.npar, self.up, self.names, self.values, self.errors, self.fixed, self.limits, self.strategy, self.covariance, self.maxcalls)

    if self.hesse_valid:
      self.hesse_whystring = "Hesse succeeded."
    else:
      self.hesse_whystring = "Hesse failed."

    if self.raise_exceptions and not self.hesse_valid:
      raise _minuit.MinuitError, self.hesse_whystring

    if self.verbose: print self.hesse_whystring

    self.ncalls += ncalls
    return self

  def minos(self, which=None, lower=True, upper=True):
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
        if self.minos_why[i][0][1]: whystrings += ["lower "+name[i]+" reached physical limit"]
        if self.minos_why[i][1][1]: whystrings += ["upper "+name[i]+" reached physical limit"]
        if self.minos_why[i][0][2]: whystrings += ["lower "+name[i]+" reached maxcall limit"]
        if self.minos_why[i][1][2]: whystrings += ["upper "+name[i]+" reached maxcall limit"]
        if self.minos_why[i][0][3]: whystrings += ["lower "+name[i]+" found a new minimum"]
        if self.minos_why[i][1][3]: whystrings += ["upper "+name[i]+" found a new minimum"]

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

    return self

  def contours(self, parx, pary, up=None, npoints=20):
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

    xlist, ylist =  _minuit.doscan(self.f, self.npar, self.names, self.values, self.errors, self.fixed, self.limits, self.eps, npoints, \
                                   self.strategy, self.covariance, par, low, high)
    self.ncalls += npoints

    if (sort):
      combined = zip(xlist, ylist)
      combined.sort(lambda a, b: cmp(a[0], b[0]))  # sort by x entries, not y
      xlist, ylist = zip(*combined)

    return xlist, ylist
