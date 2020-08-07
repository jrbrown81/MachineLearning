#!/bin/sh
# Script to append real positions to each line of csv files

mkdir appended

for filename in *.csv; do
        echo "Processing file: " $filename
	cp $filename appended/
        myString=${filename%.csv}  # strip ".csv" from end filename and write to myString
        newString=$(echo $myString | sed -r 's:[xy]:,:g')
        sed -i "s:$:$newString:" appended/$filename 
        done

