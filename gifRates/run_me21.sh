#use HV0,test11 DAQ and run number

./NewTest11ME21.sh csc_00000001_EmuRUI01_Test_11_000_250219_163941_UTC  14505 me21data 100000

python TMB_AG.py 2

python TMBRatePlotter.py --charges me21_txt/charges_me21_5pct.txt --Dat0V me21_txt/TMB_0V_me21_5pct.txt --DatHV0 me21_txt/TMB_HV0_me21_5pct.txt --DatT11 me21_txt/anode_me21_5pct.txt --plotname ME21_TMB
python AnodeRatePlotter_PerWG.py --tmb0v me21_txt/TMB_0V_me21_5pct.txt --tmbhv0 me21_txt/TMB_HV0_me21_5pct.txt --data me21_txt/anode_me21_5pct.txt --chambtype 2 --name AnodeSingleRate_me21

