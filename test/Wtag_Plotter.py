#!it/usr/bin/env python
from optparse import OptionParser
from numpy import *
import CMS_lumi, tdrstyle
import ROOT
import array
import math
import time 

parser = OptionParser()

parser.add_option('--infile', type='string', action='store',
                  dest='infile',
                  default = "",
                  help='Input file')

parser.add_option('--maxEvents', type='int', action='store',
              default=-1,
              dest='maxEvents',
              help='Number of events to run. -1 is all events')

parser.add_option('--b2gtrees', action='store_true',
                  default=False,
                  dest='b2gtrees',
                  help='Are the ttrees produced using B2GTTbarb2gtrees.cc ?')

parser.add_option('--treeLocation', type='string', action='store',
                  dest='treeLocation',
                  default = '80xTTrees',# 'Last80xTrees',#
                  help='directory XXX where CRAB output ttrees created by NtupleReader are located /store/group/lpctlbsm/aparker/XXX') 

parser.add_option('--CSelect', action='store_true',
                  default=False,
                  dest='CSelect',
                  help='Are the histos made using LoopTree.cc (only makes sense to use with --b2gtrees) ?')

parser.add_option('--passTau21', action='store_true',
                  default=True,
                  dest='passTau21',
                  help='Plot the mass of W candidate passing tau21 cut')

parser.add_option('--failTau21', action='store_true',
                  default=True,
                  dest='failTau21',
                  help='Plot the mass of W candidate failing the tau21 cut')

parser.add_option('--PlotPtTypes', action='store_true',
              default=False,
              dest='PlotPtTypes',
              help='Do you want to plot the Pts of type 1 vs Type 2 W jet candidates???')

parser.add_option('--filestr', type='string', action='store',
                  dest='filestr',
                  default = "nom",
                  help='Label for plots')

parser.add_option('--Type2', action='store_true',
                  default=False,
                  dest='Type2',
                  help='Do you want to apply selection for type 2 tops as described in AN-16-215 ?')

parser.add_option('--minval', type='float', action='store',
                  dest='minval',
                  default = 0.,
                  help='Minval for the plot')

parser.add_option('--maxval', type='float', action='store',
                  dest='maxval',
                  default = 250.,
                  help='Maxval for the plot')

parser.add_option('--80X', action='store_true',
                  default=True,
                  dest='80X',
                  help='Are the ttrees produced using CMSSW 80X?')

parser.add_option('--nbins', type='int', action='store',
                  dest='nbins',
                  default = 25,
                  help='Nbins for the plot')

parser.add_option('--legleft',  action='store_true',
                  dest='legleft',
                  default = False,
                  help='Plot legend on the left')

parser.add_option('--pre',  action='store_true',
                  dest='pre',
                  default = False,
                  help='Plot selection before tog tag cut.')

parser.add_option('--Eldata',  action='store_true',
                  dest='Eldata',
                  default = False,
                  help='Plot only electron data')

parser.add_option('--Mudata',  action='store_true',
                  dest='Mudata',
                  default = False,
                  help='Plot only muon data')

parser.add_option('--allMC', action='store_true',
                  default=False,
                  dest='allMC',
                  help='Do you want to plot all MC? (or just ttjets)')

parser.add_option('--quickPlot', action='store_true',
                  default=False,
                  dest='quickPlot',
                  help='only plot lepton pt and tau21 ?')

parser.add_option('--ttSF', action='store_true',
                  default=False,
                  dest='ttSF',
                  help='Apply a ttbar scale factor computed here ?')

parser.add_option('--fixFit',  action='store_true',
                  dest='fixFit',
                  default = False,
                  help='Constrain the mean and sigma of Gaussian.')

(options, args) = parser.parse_args()
argv = []

startTime = time.time()

if options.b2gtrees and (not options.Type2):
    plotdir = 'b2gtree_WsubjetSF'
if options.b2gtrees and  options.Type2 :
    plotdir = 'b2gtree_JWjetSF'
if (not options.b2gtrees) and (not options.Type2):
    plotdir = 'B2GTTBARtree_WsubjetSF'
if ( not options.b2gtrees) and  options.Type2 :
    plotdir = 'B2GTTBARtree_WjetSF'
# define the scaling operations
#import Wtag_def as wd                   fix: find out how to import sys.arv from this script to Wtag_def.py
lumi = 12300.

def scaleST(hstT1_, hstT2_, hstT3_, hstT4_, ipt__):
    hstT_ = hstT1_.Clone()
    hstT_.Reset()
    hst34_ = hstT3_.Clone()
    hst34_.Reset()
    if hstT1_.Integral() > 0 : 
        hstT1_.Scale(lumi * 136.02 * 0.322 / 3279200. ) 
    else :
        print "st top bin {0} empty".format(int(ipt__))
        hstT1_.Scale( 0.)
    if hstT2_.Integral() > 0 : 
        hstT2_.Scale(lumi * 80.95 * 0.322/ 1682400. ) 
    else :
        print "st antitop bin {0} empty".format(int(ipt__))
        hstT2_.Scale( 0.)
    hst34_ = hstT3_.Clone()
    hst34_.SetDirectory(0)
    hst34_.Add(hstT4_)
    if hst34_.Integral() > 0 : 
        hst34_.Scale(lumi * 35.6 / (998400.+985000.) ) 
    else :
        print "st tW bin {0} empty".format(int(ipt__))
        hst34_.Scale( 0.)
    hstT_ = hstT1_.Clone()
    hstT_.SetDirectory(0)
    hstT_.Add(hstT2_)
    hstT_.Add(hst34_)
    return hstT_


def scaleTT(httbarT_, ipt__):
    if httbarT_ != None :
        if httbarT_.Integral() > 0 : 
            httbarT_.Scale(lumi* 831.76 /  91061600. ) 
            # t tbar - https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki
        else :
            print "tt {0} empty".format(httbarT_)
            httbarT_.Scale( 0.)
        return httbarT_
    else :
        print  "tt {0} empty".format(httbarT_)
        return None

def ScalettMC(httbar__, heldata__, hmudata__ , hstT__ , hwjetsT__, intMin, intMax ) :
    # Find the tt scale factor
    sf = 0.
    scalefactortt = 0.
    if options.Eldata : 
        hdata__ = heldata__.Clone()
        hdata__.SetDirectory(0)
    if options.Mudata : 
        hdata__ = hmudata__.Clone()
        hdata__.SetDirectory(0)

    hMC__ = httbar__.Clone()
    hMC__.SetDirectory(0)
    if options.allMC:
        hMC__.Add(hstT__)
        hMC__.Add(hwjetsT__)

    intMinbin = hMC__.FindBin(intMin)
    intMaxbin = hMC__.FindBin(intMax)

    if (hdata__.Integral() > 0.) and (hMC__.Integral() > 0.) and options.ttSF: 
        diff = float(hdata__.Integral(intMinbin, intMaxbin))- float(  hMC__.Integral(intMinbin, intMaxbin)  )
        sf = abs(    diff/ float(  httbar__.Integral(intMinbin, intMaxbin)     +1.  )        )     
    if not options.ttSF: 
        sf = 1.

    scalefactortt = sf 
    if options.ttSF: print "tt SCALE FACTOR APPLIED WAS : " + str(scalefactortt)

    if httbar__.Integral() > 0 : 
        httbar__.Scale( scalefactortt ) 
    else :
        print "tt bin  empty when using scalettMC() "
        httbar__.Scale( 0.)

    return httbar__ 

def scaleWjets(hwjetsT1_, hwjetsT2_, hwjetsT3_, hwjetsT4_, hwjetsT5_, hwjetsT6_, hwjetsT7_, ipt__) :
    hwjetsT_ = hwjetsT1_.Clone()
    hwjetsT_.Reset()
    scalefactor = 1.
    kfactorw = 1.21
    if hwjetsT1_.Integral() > 0 : 
        hwjetsT1_.Scale(lumi * kfactorw * scalefactor *1345. / 27529599. ) 
    else :
        print "w+jets 100to200 b{0} empty".format(str(ipt__))
        hwjetsT1_.Scale( 0.)
    if hwjetsT2_.Integral() > 0 : 
        hwjetsT2_.Scale(lumi *kfactorw * scalefactor * 359.7 / 4963240.) 
    else :
        print "w+jets 200to400 b{0} empty".format(str(ipt__))
        hwjetsT2_.Scale( 0.)
    if hwjetsT3_.Integral() > 0 : 
        hwjetsT3_.Scale(lumi * kfactorw * scalefactor *48.91/ 1963464. ) 
    else :
        print "w+jets 400to600 b{0} empty".format(str(ipt__))
        hwjetsT3_.Scale( 0.)
    if hwjetsT4_.Integral() > 0 : 
        hwjetsT4_.Scale(lumi * kfactorw * scalefactor * 12.05/  3722395.) 
    else :
        print "w+jets 600to800 b{0} empty".format(str(ipt__))
        hwjetsT4_.Scale( 0.)
    if hwjetsT5_.Integral() > 0 : 
        hwjetsT5_.Scale(lumi *kfactorw * scalefactor * 5.501 / 6314257.) 
    else :
        print "w+jets 800to1200 b{0} empty".format(str(ipt__))
        hwjetsT5_.Scale( 0.)
    if hwjetsT6_.Integral() > 0 : 
        hwjetsT6_.Scale(lumi  * kfactorw * scalefactor *1.329 / 6768156.) 
    else :
        print "w+jets 1200to2500 b{0} empty".format(str(ipt__))
        hwjetsT6_.Scale( 0.)
    if hwjetsT7_.Integral() > 0 : 
        hwjetsT7_.Scale(lumi * kfactorw * scalefactor * 0.03216 / 253561.) 
    else :
        print "w+jets 2500toInf b{0} empty".format(str(ipt__))
        hwjetsT7_.Scale( 0.)

    hwjetsT_ = hwjetsT1_.Clone()
    hwjetsT_.SetDirectory(0)
    hwjetsT_.Add(hwjetsT2_)
    hwjetsT_.Add(hwjetsT3_)
    hwjetsT_.Add(hwjetsT4_)
    hwjetsT_.Add(hwjetsT5_)
    hwjetsT_.Add(hwjetsT6_)
    hwjetsT_.Add(hwjetsT7_)
    return hwjetsT_

def ScaleStackPlot(name, xtitle, scaleFactor, TheRebinNum, xlow, xhigh, ttbarHist, st1Hist,  st2Hist, st3Hist, st4Hist, wjets1Hist , wjets2Hist, wjets3Hist, wjets4Hist, wjets5Hist, wjets6Hist, wjets7Hist, dataHist, mudataHist, eldataHist, intMin, intMax ) :

    #scale by luminosity and cross section
    SttbarHist = scaleTT(ttbarHist, ipt)
    if SttbarHist == None : 
        print "The ttbar histogram for plot of name {} and title {} is empty or not properly read.".format(name, xtitle)
        return None
    #scale ttjets MC to match data
    if st1Hist != None :
	    hstT = st1Hist.Clone()
	    hstT.Add( st2Hist )
	    hstT.Add( st3Hist )
	    hstT.Add( st4Hist )

	    hwjetsT = wjets1Hist.Clone()
	    hwjetsT.Add( wjets2Hist )
	    hwjetsT.Add( wjets3Hist )
	    hwjetsT.Add( wjets4Hist )
	    hwjetsT.Add( wjets5Hist )
	    hwjetsT.Add( wjets6Hist )
	    hwjetsT.Add( wjets7Hist )

	    SttbarHist = ScalettMC( SttbarHist ,  dataHist, mudataHist , hstT , hwjetsT , intMin, intMax)

    rebinnum = TheRebinNum
    SttbarHist.Rebin( rebinnum )
    dataHist.Rebin( rebinnum )
    eldataHist.Rebin( rebinnum )
    mudataHist.Rebin( rebinnum )

    if options.allMC :
        SstHist = scaleST(st1Hist, st2Hist, st3Hist, st4Hist, ipt) 
        SwjetsHist = scaleWjets(wjets1Hist , wjets2Hist, wjets3Hist, wjets4Hist, wjets5Hist, wjets6Hist, wjets7Hist, ipt)
        SstHist.Rebin(  rebinnum )
        SwjetsHist.Rebin(  rebinnum )


    mcStack = ROOT.THStack( name ,';  ;Number of Events') #Mass_{SD subjet_{0} }
    if options.allMC :
        SstHist.SetFillColor(ROOT.kCyan )
        SwjetsHist.SetFillColor(ROOT.kRed)
        mcStack.Add( SwjetsHist)
        mcStack.Add( SstHist)
    SttbarHist.SetFillColor(ROOT.kGreen + 2)
    mcStack.Add( SttbarHist)

    theCanvas = ROOT.TCanvas(name, name)
    theCanvas.SetFillColor(0)
    theCanvas.SetBorderMode(0)
    theCanvas.SetFrameFillStyle(0)
    theCanvas.SetFrameBorderMode(0)
    theCanvas.SetLeftMargin( L/W )
    theCanvas.SetRightMargin( R/W )
    theCanvas.SetTopMargin( T/H )
    theCanvas.SetBottomMargin( B/H )
    theCanvas.SetTickx(0)
    theCanvas.SetTicky(0)
    dataHist.SetMarkerStyle(20)
    mudataHist.SetMarkerStyle(20)
    eldataHist.SetMarkerStyle(20)
    
    dataHist.GetXaxis().SetLimits(xlow,xhigh)
    eldataHist.GetXaxis().SetLimits(xlow,xhigh)
    mudataHist.GetXaxis().SetLimits(xlow,xhigh)
    
    SttbarHist.GetXaxis().SetLimits(xlow,xhigh)
    if options.allMC :
        SstHist.GetXaxis().SetLimits(xlow,xhigh)
        SwjetsHist.GetXaxis().SetLimits(xlow,xhigh)
    
    max1 = mudataHist.GetMaximum()
    max2 = mcStack.GetMaximum()
    dataHist.SetMaximum(   max (max1,max2) * 1.618 )
    eldataHist.SetMaximum( max (max1,max2) * 1.618 )
    mudataHist.SetMaximum( max (max1,max2) * 1.618 )

    dataHist.GetYaxis().SetTitleOffset(1.9)
    eldataHist.GetYaxis().SetTitleOffset(1.9)
    mudataHist.GetYaxis().SetTitleOffset(1.9)
    eldataHist.SetXTitle(xtitle)
    eldataHist.SetYTitle("Events")
    mudataHist.SetXTitle(xtitle)
    mudataHist.SetYTitle("Events")
    dataHist.SetXTitle(xtitle)
    dataHist.SetYTitle("Events")
    eldataHist.BufferEmpty(1)
    eldataHist.GetXaxis().SetTitleSize(0.057)
    eldataHist.GetYaxis().SetTitleSize(0.057)
    dataHist.BufferEmpty(1)
    dataHist.GetXaxis().SetTitleSize(0.057)
    dataHist.GetYaxis().SetTitleSize(0.057)
    mudataHist.BufferEmpty(1)
    mudataHist.GetXaxis().SetTitleSize(0.057)
    mudataHist.GetYaxis().SetTitleSize(0.057)      
    binSizeMuDataPt = mudataHist.GetBinWidth(0)
    binSizeMCPt = SttbarHist.GetBinWidth(0)
    print "Bin size: data {0:1.2f}, MC  {1:1.2f}- rebinnum is {2:1.0f}".format(binSizeMuDataPt, binSizeMCPt,  rebinnum )

    if options.Eldata :
        eldataHist.Draw('e')
    if options.Mudata :
        mudataHist.Draw('e')
    if not (options.Mudata and options.Eldata ) :
        dataHist.Draw('e')

    mcStack.Draw("histsame")
    mcStack.GetXaxis().SetLimits(xlow,xhigh)
    mcStack.SetMaximum( max (max1,max2) * 1.618 )


    if options.Eldata :
        #eldataHist.Draw('e same')
        eldataHist.Draw('esamex0')
        eldataHist.Draw('axis same')
    elif options.Mudata :
        mudataHist.Draw('esamex0')
        mudataHist.Draw('e same')
        mudataHist.Draw('axis same')
    elif not (options.Mudata and options.Eldata ) :
        dataHist.Draw('esamex0')
        #dataHist.Draw('e same')
        dataHist.Draw('axis same')


    CMS_lumi.CMS_lumi(theCanvas, iPeriod, iPos)

    leg = ROOT.TLegend(0.7,0.7,0.9,0.9)
    leg.SetFillColor(0)
    leg.SetBorderSize(0)

    if options.Eldata :
        leg.AddEntry( eldataHist, 'Electron Data', 'p')
    elif options.Mudata :
        leg.AddEntry( mudataHist, 'Muon Data', 'p')
    elif not (options.Mudata and options.Eldata ) :
        leg.AddEntry( dataHist, 'Data', 'p')


    leg.AddEntry( SttbarHist, 't#bar{t}', 'f')
    if options.allMC :
        leg.AddEntry( SwjetsHist, 'W + jets', 'f')
        leg.AddEntry( SstHist, 'Single Top', 'f')
    leg.Draw()

    theCanvas.Update()
    theCanvas.Draw()
    if options.Mudata :
        theCanvas.Print(plotdir + '/MuData/'  + options.treeLocation + '/' + name    +  options.filestr + '.png', 'png' )
        theCanvas.Print(plotdir + '/MuData/'  + options.treeLocation + '/' + name    +  options.filestr + '.pdf', 'pdf' )
        theCanvas.Print(plotdir + '/MuData/'  + options.treeLocation + '/' + name    +  options.filestr + '.root', 'root' )
    elif options.Eldata :
        theCanvas.Print(plotdir + '/ElData/' + options.treeLocation + '/' + name    + options.filestr + '.png', 'png' )
        theCanvas.Print(plotdir + '/ElData/' + options.treeLocation + '/' + name    + options.filestr + '.pdf', 'pdf' )
        theCanvas.Print(plotdir + '/ElData/' + options.treeLocation + '/' + name    + options.filestr + '.root', 'root' )
    elif not (options.Mudata and options.Eldata):
        theCanvas.Print(plotdir + '/AllData/'  + options.treeLocation + '/' + name     +  options.filestr + '.png', 'png' )
        theCanvas.Print(plotdir + '/AllData/'  + options.treeLocation + '/' + name     +  options.filestr + '.pdf', 'pdf' )
        theCanvas.Print(plotdir + '/AllData/'  + options.treeLocation + '/' + name     +  options.filestr + '.root', 'root' )


#set the tdr style
tdrstyle.setTDRStyle()

#change the CMS_lumi variables (see CMS_lumi.py)

CMS_lumi.lumi_13TeV = "12.3 fb^{-1}"
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

iPos = 11
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4

H_ref = 600; 
W_ref = 800; 
W = W_ref
H  = H_ref


