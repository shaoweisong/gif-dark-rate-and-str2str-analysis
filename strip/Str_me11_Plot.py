import argparse, re
import ctypes
import os
from ROOT import gROOT, TCanvas, TLegend, TGraphErrors, TDatime, TH2F, gStyle, kYellow, kCyan, kRed, kGreen, kOrange, kViolet, TMath, gPad
from datetime import datetime
gStyle.SetOptStat(0)

parser = argparse.ArgumentParser(description='For plotting strip to strip resistances')
parser.add_argument('--tenpct', action='store_true', default=False, help="Are you treating 10 percent or 2 percent CF4 as the charge zero point?")
parser.add_argument('--plotname', action='store', default="RStr2Str", type=str, help="name of pdf plot generated")
parser.add_argument('--data', action='store', default="datame11/2pct_stripdatecharges.txt", type=str, help="charge and date data")
args = parser.parse_args()

gROOT.Macro(os.path.expanduser('rootlogon.C'))
def getR( I ):
    if (I == 0):
        return 0.0
    else:
        return 300.0/TMath.Abs(I)
def getdR( I , dI):
    if (I == 0):
        return 0.0
    else:
        return getR(I) * TMath.Abs(dI)/TMath.Abs(I)
class LayerStrip:
    def __init__(self, nmeas, title, PlotColor = 1):
        self.size = nmeas
        self.graph = TGraphErrors(self.size)
        self.title = title
        self.color = PlotColor
        self.measnum = 0
    def meas(self, current, error, charge):
        self.graph.SetPoint(self.measnum, charge, getR(current))
        self.graph.SetPointError(self.measnum, 0, getdR(current, error))
        self.measnum += 1
    def killTrailingPoints(self):
        # delete all points which were not filled (reduces clutter on final plot)
        for i in xrange(self.size+1, 0, -1):
            x = ctypes.c_double(-1.0)
            y = ctypes.c_double(-1.0)
            self.graph.GetPoint(i, x, y)
            #print "x=", x, "y=", y, "i=", i
            if (x.value == 0 and y.value == 0) or (x.value == -1.0 and y.value == -1.0):
            #    print "REMOVED: i - ", i, "x - ", x, "y - ", y
                self.graph.RemovePoint(i)

def readCurrentFile(ifile, LayerStrips, charge, measnum):
    with open(ifile, "r") as f:
        for linenum, line in enumerate(f):
            if linenum < 3: continue
            print("Line is "+line)
            lsplit = line.split()
            match = re.match('layer(\d)_strips(\d\d)_300V',lsplit[0])
            lstitle = match.group(1,2)
            if (not match): continue
            if (lstitle[1] == "12"):
                stripnum = 0
            elif (lstitle[1] == "23"):
                stripnum = 1
            else:
                print "regex error in ", ifile
                quit()
            lsnum = (int(lstitle[0]) -1)* 2 + stripnum
            #print "LayerStrip: ", int(lsnum/2), lstitle[1], "meas. number ", measnum, "current ", lsplit[2], "+/-", lsplit[5], "charge ", charge
            LayerStrips[lsnum].meas(float(lsplit[2]), float(lsplit[5]), charge)
            
        f.close()
def doplot(lslist):
#first doing between str 1 and 2
    Canvas12 = TCanvas("Canvas12", "Strip 1 to Strip 2 Resistance vs Charge", 200, 10, 1400, 1000)
    Canvas12.cd()

    if args.tenpct:
        Limits12 = TH2F("limits12", "Strips 1 and 2;Accumulated Charge (mC/cm);Strip 1 to Strip 2 Resistance (T#Omega)", 1000, 330, 750, 100, 10**(-3), 10**(6))
    else:
        Limits12 = TH2F("limits12", "Strips 1 and 2;Accumulated Charge (mC/cm);Strip 1 to Strip 2 Resistance (T#Omega)", 1000, 0, 500, 100, 10**(-3), 10**(6))
    #Limits12.GetXaxis().SetLabelSize(0.03)
    #Limits12.GetYaxis().SetLabelSize(0.03)
    #Limits12.GetYaxis().SetTitleSize(0.03)
    #Limits12.GetYaxis().SetTitleOffset(1)
    Limits12.Draw();
    
    gPad.SetLogy()
    legend = TLegend(0.38, 0.58, 0.58, 0.88)
    legend.SetNColumns(2)

    for i, layerstrip in enumerate(lslist):
        if ( i % 2 == 0 ):
            layerstrip.graph.SetMarkerColor(layerstrip.color)
            layerstrip.graph.SetLineColor(layerstrip.color)
            layerstrip.graph.SetMarkerStyle(20)
            layerstrip.graph.SetMarkerSize(4)
            layerstrip.graph.Draw("PL SAME")
            legend.AddEntry(layerstrip.graph, layerstrip.title, "pla")
    legend.Draw("SAME")
    Canvas12.SaveAs(args.plotname + "_Str12.pdf")
    #Canvas12.SaveAs(args.plotname + "_Str12.C")
#Now str 2 and 3
    Canvas23 = TCanvas("Canvas23", "Strip 2 to Strip 3 Resistance vs Charge", 200, 10, 1400, 1000)
    Canvas23.cd()

    if args.tenpct:
        Limits23 = TH2F("limits23", "Strips 2 and 3;Accumulated Charge (mC/cm);Strip 2 to Strip 3 Resistance (T#Omega)", 1000, 330, 750, 100, 10**(-3), 10**(6))
    else:
        Limits23 = TH2F("limits23", "Strips 2 and 3;Accumulated Charge (mC/cm);Strip 2 to Strip 3 Resistance (T#Omega)", 1000, 0, 500, 100, 10**(-3), 10**(6))
    #Limits23.GetXaxis().SetLabelSize(0.03)
    #Limits23.GetYaxis().SetLabelSize(0.03)
    #Limits23.GetYaxis().SetTitleSize(0.03)
    #Limits23.GetYaxis().SetTitleOffset(1)
    Limits23.Draw();
    gPad.SetLogy()
    for i, layerstrip in enumerate(lslist):
        if ( i % 2 != 0 ):
            layerstrip.graph.SetMarkerColor(layerstrip.color)
            layerstrip.graph.SetLineColor(layerstrip.color)
            layerstrip.graph.SetMarkerStyle(20)
            layerstrip.graph.SetMarkerSize(4)
            layerstrip.graph.Draw("PL SAME")
    legend.Draw("SAME")
    Canvas23.SaveAs(args.plotname + "_Str23.pdf")
    #Canvas23.SaveAs(args.plotname + "_Str23.C")

colors = [kYellow+1, kCyan, kRed, kGreen-3, kViolet-1, kOrange-1]
#initialize graphs
nummeas = sum(1 for line in open(args.data, "r"))
LayerStrips = []
for i in xrange(12):
    lsi = LayerStrip(nummeas, "L"+str(int(i/2) + 1), colors[int(i/2)])
    LayerStrips.append(lsi)

# importing charge and time data for me11
qtot = []
t_q = []
with open(args.data, "r") as f1:
    for line in f1:
        t_q += ["datame11/"+line.split()[0]+".txt"]
        if args.tenpct:
            qtot += [float(line.split()[1]) + 330]
        else:
            qtot += [float(line.split()[1])]
    f1.close()
# Read the Current measurements into the graphs
for k, t in enumerate(t_q):
    readCurrentFile(t, LayerStrips, qtot[k], k)
# Remove trailing points
for ls in LayerStrips:
#    print "killing trailing points for ", ls.title, "initial number of points: ", ls.graph.GetN()
    ls.killTrailingPoints()
#    print ls.measnum
doplot(LayerStrips)
