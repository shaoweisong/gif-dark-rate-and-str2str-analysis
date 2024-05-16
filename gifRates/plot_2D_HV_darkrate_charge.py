# python plot_2D_HV_darkrate_charge.py --tenpctzero --tmb0v me11_txt/TMB_0V_me11_2pct.txt --tmbhv0 me11_txt/TMB_HV0_me11_2pct.txt --data me11_txt/anode_me11_2pct.txt --chambtype 1 --name hv_alct_me11 --hvfile me11root/anode_me11_2pct.txt
# python plot_2D_HV_darkrate_charge.py --tenpctzero --tmb0v me11_txt/TMB_0V_me11_2pct.txt --tmbhv0 me11_txt/TMB_HV0_me11_2pct.txt --data me11_txt/anode_me11_2pct.txt --chambtype 1 --name hv_alct_me11 --hvfile me11root/anode_me11_2pct.txt --full
# python plot_2D_HV_darkrate_charge.py  --tmb0v me21_txt/TMB_0V_me21_2pct.txt --tmbhv0 me21_txt/TMB_HV0_me21_2pct.txt --data me21_txt/anode_me21_5pct.txt --chambtype 2 --name hv_alct_me21 --hvfile me21root/anode_me21_5pct.txt
# python plot_2D_HV_darkrate_charge.py --tmb0v me21_txt/TMB_0V_me21_2pct.txt --tmbhv0 me21_txt/TMB_HV0_me21_2pct.txt --data me21_txt/anode_me21_5pct.txt --chambtype 2 --name hv_alct_me21 --hvfile me21root/anode_me21_5pct.txt --full
import argparse, array
from ROOT import gROOT, TCanvas, TLegend, TGraphErrors, TDatime, TH2F, gStyle, kYellow, kCyan, kRed, kGreen, kOrange, kViolet, TMath, gPad, TFile, TPaletteAxis
#from datetime import datetime
gStyle.SetOptStat(0)
gStyle.SetPalette(1)


parser = argparse.ArgumentParser(description='For plotting strip to strip resistances')

parser.add_argument('--tenpctzero', action='store_true', default=False, help="use the start of 10 percent irradiation as the zero point for charge\n DEFAULT: False")
parser.add_argument('--verbose', action='store_true', default=False, help="Print statements\n DEFAULT: False")
parser.add_argument('--tmbnorm', action='store_true', default=False, help="Normalize by TMB dump Total_Hit_clusters_minus_muons (NOT RECOMMENDED)\n DEFAULT: False")
parser.add_argument('--anodetotalnorm', action='store_true', default=False, help="Normalize by corrected total anode rate from test 11\n DEFAULT: False")
parser.add_argument('--tmb0v', action='store', type=str, default="TMB_0V_me11_2pct.txt", help="where to pull 0V tmb dump data from (only used if doing --tmbnorm)\n DEFAULT: TMB_0V_me11_2pct.txt")
parser.add_argument('--tmbhv0', action='store', type=str, default="TMB_HV0_me11_2pct.txt", help="where to pull HV0 tmb dump data from (only used if doing --tmbnorm)\n DEFAULT: TMB_HV0_me11_2pct.txt")
parser.add_argument('--data', action='store', default="anode_me11_2pct.txt", type=str, help="where to look for data on Total Chamber Rate\n DEFAULT: anode_me11_2pct.txt")
parser.add_argument('--chambtype', action='store', default=1, type=int, help="ME1/1 (Put 1) or ME2/1 (Put 2)?\n DEFAULT: 1")
parser.add_argument('--name', action='store', default="AnodeHitDensity2pct_ME11", type=str, help="name of output file (without the .pdf)\n DEFAULT: AnodeHitDensity2pct_ME11")
parser.add_argument('--compare2old', action='store_true', default=False, help="comparing to older treatment of the data - splits up plots into a few different ranges of charge\n DEFAULT: False")
parser.add_argument('--hvfile',action='store', default="anode_me11_2pct.txt", type=str, help="where to look for data on Total Chamber Rate\n DEFAULT: anode_me11_2pct.txt")
parser.add_argument('--full', action='store_true', default=False, help="plot the full range of charges\n DEFAULT: False")
args = parser.parse_args()

if args.tenpctzero:
    plus300 = True
else:
    plus300 = False
if args.compare2old:
    plus300 = True

# importing data
charges = array.array('d')
rootfiles = []
hvfiles = []
# Due to some interesting behavior which appears uniquely for bad points with test 11 normalization, it was decided to use Test 11 Total_Hit_clusters_minus_muons
if not args.tmbnorm and not args.anodetotalnorm:
    Test11_Total_Hit_clusters_minus_muons = True
else:
    Test11_Total_Hit_clusters_minus_muons = False
if Test11_Total_Hit_clusters_minus_muons:
    Test11_Total_Hit_clusters_minus_muonsrates = []
with open(args.data, "r") as f1:
    for lnum, line in enumerate(f1):
        if lnum == 0: continue
        rootfiles += [line.split()[0]]
        charges.append(float(line.split()[1]))
        if Test11_Total_Hit_clusters_minus_muons:
            tmpfile = TFile(line.split()[0], "read")
            Test11_Total_Hit_clusters_minus_muonsrates += [float(tmpfile.Get("ALCT/hNofAhit[2]").GetBinContent(3)/30.0)]
            tmpfile.Close()
            if args.verbose:
                print "Test11 Total_Hit_clusters_minus_muons:", Test11_Total_Hit_clusters_minus_muonsrates[-1]
    f1.close()
