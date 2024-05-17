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
value1=[7213,7156,5009,8285,32569,944161]
value2=[6617,6893,6978,687,0,691245]
value3=[6797,6971,7210,6871,19345,3429851]
value4=[7009,7300,7449,6536,93928,2842243]
value5=[6882.,7028,6362,8657,91841,3694824]
value6=[6751.,6970,7066,7547,7405,2947748]
value7=[6762,6924,7302,24049,97023,5320931]
valuelist=[value1,value2,value3,value4,value5,value6,value7]
Voltages_replacestring = [2700, 2800, 2850, 2900, 2950, 3000]
for j in range(0,7):
# set HVO as 2850, HV1 as 2920 for ME11
    root_file = ROOT.TFile("./me11_corrroot/"+date[j]+".root", "RECREATE")
    tree = ROOT.TTree("ALCT", "ALCT tree")
    hist = ROOT.TH1F("darkrate_vs_HV", "Dark Rate vs HV", len(Voltages_replacestring), 0, len(Voltages_replacestring))
    value_=valuelist[j]
    for i in range(0, len(Voltages_replacestring)):
        hist.SetBinContent(i + 1, value_[i])
    tree.Fill()
    root_file.Write()
    root_file.Close()