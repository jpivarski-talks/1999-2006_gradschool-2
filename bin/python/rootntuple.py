import _rootntuple

class RootDir:
  def __init__(self, filename):
    """Create a RootDir from a filename or internal object.

    Arguments: name of the ROOT file (or an object of type _rootntuple.RootDir)

    Opens a file which is not closed by deleting the object, so that
    the following syntax will work:

        ntuple = RootDir(filename).get(directoryname).get(ntuplename)

    ROOT features such as network files should work, if you supply the
    appropriate filename prefix.

    The user is not meant to play with _rootntuple.RootDir objects."""

    if isinstance(filename, _rootntuple.RootDir): self.internal = filename
    else: self.internal = _rootntuple.RootDir(filename)

  def list(self):
    """Get a listing of ROOT objects in this directory level.

    Arguments: none
    Returns: a dictionary mapping object names to ROOT object types."""

    return self.internal.list()

  def get(self, name):
    """Extract a directory, ntuple, or histogram from this directory level.

    Arguments: name of the ROOT object
    Returns: a RootDir (from TDirectory), RootNtuple (from TNtuple),
             or RootHist (from TH1F, TProfile, or TH2F)

    If you try to extract an unsupported object, you will get a
    NotImplementedError."""

    obj = self.internal.get(name)
    if isinstance(obj, _rootntuple.RootDir): return RootDir(obj)
    elif isinstance(obj, _rootntuple.RootNtuple): return RootNtuple(obj)
    elif isinstance(obj, _rootntuple.RootHist): return RootHist(obj)
    else: raise NotImplementedError  # this should have already happened in the internal get()

  def ls(self):
    """Print out a listing in ROOT format.

    Arguments: none
    Returns: None"""

    self.internal.ls()
    return None

  def path(self):
    """Get the ROOT path string which represents this object.

    Arguments: none
    Returns: path string"""

    return self.internal.path()

  def closefile(self):
    """Explicitly close the ROOT file.

    Arguments: none
    Returns: None

    If you have other objects associated with this file, they will all
    break after you call this."""

    self.internal.closefile()
    return None

#################################################################

class RootHist:
  def __init__(self, obj):
    """Create a RootHist from an internal object.

    RootHist objects have a member generic, which is a dictionary of
    the following information (and therefore a completely generic
    histogram, for the purpose of translating into your favorite
    framework):
        dimensions       1 for TH1F and TProfile, 2 for TH2F

        if dimensions == 1:
            mean             the distribution mean, determined at filling time
            mean_error       its uncertainty
            rms              the distribution STANDARD DEVIATION, determined at filling time
            rms_error        its uncertainty
            entries          the number of times `fill' was called

            values           a list of bin values
            errors           a list of bin uncertainties (sqrt(N) by default in ROOT)
            overflow         the value of the overflow bin
            overflow_error   its uncertainty
            underflow        the value of the underflow bin
            underflow_error  its uncertainty

            bins             number of bins
            low              the threshold of the low edge
            high             the threshold of the high edge
            bin_lowedges
            bin_centers      lists of bin thresholds
            bin_highedges

        else:
            meanX            the mean in the X direction
            meanX_error      its uncertainty
            meanY            the mean in the Y direction
            meanY_error      its uncertainty
            rmsX             the distribution standard deviation (same for Y)
            rmsX_error       its uncertainty
            entries          the number of times `fill' was called

            values           a two-dimensional list of bin values
            errors           a two-dimensional list of bin uncertainties
                             unfortunately, no over/underflow information is available
                             because I don't know how to extract that from ROOT

            bins             a tuple of binsX, binsY
                             unfortunately, no lowX, highX, lowY, highY information is
                             available, because I don't know how to extract that

    The user is not meant to execute this function."""

    self.internal = obj

    g = self.generic = {}
    if type(obj.mean()[0]) == tuple:  # this is a 2D histogram (TH2F); some things don't work
      (g["meanX"], g["meanX_error"]), (g["meanY"], g["meanY_error"]) = obj.mean()
      (g["rmsX"], g["rmsX_error"]), (g["rmsY"], g["rmsY_error"]) = obj.rms()
      g["entries"] = obj.entries()
      g["values"] = obj.values()
      g["errors"] = obj.errors()
      g["bins"] = len(g["values"]), len(g["values"][0])
      self.options = "colz"
    else:
      g["mean"], g["mean_error"] = obj.mean()
      g["rms"], g["rms_error"] = obj.rms()
      g["entries"] = obj.entries()
      g["values"] = obj.values()
      g["errors"] = obj.errors()
      g["overflow"], g["underflow"] = obj.ouvalues()
      g["overflow_error"], g["underflow_error"] = obj.ouerrors()
      g["bin_lowedges"] = obj.bins(-1)
      g["bin_centers"] = obj.bins(0)
      g["bin_highedges"] = obj.bins(1)
      g["bins"] = len(g["bin_centers"])
      g["low"] = g["bin_lowedges"][0]
      g["high"] = g["bin_highedges"][-1]
      self.options = ""

    self.log = False

  def redraw(self, options=None, log=None):
    """Draw or redraw the histogram in its own ROOT canvas.

    Optional: options --- a ROOT options string
              log --- plot in logscale if True
    Returns: None

    Aliased to draw and plot.

    If options or log are not specified, member data will be used."""

    if options == None: options = self.options
    if log == None: log = self.log
    
    self.internal.log = log
    self.internal.redraw(options)
    return None

  def draw(self, options=None, log=None):
    """See redraw()."""

    return self.redraw(options, log)

  def plot(self, options=None, log=None):
    """See redraw()."""

    return self.redraw(options, log)

  def postscript(self, filename):
    """Write the current plot out to a PS/EPS file.

    Arguments: name of the output file, with extension
    Returns: None

    If the file extension is ".eps", the postscript will be encapsulated;
    if the file extension is ".ps", it will not."""

    self.internal.postscript(filename)
    return None

  def closewindow(self):
    """TRY to close the histogram's window.

    Arguments: none
    Returns: None

    Perhaps the threaded window updater will close it, after 1 second."""

    self.internal.closewindow()

