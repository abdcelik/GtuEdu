package com.abdcelik;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.function.BiPredicate;

/**
 * MaxHeap class to keep objects according to their priority.
 * Default priority is the number of people.
 * @param <E> generic type object
 */
public class MaxHeap<E extends AgeDataInterface>
{
    /** Keeps objects array using ArrayList */
    private ArrayList<E> data;
    /** Comparator object for comparision */
    private Comparator<E> comparator;

    /**
     * No parameter constructor to build a MaxHeap object.
     * Default priority is the number of people.
     */
    public MaxHeap()
    {
        data = new ArrayList<>();
        comparator = (E o1, E o2) -> o1.getNumberOfPeople() - o2.getNumberOfPeople();
    }

    /**
     * One parameter constructor to build a MaxHeap object with its Comparator object.
     * @param comparator for the desired comparison
     */
    public MaxHeap(Comparator<E> comparator)
    {
        data = new ArrayList<>();
        this.comparator = comparator;
    }

    /**
     * Adding new item(is not null) to heap.
     * @param item new item to be added
     * @return true if item can be added. Otherwise returns false
     */
    public boolean add(E item)
    {
        if(item == null)
            return false;

        int index;

        if((index = data.indexOf(item)) != -1)
            data.get(index).increaseNumberOfPeople();
        else
        {
            data.add(item);
            index = data.size()-1;
        }

        for(int parent = (index-1)/2 ; parent >= 0 && comparator.compare(data.get(parent),data.get(index)) < 0 ;)
        {
            swap(parent,index); // index is index of child
            index = parent;
            parent = (index-1)/2;
        }

        return true;
    }

    /**
     * Removing an item from heap.
     * @param item to be removed
     * @return true if item can be removed. Otherwise returns false
     */
    public boolean remove(E item)
    {
        int index;

        if((index = data.indexOf(item)) == -1)
            return false;

        if(data.get(index).decreaseNumberOfPeople() < 1)
        {
            if(index == data.size()-1)
                data.remove(data.size()-1);
            else
            {
                swap(index,data.size()-1);
                data.remove(data.size()-1);

                for(int parent = (index-1)/2 ; index != 0 ; parent = (index-1)/2)
                {
                    if(comparator.compare(data.get(index),data.get(parent)) > 0)
                    {
                        swap(index,parent);
                        index = parent;
                    }
                    else
                        break;
                }
            }
        }
        else
        {
            for(int parent = index, leftChild = 2*parent+1, rightChild, bigChild ; leftChild < data.size() ; leftChild = 2*parent+1)
            {
                rightChild = leftChild + 1;
                bigChild = leftChild;

                if(rightChild < data.size() && comparator.compare(data.get(leftChild),data.get(rightChild)) < 0)
                    bigChild = rightChild;

                if(comparator.compare(data.get(parent),data.get(bigChild)) < 0)
                {
                    swap(parent,bigChild);
                    parent = bigChild;
                }
                else
                    break;
            }
        }

        return true;
    }

    /**
     * Finding an item from heap and returns it if it is available.
     * @param item to be searched
     * @return item if it is available. Otherwise returns null.
     */
    public E find(E item)
    {
        if(item == null)
            return null;

        for(E i : data)
            if(i.getAge() == item.getAge())
                return i;
        return null;
    }

    /**
     * Returns the number of people younger than given age.
     * @param age given age
     * @return the number of people younger than given age
     */
    public int youngerThan(int age) { return counterThan(age,(e,t) -> e < t); }

    /**
     * Returns the number of people older than given age.
     * @param age given age
     * @return the number of people older than give age
     */
    public int olderThan(int age) { return counterThan(age,(e,t) -> e > t); }

    /**
     * Compares the given age with the object in MaxHeap according to the given predicate method.
     * Returns the number of people based on this comparison result.
     * @param age given age
     * @param predicate given comparision
     * @return the number of people based on this comparison result.
     */
    private int counterThan(int age, BiPredicate<Integer,Integer> predicate)
    {
        int result = 0;

        for(E i : data)
            if(predicate.test(i.getAge(),age))
                result += i.getNumberOfPeople();

        return result;
    }

    /**
     * Swaps two objects.
     * @param i first object
     * @param j second object
     */
    private void swap(int i, int j)
    {
        E temp = data.get(i);
        data.set(i,data.get(j));
        data.set(j,temp);
    }

    /**
     * Returns string representation of the MaxHeap class.
     * @return string representation of the MaxHeap class.
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        for(E i : data) sb.append(i.getAge()).append(" - ").append(i.getNumberOfPeople()).append("\n");

        return sb.toString();
    }
}