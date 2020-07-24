import os, cPickle as pickle, re, time, math
from pyx import *

### User configuration options ##########################

tmp_directory = "/tmp"

# Your TeX setup (see PyX documentation for details)
def reboot_tex():
  global texrunner
  texrunner = text.texrunner(mode="latex", lfs="12pt", errordebug=1)
  texrunner.preamble(r"""
\setlength{\parskip}{0.2 cm}
""")
reboot_tex()

#########################################################

pyxplotset = set()

class PyxPlot_command:
  def __init__(self, item, command="insert", attrs=[]):
    self.item = item
    if command == "insert":   self.command = 0
    elif command == "stroke": self.command = 1
    elif command == "fill":   self.command = 2
    elif command == "draw":   self.command = 3
    else:
      raise ValueError, "Command must be 'insert', 'stroke', 'fill', or 'draw'."
    self.attrs = attrs

  def apply(self, canvas):
    if self.command == 0:   canvas.insert(self.item, self.attrs)
    elif self.command == 1: canvas.stroke(self.item, self.attrs)
    elif self.command == 2: canvas.fill(self.item, self.attrs)
    elif self.command == 3: canvas.draw(self.item, self.attrs)

  def commands(self):
    if self.command == 0:   return "canvas.insert("+repr(self.item)+", "+repr(self.attrs)+")"
    elif self.command == 1: return "canvas.stroke("+repr(self.item)+", "+repr(self.attrs)+")"
    elif self.command == 2: return "canvas.fill("+repr(self.item)+", "+repr(self.attrs)+")"
    elif self.command == 3: return "canvas.draw("+repr(self.item)+", "+repr(self.attrs)+")"

###############################################################

class PyxLinkedAxis_pointer:
  def __init__(self, which, pointer):
    self.which = which
    self.pointer = pointer

  def apply(self):
    return graph.axis.linkedaxis(self.pointer.graph.axes[self.which])

class PyxGraph_command:
  def __init__(self, *dsb, **args):
    self.dsb = list(dsb)
    self.args = args

  def modify(self, **args):
    self.args.update(args)

  def apply(self, **args):
    a = self.args.copy()
    a.update(args)
    for kw, val in a.items():
      if isinstance(val, PyxLinkedAxis_pointer):
        a[kw] = val.apply()
    self.graph = graph.graphxy(**a)
    for d, s, b in self.dsb: self.graph.plot(d, s)
    return self.graph

  def copy(self, **args):
    a = self.args.copy()
    a.update(args)
    return PyxGraph_command(*self.dsb, **a)

  def commands(self):
    output = "pyx.graph.graphxy("
    keys = self.args.keys()
    order = {"xpos":0, "ypos":1, "width":2, "height":3, "ratio":4, "key":5, "backgroundattrs":6, "axesdist":7, "axisat":8, "yaxisat":9}
    keys.sort(lambda a1, a2: cmp(order.get(a1,10), order.get(a2,10)))
    for k in keys: output += k+"="+repr(self.args[k])+", "
    output += ")\n"
    for d, s, b in self.dsb:
      output += "plot("+repr(d)+", styles="+repr(s)+")\n"
    return output

###############################################################

class PyxPlot:
  def __init__(self, name="pyxplot", logfile_name=None, plogfile_name=None, width=15, height=15, display=None, logpaperformat=document.paperformat.Letter):

    # Give this pyxplot a unique (human-grokable) name
    assigned_name = name[:]
    counter = 1
    while assigned_name in pyxplotset:
      counter += 1
      assigned_name = name+"<"+str(counter)+">"
    pyxplotset.add(assigned_name)
    self.name = assigned_name

    self.instance = id(self)
    self.session_name = "pyxplot-"+str(self.instance)
    self.file_name = tmp_directory+"/pyxplot-"+str(self.instance)+".pdf"

    self.width = width
    self.height = height
    self.xgap = 1.7
    self.x2gap = 0.3
    self.ygap = 1.5
    self.y2gap = 0.5
    self.lining("invisible")
    self.graphs = []
    self.make_canvas().writePDFfile(self.file_name)

    # Note: this is not a safe OS call: what if self.name contained
    # something dastardly like "; rm -rf *"?  It only affects the
    # user's own area.
    dodisplay = ""
    if display: dodisplay = "-display "+display
    os.system("xpdf -z width -t '"+self.name+"' "+dodisplay+" -remote "+self.session_name+" "+self.file_name+" &")

    # Set up the paper trail
    self.log = []
    if logfile_name == None: logfile_name = name+".ps"
    if plogfile_name == None: plogfile_name = name+".p"
    self.paperformat = logpaperformat
    self.plog = {}
    self.plog_page = []
    self.logfile_name = logfile_name
    self.plogfile_name = plogfile_name

  def __del__(self):
    pyxplotset.remove(self.name)
    os.system("xpdf -remote "+self.session_name+" -quit")
    if self.file_name != None: os.remove(self.file_name)

