import ROOT


fData = ROOT.TFile("NTUPLES/singlemu_v74x_v6_dataset5_jecv5_updateddphi_ntuple.root")
fMC = ROOT.TFile("NTUPLES/ttjets_b2ganafw_v6_jecv5_updateddphi_ntuple.root")

hData = fData.Get("h_NPVert")
hMC = fMC.Get("h_NPVert")

hData.Sumw2()
hMC.Sumw2()

hData.Scale( 1.0 / hData.Integral() )
hMC.Scale( 1.0 / hMC.Integral() )

hData.Divide( hMC )

hData.Draw("e")

fOut = ROOT.TFile("pileup_reweight.root", "RECREATE")
hData.Write()
fOut.Close()
