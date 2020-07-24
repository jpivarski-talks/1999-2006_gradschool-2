from pyx import *
text.defaulttexrunner = text.texrunner(mode="latex", lfs="12pt", errordebug=1)

c = canvas.canvas()
c.text(0, 0, r"$\Gamma_{ee}(2S)/\Gamma_{ee}(1S) \, \times \, {M_{\Upsilon(2S)}}^2/{M_{\Upsilon(1S)}}^2$", [text.halign.boxcenter])
c.writeEPSfile("part_geerat.eps")

