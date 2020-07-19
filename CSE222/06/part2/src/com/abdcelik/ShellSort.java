package com.abdcelik;

import java.time.Duration;
import java.time.Instant;


/** Implements the Shell sort algorithm. */
public class ShellSort {

    private static int comparisionAmount;
    private static int swapAmount;
    private static long runTime;
    private static long expectedRuntime;

    /** Sort the table using Shell sort algorithm.
     @param table The array to be sorted
     */
    public static <E extends Comparable<? super E>> void sort(E[] table) {

        Instant start = Instant.now();

        int gap = table.length / 2;

        while (gap > 0) {
            for (int nextPos = gap ; nextPos < table.length ; nextPos++) {
                insert(table, nextPos, gap);
            }
            if (gap == 2) {
                gap = 1;
            } else {
                gap = (int) (gap / 2.2);
            }
        }

        Instant end = Instant.now();

        runTime = Duration.between( start , end ).toMillis();
        swapAmount = 0;
        comparisionAmount = 0;
        expectedRuntime = 0;
    }


    /** Inserts element at nextPos where it belongs in array.
     @param table The array being sorted
     @param nextPos The position of element to insert
     @param gap The gap between elements in the subarray
     */
    private static <E extends Comparable<? super E>> void insert(E[] table,
                                                         int nextPos, int gap) {
        E nextVal = table[nextPos];

        while ((nextPos > gap - 1) && (nextVal.compareTo
                (table[nextPos - gap]) < 0)) {

            table[nextPos] = table[nextPos - gap];

            nextPos -= gap;
        }

        table[nextPos] = nextVal;
    }

    /**
     * Clear the status
     */
    public static void clearStat( ) {
        comparisionAmount = 0;
        swapAmount = 0;
        runTime = 0;
        expectedRuntime = 0;
    }

    /**
     * Get comparision amount
     * @return comparision amount
     */
    public static int getComparisionAmount() {
        return comparisionAmount;
    }

    /**
     * Get swap amount
     * @return swap amount
     */
    public static int getSwapAmount() {
        return swapAmount;
    }

    /**
     * Get runtime
     * @return runtime
     */
    public static long getRunTime() {
        return runTime;
    }

    /**
     * Get expected runtime
     * @return expected runtime.
     */
    public static long getExpectedRuntime() {
        return expectedRuntime;
    }

}