###############################################################

  def make_canvas(self):
    commands = self.commands_lining + map(lambda g: PyxPlot_command(g.apply()), self.graphs)

    c = canvas.canvas(texrunner=texrunner)
    for i in commands: i.apply(c)
    return c

  def redraw(self):
    self.make_canvas().writePDFfile(self.file_name)
    os.system("xpdf -remote "+self.session_name+" -reload")

  def raise_window(self):
    os.system("xpdf -remote "+self.session_name+" -raise")

###############################################################

  def append_log(self, message=r"\mbox{ }", objects={}):
    # Add these objects to the pickled dictionary with a unique name
    # and remember what page they're associated with.
    page_objects = []

    objects_newnames = {}
    for k, o in objects.items():
      assigned_name = k[:]
      counter = 1
      while assigned_name in self.plog:
        counter += 1
        assigned_name = k+"_"+str(counter)

      self.plog[assigned_name] = o
      page_objects.append(assigned_name)

    self.plog_page.append(page_objects)
        
    # Add useful information to the message
    underscore = re.compile("_")
    message += "\n\n\\mbox{ }\n\n\\hline\n"

    if len(page_objects) > 0:
      message += "\\begin{itemize}\\setlength{\\itemsep}{-0.2 cm}\n"
      for assigned_name in page_objects:
        message += "    \\item "+underscore.sub("\\_", assigned_name)+"\n"
      message += "\\end{itemize}\n"

    name_with_underscores = os.path.abspath(self.logfile_name)
    name_with_underscores = underscore.sub("\\_", name_with_underscores)
    message += "{\\it "+time.asctime(time.localtime(time.time()))+" \\hfill "+name_with_underscores+"}"

    # Write the objects out to the pickle file
    pickle.dump(self.plog, open(self.plogfile_name, "w"))

    # Create the textbox and write out the pdf
    textbox = texrunner.text(0, -0.5, message, [text.parbox(15), text.halign.left, text.halign.flushleft, text.valign.top])
    c = self.make_canvas()
    c.insert(textbox)
    self.log.append(document.page(c, paperformat=self.paperformat, fittosize=1))
    document.document(self.log).writetofile(self.logfile_name)

    # Take a look
    self.view_log(-1)

  def view_log(self, page=None):
    if page == None:
      os.system("gv "+self.logfile_name)
    else:
      if type(page) != int and type(page) != long:
        raise TypeError, "Only one page, please."
      self.log[page].canvas.writePDFfile(self.file_name)
      os.system("xpdf -remote "+self.session_name+" -reload")

  def del_log(self, page=None):
    if page == None: page = -1
    if type(page) != int and type(page) != long:
      raise TypeError, "Only one page, please."
    for name in self.plog_page[page]:
      del self.plog[name]
    del self.log[page]
    del self.plog_page[page]

    # Update the pickle and pdf files
    pickle.dump(self.plog, open(self.plogfile_name, "w"))
    document.document(self.log).writetofile(self.logfile_name)

