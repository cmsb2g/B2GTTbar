#!/usr/bin/env python
from optparse import OptionParser
parser = OptionParser()

parser.add_option('--bunchX', metavar='F', type='string', action='store',
                  dest='BX',
                  default='25ns',
                  help='Bunch Crossing ex: 25 or 50ns')
parser.add_option('--files', type='string', action='store',
                  dest='inFiles',
                  help='Input files')
#parser.add_option('--dynamic', '--db',
#                  action='store_true',
#                  default=False,
#                  dest='dynamicBin',
#                  help='Dynamic binning based on events per bin')
parser.add_option('--setTitles', metavar='F', type='string', action='store',
                  default=None,
                  dest='SampleTitle',
                  help='Set desired title for plots, typically indicating sample')


(options, args) = parser.parse_args()
argv = []

import ROOT

ROOT.gStyle.SetOptStat(000000)
ROOT.gROOT.Macro("rootlogon.C")

histlist = [
'h_mttbar',
'h_ptLep',
'h_etaLep',
'h_met',
'h_dRMin',
'h_ptAK4',
'h_etaAK4',
'h_mAK4',
'h_bdiscAK4',
'h_ptAK8',
'h_etaAK8',
'h_mAK8',
'h_mprunedAK8',
'h_mfilteredAK8',
'h_mtrimmedAK8',
'h_mSDropAK8',
'h_nsjAK8',
'h_tau21AK8',
'h_tau32AK8' 
]
Titles = [
';Mass(GeV) of ttbar;Number of Events',
';p_{T}(GeV) of Lepton;Number of Events',
';y of Lepton;Number of Events',
';MET(GeV);Number of Events',
';dRMin;Number of Events',
';p_{T}(GeV) of AK4 Jet;Number of Events',
';y of AK4 Jet;Number of Events',
';Mass(GeV) of AK4 Jet;Number of Events',
';bDisc of AK4 Jet;Number of Events',
';p_{T}(GeV) of AK8 Jet;Number of Events',
';y of AK8 Jet;Number of Events',
';Mass(GeV) of AK8 Jet;Number of Events',
';Pruned Mass (GeV);Number of Events',
';Filtered Mass (GeV);Number of Events',
';Trimmed Mass (GeV);Number of Events',
';Soft Drop Mass (GeV);Number of Events',
';Number of Subjets;Number of Events',
';\Tau_{21};Number of Events',
';\Tau_{32};Number of Events'
]

Files = []

fileList = file(options.inFiles)
filesraw = fileList.readlines()

for filename in filesraw :
    if len( filename ) > 2 :
        s = filename.rstrip()
        Files.append( ROOT.TFile(s) )



colors = [2,4,7,9,1]
markers = [20,21,22,23,24]
Samples = [
"TTBar",
"ZPrime 2 TeV",
"ZPrime 2.5 TeV",
"ZPrime 3 TeV",
"QCD"
]

canvs = []

#Get various signal region backgrounds
for ihist,shist in enumerate( histlist ) :
    print 'processing shist = ' +  shist
    canv = ROOT.TCanvas(shist, shist, 1600, 800)
    leg = ROOT.TLegend(0.8, 0.6, 1.05, 0.85)

    for iinfile,infile in enumerate(Files) :
        print '   processing infile = ' + infile.GetName()
        
        hist = infile.Get( shist )
        
        if iinfile == 0 : 
            scale = hist.GetEntries()
        else :
            if hist.GetEntries() != 0 :
                hist.Scale(scale/hist.GetEntries())


        hist.SetMarkerColor(colors[iinfile])
        hist.SetLineColor(colors[iinfile])
        hist.SetMarkerStyle(markers[iinfile])
        
        hist.SetTitle( Titles[ihist] )
        
        leg.AddEntry( hist, Samples[iinfile], 'p')
        
        if iinfile == 0 : 
            hist.Draw()
        else :
            hist.Draw('same')
            
    leg.Draw()
    canv.Draw()
    canvs.append(canv)
    canv.Print('pngs/' + canv.GetName() + '_' + options.BX + '.png' )
    canv.Print('pdfs/' + canv.GetName() + '_' + options.BX + '.pdf' )
