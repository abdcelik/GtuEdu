package com.abdcelik;

import java.util.Arrays;
import java.util.Random;

/**
 * Each node in the lowest-level list keeps several elements instead of just one element as in a B-tree node.
 * @param <E> type of element to be stored
 * @author Abdullah Celik
 */
public class SkipList<E extends Comparable<E>>
{
    /** Head of the skip-list */
    private SLNode<E> head;
    /** Size of the skip list */
    private int size;
    /** The maximum level of the skip-list */
    private int maxLevel;
    /** Smallest power of 2 that is greater than the current skip-list size */
    private int maxCap;
    /** Minimum element in a node(maxElement/2)*/
    private int minElement;
    /** Maximum element in a node */
    private int maxElement;
    /** Natural log of 2 */
    private static final double LOG2 = Math.log(2.0);
    /** Random number generator*/
    private Random rand = new Random();

    /**
     * Constructor with one parameter for building SkipList data structure.
     * @param max maximum element in a node
     */
    public SkipList(int max)
    {
        if(max < 1)
            throw new IndexOutOfBoundsException("Invalid size!");

        size = 0;
        maxLevel = 0;
        maxCap = computeMaxCap(maxLevel);
        maxElement = Math.max(1,max);
        minElement = maxElement/2;
        head = new SLNode<>(getMaxNodeCapacity(),maxLevel);
    }

    /**
     * Search for an item in the list
     * @param target The item being sought
     * @return An SLNode array which references the predecessors of the target at each level.
     */
    @SuppressWarnings("unchecked")
    private SLNode<E>[] search(E target)
    {
        SLNode<E>[] pred = new SLNode[getMaxLevel()];
        SLNode<E> current = getHead();
        boolean exit = false;

        for(int i = current.links.length-1,j ; i >= 0 ; --i)
        {
            while(current.links[i] != null && !exit)
            {
                for(j=0 ; j < current.links[i].getNodeSize() && current.links[i].data[j].compareTo(target) < 0 ; ++j);

                if(j >= current.links[i].getNodeSize() && current.links[i].links[i] != null)
                    current = current.links[i];
                else
                    exit = true;
            }
            pred[i] = current;
            exit = false;
        }

        return pred;
    }

    /**
     * Find an object in the skip-list.
     * @param target The item being sought
     * @param pred references the predecessors of the target at each level
     * @return A reference to the object in the skip-list that matches the target. If not found, null is returned
     */
    private E find(E target, SLNode<E>[] pred)
    {
        if(pred.length != 0)
            for(int i=0 ; i < pred[0].links[0].getNodeSize() ; ++i)
                if(pred[0].links[0].data[i].compareTo(target) == 0)
                    return pred[0].links[0].data[i];
        return null;
    }

    /**
     * Find an object in the skip-list.
     * @param target The item being sought
     * @return A reference to the object in the skip-list that matches the target. If not found, null is returned
     */
    public E find(E target) { return find(target,search(target)); }

    /**
     * Inserts the given item
     * @param item The item to add
     * @return true as the item is added
     */
    public boolean add(E item)
    {
        SLNode<E>[] pred = search(item);

        if(find(item,pred) != null)
            return false;

        if(getHead().links.length == 0)
        {
            initializeHead(item);
            return true;
        }

        SLNode<E> addedNode = pred[0].links[0];

        if(addedNode.getNodeSize() < getMaxNodeCapacity())
            return addedNode.add(item);

        SLNode<E> newNode = new SLNode<>(getMaxNodeCapacity(),logRandom());


        if(addedNode.queryElement(item) < getMinNodeCapacity())
        {
            newNode.add(item);
            for(int i = 0 ; i < getMinNodeCapacity() - newNode.getNodeSize() ; ++i)
                newNode.add(addedNode.remove(i));
        }
        else
        {
            for(int i = 0 ; i < getMinNodeCapacity() ; ++i)
                newNode.add(addedNode.remove(0));
            addedNode.add(item);
        }

        for(int i=0 ; i < newNode.links.length ; ++i)
        {
            newNode.links[i] = pred[i].links[i];
            pred[i].links[i] = newNode;
        }

        ++size;
        updateSkipList();
        return true;
    }

