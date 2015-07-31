In order to:

(NOTE: 50ns scripts include data as well as MC)

plot all 10 AK8 histograms at once-

$root StackedHistoMachineAK8_50ns.cc+

or

$root StackedHistoMachineAK8_25ns.cc+ 

plot all AK4 and lepton histograms at once-

$root StackedHistoMachineAK4_50ns.cc+

or

$root StackedHistoMachineAK4_25ns.cc+



To iteractively plot:

whichever AK8 histo you would like-

$root StackedHistoMachineAK8_50ns_interactive.cc+

a given AK8 histo and compare the 25 and 50ns bunchcrossings in MC-

$root Compare25and50_AK8_interactive.cc+

a given AK4 or lepton Pt histo

$root StackedHistoMachineAK4_25ns.cc+



****************************************
For all of the above scripts be sure to:
****************************************
-use input root files which are the output from the latest version of the NtupleReader_fwlite.py 

-check the event numbers are correct for a given MC sample

-check that the luminosity you normailize to matches that which the data was produced with
