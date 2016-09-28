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

parser.add_option('--hist', type='string', action='store',
                  dest='hist',
                  default = '',
                  help='Hist string')




(options, args) = parser.parse_args(sys.argv)
argv = []



import ROOT


xs_ttbar = 831.
nev_ttbar = 92925926.
lumi = 20000. # pb-1

xs_wjets = [
    1345.,     #100To200  
    359.7,     #200To400  
    48.91,     #400To600  
    12.05,     #600To800  
    5.501,     #800To1200 
    1.329,     #1200To2500
    0.03216,   #2500ToInf 
    ]

nev_wjets = [
    26304033., #100To200   10 / 214 failed
    4963240.,  #200To400 
    1963464.,  #400To600 
    3722395.,  #600To800
    6314257.,  #800To1200 
    5215198.,  #1200To2500 12 / 54 failed  (total = 6817172)
    253561.,   #2500ToInf 
    ]


ROOT.gStyle.SetOptStat(000000)


ttbarfile = ROOT.TFile('ttbar_outfile.root')
datafile = ROOT.TFile('singlemu_run2016.root')

wjetsfiles = [
    ROOT.TFile('wjets100to200_outfile.root'),
    ROOT.TFile('wjets200to400_outfile.root'),
    ROOT.TFile('wjets400to600_outfile.root'),
    ROOT.TFile('wjets600to800_outfile.root'),
    ROOT.TFile('wjets800to1200_outfile.root'),
    ROOT.TFile('wjets1200to2500_outfile.root'),
    ROOT.TFile('wjets2500toinf_outfile.root'),
    ]

wjets_colors = [ 
    ROOT.kWhite,ROOT.kRed - 9, ROOT.kRed - 7, ROOT.kRed - 4, ROOT.kRed, ROOT.kRed +1, ROOT.kRed +2   ]


objs = []

for istage in xrange(11) : 
    httbar = ttbarfile.Get(options.hist + str(istage))
    httbar.Sumw2()
    httbar.Scale( xs_ttbar / nev_ttbar * lumi ) 
    httbar.SetFillColor(ROOT.kGreen + 2)


    hdata = datafile.Get(options.hist + str(istage))
    hdata.SetMarkerStyle(20)


    hwjets_list = []
    hwjets = None
    hwjets_stack = ROOT.THStack("hwjets_stack", "hwjets_stack")

    for iwjet in xrange(len(wjetsfiles)) :
        htemp = wjetsfiles[iwjet].Get(options.hist + str(istage))
        htemp.Scale( xs_wjets[iwjet] / nev_wjets[iwjet] * lumi )
        hwjets_list.append( htemp )
        htemp.SetFillColor( wjets_colors[iwjet] )
        if iwjet == 0 :
            hwjets = htemp.Clone('hwjets')
        else :
            hwjets.Add( htemp )
        hwjets_stack.Add( htemp )
    #hwjets_stack.Draw("hist")


    hwjets.SetFillColor( ROOT.kRed )

    hwjets.Rebin(10)
    httbar.Rebin(10)
    hdata.Rebin(10)

    hstack = ROOT.THStack("bkgs", "")
    hstack.Add( hwjets )
    hstack.Add( httbar )


    c1 = ROOT.TCanvas("c" + str(istage), "c" + str(istage) )
    hdata.Draw("e")
    hstack.Draw("hist same")
    hdata.Draw("e same")

    leg = ROOT.TLegend(0.8, 0.8, 1.0, 1.0)
    leg.SetFillColor(0)
    leg.SetBorderSize(0)
    leg.AddEntry( hdata, 'Data', 'p')
    leg.AddEntry( httbar, 't#bar{t}', 'f')
    leg.AddEntry( hwjets, 'W+jets', 'f')
    leg.Draw()
    
    c1.Update()

    c1.Print("plot_" + options.hist + str(istage) + ".pdf", "pdf")
    c1.Print("plot_" + options.hist + str(istage) + ".png", "png")
    objs.append( [hdata, httbar, hwjets, c1, hstack, leg] )
