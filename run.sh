#!/bin/bash
# define array of sorting algorithms
declare -a sorts=("InsertionSort" "BucketSort" "MergeSort")

# define array of data set sizes
declare -a sizes=("1k" "10k" "100k" "500k" "1000k")

# define array of data set sizes in numbers
declare -a size_nums=("1000" "10000" "100000" "500000" "1000000")

declare -a other_cases=("1000k_decreasing.txt" "1000k_random.txt")

# compile C code with -Ofast flag inside the C folder
cd C
gcc -Ofast -o InsertionSort.exe InsertionSort.c
gcc -Ofast -o BucketSort.exe BucketSort.c
gcc -Ofast -o MergeSort.exe MergeSort.c

# # run all 95% test cases for Java
# mkdir -p ../Results/Java
# for sort in "${sorts[@]}"
# do
#     for index in "${!sizes[@]}"
#     do
#         size=${sizes[$index]}
#         size_num=${size_nums[$index]}
#         # write in the file what test and size it is running now
#         echo "Running ${sort} test with ${size}_parc_ordenado dataset" >> "../Results/Java/${sort}.txt"
#         for i in {1..3}
#             do
#             ./${sort}.exe "../Dataset/${size}_parc_ordenado.txt" "../Results/Java/${sort}.txt" ${size_num}
#         done
        
#     done
# done

# for sort in "${sorts[@]}"
# do
#     for index in "${!sizes[@]}"
#     do
#         size=${sizes[$index]}
#         size_num=${size_nums[$index]}
#         # write in the file what test and size it is running now
#         echo "Running ${sort} test with ${size}_decreasing size" >> "../Results/Java/${sort}.txt"
#         for i in {1..3}
#             do
#             ./${sort}.exe "../Dataset/1000k_decreasing.txt" "../Results/Java/${sort}.txt" ${size_num}
#         done
#         # write in the file what test and size it is running now
#         echo "Running ${sort} test with ${size}_random size" >> "../Results/Java/${sort}.txt"
#         for i in {1..3}
#             do
#             ./${sort}.exe "../Dataset/1000k_random.txt" "../Results/Java/${sort}.txt" ${size_num}
#         done
#     done
# done

cd ../Java
#set JAVA_HOME="C:\Program Files\Java\jdk-22"
export JAVA_HOME="/mnt/c/Program Files/Java/jdk-22"
export PATH=$JAVA_HOME/bin:$PATH
# compile Java code
javac *.java

# run all 95% test cases for Java
mkdir -p ../Results/Java
for sort in "${sorts[@]}"
do
    for index in "${!sizes[@]}"
    do
        size=${sizes[$index]}
        size_num=${size_nums[$index]}
        # write in the file what test and size it is running now
        echo "Running ${sort} test with ${size}_parc_ordenado dataset" >> "../Results/Java/${sort}.txt"
        for i in {1..3}
            do
            java ${sort} "../Dataset/${size}_parc_ordenado.txt" "../Results/Java/${sort}.txt" ${size_num}
        done
        
    done
done

for sort in "${sorts[@]}"
do
    for index in "${!sizes[@]}"
    do
        size=${sizes[$index]}
        size_num=${size_nums[$index]}
        # write in the file what test and size it is running now
        echo "Running ${sort} test with ${size}_decreasing size" >> "../Results/Java/${sort}.txt"
        for i in {1..3}
            do
            java ${sort} "../Dataset/1000k_decreasing.txt" "../Results/Java/${sort}.txt" ${size_num}
        done
        # write in the file what test and size it is running now
        echo "Running ${sort} test with ${size}_random size" >> "../Results/Java/${sort}.txt"
        for i in {1..3}
            do
            java ${sort} "../Dataset/1000k_random.txt" "../Results/Java/${sort}.txt" ${size_num}
        done
    done
done

