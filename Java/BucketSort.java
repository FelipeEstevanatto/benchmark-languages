import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.FileOutputStream;

// Average complexity: O(n+k)
// Worst case complexity: O(n^2)

public class BucketSort {
    public static int[] readDataset(String filePath, int maxSize) {
        Scanner datasetFile;
        try {
            datasetFile = new Scanner(new File(filePath));
        } catch (FileNotFoundException e) {
            System.err.println("Failed to open dataset file");
            return null;
        }

        int[] numbers = new int[maxSize];
        int index = 0;
        while (datasetFile.hasNextInt() && index < maxSize) {
            numbers[index++] = datasetFile.nextInt();
        }
        datasetFile.close();

        return numbers;
    }

    public static void main(String args[]) {
        // Default values
        String filePath = "../Dataset/1000k_parc_ordenado.txt";
        String resultPath = "../Results/BucketSort.txt";
        int maxSize = 1000000;

        // Check if the user provided the input file
        if (args.length >= 1) {
            filePath = args[0];
        }

        if (args.length >= 2) {
            resultPath = args[1];
        }

        if (args.length >= 3) {
            maxSize = Integer.parseInt(args[2]);
        }

        int[] numbers = readDataset(filePath, maxSize);
        if (numbers == null) {
            return;
        }

        long startTime = System.currentTimeMillis();
        bucketSort(numbers);
        long endTime = System.currentTimeMillis();

        long elapsedTime = endTime - startTime;

        System.out.println("Elapsed time: " + elapsedTime + " miliseconds");

        writeResult(elapsedTime, filePath, resultPath);
    }

    public static void bucketSort(int[] numbers) {
        int max = Arrays.stream(numbers).max().getAsInt();
        int min = Arrays.stream(numbers).min().getAsInt();
        int bucketSize = 5;
        int bucketCount = (max - min) / bucketSize + 1;
        List<List<Integer>> buckets = new ArrayList<>(bucketCount);
        for (int i = 0; i < bucketCount; i++) {
            buckets.add(new ArrayList<>());
        }

        for (int number : numbers) {
            int bucketIndex = (number - min) / bucketSize;
            buckets.get(bucketIndex).add(number);
        }

        int index = 0;
        for (List<Integer> bucket : buckets) {
            int[] bucketArray = new int[bucket.size()];
            for (int i = 0; i < bucket.size(); i++) {
                bucketArray[i] = bucket.get(i);
            }
            insertionSort(bucketArray);
            for (int number : bucketArray) {
                numbers[index++] = number;
            }
        }
    }

    public static void insertionSort(int[] numbers) {
        for (int currentIndex = 1; currentIndex < numbers.length; currentIndex++) {
            int currentNumber = numbers[currentIndex];
            int previousIndex = currentIndex - 1;
            while (previousIndex >= 0 && numbers[previousIndex] > currentNumber) {
                numbers[previousIndex + 1] = numbers[previousIndex];
                previousIndex = previousIndex - 1;
            }
            numbers[previousIndex + 1] = currentNumber;
        }
    }

    public static void writeResult(long executionTime, String fileName, String resultPath) {
        File resultsFile = new File(resultPath);
        PrintWriter writer;
        try {
            writer = new PrintWriter(new FileOutputStream(resultsFile, true)); // true for append mode
        } catch (FileNotFoundException e) {
            System.err.println("Error opening the results file");
            return;
        }

        String name = new File(fileName).getName();
        writer.printf("Java - BucketSort - File: %s\n", name);
        writer.printf("Execution time: %.2f ms\n", (double)executionTime / 1_000_000); // convert nanoseconds to milliseconds
        writer.close();
    }
}