#################################################################

class RootNtuple:
  def __init__(self, source, start=None, stop=None, step=None):
    """Construct a ROOT ntuple chain from a ROOT path, a list of RootNtuples, or from an internal object.

    """

    # Get the ntuple from an internal object
    if isinstance(source, _rootntuple.RootNtuple):
      self.internal = [source]

    # Get the ntuple from a list of RootNtuple objects
    elif "__iter__" in source or type(source) == list or type(source) == tuple:
      self.internal = []

      for s in source:
        if isinstance(s, RootNtuple):
          for si in s.internal:
            self.internal.append(si)

        elif isinstance(s, _rootntuple.RootNtuple):
          self.internal.append(s)

        else:
          raise TypeError, "The list must contain only RootNtuple objects (internal or public)."

    # Get the ntuple from a string ROOT path
    elif type(source) == str:
      import os, re
      
      names = re.split(re.compile(":"), source)

      # Expand file lists with `ls'
      if len(names) == 2 and names[0] != "" and names[1] != "":
        self.internal = []
        
        dirs = re.split(re.compile("/"), names[1])
        for filename in os.popen("ls "+names[0]).readlines():
          stuff = _rootntuple.RootDir(filename[0:-1])
          for d in dirs:
            if d != "": stuff = stuff.get(d)
          if isinstance(stuff, _rootntuple.RootNtuple):
            self.internal.append(stuff)
          else:
            raise ValueError, "Not an ntuple: "+filename[0:-1]+":"+names[1]

      # Don't expand file lists with `ls' (could be a network file)
      elif len(names) == 3 and names[0] != "" and names[1] != "" and names[2] != "":

        dirs = re.split(re.compile("/"), names[2])
        stuff = _rootntuple.RootDir(names[0]+":"+names[1])
        for d in dirs:
          if d != "": stuff = stuff.get(d)
        if isinstance(stuff, _rootntuple.RootNtuple):
          self.internal = [stuff]
        else:
          raise ValueError, "Not an ntuple: "+source

      # Fail
      else:
        raise ValueError, "ROOT path format is filename:/dir1/dir2/nt1"

    # Fail
    else:
      raise TypeError, "This source is neither a string, a list of RootNtuples, or an internal object."

    # Get the largest subset of variable names, in the right order
    # If you can find a way to protect these attributes, do so.
    self.labels = self.internal[0].list()
    for i in self.internal[1:]:
      labels2 = i.list()
      survive = []
      for l in self.labels:
        if l in labels2: survive.append(l)
      self.labels = survive

    # Count the total number of entries
    # If you can find a way to protect these attributes, do so.
    self.entries = 0
    self.indexmap = []
    for inter in self.internal:
      self.indexmap.append(self.entries)
      self.entries += inter.allentries()

    # Set up public members
    self.start = 0
    self.stop = self.entries
    self.step = 1
    self.i = 0  # this iterates over ntuples
    self.optimize = None

    self.frequency = 1000
    self.canvas_size = 500, 500
    self.profiletype = ""
    self.options = ""
    self.options2 = "colz"
    self.log = False
    self.last2d = False

    self.leftloss = 0.01
    self.toploss = 0.01
    self.rightloss = 0.01
    self.bottomloss = 0.01
    self.padding = 0.10
    self.sample = 1000
    
    self.filter = None

  def __add__(self, other):
    """Combine RootNtuple chains into a bigger chain."""

    return RootNtuple(self.internal + other.internal)

  def global_to_local_index(self, index):
    """Translate a RootNtuple index into an internal object and its index.

    The user is not meant to call this function."""

    for i in range(0, len(self.indexmap)):
      if i == len(self.indexmap)-1 or self.indexmap[i] <= index < self.indexmap[i+1]:
        if index - self.indexmap[i] > self.internal[i].allentries(): raise ValueError
        return i, index - self.indexmap[i]
      
  def local_to_global_index(self, mapi, index):
    """Translate an internal object and its index into a RootNtuple index.

    The user is not meant to call this function."""

    if mapi > len(self.indexmap)-1 or mapi < 0: raise ValueError

    glob = 0
    for i in range(0, mapi): glob += self.internal[i].allentries()
    glob += index
    return glob

  def setup_sss(self, start=None, stop=None, step=None):
    """Set up self, stop, and step for all internal objects.

    The user is not meant to call this function."""

    if start == None: start = self.start
    if stop == None: stop = self.stop
    if step == None: step = self.step

    # Make sure start, stop, and step are reasonable
    if (type(start) != int and type(start) != long) or start < 0:
      raise ValueError, "Member `start' must be a nonnegative integer."

    if (type(stop) != int and type(stop) != long) or stop < 0 or stop > self.entries or stop < start:
      raise ValueError, "Member `stop' must be a nonnegative integer less than or equal to `entries' and greater than or equal to `start'."

    if (type(step) != int and type(step) != long) or step < 1:
      raise ValueError, "Member `step' must be a positive integer."

    # Set up start, stop, and step on each internal object to simulate
    # one global object
    for inter in self.internal:
      inter.start = 0
      inter.stop = 0
      inter.step = step

    starti, startindex = self.global_to_local_index(start)
    stopi, stopindex = self.global_to_local_index(stop)

    self.internal[starti].start = startindex
    self.internal[stopi].stop = stopindex

    for i in range(starti, stopi): # includes starti, excludes stopi
      self.internal[i].stop = self.internal[i].allentries()

    justtheonesyouuse = self.internal[starti].allentries() - startindex
    for i in range(starti+1, stopi+1): # excludes starti, includes stopi
      self.internal[i].start = justtheonesyouuse % step
      justtheonesyouuse += self.internal[i].allentries()
    
    return start, stop, step

  def compile_function(self, function, singleton_okay=True):
    """Compiles a string into a callable lambda function.

    Arguments: function may be a string or a callable
    Returns: a callable or single variable string

    If function is already callable, it is returned unchanged.

    If function is a single variable string, it is returned unchanged,
    because internal ntuple objects use this directly to avoid the
    overhead involved in "lambda x: x".  (Only if singleton_okay.)

    The user is not meant to call this function."""

    if type(function) == str:
      compiled_code = compile(function, "<string>", "eval")
      if not singleton_okay or compiled_code.co_names != (function,):
        names = []
        for n in compiled_code.co_names:
          if n in self.labels:
            names.append(n)
        function = lambda *args: eval(compiled_code, dict(zip(names, args)))
        function.varnames = tuple(names)

    elif callable(function):
      compiled_code = function.func_code
      function.varnames = compiled_code.co_varnames[0:compiled_code.co_argcount]

    else:
      raise TypeError, "Function must be callable or a string than can be compiled into a callable."

    return function

  def compile_functions(self, function):
    """Compiles strings into a callable lambda function.

    Arguments: function may be a string, a tuple of two strings, or a callable
    Returns: a callable or single variable string

    If function is already callable, it is returned unchanged.

    If both elements of function are single variable strings, they are
    returned unchanged, because internal ntuple objects use this
    directly to avoid the overhead involved in "lambda x: x".

    The user is not meant to call this function."""

    if type(function) == str:
      function = self.compile_function(function, False)
    
    elif type(function) == tuple and len(function) == 2:
      left = self.compile_function(function[0], True)
      right = self.compile_function(function[1], True)

      if callable(left) or callable(right):
        left = self.compile_function(function[0], False)
        right = self.compile_function(function[1], False)
        names = left.varnames + right.varnames
        function = lambda *args: (left(*args[:len(left.varnames)]), \
                                  right(*args[len(left.varnames):]))
        function.varnames = names

    elif callable(function):
      compiled_code = function.func_code
      function.varnames = compiled_code.co_varnames[0:compiled_code.co_argcount]

    else:
      raise TypeError, "Function must be callable or a string than can be compiled into a callable."
    return function

