import os
from pyx import *

text.defaulttexrunner = text.texrunner(mode="latex", lfs="12pt", errordebug=1)

c = canvas.canvas()
c.text(0, 0, r"\fbox{$f_{B}$}", [text.halign.boxcenter])
c.text(0, -0.65, r"theory only", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_fB.eps")

c = canvas.canvas()
c.text(0, 0, r"\fbox{$f_{D}$}", [text.halign.boxcenter])
c.text(0, -0.65, r"theory vs", [text.halign.boxcenter])
c.text(0, -1, r"experiment", [text.halign.boxcenter])
c.text(0, -1.5, r"$D^+ \to \mu^+ \nu$", [text.halign.boxcenter, color.rgb(0,0,0.546875)])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_fD.eps")

c = canvas.canvas()
c.text(0, 0, r"\fbox{$\Gamma_{ee}(\Upsilon)$}", [text.halign.boxcenter])
c.text(0, -0.65, r"theory vs", [text.halign.boxcenter])
c.text(0, -1, r"experiment", [text.halign.boxcenter])
c.text(0, -1.5, r"$\Upsilon \to e^+e^-$", [text.halign.boxcenter, color.rgb(0.546875,0,0)])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_GeeU.eps")

c = canvas.canvas()
c.text(0, 0, r"\fbox{$\Gamma_{ee}(\psi)$}", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_Geepsi.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon$", [text.halign.boxcenter, color.rgb(0.546875,0,0)])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_justU.eps")

c = canvas.canvas()
c.text(0, 0, r"$\Upsilon$", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("motivation_table_pyx_justU2.eps")

c = canvas.canvas()
c.text(0, 0, r"$\psi(3770) \to \pi^+\pi^- J/\psi$", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_pyx_3770.eps")

c = canvas.canvas()
c.text(-0.3, 0, r"$e^+e^- \to$", [text.halign.boxright])
c.text(0, 0, r"\boldmath $\gamma$", [text.halign.boxcenter, color.cmyk.Purple])
c.text(0.2, 0, r"$\psi(2S)$", [text.halign.boxleft])
c.text(1.7, -0.5, r"$\psi(2S) \to \pi^+\pi^- J/\psi$", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_pyx_psi2s.eps")

c = canvas.canvas()
c.text(0, 0, r"$E_{\mbox{ }}$ (missing)", [text.halign.boxleft])
c.text(0.15, 0, r"\boldmath $\mbox{ }_\gamma$", [text.halign.boxleft, color.cmyk.Purple])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_pyx_missing.eps")

c = canvas.canvas()
c.text(0, 0, r"Events/2 MeV", [text.halign.boxcenter])
c.writePDFfile("pyx_tmp.pdf")
os.system("xpdf -remote boingy -reload")
c.writeEPSfile("psi_gamee2_pyx_events.eps")



