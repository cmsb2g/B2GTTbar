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


parser.add_option('--highmass', action='store_true',
                  dest='highmass',
                  default = False,
                  help='High mass?')



(options, args) = parser.parse_args(sys.argv)
argv = []



import ROOT


xs_ttbar = 831.
nev_ttbar = 92925926.

lumi = 36220. # pb-1

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
    10231928., #100To200   10 / 214 failed
    4963240.,  #200To400 
    1963464.,  #400To600 
    3722395.,  #600To800
    1540477.,  #800To1200 
    246737.,   #1200To2500 12 / 54 failed  (total = 6817172)
    253561.,   #2500ToInf 
    ]
xs_qcd = [
    27990000., # 100To200
    1712000.,  # 200To300
    347700.,   # 300To500
    32100.,    # 500To700
    6831.,     # 700To1000
    1207.,     # 1000To1500
    119.9,     # 1500To2000
    25.24,     # 2000ToInf 
    ]

nev_qcd = [
    82073090., # 100To200  
    18523829., # 200To300  
    16830696., # 300To500  
    19199088., # 500To700  
    15621634., # 700To1000 
    4980387.,  # 1000To1500
    3846616.,  # 1500To2000
    1960245.   # 2000ToInf 
    ]

xs_singletop = [
    136.02 * 0.322,#singletop_tchanneltop_outfile.root
    80.95 * 0.322, #singletop_tchannel_outfile.root
    35.6,          #singletop_tW_outfile.root
    35.6,          #singletop_tWantitop_outfile.root
    3.36           #singletop_schannel_outfile.root    
    ]
nev_singletop = [
    32808300.,
    19825855.,
    998400.,
    985000.,
    1000000.
    ]


    
ROOT.gStyle.SetOptStat(000000)

instring = ''
if options.highmass :
    instring = '_highmass'

ttbarfile = ROOT.TFile('ttbar' + instring + '_outfile.root')
if 'Electron' not in options.hist : 
    datafile = ROOT.TFile('singlemu' + instring + '_outfile.root')
else :
    datafile = ROOT.TFile('singleel' + instring + '_outfile.root')

wjetsfiles = [
    ROOT.TFile('wjets100to200' + instring + '_outfile.root'),
    ROOT.TFile('wjets200to400' + instring + '_outfile.root'),
    ROOT.TFile('wjets400to600' + instring + '_outfile.root'),
    ROOT.TFile('wjets600to800' + instring + '_outfile.root'),
    ROOT.TFile('wjets800to1200' + instring + '_outfile.root'),
    ROOT.TFile('wjets1200to2500' + instring + '_outfile.root'),
    ROOT.TFile('wjets2500toinf' + instring + '_outfile.root'),
    ]

wjets_colors = [ 
    ROOT.kWhite,ROOT.kRed - 9, ROOT.kRed - 7, ROOT.kRed - 4, ROOT.kRed, ROOT.kRed +1, ROOT.kRed +2   ]

qcdfiles = [
    ROOT.TFile('qcd100' + instring + '_outfile.root'),
    ROOT.TFile('qcd200' + instring + '_outfile.root'),
    ROOT.TFile('qcd300' + instring + '_outfile.root'),
    ROOT.TFile('qcd500' + instring + '_outfile.root'),
    ROOT.TFile('qcd700' + instring + '_outfile.root'),
    ROOT.TFile('qcd1000' + instring + '_outfile.root'),
    ROOT.TFile('qcd1500' + instring + '_outfile.root'),
    ROOT.TFile('qcd2000' + instring + '_outfile.root'),
    ]

singletopfiles = [
    ROOT.TFile('singletop_tchanneltop' + instring + '_outfile.root'),
    ROOT.TFile('singletop_tchannel' + instring + '_outfile.root'),
    ROOT.TFile('singletop_tW' + instring + '_outfile.root'),
    ROOT.TFile('singletop_tWantitop' + instring + '_outfile.root'),
    ROOT.TFile('singletop_schannel' + instring + '_outfile.root'),
    ]
    
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


    hqcd_list = []
    hqcd = None
    hqcd_stack = ROOT.THStack("hqcd_stack", "hqcd_stack")

    for iqcd in xrange(len(qcdfiles)) :
        htemp = qcdfiles[iqcd].Get(options.hist + str(istage))
        htemp.Scale( xs_qcd[iqcd] / nev_qcd[iqcd] * lumi )
        hqcd_list.append( htemp )
        #htemp.SetFillColor( qcd_colors[iqcd] )
        if iqcd == 0 :
            hqcd = htemp.Clone('hqcd')
        else :
            hqcd.Add( htemp )
        hqcd_stack.Add( htemp )
    #hqcd_stack.Draw("hist")


    hqcd.SetFillColor( ROOT.kYellow )
    


    hsingletop_list = []
    hsingletop = None
    hsingletop_stack = ROOT.THStack("hsingletop_stack", "hsingletop_stack")

    for isingletop in xrange(len(singletopfiles)) :
        htemp = singletopfiles[isingletop].Get(options.hist + str(istage))
        htemp.Scale( xs_singletop[isingletop] / nev_singletop[isingletop] * lumi )
        hsingletop_list.append( htemp )
        #htemp.SetFillColor( singletop_colors[isingletop] )
        if isingletop == 0 :
            hsingletop = htemp.Clone('hsingletop')
        else :
            hsingletop.Add( htemp )
        hsingletop_stack.Add( htemp )
    #hsingletop_stack.Draw("hist")


    hsingletop.SetFillColor( ROOT.kMagenta )
    
    
    hqcd.Rebin(10)
    hsingletop.Rebin(10)
    hwjets.Rebin(10)
    httbar.Rebin(10)
    hdata.Rebin(10)

    hstack = ROOT.THStack("bkgs", "")
    hstack.Add( hqcd )
    hstack.Add( hsingletop )
    hstack.Add( hwjets )
    hstack.Add( httbar )


    c1 = ROOT.TCanvas("c" + str(istage), "c" + str(istage) )


    
    hdata.Draw("e")
    hstack.Draw("hist same")
    maxval = max( hdata.GetMaximum(), hstack.GetMaximum() )
    hdata.SetMaximum( maxval * 1.2 )
    hdata.Draw("e same")
    

    leg = ROOT.TLegend(0.8, 0.8, 1.0, 1.0)
    leg.SetFillColor(0)
    leg.SetBorderSize(0)
    leg.AddEntry( hdata, 'Data', 'p')
    leg.AddEntry( httbar, 't#bar{t}', 'f')
    leg.AddEntry( hwjets, 'W+jets', 'f')
    leg.AddEntry( hsingletop, 'Single top', 'f')
    leg.AddEntry( hqcd, 'QCD', 'f')
    leg.Draw()
    
    c1.Update()

    c1.Print("plot_" + options.hist + str(istage) + instring + ".pdf", "pdf")
    c1.Print("plot_" + options.hist + str(istage) + instring + ".png", "png")
    objs.append( [hdata, httbar, hwjets, c1, hstack, leg] )
