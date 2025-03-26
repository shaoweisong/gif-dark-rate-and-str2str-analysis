'''
Created on 25 Apr 2017

@author: kkuzn

TBD = REWRITE!!!
'''
import cx_Oracle
from datetime import *

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



wireLengthME11 = 20468; # cm                                       
wireLengthME21 = 55428; # cm                                       
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
    ### ME2/1dose = 0.27*(S1[L1+L3+L4+L5]/4)+0.33*(S2[L1+L3]/2)+0.4*(S3[L1]) 
    ME21segment1Flag = [1,0,1,1,1,0]
    ME21segment2Flag = [1,0,1,0,0,0]
    ME21segment3Flag = [1,0,0,0,0,0]
    channelFlag  = [[0,1,1,1,1,0]]
    nLayers      = [4]

    for aDate in dateList:
        ok   = True
        ### <<=== here where the dose is wrong
        tmpCase = (aDate > datetime(2022, 1, 1)) 
        if(chamber==2) :  
            if (tmpCase) : 
                channelFlag = [ME21segment1Flag, ME21segment2Flag, ME21segment3Flag]
                nLayers     = [4, 2, 1]
            else : 
                channelFlag = [[0,1,1,1,1,0], [0,1,1,1,1,0], [0,1,1,1,1,0]]
                nLayers     = [4, 4, 4]

        if(debug) : print(aDate.strftime('%d.%m.%Y'), tmpCase, "\t",)
        for S in range(1,maxSec+1):            
            dose = 0
            for L in range(1,7):
                cmd  = """select value from (select value, version_id from accumulated_currents where chamber=%d and layer=%d and sector=%d and
                time_stop=TO_DATE('%s','DD.MM.yyyy') order by version_id desc) where rownum=1"""%(chamber, L, S, aDate.strftime('%d.%m.%Y'))
                #print cmd
                curs.execute(cmd)
                rows  = curs.fetchall() 
                if(len(rows)>0):
                    if(debug):
                        norm = float(WL)
                        if(chamber==2):
                            norm = float(WL)*segmW[S-1]
                        print("%6.2f"%(rows[0][0]//1000.0/4.),)
                    dose+=rows[0][0]*channelFlag[S-1][L-1]
                    if(debug) : print(S, L, channelFlag[S-1][L-1], nLayers[S-1])
                else:
                    ok = False
                    if(debug):
                        print("%6s"%("None"),)
            if(ok):
                dose=dose/float(WL)/1000.0/nLayers[S-1]
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
