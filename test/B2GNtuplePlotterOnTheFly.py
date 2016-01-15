#!it/usr/bin/env python
from optparse import OptionParser
from numpy import *

parser = OptionParser()
parser.add_option('--cut', type='string', action='store',
                  dest='cut',
                  default = "FatJetTau2/FatJetTau1 < 0.6 && LeptonPt > 50. && LeptonPt + SemiLepMETpt > 250. && FatJetMassSoftDrop > 0 && AK4bDisc > 0.6",
                  help='Cut for')
parser.add_option('--filestr', type='string', action='store',
                  dest='filestr',
                  default = "nom",
                  help='Label for plots')
parser.add_option('--variable', type='string', action='store',
                  dest='variable',
                  default = 'FatJetMassSoftDrop',
                  help='Variable to plot')
parser.add_option('--lep', type='string', action='store',
                  dest='lep',
                  default = 'all',
                  help='Lepton to plot')
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
parser.add_option('--trig', type = 'string', action='store',
                  dest='trig',
                  default = None,
                  help="Triggers to plot")
parser.add_option('--type2', action='store_true',
                  default=False,
                  dest='Type2',
                  help='W and B jets NOT merged')
(options, args) = parser.parse_args()
argv = []

import ROOT
import array


#ROOT.gStyle.SetOptStat(000000)

#ROOT.gROOT.Macro("rootlogon.C")
ROOT.gStyle.SetTitleOffset(1.0, "Y")
## ttbarIn = ROOT.TFile( 'NTUPLES/ttjets_b2ganafw_v6_jecv5_updatedsel_ntuple.root' )
## wjetsIn = ROOT.TFile( 'NTUPLES/wjets_b2ganafw_v5_sel1_extracats_jecv5_updatedsel_ntuple.root' )
## zjetsIn = ROOT.TFile( 'NTUPLES/zjets_b2ganafw_v4_sel1_extracats_jecv5_updatedsel_ntuple.root' )
## singletopIn = ROOT.TFile( 'NTUPLES/singletop_v74x_v4.3_tchan_local_sel1_extracats_jecv5_updatedsel_ntuple.root' )
## singlemuIn = ROOT.TFile( 'NTUPLES/singlemu_v74x_v6_dataset5_jecv5_updatedsel_ntuple.root' )
## singleelIn = ROOT.TFile( 'NTUPLES/singleel_v74x_v6_dataset5_jecv5_updatedsel_ntuple.root' )

ttbarIn = ROOT.TFile( 'NTUPLES/ttjets_b2ganafw_v6_jecv5_updatedmcrw_ntuple.root' )
wjetsIn = ROOT.TFile( 'NTUPLES/wjets_b2ganafw_v5_sel1_extracats_jecv5_updatedmcrw_ntuple.root' )
zjetsIn = ROOT.TFile( 'NTUPLES/zjets_b2ganafw_v4_sel1_extracats_jecv5_updatedmcrw_ntuple.root' )
singletopIn = ROOT.TFile( 'NTUPLES/singletop_v74x_v4.3_tchan_local_sel1_extracats_jecv5_updatedmcrw_ntuple.root' )
singlemuIn = ROOT.TFile( 'NTUPLES/singlemu_v74x_v6_dataset6_jecv5_updateddphi_ntuple.root' )
singleelIn = ROOT.TFile( 'NTUPLES/singleel_v74x_v6_dataset5_jecv5_updateddphi_ntuple.root' )

lumi = 1263.88
ttbarIn = ROOT.TFile( './ttjets_b2ganafw_v6_sel1_jec25nsV6_ntuple_Nov9b.root' )
print "tt in"
wjetsIn = ROOT.TFile( './wjets_b2ganafw_v5_sel1_negWeights_jec25nsV6_ntuple_Nov9.root' )
print "w in"
zjetsIn = ROOT.TFile( './zjets_b2ganafw_v4_sel1_negWeights_jec25nsV6_ntuple_Nov9.root' )
print "z in"
singletopIn = ROOT.TFile( './singletop_v74x_v4.3_tchan_local_sel1_negWeights_jec25nsV6_ntuple_Nov9.root' )
print "ST in"
singlemuIn = ROOT.TFile( './singlemu_v74x_v6_dataset6_jec25nsV6_ntuple_Nov9b.root' )
print "single mu data in"
singleelIn = ROOT.TFile( './singleel_v74x_v6_dataset6_jec25nsV6_updateddphi_ntuple_Nov9.root' )
print "single el data"


