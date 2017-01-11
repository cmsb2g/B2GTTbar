
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ttbar_all_V4.root --outfile ttbar_highmass_outfile.root >& ttbar_highmass_outfile_out.log &

python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_100_V4.root --ignoreTrig --outfile wjets100to200_highmass_outfile.root >& wjets100to200_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_200_V4.root --ignoreTrig --outfile wjets200to400_highmass_outfile.root >& wjets200to400_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_400_V4.root --ignoreTrig --outfile wjets400to600_highmass_outfile.root >& wjets400to600_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_600_V4.root --ignoreTrig --outfile wjets600to800_highmass_outfile.root >& wjets600to800_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_800_V4.root  --ignoreTrig --outfile wjets800to1200_highmass_outfile.root >& wjets800to1000_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_1200_V4.root --ignoreTrig --outfile wjets1200to2500_highmass_outfile.root >& wjets1200to2500_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_2500_V4.root --ignoreTrig --outfile wjets2500toinf_highmass_outfile.root >& wjets2500toinf_highmass_outfile_out.log &


python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016B_all_V4.root --outfile run2016b_highmass_outfile.root
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016C_all_V4.root --outfile run2016c_highmass_outfile.root
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016D_all_V4.root --outfile run2016d_highmass_outfile.root
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016B-23Sep_all_V4.root --outfile run2016b_highmass_outfile.root
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016F-23Sep_all_V4.root
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016G-23Sep_all_V4.root




hadd singlemu_run2016B_0.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0000/ | grep '\.root'`
hadd singlemu_run2016B_1.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0001/ | grep '\.root'`
hadd singlemu_run2016B_2.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0002/ | grep '\.root'`



python RunSemiLepTTbar_HighMass.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016B.root --outfile singlemu_run2016B_highmass_histos.root > & singlemu_run2016B_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016C.root --outfile singlemu_run2016C_highmass_histos.root > & singlemu_run2016C_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016D.root --outfile singlemu_run2016D_highmass_histos.root > & singlemu_run2016D_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016E.root --outfile singlemu_run2016E_highmass_histos.root > & singlemu_run2016E_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/aparker/B2G2016/V4Trees/b2gtree_mudata_Run2016F-23Sep_all_V4.root --outfile singlemu_run2016F_highmass_histos.root >& singlemu_run2016F_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmseos.fnal.gov//store/user/aparker/B2G2016/V4Trees/b2gtree_mudata_Run2016G-23Sep_all_V4.root --outfile singlemu_run2016G_highmass_histos.root >& singlemu_run2016G_highmass_histos.txt &
python RunSemiLepTTbar_HighMass.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016H.root --outfile singlemu_run2016H_highmass_histos.root > & singlemu_run2016H_highmass_histos.txt &

python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht100_V4.root --ignoreTrig --outfile qcd100_highmass_outfile.root >& qcd100_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht200_V4.root --ignoreTrig --outfile qcd200_highmass_outfile.root >& qcd200_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht300_V4.root --ignoreTrig --outfile qcd300_highmass_outfile.root >& qcd300_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht500_V4.root --ignoreTrig --outfile qcd500_highmass_outfile.root >& qcd500_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht700_V4.root --ignoreTrig --outfile qcd700_highmass_outfile.root >& qcd700_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht1000_V4.root --ignoreTrig --outfile qcd1000_highmass_outfile.root >& qcd1000_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht1500_V4.root --ignoreTrig --outfile qcd1500_highmass_outfile.root >& qcd1500_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht2000_V4.root --ignoreTrig --outfile qcd2000_highmass_outfile.root >& qcd2000_highmass_outfile_out.log &

python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_schannel_V4.root --ignoreTrig --outfile singletop_schannel_highmass_outfile.root >& singletop_schannel_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tW-top_V4.root --ignoreTrig --outfile singletop_tW_highmass_outfile.root >& singletop_tW_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tchannel-antitop_V4.root --ignoreTrig --outfile singletop_tchannel_highmass_outfile.root >& singletop_tchannel_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tW-antitop_V4.root --ignoreTrig --outfile singletop_tWantitop_highmass_outfile.root >& singletop_tWantitop_highmass_outfile_out.log &
python RunSemiLepTTbar_HighMass.py --infile /uscms_data/d2/rappocc/analysis/B2G/CMSSW_8_0_22/src/Analysis/B2GTTbar/test/pyttbarfw/b2gtree_MC_ST_tchannel-top_V4.root --ignoreTrig --outfile singletop_tchanneltop_highmass_outfile.root >& singletop_tchanneltop_highmass_outfile_out.log &
