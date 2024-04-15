# Take the information from the sorting .txt inside Results
# Results
#   |__ C
#       |__ BucketSort.txt
#       |__ InsetionSort.txt
#       |__ MergeSort.txt
#   |__ C++
#   |__ Java
# Each file has the following format:
# Running BucketSort test with 1k_parc_ordenado dataset
# Execution time: 0.000000 ms
# Execution time: 0.000000 ms
# Execution time: 0.000000 ms
# Running BucketSort test with 10k_parc_ordenado dataset
# Execution time: 0.000000 ms
# Execution time: 0.000000 ms
# Execution time: 0.000000 ms
# Running BucketSort test with 100k_parc_ordenado dataset
# Execution time: 1.000000 ms
# Execution time: 0.000000 ms
# Execution time: 0.000000 ms

# The goal is to read from these files, average the 3 runs of each case and store them like this:
# data = {
#     'C': {
#         'BucketSort': {
#               'random': {
#                   '1000': 0.0,
#                   '10000': 0.0,
#                   '100000': 0.0,
#                   '1000000': 0,0
#               },
#         },
#     },
# }

def get_data(file):
    data = {}
    with open(file) as f:
        lines = f.readlines()
        i = 0
        while i < len(lines):
            # Parse the test info
            test_info = lines[i].strip().split()
            test_name = test_info[1]
            dataset_size = test_info[4].split('_')[0]
            dataset_type = test_info[4].split('_')[1]
            print(test_name, dataset_type, dataset_size, dataset_type)
            # Initialize the data structure if necessary
            if dataset_type not in data:
                data[dataset_type] = {}

            # Parse the execution times
            times = []
            for j in range(3):
                i += 1
                time = float(lines[i].split()[2])
                times.append(time)
            
            # Store the average time
            avg_time = sum(times) / len(times)
            data[dataset_type][dataset_size] = avg_time
            i += 1
    return data

data = {
    'C': {},
    'C++': {},
    'Java': {},
}

sorting_algorithms = ['BucketSort', 'InsertionSort', 'MergeSort']

for language in data.keys():
    print(f'Processing {language}')
    for algorithm in sorting_algorithms:
        file = f'Results/{language}/{algorithm}.txt'
        data[language][algorithm] = get_data(file)

import csv

for language in data.keys():
    with open(f'{language}.csv', 'w') as f:
        writer = csv.writer(f)
        writer.writerow(['Linguagem', 'Test', 'Dataset Size', 'Execution Time (ms)'])
        for algorithm in sorting_algorithms:
            for dataset_type in data[language][algorithm].keys():
                for dataset_size, time in data[language][algorithm][dataset_type].items():
                    writer.writerow([language, algorithm, f'{dataset_size}_{dataset_type}', time])






# save the data to a json file
import json

with open('data.json', 'w') as f:
    json.dump(data, f, indent=4)

        

#print(data)
