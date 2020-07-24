# execfile("/home/mccann/bin/python/jimtools.py")
# p = pyxplot.PyxPlot("whatever")

from __future__ import division
import pyxplot
import rootntuple
# import minuit
from math import *
from pyx import *
import cPickle as pickle

def mean(xlist):
  """Takes a list of values and returns the mean."""
  s = 0.
  for x in xlist:
    s += x
  return s/float(len(xlist))

def rms(xlist):
  """Takes a list of values and returns the root mean square (not standard deviation)."""
  s2 = 0.
  for x in xlist:
    s2 += x**2
  return sqrt(s2/float(len(xlist)))

def stdev(xlist):
  """Takes a list of values and returns the standard deviation."""
  s = 0.
  s2 = 0.
  for x in xlist:
    s += x
    s2 += x**2
  return sqrt(s2/float(len(xlist)) - (s/float(len(xlist)))**2)

def wmean(xlist):
  """Takes a list of (value, error) pairs and returns (weighted mean, its error).  Values with non-positive errors are ignored (dropped from the list)."""
  s = 0.
  w = 0.
  for (x,e) in xlist:
    if e > 0:
      wi = 1.0/float(e)**2
      s += x*wi
      w += wi
  return s/w, sqrt(1.0/w)

def corr(xlist, ylist):
  """Takes two lists and returns the correlation coefficient of these lists."""

  if len(xlist) != len(ylist):
    raise ValueError, "Lists must have the same length."

  xmean = mean(xlist)
  ymean = mean(ylist)
  ssxx = 0.
  ssyy = 0.
  ssxy = 0.
  for x, y in zip(xlist, ylist):
    ssxx += (x - xmean)**2
    ssyy += (y - ymean)**2
    ssxy += (x - xmean) * (y - ymean)

  return ssxy / sqrt(ssxx * ssyy)

##############################################################

def ibin(low, high): return (high-low+1, low-0.5, high+0.5)

class hist:
  def __init__(self, bins, low, high):
    self.bins = int(bins)
    self.low = float(low)
    self.high = float(high)
    self.values = [0.]*bins
    self.errors = [0.]*bins
    self.overflow = 0.
    self.overflow_error = 0.
    self.underflow = 0.
    self.underflow_error = 0.
    self.fill_factor = 1./float(high - low)*float(bins)

  def ntuple(self, ntuple, function, filter=None, start=None, stop=None, step=None):
    if not isinstance(ntuple, rootntuple.RootNtuple):
      raise TypeError, "Please supply a RootNtuple object."

    dicthist = ntuple.bin(self.bins, self.low, self.high, function, filter, start, stop, step)

    self.values = dicthist["values"]
    self.errors = dicthist["errors"]
    self.overflow, self.overflow_error = dicthist["overflow"], dicthist["overflow_error"]
    self.underflow, self.underflow_error = dicthist["underflow"], dicthist["underflow_error"]

    return self

  def plot(self, logy=False):
    return pyxplot.PyxHist(self.low, self.high, self.values, self.errors, self.overflow, self.overflow_error, self.underflow, self.underflow_error, logy=logy)

  def fillmany(self, x, weight=None):
    if "__iter__" in dir(x) or type(x) == list or type(x) == tuple:
      if "__iter__" in dir(weight) or type(weight) == list or type(weight) == tuple:
        for xi, wi in zip(x, weight):
          self.fill(xi, wi)
      elif weight != None:
        raise TypeError, "Argument weight must be iterable, a list, a tuple, or None."
      else:
        for xi in x:
          self.fill(xi)
    else:
      raise TypeError, "Argument x must be iterable, a list, or a tuple."

  def fill(self, x, weight=None):
    w = 1.
    if weight != None: w = float(weight)
    if x >= self.high: self.overflow += w
    elif x < self.low: self.underflow += w
    else:
      self.values[int(floor((x - self.low)*self.fill_factor))] += w

  def rootn(self):
    for i in range(0, self.bins):
      self.errors[i] = sqrt(self.values[i])
    self.overflow_error = sqrt(self.overflow)
    self.underflow_error = sqrt(self.underflow)

  def do_operations(self, other, do_one, op):
    out = hist(self.bins, self.low, self.high)

    if isinstance(other, hist):
      if self.bins != other.bins or self.low != other.low or self.high != other.high:
        raise ValueError, "Can't "+op+" histograms with different frames."

      for i in range(self.bins):
        out.values[i], out.errors[i] = do_one(self.values[i], other.values[i], self.errors[i], other.errors[i])
      out.overflow, out.overflow_error = do_one(self.overflow, other.overflow, self.overflow_error, other.overflow_error)
      out.underflow, out.underflow_error = do_one(self.underflow, other.underflow, self.underflow_error, other.underflow_error)

    else:
      for i in range(self.bins):
        out.values[i], out.errors[i] = do_one(self.values[i], other, self.errors[i], 0.)
      out.overflow, out.overflow_error = do_one(self.overflow, other, self.overflow_error, 0.)
      out.underflow, out.underflow_error = do_one(self.underflow, other, self.underflow_error, 0.)

    return out

  def __add__(self, other):
    def do_one(s, o, se, oe):
      try:
        return s + o, sqrt(se**2 + oe**2)
      except ZeroDivisionError:
        return 0., 0.
    return self.do_operations(other, do_one, "add")

  def __sub__(self, other):
    def do_one(s, o, se, oe):
      try:
        return s - o, sqrt(se**2 + oe**2)
      except ZeroDivisionError:
        return 0., 0.
    return self.do_operations(other, do_one, "subtract")

  def __mul__(self, other):
    def do_one(s, o, se, oe):
      try:
        return s * o, (s*o)*sqrt(se**2/s**2 + oe**2/o**2)
      except ZeroDivisionError:
        return 0., 0.
    return self.do_operations(other, do_one, "multiply")

  def __div__(self, other):
    def do_one(s, o, se, oe):
      try:
        return s / o, (s/o)*sqrt(se**2/s**2 + oe**2/o**2)
      except ZeroDivisionError:
        return 0., 0.
    return self.do_operations(other, do_one, "divide")

  def bin_lowedges(self):
    output = []
    width = (self.high - self.low)/float(self.bins)
    x = self.low
    for i in range(0, self.bins):
      output.append(x)
      x += width
    return output

  def bin_centers(self):
    output = []
    width = (self.high - self.low)/float(self.bins)
    x = self.low + width/2.
    for i in range(0, self.bins):
      output.append(x)
      x += width
    return output

  def bin_highedges(self):
    output = []
    width = (self.high - self.low)/float(self.bins)
    x = self.low + width
    for i in range(0, self.bins):
      output.append(x)
      x += width
    return output

