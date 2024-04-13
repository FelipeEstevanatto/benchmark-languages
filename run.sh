#!/bin/bash

# compile C code with -Ofast flag inside the C folder
cd C
gcc -Ofast -o InsertionSort.exe InsertionSort.c
gcc -Ofast -o BucketSort.exe BucketSort.c
gcc -Ofast -o MergeSort.exe MergeSort.c

# define array of sorting algorithms
declare -a sorts=("InsertionSort" "BucketSort" "MergeSort")

# define array of data set sizes
declare -a sizes=("1k" "10k" "100k" "500k" "1000k")

# define array of data set sizes in numbers
declare -a size_nums=("1000" "10000" "100000" "500000" "1000000")

# run all 95% test cases for C
for i in {1..3}
do
    for sort in "${sorts[@]}"
    do
        for index in "${!sizes[@]}"
        do
            size=${sizes[$index]}
            size_num=${size_nums[$index]}
            ./${sort}.exe "../Dataset/${size}_parc_ordenado.txt" "../Results/${sort}.txt" ${size_num}
        done
    done
done

declare -a other_cases=("1000k_decreasing.txt", "1000k_random.txt")

for i in {1..3}
do
    for sort in "${sorts[@]}"
    do
        for index in "${!sizes[@]}"
        do
            size=${sizes[$index]}
            size_num=${size_nums[$index]}
            ./${sort}.exe "../Dataset/1000k_decreasing.txt" "../Results/${sort}.txt" ${size_num}
            ./${sort}.exe "../Dataset/1000k_random.txt" "../Results/${sort}.txt" ${size_num}
        done
    done
done

# compile C++ code with -Ofast flag inside the C folder
cc ../C++
gcc -Ofast -o InsertionSort.exe InsertionSort.c
gcc -Ofast -o BucketSort.exe BucketSort.c
gcc -Ofast -o MergeSort.exe MergeSort.c

# run all 95% test cases for C++
# for i in {1..3}
# do
    for sort in "${sorts[@]}"
    do
        for index in "${!sizes[@]}"
        do
            size=${sizes[$index]}
            size_num=${size_nums[$index]}
            for i in {1..3}
                do
                ./${sort}.exe "../Dataset/${size}_parc_ordenado.txt" "../Results/${sort}.txt" ${size_num}
            done
        done
    done
# done

# for i in {1..3}
# do
    for sort in "${sorts[@]}"
    do
        for index in "${!sizes[@]}"
        do
            for i in {1..3}
                do
                size=${sizes[$index]}
                size_num=${size_nums[$index]}
                ./${sort}.exe "../Dataset/1000k_decreasing.txt" "../Results/${sort}.txt" ${size_num}
                ./${sort}.exe "../Dataset/1000k_random.txt" "../Results/${sort}.txt" ${size_num}
            done
        done
    done
# done
