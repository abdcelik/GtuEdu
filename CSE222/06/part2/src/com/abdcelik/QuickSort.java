package com.abdcelik;

/** Implements the quicksort algorithm. */
public class QuickSort
{
    /**
     * Sort the table using the quicksort algorithm.
     * @param table The array to be sorted
     * @pre table contains Comparable objects.
     * @post table is sorted.
     */
    public static <E extends Comparable<? super E>> void sort(E[] table)
    {
        quickSort(table, 0, table.length - 1);
    }

    /**
     * Sort a part of the table using the quicksort algorithm.
     *
     * @param table The array to be sorted
     * @param first The index of the low bound
     * @param last  The index of the high bound
     * @post The part of table from first through last is sorted.
     */
    private static <E extends Comparable<? super E>> void quickSort(E[] table, int first, int last) {
        if (first < last)
        {
            int pivIndex = partition(table, first, last);
            quickSort(table, first, pivIndex - 1);
            quickSort(table, pivIndex + 1, last);
        }
    }

    /** Partition the table so that values from first to pivIndex
     are less than or equal to the pivot value, and values from
     pivIndex to last are greater than the pivot value.
     @param table The table to be partitioned
     @param first The index of the low bound
     @param last The index of the high bound
     @return The location of the pivot value
     */
    private static <E extends Comparable<? super E>> int partition(E[] table, int first, int last)
    {
        sort3(table, first, last);
        swap(table, first, (first + last) / 2);
        E pivot = table[first];

        int up = first;
        int down = last;

        do
        {
            while ((up < last) && (pivot.compareTo(table[up]) >= 0)) {
                up++;
            }
            while (pivot.compareTo(table[down]) < 0) {
                down--;
            }
            if (up < down) {
                swap(table, up, down);
            }

        } while (up < down);

        swap(table, first, down);
        return down;
    }

    /** Swap the items in table[i] and table[j].
     @param table The array that contains the items
     @param i The index of one item
     @param j The index of the other item
     */
    private static <E extends Comparable<? super E>> void swap(E[] table, int i, int j)
    {
        E temp = table[i];
        table[i] = table[j];
        table[j] = temp;
    }

    /** Sort table[first], table[middle], and table[last].
     @param table The table to be sorted
     @param first Index of the first element
     @param last Index of the last element
     */
    private static <E extends Comparable<? super E>> void sort3(E[] table, int first, int last)
    {
        int middle = (first + last) / 2;

        if (table[middle].compareTo(table[first]) < 0)
            swap(table, first, middle);

        if (table[last].compareTo(table[middle]) < 0)
            swap(table, middle, last);

        if (table[middle].compareTo(table[first]) < 0)
            swap(table, first, middle);
    }
}