lumi = 1263.88
print "open tree"
ttbar = ttbarIn.Get("TreeSemiLept")
print "second tree"
wjets = wjetsIn.Get("TreeSemiLept")
zjets = zjetsIn.Get("TreeSemiLept")
singletop = singletopIn.Get("TreeSemiLept")
singlemu = singlemuIn.Get("TreeSemiLept")
singleel = singleelIn.Get("TreeSemiLept")
    
titles = {
    'BoosttypE':['typE',';Boost Type(1 = fully merged W and B jets);Number'],
    'FatJetPt':['AK8Pt','; Jet P_t (GeV);Number'],
    'FatJetEta':['AK8Eta','; Jet \| #eta \| ;Number'],
    'FatJetPhi':['AK8Phi','; Jet #phi ;Number'],
    'FatJetRap':['AK8Rap','; Jet Rapidity ;Number'],
    'FatJetEnergy':['AK8Energy','; Jet Energy ( GeV ) ;Number'],
    'FatJetBDisc':['AK8BDisc','; CSV-v2 B Discriminator ; Number'],
    'FatJetRhoRatio':['ak8rho', ';Jet #rho = (m/p_{T}R)^{2};Number'],
    'FatJetRho':['AK8BDisc','; CSV-v2 B Discriminator ; Number'] ,
    'FatJetMass':['AK8mass',';Jet Mass (GeV);Number'],
    'FatJetMassSoftDrop':['m_softdrop',';Soft Drop (#beta=0) Jet Mass (GeV);Number'],
    'FatJetMassPruned':['m_pruned',';Pruned Jet Mass (GeV);Number'],
    'FatJetMassFiltered':['m_filtered',';Filtered Jet Mass (GeV);Number'],
    'FatJetMassTrimmed':['m_trimmed',';Trimmed Jet Mass (GeV);Number'],
    'FatJetTau21':['tau21',';#tau_{2}/#tau_{1};Number'],
    'FatJetTau32':['tau32',';#tau_{3}/#tau_{2};Number'],
    'FatJetSDnsubjets':['SDnsubjets',';Number of SD subjets ;Number'],
    'FatJetSDbdiscW':['SDsubjetbdiscW',';CSV-v2 B Discriminator of W subjet ;Number'],
    'FatJetSDbdiscB':['SDsubjetbdiscB',';CSV-v2 B Discriminator of B subjet ;Number'],
    'FatJetSDsubjetWpt':['SDsubjetWpt',';P_T of W tag Jet ( GeV ) ;Number'],
    'FatJetSDsubjetBpt':['SDsubjetBpt',';P_T of B tag Jet ( GeV ) ;Number'],
    'FatJetSDsubjetWmass':['Wmass',';Mass of W subjet( GeV ) ;Number'],
    'FatJetSDsubjetBmass':['Bmass',';Mass of B subjet( GeV ) ;Number'],
    'FatJetCMSnsubjets':['CMSnsubjets',';Number of CMS subjets ;Number'],
    'FatJetCMSminMass':['CMSminMass',';Minimum Pairwise Mass ( GeV) ;Number'],
    'FatJetCMSm01':['CMSm01',';Mass of subjets 0 and 1 (GeV) ;Number'],
    'FatJetCMSm02':['CMSm02',';Mass of subjets 0 and 2 (GeV) ;Number'],
    'FatJetCMSm12':['CMSm12',';Mass of subjets 1 and 2 (GeV) ;Number'],
    'BJetbDisc':['BJetbDisc',';CSV-v2 B Discriminator of Jet;Number'],
    'BJetPt':['BJet_Pt','; Jet P_t (GeV);Number'],
    'BJetEta':['BJet_Eta','; Jet \| #eta \| ;Number'],
    'BJetPhi':['BJet_Phi','; Jet #phi ;Number'],
    'BJetMass':['BJetmass',';Jet Mass (GeV);Number'],
    'LeptonType':['leptype',';Lepton type ;Number'],
    'LeptonPt':['leppt',';Lepton p_{T} (GeV);Number'],
    'LeptonEta':['Lepton_Eta','; Lepton \| #eta \| ;Number'],
    'LeptonPhi':['Lepton_Phi','; Lepton  #phi ;Number'],
    'LeptonPt + SemiLepMETpt':['htlep',';H_{T}^{LEP} (GeV);Number'],
    'LeptonPtRel':['LeptonPtRel',';p_{T}^{REL} (lep,jet);Number'],
    'LeptonDRMin':['LeptonDRMin',';#Delta R (lep,jet);Number'],
    'AK4bDisc':['ak4bdisc',';Jet B Discriminator;Number'],
    'NearestAK4JetPt':['ak4pt',';Lepton-side AK4 Jet p_{T} (GeV);Number'],
    'DeltaPhiLepFat':['deltaPhiLepFat',';#Delta #phi (lep, AK8);Number'],
    'NearestAK4JetEta':['ak4eta', ';Jet Rapidity;Number']
    }

