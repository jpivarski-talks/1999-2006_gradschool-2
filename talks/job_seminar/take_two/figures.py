import os
from pyx import *
text.defaulttexrunner = text.texrunner(mode="latex", lfs="12pt", errordebug=1)

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon$", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("diagram_GeeU_U.eps")

c = canvas.canvas()
c.text(0, 0, r"\boldmath $\ell$", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("diagram_Btolnu_ell.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}$ for $\Upsilon(1S)$, $\Upsilon(2S)$, and $\Upsilon(3S)$", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title_GeeU.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}$ for $\psi(2S)$ from Radiative Returns", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title_Geepsi.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma(\psi(2S) \to e^+e^-)$", [text.halign.boxcenter])
c.writeEPSfile("title_Geepsi_again.eps")

c = canvas.canvas()
c.text(0, 0, r"at $E_{beam}$ = 3770 MeV", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title_Geepsi2.eps")

c = canvas.canvas()
c.text(0, 0, r"$f_D$ from $D^+ \to \mu^+ \nu$", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title_fD.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}$ and $f_D$:", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title.eps")

c = canvas.canvas()
c.text(0, 0, r"Testing the Flavors of Lattice QCD", [text.halign.boxcenter])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("title2.eps")

# c = canvas.canvas()
# c.text(0, 0, r"$\psi(3770)$ \par $\to \pi^+\pi^- J/\psi$", [text.parbox(2.5), text.halign.boxcenter, text.halign.flushcenter])
# c.writePDFfile("../pyx_tmp.pdf")
# os.system("xpdf -remote boingy -reload")
# c.writeEPSfile("psi_gamee2_3770.eps")

c = canvas.canvas()
c.text(0, 0, r"$\psi(3770)$")
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_3770.eps")

c = canvas.canvas()
c.text(0, 0, r"$\psi(2S)$")
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_2S.eps")

c = canvas.canvas()
c.text(0, 0, r"$\pi^+\pi^- J/\psi$ events/4 MeV")
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_ylabel.eps")

c = canvas.canvas()
c.text(0, 0, r"$E_\gamma$ (missing)")
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_xlabel.eps")

# c = canvas.canvas()
# t = [graph.axis.tick.tick(4, label=r"$\Gamma_{ee}(\Upsilon) \ \frac{2S}{1S}$"), \
#      graph.axis.tick.tick(3, label=r"$f_D$"), \
#      graph.axis.tick.tick(2, label=r"$\Gamma_{ee}(\psi)$"), \
#      graph.axis.tick.tick(1, label=r"$f_B$")]
# g = graph.graphxy(width=3, height=6, x=graph.axis.linear(title="LQCD/Experiment", min=0.7, max=1.3), y=graph.axis.linear(min=0.5, max=4.5, manualticks=t, parter=None))
# g.plot(graph.data.list([(4, 1.04, 0.11), (3, 0.90, 0.10)], x=2, dx=3, y=1), [graph.style.symbol(graph.style.symbol.circle, size=0.08*unit.v_cm, symbolattrs=[deco.filled()]), graph.style.errorbar()])
# c.insert(g)
# g.finish()
# p = path.path(path.moveto(*g.pos(1, 0.5)), path.lineto(*g.pos(1, 4.5)))
# c.stroke(p, [style.linestyle.dashed])
# where = g.pos(1, 2)
# c.text(where[0], where[1], r"No LQCD yet", [text.halign.boxcenter, text.valign.middle])
# where = g.pos(1, 1)
# c.text(where[0], where[1], r"No Experiment", [text.halign.boxcenter, text.valign.middle])
# c.writePDFfile("../pyx_tmp.pdf")
# os.system("xpdf -remote boingy -reload")
# c.writeEPSfile("new_ratio_plot.eps")

c = canvas.canvas()
t = [graph.axis.tick.tick(4, label=r"$\Gamma_{ee}(\Upsilon) \ \frac{2S}{1S}$"), \
     graph.axis.tick.tick(3, label=r"$f_D$") ]
