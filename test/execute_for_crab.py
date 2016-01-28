import sys
import PSet
files = []
outfile = file( 'filesToProcess.txt', 'w')
for ifile in PSet.process.source.fileNames :    
    outfile.write('root://xrootd.unl.edu/' + ifile + '\n' )


outfile.close()

sys.argv.append('--files')
sys.argv.append('filesToProcess.txt')

print sys.argv

#from NtupleReader_fwlite import *

#NtupleReader_fwlite(sys.argv)