    /**
     * Initializes head.
     * @param item to be added
     */
    private void initializeHead(E item)
    {
        SLNode<E> newNode = new SLNode<>(getMaxNodeCapacity(),1,item);

        ++size;
        updateSkipList();
        getHead().links[0] = newNode;
    }

    /**
     * Updates skip list information such as maxLevel, maxCap.
     */
    private void updateSkipList()
    {
        if(size > maxCap)
        {
            ++maxLevel;
            maxCap = computeMaxCap(maxLevel);
            head.links = Arrays.copyOf(head.links, maxLevel);
        }
    }

    /**
     * Merges given target node with given source node and organizes links. Target node is next node of source node.
     * @param target given target node
     * @param source given source node
     * @param pred references the predecessors of the target at each level
     */
    private void mergeNextNode(SLNode<E> target, SLNode<E> source, SLNode<E>[] pred)
    {
        if(target.getNodeSize() + source.getNodeSize() <= getMaxNodeCapacity())
        {
            for(int i=0 ; i < source.getNodeSize() ; ++i)
                target.add(source.data[i]);

            for(int i=0 ; i < source.links.length ; ++i)
                pred[i].links[i] = pred[i].links[i].links[i];
        }
        else
            for(int i=0 ; i < getMinNodeCapacity() - source.getNodeSize() ; ++i)
                source.add(target.remove(i));
    }

    /**
     * Merges given target node with given source node and organizes links. Target node is previous node of source node.
     * @param target given target node
     * @param source given source node
     * @param pred references the predecessors of the target at each level
     */
    private void mergePreviousNode(SLNode<E> target, SLNode<E> source, SLNode<E>[] pred)
    {
        if(target.getNodeSize() + source.getNodeSize() <= getMaxNodeCapacity())
        {
            for(int i=0 ; i < source.getNodeSize() ; ++i)
                target.add(source.data[i]);

            for(int i=0 ; i < source.links.length ; ++i)
                pred[i].links[i] = pred[i].links[i].links[i];
        }
        else
            for(int i = target.getNodeSize()-1 ; i >= getMaxNodeCapacity() - getMinNodeCapacity() + source.getNodeSize() ; --i)
                source.add(target.remove(i));
    }

    /**
     * Removes an instance of the given item
     * @param item The item to remove
     * @return true if the item is removed, false if the item is not in the list
     */
    public boolean remove(E item)
    {
        SLNode<E>[] pred = search(item);

        if(find(item,pred) == null)
            return false;

        SLNode<E> deleteNode = pred[0].links[0];
        int index = deleteNode.queryElement(item);
        deleteNode.remove(index);

        if(deleteNode.getNodeSize() >= getMinNodeCapacity())
            return true;

        --size;

        if(pred[0] != getHead())
            mergePreviousNode(pred[0],deleteNode,pred);
        else if(deleteNode.links != null && deleteNode.links[0] != null)
            mergeNextNode(deleteNode.links[0],deleteNode,pred);
        else if(deleteNode.getNodeSize() == 0)
            Arrays.fill(getHead().links,null);
        else
            ++size;

        return true;
    }

    /**
     * Method to generate a logarithmic distributed integer between 1 and maxLevel.
     *  I.E. 1/2 of the values are 1, 1/4 are 2, etc.
     * @return a random logarithmic distributed int between 1 and maxLevel
     */
    private int logRandom()
    {
        int r = rand.nextInt(maxCap);
        int k = (int) (Math.log(r + 1) / LOG2);

        if(k > maxLevel - 1)
            k = maxLevel - 1;

        return maxLevel - k;
    }

