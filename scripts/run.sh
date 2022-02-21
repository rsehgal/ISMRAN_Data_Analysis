#!/bin/sh
dir=$1
dt=$2
outfilePath=$3
#counter=1
#for FILE in $dir/*$dt*
if [ -z "$dt" ]
then
searchFor=$dir/*
else
searchFor=$dir/*$dt*
fi

#for FILE in $dir/*
for FILE in $searchFor
do 
#((counter=counter+1))
base_name=$(basename ${FILE})
outfileName=$outfilePath"/MuonPeak_"$base_name
#echo $counter" : "$base_name
echo "Processing file : "$FILE
./Test_GenerateMuonPeakPosTree $FILE $outfileName
done
