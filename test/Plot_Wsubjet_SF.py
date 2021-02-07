#!it/usr/bin/env python
from optparse import OptionParser
from numpy import *

parser = OptionParser()
parser.add_option('--infile', type='string', action='store',
                  dest='infile',
                  default = "",
                  help='Input file')
parser.add_option('--filestr', type='string', action='store',
                  dest='filestr',
                  default = "nom",
                  help='Label for plots')
parser.add_option('--minval', type='float', action='store',
                  dest='minval',
                  default = 0.,
                  help='Minval for the plot')
parser.add_option('--maxval', type='float', action='store',
                  dest='maxval',
                  default = 250.,
                  help='Maxval for the plot')
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
(options, args) = parser.parse_args()
argv = []

import ROOT
import array
import math

ROOT.gStyle.SetTitleOffset(1.0, "Y")


fout= ROOT.TFile('Wmass_meanrat' + options.infile + '.root', "RECREATE")
if options.pre :
    fout= ROOT.TFile('Wmass_meanrat_pre' + options.infile + '.root', "RECREATE")


ptBs =  array.array('d', [200., 300., 400., 500., 800.] )
nptBs = len(ptBs) - 1

    
#hmean = ROOT.TH1F("hmean", " ;p_{T} of SD subjet 0 (GeV); SF (data/MC)", 4, 0.0, 800.0)
hpeak = ROOT.TH1F("hpeak", " ;p_{T} of SD subjet 0 (GeV); JMS ",  nptBs, ptBs)  ##frac{Mean Mass_{data}}{Mean Mass_{MC}}
hwidth = ROOT.TH1F("hwidth", " ;p_{T} of SD subjet 0 (GeV); JMR ", nptBs, ptBs) ##frac{#sigma_{data}}{#sigma_{MC}}

filein = ROOT.TFile.Open('Wmass_pt_binned' + options.infile + '.root')
lumi = 2136.0

httbar = filein.Get("h_mWsubjet_ttjets")
ttbar_pt = filein.Get("h_ptWsubjet_ttjets")

httbar2 = filein.Get("h_mWjet_ttjets")
ttbar_pt2 = filein.Get("h_ptWjet_ttjets")

# Mass of SD subjet 0 of the AK8 jet in semi-leptonic Z' selection, binned in pt. 0-200 GeV, 200-400 GeV, 400-600 Gev, 600-Infinity GeV
httbar_b1 = filein.Get("h_mWsubjet_b1_ttjets")
httbar_b2 = filein.Get("h_mWsubjet_b2_ttjets")
httbar_b3 = filein.Get("h_mWsubjet_b3_ttjets")
httbar_b4 = filein.Get("h_mWsubjet_b4_ttjets")

httbar_b1p = filein.Get("h_mWsubjet_b1_ttjetsp")
httbar_b2p = filein.Get("h_mWsubjet_b2_ttjetsp")
httbar_b3p = filein.Get("h_mWsubjet_b3_ttjetsp")
httbar_b4p = filein.Get("h_mWsubjet_b4_ttjetsp")

singlemu_m = filein.Get("h_mWsubjet_MuData")
singlemu_pt = filein.Get("h_ptWsubjet_MuData")

singlemu_m_b1 = filein.Get("h_mWsubjet_b1_MuData")
singlemu_m_b2 = filein.Get("h_mWsubjet_b2_MuData")
singlemu_m_b3 = filein.Get("h_mWsubjet_b3_MuData")
singlemu_m_b4 = filein.Get("h_mWsubjet_b4_MuData")

singlemu_mp = filein.Get("h_mWsubjet_MuDatap")
singlemu_ptp = filein.Get("h_ptWsubjet_MuDatap")

singlemu_m_b1p = filein.Get("h_mWsubjet_b1_MuDatap")
singlemu_m_b2p = filein.Get("h_mWsubjet_b2_MuDatap")
singlemu_m_b3p = filein.Get("h_mWsubjet_b3_MuDatap")
singlemu_m_b4p = filein.Get("h_mWsubjet_b4_MuDatap")

singleel_m = filein.Get("h_mWsubjet_EleData")
singleel_pt = filein.Get("h_ptWsubjet_EleData")

