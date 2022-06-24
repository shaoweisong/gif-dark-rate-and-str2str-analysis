#!/bin/bash
# TODO:
# run test_plot.cc for each YYYY_MMDD in stripdates.txt
test1dir=$PWD
cd ../strip/datame21
datdir=$PWD
while read -r line;
arr22=$line
echo $arr22
A="$(echo $line | cut -d' ' -f1)"
echo $A
echo $arr22
do
    A="$(echo $line | cut -d' ' -f1)"
    root -b -q -l "test_plot.cc(\"$A\")"
done < $datdir/10pct_stripdatecharges.txt
