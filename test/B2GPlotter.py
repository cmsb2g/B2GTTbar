#!/usr/bin/env python
from optparse import OptionParser
parser = OptionParser()

parser.add_option('--stage', type='string', action='store',
                  dest='stage',
                  default = None,
                  help='Stage of selection')


parser.add_option('--lep', type='string', action='store',
                  dest='lep',
                  default = None,
                  help='Lepton "el" or "mu"')

parser.add_option('--hmax', type='float', action='store',
                  dest='hmax',
                  default = None,
                  help='Histogram y max')


parser.add_option('--plotW', action='store_true',
                  dest='plotW',
                  default = False,
                  help='Plot W or top')


(options, args) = parser.parse_args()
argv = []

import ROOT

ROOT.gStyle.SetOptStat(000000)
ROOT.gROOT.Macro("rootlogon.C")
ROOT.gStyle.SetTitleOffset(1.0, "Y")
HNAME_NDX = 0
HTITLE_NDX = 1
REBIN_NDX = 2
HMAX_NDX = 3
HXMIN_NDX = 4
HXMAX_NDX = 5
LEGXMIN_NDX = 6
LEGYMIN_NDX = 7
LEGXMAX_NDX = 8
LEGYMAX_NDX = 9
LOGY_NDX = 10

if options.plotW :
    hists = [
    #    ['h_ptLep',            ';p_{T}(GeV) of Lepton;Number of Events', 500., 0., 1000., 0.6, 0.6, 0.85, 0.85],
    #    ['h_etaLep',           ';y of Lepton;Number of Events',          500., -3., 3.,   0.6, 0.6, 0.85, 0.85],
    #    ['h_met',              ';MET(GeV);Number of Events',             500., 0., 1000., 0.6, 0.6, 0.85, 0.85],
    #    ['h_dRMin',            ';dRMin;Number of Events',                500., 0., 5.,    0.6, 0.6, 0.85, 0.85],
    #    Name                  Title                                                        Rebin Max, Xmin, Xmax   Legend location 
        ['SelectionLoop/h_ptAK4',            ';p_{T}(GeV) of AK4 Jet;Number of Events',     None,1000., 0., 1500.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_etaAK4',           ';y of AK4 Jet;Number of Events',              None,1000., -3., 3.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mAK4',             ';Mass(GeV) of AK4 Jet;Number of Events',      None,1000., 0., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_bdiscAK4',         ';b discriminator of AK4 Jet;Number of Events',None,1000., 0., 1.0,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_ptAK8',            ';p_{T}(GeV) of AK8 Jet;Number of Events',     None,1000., 200., 1500., 0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_etaAK8',           ';y of AK8 Jet;Number of Events',              None,1000., -3., 3.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mAK8',             ';Mass(GeV) of AK8 Jet;Number of Events',      None,1000., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mprunedAK8',       ';Pruned Mass (GeV);Number of Events',         None,1000., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mfilteredAK8',     ';Filtered Mass (GeV);Number of Events',       None,1000., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mtrimmedAK8',      ';Trimmed Mass (GeV);Number of Events',        None,1000., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mSDropAK8',        ';Soft Drop Mass (GeV);Number of Events',      None,1000., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nsjAK8',           ';Number of Subjets;Number of Events',         None,3000., 0., 5.,      0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_tau21AK8',         ';#tau_{21};Number of Events',                 None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_tau32AK8',         ';#tau_{32};Number of Events',                 None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nhfAK8',           ';Neutral hadron fraction;Number of Events',   None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_chfAK8',           ';Charged hadron fraction;Number of Events',   None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nefAK8',           ';Neutral EM fraction;Number of Events',       None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_cefAK8',           ';Charged EM fraction;Number of Events',       None,1.0e4,  0., 1.,     0.6, 0.6, 0.85, 0.85, True],
    ]
else : 
    hists = [
    #    ['h_ptLep',            ';p_{T}(GeV) of Lepton;Number of Events', 500., 0., 1000., 0.6, 0.6, 0.85, 0.85],
    #    ['h_etaLep',           ';y of Lepton;Number of Events',          500., -3., 3.,   0.6, 0.6, 0.85, 0.85],
    #    ['h_met',              ';MET(GeV);Number of Events',             500., 0., 1000., 0.6, 0.6, 0.85, 0.85],
    #    ['h_dRMin',            ';dRMin;Number of Events',                500., 0., 5.,    0.6, 0.6, 0.85, 0.85],
    #    Name                  Title                                                        Rebin Max, Xmin, Xmax   Legend location 
        ['SelectionLoop/h_ptAK4',            ';p_{T}(GeV) of AK4 Jet;Number of Events',     None,  20., 0., 1500.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_etaAK4',           ';y of AK4 Jet;Number of Events',              None,  20., -3., 3.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mAK4',             ';Mass(GeV) of AK4 Jet;Number of Events',      None,  60., 10., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_bdiscAK4',         ';b discriminator of AK4 Jet;Number of Events',None,  20., 0., 1.0,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_ptAK8',            ';p_{T}(GeV) of AK8 Jet;Number of Events',     None,  10., 400., 1500., 0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_etaAK8',           ';y of AK8 Jet;Number of Events',              None,  10., -3., 3.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mAK8',             ';Mass(GeV) of AK8 Jet;Number of Events',      None,  20., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mprunedAK8',       ';Pruned Mass (GeV);Number of Events',         None,  20., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mfilteredAK8',     ';Filtered Mass (GeV);Number of Events',       None,  20., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mtrimmedAK8',      ';Trimmed Mass (GeV);Number of Events',        None,  20., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_mSDropAK8',        ';Soft Drop Mass (GeV);Number of Events',      None,  20., 20., 300.,   0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nsjAK8',           ';Number of Subjets;Number of Events',         None,1000., 0., 5.,      0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_tau21AK8',         ';#tau_{21};Number of Events',                 None, 200.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_tau32AK8',         ';#tau_{32};Number of Events',                 None, 200.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nhfAK8',           ';Neutral hadron fraction;Number of Events',   None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_chfAK8',           ';Charged hadron fraction;Number of Events',   None, 200.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_nefAK8',           ';Neutral EM fraction;Number of Events',       None, 200.,  0., 1.,     0.6, 0.6, 0.85, 0.85, False],
        ['SelectionLoop/h_cefAK8',           ';Charged EM fraction;Number of Events',       None,1000.,  0., 1.,     0.6, 0.6, 0.85, 0.85, True],
    ]

if options.stage != None :
    for ihist in hists :
        if options.lep != None :
            ihist[HNAME_NDX] += options.lep
        ihist[HNAME_NDX] += '_' + options.stage
        print 'Getting histogram : ' + ihist[HNAME_NDX]

FILE_NDX = 0
NAME_NDX = 1
TITLE_NDX = 2
SCALE_NDX = 3
COLOR_NDX = 4
lumi = 626.4
if options.plotW :
    samples = [
        ["NTUPLES/ttjets_b2ganafw_v6_jecv5_ntuple.root",                     'ttbar',  't#bar{t}',          831.76 * lumi / 19665194., ROOT.kRed + 1],
        ["NTUPLES/wjets_b2ganafw_v5_sel1_extracats_jecv5_ntuple.root",       'wjets',  'W + Jets',         20508.9 * lumi / 24089991., ROOT.kGreen + 1 ],
        ["NTUPLES/singletop_v74x_v4.3_tchan_local_sel1_extracats_jecv5_ntuple.root",'st',     'Single Top Quark',  216.99 * lumi / 3999910.,  ROOT.kMagenta + 1 ],
        ["NTUPLES/zjets_b2ganafw_v4_sel1_extracats_jecv5_ntuple.root",              'zjets',  'Z + Jets',          2008.4 * lumi / 19925500., ROOT.kBlue - 4 ], 
        ["NTUPLES/singlemu_v74x_v6_dataset5_jecv5_ntuple.root",                     'mudata', 'Data',              1.0,                       0 ],
        ["NTUPLES/singleel_v74x_v6_dataset5_jecv5_ntuple.root",                     'eldata', 'Data',              1.0,                       0  ],
    ]
else : 
    samples = [
        ["NTUPLES/ttjets_b2ganafw_v6_jecv5_ntuple.root",                     'ttbar',  't#bar{t}',          831.76 * lumi / 19665194., ROOT.kRed + 1],
        ["NTUPLES/wjets_b2ganafw_v5_sel1_extracats_jecv5_ntuple.root",       'wjets',  'W + Jets',         20508.9 * lumi / 24089991., ROOT.kGreen + 1 ],
        ["NTUPLES/singletop_v74x_v4.3_tchan_local_sel1_extracats_jecv5.root",'st',     'Single Top Quark',  216.99 * lumi / 3999910.,  ROOT.kMagenta + 1 ],
        ["NTUPLES/zjets_b2ganafw_v4_sel1_extracats_jecv5.root",              'zjets',  'Z + Jets',          2008.4 * lumi / 19925500., ROOT.kBlue - 4 ], 
        ["NTUPLES/singlemu_v74x_v6_dataset5_jecv5.root",                     'mudata', 'Data',              1.0,                       0 ],
        ["NTUPLES/singleel_v74x_v6_dataset5_jecv5.root",                     'eldata', 'Data',              1.0,                       0  ],
    ]

histsMC = []
histsData = []
hstacks = []
canvs = []
files = []
legs = []

for sample in samples :
    ifile = ROOT.TFile( sample[FILE_NDX] )
    files.append(ifile)

for ihist,shist in enumerate( hists ) :
    hstack = ROOT.THStack( shist[HNAME_NDX], shist[HTITLE_NDX] )
    hdata = None
    leg = ROOT.TLegend( shist[LEGXMIN_NDX],shist[LEGYMIN_NDX],shist[LEGXMAX_NDX],shist[LEGYMAX_NDX])
    leg.SetFillColor(0)
    leg.SetBorderSize(0)
    print 'Getting histogram ' + shist[HNAME_NDX]
    for isample,sample in enumerate(samples) :
        iname = sample[NAME_NDX]
        print '   -- Sample : ' + iname
        
        ihist = files[isample].Get( shist[HNAME_NDX] ).Clone()
        ihist.UseCurrentStyle()
        ihist.SetName( ihist.GetName() + '_' + iname )
        if shist[REBIN_NDX] != None :
            ihist.Rebin( shist[REBIN_NDX] )
        ihist.Scale( sample[SCALE_NDX] )
        if iname in ['ttbar', 'wjets', 'st', 'zjets' ] :
            ihist.SetFillColor( sample[COLOR_NDX] )
            hstack.Add( ihist )
            histsMC.append( ihist )
            leg.AddEntry( ihist, sample[TITLE_NDX], 'f')
            print '    ====> Added to MC'
        elif iname == 'mudata' :
            hdata = ihist.Clone()
            hdata.SetName( ihist.GetName() + '_' + 'data' )
            histsData.append( hdata )
            print '    ====> Initialized data with mu'
        elif iname == 'eldata' :
            hdata.Add ( ihist )
            histsData.append( ihist )
            print '    ====> Added to data with el'
            hdata.SetMarkerStyle(20)
            leg.AddEntry( hdata, 'Data', 'p')
        
    canv = ROOT.TCanvas( 'c'+ shist[HNAME_NDX], 'c'+ shist[HNAME_NDX] )
    hstack.Draw('hist')
    hdata.Draw('e same')

    if options.hmax != None : 
        hstack.SetMaximum( options.hmax  )
    else :
        hstack.SetMaximum( shist[HMAX_NDX] )
    hstack.GetXaxis().SetRangeUser( shist[HXMIN_NDX], shist[HXMAX_NDX] )


    if shist[LOGY_NDX] == True :
        canv.SetLogy()
    
    leg.Draw()

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.905, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi) + " pb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
    tlx.SetTextSize(0.025)
    xInfo = 0.18
    yInfoTop = 0.84
    yInfo2 = yInfoTop-0.042
    yInfo3 = yInfo2-0.042
    yInfo4 = yInfo3-0.042
    yInfo5 = yInfo4-0.042
    yInfo6 = yInfo5-0.042
    tlx.DrawLatex(xInfo, yInfoTop, "#bf{CMS Top Tagger}") # same for AK4 and AK8
    tlx.DrawLatex(xInfo, yInfo2 , "#bf{Madgraph}") # same for AK4 and AK8                   
    tlx.DrawLatex(xInfo, yInfo3, "#bf{AK R= 0.8}") # 0.8 or 0.4 for AK8 and AK4              change with histo
    tlx.DrawLatex(xInfo, yInfo4, "#bf{|#eta| < 2.4 }")  # same for AK4 and AK8
    if options.plotW :
        tlx.DrawLatex(xInfo, yInfo5, "#bf{P_{T} > 200 GeV}")# > 400 for AK8 and > 30 for AK4     change with histo
    else : 
        tlx.DrawLatex(xInfo, yInfo5, "#bf{P_{T} > 400 GeV}")# > 400 for AK8 and > 30 for AK4     change with histo
    tlx.DrawLatex(xInfo, yInfo6, "#bf{25 ns}")  # change with 25 or 50 ns bunchcrossings     change with root files
    
    canv.Draw()

    legs.append(leg)
    canvs.append(canv)
    hstacks.append(hstack)
    canv.Print(shist[HNAME_NDX] + '.png', 'png')
    canv.Print(shist[HNAME_NDX] + '.pdf', 'pdf')    
    
    
