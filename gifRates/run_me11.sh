./NewTest11.sh csc_00000001_EmuRUI01_Test_11_000_250326_101827_UTC 14594 me11data 100000

python TMB_AG.py 1

python TMBRatePlotter_1.py --tenpctzero --charges me11_txt/charges_me11_all.txt --Dat0V me11_txt/TMB_0V_me11_all.txt --DatHV0 me11_txt/TMB_HV0_me11_all.txt --DatT11 me11_txt/anode_me11_all.txt --plotname ME11


python AnodeRatePlotter_PerWG.py --tmb0v me11_txt/TMB_0V_me11_all.txt --tmbhv0 me11_txt/TMB_HV0_me11_all.txt --data me11_txt/anode_me11_all.txt --chambtype 1 --name AnodeSingleRate_me11