variable = options.variable
cut = options.cut
name = titles[variable][0]
title = titles[variable][1]
minval = options.minval
maxval = options.maxval
nbins = options.nbins
histbins = "(" + str(nbins) + ',' + str(minval) + ',' + str(maxval) + ")"


lepstrMC  = 'LeptonType >= 1'
lepstrELE = 'LeptonType == 1'
lepstrMUO = 'LeptonType == 2'

type1str = 'BoosttypE == 1'
type2str = 'BoosttypE == 2'

if options.lep == 'mu' :
    lepstrMC = lepstrMUO
elif options.lep == 'el' :
    lepstrMC = lepstrELE

#weightstr = "SemiLeptWeight * "
weightstr = ""

if options.Type2 :
    ttbar.Draw(variable     + " >> httbar"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type2str + ")", "goff")
    wjets.Draw(variable     + " >> hwjets"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type2str +")", "goff")
    zjets.Draw(variable     + " >> hzjets"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type2str +")", "goff")
    singletop.Draw(variable + " >> hsingletop" + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type2str +")", "goff")
    singlemu.Draw(variable  + " >> hsinglemu"  + histbins, cut + " && " + lepstrMUO + " && " + type2str +" && " + options.trig, "goff")
    singleel.Draw(variable  + " >> hsingleel"  + histbins, cut + " && " + lepstrELE + " && " + type2str +" && " + options.trig, "goff")

else :
    ttbar.Draw(variable     + " >> httbar"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type1str +")", "goff")
    wjets.Draw(variable     + " >> hwjets"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type1str +")", "goff")
    zjets.Draw(variable     + " >> hzjets"     + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type1str +")", "goff")
    singletop.Draw(variable + " >> hsingletop" + histbins, weightstr + "(" + cut + " && " + lepstrMC + " && " + type1str +")", "goff")
    singlemu.Draw(variable  + " >> hsinglemu"  + histbins, cut + " && " + lepstrMUO + " && " + type1str +" && " + options.trig, "goff")
    singleel.Draw(variable  + " >> hsingleel"  + histbins, cut + " && " + lepstrELE + " && " + type1str +" && " + options.trig, "goff")

httbar = ROOT.gDirectory.Get('httbar')
hwjets = ROOT.gDirectory.Get('hwjets')
hzjets = ROOT.gDirectory.Get('hzjets')
hsingletop = ROOT.gDirectory.Get('hsingletop')



if options.lep == 'mu' : 
    hdata = ROOT.gDirectory.Get('hsinglemu').Clone()
    hdata.SetName("hdata")
    fdata = ROOT.gDirectory.Get('hsinglemu').Clone()
    fdata.SetName("fdata")
elif options.lep == 'el' : 
    hdata = ROOT.gDirectory.Get('hsingleel').Clone()
    hdata.SetName("hdata")
    fdata = ROOT.gDirectory.Get('fsingleel').Clone()
    fdata.SetName("fdata")
else :
    hdata = ROOT.gDirectory.Get('hsinglemu').Clone()
    hdata.SetName("hdata")
    hsingleel = ROOT.gDirectory.Get('hsingleel')
    hdata.Add( hsingleel)

    fdata = ROOT.gDirectory.Get('hsinglemu').Clone()
    fdata.SetName("fdata")
    hsingleel = ROOT.gDirectory.Get('hsingleel')
    fdata.Add( hsingleel)



if httbar.Integral() > 0 : 
    httbar.Scale( 831.76 * lumi / 19665194. * httbar.GetEntries()/httbar.Integral())
    # t tbar - https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO used top mass as 172.5, uncertainties on twiki
else :
    print "tt empty"
    httbar.Scale( 0.)
httbar.SetFillColor(ROOT.kGreen + 2)

if hwjets.Integral() > 0 : 
    hwjets.Scale(20508.9 * lumi / 24089991. * hwjets.GetEntries()/hwjets.Integral())
    # inclusive W  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
else :
    print "w empty"
    hwjets.Scale( 0.)
hwjets.SetFillColor(ROOT.kRed)

if hzjets.Integral() > 0 : 
    hzjets.Scale( 2008.4 * lumi / 19925500. * hzjets.GetEntries()/hzjets.Integral())
    # inclusive Z production https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
else :
    print "z empty"
    hzjets.Scale( 0. )
hzjets.SetFillColor(ROOT.kBlue - 4)

if hsingletop.Integral() > 0  : 
    hsingletop.Scale( 216.99 * lumi / 3999910. * hsingletop.GetEntries()/hsingletop.Integral())
    # t channel top at 13 TeV https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
