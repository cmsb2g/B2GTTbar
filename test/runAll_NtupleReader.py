import subprocess

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--isZprime', action='store_true',
                  default=False,
                  dest='isZprime',
                  help='is it Zprime?')

parser.add_option('--isRSGluon', action='store_true',
                  default=False,
                  dest='isRSGluon',
                  help='is it RSGluon?')

(options, args) = parser.parse_args()
argv = []

path_Zprime = [
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1000_W-10_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1000_W-10_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1250_W-12p5_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1250_W-12p5_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1500_W-15_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1500_W-15_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-2000_W-20_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-2000_W-20_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-2500_W-25_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-2500_W-25_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-3000_W-30_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-3000_W-30_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-3500_W-35_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-3500_W-35_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-4000_W-40_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-4000_W-40_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1000_W-100_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1000_W-100_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1250_W-125_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1250_W-125_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1500_W-150_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1500_W-150_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-2000_W-200_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-2000_W-200_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-2500_W-250_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-2500_W-250_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-3000_W-300_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-3000_W-300_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-3500_W-350_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-3500_W-350_B2Gv8p4_reader603e.root &",
    #"python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-4000_W-400_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-4000_W-400_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-1000_W-300_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-1000_W-300_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-2000_W-600_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-2000_W-600_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-3000_W-900_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-3000_W-900_B2Gv8p4_reader603e.root &",
    "python NtupleReader_fwlite.py --files=FileLists/B2GanaFWv8p4/FileList_ZprimeToTT_M-4000_W-1200_miniv2_B2Gv8p4_25ns.txt  --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isZprime --outname=Trees/tree_ZprimeToTT_M-4000_W-1200_B2Gv8p4_reader603e.root &"
]

path_RSGluon = [
"python NtupleReader_fwlite.py --files=RSGluon_1000.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-1000_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_1250.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-1250_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_1500.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-1500_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_2000.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-2000_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_2500.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-2500_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_3000.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-3000_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_3500.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-3500_B2Gv8p4_reader603e.root &",
"python NtupleReader_fwlite.py --files=RSGluon_4000.txt --selection=2 --writeTree --quickSelect --minAK8Pt=350 --isMC --isRSG --outname=Trees/tree_RSGluonToTT_M-4000_B2Gv8p4_reader603e.root &"
]

if options.isZprime == True:
    path = path_Zprime
if options.isRSGluon == True:
    path = path_RSGluon


for s in path :
    print s
    subprocess.call( [s, ""], shell=True )
    print "Done!"