###############################################################

  def lining(self, style="visible"):
    if style == "invisible":
      self.commands_lining = [PyxPlot_command(path.rect(0, 0, 15, 15), "stroke", [color.grey.white])]
    elif style == "visible":
      self.commands_lining = [PyxPlot_command(path.rect(0, 0, 15, 15), "stroke", [color.grey.black])]
    elif style == "none":
      self.commands_lining = []
    else:
      self.commands_lining = [PyxPlot_command(path.rect(0, 0, 15, 15), "stroke", style)]

  def graph(self, *args, **kwds):
    xtitle = None
    ytitle = None
    logy = False
    if "xtitle" in kwds:
      xtitle = kwds["xtitle"]
      del kwds["xtitle"]
    if "ytitle" in kwds:
      ytitle = kwds["ytitle"]
      del kwds["ytitle"]
    if "logy" in kwds:
      logy = kwds["logy"]
      del kwds["logy"]

    defaults = {"xpos": self.xgap, "ypos": self.ygap, "width": self.width-self.xgap-self.x2gap, "height": self.height-self.ygap-self.y2gap, "x": graph.axis.linear(min=0, max=1), "y": graph.axis.linear(min=0, max=1)}
    if xtitle != None:
      defaults["x"] = graph.axis.linear(min=0, max=1, title=xtitle)
    if ytitle != None:
      if logy:
        defaults["y"] = graph.axis.log(min=0.1, max=1, title=ytitle)
      else:
        defaults["y"] = graph.axis.linear(min=0, max=1, title=ytitle)

    def trans(a):
      if isinstance(a, PyxHist): return a.steps(logy=logy)
      elif isinstance(a, PyxData) and data.dy != None: return a.errorbars(logy=logy)
      elif isinstance(a, PyxData): return a.errorbars(logy=logy)
      else: return a
    args2 = map(trans, args)

    if len(args2) > 0:
      xmin = min(map(lambda (d, s, b): b[0][0], args2))
      xmax = max(map(lambda (d, s, b): b[0][1], args2))
      ymin = min(map(lambda (d, s, b): b[1][0], args2))
      ymax = max(map(lambda (d, s, b): b[1][1], args2))

      if xtitle != None:
        defaults["x"] = graph.axis.linear(min=xmin, max=xmax, title=xtitle)
      else:
        defaults["x"] = graph.axis.linear(min=xmin, max=xmax)
      if ytitle != None:
        if logy:
          defaults["y"] = graph.axis.log(min=ymin, max=ymax, title=ytitle)
        else:
          defaults["y"] = graph.axis.linear(min=ymin, max=ymax, title=ytitle)
      else:
        if logy:
          defaults["y"] = graph.axis.log(min=ymin, max=ymax)
        else:
          defaults["y"] = graph.axis.linear(min=ymin, max=ymax)
    defaults.update(kwds)

    return PyxGraph_command(*args2, **defaults)

  def __call__(self, *args, **kwds):
    self.graphs = [self.graph(*args, **kwds)]
    self.redraw()
    return self.graphs[0]

  def table(self, graphs):
    output = []
    reversed_graphs = graphs[:]
    reversed_graphs.reverse()

    each_height = float(self.height) / float(len(graphs)) - self.ygap - self.y2gap
    ypos = self.ygap
    for row in reversed_graphs:
      each_width = float(self.width) / float(len(row)) - self.xgap - self.x2gap
      xpos = self.xgap
      for g in row:
        output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height))
        xpos += each_width + self.xgap + self.x2gap
      ypos += each_height + self.ygap + self.y2gap

    self.graphs = output
    self.redraw()

  def table_transpose(self, graphs):
    output = []

    each_width = float(self.width) / float(len(graphs)) - self.xgap - self.x2gap
    xpos = self.xgap
    for col in graphs:
      col.reverse()

      each_height = float(self.height) / float(len(col)) - self.ygap - self.y2gap
      ypos = self.ygap
      for g in col:
        output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height))
        ypos += each_height + self.ygap + self.y2gap
      xpos += each_width + self.xgap + self.x2gap

    self.graphs = output
    self.redraw()

  def array(self, graphs, xtitle=None, ytitle=None):
    output = []
    reversed_graphs = graphs[:]
    reversed_graphs.reverse()

    each_height = float(self.height-self.ygap-self.y2gap) / float(len(graphs))
    ypos = self.ygap
    firstrow = True
    for row in reversed_graphs:
      each_width = float(self.width-self.xgap-self.x2gap) / float(len(row))
      xpos = self.xgap
      firstcol = True
      if firstrow: xmaster = []
      i = 0
      for g in row:
        if firstrow and firstcol:  # (first row from the bottom up)
          output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height))
        elif firstrow and not firstcol:
          output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height, y=PyxLinkedAxis_pointer("y", ymaster)))
        elif not firstrow and firstcol:
          output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height, x=PyxLinkedAxis_pointer("x", xmaster[i])))
        else:
          output.append(g.copy(xpos=xpos, ypos=ypos, width=each_width, height=each_height, x=PyxLinkedAxis_pointer("x", xmaster[i]), y=PyxLinkedAxis_pointer("y", ymaster)))
        if firstrow: xmaster.append(output[-1])
        if firstcol: ymaster = output[-1]
        xpos += each_width
        firstcol = False
        i += 1
      ypos += each_height
      firstrow = False

    if xtitle != None or ytitle != None:
      output.append(PyxGraph_command(xpos=self.xgap, ypos=self.ygap, width=self.width-self.xgap-self.x2gap, height=self.height-self.ygap-self.y2gap, x=graph.axis.linear(title=xtitle, min=0, max=1, parter=None, painter=graph.axis.painter.regular(titledist=1*unit.v_cm)), y=graph.axis.linear(title=ytitle, min=0, max=1, parter=None, painter=graph.axis.painter.regular(titledist=1*unit.v_cm))))

    self.graphs = output
    self.redraw()