else :
    print "ST empty"
    hsingletop.Scale(0)
hsingletop.SetFillColor(ROOT.kCyan )


hdata.SetMarkerStyle(20)
hdata.SetTitle( title )

mc = ROOT.THStack(variable, title)
mc.Add( hzjets )
mc.Add( hwjets )
mc.Add( hsingletop )
mc.Add( httbar )


#fitting
fitter_data = ROOT.TF1("fitter_data", "gaus", 0, 220 )#50, 120)
fitter_data.SetLineColor(1)
fitter_data.SetLineWidth(2)
fitter_data.SetLineStyle(2)
fdata.Fit(fitter_data,'R' )


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

mchist = hzjets.Clone() 
mchist.Add( hsingletop )
mchist.Add( httbar )

fitter_mc = ROOT.TF1("fitter_mc", "gaus", 0, 220) #50, 120)
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

data_over_mc = mean_data / mean_mc
print 'data_over_mc '+str(data_over_mc)

#drawing


ROOT.gStyle.SetOptFit(1111)
c = ROOT.TCanvas(variable,variable)
hdata.Draw('e')
mc.Draw("hist same")
hdata.Draw('e same')
hdata.Draw("axis same")
fdata.Draw("axis same")
fitter_mc.Draw("same")
fitter_data.Draw("same")

if not options.legleft : 
    leg = ROOT.TLegend( 0.13, 0.6, 0.3, 0.89)
else :
    leg = ROOT.TLegend( 0.13, 0.6, 0.3, 0.89)
leg.SetFillColor(0)
leg.SetBorderSize(0)

leg.AddEntry( hdata, 'Data', 'p')
leg.AddEntry( httbar, 't#bar{t}', 'f')
leg.AddEntry( hwjets, 'W+Jets', 'f')
leg.AddEntry( hzjets, 'Z+Jets', 'f')
leg.AddEntry( hsingletop, 'Single Top Quark', 'f')


max1 = hdata.GetMaximum()
max2 = mchist.GetMaximum() # mc.GetHistogram().GetMaximum()

hdata.SetMaximum( max (max1,max2) * 1.2 )


leg.Draw()

tlx = ROOT.TLatex()
tlx.SetNDC()
tlx.SetTextFont(42)
tlx.SetTextSize(0.057)
tlx.DrawLatex(0.131, 0.946, "CMS Preliminary #sqrt{s}=13 TeV, " + str(lumi) + " pb^{-1}")
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

if options.Type2 :
    tlx.DrawLatex(xInfo, yInfoTop, "#bf{p_{T} > 200 GeV}")
else : 
    tlx.DrawLatex(xInfo, yInfoTop, "#bf{p_{T} > 400 GeV}")
if variable == ('LeptonType' or 'LeptonPt' or 'LeptonEta' or 'LeptonPhi' or 'LeptonPt + SemiLepMETpt' or  'LeptonPtRel' or 'LeptonDRMin'  ) :
    tlx.DrawLatex(xInfo, yInfo2, " ")
if variable == ('BJetbDisc' or'BJetPt' or 'BJetEta' or 'BJetPhi' or 'BJetMass' or 'AK4bDisc' or 'NearestAK4JetPt' or 'NearestAK4JetEta' ) :
    tlx.DrawLatex(xInfo, yInfo2, "#bf{anti-k_{T} R= 0.4}") 
else : 
    tlx.DrawLatex(xInfo, yInfo2, "#bf{anti-k_{T} R= 0.8}") 
if options.lep == 'mu' :
    tlx.DrawLatex(xInfo, yInfo3, "Muon P_T > 55 GeV") 
elif options.lep == 'el' :
    tlx.DrawLatex(xInfo, yInfo3, "Electron P_T > 110 GeV") 
#tlx.DrawLatex(xInfo, yInfo4, "#tau_2 / #tau_1 < 0.6")
#tlx.DrawLatex(xInfo, yInfoTop, "#bf{CMS Top Tagger}") # same for AK4 and AK8
#tlx.DrawLatex(xInfo, yInfo2 , "#bf{Madgraph}") 
#tlx.DrawLatex(xInfo, yInfo4, "#bf{|#eta| < 2.4 }")  # same for AK4 and AK8
#tlx.DrawLatex(xInfo, yInfo6, "#bf{25 ns}")  # change with 25 or 50 ns bunchcrossings     change with root files

c.Update()
c.Draw()

if options.Type2 :
    typE = 'type2'
else :
    typE = 'type1'

c.Print('Nov2/' + name + '_' + options.filestr + typE + '.png', 'png' )
c.Print('Nov2/' + name + '_' + options.filestr + typE +'.pdf', 'pdf' )
