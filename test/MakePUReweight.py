import ROOT


fData = ROOT.TFile("July30n-MuData-50ns-sel1.root")
fMC = ROOT.TFile("July30n-TTJets-50ns-sel1.root")

hData = fData.Get("h_NPVert")
hMC = fMC.Get("h_NPVert")

hData.Sumw2()
hMC.Sumw2()

hData.Divide( hMC )

hData.Draw("e")

fOut = ROOT.TFile("pileup_reweight.root", "RECREATE")
hData.Write()
fOut.Close()
