cp ../me11data/A11267.root .
cp ../me11data/A10861.root .
cp ../me11data/A11514.root .
cp ../me11data/A11761.root .
cp ../me11data/A12100.root .
cp ../me11data/A12229.root .
cp ../me11data/A12862.root .
cp ../me11data/A13158.root .
cp ../me11data/A13241.root .
cp ../me11data/A13274.root .
cp ../me11data/A13400.root .
cp ../me11data/A13499.root .
cp ../me11data/A13923.root .
cp ../me11data/A13960.root .
cp ../me11data/A14030.root .
cp ../me11data/A14156.root .
cp ../me11data/A14553.root .
cp ../me11data/A14594.root .
./NewTest11.sh csc_00000001_EmuRUI01_STEP_27s_000_240717_083100_UTC 13532 me11data_HV0 100000
./NewTest11.sh csc_00000001_EmuRUI01_Test_11_000_240731_084135_UTC 13712 me11data_HV0 100000
./NewTest11.sh csc_00000001_EmuRUI01_Test_11_000_240807_092627_UTC 13795 me11data_HV0 100000
./NewTest11.sh csc_00000001_EmuRUI01_Test_11_000_250430_100327_UTC 14677 me11data_HV0 100000

python TMBRatePlotter_1.py --tenpctzero --charges me11data_HV0/charge_me11_HV0.txt --Dat0V me11data_HV0/TMB_0V_me11.txt --DatHV0 me11data_HV0/TMB_HV0_me11.txt --DatT11 me11data_HV0/anode_me11_HV0.txt --plotname ME11_TMB_HV0
