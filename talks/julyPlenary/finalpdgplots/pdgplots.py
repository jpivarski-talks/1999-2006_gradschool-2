from math import *
import biggles, Numeric

names = ["Pluto '79", "DESY-Heidel. '80", "LENA '82", "DASP-II '82", "CLEO-I '84", "Crystal Ball '88", "Argus '94", "Novosibirsk '96", "CLEO-III '05"]
names.reverse()

g1 = {}
g1["Pluto '79"] = 1.35, 0.14, 0.
g1["DESY-Heidel. '80"] = 1.09, 0.25, 0.
g1["LENA '82"] = 1.13, 0.07, 0.11
g1["DASP-II '82"] = 1.23, 0.08, 0.04
g1["CLEO-I '84"] = 1.37, 0.06, 0.09
g1["Crystal Ball '88"] = 1.23, 0.02, 0.05
g1["Argus '94"] = 1.218, 0.034, 0.028
g1["Novosibirsk '96"] = 1.187, 0.023, 0.031
g1["CLEO-III '05"] = 1.252, 0.004, 0.019

g2 = {}
g2["Pluto '79"] = None
g2["DESY-Heidel. '80"] = 0.41, 0.18, 0.
g2["LENA '82"] = 0.54, 0.07, 0.07
g2["DASP-II '82"] = 0.60, 0.12, 0.07
g2["CLEO-I '84"] = 0.58, 0.03, 0.04
g2["Crystal Ball '88"] = 0.54, 0.04, 0.02
g2["Argus '94"] = 0.49816, 0.029, 0.0084
g2["Novosibirsk '96"] = 0.552, 0.031, 0.017
g2["CLEO-III '05"] = 0.581, 0.005, 0.009

g3 = {}
g3["Pluto '79"] = None
g3["DESY-Heidel. '80"] = None
g3["LENA '82"] = None
g3["DASP-II '82"] = None
g3["CLEO-I '84"] = 0.45, 0.03, 0.03
g3["Crystal Ball '88"] = None
g3["Argus '94"] = None
g3["Novosibirsk '96"] = None
g3["CLEO-III '05"] = 0.413, 0.004, 0.006

def fillemup(gwhich):
  x = []
  y = []
  yerr1 = []
  yerr2 = []
  for i, n in enumerate(names):
    if n in gwhich and gwhich[n] != None:
      x.append(i)
      y.append(gwhich[n][0])
      yerr1.append(gwhich[n][1])
      yerr2.append(sqrt(gwhich[n][1]**2+gwhich[n][2]**2))
  return x, y, yerr1, yerr2

def fillemup_mine(gwhich):
  x = []
  y = []
  yerr1 = []
  yerr2 = []
  for i, n in enumerate(names):
    if n == "CLEO-III '05":
      x.append(i)
      y.append(gwhich[n][0])
      yerr1.append(gwhich[n][1])
      yerr2.append(sqrt(gwhich[n][1]**2+gwhich[n][2]**2))
  return x, y, yerr1, yerr2

p = biggles.Table(1,3)
p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.LineX(1.216, linetype="longdashed", linecolor="black"))
p[0,0].add(biggles.LineX(1.216+0.027, linetype="dotted", linecolor="black"))
p[0,0].add(biggles.LineX(1.216-0.027, linetype="dotted", linecolor="black"))
p[0,0].add(biggles.LineY(0.5))
p[0,0].add(biggles.PlotLabel(0.1, 0.95, r"$\Upsilon(1S)$", texthalign="left", textvalign="top", fontsize=5.))
x, y, yerr1, yerr2 = fillemup(g1)
p[0,0].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5))
p[0,0].add(biggles.SymmetricErrorBarsX(y,x,yerr1))
p[0,0].add(biggles.SymmetricErrorBarsX(y,x,yerr2))
x, y, yerr1, yerr2 = fillemup_mine(g1)
p[0,0].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5, color="red"))
p[0,0].add(biggles.SymmetricErrorBarsX(y,x,yerr1, color="red"))
p[0,0].add(biggles.SymmetricErrorBarsX(y,x,yerr2, color="red"))
p[0,0].x.range = 0.7, 1.7
p[0,0].y.range = -0.5, len(names)-0.5
p[0,0].y.draw_ticks = 0
p[0,0].y.draw_ticklabels = 0
p[0,0].frame.ticklabels_style["fontsize"] = 3.5
p[0,0].aspect_ratio = 2.5

p[0,1] = biggles.FramedPlot()
p[0,1].add(biggles.LineX(0.553, linetype="longdashed", linecolor="black"))
p[0,1].add(biggles.LineX(0.553+0.023, linetype="dotted", linecolor="black"))
p[0,1].add(biggles.LineX(0.553-0.023, linetype="dotted", linecolor="black"))
p[0,1].add(biggles.LineY(0.5))
p[0,1].add(biggles.PlotLabel(0.1, 0.95, r"$\Upsilon(2S)$", texthalign="left", textvalign="top", fontsize=5.))
x, y, yerr1, yerr2 = fillemup(g2)
p[0,1].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5))
p[0,1].add(biggles.SymmetricErrorBarsX(y,x,yerr1))
p[0,1].add(biggles.SymmetricErrorBarsX(y,x,yerr2))
x, y, yerr1, yerr2 = fillemup_mine(g2)
p[0,1].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5, color="red"))
p[0,1].add(biggles.SymmetricErrorBarsX(y,x,yerr1, color="red"))
p[0,1].add(biggles.SymmetricErrorBarsX(y,x,yerr2, color="red"))
p[0,1].x.range = 0.1, 0.9
p[0,1].y.range = -0.5, len(names)-0.5
p[0,1].y.draw_ticks = 0
p[0,1].y.draw_ticklabels = 0
p[0,1].frame.ticklabels_style["fontsize"] = 3.5
p[0,1].aspect_ratio = 2.5

p[0,2] = biggles.FramedPlot()
p[0,2].add(biggles.LineX(0.45, linetype="longdashed", linecolor="black"))
p[0,2].add(biggles.LineX(0.45+0.0424, linetype="dotted", linecolor="black"))
p[0,2].add(biggles.LineX(0.45-0.0424, linetype="dotted", linecolor="black"))
p[0,2].add(biggles.LineY(0.5))
p[0,2].add(biggles.PlotLabel(0.1, 0.95, r"$\Upsilon(3S)$", texthalign="left", textvalign="top", fontsize=5.))
x, y, yerr1, yerr2 = fillemup(g3)
p[0,2].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5))
p[0,2].add(biggles.SymmetricErrorBarsX(y,x,yerr1))
p[0,2].add(biggles.SymmetricErrorBarsX(y,x,yerr2))
x, y, yerr1, yerr2 = fillemup_mine(g3)
p[0,2].add(biggles.Points(y,x, symboltype="filled circle", symbolsize=1.5, color="red"))
p[0,2].add(biggles.SymmetricErrorBarsX(y,x,yerr1, color="red"))
p[0,2].add(biggles.SymmetricErrorBarsX(y,x,yerr2, color="red"))
p[0,2].x.range = 0.33, 0.52
p[0,2].y.range = -0.5, len(names)-0.5
p[0,2].y.draw_ticks = 0
p[0,2].y.draw_ticklabels = 0
p[0,2].frame.ticklabels_style["fontsize"] = 3.5
p[0,2].aspect_ratio = 2.5
p.aspect_ratio = 8.5/10.
p.show()
p.write_eps("/home/mccann/antithesis/plots/julyPlenary/pdgplots1.eps")

