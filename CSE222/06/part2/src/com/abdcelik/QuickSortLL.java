package com.abdcelik;

import java.util.LinkedList;
import java.util.ListIterator;

public class QuickSortLL
{
    public static <T extends Comparable<T>> void sort(LinkedList<T> list)
    {
        quickSort(list,0,list.size()-1);
    }

    private static <T extends Comparable<T>> void quickSort(LinkedList<T> list, int first, int last)
    {
        if(first < last)
        {
            int p = partition(list,first,last);

            quickSort(list,first,p-1);
            quickSort(list,p+1,last);
        }
    }

    private static <T extends Comparable<T>> int partition(LinkedList<T> list, int firstIndex, int lastIndex)
    {
        ListIterator<T> temp = list.listIterator(lastIndex);
        T pivot = temp.next();
        int i = firstIndex-1;

        for(ListIterator<T> iter = list.listIterator(firstIndex) ; iter.nextIndex() <= lastIndex-1 ;)
            if(iter.next().compareTo(pivot) < 0)
            {
                ++i;
                iter.previous();
                swap(list,i,iter);
                iter.next();
            }

        temp.previous();
        swap(list,i+1,temp);
        return i+1;
    }

    private static <T extends Comparable<T>> void swap(LinkedList<T> list, int i, ListIterator<T> iter)
    {
        T temp = list.get(i);
        list.set(i,iter.next());
        iter.set(temp);
    }
}