# references for T, B, L, R
T = 0.08*H_ref
B = 0.12*H_ref 
L = 0.12*W_ref
R = 0.04*W_ref


ROOT.gStyle.SetTitleOffset(1.0, "Y")

datatype = 'Alldata_'
if options.Mudata :
    datatype = 'Mudata_'
if options.Eldata :
    datatype = 'Eldata_'

type2 = '_type1_'
if options.Type2 : type2 = '_type2_'
 

if options.b2gtrees:
    if not options.pre :
        fout= ROOT.TFile('./Joutput80xplotter/JWtag'+type2+datatype+'highPtSF_80x_' + options.infile + '_' + options.treeLocation+ '.root', "RECREATE")
    if options.pre :
        fout= ROOT.TFile('./Joutput80xplotter/JWtag' +type2+datatype+'highPtSF_preWTag_80x_'+ options.infile + '_' + options.treeLocation+'.root', "RECREATE")
if not options.b2gtrees:
    if not options.pre :
        fout= ROOT.TFile('./output80xplotter/Wtag'+type2+datatype+'highPtSF_80x_' + options.treeLocation +'_'+ options.infile  + '.root', "RECREATE")
    if options.pre :
        fout= ROOT.TFile('./output80xplotter/Wtag'+type2+datatype+'highPtSF_preWTag_80x_' + options.treeLocation+'_'+options.infile + '.root', "RECREATE")
            
ptBs =  array.array('d', [200., 300., 400., 500., 800., 200., 800.,800.])
nptBs = len(ptBs) - 1


hpeak = ROOT.TH1F("hpeak", " ;p_{T} of SD subjet 0 (GeV); JMS ",  nptBs, ptBs)  ##frac{Mean Mass_{data}}{Mean Mass_{MC}}
hwidth = ROOT.TH1F("hwidth", " ;p_{T} of SD subjet 0 (GeV); JMR ", nptBs, ptBs) ##frac{#sigma_{data}}{#sigma_{MC}}

hpeakmu = ROOT.TH1F("hpeakmu", " ;p_{T} of SD subjet 0 (GeV); JMS ",  nptBs, ptBs)  ##frac{Mean Mass_{data}}{Mean Mass_{MC}}
hwidthmu = ROOT.TH1F("hwidthmu", " ;p_{T} of SD subjet 0 (GeV); JMR ", nptBs, ptBs) ##frac{#sigma_{data}}{#sigma_{MC}}

hpeakel = ROOT.TH1F("hpeakel", " ;p_{T} of SD subjet 0 (GeV); JMS ",  nptBs, ptBs)  ##frac{Mean Mass_{data}}{Mean Mass_{MC}}
hwidthel = ROOT.TH1F("hwidthel", " ;p_{T} of SD subjet 0 (GeV); JMR ", nptBs, ptBs) ##frac{#sigma_{data}}{#sigma_{MC}}


if options.pre :
    hNpassDataPre = ROOT.TH1F("hNpassDataPre", " ;;  ", nptBs, ptBs) 
    hNpassMuDataPre = ROOT.TH1F("hNpassMuDataPre", " ;;  ", nptBs, ptBs) 
    hNpassElDataPre = ROOT.TH1F("hNpassElDataPre", " ;;  ", nptBs, ptBs) 
    hNpassMCPre = ROOT.TH1F("hNpassMCPre", " ;;  ", nptBs, ptBs) 
    hmeanDataPre = ROOT.TH1F("hmeanDataPre", " ;;  ", nptBs, ptBs) 
    hmeanMuDataPre = ROOT.TH1F("hmeanMuDataPre", " ;;  ", nptBs, ptBs) 
    hmeanElDataPre = ROOT.TH1F("hmeanElDataPre", " ;;  ", nptBs, ptBs) 
    hmeanMCPre = ROOT.TH1F("hmeanMCPre", " ;;  ", nptBs, ptBs) 
    hsigmaDataPre = ROOT.TH1F("hsigmaDataPre", " ;;  ", nptBs, ptBs) 
    hsigmaMuDataPre = ROOT.TH1F("hsigmaMuDataPre", " ;;  ", nptBs, ptBs) 
    hsigmaElDataPre = ROOT.TH1F("hsigmaElDataPre", " ;;  ", nptBs, ptBs) 
    hsigmaMCPre = ROOT.TH1F("hsigmaMCPre", " ;;  ", nptBs, ptBs) 
else:
    hNpassDataPost = ROOT.TH1F("hNpassDataPost", " ;;  ", nptBs, ptBs) 
    hNpassMuDataPost = ROOT.TH1F("hNpassMuDataPost", " ;;  ", nptBs, ptBs) 
    hNpassElDataPost = ROOT.TH1F("hNpassElDataPost", " ;;  ", nptBs, ptBs) 
    hNpassMCPost = ROOT.TH1F("hNpassMCPost", " ;;  ", nptBs, ptBs) 
    hscale = ROOT.TH1F("hscale", " ; ;  ", nptBs, ptBs)
    hDataEff = ROOT.TH1F("hDataEff", " ; ; ", nptBs, ptBs)
    hMuDataEff = ROOT.TH1F("hMuDataEff", " ; ; ", nptBs, ptBs)
    hElDataEff = ROOT.TH1F("hElDataEff", " ; ; ", nptBs, ptBs)
    hMCEff = ROOT.TH1F("hMCEff", " ; ; ", nptBs, ptBs)

# Create input file list
if options.b2gtrees or not options.allMC: dtypes = ['data', 'ttjets' ]
else : dtypes = ['data', 'ttjets','st1', 'st2', 'st3', 'st4', 'wjets1', 'wjets2', 'wjets3', 'wjets4', 'wjets5', 'wjets6', 'wjets7'] 


filesin = [] 

for idt, dt in enumerate(dtypes) :

    if options.b2gtrees :
        if options.maxEvents > 0. :
            filesin.append('./Joutput80xselector/Jhistos' +type2+'80x_' +str(options.maxEvents)+'_'+str(dt) + '_'+ options.filestr + '.root')
        else :
            filesin.append('./Joutput80xselector/Jhistos' +type2+'80x_' +str(dt) + '_'+ options.filestr + '.root')
    if not options.b2gtrees :
        if options.maxEvents > 0. :
            filesin.append('./output80xselector/histos' +type2+'80x_' +str(options.maxEvents)+'_'+str(dt) +  '_'+ options.treeLocation + '_'+ options.filestr +'.root')
        else :
            filesin.append('./output80xselector/histos' +type2+'80x_' +str(dt) +  '_'+ options.treeLocation + '_'+ options.filestr +'.root')    

print "Using input files :  {0}".format(str(filesin))

# Luminosity of input dataset
lumi = 12300. #2136.0