###############################################################

class PyxData:
  def __init__(self, x, y, dy=None, logy=False):
    self.x = x
    self.y = y
    self.dy = dy
    self.logy = logy

  def translate_symbolstyle(self, symbol, thecolor, fillcolor, size):
    if type(thecolor) == str:
      if thecolor in translate_colors:
        colorattr = translate_colors[thecolor]
      else:
        raise ValueError, "Unrecognized color \""+thecolor+"\"."
    else:
      colorattr = thecolor

    if type(fillcolor) == str:
      if fillcolor in translate_colors:
        fillcolorattr = translate_colors[fillcolor]
      elif fillcolor == "same":
        fillcolorattr = colorattr
      else:
        raise ValueError, "Unrecognized fillcolor \""+fillcolor+"\"."
    else:
      fillcolorattr = fillcolor

    if type(symbol) == str:
      if symbol in translate_symbols:
        symbolattr = translate_symbols[symbol]
    else:
      raise ValueError, "Unrecognized symbol \""+symbol+"\"."
        
    if fillcolor == None:
      return graph.style.symbol(symbolattr, size=size, symbolattrs=[deco.stroked([colorattr])])
    else:
      return graph.style.symbol(symbolattr, size=size, symbolattrs=[deco.filled([fillcolorattr]), deco.stroked([colorattr])])

  def translate_errorbarstyle(self, thecolor, size):
    if type(thecolor) == str:
      if thecolor in translate_colors:
        colorattr = translate_colors[thecolor]
      else:
        raise ValueError, "Unrecognized color \""+thecolor+"\"."
    else:
      colorattr = thecolor

    return graph.style.errorbar(size=size, errorbarattrs=[colorattr])

  def translate_linestyle(self, style, width, thecolor, fillcolor):
    if type(style) == str:
      if style in translate_style:
        styleattr = translate_style[style]
      else:
        raise ValueError, "Unrecognized style \""+style+"\"."
    else:
      styleattr = style

    if type(width) == str:
      if width in translate_widths:
        widthattr = translate_widths[width]
      else:
        raise ValueError, "Unrecognized width \""+width+"\"."
    else:
      widthattr = width

    if type(thecolor) == str:
      if thecolor in translate_colors:
        colorattr = translate_colors[thecolor]
      else:
        raise ValueError, "Unrecognized color \""+thecolor+"\"."
    else:
      colorattr = thecolor

    if type(fillcolor) == str:
      if fillcolor in translate_colors:
        fillcolorattr = translate_colors[fillcolor]
      elif fillcolor == "same":
        fillcolorattr = colorattr
      else:
        raise ValueError, "Unrecognized fillcolor \""+fillcolor+"\"."
    else:
      fillcolorattr = fillcolor

    if fillcolor == None:
      return graph.style.line([styleattr, widthattr, colorattr])
    else:
      raise NotImplementedError

  def logready(self, logy=None, x=None, y=None, dy=None):
    if logy == None: logy = self.logy

    X = self.x ; Y = self.y ; DY = self.dy
    if x != None: X = x
    if y != None: Y = y
    if dy != None: DY = dy

    x = X ; y = Y ; dy = DY
    if logy:
      x = [] ; y = [] ; dy = []
      for xi, yi, dyi in zip(X, Y, DY):
        if yi > 0.:
          x.append(xi)
          y.append(yi)
          dy.append(dyi)
    return x, y, dy    

  def bounds(self, logy=None, x=None, y=None, dy=None):
    if logy == None: logy = self.logy
    if x == None: x = self.x
    if y == None: y = self.y
    if dy == None: dy = self.dy

    width = max(x) - min(x)
    height = max(y) - min(y)
    return ((min(x)-0.1*width, max(x)+0.1*width), ((min(y)-0.1*height), max(y)+0.1*height))

  def points(self, title="", symbol="circle", color="black", fillcolor="same", size=0.13*unit.v_cm, logy=None):
    if len(self.x) != len(self.y):
      raise ValueError, "Lists x and y need to be the same length."

    x, y, dy = self.logready(logy)
    d = graph.data.list(zip(x, y), title=title, x=1, y=2)
    s = [self.translate_symbolstyle(symbol, color, fillcolor, size)]
    return d, s, self.bounds(None, x, y, dy)

  def errorbars(self, title="", symbol="circle", color="black", fillcolor="same", size=0.13*unit.v_cm, capsize=0.13*unit.v_cm, logy=None):
    if self.dy == None or len(self.x) != len(self.y) or len(self.y) != len(self.dy):
      raise ValueError, "Lists x, y, and dy need to be the same length."
    
    x, y, dy = self.logready(logy)
    d = graph.data.list(zip(x, y, dy), title=title, x=1, y=2, dy=3)
    s = [self.translate_errorbarstyle(color, capsize), self.translate_symbolstyle(symbol, color, fillcolor, size)]
    return d, s, self.bounds(None, x, y, dy)

  def lines(self, title="", style="solid", width="Thin", color="black", fillcolor=None, logy=None):

    x, y, dy = self.logready(logy)
    d = graph.data.list(zip(x, y), title=title, x=1, y=2)
    s = [self.translate_linestyle(style, width, color, fillcolor)]
    return d, s, self.bounds(None, x, y, dy)

