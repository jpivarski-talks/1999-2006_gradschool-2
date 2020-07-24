import Numeric, math, biggles

##### random utilities ###################################################

def numberQ(x):
  try:
    float(x)
    return True
  except:
    return False

def iterableQ(x):
  if type(x) == str: return False   # not iterable for my purposes
  try:
    iter(x)
    return True
  except:
    return False

##### prehist: determine the best histogram bounds #######################

class PrehistResults:
  def __init__(self):
    self.min = None
    self.max = None
    self.mean = None
    self.stdev = None
    self.all_integral = None
    self.median = None
    self.onesig = None
    self.twosig = None
    self.threesig = None

  def __repr__(self):
    retval = ""
    if self.min == None:
      retval += "List is empty."
    else:
      retval += "Range is (" + str(self.min) + ", " + str(self.max) \
          + "), mean is " + str(self.mean) \
          + ", stdev is " + str(self.stdev) \
          + ((self.all_integral and ", all with integral values.") or ".")
      if self.median != None:
        retval += "\n"
        retval += "Median is " + str(self.median)
        if self.onesig != None:
          retval += "\n"
          retval += "68% around median: +/- " + str(self.onesig) + "\n"
          retval += "95% around median: +/- " + str(self.twosig) + "\n"
          retval += "99% around median: +/- " + str(self.threesig)
    return retval

def prehist(x, quick=False):
  n = 0
  results = PrehistResults()
  themin = 0.
  themax = 0.
  thesum = 0.
  thesum2 = 0.
  sawreal = False
  sawnonnum = False
  for i in x:
    if not numberQ(i):
      print "Element", n, "is not an integer or a float."
      return
    if n == 0:
      themin = i
      themax = i
    else:
      if i < themin: themin = i
      if i > themax: themax = i
    thesum += i
    thesum2 += math.pow(i,2)
    if i != math.floor(i): sawreal = True
    n += 1
  if n == 0:
    print "List is empty."
  else:
    results.min = themin
    results.max = themax
    results.mean = thesum/float(n)
    results.stdev = math.sqrt(thesum2/float(n) - math.pow(thesum/float(n),2))
    results.all_integral = not sawreal
    print "Range is (" + str(results.min) + ", " + str(results.max) \
          + "), mean is " + str(results.mean) \
          + ", stdev is " + str(results.stdev) \
          + ((not sawreal and ", all with integral values.") or ".")
    if (not quick):
      y = Numeric.array(x)
      y = Numeric.sort(y)
      results.median = y[int(math.floor(0.5*float(n)))]
      print "Median is", results.median
      y = Numeric.array(x) - results.median
      y = Numeric.sort(Numeric.fabs(y))
      results.onesig = y[int(math.floor(0.68*float(n)))]
      results.twosig = y[int(math.floor(0.95*float(n)))]
      results.threesig = y[int(math.floor(0.997*float(n)))]
      print "68% around median: +/-", results.onesig
      print "95% around median: +/-", results.twosig
      print "99% around median: +/-", results.threesig
  return results

##### addinfobox: one of those HBOOK things ##############################

def addinfobox(p, info, width=0.38, colwidth=0.07, corner=1, numformat="%.3g"):
  lx, ly, rx, ry = 0, 0, 0, 0
  height = len(info)*0.06 + 0.03
  if corner==1:
    p.add(biggles.PlotBox((1.-width, 1.-height), (1,1)))
    lx = 1. - width + 0.02
    ly = 1. - 0.03
    rx = 1. - 0.03
    ry = 1. - 0.03
  elif corner==2:
    p.add(biggles.PlotBox((0, 1-height), (width, 1)))
    lx = 0.03
    ly = 1. - 0.03
    rx = width - 0.02
    ry = 1. - 0.03
  elif corner==3:
    p.add(biggles.PlotBox((0,0), (width, height)))
    lx = 0.03
    ly = height - 0.02
    rx = width - 0.02
    ry = height - 0.02
  elif corner==4:
    p.add(biggles.PlotBox((1.-width, 0), (1, height)))
    lx = 1. - width + 0.02
    ly = height - 0.02
    rx = 1. - 0.03
    ry = height - 0.02
  else:
    raise TypeError, "Corner must be 1 (upper-right), 2 (u-left), 3 (b-l), or 4 (b-r)."
  for line in info:
    if iterableQ(line):
      if isinstance(line[0], str):
        p.add(biggles.PlotLabel(lx, ly, line[0], halign="left", valign="top"))
      elif numberQ(line[0]):
        p.add(biggles.PlotLabel(lx, ly, (numformat % (line[0])), halign="left", valign="top"))
      else:
        raise TypeError, "Info must be a matrix of strings and numbers."
      ly -= 0.06

      extrax = [0.] * len(line)
      if numberQ(colwidth):
        s = 0.
        for i in range(len(extrax)-1, 0, -1):
          extrax[i] = s
          s += colwidth
      else:
        s = 0.
        for i in range(len(extrax)-1, 0, -1):
          extrax[i] = s
          s += colwidth[i-1]

      for i in range(1, len(line)):
        if isinstance(line[i], str):
          p.add(biggles.PlotLabel(rx - extrax[i], ry, line[i], halign="right", valign="top"))
        elif numberQ(line[i]):
          p.add(biggles.PlotLabel(rx - extrax[i], ry, (numformat % (line[i])), halign="right", valign="top"))
        else:
          raise TypeError, "Info must be a matrix of strings and numbers."
      ry -= 0.06

    elif isinstance(line, str):
      p.add(biggles.PlotLabel(lx, ly, line, halign="left", valign="top"))
      ly -= 0.06
      ry -= 0.06
    elif numberQ(line):
      p.add(biggles.PlotLabel(lx, ly, (numformat % (line)), halign="left", valign="top"))
      ly -= 0.06
      ry -= 0.06
    else:
      raise TypeError, "Info must be a matrix of strings and numbers."
  return p

