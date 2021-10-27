#!/bin/sh
filename=$1
noOfShots=$2
#shotNo=$3
finalOutputFileName="Combined.root"
haddcommand="hadd $finalOutputFileName"
rmcommand="rm -rf"
for shotNo in $(seq 1 $noOfShots)
do
    justFileName=$(basename $filename .root)
    outputFileName=$justFileName"_Shot_"$shotNo".root"
    haddcommand+=" $outputFileName"
    rmcommand+=" "$outputFileName;
    ./Test_Analyzer_F_Shots $filename $outputFileName $noOfShots $shotNo
done
$haddcommand
$rmcommand