for ifin, fin in enumerate(filesin) :
    filei = ROOT.TFile.Open( fin )
    fileIs = ROOT.TFile(fin )
    fileIs.cd()
    print " data type {0}".format(str(dtypes[ifin])) 
    if str(dtypes[ifin]) == 'data' :
        #if not (options.Mudata and options.Eldata) :
        hdata = ( filei.Get("h_mWsubjet_Data"))

        if  options.Eldata :
            heldata = ( filei.Get("h_mWsubjet_ElData"))
            heldata.SetDirectory(0)
        if options.Mudata :
            hmudata = ( filei.Get("h_mWsubjet_MuData"))
            hmudata.SetDirectory(0)


        hdata_b1 =   filei.Get("h_mWsubjet_b1")
        hdata_b2 =   filei.Get("h_mWsubjet_b2")
        hdata_b3 =   filei.Get("h_mWsubjet_b3")
        hdata_b4 =   filei.Get("h_mWsubjet_b4")
        hdata_b5 =   filei.Get("h_mWsubjet_b5")


        hdata_b1.SetDirectory(0)
        hdata_b2.SetDirectory(0)
        hdata_b3.SetDirectory(0)
        hdata_b4.SetDirectory(0)
        hdata_b5.SetDirectory(0)


        heldata_b1 =   filei.Get("h_mWsubjet_b1e")
        heldata_b2 =   filei.Get("h_mWsubjet_b2e")
        heldata_b3 =   filei.Get("h_mWsubjet_b3e")
        heldata_b4 =   filei.Get("h_mWsubjet_b4e")
        heldata_b5 =   filei.Get("h_mWsubjet_b5e")


        heldata_b1.SetDirectory(0)
        heldata_b2.SetDirectory(0)
        heldata_b3.SetDirectory(0)
        heldata_b4.SetDirectory(0)
        heldata_b5.SetDirectory(0)



        hmudata_b1 =   filei.Get("h_mWsubjet_b1m")
        hmudata_b2 =   filei.Get("h_mWsubjet_b2m")
        hmudata_b3 =   filei.Get("h_mWsubjet_b3m")
        hmudata_b4 =   filei.Get("h_mWsubjet_b4m")
        hmudata_b5 =   filei.Get("h_mWsubjet_b5m")


        hmudata_b1.SetDirectory(0)
        hmudata_b2.SetDirectory(0)
        hmudata_b3.SetDirectory(0)
        hmudata_b4.SetDirectory(0)
        hmudata_b5.SetDirectory(0)



        hdata_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hdata_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hdata_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hdata_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hdata_b5p = ( filei.Get("h_mWsubjet_b5p"))


        hdata_b1p.SetDirectory(0)
        hdata_b2p.SetDirectory(0)
        hdata_b3p.SetDirectory(0)
        hdata_b4p.SetDirectory(0)
        hdata_b5p.SetDirectory(0)


        heldata_b1p = ( filei.Get("h_mWsubjet_b1pe"))
        heldata_b2p = ( filei.Get("h_mWsubjet_b2pe"))
        heldata_b3p = ( filei.Get("h_mWsubjet_b3pe"))
        heldata_b4p = ( filei.Get("h_mWsubjet_b4pe"))
        heldata_b5p = ( filei.Get("h_mWsubjet_b5pe"))


        heldata_b1p.SetDirectory(0)
        heldata_b2p.SetDirectory(0)
        heldata_b3p.SetDirectory(0)
        heldata_b4p.SetDirectory(0)
        heldata_b5p.SetDirectory(0)


        hmudata_b1p = ( filei.Get("h_mWsubjet_b1pm"))
        hmudata_b2p = ( filei.Get("h_mWsubjet_b2pm"))
        hmudata_b3p = ( filei.Get("h_mWsubjet_b3pm"))
        hmudata_b4p = ( filei.Get("h_mWsubjet_b4pm"))
        hmudata_b5p = ( filei.Get("h_mWsubjet_b5pm"))


        hmudata_b1p.SetDirectory(0)
        hmudata_b2p.SetDirectory(0)
        hmudata_b3p.SetDirectory(0)
        hmudata_b4p.SetDirectory(0)
        hmudata_b5p.SetDirectory(0)

        hdata_leppt       = filei.Get("h_lepPt_Data")
        hdata_lepeta      = filei.Get("h_lepEta_Data")
        hdata_lephtlep    = filei.Get("h_lepHtLep_Data")
        hdata_lepht       = filei.Get("h_lepHt_Data")  
        hdata_lepst       = filei.Get("h_lepSt_Data") 

        hdatap_leppt       = filei.Get("hlep_lepPt_Data")
        hdatap_lepeta      = filei.Get("hlep_lepEta_Data")
        hdatap_lephtlep    = filei.Get("hlep_lepHtLep_Data")
        hdatap_lepht       = filei.Get("hlep_lepHt_Data")  
        hdatap_lepst       = filei.Get("hlep_lepSt_Data") 

        hdatapo_leppt       = filei.Get("hpAll_lepPt_Data")
        hdatapo_lepeta      = filei.Get("hpAll_lepEta_Data")
        hdatapo_lephtlep    = filei.Get("hpAll_lepHtLep_Data")
        hdatapo_lepht       = filei.Get("hpAll_lepHt_Data")  
        hdatapo_lepst       = filei.Get("hpAll_lepSt_Data") 

        hdata_ak8tau21    = filei.Get("h_AK8Tau21_Data") 
        hdata_ak8pt       = filei.Get("h_AK8Pt_Data")  
        hdata_ak8SJtau21  = filei.Get("h_AK8subjetTau21_Data")
        hdata_ak8SJpt     = filei.Get("h_AK8subjetPt_Data") 

        hdatap_ak8tau21    = filei.Get("hlep_AK8Tau21_Data") 
        hdatap_ak8pt       = filei.Get("hlep_AK8Pt_Data")  
        hdatap_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_Data")
        hdatap_ak8SJpt     = filei.Get("hlep_AK8subjetPt_Data")

        hdatapo_ak8tau21    = filei.Get("hpAll_AK8Tau21_Data") 
        hdatapo_ak8pt       = filei.Get("hpAll_AK8Pt_Data")  
        hdatapo_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_Data")
        hdatapo_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_Data")
 
        hdata_Pass        = filei.Get("h_mWsubjetPasstag_Data")
        hdata_Fail        = filei.Get("h_mWsubjetFailtag_Data")
        hdatap_Pass        = filei.Get("hlep_mWsubjetPasstag_Data")
        hdatap_Fail        = filei.Get("hlep_mWsubjetFailtag_Data")
        hdatapo_Pass        = filei.Get("hpAll_mWsubjetPasstag_Data")
        hdatapo_Fail        = filei.Get("hpAll_mWsubjetFailtag_Data")

        hdata_leppt.SetDirectory(0)
        hdata_lepeta.SetDirectory(0)
        hdata_lephtlep.SetDirectory(0)
        hdata_lepht.SetDirectory(0)
        hdata_lepst.SetDirectory(0) 
        hdatap_leppt.SetDirectory(0)
        hdatap_lepeta.SetDirectory(0)
        hdatap_lephtlep.SetDirectory(0)
        hdatap_lepht.SetDirectory(0)
        hdatap_lepst.SetDirectory(0) 
        hdatapo_leppt.SetDirectory(0)
        hdatapo_lepeta.SetDirectory(0)
        hdatapo_lephtlep.SetDirectory(0)
        hdatapo_lepht.SetDirectory(0)
        hdatapo_lepst.SetDirectory(0)

        hdata_ak8tau21.SetDirectory(0)
        hdata_ak8pt.SetDirectory(0) 
        hdata_ak8SJtau21.SetDirectory(0)
        hdata_ak8SJpt.SetDirectory(0)
        hdatap_ak8tau21.SetDirectory(0)
        hdatap_ak8pt.SetDirectory(0) 
        hdatap_ak8SJtau21.SetDirectory(0)
        hdatap_ak8SJpt.SetDirectory(0)
        hdatapo_ak8tau21.SetDirectory(0)
        hdatapo_ak8pt.SetDirectory(0) 
        hdatapo_ak8SJtau21.SetDirectory(0)
        hdatapo_ak8SJpt.SetDirectory(0) 


        hdata_Pass.SetDirectory(0)
        hdata_Fail.SetDirectory(0)
        hdatap_Pass.SetDirectory(0)
        hdatap_Fail.SetDirectory(0)
        hdatapo_Pass.SetDirectory(0)
        hdatapo_Fail.SetDirectory(0)


        # post-selection lepton plots
        heldata_leppt       = filei.Get("h_lepPt_ElData")
        heldata_lepeta      = filei.Get("h_lepEta_ElData")
        heldata_lephtlep    = filei.Get("h_lepHtLep_ElData")
        heldata_lepht       = filei.Get("h_lepHt_ElData")  
        heldata_lepst       = filei.Get("h_lepSt_ElData") 
        # pre-selection lepton plots
        heldatap_leppt       = filei.Get("hlep_lepPt_ElData")
        heldatap_lepeta      = filei.Get("hlep_lepEta_ElData")
        heldatap_lephtlep    = filei.Get("hlep_lepHtLep_ElData")
        heldatap_lepht       = filei.Get("hlep_lepHt_ElData")  
        heldatap_lepst       = filei.Get("hlep_lepSt_ElData")  

        heldatapo_leppt       = filei.Get("hpAll_lepPt_ElData")
        heldatapo_lepeta      = filei.Get("hpAll_lepEta_ElData")
        heldatapo_lephtlep    = filei.Get("hpAll_lepHtLep_ElData")
        heldatapo_lepht       = filei.Get("hpAll_lepHt_ElData")  
        heldatapo_lepst       = filei.Get("hpAll_lepSt_ElData")  

        heldata_ak8tau21    = filei.Get("h_AK8Tau21_ElData") 
        heldata_ak8pt       = filei.Get("h_AK8Pt_ElData")  
        heldata_ak8SJtau21  = filei.Get("h_AK8subjetTau21_ElData")
        heldata_ak8SJpt     = filei.Get("h_AK8subjetPt_ElData") 

        heldatap_ak8tau21    = filei.Get("hlep_AK8Tau21_ElData") 
        heldatap_ak8pt       = filei.Get("hlep_AK8Pt_ElData")  
        heldatap_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_ElData")
        heldatap_ak8SJpt     = filei.Get("hlep_AK8subjetPt_ElData") 

        heldatapo_ak8tau21    = filei.Get("hpAll_AK8Tau21_ElData") 
        heldatapo_ak8pt       = filei.Get("hpAll_AK8Pt_ElData")  
        heldatapo_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_ElData")
        heldatapo_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_ElData") 

 
        heldata_Pass        = filei.Get("h_mWsubjetPasstag_ElData")
        heldata_Fail        = filei.Get("h_mWsubjetFailtag_ElData")
        heldatap_Pass        = filei.Get("hlep_mWsubjetPasstag_ElData")
        heldatap_Fail        = filei.Get("hlep_mWsubjetFailtag_ElData")
        heldatapo_Pass        = filei.Get("hpAll_mWsubjetPasstag_ElData")
        heldatapo_Fail        = filei.Get("hpAll_mWsubjetFailtag_ElData")

        heldata_leppt.SetDirectory(0)
        heldata_lepeta.SetDirectory(0)
        heldata_lephtlep.SetDirectory(0)
        heldata_lepht.SetDirectory(0)
        heldata_lepst.SetDirectory(0) 
        heldata_ak8tau21.SetDirectory(0)
        heldata_ak8pt.SetDirectory(0) 
        heldata_ak8SJtau21.SetDirectory(0)
        heldata_ak8SJpt.SetDirectory(0)

        heldatap_leppt.SetDirectory(0)
        heldatap_lepeta.SetDirectory(0)
        heldatap_lephtlep.SetDirectory(0)
        heldatap_lepht.SetDirectory(0)
        heldatap_lepst.SetDirectory(0) 
        heldatap_ak8tau21.SetDirectory(0)
        heldatap_ak8pt.SetDirectory(0) 
        heldatap_ak8SJtau21.SetDirectory(0)
        heldatap_ak8SJpt.SetDirectory(0)

        heldatapo_leppt.SetDirectory(0)
        heldatapo_lepeta.SetDirectory(0)
        heldatapo_lephtlep.SetDirectory(0)
        heldatapo_lepht.SetDirectory(0)
        heldatapo_lepst.SetDirectory(0) 
        heldatapo_ak8tau21.SetDirectory(0)
        heldatapo_ak8pt.SetDirectory(0) 
        heldatapo_ak8SJtau21.SetDirectory(0)
        heldatapo_ak8SJpt.SetDirectory(0) 

        heldata_Pass.SetDirectory(0)
        heldata_Fail.SetDirectory(0)
        heldatap_Pass.SetDirectory(0)
        heldatap_Fail.SetDirectory(0)
        heldatapo_Pass.SetDirectory(0)
        heldatapo_Fail.SetDirectory(0)

        hmudata_leppt       = filei.Get("h_lepPt_MuData")
        hmudata_lepeta      = filei.Get("h_lepEta_MuData")
        hmudata_lephtlep    = filei.Get("h_lepHtLep_MuData")
        hmudata_lepht       = filei.Get("h_lepHt_MuData")  
        hmudata_lepst       = filei.Get("h_lepSt_MuData") 
        hmudatap_leppt       = filei.Get("hlep_lepPt_MuData")
        hmudatap_lepeta      = filei.Get("hlep_lepEta_MuData")
        hmudatap_lephtlep    = filei.Get("hlep_lepHtLep_MuData")
        hmudatap_lepht       = filei.Get("hlep_lepHt_MuData")  
        hmudatap_lepst       = filei.Get("hlep_lepSt_MuData") 
        hmudatapo_leppt       = filei.Get("hpAll_lepPt_MuData")
        hmudatapo_lepeta      = filei.Get("hpAll_lepEta_MuData")
        hmudatapo_lephtlep    = filei.Get("hpAll_lepHtLep_MuData")
        hmudatapo_lepht       = filei.Get("hpAll_lepHt_MuData")  
        hmudatapo_lepst       = filei.Get("hpAll_lepSt_MuData")

        hmudata_ak8tau21    = filei.Get("h_AK8Tau21_MuData") 
        hmudata_ak8pt       = filei.Get("h_AK8Pt_MuData")  
        hmudata_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MuData")
        hmudata_ak8SJpt     = filei.Get("h_AK8subjetPt_MuData") 

        hmudatap_ak8tau21    = filei.Get("hlep_AK8Tau21_MuData") 
        hmudatap_ak8pt       = filei.Get("hlep_AK8Pt_MuData")  
        hmudatap_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MuData")
        hmudatap_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MuData") 

        hmudatapo_ak8tau21    = filei.Get("hpAll_AK8Tau21_MuData") 
        hmudatapo_ak8pt       = filei.Get("hpAll_AK8Pt_MuData")  
        hmudatapo_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MuData")
        hmudatapo_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MuData") 
 
        hmudata_Pass        = filei.Get("h_mWsubjetPasstag_MuData")
        hmudata_Fail        = filei.Get("h_mWsubjetFailtag_MuData")
        hmudatap_Pass        = filei.Get("hlep_mWsubjetPasstag_MuData")
        hmudatap_Fail        = filei.Get("hlep_mWsubjetFailtag_MuData")
        hmudatapo_Pass        = filei.Get("hpAll_mWsubjetPasstag_MuData")
        hmudatapo_Fail        = filei.Get("hpAll_mWsubjetFailtag_MuData")

        hmudata_leppt.SetDirectory(0)
        hmudata_lepeta.SetDirectory(0)
        hmudata_lephtlep.SetDirectory(0)
        hmudata_lepht.SetDirectory(0)
        hmudata_lepst.SetDirectory(0)
        hmudatap_leppt.SetDirectory(0)
        hmudatap_lepeta.SetDirectory(0)
        hmudatap_lephtlep.SetDirectory(0)
        hmudatap_lepht.SetDirectory(0)
        hmudatap_lepst.SetDirectory(0)
        hmudatapo_leppt.SetDirectory(0)
        hmudatapo_lepeta.SetDirectory(0)
        hmudatapo_lephtlep.SetDirectory(0)
        hmudatapo_lepht.SetDirectory(0)
        hmudatapo_lepst.SetDirectory(0)
 
        hmudata_ak8tau21.SetDirectory(0)
        hmudata_ak8pt.SetDirectory(0) 
        hmudata_ak8SJtau21.SetDirectory(0)
        hmudata_ak8SJpt.SetDirectory(0)
        hmudatap_ak8tau21.SetDirectory(0)
        hmudatap_ak8pt.SetDirectory(0) 
        hmudatap_ak8SJtau21.SetDirectory(0)
        hmudatap_ak8SJpt.SetDirectory(0)
        hmudatapo_ak8tau21.SetDirectory(0)
        hmudatapo_ak8pt.SetDirectory(0) 
        hmudatapo_ak8SJtau21.SetDirectory(0)
        hmudatapo_ak8SJpt.SetDirectory(0)
 
        hmudata_Pass.SetDirectory(0)
        hmudata_Fail.SetDirectory(0)
        hmudatap_Pass.SetDirectory(0)
        hmudatap_Fail.SetDirectory(0)
        hmudatapo_Pass.SetDirectory(0)
        hmudatapo_Fail.SetDirectory(0)

        fileIs.Close()

    if str(dtypes[ifin]) == 'ttjets' :
        httbar = (filei.Get("h_mWsubjet_MC"))
        httbar.SetDirectory(0)


        httjets_b1 = ( filei.Get("h_mWsubjet_b1"))
        httjets_b2 = ( filei.Get("h_mWsubjet_b2"))
        httjets_b3 = ( filei.Get("h_mWsubjet_b3"))
        httjets_b4 = ( filei.Get("h_mWsubjet_b4"))
        httjets_b5 = ( filei.Get("h_mWsubjet_b5"))


        httjets_b1.SetDirectory(0)
        httjets_b2.SetDirectory(0)
        httjets_b3.SetDirectory(0)
        httjets_b4.SetDirectory(0)
        httjets_b5.SetDirectory(0)

        httjets_b1p = ( filei.Get("h_mWsubjet_b1p"))
        httjets_b2p = ( filei.Get("h_mWsubjet_b2p"))
        httjets_b3p = ( filei.Get("h_mWsubjet_b3p"))
        httjets_b4p = ( filei.Get("h_mWsubjet_b4p"))
        httjets_b5p = ( filei.Get("h_mWsubjet_b5p"))



        httjets_b1p.SetDirectory(0)
        httjets_b2p.SetDirectory(0)
        httjets_b3p.SetDirectory(0)
        httjets_b4p.SetDirectory(0)
        httjets_b5p.SetDirectory(0)

        httbar_leppt       = filei.Get("h_lepPt_MC")
        httbar_lepeta      = filei.Get("h_lepEta_MC")
        httbar_lephtlep    = filei.Get("h_lepHtLep_MC")
        httbar_lepht       = filei.Get("h_lepHt_MC")  
        httbar_lepst       = filei.Get("h_lepSt_MC") 
        httbarp_leppt       = filei.Get("hlep_lepPt_MC")
        httbarp_lepeta      = filei.Get("hlep_lepEta_MC")
        httbarp_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        httbarp_lepht       = filei.Get("hlep_lepHt_MC")  
        httbarp_lepst       = filei.Get("hlep_lepSt_MC") 
        httbarpo_leppt       = filei.Get("hpAll_lepPt_MC")
        httbarpo_lepeta      = filei.Get("hpAll_lepEta_MC")
        httbarpo_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        httbarpo_lepht       = filei.Get("hpAll_lepHt_MC")  
        httbarpo_lepst       = filei.Get("hpAll_lepSt_MC") 

        httbar_leppt.SetDirectory(0)
        httbar_lepeta.SetDirectory(0)
        httbar_lephtlep.SetDirectory(0)
        httbar_lepht.SetDirectory(0)
        httbar_lepst.SetDirectory(0) 
        httbarp_leppt.SetDirectory(0)
        httbarp_lepeta.SetDirectory(0)
        httbarp_lephtlep.SetDirectory(0)
        httbarp_lepht.SetDirectory(0)
        httbarp_lepst.SetDirectory(0)
        httbarpo_leppt.SetDirectory(0)
        httbarpo_lepeta.SetDirectory(0)
        httbarpo_lephtlep.SetDirectory(0)
        httbarpo_lepht.SetDirectory(0)
        httbarpo_lepst.SetDirectory(0)

        httbar_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        httbar_ak8pt       = filei.Get("h_AK8Pt_MC")  
        httbar_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        httbar_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
        httbarp_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        httbarp_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        httbarp_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        httbarp_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 
        httbarpo_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        httbarpo_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        httbarpo_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        httbarpo_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        httbar_ak8tau21.SetDirectory(0)
        httbar_ak8pt.SetDirectory(0) 
        httbar_ak8SJtau21.SetDirectory(0)
        httbar_ak8SJpt.SetDirectory(0)
        httbarp_ak8tau21.SetDirectory(0)
        httbarp_ak8pt.SetDirectory(0) 
        httbarp_ak8SJtau21.SetDirectory(0)
        httbarp_ak8SJpt.SetDirectory(0)
        httbarpo_ak8tau21.SetDirectory(0)
        httbarpo_ak8pt.SetDirectory(0) 
        httbarpo_ak8SJtau21.SetDirectory(0)
        httbarpo_ak8SJpt.SetDirectory(0)

        httbar_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        httbar_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        httbarp_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        httbarp_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        httbarpo_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        httbarpo_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        httbar_Pass.SetDirectory(0)
        httbar_Fail.SetDirectory(0)
        httbarp_Pass.SetDirectory(0)
        httbarp_Fail.SetDirectory(0)
        httbarpo_Pass.SetDirectory(0)
        httbarpo_Fail.SetDirectory(0)


        fileIs.Close()

    if str(dtypes[ifin]) == 'st1' :
        hst1 = (filei.Get("h_mWsubjet_MC"))
        hst1.SetDirectory(0)


        hst1_b1 = ( filei.Get("h_mWsubjet_b1"))
        hst1_b2 = ( filei.Get("h_mWsubjet_b2"))
        hst1_b3 = ( filei.Get("h_mWsubjet_b3"))
        hst1_b4 = ( filei.Get("h_mWsubjet_b4"))
        hst1_b5 = ( filei.Get("h_mWsubjet_b5"))


        hst1_b1.SetDirectory(0)
        hst1_b2.SetDirectory(0)
        hst1_b3.SetDirectory(0)
        hst1_b4.SetDirectory(0)
        hst1_b5.SetDirectory(0)


        hst1_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hst1_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hst1_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hst1_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hst1_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hst1_b1p.SetDirectory(0)
        hst1_b2p.SetDirectory(0)
        hst1_b3p.SetDirectory(0)
        hst1_b4p.SetDirectory(0)
        hst1_b5p.SetDirectory(0)


        hst1_leppt       = filei.Get("h_lepPt_MC")
        hst1_lepeta      = filei.Get("h_lepEta_MC")
        hst1_lephtlep    = filei.Get("h_lepHtLep_MC")
        hst1_lepht       = filei.Get("h_lepHt_MC")  
        hst1_lepst       = filei.Get("h_lepSt_MC") 
        hst1p_leppt       = filei.Get("hlep_lepPt_MC")
        hst1p_lepeta      = filei.Get("hlep_lepEta_MC")
        hst1p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hst1p_lepht       = filei.Get("hlep_lepHt_MC")  
        hst1p_lepst       = filei.Get("hlep_lepSt_MC") 
        hst1po_leppt       = filei.Get("hpAll_lepPt_MC")
        hst1po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hst1po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hst1po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hst1po_lepst       = filei.Get("hpAll_lepSt_MC") 

        hst1_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hst1_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hst1_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hst1_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 

        hst1p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hst1p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hst1p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hst1p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hst1po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hst1po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hst1po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hst1po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 

 
        hst1_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hst1_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hst1p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hst1p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hst1po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hst1po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hst1_leppt.SetDirectory(0)
        hst1_lepeta.SetDirectory(0)
        hst1_lephtlep.SetDirectory(0)
        hst1_lepht.SetDirectory(0)
        hst1_lepst.SetDirectory(0) 
        hst1p_leppt.SetDirectory(0)
        hst1p_lepeta.SetDirectory(0)
        hst1p_lephtlep.SetDirectory(0)
        hst1p_lepht.SetDirectory(0)
        hst1p_lepst.SetDirectory(0) 
        hst1po_leppt.SetDirectory(0)
        hst1po_lepeta.SetDirectory(0)
        hst1po_lephtlep.SetDirectory(0)
        hst1po_lepht.SetDirectory(0)
        hst1po_lepst.SetDirectory(0) 

        hst1_ak8tau21.SetDirectory(0)
        hst1_ak8pt.SetDirectory(0) 
        hst1_ak8SJtau21.SetDirectory(0)
        hst1_ak8SJpt.SetDirectory(0)
        hst1p_ak8tau21.SetDirectory(0)
        hst1p_ak8pt.SetDirectory(0) 
        hst1p_ak8SJtau21.SetDirectory(0)
        hst1p_ak8SJpt.SetDirectory(0)
        hst1po_ak8tau21.SetDirectory(0)
        hst1po_ak8pt.SetDirectory(0) 
        hst1po_ak8SJtau21.SetDirectory(0)
        hst1po_ak8SJpt.SetDirectory(0)
 
        hst1_Pass.SetDirectory(0)
        hst1_Fail.SetDirectory(0)
        hst1p_Pass.SetDirectory(0)
        hst1p_Fail.SetDirectory(0)
        hst1po_Pass.SetDirectory(0)
        hst1po_Fail.SetDirectory(0)


        fileIs.Close()
    if str(dtypes[ifin]) == 'st2' :
        hst2 = (filei.Get("h_mWsubjet_MC"))
        hst2.SetDirectory(0)

        hst2_b1 = ( filei.Get("h_mWsubjet_b1"))
        hst2_b2 = ( filei.Get("h_mWsubjet_b2"))
        hst2_b3 = ( filei.Get("h_mWsubjet_b3"))
        hst2_b4 = ( filei.Get("h_mWsubjet_b4"))
        hst2_b5 = ( filei.Get("h_mWsubjet_b5"))


        hst2_b1.SetDirectory(0)
        hst2_b2.SetDirectory(0)
        hst2_b3.SetDirectory(0)
        hst2_b4.SetDirectory(0)
        hst2_b5.SetDirectory(0)

        hst2_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hst2_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hst2_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hst2_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hst2_b5p = ( filei.Get("h_mWsubjet_b5p"))

        hst2_b1p.SetDirectory(0)
        hst2_b2p.SetDirectory(0)
        hst2_b3p.SetDirectory(0)
        hst2_b4p.SetDirectory(0)
        hst2_b5p.SetDirectory(0)


        hst2_leppt       = filei.Get("h_lepPt_MC")
        hst2_lepeta      = filei.Get("h_lepEta_MC")
        hst2_lephtlep    = filei.Get("h_lepHtLep_MC")
        hst2_lepht       = filei.Get("h_lepHt_MC")  
        hst2_lepst       = filei.Get("h_lepSt_MC") 
        hst2p_leppt       = filei.Get("hlep_lepPt_MC")
        hst2p_lepeta      = filei.Get("hlep_lepEta_MC")
        hst2p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hst2p_lepht       = filei.Get("hlep_lepHt_MC")  
        hst2p_lepst       = filei.Get("hlep_lepSt_MC") 
        hst2po_leppt       = filei.Get("hpAll_lepPt_MC")
        hst2po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hst2po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hst2po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hst2po_lepst       = filei.Get("hpAll_lepSt_MC") 

        hst2_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hst2_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hst2_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hst2_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hst2p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hst2p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hst2p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hst2p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hst2po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hst2po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hst2po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hst2po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 

        hst2_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hst2_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hst2p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hst2p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hst2po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hst2po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hst2_leppt.SetDirectory(0)
        hst2_lepeta.SetDirectory(0)
        hst2_lephtlep.SetDirectory(0)
        hst2_lepht.SetDirectory(0)
        hst2_lepst.SetDirectory(0) 
        hst2p_leppt.SetDirectory(0)
        hst2p_lepeta.SetDirectory(0)
        hst2p_lephtlep.SetDirectory(0)
        hst2p_lepht.SetDirectory(0)
        hst2p_lepst.SetDirectory(0) 
        hst2po_leppt.SetDirectory(0)
        hst2po_lepeta.SetDirectory(0)
        hst2po_lephtlep.SetDirectory(0)
        hst2po_lepht.SetDirectory(0)
        hst2po_lepst.SetDirectory(0) 

        hst2_ak8tau21.SetDirectory(0)
        hst2_ak8pt.SetDirectory(0) 
        hst2_ak8SJtau21.SetDirectory(0)
        hst2_ak8SJpt.SetDirectory(0)
        hst2p_ak8tau21.SetDirectory(0)
        hst2p_ak8pt.SetDirectory(0) 
        hst2p_ak8SJtau21.SetDirectory(0)
        hst2p_ak8SJpt.SetDirectory(0)
        hst2po_ak8tau21.SetDirectory(0)
        hst2po_ak8pt.SetDirectory(0) 
        hst2po_ak8SJtau21.SetDirectory(0)
        hst2po_ak8SJpt.SetDirectory(0)
 
        hst2_Pass.SetDirectory(0)
        hst2_Fail.SetDirectory(0)
        hst2p_Pass.SetDirectory(0)
        hst2p_Fail.SetDirectory(0)
        hst2po_Pass.SetDirectory(0)
        hst2po_Fail.SetDirectory(0)


        fileIs.Close()

    if str(dtypes[ifin]) == 'st3' :
        hst3 = (filei.Get("h_mWsubjet_MC"))
        hst3.SetDirectory(0)

        hst3_b1 = ( filei.Get("h_mWsubjet_b1"))
        hst3_b2 = ( filei.Get("h_mWsubjet_b2"))
        hst3_b3 = ( filei.Get("h_mWsubjet_b3"))
        hst3_b4 = ( filei.Get("h_mWsubjet_b4"))
        hst3_b5 = ( filei.Get("h_mWsubjet_b5"))


        hst3_b1.SetDirectory(0)
        hst3_b2.SetDirectory(0)
        hst3_b3.SetDirectory(0)
        hst3_b4.SetDirectory(0)
        hst3_b5.SetDirectory(0)



        hst3_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hst3_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hst3_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hst3_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hst3_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hst3_b1p.SetDirectory(0)
        hst3_b2p.SetDirectory(0)
        hst3_b3p.SetDirectory(0)
        hst3_b4p.SetDirectory(0)
        hst3_b5p.SetDirectory(0)

        hst3_leppt       = filei.Get("h_lepPt_MC")
        hst3_lepeta      = filei.Get("h_lepEta_MC")
        hst3_lephtlep    = filei.Get("h_lepHtLep_MC")
        hst3_lepht       = filei.Get("h_lepHt_MC")  
        hst3_lepst       = filei.Get("h_lepSt_MC") 
        hst3p_leppt       = filei.Get("hlep_lepPt_MC")
        hst3p_lepeta      = filei.Get("hlep_lepEta_MC")
        hst3p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hst3p_lepht       = filei.Get("hlep_lepHt_MC")  
        hst3p_lepst       = filei.Get("hlep_lepSt_MC") 
        hst3po_leppt       = filei.Get("hpAll_lepPt_MC")
        hst3po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hst3po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hst3po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hst3po_lepst       = filei.Get("hpAll_lepSt_MC") 

        hst3_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hst3_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hst3_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hst3_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 

        hst3p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hst3p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hst3p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hst3p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hst3po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hst3po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hst3po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hst3po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        hst3_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hst3_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hst3p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hst3p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hst3po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hst3po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hst3_leppt.SetDirectory(0)
        hst3_lepeta.SetDirectory(0)
        hst3_lephtlep.SetDirectory(0)
        hst3_lepht.SetDirectory(0)
        hst3_lepst.SetDirectory(0) 
        hst3p_leppt.SetDirectory(0)
        hst3p_lepeta.SetDirectory(0)
        hst3p_lephtlep.SetDirectory(0)
        hst3p_lepht.SetDirectory(0)
        hst3p_lepst.SetDirectory(0) 
        hst3po_leppt.SetDirectory(0)
        hst3po_lepeta.SetDirectory(0)
        hst3po_lephtlep.SetDirectory(0)
        hst3po_lepht.SetDirectory(0)
        hst3po_lepst.SetDirectory(0) 

        hst3_ak8tau21.SetDirectory(0)
        hst3_ak8pt.SetDirectory(0) 
        hst3_ak8SJtau21.SetDirectory(0)
        hst3_ak8SJpt.SetDirectory(0)
        hst3p_ak8tau21.SetDirectory(0)
        hst3p_ak8pt.SetDirectory(0) 
        hst3p_ak8SJtau21.SetDirectory(0)
        hst3p_ak8SJpt.SetDirectory(0)
        hst3po_ak8tau21.SetDirectory(0)
        hst3po_ak8pt.SetDirectory(0) 
        hst3po_ak8SJtau21.SetDirectory(0)
        hst3po_ak8SJpt.SetDirectory(0)
 
        hst3_Pass.SetDirectory(0)
        hst3_Fail.SetDirectory(0)
        hst3p_Pass.SetDirectory(0)
        hst3p_Fail.SetDirectory(0)
        hst3po_Pass.SetDirectory(0)
        hst3po_Fail.SetDirectory(0)


        fileIs.Close()

    if str(dtypes[ifin]) == 'st4' :
        hst4 = (filei.Get("h_mWsubjet_MC"))
        hst4.SetDirectory(0)


        hst4_b1 = ( filei.Get("h_mWsubjet_b1"))
        hst4_b2 = ( filei.Get("h_mWsubjet_b2"))
        hst4_b3 = ( filei.Get("h_mWsubjet_b3"))
        hst4_b4 = ( filei.Get("h_mWsubjet_b4"))
        hst4_b5 = ( filei.Get("h_mWsubjet_b5"))


        hst4_b1.SetDirectory(0)
        hst4_b2.SetDirectory(0)
        hst4_b3.SetDirectory(0)
        hst4_b4.SetDirectory(0)
        hst4_b5.SetDirectory(0)


        

        hst4_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hst4_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hst4_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hst4_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hst4_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hst4_b1p.SetDirectory(0)
        hst4_b2p.SetDirectory(0)
        hst4_b3p.SetDirectory(0)
        hst4_b4p.SetDirectory(0)
        hst4_b5p.SetDirectory(0)

        hst4_leppt       = filei.Get("h_lepPt_MC")
        hst4_lepeta      = filei.Get("h_lepEta_MC")
        hst4_lephtlep    = filei.Get("h_lepHtLep_MC")
        hst4_lepht       = filei.Get("h_lepHt_MC")  
        hst4_lepst       = filei.Get("h_lepSt_MC") 
        hst4p_leppt       = filei.Get("hlep_lepPt_MC")
        hst4p_lepeta      = filei.Get("hlep_lepEta_MC")
        hst4p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hst4p_lepht       = filei.Get("hlep_lepHt_MC")  
        hst4p_lepst       = filei.Get("hlep_lepSt_MC") 
        hst4po_leppt       = filei.Get("hpAll_lepPt_MC")
        hst4po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hst4po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hst4po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hst4po_lepst       = filei.Get("hpAll_lepSt_MC") 

        hst4_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hst4_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hst4_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hst4_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hst4p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hst4p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hst4p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hst4p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hst4po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hst4po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hst4po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hst4po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 

        hst4_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hst4_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hst4p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hst4p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hst4po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hst4po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hst4_leppt.SetDirectory(0)
        hst4_lepeta.SetDirectory(0)
        hst4_lephtlep.SetDirectory(0)
        hst4_lepht.SetDirectory(0)
        hst4_lepst.SetDirectory(0) 
        hst4p_leppt.SetDirectory(0)
        hst4p_lepeta.SetDirectory(0)
        hst4p_lephtlep.SetDirectory(0)
        hst4p_lepht.SetDirectory(0)
        hst4p_lepst.SetDirectory(0) 
        hst4po_leppt.SetDirectory(0)
        hst4po_lepeta.SetDirectory(0)
        hst4po_lephtlep.SetDirectory(0)
        hst4po_lepht.SetDirectory(0)
        hst4po_lepst.SetDirectory(0) 

        hst4_ak8tau21.SetDirectory(0)
        hst4_ak8pt.SetDirectory(0) 
        hst4_ak8SJtau21.SetDirectory(0)
        hst4_ak8SJpt.SetDirectory(0)
        hst4p_ak8tau21.SetDirectory(0)
        hst4p_ak8pt.SetDirectory(0) 
        hst4p_ak8SJtau21.SetDirectory(0)
        hst4p_ak8SJpt.SetDirectory(0)
        hst4po_ak8tau21.SetDirectory(0)
        hst4po_ak8pt.SetDirectory(0) 
        hst4po_ak8SJtau21.SetDirectory(0)
        hst4po_ak8SJpt.SetDirectory(0)
 
        hst4_Pass.SetDirectory(0)
        hst4_Fail.SetDirectory(0)
        hst4p_Pass.SetDirectory(0)
        hst4p_Fail.SetDirectory(0)
        hst4po_Pass.SetDirectory(0)
        hst4po_Fail.SetDirectory(0)


        fileIs.Close()
    if str(dtypes[ifin]) == 'wjets1' :
        hwjets1 = (filei.Get("h_mWsubjet_MC"))
        hwjets1.SetDirectory(0)

        hwjets1_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets1_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets1_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets1_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets1_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets1_b1.SetDirectory(0)
        hwjets1_b2.SetDirectory(0)
        hwjets1_b3.SetDirectory(0)
        hwjets1_b4.SetDirectory(0)
        hwjets1_b5.SetDirectory(0)

        hwjets1_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets1_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets1_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets1_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets1_b5p = ( filei.Get("h_mWsubjet_b5p"))

        hwjets1_b1p.SetDirectory(0)
        hwjets1_b2p.SetDirectory(0)
        hwjets1_b3p.SetDirectory(0)
        hwjets1_b4p.SetDirectory(0)
        hwjets1_b5p.SetDirectory(0)

        hwjets1_leppt       = filei.Get("h_lepPt_MC")
        hwjets1_lepeta      = filei.Get("h_lepEta_MC")
        hwjets1_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets1_lepht       = filei.Get("h_lepHt_MC")  
        hwjets1_lepst       = filei.Get("h_lepSt_MC") 
        hwjets1p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets1p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets1p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets1p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets1p_lepst       = filei.Get("hlep_lepSt_MC") 
        hwjets1po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets1po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets1po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets1po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets1po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets1_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets1_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets1_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets1_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 

        hwjets1p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets1p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets1p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets1p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets1po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets1po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets1po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets1po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        hwjets1_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets1_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets1p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets1p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets1po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets1po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets1_leppt.SetDirectory(0)
        hwjets1_lepeta.SetDirectory(0)
        hwjets1_lephtlep.SetDirectory(0)
        hwjets1_lepht.SetDirectory(0)
        hwjets1_lepst.SetDirectory(0) 
        hwjets1p_leppt.SetDirectory(0)
        hwjets1p_lepeta.SetDirectory(0)
        hwjets1p_lephtlep.SetDirectory(0)
        hwjets1p_lepht.SetDirectory(0)
        hwjets1p_lepst.SetDirectory(0) 
        hwjets1po_leppt.SetDirectory(0)
        hwjets1po_lepeta.SetDirectory(0)
        hwjets1po_lephtlep.SetDirectory(0)
        hwjets1po_lepht.SetDirectory(0)
        hwjets1po_lepst.SetDirectory(0) 

        hwjets1_ak8tau21.SetDirectory(0)
        hwjets1_ak8pt.SetDirectory(0) 
        hwjets1_ak8SJtau21.SetDirectory(0)
        hwjets1_ak8SJpt.SetDirectory(0)
        hwjets1p_ak8tau21.SetDirectory(0)
        hwjets1p_ak8pt.SetDirectory(0) 
        hwjets1p_ak8SJtau21.SetDirectory(0)
        hwjets1p_ak8SJpt.SetDirectory(0)
        hwjets1po_ak8tau21.SetDirectory(0)
        hwjets1po_ak8pt.SetDirectory(0) 
        hwjets1po_ak8SJtau21.SetDirectory(0)
        hwjets1po_ak8SJpt.SetDirectory(0)
 
        hwjets1_Pass.SetDirectory(0)
        hwjets1_Fail.SetDirectory(0)
        hwjets1p_Pass.SetDirectory(0)
        hwjets1p_Fail.SetDirectory(0)
        hwjets1po_Pass.SetDirectory(0)
        hwjets1po_Fail.SetDirectory(0)
        fileIs.Close()

    if str(dtypes[ifin]) == 'wjets2' :
        hwjets2 = (filei.Get("h_mWsubjet_MC"))
        hwjets2.SetDirectory(0)


        hwjets2_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets2_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets2_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets2_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets2_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets2_b1.SetDirectory(0)
        hwjets2_b2.SetDirectory(0)
        hwjets2_b3.SetDirectory(0)
        hwjets2_b4.SetDirectory(0)
        hwjets2_b5.SetDirectory(0)



        hwjets2_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets2_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets2_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets2_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets2_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hwjets2_b1p.SetDirectory(0)
        hwjets2_b2p.SetDirectory(0)
        hwjets2_b3p.SetDirectory(0)
        hwjets2_b4p.SetDirectory(0)
        hwjets2_b5p.SetDirectory(0)


        hwjets2_leppt       = filei.Get("h_lepPt_MC")
        hwjets2_lepeta      = filei.Get("h_lepEta_MC")
        hwjets2_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets2_lepht       = filei.Get("h_lepHt_MC")  
        hwjets2_lepst       = filei.Get("h_lepSt_MC") 
        hwjets2p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets2p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets2p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets2p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets2p_lepst       = filei.Get("hlep_lepSt_MC")
        hwjets2po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets2po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets2po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets2po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets2po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets2_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets2_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets2_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets2_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets2p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets2p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets2p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets2p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets2po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets2po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets2po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets2po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 

        hwjets2_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets2_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets2p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets2p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets2po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets2po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets2_leppt.SetDirectory(0)
        hwjets2_lepeta.SetDirectory(0)
        hwjets2_lephtlep.SetDirectory(0)
        hwjets2_lepht.SetDirectory(0)
        hwjets2_lepst.SetDirectory(0) 
        hwjets2p_leppt.SetDirectory(0)
        hwjets2p_lepeta.SetDirectory(0)
        hwjets2p_lephtlep.SetDirectory(0)
        hwjets2p_lepht.SetDirectory(0)
        hwjets2p_lepst.SetDirectory(0) 
        hwjets2po_leppt.SetDirectory(0)
        hwjets2po_lepeta.SetDirectory(0)
        hwjets2po_lephtlep.SetDirectory(0)
        hwjets2po_lepht.SetDirectory(0)
        hwjets2po_lepst.SetDirectory(0) 

        hwjets2_ak8tau21.SetDirectory(0)
        hwjets2_ak8pt.SetDirectory(0) 
        hwjets2_ak8SJtau21.SetDirectory(0)
        hwjets2_ak8SJpt.SetDirectory(0)
        hwjets2p_ak8tau21.SetDirectory(0)
        hwjets2p_ak8pt.SetDirectory(0) 
        hwjets2p_ak8SJtau21.SetDirectory(0)
        hwjets2p_ak8SJpt.SetDirectory(0)
        hwjets2po_ak8tau21.SetDirectory(0)
        hwjets2po_ak8pt.SetDirectory(0) 
        hwjets2po_ak8SJtau21.SetDirectory(0)
        hwjets2po_ak8SJpt.SetDirectory(0)
 
        hwjets2_Pass.SetDirectory(0)
        hwjets2_Fail.SetDirectory(0)
        hwjets2p_Pass.SetDirectory(0)
        hwjets2p_Fail.SetDirectory(0)
        hwjets2po_Pass.SetDirectory(0)
        hwjets2po_Fail.SetDirectory(0)

        fileIs.Close()

    if str(dtypes[ifin]) == 'wjets3' :
        hwjets3 = (filei.Get("h_mWsubjet_MC"))
        hwjets3.SetDirectory(0)


        hwjets3_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets3_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets3_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets3_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets3_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets3_b1.SetDirectory(0)
        hwjets3_b2.SetDirectory(0)
        hwjets3_b3.SetDirectory(0)
        hwjets3_b4.SetDirectory(0)
        hwjets3_b5.SetDirectory(0)


        hwjets3_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets3_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets3_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets3_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets3_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hwjets3_b1p.SetDirectory(0)
        hwjets3_b2p.SetDirectory(0)
        hwjets3_b3p.SetDirectory(0)
        hwjets3_b4p.SetDirectory(0)
        hwjets3_b5p.SetDirectory(0)


        hwjets3_leppt       = filei.Get("h_lepPt_MC")
        hwjets3_lepeta      = filei.Get("h_lepEta_MC")
        hwjets3_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets3_lepht       = filei.Get("h_lepHt_MC")  
        hwjets3_lepst       = filei.Get("h_lepSt_MC") 
        hwjets3p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets3p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets3p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets3p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets3p_lepst       = filei.Get("hlep_lepSt_MC") 
        hwjets3po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets3po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets3po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets3po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets3po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets3_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets3_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets3_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets3_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets3p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets3p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets3p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets3p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets3po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets3po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets3po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets3po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        hwjets3_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets3_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets3p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets3p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets3po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets3po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets3_leppt.SetDirectory(0)
        hwjets3_lepeta.SetDirectory(0)
        hwjets3_lephtlep.SetDirectory(0)
        hwjets3_lepht.SetDirectory(0)
        hwjets3_lepst.SetDirectory(0) 
        hwjets3p_leppt.SetDirectory(0)
        hwjets3p_lepeta.SetDirectory(0)
        hwjets3p_lephtlep.SetDirectory(0)
        hwjets3p_lepht.SetDirectory(0)
        hwjets3p_lepst.SetDirectory(0) 
        hwjets3po_leppt.SetDirectory(0)
        hwjets3po_lepeta.SetDirectory(0)
        hwjets3po_lephtlep.SetDirectory(0)
        hwjets3po_lepht.SetDirectory(0)
        hwjets3po_lepst.SetDirectory(0) 

        hwjets3_ak8tau21.SetDirectory(0)
        hwjets3_ak8pt.SetDirectory(0) 
        hwjets3_ak8SJtau21.SetDirectory(0)
        hwjets3_ak8SJpt.SetDirectory(0)
        hwjets3p_ak8tau21.SetDirectory(0)
        hwjets3p_ak8pt.SetDirectory(0) 
        hwjets3p_ak8SJtau21.SetDirectory(0)
        hwjets3p_ak8SJpt.SetDirectory(0)
        hwjets3po_ak8tau21.SetDirectory(0)
        hwjets3po_ak8pt.SetDirectory(0) 
        hwjets3po_ak8SJtau21.SetDirectory(0)
        hwjets3po_ak8SJpt.SetDirectory(0)
 
        hwjets3_Pass.SetDirectory(0)
        hwjets3_Fail.SetDirectory(0)
        hwjets3p_Pass.SetDirectory(0)
        hwjets3p_Fail.SetDirectory(0)
        hwjets3po_Pass.SetDirectory(0)
        hwjets3po_Fail.SetDirectory(0)
        fileIs.Close()


    if str(dtypes[ifin]) == 'wjets4' :
        hwjets4 = (filei.Get("h_mWsubjet_MC"))
        hwjets4.SetDirectory(0)


        hwjets4_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets4_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets4_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets4_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets4_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets4_b1.SetDirectory(0)
        hwjets4_b2.SetDirectory(0)
        hwjets4_b3.SetDirectory(0)
        hwjets4_b4.SetDirectory(0)
        hwjets4_b5.SetDirectory(0)


        hwjets4_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets4_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets4_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets4_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets4_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hwjets4_b1p.SetDirectory(0)
        hwjets4_b2p.SetDirectory(0)
        hwjets4_b3p.SetDirectory(0)
        hwjets4_b4p.SetDirectory(0)
        hwjets4_b5p.SetDirectory(0)


        hwjets4_leppt       = filei.Get("h_lepPt_MC")
        hwjets4_lepeta      = filei.Get("h_lepEta_MC")
        hwjets4_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets4_lepht       = filei.Get("h_lepHt_MC")  
        hwjets4_lepst       = filei.Get("h_lepSt_MC") 
        hwjets4p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets4p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets4p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets4p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets4p_lepst       = filei.Get("hlep_lepSt_MC") 
        hwjets4po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets4po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets4po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets4po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets4po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets4_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets4_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets4_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets4_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets4p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets4p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets4p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets4p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets4po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets4po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets4po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets4po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        hwjets4_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets4_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets4p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets4p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets4po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets4po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets4_leppt.SetDirectory(0)
        hwjets4_lepeta.SetDirectory(0)
        hwjets4_lephtlep.SetDirectory(0)
        hwjets4_lepht.SetDirectory(0)
        hwjets4_lepst.SetDirectory(0) 
        hwjets4p_leppt.SetDirectory(0)
        hwjets4p_lepeta.SetDirectory(0)
        hwjets4p_lephtlep.SetDirectory(0)
        hwjets4p_lepht.SetDirectory(0)
        hwjets4p_lepst.SetDirectory(0) 
        hwjets4po_leppt.SetDirectory(0)
        hwjets4po_lepeta.SetDirectory(0)
        hwjets4po_lephtlep.SetDirectory(0)
        hwjets4po_lepht.SetDirectory(0)
        hwjets4po_lepst.SetDirectory(0) 

        hwjets4_ak8tau21.SetDirectory(0)
        hwjets4_ak8pt.SetDirectory(0) 
        hwjets4_ak8SJtau21.SetDirectory(0)
        hwjets4_ak8SJpt.SetDirectory(0)
        hwjets4p_ak8tau21.SetDirectory(0)
        hwjets4p_ak8pt.SetDirectory(0) 
        hwjets4p_ak8SJtau21.SetDirectory(0)
        hwjets4p_ak8SJpt.SetDirectory(0)
        hwjets4po_ak8tau21.SetDirectory(0)
        hwjets4po_ak8pt.SetDirectory(0) 
        hwjets4po_ak8SJtau21.SetDirectory(0)
        hwjets4po_ak8SJpt.SetDirectory(0)
 
        hwjets4_Pass.SetDirectory(0)
        hwjets4_Fail.SetDirectory(0)
        hwjets4p_Pass.SetDirectory(0)
        hwjets4p_Fail.SetDirectory(0)
        hwjets4po_Pass.SetDirectory(0)
        hwjets4po_Fail.SetDirectory(0)


        fileIs.Close()
    if str(dtypes[ifin]) == 'wjets5' :
        hwjets5 = (filei.Get("h_mWsubjet_MC"))
        hwjets5.SetDirectory(0)

        hwjets5_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets5_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets5_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets5_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets5_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets5_b1.SetDirectory(0)
        hwjets5_b2.SetDirectory(0)
        hwjets5_b3.SetDirectory(0)
        hwjets5_b4.SetDirectory(0)
        hwjets5_b5.SetDirectory(0)


        hwjets5_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets5_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets5_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets5_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets5_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hwjets5_b1p.SetDirectory(0)
        hwjets5_b2p.SetDirectory(0)
        hwjets5_b3p.SetDirectory(0)
        hwjets5_b4p.SetDirectory(0)
        hwjets5_b5p.SetDirectory(0)


        hwjets5_leppt       = filei.Get("h_lepPt_MC")
        hwjets5_lepeta      = filei.Get("h_lepEta_MC")
        hwjets5_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets5_lepht       = filei.Get("h_lepHt_MC")  
        hwjets5_lepst      = filei.Get("h_lepSt_MC") 
        hwjets5p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets5p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets5p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets5p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets5p_lepst      = filei.Get("hlep_lepSt_MC") 
        hwjets5po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets5po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets5po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets5po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets5po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets5_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets5_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets5_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets5_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets5p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets5p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets5p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets5p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets5po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets5po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets5po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets5po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 

        hwjets5_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets5_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets5p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets5p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets5po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets5po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets5_leppt.SetDirectory(0)
        hwjets5_lepeta.SetDirectory(0)
        hwjets5_lephtlep.SetDirectory(0)
        hwjets5_lepht.SetDirectory(0)
        hwjets5_lepst.SetDirectory(0) 
        hwjets5p_leppt.SetDirectory(0)
        hwjets5p_lepeta.SetDirectory(0)
        hwjets5p_lephtlep.SetDirectory(0)
        hwjets5p_lepht.SetDirectory(0)
        hwjets5p_lepst.SetDirectory(0) 
        hwjets5po_leppt.SetDirectory(0)
        hwjets5po_lepeta.SetDirectory(0)
        hwjets5po_lephtlep.SetDirectory(0)
        hwjets5po_lepht.SetDirectory(0)
        hwjets5po_lepst.SetDirectory(0) 

        hwjets5_ak8tau21.SetDirectory(0)
        hwjets5_ak8pt.SetDirectory(0) 
        hwjets5_ak8SJtau21.SetDirectory(0)
        hwjets5_ak8SJpt.SetDirectory(0)
        hwjets5p_ak8tau21.SetDirectory(0)
        hwjets5p_ak8pt.SetDirectory(0) 
        hwjets5p_ak8SJtau21.SetDirectory(0)
        hwjets5p_ak8SJpt.SetDirectory(0)
        hwjets5po_ak8tau21.SetDirectory(0)
        hwjets5po_ak8pt.SetDirectory(0) 
        hwjets5po_ak8SJtau21.SetDirectory(0)
        hwjets5po_ak8SJpt.SetDirectory(0)
 
        hwjets5_Pass.SetDirectory(0)
        hwjets5_Fail.SetDirectory(0)
        hwjets5p_Pass.SetDirectory(0)
        hwjets5p_Fail.SetDirectory(0)
        hwjets5po_Pass.SetDirectory(0)
        hwjets5po_Fail.SetDirectory(0)


        fileIs.Close()
    if str(dtypes[ifin]) == 'wjets6' :
        hwjets6 = (filei.Get("h_mWsubjet_MC"))
        hwjets6.SetDirectory(0)


        hwjets6_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets6_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets6_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets6_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets6_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets6_b1.SetDirectory(0)
        hwjets6_b2.SetDirectory(0)
        hwjets6_b3.SetDirectory(0)
        hwjets6_b4.SetDirectory(0)
        hwjets6_b5.SetDirectory(0)



        hwjets6_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets6_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets6_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets6_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets6_b5p = ( filei.Get("h_mWsubjet_b5p"))



        hwjets6_b1p.SetDirectory(0)
        hwjets6_b2p.SetDirectory(0)
        hwjets6_b3p.SetDirectory(0)
        hwjets6_b4p.SetDirectory(0)
        hwjets6_b5p.SetDirectory(0)


        hwjets6_leppt       = filei.Get("h_lepPt_MC")
        hwjets6_lepeta      = filei.Get("h_lepEta_MC")
        hwjets6_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets6_lepht       = filei.Get("h_lepHt_MC")  
        hwjets6_lepst       = filei.Get("h_lepSt_MC") 
        hwjets6p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets6p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets6p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets6p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets6p_lepst       = filei.Get("hlep_lepSt_MC")
        hwjets6po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets6po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets6po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets6po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets6po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets6_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets6_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets6_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets6_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets6p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets6p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets6p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets6p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets6po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets6po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets6po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets6po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 
        hwjets6_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets6_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets6p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets6p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets6po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets6po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets6_leppt.SetDirectory(0)
        hwjets6_lepeta.SetDirectory(0)
        hwjets6_lephtlep.SetDirectory(0)
        hwjets6_lepht.SetDirectory(0)
        hwjets6_lepst.SetDirectory(0) 
        hwjets6p_leppt.SetDirectory(0)
        hwjets6p_lepeta.SetDirectory(0)
        hwjets6p_lephtlep.SetDirectory(0)
        hwjets6p_lepht.SetDirectory(0)
        hwjets6p_lepst.SetDirectory(0) 
        hwjets6po_leppt.SetDirectory(0)
        hwjets6po_lepeta.SetDirectory(0)
        hwjets6po_lephtlep.SetDirectory(0)
        hwjets6po_lepht.SetDirectory(0)
        hwjets6po_lepst.SetDirectory(0) 

        hwjets6_ak8tau21.SetDirectory(0)
        hwjets6_ak8pt.SetDirectory(0) 
        hwjets6_ak8SJtau21.SetDirectory(0)
        hwjets6_ak8SJpt.SetDirectory(0)
        hwjets6p_ak8tau21.SetDirectory(0)
        hwjets6p_ak8pt.SetDirectory(0) 
        hwjets6p_ak8SJtau21.SetDirectory(0)
        hwjets6p_ak8SJpt.SetDirectory(0)
        hwjets6po_ak8tau21.SetDirectory(0)
        hwjets6po_ak8pt.SetDirectory(0) 
        hwjets6po_ak8SJtau21.SetDirectory(0)
        hwjets6po_ak8SJpt.SetDirectory(0)
 
        hwjets6_Pass.SetDirectory(0)
        hwjets6_Fail.SetDirectory(0)
        hwjets6p_Pass.SetDirectory(0)
        hwjets6p_Fail.SetDirectory(0)
        hwjets6po_Pass.SetDirectory(0)
        hwjets6po_Fail.SetDirectory(0)
        fileIs.Close()

    if str(dtypes[ifin]) == 'wjets7' :
        hwjets7 = (filei.Get("h_mWsubjet_MC"))
        hwjets7.SetDirectory(0)

        hwjets7_b1 = ( filei.Get("h_mWsubjet_b1"))
        hwjets7_b2 = ( filei.Get("h_mWsubjet_b2"))
        hwjets7_b3 = ( filei.Get("h_mWsubjet_b3"))
        hwjets7_b4 = ( filei.Get("h_mWsubjet_b4"))
        hwjets7_b5 = ( filei.Get("h_mWsubjet_b5"))


        hwjets7_b1.SetDirectory(0)
        hwjets7_b2.SetDirectory(0)
        hwjets7_b3.SetDirectory(0)
        hwjets7_b4.SetDirectory(0)
        hwjets7_b5.SetDirectory(0)

        hwjets7_b1p = ( filei.Get("h_mWsubjet_b1p"))
        hwjets7_b2p = ( filei.Get("h_mWsubjet_b2p"))
        hwjets7_b3p = ( filei.Get("h_mWsubjet_b3p"))
        hwjets7_b4p = ( filei.Get("h_mWsubjet_b4p"))
        hwjets7_b5p = ( filei.Get("h_mWsubjet_b5p"))

        hwjets7_b1p.SetDirectory(0)
        hwjets7_b2p.SetDirectory(0)
        hwjets7_b3p.SetDirectory(0)
        hwjets7_b4p.SetDirectory(0)
        hwjets7_b5p.SetDirectory(0)

        hwjets7_leppt       = filei.Get("h_lepPt_MC")
        hwjets7_lepeta      = filei.Get("h_lepEta_MC")
        hwjets7_lephtlep    = filei.Get("h_lepHtLep_MC")
        hwjets7_lepht       = filei.Get("h_lepHt_MC")  
        hwjets7_lepst      = filei.Get("h_lepSt_MC") 
        hwjets7p_leppt       = filei.Get("hlep_lepPt_MC")
        hwjets7p_lepeta      = filei.Get("hlep_lepEta_MC")
        hwjets7p_lephtlep    = filei.Get("hlep_lepHtLep_MC")
        hwjets7p_lepht       = filei.Get("hlep_lepHt_MC")  
        hwjets7p_lepst      = filei.Get("hlep_lepSt_MC") 
        hwjets7po_leppt       = filei.Get("hpAll_lepPt_MC")
        hwjets7po_lepeta      = filei.Get("hpAll_lepEta_MC")
        hwjets7po_lephtlep    = filei.Get("hpAll_lepHtLep_MC")
        hwjets7po_lepht       = filei.Get("hpAll_lepHt_MC")  
        hwjets7po_lepst       = filei.Get("hpAll_lepSt_MC")

        hwjets7_ak8tau21    = filei.Get("h_AK8Tau21_MC") 
        hwjets7_ak8pt       = filei.Get("h_AK8Pt_MC")  
        hwjets7_ak8SJtau21  = filei.Get("h_AK8subjetTau21_MC")
        hwjets7_ak8SJpt     = filei.Get("h_AK8subjetPt_MC") 
 
        hwjets7p_ak8tau21    = filei.Get("hlep_AK8Tau21_MC") 
        hwjets7p_ak8pt       = filei.Get("hlep_AK8Pt_MC")  
        hwjets7p_ak8SJtau21  = filei.Get("hlep_AK8subjetTau21_MC")
        hwjets7p_ak8SJpt     = filei.Get("hlep_AK8subjetPt_MC") 

        hwjets7po_ak8tau21    = filei.Get("hpAll_AK8Tau21_MC") 
        hwjets7po_ak8pt       = filei.Get("hpAll_AK8Pt_MC")  
        hwjets7po_ak8SJtau21  = filei.Get("hpAll_AK8subjetTau21_MC")
        hwjets7po_ak8SJpt     = filei.Get("hpAll_AK8subjetPt_MC") 
 

        hwjets7_Pass        = filei.Get("h_mWsubjetPasstag_MC")
        hwjets7_Fail        = filei.Get("h_mWsubjetFailtag_MC")
        hwjets7p_Pass        = filei.Get("hlep_mWsubjetPasstag_MC")
        hwjets7p_Fail        = filei.Get("hlep_mWsubjetFailtag_MC")
        hwjets7po_Pass        = filei.Get("hpAll_mWsubjetPasstag_MC")
        hwjets7po_Fail        = filei.Get("hpAll_mWsubjetFailtag_MC")

        hwjets7_leppt.SetDirectory(0)
        hwjets7_lepeta.SetDirectory(0)
        hwjets7_lephtlep.SetDirectory(0)
        hwjets7_lepht.SetDirectory(0)
        hwjets7_lepst.SetDirectory(0) 
        hwjets7p_leppt.SetDirectory(0)
        hwjets7p_lepeta.SetDirectory(0)
        hwjets7p_lephtlep.SetDirectory(0)
        hwjets7p_lepht.SetDirectory(0)
        hwjets7p_lepst.SetDirectory(0) 
        hwjets7po_leppt.SetDirectory(0)
        hwjets7po_lepeta.SetDirectory(0)
        hwjets7po_lephtlep.SetDirectory(0)
        hwjets7po_lepht.SetDirectory(0)
        hwjets7po_lepst.SetDirectory(0) 

        hwjets7_ak8tau21.SetDirectory(0)
        hwjets7_ak8pt.SetDirectory(0) 
        hwjets7_ak8SJtau21.SetDirectory(0)
        hwjets7_ak8SJpt.SetDirectory(0)
        hwjets7p_ak8tau21.SetDirectory(0)
        hwjets7p_ak8pt.SetDirectory(0) 
        hwjets7p_ak8SJtau21.SetDirectory(0)
        hwjets7p_ak8SJpt.SetDirectory(0)
        hwjets7po_ak8tau21.SetDirectory(0)
        hwjets7po_ak8pt.SetDirectory(0) 
        hwjets7po_ak8SJtau21.SetDirectory(0)
        hwjets7po_ak8SJpt.SetDirectory(0)
 
        hwjets7_Pass.SetDirectory(0)
        hwjets7_Fail.SetDirectory(0)
        hwjets7p_Pass.SetDirectory(0)
        hwjets7p_Fail.SetDirectory(0)
        hwjets7po_Pass.SetDirectory(0)
        hwjets7po_Fail.SetDirectory(0)


        fileIs.Close()
