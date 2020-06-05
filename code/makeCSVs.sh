#!/bin/sh
# Script to run code to process root file into csv outputs

for filename in ../results/*.root; do
	echo "Processing file: " $filename
	filename=${filename%.root}
	root -q -b pixelAnalysis.C\(\"$filename\",1,1\)
	mv "${filename}_plots.root" "../results/plots/"
	mv "${filename}.csv" "../results/csvs/"
	done
