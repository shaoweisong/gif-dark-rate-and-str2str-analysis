#!/bin/bash
# TODO:
# run test_plot.cc for each YYYY_MMDD in stripdates.txt
test1dir=$PWD
cd ../strip/datame11
datdir=$PWD
while read -r line;
do
    arr=($line)
    root -b -q -l "test_plot.cc (\"${arr[0]}\")"
done < $datdir/10pct_stripdatecharges.txt