'''
# Fix this, get type 1 and type 2 pt distributions of W candidates

#hpts = filei.Get("h_ptWsubjet_Data_Type1")
#hpts2 = filei.Get("h_ptWsubjet_Data_Type2")

#hptsMC = filei.Get("h_ptWsubjet_MC_Type1")
#hpts2MC = filei.Get("h_ptWsubjet_MC_Type2")
'''

nMCpre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nDatapre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMuDatapre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nElDatapre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMCupre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nDataupre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMuDataupre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nElDataupre = array.array('d', [0., 0., 0., 0., 0., 0., 0.])

MCmeans = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
MCsigmas = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
Datameans = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
Datasigmas = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
ElDatameans = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
ElDatasigmas = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
MuDatameans = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
MuDatasigmas = array.array('d', [0., 0., 0., 0., 0., 0., 0.])

nMCpost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nDatapost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMuDatapost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nElDatapost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMCupost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nDataupost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nMuDataupost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])
nElDataupost = array.array('d', [0., 0., 0., 0., 0., 0., 0.])

if not options.pre : 
    filein2 = ROOT.TFile.Open('./output80xplotter/Wtag'+type2+datatype+'highPtSF_preWTag_80x_'+ options.treeLocation +'_'+ options.infile+'.root') 
    h_NpassDataPre = filein2.Get("hNpassDataPre")
    h_NpassMuDataPre = filein2.Get("hNpassMuDataPre")
    h_NpassElDataPre = filein2.Get("hNpassElDataPre")
    h_NpassMCPre = filein2.Get("hNpassMCPre")
 
    h_meanDataPre = filein2.Get("hmeanDataPre")
    h_meanMuDataPre = filein2.Get("hmeanMuDataPre")
    h_meanElDataPre = filein2.Get("hmeanElDataPre")
    h_meanMCPre = filein2.Get("hmeanMCPre")
    h_sigmaDataPre = filein2.Get("hsigmaDataPre")
    h_sigmaMuDataPre = filein2.Get("hsigmaMuDataPre")
    h_sigmaElDataPre = filein2.Get("hsigmaElDataPre")
    h_sigmaMCPre = filein2.Get("hsigmaMCPre")


    for ibin in xrange(0,h_NpassMCPre.GetNbinsX()) :
        nMCpre[ibin] = h_NpassMCPre.GetBinContent(ibin+1)
        nDatapre[ibin] = h_NpassDataPre.GetBinContent(ibin+1)
        nMuDatapre[ibin] = h_NpassMuDataPre.GetBinContent(ibin+1)
        nElDatapre[ibin] = h_NpassElDataPre.GetBinContent(ibin+1)
        print "For bin " + str(ibin)+" : preselection in mudata {0:6.3}, eldata{0:6.3} and mc {0:6.3} ".format(nMuDatapre[ibin],nElDatapre[ibin], nMCpre[ibin])
    
    print "Reading means and widths of --pre Gaussian Fits for use in constraining the post W tag fits!"
    for ibin in xrange(0,h_sigmaMCPre.GetNbinsX() ) :
        MCmeans[ibin] = h_meanMCPre.GetBinContent(ibin+1)
        MCsigmas[ibin] = h_sigmaMCPre.GetBinContent(ibin+1)
        Datameans[ibin] = h_meanDataPre.GetBinContent(ibin+1)
        Datasigmas[ibin] = h_sigmaDataPre.GetBinContent(ibin+1)        
        MuDatameans[ibin] = h_meanMuDataPre.GetBinContent(ibin+1)
        MuDatasigmas[ibin] = h_sigmaMuDataPre.GetBinContent(ibin+1)
        ElDatameans[ibin] = h_meanElDataPre.GetBinContent(ibin+1)
        ElDatasigmas[ibin] = h_sigmaElDataPre.GetBinContent(ibin+1)