singleel_m_b1 = filein.Get("h_mWsubjet_b1_EleData")
singleel_m_b2 = filein.Get("h_mWsubjet_b2_EleData")
singleel_m_b3 = filein.Get("h_mWsubjet_b3_EleData")
singleel_m_b4 = filein.Get("h_mWsubjet_b4_EleData")

singleel_mp = filein.Get("h_mWsubjet_EleDatap")
singleel_ptp = filein.Get("h_ptWsubjet_EleDatap")

singleel_m_b1p = filein.Get("h_mWsubjet_b1_EleDatap")
singleel_m_b2p = filein.Get("h_mWsubjet_b2_EleDatap")
singleel_m_b3p = filein.Get("h_mWsubjet_b3_EleDatap")
singleel_m_b4p = filein.Get("h_mWsubjet_b4_EleDatap")

hdata = filein.Get("h_mWsubjet_Data")
muel_pt = filein.Get("h_ptWsubjet_Data")

hdata_b1 = filein.Get("h_mWsubjet_b1_Data")
hdata_b2 = filein.Get("h_mWsubjet_b2_Data")
hdata_b3 = filein.Get("h_mWsubjet_b3_Data")
hdata_b4 = filein.Get("h_mWsubjet_b4_Data")

hdatap = filein.Get("h_mWsubjet_Datap")
muel_ptp = filein.Get("h_ptWsubjet_Datap")

hdata_b1p = filein.Get("h_mWsubjet_b1_Datap")
hdata_b2p = filein.Get("h_mWsubjet_b2_Datap")
hdata_b3p = filein.Get("h_mWsubjet_b3_Datap")
hdata_b4p = filein.Get("h_mWsubjet_b4_Datap")

hpts = filein.Get("h_ptWsubjet_Data_Type1")
hpts2 = filein.Get("h_ptWsubjet_Data_Type2")

hptsMC = filein.Get("h_ptWsubjet_MC_Type1")
hpts2MC = filein.Get("h_ptWsubjet_MC_Type2")


hscale = filein.Get("hSF")

'''
titles = {
    'FatJetSDsubjetWpt':['SDsubjetWpt',';P_{T} of SD subjet 0 ( GeV ) ;Number of Events'],
    'FatJetSDsubjetWmass':['Wmass',';Mass_{SD subjet 0 }( GeV ) ;Number of Events'],
    }

variable = 'FatJetSDsubjetWmass'
cut = options.cut
name = titles[variable][0]
title = titles[variable][1]
'''

minval = options.minval
maxval = options.maxval
nbins = options.nbins
histbins = "(" + str(nbins) + ',' + str(minval) + ',' + str(maxval) + ")"




