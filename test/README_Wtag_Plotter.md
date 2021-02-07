# Wtag_Plotter

From your CMSSW release area : 

To use the "PredictedDistribution" class : 

git clone https://github.com/rappoccio/PredictedDistribution.git Analysis/PredictedDistribution

git clone -b ashley https://github.com/cmsb2g/B2GTTbar.git Analysis/B2GTTbar

To create TTrees from B2GAnaFW ntuples from FNAL :

```
python NtupleReader_fwlite.py --files filestest.txt --outname test_data_outfile.root --selection 1 --applyFilters --applyTriggers --writeTree --minAK8Pt 0. --mAK8GroomedMinCut 0.0 --tau32Cut 1.1 --hemisphereDPhi 0.0 --metMin 0. --htLepMin 0.0  --minMassCut 0. --bDiscMin 0. >& data_testNtuplreader.txt &

```

To run semi-leptonic selection outlined in AN-16-215 (using ttrees created above) :

```

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type ttjets >& ttjets_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees --type data >& data_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type st1 >& st1_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type st2 >& st2_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type st3 >& st3_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type st4 >& st4_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets1 >& wjets1_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets2 >& wjets2_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets3 >& wjets3_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets4 >& wjets4_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets5 >& wjets5_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets6 >& wjets6_Selector_ Last80xTrees_tau21Is_0p4.txt &

python Wtag_Selector.py --filestr TightWP_tau21Is_0p4 --tau21Cut 0.4   --treeLocation  Last80xTrees  --isMC --type wjets7 >& wjets7_Selector_ Last80xTrees_tau21Is_0p4.txt &
```

To plot output from the above script (stored in /output80xselector/) for the muon data selection:

```
python Wtag_Plotter.py --filestr TightWP_tau21Is_0p4 --infile TightWP_tau21Is_0p4  --Mudata --allMC --treeLocation Last80xTrees --pre

python Wtag_Plotter.py --filestr TightWP_tau21Is_0p4 --infile TightWP_tau21Is_0p4  --Mudata --allMC --treeLocation Last80xTrees
```
