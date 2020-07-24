import ROOT
from array import array
import math

def fcn(npar, gin, f, par, iflag):
    f = math.pow(par[0],2) + math.pow(par[1],2) + math.pow(par[2],2)
    print f

eff = 0
fcn(None, None, eff, [1, 2, 3], None)
print eff


h = ROOT.TH1F("h", "test", 100, -2, 2)
h.FillRandom("gaus", 1000)
h.Fit("gaus")

gMinuit = ROOT.gROOT.GetGlobal( "gMinuit", 1 )
plist = array('d',9*[0])
ierflg = array('i',[0])
gMinuit.mnexcm("SHOW COR", plist, 9, ierflg)
gMinuit.mnexcm("SHOW COV", plist, 9, ierflg)


