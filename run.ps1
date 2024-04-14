# define array of sorting algorithms
$sorts = "InsertionSort", "BucketSort", "MergeSort"

# define array of data set sizes
$sizes = "1k", "10k", "100k", "500k", "1000k"

# define array of data set sizes in numbers
$size_nums = "1000", "10000", "100000", "500000", "1000000"

$other_cases = "1000k_decreasing.txt", "1000k_random.txt"

Set-Location -Path .\Java
# compile Java code
javac *.java

# run all 95% test cases for Java
if (!(Test-Path -Path ..\Results\Java)) {
    New-Item -ItemType Directory -Path ..\Results\Java
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\Java\$sort.txt" -Value "Running $sort test with ${size}_parc_ordenado dataset"
        for ($i = 1; $i -le 3; $i++) {
            java $sort "..\Dataset\${size}_parc_ordenado.txt" "..\Results\Java\$sort.txt" $size_num
        }
    }
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\Java\$sort.txt" -Value "Running $sort test with ${size}_decreasing size"
        for ($i = 1; $i -le 3; $i++) {
            java $sort "..\Dataset\1000k_decreasing.txt" "..\Results\Java\$sort.txt" $size_num
        }
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\Java\$sort.txt" -Value "Running $sort test with ${size}_random size"
        for ($i = 1; $i -le 3; $i++) {
            java $sort "..\Dataset\1000k_random.txt" "..\Results\Java\$sort.txt" $size_num
        }
    }
}

# compile C code with -Ofast flag inside the C folder
Set-Location -Path ..\C
gcc -Ofast -o InsertionSort.exe InsertionSort.c
gcc -Ofast -o BucketSort.exe BucketSort.c
gcc -Ofast -o MergeSort.exe MergeSort.c

# run all 95% test cases for C
if (!(Test-Path -Path ..\Results\C)) {
    New-Item -ItemType Directory -Path ..\Results\C
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C\$sort.txt" -Value "Running $sort test with ${size}_parc_ordenado dataset"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\${size}_parc_ordenado.txt" "..\Results\C\$sort.txt" $size_num
        }
    }
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C\$sort.txt" -Value "Running $sort test with ${size}_decreasing size"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\1000k_decreasing.txt" "..\Results\C\$sort.txt" $size_num
        }
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C\$sort.txt" -Value "Running $sort test with ${size}_random size"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\1000k_random.txt" "..\Results\C\$sort.txt" $size_num
        }
    }
}

# compile C++ code with -Ofast flag inside the C++ folder
Set-Location -Path ..\C++
g++ -Ofast -o InsertionSort.exe InsertionSort.cpp
g++ -Ofast -o BucketSort.exe BucketSort.cpp
g++ -Ofast -o MergeSort.exe MergeSort.cpp

# run all 95% test cases for C++
if (!(Test-Path -Path ..\Results\C++)) {
    New-Item -ItemType Directory -Path ..\Results\C++
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C++\$sort.txt" -Value "Running $sort test with ${size}_parc_ordenado dataset"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\${size}_parc_ordenado.txt" "..\Results\C++\$sort.txt" $size_num
        }
    }
}

foreach ($sort in $sorts) {
    for ($index = 0; $index -lt $sizes.Length; $index++) {
        $size = $sizes[$index]
        $size_num = $size_nums[$index]
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C++\$sort.txt" -Value "Running $sort test with ${size}_decreasing size"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\1000k_decreasing.txt" "..\Results\C++\$sort.txt" $size_num
        }
        # write in the file what test and size it is running now
        Add-Content -Path "..\Results\C++\$sort.txt" -Value "Running $sort test with ${size}_random size"
        for ($i = 1; $i -le 3; $i++) {
            .\$sort.exe "..\Dataset\1000k_random.txt" "..\Results\C++\$sort.txt" $size_num
        }
    }
}


