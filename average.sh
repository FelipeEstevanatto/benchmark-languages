#!/bin/bash

# Extract execution times and calculate average
average=$(awk '/Execution time:/ { sum += $3; count++ } count % 3 == 0 { print "Average execution time: " sum/count " ms"; sum = 0; count = 0 }' ./Results/C/BucketSort.txt)

echo "Average execution time: $average ms"