##### H1FRAME: a generalized 1-d histogram (arbitrary frame) #############
##### H1: 1-d histogram ##################################################

class h1frame:
  def __init__(self, frame, high=None, func=None, vals=None, errs=None, overflow=0., underflow=0., overflow_error=0., underflow_error=0.):

    # Make sure it's an array of numbers
    if not isinstance(frame, Numeric.ArrayType):
      allok = False
      if (iterableQ(frame)):
        allok = True
        prev = 0
        for i in frame:
          if not numberQ(i): allok = False
          if id(i) == id(frame[0]):
            prev = i
          else:
            if i < prev: allok = False
            prev = i
      if not allok: raise TypeError, "The frame must be an increasing list or an array of int/float.  (It is "+str(frame)+" of type "+str(type(frame))+".)"

    # It's acceptable.
    self.frame = Numeric.array(frame)
    self.regular = False

    # high is the last upper edge, so it must be beyond the frame
    if high == None or high <= frame[-1]:
      self.high = frame[-1] + (frame[-1] - frame[-2])
    else:
      self.high = high

    self.vals = Numeric.zeros(len(frame), 'd')
    self.errs = Numeric.zeros(len(frame), 'd')

    self.overflow = overflow
    self.underflow = underflow
    self.overflow_error = overflow_error
    self.underflow_error = underflow_error
    # fill_factor is only used for regular histograms
    self.fill_factor = None

    if func != None:
      self.setfunc(func)
    if vals != None:
      self.setvals(vals)
    if errs != None:
      self.seterrs(errs)
    return

  # set the values of val to the output of a function
  def setfunc(self, func):
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      self.vals[i] = func((self.frame[i] + upend)/2.)
    return self

  # setvals and seterrs walk through the array step-by-step so that
  # you don't accidentally change the type of self.vals or self.errs
  def setvals(self, vals):
    if len(vals) != len(self.frame):
      raise TypeError, "Can't set the values of this histogram ("+str(len(self.frame))+" bins) to an array of length "+str(len(vals))+"."
    for i in range(len(vals)):
      if not numberQ(vals[i]):
        raise TypeError, "Can't set value "+str(i)+" of this histogram to "+str(vals[i])+" "+str(type(vals[i]))+"."
      self.vals[i] = vals[i]
    return self

  def seterrs(self, errs):
    if len(errs) != len(self.frame):
      raise TypeError, "Can't set the values of this histogram ("+str(len(self.frame))+" bins) to an array of length "+str(len(errs))+"."
    for i in range(len(errs)):
      if not numberQ(errs[i]):
        raise TypeError, "Can't set value "+str(i)+" of this histogram to "+str(errs[i])+" "+str(type(errs[i]))+"."
      self.errs[i] = errs[i]
    return self

  # You can ask for histogram[i]; the errors are kind of like an additional column
  def __getitem__(self, i):
    if type(i) == tuple:
      if i[1] == 0:
        return self.vals[i[0]]
      else:
        return self.errs[i[0]]
    else:
      return self.vals[i]

  def __setitem__(self, i, v):
    if type(i) == tuple:
      if i[1] == 0:
        self.vals[i[0]] = v
      else:
        self.errs[i[0]] = v
    else:
      self.vals[i] = v
    return v

  # If the histogram is called like a function, return an interpolated value (0 outside range)
  def __call__(self, x):
    if x < self.frame[0] or x > self.high: return None
    x1 = 0
    x2 = 0
    for i in range(len(self.frame)-1):
      x1 = float(self.frame[i] + self.frame[i+1])/2.
      x2 = float(self.frame[i+1] + self.high)/2.
      if i != len(self.frame)-2:
        x2 = float(self.frame[i+1] + self.frame[i+2])/2.
      if (x < x1): break
      if (x >= x1 and x < x2): break
    y1 = self.vals[i]
    y2 = self.vals[i+1]
    m = float(y2 - y1)/float(x2 - x1)
    b = float(y1) - m * x1
    return m * x + b

  # add, sub, mul, and div do the four functions on histograms, or with a histogram and a scalar
  # all assume independent errors
  def __add__(self, other):
    if numberQ(other):
      tmp = h1frame(self.frame)
      tmp.regular = self.regular
      tmp.vals = self.vals + other
      tmp.errs = self.errs
      tmp.overflow = self.overflow + other
      tmp.underflow = self.underflow + other
      tmp.fill_factor = self.fill_factor
      return tmp
    if (self.frame != other.frame):
      raise TypeError, "Cannot add incompatible histograms.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = h1frame(self.frame)
    tmp.regular = self.regular or other.regular
    tmp.vals = self.vals + other.vals
    tmp.errs = Numeric.sqrt(Numeric.power(self.errs,2) + Numeric.power(other.errs,2))
    tmp.overflow = self.overflow + other.overflow
    tmp.underflow = self.underflow + other.underflow
    tmp.overflow_error = math.sqrt(self.overflow_error**2 + other.overflow_error**2)
    tmp.underflow_error = math.sqrt(self.underflow_error**2 + other.underflow_error**2)
    tmp.fill_factor = self.fill_factor or other.fill_factor
    return tmp

  # add, sub, mul, and div do the four functions on histograms, or with a histogram and a scalar
  # all assume independent errors
  def __sub__(self, other):
    if numberQ(other):
      tmp = h1frame(self.frame)
      tmp.regular = self.regular
      tmp.vals = self.vals - other
      tmp.errs = self.errs
      tmp.overflow = self.overflow - other
      tmp.underflow = self.underflow - other
      tmp.fill_factor = self.fill_factor
      return tmp
    if (self.frame != other.frame):
      raise TypeError, "Cannot subtract incompatible histograms.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = h1frame(self.frame)
    tmp.regular = self.regular or other.regular
    tmp.vals = self.vals - other.vals
    tmp.errs = Numeric.sqrt(Numeric.power(self.errs,2) + Numeric.power(other.errs,2))
    tmp.overflow = self.overflow - other.overflow
    tmp.underflow = self.underflow - other.underflow
    tmp.overflow_error = math.sqrt(self.overflow_error**2 + other.overflow_error**2)
    tmp.underflow_error = math.sqrt(self.underflow_error**2 + other.underflow_error**2)
    tmp.fill_factor = self.fill_factor or other.fill_factor
    return tmp

  # add, sub, mul, and div do the four functions on histograms, or with a histogram and a scalar
  # all assume independent errors
  def __mul__(self, other):
    if numberQ(other):
      tmp = h1frame(self.frame)
      tmp.regular = self.regular
      tmp.vals = self.vals * other
      tmp.errs = self.errs * other
      tmp.overflow = self.overflow * other
      tmp.underflow = self.underflow * other
      tmp.fill_factor = self.fill_factor
      return tmp
    if (self.frame != other.frame):
      raise TypeError, "Cannot subtract incompatible histograms.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = h1frame(self.frame)
    tmp.regular = self.regular or other.regular
    tmp.vals = self.vals * other.vals
    for i in range(len(tmp.frame)):
      s = 0
      o = 0
      if self.vals[i] > 0: s = math.pow(self.errs[i] / self.vals[i], 2)
      if other.vals[i] > 0: o = math.pow(other.errs[i] / other.vals[i], 2)
      tmp.errs[i] = tmp.vals[i] * math.sqrt(s + o)
    tmp.overflow = self.overflow * other.overflow
    tmp.underflow = self.underflow * other.underflow
    tmp.overflow_error = tmp.overflow * math.sqrt((self.overflow_error / self.overflow)**2 + (other.overflow_error / other.overflow)**2)
    tmp.underflow_error = tmp.underflow * math.sqrt((self.underflow_error / self.underflow)**2 + (other.underflow_error / other.underflow)**2)
    tmp.fill_factor = self.fill_factor or other.fill_factor
    return tmp

  # add, sub, mul, and div do the four functions on histograms, or with a histogram and a scalar
  # all assume independent errors; if you want to divide by a superset, use divide_by_superset
  def __div__(self, other):
    if numberQ(other):
      tmp = h1frame(self.frame)
      tmp.regular = self.regular
      try:
        tmp.vals = self.vals / other
        tmp.errs = self.errs / other
        tmp.overflow = self.overflow / other
        tmp.underflow = self.underflow / other
      except ZeroDivisionError:
        raise ZeroDivisionError, "Attempting to divide histogram by a zero scalar."
      tmp.fill_factor = self.fill_factor
      return tmp
    if (self.frame != other.frame):
      raise TypeError, "Cannot divide incompatible histograms.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = h1frame(self.frame)
    tmp.regular = self.regular or other.regular
    for i in range(len(tmp.frame)):
      try:
        tmp.vals[i] = self.vals[i] / other.vals[i]
      except ZeroDivisionError:
        tmp.vals[i] = 0.
    for i in range(len(tmp.frame)):
      s = 0
      o = 0
      if self.vals[i] > 0: s = math.pow(self.errs[i] / self.vals[i], 2)
      if other.vals[i] > 0: o = math.pow(other.errs[i] / other.vals[i], 2)
      tmp.errs[i] = tmp.vals[i] * math.sqrt(s + o)
    try:
      tmp.overflow = self.overflow / other.overflow
      try:
        tmp.overflow_error = tmp.overflow * math.sqrt((self.overflow_error / self.overflow)**2 + (other.overflow_error / other.overflow)**2)
      except ZeroDivisionError:
        tmp.overflow_error = 0.
    except ZeroDivisionError:
      tmp.overflow = 0.
      tmp.overflow_error = 0.
    try:
      tmp.underflow = self.underflow / other.underflow
      try:
        tmp.underflow_error = tmp.underflow * math.sqrt((self.underflow_error / self.underflow)**2 + (other.underflow_error / other.underflow)**2)
      except ZeroDivisionError:
        tmp.underflow_error = 0.
    except ZeroDivisionError:
      tmp.underflow = 0.
      tmp.underflow_error = 0.
    tmp.fill_factor = self.fill_factor or other.fill_factor
    return tmp

  # ignores the errors on both histograms and divides self / other as though self were a subset of other
  # binomial errors are calculated (limit to zero at 0% and 100%)
  def divide_by_superset(self, other):
    if (self.frame != other.frame):
      raise TypeError, "Cannot subtract incompatible histograms.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = h1frame(self.frame)
    tmp.regular = self.regular or other.regular
    for i in range(len(tmp.frame)):
      if other.vals[i] > 0:
        tmp.vals[i] = self.vals[i] / other.vals[i]
        if tmp.vals[i] > 0 and (1. - tmp.vals[i]) > 0:
          tmp.errs[i] = math.sqrt(tmp.vals[i] * (1. - tmp.vals[i]) / other.vals[i])
    try:
      tmp.overflow = self.overflow / other.overflow
      tmp.overflow_error = math.sqrt(tmp.overflow * (1.-tmp.overflow) / other.overflow)
    except ZeroDivisionError:
      tmp.overflow = 0.
      tmp.overflow_error = 0.
    try:
      tmp.underflow = self.underflow / other.underflow
      tmp.underflow_error = math.sqrt(tmp.underflow * (1.-tmp.underflow) / other.underflow)
    except ZeroDivisionError:
      tmp.underflow = 0.
      tmp.underflow_error = 0.
    tmp.fill_factor = self.fill_factor or other.fill_factor
    return tmp

  def divide_from_subset(self, other):
    return other.divide_by_superset(self)

  # This applies a function to all histogram values.
  # deriv is the derivative of func, for propogating errors (if not given, it will be approximated)
  # Divide-by-zeros result in 0 values.  Watch out!
  def map(self, func, deriv=None):
    tmp = h1frame(self.frame)
    tmp.regular = self.regular
    tmp.fill_factor = self.fill_factor
    for i in range(len(self.frame)):
      tmp.vals[i] = func(self.vals[i])
      if deriv != None:
        tmp.errs[i] = math.sqrt(math.fabs(deriv(self.vals[i]))) * self.errs[i]
      elif self.errs[i] > 0.:
        x = float(self.vals[i])
        dx = float(self.errs[i])/2.
        try:
          # This is O(dx^2)
          der = float(-func(x+2.*dx) + 8*func(x+dx) - 8*func(x-dx) + func(x-2.*dx))/12./dx
          tmp.errs[i] = math.sqrt(math.fabs(der)) * self.errs[i]
        except ZeroDivisionError:
          tmp.errs[i] = 0.        
      else:
        tmp.errs[i] = 0.

    # yes, this is copy-pasted.
    tmp.overflow = func(self.overflow)
    if deriv != None:
      tmp.overflow_error = math.sqrt(math.fabs(deriv(self.overflow))) * self.overflow_error
    elif self.overflow_error > 0.:
      x = float(self.overflow)
      dx = float(self.overflow_error)/2.
      try:
        # This is O(dx^2)
        der = float(-func(x+2.*dx) + 8*func(x+dx) - 8*func(x-dx) + func(x-2.*dx))/12./dx
        tmp.overflow_error = math.sqrt(math.fabs(der)) * self.overflow_error
      except ZeroDivisionError:
        tmp.overflow_error = 0.        
    else:
      tmp.overflow_error = 0.

    # yes, this is copy-pasted.
    tmp.overflow = func(self.overflow)
    if deriv != None:
      tmp.overflow_error = math.sqrt(math.fabs(deriv(self.overflow))) * self.overflow_error
    elif self.overflow_error > 0.:
      x = float(self.overflow)
      dx = float(self.overflow_error)/2.
      try:
        # This is O(dx^2)
        der = float(-func(x+2.*dx) + 8*func(x+dx) - 8*func(x-dx) + func(x-2.*dx))/12./dx
        tmp.overflow_error = math.sqrt(math.fabs(der)) * self.overflow_error
      except ZeroDivisionError:
        tmp.overflow_error = 0.        
    else:
      tmp.overflow_error = 0.
    return tmp

  # Put a value into the histogram, or an array, or an iterator.
  def fill(self, x, weight=1.):
    if type(x) == int or type(x) == float or numberQ(x):
      if x < self.frame[0]: self.underflow += weight
      elif x >= self.high: self.overflow += weight
      elif self.regular:
        self.vals[int(math.floor((x - self.frame[0])*self.fill_factor))] += weight
      else:
        for i in range(1, len(self.frame)):
          if x < self.frame[i]:
            self.vals[i-1] += weight
            break
        if x >= self.frame[-1]:
          self.vals[-1] += weight
    elif iterableQ(x):
      for xi in x: self.fill(xi)
      return self
    else:
      raise TypeError, "You must fill with a number or an iterator of numbers."
    return self

  # Add up histogram values within a range (full range if not given)
  # Doesn't include overflow/underflow
  # If a range end is in the middle of a bin, it will linearly interpolate
  def sum(self, xlow=None, xhigh=None, overunderflow=False):
    if xlow == None: xlow = self.frame[0]
    if xhigh == None: xhigh = self.high
    sign = 1.
    if xlow > xhigh:
      xlow, xhigh = xhigh, xlow
      sign = -1.
    if xlow == xhigh: return 0.
    s = 0.
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if xlow >= self.frame[i] and xlow < upend:
        if xhigh < upend:
          s += self.vals[i] * float(xhigh - xlow)/float(upend - self.frame[i])
          break
        else:
          s += self.vals[i] * float(upend - xlow)/float(upend - self.frame[i])
      elif xlow < self.frame[i]:
        if xhigh < upend:
          s += self.vals[i] * float(xhigh - self.frame[i])/float(upend - self.frame[i])
          break
        else:
          s += self.vals[i]
    if overunderflow:
      s += self.overflow
      s += self.underflow
    return s * sign

  # Get the error on a sum (assuming histogram errors are independent)
  def sumerr(self, xlow=None, xhigh=None, overunderflow=False):
    if xlow == None: xlow = self.frame[0]
    if xhigh == None: xhigh = self.high
    if xlow > xhigh:
      xlow, xhigh = xhigh, xlow
    if xlow == xhigh: return 0.
    s = 0.
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if xlow >= self.frame[i] and xlow < upend:
        if xhigh < upend:
          s += math.pow(self.errs[i] * float(xhigh - xlow)/float(upend - self.frame[i]), 2)
          break
        else:
          s += math.pow(self.errs[i] * float(upend - xlow)/float(upend - self.frame[i]), 2)
      elif xlow < self.frame[i]:
        if xhigh < upend:
          s += math.pow(self.errs[i] * float(xhigh - self.frame[i])/float(upend - self.frame[i]), 2)
          break
        else:
          s += math.pow(self.errs[i], 2)
    if overunderflow:
      s += math.pow(self.overflow_error[i], 2)
      s += math.pow(self.underflow_error[i], 2)
    return math.sqrt(s)

  # Integrate over the histogram, just as in sum, but taking care of the domain.
  # This would be trivially related to sum if the bins were of equal sizes.
  def int(self, xlow=None, xhigh=None):
    if xlow == None: xlow = self.frame[0]
    if xhigh == None: xhigh = self.high
    sign = 1.
    if xlow > xhigh:
      xlow, xhigh = xhigh, xlow
      sign = -1.
    if xlow == xhigh: return 0.
    s = 0.
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if xlow >= self.frame[i] and xlow < upend:
        if xhigh < upend:
          s += self.vals[i] * (xhigh - xlow)
          break
        else:
          s += self.vals[i] * (upend - xlow)
      elif xlow < self.frame[i]:
        if xhigh < upend:
          s += self.vals[i] * (xhigh - self.frame[i])
          break
        else:
          s += self.vals[i] * (upend - self.frame[i])
    return s * sign

  # Get the error on an integration (int), assuming independent histogram errors.
  def interr(self, xlow=None, xhigh=None):
    if xlow == None: xlow = self.frame[0]
    if xhigh == None: xhigh = self.high
    if xlow > xhigh:
      xlow, xhigh = xhigh, xlow
    if xlow == xhigh: return 0.
    s = 0.
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if xlow >= self.frame[i] and xlow < upend:
        if xhigh < upend:
          s += math.pow(self.errs[i] * (xhigh - xlow), 2)
          break
        else:
          s += math.pow(self.errs[i] * (upend - xlow), 2)
      elif xlow < self.frame[i]:
        if xhigh < upend:
          s += math.pow(self.errs[i] * (xhigh - self.frame[i]), 2)
          break
        else:
          s += math.pow(self.errs[i] * (upend - self.frame[i]), 2)
    return math.sqrt(s)

  # Convenience functions
  def width(self):
    return self.high - self.frame[0]

  def bins(self):
    return len(self.frame)

  # Set all histogram errors to sqrt(N)
  def rootn(self):
    for i in range(len(self.frame)):
      if self.vals[i] >= 0.:
        self.errs[i] = math.sqrt(self.vals[i])
      else:
        self.errs[i] = 0.
    self.overflow_error = math.sqrt(self.overflow)
    self.underflow_error = math.sqrt(self.underflow)
    return self

  # Draw the histogram as steps
  def steps(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    x = []
    y = []
    for i in range(len(self.frame)):
      x.append(self.frame[i])
      y.append(self.vals[i])
      if i+1 >= len(self.frame):
        x.append(self.high)
      else:
        x.append(self.frame[i+1])
      y.append(self.vals[i])
    if asbiggles:
      return biggles.Curve(x, y, linecolor=linecolor, linetype=linetype, linewidth=linewidth)
    else:
      return x, y

  # Shade under the steps, between low and high, if given
  def stepsfill(self, low = None, high = None, asbiggles=True, color=0xcccccc):
    if low == None: low = self.frame[0]
    if high == None: high = self.high
    if low > high: low, high = high, low
    x = []
    y = []
    xz = []
    yz = []
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if high > self.frame[i]:
        if self.frame[i] <= low and low < upend:
          x.append(low)
          y.append(self.vals[i])
          xz.append(low)
          yz.append(0.)
        elif low < self.frame[i]:
          x.append(self.frame[i])
          y.append(self.vals[i])
          xz.append(self.frame[i])
          yz.append(0.)
      if low < upend:
        if self.frame[i] <= high and high < upend:
          x.append(high)
          y.append(self.vals[i])
          xz.append(high)
          yz.append(0.)
        elif self.frame[i] <= high:
          x.append(upend)
          y.append(self.vals[i])
          xz.append(upend)
          yz.append(0.)
    if asbiggles:
      return biggles.FillBetween(x, y, xz, yz, color=color)
    else:
      return x, y, xz, yz

  # Draw the histogram as interpolated lines.
  def lines(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    x = [self.frame[0]]
    y = [self(self.frame[0])]
    for i in range(len(self.frame)-1):
      xmid = (self.frame[i] + self.frame[i+1])/2.
      x.append(xmid)
      y.append(self(xmid))
    x.append(self.high)
    y.append(self(self.high))
    if asbiggles:
      return biggles.Curve(x, y, linecolor=linecolor, linetype=linetype, linewidth=linewidth)
    else:
      return x, y

  # Shade under the interpolated lines, from low to high, if given.
  def linesfill(self, low=None, high=None, asbiggles=True, color=0xcccccc):
    if low == None: low = self.frame[0]
    if high == None: high = self.high
    if low > high: low, high = high, low
    x = []
    y = []
    xz = []
    yz = []
    for i in range(len(self.frame)):
      upend = self.high
      if i < len(self.frame)-1:
        upend = self.frame[i+1]
      if high > self.frame[i]:
        if self.frame[i] <= low and low < upend:
          x.append(low)
          y.append(self(low))
          xz.append(low)
          yz.append(0.)
        elif low < self.frame[i]:
          x.append(self.frame[i])
          y.append(self(self.frame[i]))
          xz.append(self.frame[i])
          yz.append(0.)
      mid = float(self.frame[i] + upend)/2.
      if low < mid and mid < high:
        x.append(mid)
        y.append(self(mid))
        xz.append(mid)
        yz.append(0.)
      if low < upend:
        if self.frame[i] < high and high <= upend:
          x.append(high)
          y.append(self(high))
          xz.append(high)
          yz.append(0.)
    if asbiggles:
      return biggles.FillBetween(x, y, xz, yz, color=color)
    else:
      return x, y, xz, yz

  # Draw the histogram as points
  def points(self, asbiggles=True, color=0x000000, symboltype="filled circle", symbolsize=0.5):
    x = []
    y = []
    for i in range(len(self.frame)-1):
      xmid = (self.frame[i] + self.frame[i+1])/2.
      x.append(xmid)
      y.append(self.vals[i])
    xmid = (self.frame[-1] + self.high)/2.
    x.append(xmid)
    y.append(self.vals[-1])
    if asbiggles:
      return biggles.Points(x, y, color=color, symbolsize=symbolsize, symboltype=symboltype)
    else:
      return x, y

  # Draw error bars
  def errorbars(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    x = []
    y = []
    err = []
    for i in range(len(self.frame)-1):
      xmid = (self.frame[i] + self.frame[i+1])/2.
      x.append(xmid)
      y.append(self.vals[i])
      err.append(self.errs[i])
    xmid = (self.frame[-1] + self.high)/2.
    x.append(xmid)
    y.append(self.vals[-1])
    err.append(self.errs[-1])
    if asbiggles:
      return biggles.SymmetricErrorBarsY(x, y, err, linecolor=linecolor, linetype=linetype, linewidth=linewidth)
    else:
      return x, y, err

  # Create a biggles plot with steps (default) and any other drawing option
  def plot(self, steps=True, stepscolor=None, lines=False, linescolor=None, points=False, errorbars=False):
    p = biggles.FramedPlot()
    p.xrange = (self.frame[0], self.high)
    ylow = min(self.vals)
    yhigh = max(self.vals)
    if lines or linescolor != None:
      ylow = min(ylow, self(self.frame[0]), self(self.high))
      yhigh = max(yhigh, self(self.frame[0]), self(self.high))
    if errorbars:
      ylow = min(self.vals - self.errs)
      yhigh = max(self.vals + self.errs)
    if ylow >= 0:
      ylow = 0
    else:
      ylow -= 0.1 * (yhigh - ylow)
    yhigh += 0.1 * (yhigh - ylow)
    if ylow == yhigh:
      ylow -= 1
      yhigh += 1
    p.yrange = (ylow, yhigh)
    if stepscolor != None:
      p.add(self.stepsfill(asbiggles=True, color=stepscolor))
    if linescolor != None:
      p.add(self.linesfill(asbiggles=True, color=linescolor))
    if steps:
      p.add(self.steps(asbiggles=True))
    if lines:
      p.add(self.lines(asbiggles=True))
    if points:
      p.add(self.points(asbiggles=True))
    if errorbars:
      p.add(self.errorbars(asbiggles=True))
    return p

  # Print out the histogram for a quick look (yay HPRINT!)
  def __repr__(self):
    retval = "%4s %8s %8s %8s\n" % ("chan", "low edge", "contents", "errors")
    retval += "%4s %8s %8g\n" % ("", "-oo", self.underflow)
    themax = max(self.vals)
    themin = min(self.vals)
    belowzero = 0.
    if themin < 0: belowzero = float(-themin)
    abovezero = 0.
    if themax > 0: abovezero = float(themax)
    if belowzero == 0. and abovezero == 0.:
      belowzero = 1.
      abovezero = 1.
    az = float(round(44.*abovezero/(abovezero+belowzero)))
    bz = 44. - az
    for i in range(len(self.frame)):
      bars = ""
      stars = 0
      if self.vals[i] < 0.:
        stars = int(round(bz*float(-self.vals[i])/belowzero))
      spaces = int(bz) - stars
      for j in range(spaces): bars += " "
      for j in range(stars): bars += "*"
      bars += "|"
      stars = 0
      if self.vals[i] > 0.:
        stars = int(round(az*float(self.vals[i])/abovezero))
      spaces = int(az) - stars
      for j in range(stars): bars += "*"
      for j in range(spaces): bars += " "
      retval += "%4d %8g %8g %8g %-45s\n" % (i, self.frame[i], self.vals[i], self.errs[i], bars)
    retval += "%4s %8g %8g %54s" % ("", self.high, self.overflow, "")
    return retval

class h1(h1frame):
  def __init__(self, bins=None, low=None, high=None, func=None, vals=None, errs=None, overflow=0., underflow=0., overflow_error=0., underflow_error=0.):
    if bins != None and not int(bins):
      raise TypeError, "bins must be an integer (or None)!"
    if low != None and not numberQ(low):
      raise TypeError, "low must be a real number (or None)!"
    if high != None and not numberQ(high):
      raise TypeError, "high must be a real number (or None)!"

    # assume the user wants integer spacing if not given
    if bins == None and int(low) and int(high):
      bins = high - low + 1
      low -= 0.5
      high += 0.5
    if int(bins) and low == None and high == None:
      low = -0.5
      high = bins + 0.5
      bins += 1

    if low > high: raise TypeError, "The lower bound ("+str(low)+") must be below the upper ("+str(high)+")."

    # I don't know what the user wants now
    if bins == None: bins = 100
    if low == None: low = 0.
    if high == None: high = 1.
    
    self.frame = Numeric.arange(low, high, float(high-low)/float(bins))
    if len(self.frame) > bins:
      self.frame = self.frame[:-1]

    self.regular = True
    self.high = high
    self.vals = Numeric.zeros(bins, 'd')
    self.errs = Numeric.zeros(bins, 'd')

    self.overflow = overflow
    self.underflow = underflow
    self.overflow_error = overflow_error
    self.underflow_error = underflow_error

    self.fill_factor = 1./float(self.high - self.frame[0])*float(len(self.frame))

    if func != None:
      self.setfunc(func)
    if vals != None:
      self.setvals(vals)
    if errs != None:
      self.seterrs(errs)
    return

##### PROF: error-on-mean profile ########################################

class profframe(h1frame):
  def __init__(self, frame, high=None, func=None, vals=None, errs=None):
    h1.__init__(self, frame, high, func, vals, errs)
    self.s = Numeric.zeros(len(self.frame), 'd')
    self.s2 = Numeric.zeros(len(self.frame), 'd')
    self.n = Numeric.zeros(len(self.frame), 'd')
    self.updated = True
    
  def update(self):
    for i in range(len(self.frame)):
      if self.n[i] > 0.:
        self.vals[i] = self.s[i] / self.n[i]
      else:
        self.vals[i] = 0.
      if self.n[i] > 0. and (self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2)) > 0.:
        self.errs[i] = math.sqrt((self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2)) / self.n[i])
      else:
        self.errs[i] = 0.
    self.updated = True

  def setfunc(self, func):
    self.updated = True
    return h1.setfunc(self, func)

  def setvals(self, vals):
    self.updated = True
    return h1.setvals(self, vals)

  def seterrs(self, errs):
    self.updated = True
    return h1.seterrs(self, errs)

  def __getitem__(self, i):
    if not self.updated: self.update()
    return h1.__getitem__(self, i)

  def __setitem__(self, i, v):
    if not self.updated: self.update()
    return h1.__setitem__(self, i, v)

  def __call__(self, x):
    if not self.updated: self.update()
    return h1.__call__(self, x)

  def __add__(self, other):
    if not self.updated: self.update()
    return h1.__add__(self, other)

  def __sub__(self, other):
    if not self.updated: self.update()
    return h1.__sub__(self, other)
  
  def __mul__(self, other):
    if not self.updated: self.update()
    return h1.__mul__(self, other)

  def __div__(self, other):
    if not self.updated: self.update()
    return h1.__div__(self, other)

  def divide_by_superset(self, other):
    if not self.updated: self.update()
    return h1.divide_by_superset(self, other)

  def divide_from_subset(self, other):
    if not self.updated: self.update()
    return h1.divide_from_subset(self, other)

  def map(self, func, deriv=None):
    if not self.updated: self.update()
    return h1.map(self, func, deriv)

  def merge(self, other):
    if (self.frame != other.frame):
      raise TypeError, "Cannot merge incompatible profiles.  (They are: "+str(self.frame)+" and "+str(other.frame)+".)"
    tmp = prof(len(self.frame), frame=self.frame)
    tmp.regular = self.regular or other.regular
    tmp.s = self.s + other.s
    tmp.s2 = self.s2 + other.s2
    tmp.n = self.n + other.n
    tmp.updated = False
    tmp.overflow = self.overflow + other.overflow
    tmp.underflow = self.underflow + other.underflow
    tmp.fill_factor = self.fill_factor
    return tmp
    
  def fill(self, x, y, weight=1.):
    if iterableQ(x) and iterableQ(y):
      for xi, yi in zip(x,y): self.fill(xi, yi, weight)
      self.updated = False
      return self

    elif numberQ(x) and numberQ(y):
      if x < self.frame[0]: self.underflow += weight
      elif x >= self.high: self.overflow += weight
      elif self.regular:
        i = int(math.floor((x - self.frame[0])*self.fill_factor))
        self.s[i] += y*weight
        self.s2[i] += math.pow(y,2)*weight
        self.n[i] += weight
      else:
        for i in range(1, len(self.frame)):
          if x < self.frame[i]:
            self.s[i-1] += y*weight
            self.s2[i-1] += math.pow(y,2)*weight
            self.n[i-1] += weight
            break
        if x >= self.frame[-1]:
          self.s[-1] += y*weight
          self.s2[-1] += math.pow(y,2)*weight
          self.n[-1] += weight
        self.updated = False

    else:
      raise TypeError, "Arguments x and y must be numbers or iterators of numbers."
    return self

  def sum(self, xlow=None, xhigh=None, overunderflow=False):
    if not self.updated: self.update()
    return h1.sum(self, xlow, xhigh, overunderflow)

  def sumerr(self, xlow=None, xhigh=None, overunderflow=False):
    if not self.updated: self.update()
    return h1.sumerr(self, xlow, xhigh, overunderflow)

  def int(self, xlow=None, xhigh=None):
    if not self.updated: self.update()
    return h1.int(self, xlow, xhigh)

  def interr(self, xlow=None, xhigh=None):
    if not self.updated: self.update()
    return h1.interr(self, xlow, xhigh)

  def width(self):
    return h1.width(self)

  def bins(self):
    return h1.bins(self)

  def rootn(self):
    print "This is totally not what you want."
    if not self.updated: self.update()
    return h1.rootn(self)

  def steps(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    if not self.updated: self.update()
    return h1.steps(self, asbiggles, linecolor, linetype, linewidth)

  def stepsfill(self, low = None, high = None, asbiggles=True, color=0xcccccc):
    if not self.updated: self.update()
    return h1.stepsfill(self, low, high, asbiggles, color)

  def lines(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    if not self.updated: self.update()
    return h1.lines(self, asbiggles, linecolor, linetype, linewidth)

  def linesfill(self, low=None, high=None, asbiggles=True, color=0xcccccc):
    if not self.updated: self.update()
    return h1.linesfill(self, low, high, asbiggles, color)

  def points(self, asbiggles=True, color=0x000000, symboltype=None, symbolsize=None):
    if not self.updated: self.update()
    return h1.points(self, asbiggles, color, symboltype, symbolsize)

  def errorbars(self, asbiggles=True, linecolor=0x000000, linetype="solid", linewidth=1):
    if not self.updated: self.update()
    return h1.errorbars(self, asbiggles, linecolor, linetype, linewidth)

  def plot(self, steps=False, stepscolor=None, lines=False, linescolor=None, points=True, errorbars=True):
    if not self.updated: self.update()
    return h1.plot(self, steps, stepscolor, lines, linescolor, points, errorbars)

  def __repr__(self):
    if not self.updated: self.update()
    return h1.__repr__(self)

class prof(profframe):
  def __init__(self, bins=None, low=None, high=None, func=None, vals=None, errs=None, overflow=0., underflow=0., overflow_error=0., underflow_error=0):
    if bins != None and not int(bins):
      raise TypeError, "bins must be an integer (or None)!"
    if low != None and not numberQ(low):
      raise TypeError, "low must be a real number (or None)!"
    if high != None and not numberQ(high):
      raise TypeError, "high must be a real number (or None)!"

    # assume the user wants integer spacing if not given
    if bins == None and int(low) and int(high):
      bins = high - low + 1
      low -= 0.5
      high += 0.5
    if int(bins) and low == None and high == None:
      low = -0.5
      high = bins + 0.5
      bins += 1

    if low > high: raise TypeError, "The lower bound ("+str(low)+") must be below the upper ("+str(high)+")."

    # I don't know what the user wants now
    if bins == None: bins = 100
    if low == None: low = 0.
    if high == None: high = 1.
    
    self.frame = Numeric.arange(low, high, float(high-low)/float(bins))
    if len(self.frame) > bins:
      self.frame = self.frame[:-1]

    self.regular = True
    self.high = high
    self.vals = Numeric.zeros(bins, 'd')
    self.errs = Numeric.zeros(bins, 'd')

    self.overflow = overflow
    self.underflow = underflow
    self.overflow_error = overflow_error
    self.underflow_error = underflow_error

    self.fill_factor = 1./float(self.high - self.frame[0])*float(len(self.frame))

    if func != None:
      self.setfunc(func)
    if vals != None:
      self.setvals(vals)
    if errs != None:
      self.seterrs(errs)

    self.s = Numeric.zeros(len(self.frame), 'd')
    self.s2 = Numeric.zeros(len(self.frame), 'd')
    self.n = Numeric.zeros(len(self.frame), 'd')
    self.updated = True

    return

##### PROFS: spread profile ##############################################

class profsframe(profframe):
  def update(self):
    for i in range(len(self.frame)):
      if self.n[i] > 0.:
        self.vals[i] = self.s[i] / self.n[i]
      else:
        self.vals[i] = 0.
      if self.n[i] > 0. and (self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2)) > 0.:
        self.errs[i] = math.sqrt(self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2))
      else:
        self.errs[i] = 0.
    self.updated = True

class profs(profsframe):
  def update(self):
    for i in range(len(self.frame)):
      if self.n[i] > 0.:
        self.vals[i] = self.s[i] / self.n[i]
      else:
        self.vals[i] = 0.
      if self.n[i] > 0. and (self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2)) > 0.:
        self.errs[i] = math.sqrt(self.s2[i]/self.n[i] - math.pow(self.s[i]/self.n[i], 2))
      else:
        self.errs[i] = 0.
    self.updated = True