binlabels = [ "200 < P_{T} < 300  ",
              "300 < P_{T} < 400  ",
              "400 < P_{T} < 500  ",
                    "P_{T} > 500  ",
              "200 < P_{T} < 800  ",
              " #tau_{21} < 0.6 ",
              " #tau_{21} > 0.6 "]

# Rebin Values for Pt binned W candidate Mass histograms
rebinBybin = [ 10, 10, 10, 10, 10, 10, 10]

for ipt in xrange(0, len(binlabels) ) :
    if ipt <= 3: pt = ptBs[int(ipt)]
    binlabel = binlabels[int(ipt)]
    # Get the W candidate mass histograms
    if ipt == 0 :
        hdataT = hdata_b1.Clone()
        hdataTp = hdata_b1p.Clone()
        httbarT = httjets_b1.Clone()
        httbarTp = httjets_b1p.Clone()

        if options.allMC :
            hstT1 = hst1_b1.Clone()
            hstTp1 = hst1_b1p.Clone()
            hstT2 = hst2_b1.Clone()
            hstTp2 = hst2_b1p.Clone()
            hstT3 = hst3_b1.Clone()
            hstTp3 = hst3_b1p.Clone()
            hstT4 = hst4_b1.Clone()
            hstTp4 = hst4_b1p.Clone()
            hwjetsT1 = hwjets1_b1.Clone()
            hwjetsTp1 = hwjets1_b1p.Clone()
            hwjetsT2 = hwjets2_b1.Clone()
            hwjetsTp2 = hwjets2_b1p.Clone()
            hwjetsT3 = hwjets3_b1.Clone()
            hwjetsTp3 = hwjets3_b1p.Clone()
            hwjetsT4 = hwjets4_b1.Clone()
            hwjetsTp4 = hwjets4_b1p.Clone()
            hwjetsT5 = hwjets5_b1.Clone()
            hwjetsTp5 = hwjets5_b1p.Clone()
            hwjetsT6 = hwjets6_b1.Clone()
            hwjetsTp6 = hwjets6_b1p.Clone()
            hwjetsT7 = hwjets7_b1.Clone()
            hwjetsTp7 = hwjets7_b1p.Clone()

        #if options.Eldata:
        heldataT = heldata_b1.Clone()
        heldataTp = heldata_b1p.Clone() 
        #if options.Mudata:
        hmudataTp = hmudata_b1p.Clone()
        hmudataT = hmudata_b1.Clone()
    if ipt == 1 :
        hdataT = hdata_b2.Clone()
        hdataTp = hdata_b2p.Clone()
        httbarT = httjets_b2.Clone()
        httbarTp = httjets_b2p.Clone()

        if options.allMC :
            hstT1 = hst1_b2.Clone()
            hstTp1 = hst1_b2p.Clone()
            hstT2 = hst2_b2.Clone()
            hstTp2 = hst2_b2p.Clone()
            hstT3 = hst3_b2.Clone()
            hstTp3 = hst3_b2p.Clone()
            hstT4 = hst4_b2.Clone()
            hstTp4 = hst4_b2p.Clone()
            hwjetsT1 = hwjets1_b2.Clone()
            hwjetsTp1 = hwjets1_b2p.Clone()
            hwjetsT2 = hwjets2_b2.Clone()
            hwjetsTp2 = hwjets2_b2p.Clone()
            hwjetsT3 = hwjets3_b2.Clone()
            hwjetsTp3 = hwjets3_b2p.Clone()
            hwjetsT4 = hwjets4_b2.Clone()
            hwjetsTp4 = hwjets4_b2p.Clone()
            hwjetsT5 = hwjets5_b2.Clone()
            hwjetsTp5 = hwjets5_b2p.Clone()
            hwjetsT6 = hwjets6_b2.Clone()
            hwjetsTp6 = hwjets6_b2p.Clone()
            hwjetsT7 = hwjets7_b2.Clone()
            hwjetsTp7 = hwjets7_b2p.Clone()
        #if options.Eldata:
        heldataT = heldata_b2.Clone()
        heldataTp = heldata_b2p.Clone() 
        #if options.Mudata:
        hmudataTp = hmudata_b2p.Clone()
        hmudataT = hmudata_b2.Clone()
    if ipt == 2 :
        hdataT = hdata_b3.Clone()
        hdataTp = hdata_b3p.Clone()
        httbarT = httjets_b3.Clone()
        httbarTp = httjets_b3p.Clone()
        if options.allMC :
            hstT1 = hst1_b3.Clone()
            hstTp1 = hst1_b3p.Clone()
            hstT2 = hst2_b3.Clone()
            hstTp2 = hst2_b3p.Clone()
            hstT3 = hst3_b3.Clone()
            hstTp3 = hst3_b3p.Clone()
            hstT4 = hst4_b3.Clone()
            hstTp4 = hst4_b3p.Clone()
            hwjetsT1 = hwjets1_b3.Clone()
            hwjetsTp1 = hwjets1_b3p.Clone()
            hwjetsT2 = hwjets2_b3.Clone()
            hwjetsTp2 = hwjets2_b3p.Clone()
            hwjetsT3 = hwjets3_b3.Clone()
            hwjetsTp3 = hwjets3_b3p.Clone()
            hwjetsT4 = hwjets4_b3.Clone()
            hwjetsTp4 = hwjets4_b3p.Clone()
            hwjetsT5 = hwjets5_b3.Clone()
            hwjetsTp5 = hwjets5_b3p.Clone()
            hwjetsT6 = hwjets6_b3.Clone()
            hwjetsTp6 = hwjets6_b3p.Clone()
            hwjetsT7 = hwjets7_b3.Clone()
            hwjetsTp7 = hwjets7_b3p.Clone()
        #if options.Eldata:
        heldataT = heldata_b3.Clone()
        heldataTp = heldata_b3p.Clone() 
        #if options.Mudata:
        hmudataTp = hmudata_b3p.Clone()
        hmudataT = hmudata_b3.Clone()
    if ipt == 3 :
        hdataT = hdata_b4.Clone()
        hdataTp = hdata_b4p.Clone()
        httbarT = httjets_b4.Clone()
        httbarTp = httjets_b4p.Clone()
        if options.allMC :
            hstT1 = hst1_b4.Clone()
            hstTp1 = hst1_b4p.Clone()
            hstT2 = hst2_b4.Clone()
            hstTp2 = hst2_b4p.Clone()
            hstT3 = hst3_b4.Clone()
            hstTp3 = hst3_b4p.Clone()
            hstT4 = hst4_b4.Clone()
            hstTp4 = hst4_b4p.Clone()
            hwjetsT1 = hwjets1_b4.Clone()
            hwjetsTp1 = hwjets1_b4p.Clone()
            hwjetsT2 = hwjets2_b4.Clone()
            hwjetsTp2 = hwjets2_b4p.Clone()
            hwjetsT3 = hwjets3_b4.Clone()
            hwjetsTp3 = hwjets3_b4p.Clone()
            hwjetsT4 = hwjets4_b4.Clone()
            hwjetsTp4 = hwjets4_b4p.Clone()
            hwjetsT5 = hwjets5_b4.Clone()
            hwjetsTp5 = hwjets5_b4p.Clone()
            hwjetsT6 = hwjets6_b4.Clone()
            hwjetsTp6 = hwjets6_b4p.Clone()
            hwjetsT7 = hwjets7_b4.Clone()
            hwjetsTp7 = hwjets7_b4p.Clone()
        #if options.Eldata:
        heldataT = heldata_b4.Clone()
        heldataTp = heldata_b4p.Clone() 
        #if options.Mudata:
        hmudataTp = hmudata_b4p.Clone()
        hmudataT = hmudata_b4.Clone()
    if ipt == 4 :
        hdataT = hdata_b5.Clone()
        hdataTp = hdata_b5p.Clone()
        httbarT = httjets_b5.Clone()
        httbarTp = httjets_b5p.Clone()
        if options.allMC :
            hstT1 = hst1_b5.Clone()
            hstTp1 = hst1_b5p.Clone()
            hstT2 = hst2_b5.Clone()
            hstTp2 = hst2_b5p.Clone()
            hstT3 = hst3_b5.Clone()
            hstTp3 = hst3_b5p.Clone()
            hstT4 = hst4_b5.Clone()
            hstTp4 = hst4_b5p.Clone() 
            hwjetsT1 = hwjets1_b5.Clone()
            hwjetsTp1 = hwjets1_b5p.Clone()
            hwjetsT2 = hwjets2_b5.Clone()
            hwjetsTp2 = hwjets2_b5p.Clone()
            hwjetsT3 = hwjets3_b5.Clone()
            hwjetsTp3 = hwjets3_b5p.Clone()
            hwjetsT4 = hwjets4_b5.Clone()
            hwjetsTp4 = hwjets4_b5p.Clone()
            hwjetsT5 = hwjets5_b5.Clone()
            hwjetsTp5 = hwjets5_b5p.Clone()
            hwjetsT6 = hwjets6_b5.Clone()
            hwjetsTp6 = hwjets6_b5p.Clone()
            hwjetsT7 = hwjets7_b5.Clone()
            hwjetsTp7 = hwjets7_b5p.Clone()
        #if options.Eldata:
        heldataT = heldata_b5.Clone()
        heldataTp = heldata_b5p.Clone() 
        #if options.Mudata:
        hmudataTp = hmudata_b5p.Clone()
        hmudataT = hmudata_b5.Clone()
    if ipt == 5 :
        hdataT = hdata_Pass.Clone()
        httbarT = httbar_Pass.Clone()
        if options.allMC :
            hwjetsT1 = hwjets1_Pass.Clone()
            hwjetsT2 = hwjets2_Pass.Clone()
            hwjetsT3 = hwjets3_Pass.Clone()
            hwjetsT4 = hwjets4_Pass.Clone()
            hwjetsT5 = hwjets5_Pass.Clone()
            hwjetsT6 = hwjets6_Pass.Clone()
            hwjetsT7 = hwjets7_Pass.Clone()
            hstT1 = hst1_Pass.Clone()
            hstT2 = hst2_Pass.Clone()
            hstT3 = hst3_Pass.Clone()
            hstT4 = hst4_Pass.Clone() 
        heldataT = heldata_Pass.Clone()
        hmudataT = hmudata_Pass.Clone()
    if ipt == 6 :
        hdataT = hdata_Fail.Clone()
        httbarT = httbar_Fail.Clone()
        if options.allMC :
            hstT1 = hst1_Fail.Clone()
            hstT2 = hst2_Fail.Clone()
            hstT3 = hst3_Fail.Clone()
            hstT4 = hst4_Fail.Clone()
            hwjetsT1 = hwjets1_Fail.Clone()
            hwjetsT2 = hwjets2_Fail.Clone()
            hwjetsT3 = hwjets3_Fail.Clone()
            hwjetsT4 = hwjets4_Fail.Clone()
            hwjetsT5 = hwjets5_Fail.Clone()
            hwjetsT6 = hwjets6_Fail.Clone()
            hwjetsT7 = hwjets7_Fail.Clone()
        heldataT = heldata_Fail.Clone()
        hmudataT = hmudata_Fail.Clone()

    # Scale the histograms appropriately

    lumi = 12300.   #  lumi is set in Wtag_def.py
    kfactorw = 1.21

    httbarT = scaleTT(httbarT, ipt)

    intMinis = 55.
    intMaxis = 105.

    if options.allMC :
        hstT = scaleST(hstT1, hstT2, hstT3, hstT4, ipt)
        hwjetsT = scaleWjets(hwjetsT1, hwjetsT2, hwjetsT3, hwjetsT4, hwjetsT5, hwjetsT6, hwjetsT7, ipt)
        httbarT = ScalettMC(httbarT, heldataT, hmudataT , hstT , hwjetsT ,intMinis, intMaxis)
    if ipt <=4 :

        httbarTp = scaleTT(httbarTp, ipt)
        if options.allMC :
            hstTp = scaleST(hstTp1, hstTp2, hstTp3, hstTp4, ipt)
            hwjetsTp = scaleWjets(hwjetsTp1, hwjetsTp2, hwjetsTp3, hwjetsTp4, hwjetsTp5, hwjetsTp6, hwjetsTp7, ipt)
            httbarTp = ScalettMC(httbarTp, heldataTp, hmudataTp , hstTp , hwjetsTp, intMinis, intMaxis )
        

    # Rebin
    hdataT.Rebin(rebinBybin[ipt])
    hmudataT.Rebin(rebinBybin[ipt])
    heldataT.Rebin(rebinBybin[ipt])
    httbarT.Rebin(rebinBybin[ipt])

    if ipt < 5 :
        hdataTp.Rebin(rebinBybin[ipt])
        hmudataTp.Rebin(rebinBybin[ipt])
        heldataTp.Rebin(rebinBybin[ipt])
        httbarTp.Rebin(rebinBybin[ipt])
        if options.allMC :
            hstTp.Rebin(rebinBybin[ipt])
            hwjetsTp.Rebin(rebinBybin[ipt])
            hstTp.SetFillColor(ROOT.kCyan )
    if options.allMC :
        hstT.Rebin(rebinBybin[ipt])
        hwjetsT.Rebin(rebinBybin[ipt])
        hwjetsTp.SetFillColor(ROOT.kRed )
        hwjetsT.SetFillColor(ROOT.kRed)
        hstT.SetFillColor(ROOT.kCyan )

    httbarT.SetFillColor(ROOT.kGreen + 2)

    if ipt < 5 :
        httbarTp.SetFillColor(ROOT.kGreen + 2)
        httbarTp.GetXaxis().SetRangeUser( 40.0, 130. )
        if options.allMC :
            hwjetsTp.GetXaxis().SetRangeUser( 40.0, 130. )
            hstTp.GetXaxis().SetRangeUser( 40.0, 130. )
        hdataTp.SetMarkerStyle(20)
        hmudataTp.SetMarkerStyle(20)
        heldataTp.SetMarkerStyle(20)

    hdataT.SetMarkerStyle(20)
    hmudataT.SetMarkerStyle(20)
    heldataT.SetMarkerStyle(20)

    httbarT.GetXaxis().SetRangeUser( 40.0, 130. )
    mc = ROOT.THStack('WmaSS','; Soft Drop Mass ( GeV ) ;Number of Events')
    if options.allMC :
        hwjetsT.GetXaxis().SetRangeUser( 40.0, 130. )
        hstT.GetXaxis().SetRangeUser( 40.0, 130. )
        mc.Add( hwjetsT)
        mc.Add( hstT)
    mc.Add( httbarT)

    mchist = httbarT.Clone()
    if options.allMC : 
        mchist.Add( hwjetsT )
        mchist.Add( hstT )

    if options.pre :
        httbarT = httbarTp.Clone()

        if options.allMC :
            hwjetsT = hwjetsTp.Clone()
            hstT = hstTp.Clone()
        hdataT = hdataTp.Clone()
        hmudataT = hmudataTp.Clone()
        heldataT = heldataTp.Clone()

    #fitting

    # min  max    binNumber
    #  55.   115.      0
    #  55.   115.      1 
    #  65.   115.      2
    #  55.   115.      3 

    minAvg = 55.
    maxAvg = 115.
    fittingLimits = [   [minAvg, minAvg, minAvg, minAvg, minAvg, minAvg, minAvg ]     ,   [maxAvg, maxAvg, maxAvg, maxAvg, maxAvg, maxAvg, maxAvg ]   ]

    minn = fittingLimits[0][ipt]
    maxx = fittingLimits[1][ipt]
    print "Fitting range is from {0:2.2f} to {1:2.2f} GeV".format(minn, maxx )

    fitter_data = ROOT.TF1("fitter_data", "gaus", minn , maxx )
    fitter_mudata = ROOT.TF1("fitter_mudata", "gaus",  minn , maxx  )
    fitter_eldata = ROOT.TF1("fitter_eldata", "gaus",  minn , maxx  )
    if ipt <= 3:
        data_meanval = Datameans[ipt]
        data_sigmaval = Datasigmas[ipt] 
        mudata_meanval = MuDatameans[ipt]
        mudata_sigmaval = MuDatasigmas[ipt] 
        eldata_meanval = ElDatameans[ipt]
        eldata_sigmaval = ElDatasigmas[ipt] 


    if options.fixFit :
        fitter_data.FixParameter(1, data_meanval)
        fitter_data.FixParameter(2, data_sigmaval)
        fitter_mudata.FixParameter(1, mudata_meanval)
        fitter_mudata.FixParameter(2, mudata_sigmaval)
        fitter_eldata.FixParameter(1, eldata_meanval)
        fitter_eldata.FixParameter(2, eldata_sigmaval)

    fitter_data.SetLineColor(1)
    fitter_data.SetLineWidth(2)
    fitter_data.SetLineStyle(2)
    fitter_mudata.SetLineColor(1)
    fitter_mudata.SetLineWidth(2)
    fitter_mudata.SetLineStyle(2)
    fitter_eldata.SetLineColor(1)
    fitter_eldata.SetLineWidth(2)
    fitter_eldata.SetLineStyle(2)
    if options.fixFit :
        hdataT.Fit(fitter_data,'B' )
        hmudataT.Fit(fitter_mudata,'B' )
        heldataT.Fit(fitter_eldata,'B' )
    else :
        hdataT.Fit(fitter_data,'R' )
        hmudataT.Fit(fitter_mudata,'R' )
        heldataT.Fit(fitter_eldata,'R' )

    amp_data    = fitter_data.GetParameter(0);
    eamp_data   = fitter_data.GetParError(0); 
    mean_data   = fitter_data.GetParameter(1);
    emean_data  = fitter_data.GetParError(1); 
    width_data  = fitter_data.GetParameter(2);
    ewidth_data = fitter_data.GetParError(2); 

    print 'Combined: amp_data {0:6.3}, eamp_data {1:6.3}, mean_data {2:6.3},emean_data {3:6.3}, width_data {4:6.3}, ewidth_data {5:6.3}  '.format(amp_data , eamp_data , mean_data, emean_data,  width_data, ewidth_data   ) 

    mamp_data    = fitter_mudata.GetParameter(0);
    meamp_data   = fitter_mudata.GetParError(0); 
    mmean_data   = fitter_mudata.GetParameter(1);
    memean_data  = fitter_mudata.GetParError(1); 
    mwidth_data  = fitter_mudata.GetParameter(2);
    mewidth_data = fitter_mudata.GetParError(2); 

    print 'Muon data: amp_data {0:6.3}, eamp_data {1:6.3}, mean_data {2:6.3},emean_data {3:6.3}, width_data {4:6.3}, ewidth_data {5:6.3}  '.format(mamp_data , meamp_data , mmean_data, memean_data,  mwidth_data, mewidth_data   ) 

    Eamp_data    = fitter_eldata.GetParameter(0);
    Eeamp_data   = fitter_eldata.GetParError(0); 
    Emean_data   = fitter_eldata.GetParameter(1);
    Eemean_data  = fitter_eldata.GetParError(1); 
    Ewidth_data  = fitter_eldata.GetParameter(2);
    Eewidth_data = fitter_eldata.GetParError(2); 

    print 'Electron data: amp_data {0:6.3}, eamp_data {1:6.3}, mean_data {2:6.3},emean_data {3:6.3}, width_data {4:6.3}, ewidth_data {5:6.3}  '.format(Eamp_data , Eeamp_data , Emean_data, Eemean_data,  Ewidth_data, Eewidth_data   ) 

    if options.pre :
        Datameans[ipt] = mean_data
        Datasigmas[ipt] = width_data
        MuDatameans[ipt] = mmean_data
        MuDatasigmas[ipt] = mwidth_data
        ElDatameans[ipt] = Emean_data
        ElDatasigmas[ipt] = Ewidth_data




    fitter_mc = ROOT.TF1("fitter_mc", "gaus", minn , maxx )
    if ipt <=6:
        mc_meanval = MCmeans[ipt]
        mc_sigmaval = MCsigmas[ipt]


    if options.fixFit :
        fitter_mc.FixParameter(1, mc_meanval)
        fitter_mc.FixParameter(2, mc_sigmaval)

    fitter_mc.SetLineColor(4)
    fitter_mc.SetLineWidth(2)
    fitter_mc.SetLineStyle(4)
    if options.fixFit :
        mchist.Fit("fitter_mc",'B' )
    else :
        mchist.Fit("fitter_mc",'R' )
    amp_mc    = fitter_mc.GetParameter(0);
    eamp_mc   = fitter_mc.GetParError(0); 
    mean_mc   = fitter_mc.GetParameter(1);
    emean_mc  = fitter_mc.GetParError(1); 
    width_mc  = fitter_mc.GetParameter(2);
    ewidth_mc = fitter_mc.GetParError(2); 
          
    print 'MC : amp_mc {0:6.3}, eamp_mc {1:6.3}, mean_mc {2:6.3},emean_mc {3:6.3}, width_mc {4:6.3}, ewidth_mc {5:6.3}  '.format(amp_mc , eamp_mc , emean_mc, emean_mc,  width_mc, ewidth_mc   ) 
    if options.pre and ipt <=3 :
        MCmeans[ipt] = mean_mc
        MCsigmas[ipt] = width_mc


    meanrat = 1.0
    meanrat_uncert = meanrat
    jms = 1.0
    jms_uncert = jms
    
    binSizeData = hdataT.GetBinWidth(0)
    binSizeMC = mchist.GetBinWidth(0) # was mchist

    print "Bin size in data {0:1.2f} and MC  {1:1.2f}".format(binSizeData, binSizeMC )
    mclow = 0. 
    mchigh = 0.

    datalow = 0.
    datahigh = 0.
    if ipt <=6 :
        mclow = MCmeans[ipt] - MCsigmas[ipt] 
        mchigh = MCmeans[ipt] + MCsigmas[ipt] 

        datalow = Datameans[ipt] - Datasigmas[ipt] 
        datahigh = Datameans[ipt] + Datasigmas[ipt]

        mudatalow = MuDatameans[ipt] - MuDatasigmas[ipt] 
        mudatahigh = MuDatameans[ipt] + MuDatasigmas[ipt]

        eldatalow = ElDatameans[ipt] - ElDatasigmas[ipt] 
        eldatahigh = ElDatameans[ipt] + ElDatasigmas[ipt]

    mcAxis = mchist.GetXaxis()
    dataAxis = hdataT.GetXaxis()
    mudataAxis = hmudataT.GetXaxis()
    eldataAxis = heldataT.GetXaxis()

    bminmc = mcAxis.FindBin(mclow)
    bmaxmc = mcAxis.FindBin(mchigh)

    bmindata = hdataT.FindBin(datalow)
    bmaxdata = hdataT.FindBin(datahigh)

    bminmudata = hmudataT.FindBin(mudatalow)
    bmaxmudata = hmudataT.FindBin(mudatahigh)

    bmineldata = heldataT.FindBin(eldatalow)
    bmaxeldata = heldataT.FindBin(eldatahigh)

    if ipt <=6:
        if options.pre  :
            nMCpre[ipt] = mchist.Integral(bminmc , bmaxmc  ) #/ binSizeMC
            nDatapre[ipt] = hdataT.Integral(bmindata, bmaxdata  ) #/ binSizeData
            nMuDatapre[ipt] = hmudataT.Integral(bminmudata, bmaxmudata  ) #/ binSizeData
            nElDatapre[ipt] = heldataT.Integral(bmineldata, bmaxeldata  ) #/ binSizeData
            nMCupre[ipt] =  math.sqrt( nMCpre[ipt] )   #mchist.IntegralError(bminmc , bmaxmc  ) / binSizeMC
            nDataupre[ipt] = math.sqrt(nDatapre[ipt] ) #hdataT.IntegralError(bmindata, bmaxdata  ) / binSizeData
            nMuDataupre[ipt] = math.sqrt(nMuDatapre[ipt] ) 
            nElDataupre[ipt] = math.sqrt(nElDatapre[ipt] ) 
        else :
            nMCpost[ipt] = mchist.Integral(bminmc , bmaxmc  ) #/ binSizeMC
            nDatapost[ipt] = hdataT.Integral(bmindata, bmaxdata  ) #/ binSizeData
            nMuDatapost[ipt] = hmudataT.Integral(bminmudata, bmaxmudata  ) 
            nElDatapost[ipt] = heldataT.Integral(bmineldata, bmaxeldata  ) 
            nMCupost[ipt] =  math.sqrt( nMCpost[ipt] )  #mchist.IntegralError(bminmc , bmaxmc  ) / binSizeMC
            nDataupost[ipt] = math.sqrt(nDatapost[ipt] )#hdataT.IntegralError(bmindata, bmaxdata  ) / binSizeData
            nMuDataupost[ipt] = math.sqrt(nMuDatapost[ipt] )
            nElDataupost[ipt] = math.sqrt(nElDatapost[ipt] )

    meanrat = 0.
    meanrat_uncert = 0.
    meanratel_uncert = 0.
    meanratel = 0.
    meanratmu = 0.
    meanratmu_uncert = 0.
    if mean_mc > 0. : 
        meanrat = mean_data / mean_mc
        meanrat_uncert = meanrat * math.sqrt( (emean_data/mean_data)**2 + (emean_mc/mean_mc)**2 )
        if options.Mudata :
            meanratmu = mmean_data / mean_mc
            meanratmu_uncert = meanratmu * math.sqrt( (memean_data/mmean_data)**2 + (emean_mc/mean_mc)**2 )
        if options.Eldata :
            meanratel_uncert = 0.
            meanratel = 0.
            if  ( abs(Emean_data) > 0.01 ) and  ( abs(mean_mc) > 0.01 ) :
                meanratel = Emean_data / mean_mc
                meanratel_uncert = meanratel * math.sqrt( (Eemean_data/Emean_data)**2 + (emean_mc/mean_mc)**2 )
    jms = 0.
    jms_uncert = 0.
    jms_mu = 0.
    jms_mu_uncert = 0.
    jms_el = 0.
    jms_el_uncert = 0.
    if width_mc > 0. :
        jms = width_data / width_mc
        jms_uncert = jms * math.sqrt( (ewidth_data/width_data)**2 + (ewidth_mc/width_mc)**2 )
        if options.Mudata :
            jms_mu = mwidth_data / width_mc
            jms_mu_uncert = jms_mu * math.sqrt( (mewidth_data/mwidth_data)**2 + (ewidth_mc/width_mc)**2 )
        if options.Eldata :
            jms_el = Ewidth_data / width_mc
            jms_el_uncert =  0.0
            if abs(Ewidth_data) > 0.0001 :
                jms_el_uncert = jms_el * math.sqrt( (Eewidth_data/Ewidth_data)**2 + (ewidth_mc/width_mc)**2 )

    #print 'data_over_mc peak combined {0:6.3}, muon {1:6.3}, electron {2:6.3} '.format(meanrat, meanratmu, meanratel)
    #print '...........................................................'

    ibin = hpeak.GetXaxis().FindBin(pt)
    hpeak.SetBinContent(ibin, meanrat ) 
    hwidth.SetBinContent(ibin, jms )
    hpeak.SetBinError(ibin, meanrat_uncert)   
    hwidth.SetBinError(ibin, jms_uncert)

    if options.Mudata :
        hpeakmu.SetBinContent(ibin, meanratmu ) 
        hwidthmu.SetBinContent(ibin, jms_mu )
        hpeakmu.SetBinError(ibin, meanratmu_uncert)   
        hwidthmu.SetBinError(ibin, jms_mu_uncert)
    if options.Eldata :
        hpeakel.SetBinContent(ibin, meanratel ) 
        hwidthel.SetBinContent(ibin, jms_el )
        hpeakel.SetBinError(ibin, meanratel_uncert)   
        hwidthel.SetBinError(ibin, jms_el_uncert)

    if ipt <=6:
        if options.pre :
            ibin = hNpassDataPre.GetXaxis().FindBin(pt)
            hNpassDataPre.SetBinContent(ibin, nDatapre[ipt])
            hNpassMuDataPre.SetBinContent(ibin, nMuDatapre[ipt])
            hNpassElDataPre.SetBinContent(ibin, nElDatapre[ipt])
            hNpassMCPre.SetBinContent(ibin, nMCpre[ipt])
            hNpassDataPre.SetBinError(ibin, nDataupre[ipt])
            hNpassMuDataPre.SetBinError(ibin, nMuDataupre[ipt])
            hNpassElDataPre.SetBinError(ibin, nElDataupre[ipt])
            hNpassMCPre.SetBinError(ibin, nMCupre[ipt])
            hmeanDataPre.SetBinContent(ibin, Datameans[ipt]) 
            hmeanMuDataPre.SetBinContent(ibin, MuDatameans[ipt]) 
            hmeanElDataPre.SetBinContent(ibin, ElDatameans[ipt]) 
            hmeanMCPre.SetBinContent(ibin, MCmeans[ipt] )
            hsigmaDataPre.SetBinContent(ibin, Datasigmas[ipt])
            hsigmaMuDataPre.SetBinContent(ibin, MuDatasigmas[ipt])
            hsigmaElDataPre.SetBinContent(ibin, ElDatasigmas[ipt])
            hsigmaMCPre.SetBinContent(ibin,  MCsigmas[ipt] )
        else :
            ibin = hNpassDataPost.GetXaxis().FindBin(pt)
            hNpassDataPost.SetBinContent(ibin, nDatapost[ipt])
            hNpassMuDataPost.SetBinContent(ibin, nMuDatapost[ipt])
            hNpassElDataPost.SetBinContent(ibin, nElDatapost[ipt])
            hNpassMCPost.SetBinContent(ibin, nMCpost[ipt])
            hNpassDataPost.SetBinError(ibin, nDataupost[ipt])
            hNpassMuDataPost.SetBinError(ibin, nMuDataupost[ipt])
            hNpassElDataPost.SetBinError(ibin, nElDataupost[ipt])
            hNpassMCPost.SetBinError(ibin, nMCupost[ipt])


    #  DRAWING TIME!!!!!!!!!!!!

    if not options.quickPlot :
        ROOT.gStyle.SetOptFit(1111)
        ROOT.gStyle.SetOptStat(0000000000)
        cmsTextFont   = 61  

        if not (options.Mudata and options.Eldata) :

             #Wmass_data = ScaleStackPlot(Wmass, "Jet Mass (GeV)", 1.0 , 3, 40. , 130., ttbarHist, st1Hist,  st2Hist, st3Hist, st4Hist, wjets1Hist , wjets2Hist, wjets3Hist, wjets4Hist, wjets5Hist, wjets6Hist, wjets7Hist )

            c = ROOT.TCanvas('WmaSS','WmaSS',50,50,W,H)
            c.SetFillColor(0)
            c.SetBorderMode(0)
            c.SetFrameFillStyle(0)
            c.SetFrameBorderMode(0)
            c.SetLeftMargin( L/W )
            c.SetRightMargin( R/W )
            c.SetTopMargin( T/H )
            c.SetBottomMargin( B/H )
            c.SetTickx(0)
            c.SetTicky(0)

            #hdataT.Draw('e')
            mc.Draw("histsame")

            max1 = hdataT.GetMaximum()
            max2 = mc.GetHistogram().GetMaximum() # mc.GetHistogram().GetMaximum()
            hdataT.SetMaximum( max (max1,max2) * 1.618 )
            mc.SetMaximum( max (max1,max2) * 1.618 )
            hdataT.GetXaxis().SetRangeUser( 40.0, 130. )
            mc.GetXaxis().SetRangeUser( 40.0, 130. )

            mc.Draw("histsame")

            hdataT.Draw('esamex0')

            #hdataT.Draw('e same')
            #hdataT.Draw("axis same")
            fitter_mc.Draw("same")
            fitter_data.Draw("same")

            CMS_lumi.CMS_lumi(c, iPeriod, iPos)

            if not options.legleft : 
                leg = ROOT.TLegend( 0.698, 0.316, 0.816, 0.5106)  #leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            else :
                leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            leg.SetFillColor(0)
            leg.SetBorderSize(0)

            leg.AddEntry( hdataT, 'Data', 'p')
            leg.AddEntry( httbarT, 't#bar{t}', 'f')
            if options.allMC :
                leg.AddEntry( hwjetsT, 'W + jets', 'f')
                leg.AddEntry( hstT, 'Single Top', 'f')
            '''
            leg.AddEntry( hzjets, 'Z+Jets', 'f')

            '''

            if options.Type2 :
                hdataT.SetXTitle("Soft Drop Jet Mass (GeV)")
            if not options.Type2 :
                hdataT.SetXTitle("Soft Drop Subjet Mass (GeV)")
            hdataT.SetYTitle("Events")
            hdataT.BufferEmpty(1)
            hdataT.GetXaxis().SetTitleSize(0.047)
            hdataT.GetYaxis().SetTitleSize(0.047)

            leg.Draw()

            tlx = ROOT.TLatex()
            tlx.SetNDC()
            tlx.SetTextFont(42)
            tlx.SetTextSize(0.057)
            #tlx.DrawLatex(0.68, 0.957,  str(lumi) + " fb^{-1} (13TeV)")
            tlx.DrawLatex(0.67, 0.86, binlabel )
            c.Update()
            c.Draw()
            sele = options.filestr
            if options.pre :
                sele = options.filestr + '_preWTag'
            if (ipt < 5  and not options.Type2):
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 5 :
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 6 :
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                c.Print(plotdir + '/AllData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )

        if options.Mudata:

            cc = ROOT.TCanvas('WmaSSMu','WmaSSMu',50,50,W,H)
            cc.SetFillColor(0)
            cc.SetBorderMode(0)
            cc.SetFrameFillStyle(0)
            cc.SetFrameBorderMode(0)
            cc.SetLeftMargin( L/W )
            cc.SetRightMargin( R/W )
            cc.SetTopMargin( T/H )
            cc.SetBottomMargin( B/H )
            cc.SetTickx(0)
            cc.SetTicky(0)

            hmudataT.Draw('e')
            mc.Draw("histsame")
            hmudataT.Draw('esamex0')

            hmudataT.Draw('e same')
            hmudataT.Draw("axis same")
            fitter_mc.Draw("same")
            fitter_mudata.Draw("same")

            CMS_lumi.CMS_lumi(cc, iPeriod, iPos)

            if not options.legleft : 
                leg = ROOT.TLegend( 0.698, 0.316, 0.816, 0.5106)  #leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            else :
                leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            leg.SetFillColor(0)
            leg.SetBorderSize(0)

            leg.AddEntry( hmudataT, 'Muon Data', 'p')
            leg.AddEntry( httbarT, 't#bar{t}', 'f')
            if options.allMC :
                leg.AddEntry( hwjetsT, 'W + jets', 'f')
                leg.AddEntry( hstT, 'Single Top', 'f')
            
            #leg.AddEntry( hzjets, 'Z+Jets', 'f')

            
            max1 = hmudataT.GetMaximum()
            max2 = mc.GetMaximum() # mc.GetHistogram().GetMaximum()
            hmudataT.GetXaxis().SetRangeUser( 40.0, 130. )
            mc.GetXaxis().SetRangeUser( 40.0, 130. )

            #hmudataT.SetMaximum( max (max1,max2) * 1.618 )

            hmudataT.SetXTitle("Subjet Soft Drop Mass (GeV)")
            hmudataT.SetYTitle("Events")
            hmudataT.BufferEmpty(1)
            hmudataT.GetXaxis().SetTitleSize(0.047)
            hmudataT.GetYaxis().SetTitleSize(0.047)
            hmudataT.GetXaxis().SetLabelSize(0.04)
            hmudataT.GetYaxis().SetLabelSize(0.04)

            leg.Draw()

            tlx = ROOT.TLatex()
            tlx.SetNDC()
            tlx.SetTextFont(42)
            tlx.SetTextSize(0.057)

            tlx.DrawLatex(0.67, 0.86, binlabel )

            cc.Update()
            cc.Draw()
            sele = options.filestr
            if options.pre :
                sele = options.filestr + '_preWTag'
            if ipt < 5 and not options.Type2 :
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + sele + '.png', 'png' ) 
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 5 :
                #hmudataT.SetMaximum(10000   )
                #mc.SetMaximum( 10000  )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 6 and not options.pre:
                hmudataT.SetMaximum( 520. )
                mc.SetMaximum( 520. )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                cc.Print(plotdir + '/MuData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
        


        if options.Eldata :
            ccc = ROOT.TCanvas('WmaSSel','WmaSSel',50,50,W,H)
            ccc.SetFillColor(0)
            ccc.SetBorderMode(0)
            ccc.SetFrameFillStyle(0)
            ccc.SetFrameBorderMode(0)
            ccc.SetLeftMargin( L/W )
            ccc.SetRightMargin( R/W )
            ccc.SetTopMargin( T/H )
            ccc.SetBottomMargin( B/H )
            ccc.SetTickx(0)
            ccc.SetTicky(0)

            heldataT.Draw('e')
            mc.Draw("histsame")
            heldataT.Draw('esamex0')

            heldataT.Draw('e same')
            heldataT.Draw("axis same")
            fitter_mc.Draw("same")
            fitter_eldata.Draw("same")

            CMS_lumi.CMS_lumi(ccc, iPeriod, iPos)

            if not options.legleft : 
                leg = ROOT.TLegend( 0.698, 0.316, 0.816, 0.5106)  #leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            else :
                leg = ROOT.TLegend( 0.746, 0.691, 0.864, 0.886)
            leg.SetFillColor(0)
            leg.SetBorderSize(0)

            leg.AddEntry( heldataT, 'Electron Data', 'p')
            leg.AddEntry( httbarT, 't#bar{t}', 'f')
            if options.allMC :
                leg.AddEntry( hwjetsT, 'W + jets', 'f')
                leg.AddEntry( hstT, 'Single Top', 'f')

            max1 = heldataT.GetMaximum()
            max2 = mc.GetMaximum() # mc.GetHistogram().GetMaximum()

            heldataT.SetMaximum( max (max1,max2) * 1.618 )

            heldataT.SetXTitle("Subjet Soft Drop Mass (GeV)")
            heldataT.SetYTitle("Events")
            heldataT.BufferEmpty(1)
            heldataT.GetXaxis().SetTitleSize(0.047)
            heldataT.GetYaxis().SetTitleSize(0.047)
            heldataT.GetXaxis().SetLabelSize(0.04)
            heldataT.GetYaxis().SetLabelSize(0.04)

            leg.Draw()

            tlx = ROOT.TLatex()
            tlx.SetNDC()
            tlx.SetTextFont(42)
            tlx.SetTextSize(0.057)
            tlx.DrawLatex(0.67, 0.86, binlabel )


            ccc.Update()
            ccc.Draw()
            sele = options.filestr
            if options.pre and not options.Type2 :
                sele = options.filestr + '_preWTag'
            ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
            ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
            ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_Bin'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 5 :
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_passTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )
            if ipt == 6 :
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.png', 'png' )
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.pdf', 'pdf' )
                ccc.Print(plotdir + '/ElData/'+ options.treeLocation +'/wMass_failTau21'+ str(ipt) + '_' +str(rebinBybin[ipt]) + '_' + '_' + sele + '.root', 'root' )

        if ipt <=4 and not options.Type2:
            ee = ROOT.TCanvas('wid','wid')
            hwidth.Draw('e')

            hwidth.SetMarkerStyle(20)
            hwidth.SetMaximum(3.0)
            hwidth.SetMinimum(0.0)

            CMS_lumi.CMS_lumi(ee, iPeriod, iPos)

            ee.Update()
            ee.Draw()

            if  options.Eldata : # working here 
                ee.Print(plotdir + '/ElData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.png', 'png' )
                ee.Print(plotdir + '/ElData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.pdf', 'pdf' )
                ee.Print(plotdir + '/ElData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.root', 'root' )
            elif options.Mudata : # working here 
                ee.Print(plotdir + '/MuData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.png', 'png' )
                ee.Print(plotdir + '/MuData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.pdf', 'pdf' )
                ee.Print(plotdir + '/MuData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.root', 'root' )
            elif not (options.Eldata and options.Mudata): # working here 
                ee.Print(plotdir + '/AllData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.png', 'png' )
                ee.Print(plotdir + '/AllData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.pdf', 'pdf' )
                ee.Print(plotdir + '/AllData/' + options.treeLocation + '/JMR_W_' + str(options.filestr) + '.root', 'root' )


        if options.PlotPtTypes : # FIX THIS : fill these histos in selector code
            ff = ROOT.TCanvas('P_t_Comparison','P_t_Comparison')
            ff.SetLogy()
            hpts.Draw()
            hpts2.Draw('same')
            hptsMC.Draw('same')
            hpts2MC.Draw('same')
            hpts.SetLineColor(ROOT.kBlue)
            hpts2.SetLineColor(ROOT.kCyan)
            hptsMC.SetLineColor(ROOT.kMagenta)
            hpts2MC.SetLineColor(ROOT.kGreen)
           
            xmax =  1000.

            hpts2.GetXaxis().SetRangeUser(0.0,xmax)
            hpts.GetXaxis().SetRangeUser(0.0, xmax)
            hpts2MC.GetXaxis().SetRangeUser(0.0,xmax)
            hptsMC.GetXaxis().SetRangeUser(0.0, xmax)

            maxpt2y = hpts2.GetMaximum()
            maxpty = hpts.GetMaximum()
            maxpt2MCy = hpts2MC.GetMaximum()
            maxptMCy = hptsMC.GetMaximum()

            maxpt = 1.618 * max(maxpt2y, maxpty, maxpt2MCy, maxptMCy)

            hpts2.SetMaximum(maxpt)
            #hpts2.SetMinimum(maxpt)
            hpts.SetMaximum(maxpt)
            #hpts.SetMinimum()
            hpts2MC.SetMaximum(maxpt)
            #hpts2MC.SetMinimum(0.0001)
            hptsMC.SetMaximum(maxpt)


            CMS_lumi.CMS_lumi(ff, iPeriod, iPos)
            tlx = ROOT.TLatex()
            tlx.SetNDC()
            tlx.SetTextFont(42)
            tlx.SetTextSize(0.057)

            legy = ROOT.TLegend( 0.68, 0.68, 0.799, 0.875)
            legy.SetFillColor(0)
            legy.SetBorderSize(0)

            legy.AddEntry( hpts, 'Data: Type 1', 'l')
            legy.AddEntry( hpts2, 'Data: Type 2', 'l')
            legy.AddEntry( hptsMC, 'MC: Type 1', 'l')
            legy.AddEntry( hpts2MC, 'MC: Type 2', 'l')
            legy.Draw()

            ff.Update()
            ff.Draw()
            ff.Print(plotdir + '/AllData/'+ options.treeLocation +'Pt_type1and2_' + options.filestr + '.png', 'png' )
            ff.Print(plotdir + '/AllData/'+ options.treeLocation +'Pt_type1and2_' + options.filestr + '.pdf', 'pdf' )
            ff.Print(plotdir + '/AllData/'+ options.treeLocation +'Pt_type1and2_' + options.filestr + '.root', 'root' )

        if ipt <= 3 and not options.Type2:
            gg = ROOT.TCanvas('peak','peak')
            hpeak.Draw('e')

            hpeak.SetMarkerStyle(20)
            #hpeak.GetYaxis().SetRange(0.8,1.0)
            hpeak.SetMaximum(3.0)
            hpeak.SetMinimum(0.0)

            CMS_lumi.CMS_lumi(gg, iPeriod, iPos)

            tlx = ROOT.TLatex()
            tlx.SetNDC()
            tlx.SetTextFont(42)
            tlx.SetTextSize(0.057)

            gg.Update()
            gg.Draw() 
            if  options.Eldata : # working here 
                gg.Print(plotdir + '/ElData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.png', 'png' )
                gg.Print(plotdir + '/ElData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.pdf', 'pdf' )
                gg.Print(plotdir + '/ElData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.root', 'root' )
            elif options.Mudata : # working here 
                gg.Print(plotdir + '/MuData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.png', 'png' )
                gg.Print(plotdir + '/MuData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.pdf', 'pdf' )
                gg.Print(plotdir + '/MuData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.root', 'root' )
            elif not (options.Mudata and options.Eldata): # working here 
                gg.Print(plotdir + '/AllData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.png', 'png' )
                gg.Print(plotdir + '/AllData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.pdf', 'pdf' )
                gg.Print(plotdir + '/AllData/' + options.treeLocation + '/JMS_W_' + options.filestr + '.root', 'root' )