###############################################################

class PyxHist(PyxData):
  def __init__(self, low, high, values, errors, overflow=None, overflow_error=None, underflow=None, underflow_error=None, logy=False):
    self.bins = len(values)
    self.low = low
    self.high = high
    self.values = values
    self.errors = errors
    self.overflow = overflow
    self.overflow_error = overflow_error
    self.underflow = underflow
    self.underflow_error = underflow_error
    self.logy = logy

  def logready(self, logy=None):
    if logy == None: logy = self.logy

    if not logy: return self.values, self.values, self.errors
    
    pretend_values = []
    for v in self.values:
      if v > 0.: pretend_values.append(v)

    draw_values = []
    for v in self.values:
      if v > 0.: draw_values.append(v)
      else: draw_values.append(min(pretend_values)/1000.)

    draw_errors = []
    for e in self.errors:
      if e > 0.: draw_errors.append(e)
      else: draw_errors.append(0.)

    return pretend_values, draw_values, draw_errors

  def bounds(self, logy=None, values=None):  # pretend_values, that is
    if logy == None: logy = self.logy
    if values == None: values = self.values

    if logy:
      height = math.log10(max(values)/min(values))

      return ((self.low, self.high), (min(values)*10**(-0.1*height), max(values)*10**(0.1*height)))
    else:
      height = max(values) - min(values)
      if min(values) < 0:
        return ((self.low, self.high), ((min(values)-0.1*height), max(values)+0.1*height))
      else:
        return ((self.low, self.high), ((0., max(values)+0.1*height)))

  def points(self, title="", symbol="circle", color="black", fillcolor="same", size=0.13*unit.v_cm, logy=None):
    pretend_values, draw_values, draw_errors = self.logready(logy)

    d = graph.data.list(zip(self.bin_centers(), draw_values), title=title, x=1, y=2)
    s = [self.translate_symbolstyle(symbol, color, fillcolor, size)]
    return d, s, self.bounds(logy, pretend_values)

  def errorbars(self, title="", symbol="circle", color="black", fillcolor="same", size=0.13*unit.v_cm, capsize=0.13*unit.v_cm, logy=None):
    pretend_values, draw_values, draw_errors = self.logready(logy)

    d = graph.data.list(zip(self.bin_centers(), draw_values, draw_errors), title=title, x=1, y=2, dy=3)
    s = [self.translate_errorbarstyle(color, capsize), self.translate_symbolstyle(symbol, color, fillcolor, size)]
    return d, s, self.bounds(logy, pretend_values)

  def lines(self, title="", style="solid", width="Thin", color="black", fillcolor=None, logy=None):
    pretend_values, draw_values, draw_errors = self.logready(logy)

    d = graph.data.list(zip(self.bin_centers(), draw_values), title=title, x=1, y=2)
    s = [self.translate_linestyle(style, width, color, fillcolor)]
    return d, s, self.bounds(logy, pretend_values)

  def steps(self, title="", style="solid", width="Thin", color="black", fillcolor=None, logy=None):
    pretend_values, draw_values, draw_errors = self.logready(logy)

    x = []; y = []
    for left, right, height in zip(self.bin_lowedges(), self.bin_highedges(), draw_values):
      x.append(left)
      y.append(height)
      x.append(right)
      y.append(height)

    d = graph.data.list(zip(x, y), title=title, x=1, y=2)
    s = [self.translate_linestyle(style, width, color, fillcolor)]
    return d, s, self.bounds(logy, pretend_values)

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

