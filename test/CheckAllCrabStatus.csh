#!/bin/tcsh
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc530
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh

foreach dir (crab_b2g*)
    echo CHECK STATUS OF CRAB DIRECTORY:  $dir
    crab status -d  $dir
    echo "-----------------------------------------------------------------------------------------"
    echo
end