##### SPECKLE: 2-d ntuple masquerading as a histogram ####################

class speckle:
  def __init__(self, x, y, xlow=None, xhigh=None, ylow=None, yhigh=None, mask=None):
    if isinstance(x, Numeric.ArrayType): self.x = x
    else: self.x = Numeric.array(x, 'd')
    if isinstance(y, Numeric.ArrayType): self.y = y
    else: self.y = Numeric.array(y, 'd')
    if xlow == None: xlow = min(x)
    if xhigh == None: xhigh = max(x)
    if ylow == None: ylow = min(y)
    if yhigh == None: yhigh = max(y)
    self.xlow = xlow
    self.xhigh = xhigh
    self.ylow = ylow
    self.yhigh = yhigh
    self.mask = mask
    
  def merge(self, other):
    tmpx = Numeric.empty(len(self.x) + len(other.x), 'd')
    tmpx[0:len(self.x)] = self.x
    tmpx[len(self.x):len(self.x)+len(other.x)] = other.x
    tmpy = Numeric.empty(len(self.y) + len(other.y), 'd')
    tmpy[0:len(self.y)] = self.y
    tmpy[len(self.y):len(self.y)+len(other.y)] = other.y
    mask = None
    if self.mask != None and other.mask != None:
      mask = lambda x,y: self.mask(x,y) or other.mask(x,y)
    elif self.mask != None:
      mask = self.mask
    elif other.mask != None:
      mask = other.mask
    return speckle(tmpx, tmpy, min(self.xlow, other.xlow), max(self.xhigh, other.xhigh), min(self.ylow, other.ylow), may(self.yhigh, other.yhigh), mask)

  def setmask(self, mask):
    self.mask = mask
    return self

  def unionmask(self, mask):
    tmp = self.mask
    if self.mask == None:
      tmp = lambda x,y: False
    self.mask = lambda x,y: tmp(x,y) or mask(x,y)
    return self

  def intersectionmask(self, mask):
    tmp = self.mask
    if self.mask == None:
      tmp = lambda x,y: True
    self.mask = lambda x,y: tmp(x,y) and mask(x,y)
    return self

  def complimentmask(self):
    tmp = self.mask
    if self.mask == None:
      tmp = lambda x,y: False
    self.mask = lambda x,y: not tmp(x,y)
    return self

  def sum(self, inmask=True):
    if inmask and self.mask != None:
      s = 0.
      for xi, yi in zip(self.x, self.y):
        if self.mask(xi, yi): s += 1.
      return s
    return len(self.x)

  def plotmask(self, divisions=100, color=(0.8, 0.8, 0.8)):
    raster = Numeric.ones((divisions,divisions,3), 'd')
    xfactor = (self.xhigh - self.xlow)/float(divisions)
    yfactor = (self.yhigh - self.ylow)/float(divisions)
    for i in range(int(divisions)):
      x = self.xlow + xfactor*(float(i) + 0.5)
      for j in range(int(divisions)):
        y = self.ylow + yfactor*(float(j) + 0.5)
        if self.mask(x,y):
          raster[i,j,0] = color[0]
          raster[i,j,1] = color[1]
          raster[i,j,2] = color[2]
    return biggles.Density(raster, ((self.xlow, self.ylow), (self.xhigh, self.yhigh)))

  def plotpoints(self, color=0x000000, symboltype="dot", symbolsize=1.):
    return biggles.Points(self.x, self.y, color=color, symbolsize=symbolsize, symboltype=symboltype)

  def plot(self, points=True, mask=True, divisions=100, pointscolor=0x000000, symboltype="dot", symbolsize=1., maskcolor=(0.8, 0.8, 0.8)):
    p = biggles.FramedPlot()
    p.xrange = (self.xlow, self.xhigh)
    p.yrange = (self.ylow, self.yhigh)
    if mask and self.mask != None:
      p.add(self.plotmask(divisions=divisions, color=maskcolor))
    if points:
      p.add(self.plotpoints(color=pointscolor, symbolsize=symbolsize, symboltype=symboltype))
    return p

##### H2: simple 2-d histogram ###########################################

# class h2:
#   def __init__(self, xbins, xlow, xhigh, ybins, ylow, yhigh):
    
