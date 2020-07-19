package com.abdcelik;

import java.util.LinkedList;

/** Implements the recursive merge sort algorithm. In this version, copies of the sublist are made, sorted, and then merged. */
public class MergeSortLL
{
    /**
     * Sort the linked list using the merge sort algorithm.
     * pre: list contains Comparable objects.
     * post: list is sorted.
     * @param list The linked list to be sorted
     * @param <T> generic type of items
     */
    public static <T extends Comparable<T>> void sort(LinkedList<T> list)
    {
        if(list.size() <= 1)
            return;

        int halfSize = list.size()/2;

        LinkedList<T> left = new LinkedList<>(list.subList(0,halfSize));
        LinkedList<T> right = new LinkedList<>(list.subList(halfSize,list.size()));

        sort(left);
        sort(right);

        list.clear();
        merge(list,left,right);
    }

    /** Merge two sequences.
      * pre: left and right are sorted.
      * post: list is the merged result and is sorted.
      * @param list The destination
      * @param left The left input
      * @param right The right input
      * @param <T> generic type of items
     */
    private static <T extends Comparable<T>> void merge(LinkedList<T> list, LinkedList<T> left, LinkedList<T> right)
    {
        while(left.size() != 0 && right.size() != 0)
            if(left.getFirst().compareTo(right.getFirst()) < 0)
                list.add(left.remove());
            else
                list.add(right.remove());

        while(left.size() != 0)
            list.add(left.remove());

        while(right.size() != 0)
            list.add(right.remove());
    }
}