if not options.quickPlot :
    #   SF =  ( nData / nDatap ) / ( nMC / nMCp )
    print "Integrals of fitted mass peak for W subjet of high Pt top:"


    print "##################  DATA  #############################"

    print "N pass post W tag Data pt 200-300 : " + str( nDatapost[0])
    print "N pass pre W tag Data pt 200-300 : " + str(nDatapre[0])

    print "N pass post W tag Data pt 300-400 : " + str(nDatapost[1])
    print "N pass pre W tag Data pt 300-400 : " + str(nDatapre[1])

    print "N pass post W tag Data pt 400-500 : " + str(nDatapost[2])
    print "N pass pre W tag Data pt 400-500 : " + str(nDatapre[2])

    print "N pass post W tag Data pt 500-800 : " + str(nDatapost[3])
    print "N pass pre W tag Data pt 500-800 : " + str(nDatapre[3])

    print "N pass post W tag Data pt 200-800 : " + str(nDatapost[4])
    print "N pass pre W tag Data pt 200-800 : " + str(nDatapre[4])

    print "N pass post W tag Data pt 200-800, pass tau21 : " + str(nDatapost[5])
    print "N pass pre W tag Data pt 200-800,  pass tau21  : " + str(nDatapre[5])

    print "N pass post W tag Data pt 200-800, fail tau21 : " + str(nDatapost[6])
    print "N pass pre W tag Data pt 200-800,  fail tau21  : " + str(nDatapre[6])

    print "##################   MC   #############################"

    print "N pass post W tag MC pt 200-300 : " + str( nMCpost[0])
    print "N pass pre W tag MC pt 200-300 : " + str(nMCpre[0])

    print "N pass post W tag MC pt 300-400 : " + str(nMCpost[1])
    print "N pass pre W tag MC pt 300-400 : " + str(nMCpre[1])

    print "N pass post W tag MC pt 400-500 : " + str(nMCpost[2])
    print "N pass pre W tag MC pt 400-500 : " + str(nMCpre[2])

    print "N pass post W tag MC pt 500-inf : " + str(nMCpost[3])
    print "N pass pre W tag MC pt 500-inf : " + str(nMCpre[3])

    print "N pass post W tag MC pt 200-800 : " + str(nMCpost[4])
    print "N pass pre W tag MC pt 200-800 : " + str(nMCpre[4])

    print "N pass post W tag MC pt 200-800, pass tau21 : " + str(nMCpost[5])
    print "N pass pre W tag MC pt 200-800,  pass tau21  : " + str(nMCpre[5])

    print "N pass post W tag MC pt 200-800, fail tau21 : " + str(nMCpost[6])
    print "N pass pre W tag MC pt 200-800,  fail tau21  : " + str(nMCpre[6])

    print "###############################################"




    if not options.pre :
        for ipt in xrange(0, len(ptBs)-1 ) :
            if options.Mudata :
                datapost = nMuDatapost[ipt] 
                datapre  = nMuDatapre[ipt] 

            if options.Eldata :
                datapost = nElDatapost[ipt] 
                datapre  = nElDatapre[ipt] 

            if not (options.Eldata and options.Mudata):
                datapost = nDatapost[ipt] 
                datapre  = nDatapre[ipt] 
            pt = ptBs[ipt]
            ptToFill = float(pt)
            if pt > 800. :
                ptToFill = 799.
            bot = -1.
            if float(nMCpre[ipt]) > 0.001 :
                bot = ( float(nMCpost[ipt]) / float(nMCpre[ipt]) )
            if (nDatapre[ipt] > 0.001 and nMCpre[ipt] > 0.001 and pt >= 201. and float(datapre) > 0.001 and  bot > 0.001) :
                print "bot {} datapre {} datapost {}".format(bot, datapre, datapost)
                SF =  ( float(datapost) / float(datapre) ) / bot
                SF_sd = SF * math.sqrt(   (- float(datapost) + float(datapre) ) / ( float(datapost) * float(datapre) )  + (-float(nMCpost[ipt]) + float(nMCpre[ipt])) / (float(nMCpost[ipt]) * float(nMCpre[ipt]))  )
                print "............................................"
                print "             SCALE FACTOR                   "
                print "............................................"
                print "pt Bin lower bound in GeV :  " + str(pt)
                print "Preliminary W tagging SF from subjet w : " + str(SF)
                print "Data efficiency for this  bin {0:5.3}".format(  float(datapost) / float(datapre) )
                print "MC efficiency for this  bin" + str(float(nMCpost[ipt]) / float(nMCpre[ipt]))
                print "standard deviation : " + str(SF_sd)
                print "............................................"
                ibin = hscale.GetXaxis().FindBin(ptToFill)
                hscale.SetBinContent(ibin, SF )
                hscale.SetBinError(ibin, SF_sd)
            else :
                ibin = hscale.GetXaxis().FindBin(ptToFill)
                hscale.SetBinContent(ibin, 0.0 )




        # DRAWING TIME!


        # Plot the scale factor in each Pt bin

        ROOT.gStyle.SetOptStat(0000000000)

        d = ROOT.TCanvas('sf','sf',50,50,W,H)
        d.SetFillColor(0)
        d.SetBorderMode(0)
        d.SetFrameFillStyle(0)
        d.SetFrameBorderMode(0)
        d.SetLeftMargin( L/W )
        d.SetRightMargin( R/W )
        d.SetTopMargin( T/H )
        d.SetBottomMargin( B/H )
        d.SetTickx(0)
        d.SetTicky(0)



        hscale.Draw('P')

        hscale.SetMaximum(2.)
        hscale.SetMinimum(0.0)

        hscale.SetMarkerStyle(20)

        hscale.SetXTitle("Subjet P_{T} (GeV)")
        hscale.SetYTitle("Scale Factor")
        hscale.BufferEmpty(1)
        hscale.GetXaxis().SetTitleSize(0.047)
        hscale.GetYaxis().SetTitleSize(0.047)
        hscale.GetXaxis().SetLabelSize(0.04)
        hscale.GetYaxis().SetLabelSize(0.04)

        CMS_lumi.CMS_lumi(d, iPeriod, iPos)


        #hscale.GetYaxis().SetRange(0.8,1.0)

        tlx = ROOT.TLatex()
        tlx.SetNDC()
        tlx.SetTextFont(42)
        tlx.SetTextSize(0.057)
        tlx.SetTextSize(0.029)
        xInfo = 0.15
        yInfoTop = 0.475
        yInfo2 = yInfoTop-0.042
        yInfo3 = yInfo2-0.042
        yInfo4 = yInfo3-0.042
        yInfo5 = yInfo4-0.042
        yInfo6 = yInfo5-0.042
        yInfo7 = yInfo6-0.042
        yInfo8 = yInfo7-0.042

        d.Update()
        d.Draw()



