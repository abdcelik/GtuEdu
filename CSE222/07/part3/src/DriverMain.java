import abdcelik.Trees.*;

import java.util.LinkedList;
import java.util.Random;
import java.util.TreeMap;
import java.util.concurrent.ConcurrentSkipListSet;

public class DriverMain
{
    public static boolean testRegularBinarySearchTree = true;
    public static boolean testRedBlackTreeInTheBook = true;
    public static boolean testRedBlackTreeInJava = true;
    public static boolean testBTreeInTheBook = true; // remove kısmı
    public static boolean testSkipListInTheBook = true;
    public static boolean testSkipListInJava = true;
    public static boolean testSkipListInQ2 = true;
    private static Random rand = new Random();

    public static void main(String[] argv)
    {
        if(testRegularBinarySearchTree)
        {
            testRegularBinarySearchTree(10000,10);
            testRegularBinarySearchTree(20000,10);
            testRegularBinarySearchTree(40000,10);
            testRegularBinarySearchTree(80000,10);
        }

        if(testRedBlackTreeInTheBook)
        {
            testRedBlackTreeInTheBook(10000,10);
            testRedBlackTreeInTheBook(20000,10);
            testRedBlackTreeInTheBook(40000,10);
            testRedBlackTreeInTheBook(80000,10);
        }

        if(testRedBlackTreeInJava)
        {
            testRedBlackTreeInJava(10000,10);
            testRedBlackTreeInJava(20000,10);
            testRedBlackTreeInJava(40000,10);
            testRedBlackTreeInJava(80000,10);
        }

        if(testBTreeInTheBook)
        {
            testBTreeInTheBook(10000,10);
            testBTreeInTheBook(20000,10);
            testBTreeInTheBook(40000,10);
            testBTreeInTheBook(80000,10);
        }

        if(testSkipListInTheBook)
        {
            testSkipListInTheBook(10000,10);
            testSkipListInTheBook(20000,10);
            testSkipListInTheBook(40000,10);
            testSkipListInTheBook(80000,10);
        }

        if(testSkipListInJava)
        {
            testSkipListInJava(10000,10);
            testSkipListInJava(20000,10);
            testSkipListInJava(40000,10);
            testSkipListInJava(80000,10);
        }

        if(testSkipListInQ2)
        {
            testSkipListInQ2(10000,10);
            testSkipListInQ2(20000,10);
            testSkipListInQ2(40000,10);
            testSkipListInQ2(80000,10);
        }
    }

    public static void testRegularBinarySearchTree(int size, int repetition)
    {
        BinarySearchTree<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Regular Binary Search Tree Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new BinarySearchTree<>();
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Regular Binary Search Tree, average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Regular Binary Search Tree, average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testRedBlackTreeInTheBook(int size, int repetition)
    {
        RedBlackTree<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Red Black Tree(in the book) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new RedBlackTree<>();
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Red Black Tree(in the book), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Red Black Tree(in the book), average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testRedBlackTreeInJava(int size, int repetition)
    {
        TreeMap<Integer,Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Red Black Tree(in java) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new TreeMap<>();
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.put(rand.nextInt(),0);
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.put(added[j],0);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Red Black Tree(in java), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Red Black Tree(in java), average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testBTreeInTheBook(int size, int repetition)
    {
        BTree<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- BTree(in the book) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new BTree<>(4);
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;
        }

        System.out.println("BTree(in the book), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testSkipListInTheBook(int size, int repetition)
    {
        SkipList<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Skip List(in the book) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new SkipList<>();
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Skip List(in the book), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Skip List(in the book), average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testSkipListInJava(int size, int repetition)
    {
        ConcurrentSkipListSet<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Skip List(in java) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");

        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new ConcurrentSkipListSet<>();
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Skip List(in java), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Skip List(in java), average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static void testSkipListInQ2(int size, int repetition)
    {
        SkipListQ2<Integer> tree;
        long start,finish,randAverage=0,delAverage=0;
        int[] added = new int[10];

        System.out.println("------------- Skip List(in Q2) Test -------------\n");
        System.out.println("-------------------- " + size + " Begin --------------------");
        for(int i=0 ; i < repetition ; ++i)
        {
            tree = new SkipListQ2<>(4);
            System.out.println("Trial " + (i+1) + ":");

            for(int j=0 ; j < size ; ++j)
                tree.add(rand.nextInt());
            for(int j=0 ; j < 10 ; ++j)
                added[j] = rand.nextInt();

            System.out.print("Adding 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.add(added[j]);

            finish = System.nanoTime() - start;
            System.out.println(finish + " nanosecond");
            randAverage += finish;

            System.out.print("Removing 10 elements: ");
            start = System.nanoTime();
            for(int j=0 ; j < 10 ; ++j)
                tree.remove(added[j]);
            finish = (System.nanoTime() - start);
            System.out.println(finish + " nanosecond");
            delAverage += finish;
        }

        System.out.println("Skip List(in Q2), average of " + repetition + " repetition, adding 10 random number: " + randAverage/repetition + " nanosecond");
        System.out.println("Skip List(in Q2), average of " + repetition + " repetition, removing 10 random number: " + delAverage/repetition + " nanosecond");
        System.out.println("-------------------- " + size + " End --------------------");
    }

    public static LinkedList<Integer> generateRandomIntegerLinkList(int size)
    {
        LinkedList<Integer> list = new LinkedList<>();
        Random rand = new Random();

        for(int i=0 ; i < size ; ++i)
            list.add(rand.nextInt());

        return list;
    }
}