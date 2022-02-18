#!/bin/sh
dir=$1
dt=$2
#counter=1
#for FILE in $dir/*$dt*
for FILE in $dir/*
do 
#((counter=counter+1))
base_name=$(basename ${FILE})
outfileName="MuonPeak_"$base_name".root"
#echo $counter" : "$base_name
echo "Processing file : "$FILE
./Test_GenerateMuonPeakPosTree $FILE $outfileName
done