if (options.quickPlot or not options.quickPlot) and not options.pre: 

    if options.allMC :

        rebinNumis = 20


        # Plot St after final selection

        # Plot the subjet tau 21 distribution
        #Plot_AK8SJTau21_mid = ScaleStackPlot("AK8SJTau21_mid", "#tau_{21}", 1.0, rebinNumis, 0., 600., httbarp_ak8SJtau21 , hst1p_ak8tau21, hst2p_ak8tau21, hst3p_ak8tau21, hst4p_ak8tau21, hwjets1p_ak8tau21, hwjets2p_ak8tau21, hwjets3p_ak8tau21, hwjets4p_ak8tau21, hwjets5p_ak8tau21, hwjets6p_ak8tau21, hwjets7p_ak8tau21, hdatap_ak8tau21, hmudatap_ak8tau21 , heldatap_ak8tau21, IntMin, IntMax )

        # Plot tau 21 distribution
        Plot_AK8Tau21_mid = ScaleStackPlot("AK8Tau21_mid", "#tau_{21}", 1.0, rebinNumis, 0., 1., httbarp_ak8tau21 , hst1p_ak8tau21, hst2p_ak8tau21, hst3p_ak8tau21, hst4p_ak8tau21, hwjets1p_ak8tau21, hwjets2p_ak8tau21, hwjets3p_ak8tau21, hwjets4p_ak8tau21, hwjets5p_ak8tau21, hwjets6p_ak8tau21, hwjets7p_ak8tau21, hdatap_ak8tau21, hmudatap_ak8tau21 , heldatap_ak8tau21 , 0., 1. )

        # Plot the Lepton Pt after AK8 Pt > 200 GeV and lepton and ak4 cuts but before other ak8 cuts
        #print "THE Integral of ttbar Lepton Pt  httbarp_leppt is : ".format( httbarp_leppt.Integral() )

        Plot_PtLep_mid = ScaleStackPlot("Pt_Lep_mid", "Lepton Pt (GeV)", 1.0, rebinNumis, 0., 600., httbarp_leppt , hst1p_leppt, hst2p_leppt, hst3p_leppt, hst4p_leppt, hwjets1p_leppt, hwjets2p_leppt, hwjets3p_leppt, hwjets4p_leppt, hwjets5p_leppt, hwjets6p_leppt, hwjets7p_leppt, hdatap_leppt, hmudatap_leppt , heldatap_leppt , 53., 300. )

        # Plot the Lepton Pt before all selection except  AK8 Pt > 200 GeV

        Plot_PtLep_pre = ScaleStackPlot("Pt_Lep_pre", "Lepton Pt (GeV)", 1.0, rebinNumis, 0., 600., httbarpo_leppt , hst1po_leppt, hst2po_leppt, hst3po_leppt, hst4po_leppt, hwjets1po_leppt, hwjets2po_leppt, hwjets3po_leppt, hwjets4po_leppt, hwjets5po_leppt, hwjets6po_leppt, hwjets7po_leppt, hdatapo_leppt, hmudatapo_leppt , heldatapo_leppt, 53., 300.  )

        # Plot the Lepton Pt after final selection

        Plot_PtLep_post = ScaleStackPlot("Pt_Lep_post", "Lepton Pt (GeV)", 1.0, rebinNumis, 0., 600., httbar_leppt , hst1_leppt, hst2_leppt, hst3_leppt, hst4_leppt, hwjets1_leppt, hwjets2_leppt, hwjets3_leppt, hwjets4_leppt, hwjets5_leppt, hwjets6_leppt, hwjets7_leppt, hdata_leppt, hmudata_leppt , heldata_leppt, 53., 300.  )


        # Plot the AK8 Pt after final selection

        Plot_PtAK8_final = ScaleStackPlot("Pt_AK8_final", "AK8 Pt (GeV)", 1.0, rebinNumis, 0., 1000., httbar_ak8pt , hst1_ak8pt, hst2_ak8pt, hst3_ak8pt, hst4_ak8pt, hwjets1_ak8pt, hwjets2_ak8pt, hwjets3_ak8pt, hwjets4_ak8pt, hwjets5_ak8pt, hwjets6_ak8pt, hwjets7_ak8pt, hdata_ak8pt, hmudata_ak8pt , heldata_ak8pt, 200.,800. )

        #Plot the Ht of the lepton

        Plot_HtLep = ScaleStackPlot("Ht_Lep", "Lepton Ht (GeV)", 1.0, rebinNumis, 0., 600., httbar_lephtlep , hst1_lephtlep, hst2_lephtlep, hst3_lephtlep, hst4_lephtlep, hwjets1_lephtlep , hwjets2_lephtlep, hwjets3_lephtlep, hwjets4_lephtlep, hwjets5_lephtlep, hwjets6_lephtlep, hwjets7_lephtlep, hdata_lephtlep, hmudata_lephtlep , heldata_lephtlep, 100., 400.  )

fout.cd()
fout.Write()
fout.Close()


ts = (time.time() -startTime)

unitIs = 'Seconds'
if ts > 60. :
    ts /= 60.
    unitIs = 'Minutes'
    if ts > 60. :
        ts /= 60.
        unitIs = 'Hours' 

print ('The script took {0}  {1}!'.format(   ts  , unitIs    ) )