for ipt, pt in enumerate(ptBs) :
    print "pt variable is : " + str(pt)
    print "ipt variable is : " + str(ipt)
    if (ipt == 0) :
        httbarT = httbar_b1.Clone()
        hdataT = hdata_b1.Clone()
        httbarTp = httbar_b1p.Clone()
        hdataTp = hdata_b1p.Clone()
    if (ipt == 1) :
        httbarT = httbar_b2.Clone()
        hdataT = hdata_b2.Clone()
        httbarTp = httbar_b2p.Clone()
        hdataTp = hdata_b2p.Clone()
    if (ipt == 2) :
        httbarT = httbar_b3.Clone()
        hdataT = hdata_b3.Clone()
        httbarTp = httbar_b3p.Clone()
        hdataTp = hdata_b3p.Clone()
    if (ipt == 3) :
        httbarT = httbar_b4.Clone()
        hdataT = hdata_b4.Clone()
        httbarTp = httbar_b4p.Clone()
        hdataTp = hdata_b4p.Clone()

    hdataT.Rebin(5)
    httbarT.Rebin(5)
    hdataTp.Rebin(5)
    httbarTp.Rebin(5)

    if httbarT.Integral() > 0 : 
        httbarT.Scale( hdataT.GetEntries()/ httbarT.Integral())
        # t tbar - https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki
    else :
        print "tt empty"
        httbarT.Scale( 0.)
    httbarT.SetFillColor(ROOT.kGreen + 2)

    if httbarTp.Integral() > 0 : 
        httbarTp.Scale( hdataTp.GetEntries()/ httbarTp.Integral())
        # t tbar - https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki
    else :
        print "tt empty"
        httbarTp.Scale( 0.)
    httbarTp.SetFillColor(ROOT.kGreen + 2)

    hdataT.SetMarkerStyle(20)
    hdataTp.SetMarkerStyle(20)
    #hdataT_b1p.SetTitle( title )

    if options.pre :
        httbarT = httbarTp.Clone()
        hdataT = hdataTp.Clone()

    mc = ROOT.THStack('WmaSS',';Mass_{SD subjet_{0} }( GeV ) ;Number of Events')
    #mc.Add( hzjets )
    #mc.Add( hwjets )
    #mc.Add( hsingletop )
    mc.Add( httbarT)


    #fitting
    fitter_data = ROOT.TF1("fitter_data", "gaus", 50, 120) #40, 130 )#50, 120)
    if options.pre :
        fitter_data = ROOT.TF1("fitter_data", "gaus", 50, 120)# 40, 130 )
    fitter_data.SetLineColor(1)
    fitter_data.SetLineWidth(2)
    fitter_data.SetLineStyle(2)
    hdataT.Fit(fitter_data,'R' )


    amp_data    = fitter_data.GetParameter(0);
    eamp_data   = fitter_data.GetParError(0); 
    mean_data   = fitter_data.GetParameter(1);
    emean_data  = fitter_data.GetParError(1); 
    width_data  = fitter_data.GetParameter(2);
    ewidth_data = fitter_data.GetParError(2); 

    print 'amp_data    '+str(amp_data    ) 
    print 'eamp_data   '+str(eamp_data   ) 
    print 'mean_data   '+str(mean_data   ) 
    print 'emean_data  '+str(emean_data  ) 
    print 'width_data  '+str(width_data  ) 
    print 'ewidth_data '+str(ewidth_data ) 

    mchist = httbarT.Clone()
     
    #mchist.Add( hsingletop )
    #mchist.Add( httbarT )

    fitter_mc = ROOT.TF1("fitter_mc", "gaus",  50, 120)#40, 130) #50, 120)
    if options.pre :
        fitter_mc = ROOT.TF1("fitter_mc", "gaus", 50, 120)# 40, 130)
    fitter_mc.SetLineColor(4)
    fitter_mc.SetLineWidth(2)
    fitter_mc.SetLineStyle(4)
    mchist.Fit("fitter_mc",'R' )
    amp_mc    = fitter_mc.GetParameter(0);
    eamp_mc   = fitter_mc.GetParError(0); 
    mean_mc   = fitter_mc.GetParameter(1);
    emean_mc  = fitter_mc.GetParError(1); 
    width_mc  = fitter_mc.GetParameter(2);
    ewidth_mc = fitter_mc.GetParError(2); 

    print 'amp_mc    '+str(amp_mc    ) 
    print 'eamp_mc   '+str(eamp_mc   ) 
    print 'mean_mc   '+str(mean_mc   ) 
    print 'emean_mc  '+str(emean_mc  ) 
    print 'width_mc  '+str(width_mc  ) 
    print 'ewidth_mc '+str(ewidth_mc ) 

    meanrat = 1.0
    meanrat_uncert = meanrat
    jms = 1.0
    jms_uncert = jms
    if mean_mc > 0. :
        meanrat = mean_data / mean_mc
        meanrat_uncert = meanrat * math.sqrt( (emean_data/mean_data)**2 + (emean_mc/mean_mc)**2 )
    if width_mc > 0. :
        jms = width_data / width_mc
        jms_uncert = jms * math.sqrt( (ewidth_data/width_data)**2 + (ewidth_mc/width_mc)**2 )

    print 'data_over_mc peak :  '+str(meanrat)
    print '...........................................................'

    ibin = hpeak.GetXaxis().FindBin(pt)
    hpeak.SetBinContent(ibin, meanrat ) 
    hwidth.SetBinContent(ibin, jms )
    hpeak.SetBinError(ibin, meanrat_uncert)   
    hwidth.SetBinError(ibin, jms_uncert)
    #drawing


    ROOT.gStyle.SetOptFit(1111)
    c = ROOT.TCanvas('WmaSS','WmaSS')
    hdataT.Draw('e')
    mc.Draw("hist same")
    hdataT.Draw('e same')
    hdataT.Draw("axis same")
    fitter_mc.Draw("same")
    fitter_data.Draw("same")

    if not options.legleft : 
        leg = ROOT.TLegend( 0.48, 0.68, 0.599, 0.875)
    else :
        leg = ROOT.TLegend( 0.48, 0.68, 0.599, 0.875)
    leg.SetFillColor(0)
    leg.SetBorderSize(0)

    leg.AddEntry( hdataT, 'Data', 'p')
    leg.AddEntry( httbarT, 't#bar{t}', 'f')
    '''
    leg.AddEntry( hwjets, 'W+Jets', 'f')
    leg.AddEntry( hzjets, 'Z+Jets', 'f')
    leg.AddEntry( hsingletop, 'Single Top Quark', 'f')

    '''
    max1 = hdataT.GetMaximum()
    max2 = mchist.GetMaximum() # mc.GetHistogram().GetMaximum()

    hdataT.SetMaximum( max (max1,max2) * 1.2 )


    leg.Draw()

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.946, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi) + " pb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
    tlx.SetTextSize(0.027)
    xInfo = 0.49
    yInfoTop = 0.475
    yInfo2 = yInfoTop-0.042
    yInfo3 = yInfo2-0.042
    yInfo4 = yInfo3-0.042
    yInfo5 = yInfo4-0.042
    yInfo6 = yInfo5-0.042
    yInfo7 = yInfo6-0.042
    yInfo8 = yInfo7-0.042
    yInfo9 = yInfo8-0.042
    #if not options.pre :
    #    tlx.DrawLatex(xInfo, yInfo4+0.13,"#bf{40 < m_{SD subjet 0} (GeV) < 120}")

    c.Update()
    c.Draw()
    sele = options.filestr
    if options.pre :
        sele = 'preWTag'
    c.Print('WsubjetSF/wMass_Bin'+ str(ipt) + '_' + sele + '.png', 'png' )
    c.Print('WsubjetSF/wMass_Bin'+ str(ipt) + '_' + sele + '.pdf', 'pdf' )
