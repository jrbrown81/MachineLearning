#!/bin/sh
# Script to run ./OpModel simulation, then execute hadd to merge rootfiles into a single file

for x in `seq -20 5 20`;
	do
		for y in `seq -20 5 20`;
			do
				echo $x $y
				echo "Modifying gps_source.in..."
				sed -i "\/gps\/pos\/centre/c\/gps\/pos\/centre $x $y -40 mm" gps_source.in
				cp gps_source.in x${x}y${y}.in
				echo "Executing ./OpModel ..."
				./OpModel -m x${x}y${y}.in
				echo "...combining rootfiles with hadd..."
				hadd x${x}y${y}.root RootOut_t0.root RootOut_t1.root
				echo ".../moving files to ../results/..."
				mv x${x}y${y}.root ../results/
				mv x${x}y${y}.in ../results/
			done 
	done

