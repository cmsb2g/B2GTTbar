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
(options, args) = parser.parse_args()
argv = []

import ROOT
import array


ROOT.gStyle.SetOptStat(000000)
#ROOT.gROOT.Macro("rootlogon.C")
ROOT.gStyle.SetTitleOffset(1.0, "Y")
ttbarIn = ROOT.TFile( 'NTUPLES/ttjets_b2ganafw_v6_jecv5_ntuple.root' )
wjetsIn = ROOT.TFile( 'NTUPLES/wjets_b2ganafw_v5_sel1_extracats_jecv5_ntuple.root' )
singlemuIn = ROOT.TFile( 'NTUPLES/singlemu_v74x_v6_dataset5_jecv5_ntuple.root' )

lumi = 626.4

ttbar = ttbarIn.Get("TreeSemiLept")
wjets = wjetsIn.Get("TreeSemiLept")
singlemu = singlemuIn.Get("TreeSemiLept")


ttbar.Draw("FatJetMassSoftDrop >> httbar(25,0,250)", "FatJetTau2/FatJetTau1 < 0.6 && FatJetPt > 200 && FatJetMassSoftDrop > 0 && AK4bDisc > 0.6 && LeptonType == 2", "goff")
wjets.Draw("FatJetMassSoftDrop >> hwjets(25,0,250)", "FatJetTau2/FatJetTau1 < 0.6 && FatJetPt > 200 && FatJetMassSoftDrop > 0 && AK4bDisc > 0.6 && LeptonType == 2", "goff")
singlemu.Draw("FatJetMassSoftDrop >> hsinglemu(25,0,250)", "FatJetTau2/FatJetTau1 < 0.6 && FatJetPt > 200 && FatJetMassSoftDrop > 0 && AK4bDisc > 0.6 && LeptonType == 2", "goff")

httbar = ROOT.gDirectory.Get('httbar')
hwjets = ROOT.gDirectory.Get('hwjets')
hsinglemu = ROOT.gDirectory.Get('hsinglemu')


httbar.Scale( 831.76 * lumi / 19665194. )
httbar.SetFillColor(ROOT.kRed)
hwjets.Scale(20508.9 * lumi / 24089991. )
hwjets.SetFillColor(ROOT.kGreen + 1)

hsinglemu.SetMarkerStyle(20)


mc = ROOT.THStack('FatJetMassSoftDrop', ';Soft Drop Mass (GeV);')
mc.Add( httbar )
mc.Add( hwjets )

hsinglemu.Draw('e')
mc.Draw("hist same")
hsinglemu.Draw('e same')