###############################################################

# p = PyxPlot()

# p.table([[p.graph(x=graph.axis.lin(title="x", min=0, max=1), y=graph.axis.lin(title="y", min=0, max=1)), p.graph(x=graph.axis.lin(title="x", min=0, max=1), y=graph.axis.lin(title="y", min=0, max=1))], [p.graph(x=graph.axis.lin(title="x", min=0, max=1), y=graph.axis.lin(title="y", min=0, max=1)), p.graph(x=graph.axis.lin(title="x", min=0, max=1), y=graph.axis.lin(title="y", min=0, max=1))]])

# p.array([[p.graph(y=graph.axis.lin(title="y1", min=0, max=1)), p.graph()], [p.graph(x=graph.axis.lin(title="x1", min=0, max=1), y=graph.axis.lin(title="y2", min=0, max=1)), p.graph(x=graph.axis.lin(title="x2", min=0, max=1))]])

###############################################################

translate_colors = {"black": color.grey.black, \
                    "white": color.grey.white, \
                    "grey10": color.grey(0.10), \
                    "grey20": color.grey(0.20), \
                    "grey30": color.grey(0.30), \
                    "grey40": color.grey(0.40), \
                    "grey50": color.grey(0.50), \
                    "grey60": color.grey(0.60), \
                    "grey70": color.grey(0.70), \
                    "grey80": color.grey(0.80), \
                    "grey90": color.grey(0.90), \
                    "red": color.rgb.red, \
                    "green": color.rgb.green, \
                    "blue": color.rgb.blue, \
                    "GreenYellow": color.cmyk.GreenYellow, \
                    "Yellow": color.cmyk.Yellow, \
                    "Goldenrod": color.cmyk.Goldenrod, \
                    "Dandelion": color.cmyk.Dandelion, \
                    "Apricot": color.cmyk.Apricot, \
                    "Peach": color.cmyk.Peach, \
                    "Melon": color.cmyk.Melon, \
                    "YellowOrange": color.cmyk.YellowOrange, \
                    "Orange": color.cmyk.Orange, \
                    "BurntOrange": color.cmyk.BurntOrange, \
                    "Bittersweet": color.cmyk.Bittersweet, \
                    "RedOrange": color.cmyk.RedOrange, \
                    "Mahogany": color.cmyk.Mahogany, \
                    "Maroon": color.cmyk.Maroon, \
                    "BrickRed": color.cmyk.BrickRed, \
                    "Red": color.cmyk.Red, \
                    "OrangeRed": color.cmyk.OrangeRed, \
                    "RubineRed": color.cmyk.RubineRed, \
                    "WildStrawberry": color.cmyk.WildStrawberry, \
                    "Salmon": color.cmyk.Salmon, \
                    "CarnationPink": color.cmyk.CarnationPink, \
                    "Magenta": color.cmyk.Magenta, \
                    "VioletRed": color.cmyk.VioletRed, \
                    "Rhodamine": color.cmyk.Rhodamine, \
                    "Mulberry": color.cmyk.Mulberry, \
                    "RedViolet": color.cmyk.RedViolet, \
                    "Fuchsia": color.cmyk.Fuchsia, \
                    "Lavender": color.cmyk.Lavender, \
                    "Thistle": color.cmyk.Thistle, \
                    "Orchid": color.cmyk.Orchid, \
                    "DarkOrchid": color.cmyk.DarkOrchid, \
                    "Purple": color.cmyk.Purple, \
                    "Plum": color.cmyk.Plum, \
                    "Violet": color.cmyk.Violet, \
                    "RoyalPurple": color.cmyk.RoyalPurple, \
                    "BlueViolet": color.cmyk.BlueViolet, \
                    "Periwinkle": color.cmyk.Periwinkle, \
                    "CadetBlue": color.cmyk.CadetBlue, \
                    "CornflowerBlue": color.cmyk.CornflowerBlue, \
                    "MidnightBlue": color.cmyk.MidnightBlue, \
                    "NavyBlue": color.cmyk.NavyBlue, \
                    "RoyalBlue": color.cmyk.RoyalBlue, \
                    "Blue": color.cmyk.Blue, \
                    "Cerulean": color.cmyk.Cerulean, \
                    "Cyan": color.cmyk.Cyan, \
                    "ProcessBlue": color.cmyk.ProcessBlue, \
                    "SkyBlue": color.cmyk.SkyBlue, \
                    "Turquoise": color.cmyk.Turquoise, \
                    "TealBlue": color.cmyk.TealBlue, \
                    "Aquamarine": color.cmyk.Aquamarine, \
                    "BlueGreen": color.cmyk.BlueGreen, \
                    "Emerald": color.cmyk.Emerald, \
                    "JungleGreen": color.cmyk.JungleGreen, \
                    "SeaGreen": color.cmyk.SeaGreen, \
                    "Green": color.cmyk.Green, \
                    "ForestGreen": color.cmyk.ForestGreen, \
                    "PineGreen": color.cmyk.PineGreen, \
                    "LimeGreen": color.cmyk.LimeGreen, \
                    "YellowGreen": color.cmyk.YellowGreen, \
                    "SpringGreen": color.cmyk.SpringGreen, \
                    "OliveGreen": color.cmyk.OliveGreen, \
                    "RawSienna": color.cmyk.RawSienna, \
                    "Sepia": color.cmyk.Sepia, \
                    "Brown": color.cmyk.Brown, \
                    "Tan": color.cmyk.Tan}

translate_symbols = {"cross": graph.style.symbol.cross, \
                     "plus": graph.style.symbol.plus, \
                     "square": graph.style.symbol.square, \
                     "triangle": graph.style.symbol.triangle, \
                     "circle": graph.style.symbol.circle, \
                     "diamond": graph.style.symbol.diamond}

translate_widths = {"THIN": style.linewidth.THIN, \
                    "THIn": style.linewidth.THIn, \
                    "THin": style.linewidth.THin, \
                    "Thin": style.linewidth.Thin, \
                    "thin": style.linewidth.thin, \
                    "normal": style.linewidth.normal, \
                    "thick": style.linewidth.thick, \
                    "Thick": style.linewidth.Thick, \
                    "THick": style.linewidth.THick, \
                    "THIck": style.linewidth.THIck, \
                    "THICk": style.linewidth.THICk, \
                    "THICK": style.linewidth.THICK}

translate_style = {"solid": style.linestyle.solid, \
                   "dashed": style.linestyle.dashed, \
                   "dotted": style.linestyle.dotted, \
                   "dashdotted": style.linestyle.dashdotted}
