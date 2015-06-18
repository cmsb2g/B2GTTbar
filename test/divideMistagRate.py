#!/usr/bin/env python

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--infile', type='string', action='store',
                  dest='infile',
                  help='Input file')

parser.add_option('--outfile', type='string', action='store',
                  dest='outfile',
                  help='Output file, without the .root')

parser.add_option('--num', type='string', action='store',
                  dest='num',
                  default = 'h2_rho_tau21cut',
                  help='Numerator histogram')

parser.add_option('--den', type='string', action='store',
                  dest='den',
                  default = 'h2_rho_all',
                  help='Denominator histogram')

(options, args) = parser.parse_args()
argv = []


import ROOT
ROOT.gROOT.Macro("rootlogon.C")

fin = ROOT.TFile(options.infile)
num = fin.Get(options.num)
den = fin.Get(options.den)

num.SetMarkerStyle(21)
den.SetMarkerStyle(25)

num.Sumw2()
den.Sumw2()


prettyone = ROOT.THStack(num.GetName() +'_pretty', num.GetTitle())
prettyone.Add( num )
prettyone.Add( den )

rate = num.Clone()
rate.Divide( rate, den, 1., 1., "b")
rate.SetName('rate_' + options.outfile)
rate.SetMarkerStyle(20)

c1 = ROOT.TCanvas('c1', 'c1')
prettyone.Draw('nostack')
c1.SetLogx()
c1.SetLogy()
c1.Print( 'hist_' + options.outfile + '.png')
c1.Print( 'hist_' + options.outfile + '.pdf')

c2 = ROOT.TCanvas('c2', 'c2')
rate.Draw('e')
c2.SetLogx()
c2.Print( 'rate_' + options.outfile + '.png')
c2.Print( 'rate_' + options.outfile + '.pdf')
rate.SetMinimum(0.0)
rate.SetMaximum(1.2)

fout = ROOT.TFile(options.outfile + '.root', 'RECREATE')
fout.cd()
rate.Write()
fout.Close()