    /**
     * Recompute the max cap belong to given level
     * @param level given level
     * @return max capacity
     */
    private int computeMaxCap(int level) { return (int) Math.pow(2,level) -1; }

    /**
     * Returns head node.
     * @return head node
     */
    private SLNode<E> getHead() { return head; }

    /**
     * Returns maximum level.
     * @return maximum level
     */
    private int getMaxLevel() { return maxLevel; }

    /**
     * Returns minimum number of elements in a node.
     * @return minimum number of elements in a node.
     */
    private int getMinNodeCapacity() { return minElement; }

    /**
     * Returns maximum number of elements in a node.
     * @return maximum number of elements in a node.
     */
    public int getMaxNodeCapacity() { return maxElement; }

    /**
     * Returns string representation of the skip list.
     * @return string representation of the skip list.
     */
    @Override
    public String toString()
    {
        if(size == 0)
            return "Empty";

        StringBuilder sb = new StringBuilder();
        SLNode<E> iter = head;
        int lineMaker = 0;

        sb.append("Head: ").append(getMaxLevel());

        while(iter.links[0] != null)
        {
            iter = iter.links[0];
            sb.append("-->").append(iter.toString());

            if(++lineMaker == 5)
            {
                sb.append("\n");
                lineMaker = 0;
            }
        }
        return sb.toString();
    }

    /**
     * Static class to contain data and links.
     * @param <E> The type of data stored. Must be a Comparable
     */
    private static class SLNode<E extends Comparable<E>>
    {
        /** Keeps elements in a node */
        private E[] data;
        /** Size of elements */
        private int size;
        /** Keeps links of node */
        private SLNode<E>[] links;

        /**
         * Creates a node of given level.
         * @param maxNodeCap maximum number of elements in a node
         * @param level given level
         */
        @SuppressWarnings("unchecked")
        public SLNode(int maxNodeCap, int level)
        {
            size = 0;
            data = (E[]) new Comparable[maxNodeCap];
            links = (SLNode<E>[]) new SLNode[level];
        }

        /**
         * Creates a node of given level.
         * @param maxNodeCap maximum number of elements in a node
         * @param level given level
         * @param item The data to be stored
         */
        public SLNode(int maxNodeCap, int level, E item)
        {
            this(maxNodeCap,level);
            ++size;
            data[0] = item;
        }

        /**
         * Adds given item to node.
         * @param item given item
         * @return true if item can be added. Otherwise false
         */
        public boolean add(E item)
        {
            if(getNodeSize() == data.length)
                return false;

            int i;

            for(i=0 ; i < size && item.compareTo(data[i]) > 0 ; ++i);

            for(int j = size ; j > i  ; --j)
                data[j] = data[j-1];

            data[i] = item;
            ++size;
            return true;
        }

        /**
         * Removes given index from node.
         * @param index given index
         * @return removed item if it can be removed. Otherwise null
         */
        public E remove(int index)
        {
            if(index < 0 || index >= getNodeSize())
                return null;

            E temp = data[index];

            for(int i = index ; i < getNodeSize()-1 ; ++i)
                data[i] = data[i+1];

            --size;
            return temp;
        }

        /**
         * Queries given item in node's element.
         * @param item given item
         * @return index of the given item in the increasing node flour elements
         */
        public int queryElement(E item)
        {
            int i;

            for(i=0 ; i < getNodeSize() && data[i].compareTo(item) < 0 ; ++i);

            return i;
        }

        /**
         * Returns node's size.
         * @return node's size
         */
        public int getNodeSize() { return size; }

        /**
         * Returns string representation of the node.
         * @return string representation of the node.
         */
        @Override
        public String toString()
        {
            StringBuilder sb = new StringBuilder();

            for(int i=0 ; i < getNodeSize() ; ++i)
                sb.append(data[i]).append(",");

            sb.deleteCharAt(sb.length()-1);
            sb.append("|").append(links.length).append("|");
            return sb.toString();
        }
    }
}