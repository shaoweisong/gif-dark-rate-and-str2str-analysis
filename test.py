import sys

from string import *
import os
import cx_Oracle

from datetime import timedelta, datetime, tzinfo
import time
# import ROOT
import ROOT

import getpass
date=["12_OCT_2022","05_APR_2023","12_May_2023","09_AUG_2023","16_AUG_2023","21_Feb_2024","27_Mar_2024"]
value1=[94416.1333333,3256.9,828.533333333,500.933333333,715.666666667,721.366666667]
value2=[69124.5333333,845.633333333,0,687,697.866666667,689.3,661.766666667]
value3=[342985.166667,1934.53333333,687.1,721.066666667,697.133333333,679.766666667]
value4=[284224.333333,9392.83333333,653.6,744.966666667,730.0,700.966666667]
value5=[369482.433333,9184.16666667,865.7,636.233333333,702.866666667,688.2]
value6=[294774.833333,740.533333333,754.733333333,706.633333333,697.0,675.1]
value7=[532093.166667,9702.3,2404.96666667,730.266666667,692.43333333,676.2]
valuelist=[value1,value2,value3,value4,value5,value6,value7]
Voltages_replacestring = [2700, 2800, 2850, 2900, 2950, 3000]
for j in range(0,7):
# set HVO as 2850, HV1 as 2920 for ME11
    root_file = ROOT.TFile("./me11_corrroot/"+date[j]+".root", "RECREATE")
    tree = ROOT.TTree("ALCT", "ALCT tree")
    hist = ROOT.TH1F("darkrate_vs_HV", "Dark Rate vs HV", len(Voltages_replacestring), 0, len(Voltages_replacestring))
    valuelist=valuelist[j]
    for i, value in enumerate(valuelist):
        hist.SetBinContent(i + 1, value)
    tree.Fill()
    root_file.Write()
    root_file.Close()