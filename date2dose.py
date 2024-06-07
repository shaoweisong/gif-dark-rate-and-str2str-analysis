#! /usr/bin/env python

import sys

from string import *
import os
import cx_Oracle

from datetime import timedelta, datetime, tzinfo
import time

import getpass

# ---------------------------------------------------------------------------

class connectDBdose:
    def __init__(self):
        magic='HV_pvss_emu1'
        connect= 'cms_emu_hvwrite_r/' + magic + '@cmsr'
        #print "connecting to dose db..."
        self.orcl = cx_Oracle.connect(connect)
        self.curs = self.orcl.cursor()
        #print "                    ...done"
        
    def __del__(self):
        #print "\n\nclosing connection to dose db..."
        self.orcl.close()
        #print "                                ...done"        
        
    def cursor(self):
        return self.curs
# ---------------------------------------------------------------------------
wireLengthME11 = 20468; # cm                                       
wireLengthME21 = 55428; # cm 

#!!!TBD!!! - please update charge at the beginning of the current run (5%CF4)?
charge0ME11    = 1000; # mC/cm 
charge0ME21    = 330; # mC/cm

#!!!TBD!!! - to be set as 1 for all layers as soon as chargeDB is updated

                                       
def createMapOfDoses(chamber, dateList, debug=False):
    aveDoses = {}

    orac = connectDBdose()
    curs = orac.cursor()
    maxSec = 1
    WL     = wireLengthME11
    if(chamber==2):
        maxSec = 3
        WL     = wireLengthME21
    
    vals = [0,0,0]
    segmW =  [.27,.33,.40]; # areas: 0.45, 0.54, 0.67 m2; sum = 1.66

    today = datetime.now()
    today = today.replace(hour=12, minute=0, second=0, microsecond=0)
    for aDate in dateList:
        ok   = True
        if(debug): print(aDate.strftime('%d.%m.%Y'), "\t",)

        # a fix for the current day (no dose in DB yet)
        aDateX = aDate
        if (aDate==today): aDateX = aDate - timedelta(hours=24)

        for S in range(1,maxSec+1):            
            dose = 0
            for L in range(2,6):
                cmd  = """select value from (select value, version_id from accumulated_currents where chamber=%d and layer=%d and sector=%d and
                time_stop=TO_DATE('%s','DD.MM.yyyy') order by version_id desc) where rownum=1"""%(chamber, L, S, aDateX.strftime('%d.%m.%Y'))
                #print cmd
                curs.execute(cmd)
                rows  = curs.fetchall()        
                if(len(rows)>0):
                    if(debug):
                        norm = float(WL)
                        if(chamber==2):
                            norm = float(WL)*segmW[S-1]
                        print("%6.2f"%(rows[0][0]//1000.0/4.),)
                    dose+=rows[0][0]
                else:
                    ok = False
                    if(debug):
                        print("%6s"%("None"),)
            if(ok):
                dose=float(dose)/float(WL)/float(1000.0)/float(4.0)
                if(chamber==2):
                    dose = dose/segmW[S-1]
            else:
                dose=-1            
            if(debug):
                print(" => %6.2f"%dose)
            vals[S-1] = dose
            
        aveDoses[aDate]=[vals[0], vals[1], vals[2]]
        
    del orac
    return aveDoses
# ---------------------------------------------------------------------------
def isfloat(text):
    try:
        int(text)
        return True
    except (ValueError, TypeError) as e:
        pass

    try:
        float(text)
        return True    
    except (ValueError, TypeError) as e:
        pass

    return False

# ---------------------------------------------------------------------------
if __name__ == "__main__":
    if(len(sys.argv)<2) : 
        print("usage: %s date <segment>\n\t where date dd.mm.yy and segment is 0 for ME1/1 or HVsegment# form ME2/1 (1,2 or 3)\n")
        sys.exit(0)
    
    segment = -1
    if(len(sys.argv)>2) : 
        if isfloat(sys.argv[2]) : segment = int(sys.argv[2])
    
    theDate = datetime.today()
    try:
        theDate = datetime.strptime(sys.argv[1], '%d.%m.%y')
    except:
        print("can't convert date")
        sys.exit(0)
    
    outstr = ""
    #print segment
    if  (segment<0):
        aveDosesME11 = createMapOfDoses(1,[theDate], True)
        outstr      += "%4.0f" % aveDosesME11[theDate][0]
        aveDosesME21 = createMapOfDoses(2,[theDate])
        outstr      +="".join("%4.0f" % aveDosesME21[theDate][ii] for ii in range(3))
    elif (segment>0):
        aveDosesME21 = createMapOfDoses(2,[theDate])
        outstr      +="".join("%4.0f" % aveDosesME21[theDate][segment-1])
    else :
        aveDosesME11 = createMapOfDoses(1,[theDate])
        outstr      += "%4.0f" % aveDosesME11[theDate][0]
    
    print(outstr)

 
