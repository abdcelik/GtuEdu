import com.abdcelik.*;
import java.util.LinkedList;
import java.util.Random;

class DriverMain
{
    public static boolean testMergeSortLL      = false;
    public static boolean testQuickSortLL      = false;
    public static boolean testMergeSort        = false;
    public static boolean testQuickSort        = false;
    public static boolean testBubbleSort       = false;
    public static boolean testHeapSort         = false;
    public static boolean testInsertionSort    = false;
    public static boolean testSelectionSort    = false;
    public static boolean testShellSort        = false;

    public static void main(String[] argv)
    {
        if(testSelectionSort)
            TestSelectionSort(0,1);

        if(testBubbleSort)
            TestBubbleSort(0,1);

        if(testInsertionSort)
            TestInsertionSort(0,1);

        if(testShellSort)
            TestShellSort(0,1);

        if(testMergeSort)
            TestMergeSort(0,1);

        if(testHeapSort)
            TestHeapSort(0,1);

        if(testQuickSort)
            TestQuickSort(0,1);

        if(testMergeSortLL)
            TestMergeSortLL(0,1);

        if(testQuickSortLL)
            TestQuickSortLL(0,1);
    }

    public static void TestSelectionSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Selection-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Selection-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Selection-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Selection-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Selection-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            SelectionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Selection-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Selection-Sort-Test-End--------------------------");
    }

    public static void TestBubbleSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Bubble-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Bubble-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Bubble-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Bubble-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Bubble-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            BubbleSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Bubble-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Bubble-Sort-Test-End--------------------------");
    }

    public static void TestInsertionSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Insertion-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Insertion-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Insertion-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Insertion-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Insertion-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            InsertionSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Insertion-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Insertion-Sort-Test-End--------------------------");
    }

    public static void TestShellSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Shell-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Shell-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Shell-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Shell-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Shell-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            ShellSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Shell-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Shell-Sort-Test-End--------------------------");
    }

    public static void TestMergeSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Merge-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Merge-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Merge-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Merge-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Merge-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            MergeSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Merge-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Merge-Sort-Test-End--------------------------");
    }

    public static void TestHeapSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Heap-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Heap-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Heap-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Heap-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Heap-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            HeapSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Heap-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Heap-Sort-Test-End--------------------------");
    }

    public static void TestQuickSort(int randRepetition, int sortedRepetition)
    {
        Integer[] rand;
        long start,average;
        int size;

        System.out.println("---------------Quick-Sort Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Quick-Sort , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");




        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Quick-Sort , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");

        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Quick-Sort , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Quick-Sort , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerArray(size);
            start = System.nanoTime();
            QuickSort.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("Quick-Sort , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------Quick-Sort-Test-End--------------------------");
    }

    public static void TestMergeSortLL(int randRepetition, int sortedRepetition)
    {
        LinkedList<Integer> rand;
        long start,average;
        int size;

        System.out.println("---------------MergeSortLL Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("MergeSortLL , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("MergeSortLL , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");


        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("MergeSortLL , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("MergeSortLL , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");

        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            MergeSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("MergeSortLL , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------MergeSortLL-End--------------------------");
    }

    public static void TestQuickSortLL(int randRepetition, int sortedRepetition)
    {
        LinkedList<Integer> rand;
        long start,average;
        int size;

        System.out.println("---------------QuickSortLL Test---------------\n");
        System.out.println("---------------------------10K-Begin-------------------------");
        average = 0;
        size = 10000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("QuickSortLL , running time for 10K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------10K-End----------------------------------------\n");


        System.out.println("---------------------------40K-Begin-------------------------");
        average = 0;
        size = 40000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("QuickSortLL , running time for 40K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------40K-End----------------------------------------\n");



        System.out.println("---------------------------100K-Begin-------------------------");
        average = 0;
        size = 100000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("QuickSortLL , running time for 100K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------100K-End----------------------------------------\n");

        System.out.println("---------------------------150K-Begin-------------------------");
        average = 0;
        size = 150000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("QuickSortLL , running time for 150K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------150K-End----------------------------------------\n");


        System.out.println("---------------------------180K-Begin-------------------------");
        average = 0;
        size = 180000;
        for(int i = 0 ; i < randRepetition ; ++i)
        {
            rand = generateRandomIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        for(int i = 0 ; i < sortedRepetition ; ++i)
        {
            rand = generateSortedIntegerLinkList(size);
            start = System.nanoTime();
            QuickSortLL.sort(rand);
            average += (System.nanoTime() - start) / 1000000;
        }
        System.out.println("QuickSortLL , running time for 180K : " + average/(randRepetition+sortedRepetition) + " millisecond.");
        System.out.println("--------------------180K-End----------------------------------------\n");
        System.out.println("--------------------MergeSortLL-End--------------------------");
    }

    public static Integer[] generateRandomIntegerArray(int size)
    {
        Integer[] arr = new Integer[size];
        Random rand = new Random();

        for(int i=0 ; i < size ; ++i)
            arr[i] = rand.nextInt();

        return arr;
    }

    public static Integer[] generateSortedIntegerArray(int size)
    {
        Integer[] arr = new Integer[size];

        for(int i=0 ; i < size ; ++i)
            arr[i] = i;

        return arr;
    }

    public static LinkedList<Integer> generateRandomIntegerLinkList(int size)
    {
        LinkedList<Integer> list = new LinkedList<>();
        Random rand = new Random();

        for(int i=0 ; i < size ; ++i)
            list.add(rand.nextInt());

        return list;
    }

    public static LinkedList<Integer> generateSortedIntegerLinkList(int size)
    {
        LinkedList<Integer> list = new LinkedList<>();

        for(int i=0 ; i < size ; ++i)
            list.add(i);

        return list;
    }
}