In order to:

plot all 10 AK8 histograms at once-

$root StackedHistoMachineAK8_50ns.cc+

iteractively plot which AK8 histo you would like-

$root StackedHistoMachineAK8_50ns_interactive.cc+ 

iteractively plot a given AK8 histo and compare the 25 and 50ns bunchcrossings in MC-

$root Compare25and50_AK8_interactive.cc+

For all of the above scripts be sure to:

-use input root files which are the output from the latest version of the NtupleReader_fwlite.py
-be sure the event numbers are correct for a given MC sample
-check that the luminosity you normailize to matches that which the data was produced with
