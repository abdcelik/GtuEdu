package com.abdcelik;

public class BubbleSort
{
    /**
     * Sort the given array.
     * @param table Given array
     * @param <E> item that implements Comparable interface.
     */
    public static <E extends Comparable< ? super E>> void sort( E[] table )
    {
        int pass = 1;
        boolean exchanges;

        do
        {
            exchanges = false;

            for( int i = 0 ;i < table.length - pass ; ++i ) {
                if( table[i].compareTo(table[i+1]) > 0 ) {

                    E temp = table[i];
                    table[i] = table[i + 1];
                    table[i + 1] = temp;

                    exchanges = true;
                }
            }
            pass++;
        } while ( exchanges );
    }
}