print plus300
if plus300: 
    for i in xrange(len(charges)):
        charges[i] += 330
    zeropoint = '330_mCcm_'
else:
    zeropoint = '0_mCcm_'
# creating the range for split histograms
# I commented out functionality which will plot a third histogram in a range complementary to the one used for comparison plot - though in practice I haven't needed it.

class Layer:
    def __init__(self, nmeas, layernum, charges, chambtype, name=''):
        if chambtype == 1:
            self.nwg = 14
            self.voltage = ['0', '2100', '2200', '2300', '2400', '2500', '2600', '2700', '2800','HV0' ,'2900','HV1_ageing', '2950', '3000']
        elif chambtype == 2:
            self.nwg = 16
            self.voltage = ['0',' 2700',' 2800',' 2900',' 3000',' 3100',' 3200',' 3300',' 3400',' 3500',' 3600','HV0',' 3700', 'HV1_ageing', '3800', '3900']
        else:
            print "only ME11 (type = 1) and ME21 (type = 2) Are supported. Number of wire groups set to 0 in protest."
            self.nwg = 0
        self.meas = nmeas
        domain = charges
        domain.append(domain[-1] +5)
        self.num = int(layernum+1)
        self.hist = TH2F(name, name, nmeas, domain, self.nwg, 0, self.nwg)
        self.hist.GetXaxis().SetTitle("Accumulated charge [mC/cm]")
        self.hist.GetYaxis().SetTitle("Voltage")
        self.hist.GetXaxis().SetLabelSize(0.03)
        self.hist.GetYaxis().SetLabelSize(0.03)
        self.hist.GetYaxis().SetTitleSize(0.03)
        self.hist.GetYaxis().SetTitleOffset(1)
        for i in range(1, self.nwg+1):  # Y axis bins start from 1
            self.hist.GetYaxis().SetBinLabel(i, self.voltage[i-1])
    def measure(self, measnum, ratehist):
        for wg in xrange(self.nwg+1):
            #+1 is because the histogram's bins start counting at 1
            self.hist.SetBinContent(measnum+1, wg+1, ratehist.GetBinContent(wg+1))
            # self.hist.SetBinContent(measnum+1, wg+1, 2000)
def doplots(layerlist, plotname):
    Canvas = TCanvas("Canvas", "Anode ALCT*CLCT Rate", 200, 10, 1400, 1000)
    for layer in layerlist:
        if args.full:
            layer.hist.SetMaximum(4000000)
            layer.hist.SetMinimum(0.001)
        else:
            layer.hist.SetMaximum(200000)
            # layer.hist.SetMaximum(20000)
            layer.hist.SetMinimum(0.001)
        layer.hist.SetTitle("Anode ALCT*CLCT Dark Rate")
        layer.hist.Draw("colz")
        gPad.Update()
        layer.hist.GetZaxis().SetLabelSize(0.025)
    if not args.name:
        Canvas.SaveAs(plotname +"ME"+str(args.chambtype)+"1_Anode_Rate_vs_WG_vs_charge.pdf")
    else:
        Canvas.SaveAs(args.name+"_330+.pdf")
    Canvas.Close()

#initialize histos
nummeas = len(charges)
if Test11_Total_Hit_clusters_minus_muons:
    LayersTotal_Hit_clusters_minus_muons = []
if args.anodetotalnorm:
    LayersTotal_Hit_clusters = []
if args.tmbnorm:
    LayersTMB = []
for i in xrange(1):
    if Test11_Total_Hit_clusters_minus_muons:
        liTotal_Hit_clusters_minus_muons = Layer(nummeas, i, charges, args.chambtype, "Test11_Total_Hit_clusters_minus_muons_Normalized")
        LayersTotal_Hit_clusters_minus_muons.append(liTotal_Hit_clusters_minus_muons)
    if args.anodetotalnorm:
        liTotal_Hit_clusters = Layer(nummeas, i, charges, args.chambtype)
        LayersTotal_Hit_clusters.append(liTotal_Hit_clusters)
    if args.tmbnorm:
        liTMB = Layer(nummeas, i, charges, args.chambtype, "TMBDumpNormalized")
        LayersTMB.append(liTMB)
# filling histograms for each layer for each measurement
with open(args.hvfile, "r") as f1:
    for lnum, line in enumerate(f1):
        if lnum == 0: continue
        hvfiles += [line.split()[0]]
if Test11_Total_Hit_clusters_minus_muons:
    for imeas, anoderate in enumerate(Test11_Total_Hit_clusters_minus_muonsrates):
        measfile = TFile(hvfiles[imeas], "read")
        for iL, layer in enumerate(LayersTotal_Hit_clusters_minus_muons):
            ratehist = measfile.Get("darkrate_vs_HV")
            layer.measure(imeas, ratehist)
        measfile.Close()
    doplots(LayersTotal_Hit_clusters_minus_muons, zeropoint + "Test11_Total_Hit_clusters_minus_muons_Normalized_")
