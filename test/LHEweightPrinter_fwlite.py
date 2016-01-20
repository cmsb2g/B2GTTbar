#! /usr/bin/env python

#@ CONFIGURATION                                                                                                                                                                                                                              
from optparse import OptionParser
parser = OptionParser()

parser.add_option('--files', type='string', action='store',
                  dest='files',
                  help='Input files')

parser.add_option('--maxruns', type='int', action='store',
                  default=-1,
                  dest='maxruns',
                  help='Number of runs to run. -1 is all runs')

(options, args) = parser.parse_args()
argv = []


#@ FWLITE STUFF

import ROOT
import sys
from DataFormats.FWLite import Runs, Handle
ROOT.gROOT.Macro("rootlogon.C")
from leptonic_nu_z_component import solve_nu_tmass, solve_nu
import copy
from array import array
from math import *
ROOT.gSystem.Load("libAnalysisPredictedDistribution")

#@ Labels and Handles
h_lheRun = Handle("LHERunInfoProduct")
l_lheRun = ("externalLHEProducer", "")

    
#@ RUN LOOP

filelist = file( options.files )
filesraw = filelist.readlines()

files = []
#files.append('root://xrootd.unl.edu//store/mc/RunIISpring15DR74/ZprimeToTT_M-3000_W-900_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/AODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/02C3658C-8B08-E511-9624-AC853D9DACE3.root')
Nruns = 0
for ifile in filesraw : #{ Loop over text file and find root files linked
    if len( ifile ) > 2 :
        s = ifile.rstrip()
        files.append( s )
        print 'Added ' + s
        #} End loop over txt file

# loop over files
for ifile in files : #{ Loop over root files
    print 'Processing file ' + ifile
    runs = Runs (ifile)
    if options.maxruns > 0 and Nruns > options.maxruns :
        break

    # Make sure the handles we want are in the files so we can
    # avoid leaking memory
    readFilters = True

    
    #NrunsInFile = runs.size()
    #if NrunsInFile <= 0 : 
        #continue
    # loop over runs in this file
    for run in runs: #{ Loop over runs in root files

        #Event weight errors
        #gotLHE = event.getByLabel( l_lhe, h_lhe )
        #lhe = h_lhe.product()
        #weight_id = lhe.weights()[0].wgt                                                                                                                                                                                                
            #print '***********' + str(weight_id)                                                                                                                                                                                             
            ## if not gotGenerator or not gotLHE :                                                                                                                                                                                            
            ##     continue                   
        
        gotLHErun = run.getByLabel( l_lheRun, h_lheRun )
        lheRun = h_lheRun.product() 

        

        for i_lheRun in lheRun:
            #print lheRun.headers()[i_lheRun].tag
            print i_lheRun

