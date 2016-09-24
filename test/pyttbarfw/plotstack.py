#! /usr/bin/env python


## _________                _____.__                            __  .__               
## \_   ___ \  ____   _____/ ____\__| ____  __ ______________ _/  |_|__| ____   ____  
## /    \  \/ /  _ \ /    \   __\|  |/ ___\|  |  \_  __ \__  \\   __\  |/  _ \ /    \ 
## \     \___(  <_> )   |  \  |  |  / /_/  >  |  /|  | \// __ \|  | |  (  <_> )   |  \
##  \______  /\____/|___|  /__|  |__\___  /|____/ |__|  (____  /__| |__|\____/|___|  /
##         \/            \/        /_____/                   \/                    \/ 
import sys
import math
import array as array
from optparse import OptionParser

parser = OptionParser()

parser.add_option('--ttbarfile', type='string', action='store',
                  dest='ttbarfile',
                  default = '',
                  help='ttbar file string')


parser.add_option('--datafile', type='string', action='store',
                  dest='datafile',
                  default = '',
                  help='Data file string')


parser.add_option('--hist', type='string', action='store',
                  dest='hist',
                  default = '',
                  help='Hist string')




(options, args) = parser.parse_args(sys.argv)
argv = []



import ROOT



ttbarfile = ROOT.TFile(options.ttbarfile)
datafile = ROOT.TFile(options.datafile)


httbar = ttbarfile.Get(options.hist)
hdata = datafile.Get(options.hist)


lumi = 20000. # pb-1
xs_ttbar = 831.
nev_ttbar = 92925926.

httbar.Sumw2()
hdata.SetMarkerStyle(20)

httbar.Scale( xs_ttbar / nev_ttbar * lumi ) 
httbar.SetFillColor(ROOT.kGreen)
httbar.Rebin(5)
hdata.Rebin(5)
hdata.Draw("e")
httbar.Draw("hist same")
hdata.Draw("e same")
