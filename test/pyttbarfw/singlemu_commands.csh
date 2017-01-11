
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ttbar_all_V4.root --outfile ttbar_outfile.root >& ttbar_outfile_out.log &

python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_100_V4.root --outfile wjets100to200_outfile.root >& wjets100to200_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_200_V4.root --outfile wjets200to400_outfile.root >& wjets200to400_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_400_V4.root --outfile wjets400to600_outfile.root >& wjets400to600_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_600_V4.root --outfile wjets600to800_outfile.root >& wjets600to800_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_800_V4.root  --outfile wjets800to1200_outfile.root >& wjets800to1000_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_1200_V4.root --outfile wjets1200to2500_outfile.root >& wjets1200to2500_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_wjets_2500_V4.root --outfile wjets2500toinf_outfile.root >& wjets2500toinf_outfile_out.log &


python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016B_all_V4.root --outfile run2016b_outfile.root
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016C_all_V4.root --outfile run2016c_outfile.root
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_data_Run2016D_all_V4.root --outfile run2016d_outfile.root
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016B-23Sep_all_V4.root --outfile run2016b_outfile.root
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016F-23Sep_all_V4.root
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_mudata_Run2016G-23Sep_all_V4.root




hadd singlemu_run2016B_0.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0000/ | grep '\.root'`
hadd singlemu_run2016B_1.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0001/ | grep '\.root'`
hadd singlemu_run2016B_2.root `xrdfsls -u /store/user/jdolen/B2G2016/SingleMuon/crab_b2gtreeV4_SingleMuon_Run2016B-23Sep2016-v3_JSONnov14/161116_084007/0002/ | grep '\.root'`



python RunSemiLepTTbar.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016B.root --outfile singlemu_run2016B_histos.root > & singlemu_run2016B_histos.txt &
python RunSemiLepTTbar.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016C.root --outfile singlemu_run2016C_histos.root > & singlemu_run2016C_histos.txt &
python RunSemiLepTTbar.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016D.root --outfile singlemu_run2016D_histos.root > & singlemu_run2016D_histos.txt &
python RunSemiLepTTbar.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016E.root --outfile singlemu_run2016E_histos.root > & singlemu_run2016E_histos.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/aparker/B2G2016/V4Trees/b2gtree_mudata_Run2016F-23Sep_all_V4.root --outfile singlemu_run2016F_histos.root >& singlemu_run2016F_histos.txt &
python RunSemiLepTTbar.py --infile root://cmseos.fnal.gov//store/user/aparker/B2G2016/V4Trees/b2gtree_mudata_Run2016G-23Sep_all_V4.root --outfile singlemu_run2016G_histos.root >& singlemu_run2016G_histos.txt &
python RunSemiLepTTbar.py --infile root://cmsxrootd.fnal.gov//store/user/rappocc/B2GAnaFWFiles16Dec2016/singlemu_run2016H.root --outfile singlemu_run2016H_histos.root > & singlemu_run2016H_histos.txt &

python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht100_V4.root --outfile qcd100_outfile.root >& qcd100_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht200_V4.root --outfile qcd200_outfile.root >& qcd200_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht300_V4.root --outfile qcd300_outfile.root >& qcd300_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht500_V4.root --outfile qcd500_outfile.root >& qcd500_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht700_V4.root --outfile qcd700_outfile.root >& qcd700_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht1000_V4.root --outfile qcd1000_outfile.root >& qcd1000_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht1500_V4.root --outfile qcd1500_outfile.root >& qcd1500_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_QCD_Ht2000_V4.root --outfile qcd2000_outfile.root >& qcd2000_outfile_out.log &

python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_schannel_V4.root --outfile singletop_schannel_outfile.root >& singletop_schannel_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tW-top_V4.root --outfile singletop_tW_outfile.root >& singletop_tW_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tchannel-antitop_V4.root --outfile singletop_tchannel_outfile.root >& singletop_tchannel_outfile_out.log &
python RunSemiLepTTbar.py --infile root://131.225.207.127:1094//store/user/asparker/B2G2016/V4Trees/b2gtree_MC_ST_tW-antitop_V4.root --outfile singletop_tWantitop_outfile.root >& singletop_tWantitop_outfile_out.log &
python RunSemiLepTTbar.py --infile /uscms_data/d2/rappocc/analysis/B2G/CMSSW_8_0_22/src/Analysis/B2GTTbar/test/pyttbarfw/b2gtree_MC_ST_tchannel-top_V4.root --outfile singletop_tchanneltop_outfile.root >& singletop_tchanneltop_outfile_out.log &
