from minuit import *
execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time

nbish2nb = 23.0481

u1runs = []
u2runs = []
u3runs = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs.append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs.append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs.append(r)

def get_runs(runs, usebhabha=False):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    
    if usebhabha:
      ngg = therun.bhabha
      if r in mycarefulscan: ngg = therun.bhabha_vstime.sum(0.,0.99)

    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if usebhabha:
        g -= therun.gamgam_vstime.sum(0.,0.99)
        g += therun.bhabha_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if usebhabha:
        g -= therun.gamgam
        g += therun.bhabha

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Hadronic cross-section is", cs, "+/-", cs_err

  if usebhabha:
    cs /= 0.077045
    cs_err /= 0.077045

  return average_energy, cs, cs_err

u1data = []
u2data = []
u3data = []
for r in u1runs: u1data.append(get_runs([r]))
for r in u2runs: u2data.append(get_runs([r]))
for r in u3runs: u3data.append(get_runs([r]))

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  else:
    return run_date(r-1)

mean1 = jt.wmean(map(lambda (a,b,c): (b,c), u1data))[0]
mean2 = jt.wmean(map(lambda (a,b,c): (b,c), u2data))[0]
mean3 = jt.wmean(map(lambda (a,b,c): (b,c), u3data))[0]

x = []
y = []
yerr = []
for r, (e, c, cerr) in zip(u1runs, u1data):
  x.append(run_date(r))
  y.append(c - mean1)
  yerr.append(cerr)
for r, (e, c, cerr) in zip(u2runs, u2data):
  x.append(run_date(r))
  y.append(c - mean2)
  yerr.append(cerr)
for r, (e, c, cerr) in zip(u3runs, u3data):
  x.append(run_date(r))
  y.append(c - mean3)
  yerr.append(cerr)

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", size=0.7))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.add(biggles.LineY(0.))
p.x1.range = min(x)-14.*24.*60.*60., max(x)+14.*24.*60.*60.
p.y1.range = -2., 2.
p.show()

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1,]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("", "Feb", "", "Apr", "", "Jun", "", "Aug", "", "Oct", "", "Dec"):
    for d in [1,]:
      dlabels.append("%s" % (m))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
    if d % 7 == 0:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
subticks = []
sublabels = []
for t, l in zip(dticks, dlabels):
  if min(x)-14.*24.*60.*60. < t < max(x)+14.*24.*60.*60.:
    subticks.append(t)
    sublabels.append(l)
subsubticks = []
for t in dsubticks:
  if min(x)-14.*24.*60.*60. < t < max(x)+14.*24.*60.*60.:
    subsubticks.append(t)
p.x1.ticks = subticks
p.x1.subticks = subsubticks
p.x1.ticklabels = sublabels
p.x2.ticks = subticks
p.x2.subticks = subsubticks
p.x2.draw_ticklabels = 0

p.y1.label = r"$\sigma - \langle\sigma\rangle$ in nb"
p.x1.label = "Date in 2001-2002"
p.show()

class MoreThanHist:
  def __init__(self, bins, low, high):
    self.h = hist.h1(bins, low, high)
    self.data = []
  def fill(self, l):
    for x in l:
      self.data.append(x)
      self.h.fill(x)
  def rootn(self):
    self.h.rootn()
  def plot(self):
    return self.h.plot()
  def sum(self):
    return self.h.sum()
  def overflow(self):
    return self.h.overflow
  def underflow(self):
    return self.h.underflow

def dofitgauss(h):
  def gauss(m, s, x): return exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
  def fitgauss(m,s):
    c = 0.
    for x in h.data:
      c += -log(gauss(m, s, x))
    return c
  m = Minuit(fitgauss, start=[0., 1.], up=0.5)
  m.migrad()
  m.minos([0,1])
  err0 = (m.minos_errors[0][1] - m.minos_errors[0][0])/2.
  err1 = (m.minos_errors[1][1] - m.minos_errors[1][0])/2.
  return m.values[0], err0, m.values[1], err1, lambda x: 0.1*len(h.data)*gauss(m.values[0], m.values[1], x)

h = MoreThanHist(100, -5., 5.)
h.fill(map(lambda (e,c,cerr): (c-mean1)/cerr, u1data))
h.fill(map(lambda (e,c,cerr): (c-mean2)/cerr, u2data))
h.fill(map(lambda (e,c,cerr): (c-mean3)/cerr, u3data))
mean, meanerr, width, widtherr, f = dofitgauss(h)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)

q = h.plot()
q.add(biggles.Curve(x,y, linewidth=3.5, color="red"))
entries = h.sum() + h.underflow() + h.overflow()
hist.addinfobox(q, [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))]], width=0.5, colwidth=0.07)
q.x1.label = r"Pull"
q.show()

r = biggles.Table(1,2)
p.aspect_ratio = 1.
q.aspect_ratio = 1.
r[0,0] = p
r[0,1] = q
r.aspect_ratio = 5./11.
# r.show()
r.write_eps("/home/mccann/antithesis/plots/julyPlenary/stability.eps")


