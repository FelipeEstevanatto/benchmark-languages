import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.FileOutputStream;

// Average complexity: O(nlog(n))
// Worst complexity: O(nlog(n))

public class MergeSort {
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
        String resultPath = "../Results/MergeSort.txt";
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
        mergeSort(numbers);
        long endTime = System.currentTimeMillis();

        long elapsedTime = endTime - startTime;

        System.out.println("Elapsed time: " + elapsedTime + " miliseconds");

        writeResult(elapsedTime, filePath, resultPath);
    }

    public static void mergeSort(int[] list) {
        if (list.length > 1) {
            int mid = list.length / 2;
            int[] left = Arrays.copyOfRange(list, 0, mid);
            int[] right = Arrays.copyOfRange(list, mid, list.length);

            mergeSort(left);
            mergeSort(right);

            merge(list, left, right);
        }

    }

    public static void merge(int[] mainArray, int[] leftArray, int[] rightArray) {
        int leftIndex = 0;
        int rightIndex = 0;
        int mainIndex = 0;
    
        while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
            if (leftArray[leftIndex] < rightArray[rightIndex]) {
                mainArray[mainIndex] = leftArray[leftIndex];
                leftIndex++;
            } else {
                mainArray[mainIndex] = rightArray[rightIndex];
                rightIndex++;
            }
            mainIndex++;
        }
    
        while (leftIndex < leftArray.length) {
            mainArray[mainIndex] = leftArray[leftIndex];
            leftIndex++;
            mainIndex++;
        }
    
        while (rightIndex < rightArray.length) {
            mainArray[mainIndex] = rightArray[rightIndex];
            rightIndex++;
            mainIndex++;
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
        writer.printf("Java - MergeSort - File: %s\n", name);
        writer.printf("Execution time: %.2f ms\n", (double)executionTime / 1_000_000); // convert nanoseconds to milliseconds
        writer.close();
    }
}