g = graph.graphxy(width=3, height=3, x=graph.axis.linear(title="LQCD/Experiment", min=0.7, max=1.3), y=graph.axis.linear(min=2.5, max=4.5, manualticks=t, parter=None))
g.plot(graph.data.list([(4, 1.04, 0.11)], x=2, dx=3, y=1), [graph.style.symbol(graph.style.symbol.circle, size=0.08*unit.v_cm, symbolattrs=[deco.filled()]), graph.style.errorbar()])
c.insert(g)
g.finish()
p = path.path(path.moveto(*g.pos(1, 2.5)), path.lineto(*g.pos(1, 4.5)))
c.stroke(p, [style.linestyle.dashed])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("new_ratio_plot.eps")

c = canvas.canvas()
t = [graph.axis.tick.tick(4, label=r"$\Gamma_{ee}(\Upsilon) \ \frac{2S}{1S}$"), \
     graph.axis.tick.tick(3, label=r"$f_D$") ]
g = graph.graphxy(width=3, height=3, x=graph.axis.linear(title="LQCD/Experiment", min=0.7, max=1.3), y=graph.axis.linear(min=2.5, max=4.5, manualticks=t, parter=None))
g.plot(graph.data.list([(4, 1.04, 0.11), (3, 0.90, 0.10)], x=2, dx=3, y=1), [graph.style.symbol(graph.style.symbol.circle, size=0.08*unit.v_cm, symbolattrs=[deco.filled()]), graph.style.errorbar()])
c.insert(g)
g.finish()
p = path.path(path.moveto(*g.pos(1, 2.5)), path.lineto(*g.pos(1, 4.5)))
c.stroke(p, [style.linestyle.dashed])
c.writePDFfile("../pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("new_ratio_plot2.eps")

c = canvas.canvas()
c.text(0, 0, r"$e^+e^-$", [color.rgb.red])
c.writeEPSfile("ups_spectrum2_ee.eps")

c = canvas.canvas()
c.text(0, 0, r"$\mu^+\mu^-$", [color.rgb.red])
c.writeEPSfile("ups_spectrum2_mm.eps")

c = canvas.canvas()
c.text(0, 0, r"$\pi\pi$", [color.rgb.blue])
c.writeEPSfile("ups_spectrum2_pipi.eps")

c = canvas.canvas()
c.text(0, 0, r"$\gamma$", [color.rgb.blue])
c.writeEPSfile("ups_spectrum2_gamma.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon(1S)$")
c.writeEPSfile("ups_spectrum2_u1.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon(2S)$")
c.writeEPSfile("ups_spectrum2_u2.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon(3S)$")
c.writeEPSfile("ups_spectrum2_u3.eps")

c = canvas.canvas()
c.text(0, 0, r"$\chi_b(1P)$")
c.writeEPSfile("ups_spectrum2_c1.eps")

c = canvas.canvas()
c.text(0, 0, r"$\chi_b(2P)$")
c.writeEPSfile("ups_spectrum2_c2.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}$ ratio $\times$ mass ratio$^2$")
c.writeEPSfile("dependence_ylabel.eps")

c = canvas.canvas()
c.text(0, 0, r"Scale of lattice spacing in GeV$^{-2}$")
c.writeEPSfile("dependence_xlabel.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}(\Upsilon)$")
c.writeEPSfile("just_GeeU.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}(\psi)$")
c.writeEPSfile("just_Geepsi.eps")

c = canvas.canvas()
c.text(0, 0, r"$f_B$")
c.writeEPSfile("just_fB.eps")

c = canvas.canvas()
c.text(0, 0, r"$f_D$")
c.writeEPSfile("just_fD.eps")

c = canvas.canvas()
c.text(0, 0, r"\sf Outline")
c.writeEPSfile("title_outline.eps")