#################################################################

  def list(self):
    """Get a listing of ntuple variable names.

    Arguments: none
    Returns: a list of strings

    If ntuples in the chain have different sets of variables, this is
    the largest subset.

    This is a synonym for self.labels."""

    return self.labels

  def range(self, *args):
    """Set start, stop, and step the same way one would construct a python range.

    Optional: [start,] stop[, step]
    Returns: None (changes RootNtuple's state)

    Missing arguments return to the defaults: 0, entries, 1."""

    if len(args) == 0:
      self.start, self.stop, self.step = 0, self.entries, 1

    elif len(args) == 1:
      self.start, self.stop, self.step = 0, args[0], 1

    elif len(args) == 2:
      self.start, self.stop, self.step = args[0], args[1], 1

    elif len(args) == 3:
      self.start, self.stop, self.step = args[0], args[1], args[2]

    else:
      raise TypeError, "Too many arguments."

  def __getitem__(self, index):
    """Return one item from the ntuple with random access.

    Arguments: index --- must be between 0 and entries
    Returns: an internal RootNtupleEntry object

    Use it like this: ntuple[55].varname."""

    if index < 0:
      raise NotImplementedError, "RootNtuple doesn't support fancy python indexing."
    elif index >= self.entries:
      raise IndexError, "This ntuple only contains %d values." % (self.entries,)

    i, loc = self.global_to_local_index(index)
    return self.internal[i].entry(loc)

  def count(self, filter, start=None, stop=None, step=None):
    """Count entries subject to filter, start, stop, and step.

    Arguments: filter function --- may be a string ("x > y") or a
               callable (lambda x, y: x > y, predefined_func), but
               argument names must be ntuple labels.
               Arbitrary python code/global variables may be referenced.
               Must return True or False.

               If None, all events will be counted (faster than lambda: True)

    Optional: start, stop, step --- control entry range;
              Defaults are 0, entries, 1.

    Returns: number of entries.

    Optional arguments, if unspecified, default to member data.
    Note that this DOESN'T include filter."""
    
    if filter != None: filter = self.compile_function(filter)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)

    for v in ["filter"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    total = 0
    for inter in self.internal:
      total += inter.count()
    return total

  def bounds(self, variables, filter=None, start=None, stop=None, step=None):
    """Determine variable max/minima subject to filter, start, stop, and step.

    Arguments: variables --- list of strings (like self.labels)
               A string will be interpreted as a singleton.

    Optional: filter function --- may be a string ("x > y") or a
              callable (lambda x, y: x > y, predefined_func), but
              argument names must be ntuple labels.
              Arbitrary python code/global variables may be referenced.
              Must return True or False.

              start, stop, step --- control entry range;
              Defaults are 0, entries, 1.

    Returns: a dictionary of variable name --> (lower, upper) pairs

    Optional arguments, if unspecified, default to member data.
    Note that this INCLUDES the filter function."""
    
    if type(variables) == str: variables = [variables]

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)

    for v in ["filter"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    output = self.internal[0].bounds(variables)
    for inter in self.internal[1:]:
      for (varname, (low, high)) in inter.bounds(variables).items():
        revised = list(output[varname])
        if low < revised[0]: revised[0] = low
        if high > revised[1]: revised[1] = high
        output[varname] = tuple(revised)
    return output

  def map(self, function, filter=None, output=False, start=None, stop=None, step=None):
    """Apply a function to each entry subject to filter, start, stop, and step.

    Arguments: function to be called --- argument names must be ntuple
               labels, but arbitrary python code/globals may be referenced.
               Must be callable or a string; strings are compiled into
               lambda expressions.

    Optional: filter function --- may be a string ("x > y") or a
              callable (lambda x, y: x > y, predefined_func), but
              argument names must be ntuple labels.
              Arbitrary python code/global variables may be referenced.
              Must return True or False.

              output --- if True, return a list of function output
              Defaults to False.

              start, stop, step --- control entry range;
              Defaults are 0, entries, 1.

    Returns: None or a list of function output, depending on `output'."""

    function = self.compile_function(function, singleton_okay=False)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)

    for v in ["filter"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    if output: out = []
    for inter in self.internal:
      tmp = inter.map(function, output)
      if output: out += tmp

    if output: return out
    return None

  def __iter__(self):
    """Get ready to iterate.

    This is meant to be called automatically by a for statement:
        for n in ntuple:
            print n.varname

    The filter function's weight output can be accessed by n._weight

    It is less efficient than the specialized functions because it has
    to read all ntuple variables.

    UNLESS you set ntuple.optimize to a list of variable names, in
    which case it will only extract those (and whatever the filter
    function needs).  (About a factor of 2 speedup.)"""
    
    self.setup_sss()
    if self.filter != None:
      filter = self.compile_function(self.filter)
    else:
      filter = None

    for inter in self.internal:
      inter.filter = filter
      inter.optimize = self.optimize
      iter(inter)
    self.i = 0
    return self

  def next(self):
    """Iterate.

    This is meant to be called automatically by a for statement:
        for n in ntuple:
            print n.varname

    The filter function's weight output can be accessed by n._weight

    It is less efficient than the specialized functions because it has
    to read all ntuple variables.

    UNLESS you set ntuple.optimize to a list of variable names, in
    which case it will only extract those (and whatever the filter
    function needs).  (About a factor of 2 speedup.)"""
    
    try:
      return self.internal[self.i].next()
    except StopIteration:

      if self.local_to_global_index(self.i, self.internal[self.i].i) >= self.stop:
        raise StopIteration

      self.i += 1
      if self.i >= len(self.internal):
        raise StopIteration
      
      return self.next()

  def bin(self, bins, low, high, function, filter=None, start=None, stop=None, step=None):
    """Bin a histogram from a function of ntuple variables.

    Arguments: bins, low, high --- histogram specification
               
               function to be plotted --- may be a string ("x+y", "x")
               or a callable (lambda x, y: x+y, predefined_func).
               Argument names must be ntuple labels, but arbitrary
               python code/globals may be referenced.
               Must evaluate to a number.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

    Returns: a dictionary with the following entries
             "values" --- a list of histogram values
             "errors" --- sqrt(N) errors
             "overflow", "overflow_error" --- the overflow bin
             "underflow", "underflow_error" --- the underflow bin
             "bins" --- number of bins
             "width" --- width of one bin
             "bin_lowedges"
             "bin_centers"   --- the generated edge placement
             "bin_highedges"
             
    Meant to be the correct way to bin a histogram and send it off to
    another package for plotting.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname."""

    import math

    if (type(bins) != int and type(bins) != long) or bins < 1:
      raise ValueError, "Argument bins must be a positive integer."
    if low >= high: raise ValueError, "Argument low must be less than high."

    h = {"bins": bins, "width": (float(high)-float(low))/float(bins), \
         "bin_lowedges": [], "bin_centers": [], "bin_highedges": []}

    x = low
    for i in range(bins):
      h["bin_lowedges"].append(x)
      x += h["width"]/2.
      h["bin_centers"].append(x)
      x += h["width"]/2.
      h["bin_highedges"].append(x)

    function = self.compile_function(function)
    quick = False
    if type(function) == str: quick = True

    values = h["values"] = [0.] * bins
    h["errors"] = [0.] * bins
    h["overflow"] = 0. ; h["overflow_error"] = 0.
    h["underflow"] = 0. ; h["underflow_error"] = 0.

    fill_factor = 1./float(high - low)*float(bins)

    tmp_filter = self.filter
    tmp_start = self.start
    tmp_stop = self.stop
    tmp_step = self.step
    tmp_optimize = self.optimize

    if filter != None: self.filter = filter
    if start != None: self.start = start
    if stop != None: self.stop = stop
    if step != None: self.step = step
    if quick: self.optimize = [function]
    else: self.optimize = function.varnames

    if quick:
      compiled = compile("n."+function, "<string>", "eval")
    else:
      compiled = []
      for name in function.varnames:
        compiled.append(compile("n."+name, "<string>", "eval"))

    for n in self:
      if quick:
        x = eval(compiled)
      else:
        args = []
        for c in compiled:
          args.append(eval(c))
        x = function(*tuple(args))

      if x >= high: h["overflow"] += n._weight
      elif x < low: h["underflow"] += n._weight
      else: values[int(math.floor((x - low)*fill_factor))] += n._weight

    for i in range(len(h["values"])):
      h["errors"][i] = math.sqrt(h["values"][i])

    h["overflow_error"] = math.sqrt(h["overflow"])
    h["underflow_error"] = math.sqrt(h["underflow"])

    self.filter = tmp_filter
    self.start = tmp_start
    self.stop = tmp_stop
    self.step = tmp_step
    self.optimize = tmp_optimize
    return h

####be#afraid#be#very#afraid#####################################

  def plot(self, function, filter=None, start=None, stop=None, step=None, sample=None, leftloss=None, rightloss=None, padding=None, options=None, frequency=None, log=None, canvas_size=None):
    """Auto-bin and plot a function of ntuple variables.

    Arguments: function to be plotted --- may be a string ("x+y", "x")
               or a callable (lambda x, y: x+y, predefined_func).
               Argument names must be ntuple labels, but arbitrary
               python code/globals may be referenced.
               Must evaluate to a number.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              sample --- number of good entries to use in determining
              histogram range and binning (good means passing filter).
              Default is 1000.

              leftloss, rightloss --- fraction of events you're
              willing to use in determining the range (can be 0).
              Useful if distribution has a few extreme outliers.
              Expressed as a fraction of total area.
              Default is 0.01 == 1%.

              padding --- extra left/right margins for aesthetics.
              Expressed as a fraction of the x range.
              Default is 0.1 == 10%.

              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: chosen histogram bounds (bins, low, high) for continuous
             distributions and (min, max) for integer distributions

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To histogram with explicit bins and ranges, use plotbin or plotint.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, bin, simple iteration)
    for later work in another package.

    I painted myself into a corner in this design.
        1. Only the first ntuple in the chain can be used to determine
           histogram bounds, no matter how large `sample' is.
        2. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_function(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "sample", "leftloss", "rightloss", "padding", \
              "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    output = self.internal[i].plot(function, sample, leftloss, rightloss, padding, options, frequency, None, start, stop, self.indexmap[i])
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.plot(function, 0, leftloss, rightloss, padding, options, frequency, master)
    return output

  def plotbin(self, bins, low, high, function, filter=None, start=None, stop=None, step=None, options=None, frequency=None, log=None, canvas_size=None):
    """Bin and plot a function of ntuple variables.

    Arguments: bins, low, high --- histogram specification
               
               function to be plotted --- may be a string ("x+y", "x")
               or a callable (lambda x, y: x+y, predefined_func).
               Argument names must be ntuple labels, but arbitrary
               python code/globals may be referenced.
               Must evaluate to a number.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: None

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To auto-bin histogram, use plot.  To bin a histogram of integers,
    use plotint.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_function(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].plotbin(function, bins, low, high, options, frequency, None)
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.plotbin(function, bins, low, high, options, frequency, master)
    return None

  def plotint(self, min, max, function, filter=None, start=None, stop=None, step=None, options=None, frequency=None, log=None, canvas_size=None):
    """Bin and plot a integer function of ntuple variables.

    Arguments: min, max --- integer histogram specification (inclusive)
               
               function to be plotted --- may be a string ("x+y", "x")
               or a callable (lambda x, y: x+y, predefined_func).
               Argument names must be ntuple labels, but arbitrary
               python code/globals may be referenced.
               Must evaluate to a number.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: None

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To auto-bin histogram, use plot.  To bin a continuous histogram,
    use plotbin.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_function(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].plotint(function, min, max, options, frequency, None)
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.plotint(function, min, max, options, frequency, master)
    return None

  def profile(self, function, filter=None, start=None, stop=None, step=None, sample=None, leftloss=None, rightloss=None, padding=None, profiletype=None, options=None, frequency=None, log=None, canvas_size=None):
    """Auto-bin and profile a function of ntuple variables.

    Arguments: function to be plotted --- may be a string ("x+y, y"),
               a tuple of two strings ("x+y", "y") or a callable
               (lambda x, y: x+y, y, predefined_func).  Argument names
               must be ntuple labels, but arbitrary python
               code/globals may be referenced.
               Must evaluate to a pair of numbers for X and Y.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              sample --- number of good entries to use in determining
              histogram range and binning (good means passing filter).
              Default is 1000.

              leftloss, rightloss --- fraction of events you're
              willing to use in determining the range (can be 0).
              Useful if distribution has a few extreme outliers.
              Expressed as a fraction of total area.
              Default is 0.01 == 1%.

              padding --- extra left/right margins for aesthetics.
              Expressed as a fraction of the x range.
              Default is 0.1 == 10%.

              profiletype --- ROOT profile type ("" error on mean, "s" spread)
              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: chosen histogram bounds (bins, low, high) for continuous
             distributions and (min, max) for integer distributions

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To histogram with explicit bins and ranges, use profilebin or profileint.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. Only the first ntuple in the chain can be used to determine
           histogram bounds, no matter how large `sample' is.
        2. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_functions(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "sample", "leftloss", "rightloss", "padding", \
              "profiletype", "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    output = self.internal[i].profile(function, sample, leftloss, rightloss, padding, profiletype, options, frequency, None, start, stop, self.indexmap[i])
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.profile(function, 0, leftloss, rightloss, padding, options, profiletype, frequency, master)
    return output

  def profilebin(self, bins, low, high, function, filter=None, start=None, stop=None, step=None, profiletype=None, options=None, frequency=None, log=None, canvas_size=None):
    """Bin and profile a function of ntuple variables.

    Arguments: bins, low, high --- histogram specification
               
               function to be plotted --- may be a string ("x+y, y"),
               a tuple of two strings ("x+y", "y") or a callable
               (lambda x, y: x+y, y, predefined_func).  Argument names
               must be ntuple labels, but arbitrary python
               code/globals may be referenced.
               Must evaluate to a pair of numbers for X and Y.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              profiletype --- ROOT profile type ("" error on mean, "s" spread)
              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: None

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To auto-bin histogram, use profile.  To bin a histogram of integers,
    use profileint.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_functions(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "profiletype", "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].profilebin(function, bins, low, high, profiletype, options, frequency, None)
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.profilebin(function, bins, low, high, profiletype, options, frequency, master)
    return None

  def profileint(self, min, max, function, filter=None, start=None, stop=None, step=None, profiletype=None, options=None, frequency=None, log=None, canvas_size=None):
    """Bin and profile a integer function of ntuple variables.

    Arguments: min, max --- integer histogram specification (inclusive)
               
               function to be plotted --- may be a string ("x+y, y"),
               a tuple of two strings ("x+y", "y") or a callable
               (lambda x, y: x+y, y, predefined_func).  Argument names
               must be ntuple labels, but arbitrary python
               code/globals may be referenced.
               Must evaluate to a pair of numbers for X and Y.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              profiletype --- ROOT profile type ("" error on mean, "s" spread)
              options --- ROOT plot option string ("hist", "e", etc.)

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (y) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: None

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To auto-bin histogram, use profile.  To bin a continuous histogram,
    use profilebin.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_functions(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "profiletype", "options", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = False

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].profileint(function, min, max, profiletype, options, frequency, None)
    master = self.internal[i]
    for inter in self.internal[i+1:]:
      inter.profileint(function, min, max, profiletype, options, frequency, master)
    return None

  def plot2(self, function, filter=None, sample=None, leftloss=None, toploss=None, rightloss=None, bottomloss=None, padding=None, canvas_size=None, start=None, stop=None, step=None):
    """Scatter-plot a two-dimensional function of ntuple variables and
    determine an optimal binning.

    Arguments: function to be plotted --- may be a string ("x+y, y"),
               a tuple of two strings ("x+y", "y") or a callable
               (lambda x, y: x+y, y, predefined_func).  Argument names
               must be ntuple labels, but arbitrary python
               code/globals may be referenced.
               Must evaluate to a pair of numbers for X and Y.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              sample --- number of good entries plotted and used to
              determine histogram range and binning (good means
              passing filter).
              Default is 1000; will not exceed first ntuple in chain.

              leftloss, toploss, rightloss, bottomloss --- fraction
              of events you're willing to use in determining the range.
              Useful if distribution has a few extreme outliers.
              Expressed as a fraction of total area.
              Default is 0.01 == 1%.

              padding --- extra left/right margins for aesthetics.
              Expressed as a fraction of the x range.
              Default is 0.1 == 10%.

              canvas_size --- 2-tuple of integers (500, 500)

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.
              This is less important because the number of events is
              controlled by sample, but useful for extrapolating bin
              sizes to the plot2bin follow-up.

    Returns: chosen histogram bounds (binsX, lowX, highX, binsY, lowY, highY)

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    Because UNBINNED scatter plotting is expensive (from what I can
    see of the documentation, even ROOT doesn't do this), this
    function only plots the sample used to determine histogram bounds.
    To see all the data in your ntuple, follow-up with plot2bin.
    
    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. Only the first ntuple in the chain can be used, no matter
           how large `sample' is.
        2. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_functions(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "sample", "leftloss", "toploss", "rightloss", "bottomloss", "padding", \
              "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)

    for v in ["filter", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = True

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    return self.internal[i].plot2(function, sample, leftloss, toploss, rightloss, bottomloss, padding, start, stop, self.indexmap[i])

  def plot2bin(self, binsX, lowX, highX, binsY, lowY, highY, function, filter=None, start=None, stop=None, step=None, options2=None, frequency=None, log=None, canvas_size=None):
    """Bin and plot a two-dimensional function of ntuple variables.

    Arguments: binsX, lowX, highX, binsY, lowY, highY --- hist specification
               
               function to be plotted --- may be a string ("x+y, y"),
               a tuple of two strings ("x+y", "y") or a callable
               (lambda x, y: x+y, y, predefined_func).  Argument names
               must be ntuple labels, but arbitrary python
               code/globals may be referenced.
               Must evaluate to a pair of numbers for X and Y.

    Optional: filter to select entries --- same forms as function.
              Must return True, False or a numerical weight.

              start, stop, step --- control entry range;
              step = ntuple.entries/N plots N entries.
              Defaults are 0, entries, 1.

              options2 --- ROOT 2-D plot option string (defaults "colz")

              frequency --- how often to update the plot while filling.
              Expressed as a number of good events.
              If 0, only plot after all filling.
              Default is 1000.

              log --- plot in log (z) scale if True

              canvas_size --- 2-tuple of integers (500, 500)

    Returns: None

    Meant to be a quick way of exploring ntuple data before
    constructing and drawing histograms in another package.

    To auto-bin histogram and see unbinned scatter, use plot2.

    Optional arguments, if unspecified, default to member data.

    Supplying a single-variable extraction as "varname" is faster
    than lambda varname: varname.

    Drawn with ROOT graphics, updated by a ROOT thread on a 1-second
    timer.  If ROOT deletes objects without my knowledge, python will
    crash one second later (with OneSecondLoop in the stack trace).
    Data is most secure if you use the non-graphical functions.  I
    recommend using these plotting functions to get a first look at
    the ntuples (to determine optimal ranges, cuts, variables to
    plot), and the extraction functions (map, pyxplot, simple
    iteration) for later work in another package.

    I painted myself into a corner in this design.
        1. If start is beyond than the first ntuple in the chain, you
           may get a second window."""

    function = self.compile_functions(function)

    start, stop, step = self.setup_sss(start=start, stop=stop, step=step)
    for v in ["filter", \
              "options2", "frequency", "log", "canvas_size"]:
      exec "if %(v)s == None: %(v)s = self.%(v)s" % {"v": v}
    if filter != None: filter = self.compile_function(filter)
    if frequency == 0: frequency = None

    for v in ["filter", "log", "canvas_size"]:
      for inter in self.internal:
        exec "inter.%(v)s = %(v)s" % {"v": v}

    self.last2d = True

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].plot2bin(function, binsX, lowX, highX, binsY, lowY, highY, options2, frequency, None)
    master = self.internal[i]

    for inter in self.internal[i+1:]:
      inter.plot2bin(function, binsX, lowX, highX, binsY, lowY, highY, options2, frequency, master)
    return None

  def redraw(self, options=None):
    """Redraw the last histogram.

    Optional: options --- new ROOT plot options
    Returns: None

    If the histogram is 2-D, options default to self.options2."""

    if self.last2d:
      if options == None: options = self.options2
    else:
      if options == None: options = self.options

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].redraw(options)

  def postscript(self, filename):
    """Write the last histogram out to a postscript file.

    Arguments: filename
    Returns: None

    Whether or not the postscript is encapsulated depends on the
    filename extension: .eps or .ps."""
    
    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].postscript(filename)

  def closewindow(self):
    """TRY to close the histogram's window.

    Arguments: none
    Returns: None

    Perhaps the threaded window updater will close it, after 1 second."""    

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    self.internal[i].closewindow()

  def hist(self, name, title=None):
    """Obtain a RootHist object from the last drawn histogram.

    Arguments: name --- internal ROOT name for the histogram
    Optional: title --- ROOT puts this over the plot
    Returns: the RootHist object

    Unfortunately, yes, you have to name it.  And you can crash python
    if you choose a name that is already in use.  Isn't ROOT
    wonderful?"""

    for i in range(0, len(self.internal)):
      if self.internal[i].start != self.internal[i].stop: break

    if title != None:
      return self.internal[i].hist(name, title)
    else:
      return self.internal[i].hist(name)
