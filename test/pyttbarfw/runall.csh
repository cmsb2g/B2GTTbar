
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_V2_99percentFinished_All.root --outfile ttbar_outfile.root >& ttbar_outfile.txt &

python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016B-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016b_outfile.root >& run2016b_outfile.txt &
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016C-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016c_outfile.root >& run2016c_outfile.txt &
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016D-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016d_outfile.root >& run2016d_outfile.txt &
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016E-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016e_outfile.root >& run2016e_outfile.txt &
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016F-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016f_outfile.root >& run2016f_outfile.txt &
python RunSemiLepTTbar.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016G-PromptReco-v1_JSONsept9_V2_99percentFinished_All.root --outfile run2016g_outfile.root >& run2016g_outfile.txt &



python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-100To200.root    --outfile wjets100to200_outfile.root     --ignoreTrig >&wjets100to200_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-200To400.root    --outfile wjets200to400_outfile.root --ignoreTrig >&wjets200to400_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-400To600.root    --outfile wjets400to600_outfile.root --ignoreTrig >&wjets400to600_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-600To800.root    --outfile wjets600to800_outfile.root --ignoreTrig >&wjets600to800_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-800To1200.root   --outfile wjets800to1200_outfile.root --ignoreTrig >&wjets800to1200_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-1200To2500.root  --outfile wjets1200to2500_outfile.root --ignoreTrig >&wjets1200to2500_outfile.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-2500ToInf.root   --outfile wjets2500toinf_outfile.root --ignoreTrig >&wjets2500toinf_outfile.txt &



python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring16MiniAODv2-PUSpring16_reHLT_V2_99percentFinished_All.root --outfile ttbar_highmass_outfile.root >& ttbar_highmass_outfile.txt &

python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016B-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016b_highmass_outfile.root >& run2016b_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016C-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016c_highmass_outfile.root >& run2016c_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016D-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016d_highmass_outfile.root >& run2016d_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016E-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016e_highmass_outfile.root >& run2016e_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016F-PromptReco-v2_JSONsept9_V2_99percentFinished_All.root --outfile run2016f_highmass_outfile.root >& run2016f_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile /uscmst1b_scratch/lpc1/lpcphys/jdolen/B2G2016/V2/b2gtree_SingleMuon_Run2016G-PromptReco-v1_JSONsept9_V2_99percentFinished_All.root --outfile run2016g_highmass_outfile.root >& run2016g_highmass_outfile.txt &



python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-100To200.root    --outfile wjets100to200_highmass_outfile.root     --ignoreTrig >&wjets100to200_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-200To400.root    --outfile wjets200to400_highmass_outfile.root --ignoreTrig >&wjets200to400_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-400To600.root    --outfile wjets400to600_highmass_outfile.root --ignoreTrig >&wjets400to600_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-600To800.root    --outfile wjets600to800_highmass_outfile.root --ignoreTrig >&wjets600to800_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-800To1200.root   --outfile wjets800to1200_highmass_outfile.root --ignoreTrig >&wjets800to1200_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-1200To2500.root  --outfile wjets1200to2500_highmass_outfile.root --ignoreTrig >&wjets1200to2500_highmass_outfile.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/rappocc/B2G2016/WJetsToLNu/WJetsToLNu_HT-2500ToInf.root   --outfile wjets2500toinf_highmass_outfile.root --ignoreTrig >&wjets2500toinf_highmass_outfile.txt &