#    c.Print('WsubjetSF/wMass_Bin'+ str(ipt) + '_' + sele + '.pdf', 'pdf' )

if not options.pre :
     #ROOT.gStyle.SetOptFit(1111)
    ROOT.gStyle.SetOptStat(000000)

    d = ROOT.TCanvas('sf','sf')
    hscale.Draw('P')

    hscale.SetMaximum(2.0)
    hscale.SetMinimum(0.0)

    hscale.SetMarkerStyle(20)
    #hscale.GetYaxis().SetRange(0.8,1.0)

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.93, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi/1000.0) + " fb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
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

    #tlx.DrawLatex(xInfo, yInfo4+0.4,"#bf{65 < m_{SD subjet 0} (GeV) < 130}")

    #tlx.DrawLatex(xInfo, yInfo2, "#bf{anti-k_{T} R= 0.8, p_{T} > 400 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo3, "#bf{110 < m_{SD AK8 Jet}(GeV) < 250 , #tau_3 / #tau_2 < 0.6}")
    #tlx.DrawLatex(xInfo, yInfo4,"#bf{m_{SD subjet 0} > 50, p_{T of SD subjet 0} > 200 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo5, "#bf{AK4 CSVv2 B disc. > 0.7}") 
    #tlx.DrawLatex(xInfo, yInfo6, "#bf{2D cut}") 
    #tlx.DrawLatex(xInfo, yInfo7, "#bf{e :p_{T} > 110 and p_{T of MET} > 120 (GeV)}") 
    #tlx.DrawLatex(xInfo, yInfo8, "#bf{#mu :p_{T} > 55 and (p_{T} + P_{T of MET} ) > 150 (GeV)}")
    d.Update()
    d.Draw()
    d.Print('WsubjetSF/ScaleFactor_Wsubjet_AllBins_' + options.filestr + '.png', 'png' )
    d.Print('WsubjetSF/ScaleFactor_Wsubjet_AllBins_' + options.filestr + '.pdf', 'pdf' )

    ee = ROOT.TCanvas('wid','wid')
    hwidth.Draw('e')

    hwidth.SetMarkerStyle(20)
    #hwidth.GetYaxis().SetRange(0.8,1.0)
    hwidth.SetMaximum(2.0)
    hwidth.SetMinimum(0.0)

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.91, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi/1000.0) + " fb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
    tlx.SetTextSize(0.029)
    xInfo = 0.51
    yInfoTop = 0.475
    yInfo2 = yInfoTop-0.042
    yInfo3 = yInfo2-0.042
    yInfo4 = yInfo3-0.042
    yInfo5 = yInfo4-0.042
    yInfo6 = yInfo5-0.042
    yInfo7 = yInfo6-0.042
    yInfo8 = yInfo7-0.042

    #tlx.DrawLatex(xInfo, yInfo4+0.4,"#bf{65 < m_{SD subjet 0} (GeV) < 130}")

    #tlx.DrawLatex(xInfo, yInfo2, "#bf{anti-k_{T} R= 0.8, p_{T} > 400 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo3, "#bf{110 < m_{SD AK8 Jet}(GeV) < 250 , #tau_3 / #tau_2 < 0.6}")
    #tlx.DrawLatex(xInfo, yInfo4,"#bf{m_{SD subjet 0} > 50, p_{T of SD subjet 0} > 200 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo5, "#bf{AK4 CSVv2 B disc. > 0.7}") 
    #tlx.DrawLatex(xInfo, yInfo6, "#bf{2D cut}") 
    #tlx.DrawLatex(xInfo, yInfo7, "#bf{e :p_{T} > 110 and p_{T of MET} > 120 (GeV)}") 
    #tlx.DrawLatex(xInfo, yInfo8, "#bf{#mu :p_{T} > 55 and (p_{T} + P_{T of MET} ) > 150 (GeV)}")

    ee.Update()
    ee.Draw()
    ee.Print('WsubjetSF/JMR_Wsubjet_AllBins' + '_' + options.filestr + '.png', 'png' )
    ee.Print('WsubjetSF/JMR_Wsubjet_AllBins' + '_' + options.filestr + '.pdf', 'pdf' )


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
    hpts2.SetMaximum(7000.)
    hpts2.SetMinimum(0.0001)
    hpts.SetMaximum(7000.)
    hpts.SetMinimum(0.0001)
    hpts2MC.SetMaximum(7000.)
    hpts2MC.SetMinimum(0.0001)
    hptsMC.SetMaximum(7000.)
    hptsMC.SetMinimum(0.0001)
    #hpts.SetMarkerStyle(20)
    #hpts.SetMaximum(3)
    #hpts.SetMinimum(0)

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.91, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi/1000.0) + " fb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
    tlx.SetTextSize(0.029)
    xInfo = 0.75
    yInfoTop = 0.475
    yInfo2 = yInfoTop-0.042
    yInfo3 = yInfo2-0.042
    yInfo4 = yInfo3-0.042
    yInfo5 = yInfo4-0.042
    yInfo6 = yInfo5-0.042
    yInfo7 = yInfo6-0.042
    yInfo8 = yInfo7-0.042
    
    legy = ROOT.TLegend( 0.68, 0.68, 0.799, 0.875)
    legy.SetFillColor(0)
    legy.SetBorderSize(0)

    legy.AddEntry( hpts, 'Data: Type 1', 'l')
    legy.AddEntry( hpts2, 'Data: Type 2', 'l')
    legy.AddEntry( hptsMC, 'MC: Type 1', 'l')
    legy.AddEntry( hpts2MC, 'MC: Type 2', 'l')
    legy.Draw()
#    tlx.DrawLatex(xInfo, yInfo4+0.4,"#bf{65 < m_{SD subjet 0} (GeV) < 130}")

    #tlx.DrawLatex(xInfo, yInfo2, "#bf{Type 1 : 1 anti-k_{T} R= 0.8 Jet, p_{T} > 400 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo3, "#bf{Type 2 : 2 anti-k_{T} R= 0.8 Jets, p_{T} > 200 (GeV)}")
#    tlx.DrawLatex(xInfo, yInfo3, "#bf{110 < m_{SD AK8 Jet}(GeV) < 250 , #tau_3 / #tau_2 < 0.6}")
#    tlx.DrawLatex(xInfo, yInfo4,"#bf{m_{SD subjet 0} > 50, p_{T of SD subjet 0} > 200 (GeV)}")
#    tlx.DrawLatex(xInfo, yInfo5, "#bf{AK4 CSVv2 B disc. > 0.7}") 
#    tlx.DrawLatex(xInfo, yInfo6, "#bf{2D cut}") 
#    tlx.DrawLatex(xInfo, yInfo7, "#bf{e :p_{T} > 110 and p_{T of MET} > 120 (GeV)}") 
#    tlx.DrawLatex(xInfo, yInfo8, "#bf{#mu :p_{T} > 55 and (p_{T} + P_{T of MET} ) > 150 (GeV)}")

    ff.Update()
    ff.Draw()
    ff.Print('WsubjetSF/Pt_type1and2_' + options.filestr + '.png', 'png' )
    ff.Print('WsubjetSF/Pt_type1and2_' + options.filestr + '.pdf', 'pdf' )


    gg = ROOT.TCanvas('peak','peak')
    hpeak.Draw('e')

    hpeak.SetMarkerStyle(20)
    #hpeak.GetYaxis().SetRange(0.8,1.0)
    hpeak.SetMaximum(2.0)
    hpeak.SetMinimum(0.0)

    tlx = ROOT.TLatex()
    tlx.SetNDC()
    tlx.SetTextFont(42)
    tlx.SetTextSize(0.057)
    tlx.DrawLatex(0.131, 0.91, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi/1000.0) + " fb^{-1}")
    # tlx.DrawLatex(0.77, 0.86, "#bf{CMS}")
    # tlx.DrawLatex(0.72, 0.83, "#it{very preliminary}")
    tlx.SetTextSize(0.029)
    xInfo = 0.51
    yInfoTop = 0.475
    yInfo2 = yInfoTop-0.042
    yInfo3 = yInfo2-0.042
    yInfo4 = yInfo3-0.042
    yInfo5 = yInfo4-0.042
    yInfo6 = yInfo5-0.042
    yInfo7 = yInfo6-0.042
    yInfo8 = yInfo7-0.042

    #tlx.DrawLatex(xInfo, yInfo4+0.4,"#bf{65 < m_{SD subjet 0} (GeV) < 130}")

    #tlx.DrawLatex(xInfo, yInfo2, "#bf{anti-k_{T} R= 0.8, p_{T} > 400 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo3, "#bf{110 < m_{SD AK8 Jet}(GeV) < 250 , #tau_3 / #tau_2 < 0.6}")
    #tlx.DrawLatex(xInfo, yInfo4,"#bf{m_{SD subjet 0} > 50, p_{T of SD subjet 0} > 200 (GeV)}")
    #tlx.DrawLatex(xInfo, yInfo5, "#bf{AK4 CSVv2 B disc. > 0.7}") 
    #tlx.DrawLatex(xInfo, yInfo6, "#bf{2D cut}") 
    #tlx.DrawLatex(xInfo, yInfo7, "#bf{e :p_{T} > 110 and p_{T of MET} > 120 (GeV)}") 
    #tlx.DrawLatex(xInfo, yInfo8, "#bf{#mu :p_{T} > 55 and (p_{T} + P_{T of MET} ) > 150 (GeV)}")

    gg.Update()
    gg.Draw()
    gg.Print('WsubjetSF/JMS_Wsubjet_AllBins' + '_' + options.filestr + '.png', 'png' )
    gg.Print('WsubjetSF/JMS_Wsubjet_AllBins' + '_' + options.filestr + '.pdf', 'pdf' )



fout.cd()
fout.Write()
fout.Close()
