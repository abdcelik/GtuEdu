package HW03.cse222;
import java.util.AbstractList;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * Generic linked array list. Each node has own array with constant size(5).
 * @param <E> generic type of collection.
 * @author Abdullah_Celik_171044002
 */
public class LinkedArrayList<E> extends AbstractList<E> implements List<E>
{
    /** Start node of LinkedArrayList */
    private Node head = null;
    /** Total size of LinkedArrayList */
    private int listSize = 0;
    /** Maximum array capacity that a node can have */
    private final int maxNodeCapacity = 5;

    /**
     * No parameter constructor.
     */
    public LinkedArrayList() {}

    /**
     * Returns a list iterator over the elements in this list (in proper sequence).
     * @param index index of the first element to be returned from the list iterator (by a call to next).
     * @return a list iterator over the elements in this list (in proper sequence), starting at the specified position in the list.
     * @throws IndexOutOfBoundsException if index lower than 0 or index greater than size.
     */
    @Override
    public ListIterator<E> listIterator(int index) { return new LinkedArrayListIterator(index); }

    /**
     * Returns the element at the specified position in this list.
     * @param index index of the element to return.
     * @return the element at the specified position in this list.
     * @throws IndexOutOfBoundsException if the index is out of range (index lower than 0 || index greater than size()).
     */
    @Override
    public E get(int index)
    {
        if(index < 0 || index >= size())
            throw new IndexOutOfBoundsException();

        return listIterator(index).next();
    }

    /**
     * Returns the number of elements in this list.
     * @return the number of elements in this list.
     */
    @Override
    public int size() { return listSize; }

    /**
     * Inserts the specified element at the specified position in this list. Shifts the element currently at that position (if any) and any subsequent elements to the right (adds one to their indices).
     * @param index index at which the specified element is to be inserted.
     * @param e element to be inserted.
     * @throws IndexOutOfBoundsException if the index is out of range (index lower than 0 || index greater than size()).
     * @throws ClassCastException if the class of the specified element prevents it from being added to this list.
     */
    @Override
    public void add(int index, E e) { listIterator(index).add(e); }

    /**
     * Removes the element at the specified position in this list. Shifts any subsequent elements to the left (subtracts one from their indices). Returns the element that was removed from the list.
     * @param index the index of the element to be removed.
     * @return the element previously at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index lower than 0 || index greater than size()).
     */
    @Override
    public E remove(int index)
    {
        if(index < 0 || index >= size())
            throw new IndexOutOfBoundsException();

        ListIterator<E> iter = listIterator(index);
        E element = iter.next();
        iter.remove();

        return element;
    }

    /**
     * Replaces the element at the specified position in this list with the specified element.
     * @param index index of the element to replace.
     * @param e element to be stored at the specified position.
     * @return the element previously at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index lower than 0 || index greater than size()).
     * @throws ClassCastException if the class of the specified element prevents it from being added to this list
     */
    @Override
    public E set(int index, E e)
    {
        if(index < 0 || index >= size())
            throw new IndexOutOfBoundsException();

        ListIterator<E> iter = listIterator(index);
        E element = iter.next();
        iter.set(e);

        return element;
    }

    /**
     * Getter for the maximum capacity that a node can have.
     * @return maximum capacity.
     */
    public final int getMaxNodeCapacity() { return maxNodeCapacity; }

    /**
     * Setter for the size of the LinkedArrayList.
     * @param listSize new size of the LinkedArrayList.
     */
    private void setListSize(int listSize) { this.listSize = listSize; }

    /**
     * The node class for LinkedArrayList's used node. Node have an array to keep data.
     */
    private class Node
    {
        /** A generic array that the node holds */
        private E[] content;
        /** Size of the array that the node holds */
        private int used = 0;
        /** Previous node */
        private Node previous = null;
        /** Next node */
        private Node next = null;

        /**
         * No parameter constructor. Construct the content array.
         */
        public Node()
        {
            @SuppressWarnings("unchecked")
            E[] temp = (E[])new Object[getMaxNodeCapacity()];
            content = temp;
        }

        /**
         * Two parameter constructor. Construct a node and set previous and next node.
         * @param previous previous node that current node points it.
         * @param next next node that current node points it.
         */
        public Node(Node previous, Node next)
        {
            this();
            this.previous = previous;
            this.next = next;
        }

        /**
         * Access the specified element in the node.
         * @param index specified position.
         * @return content in the specified position.
         */
        public E at(int index) { return content[index]; }

        /**
         * Modify the specified position in the node.
         * @param index specified position.
         * @param e new element.
         */
        public void setContent(int index, E e) { content[index] = e; }

        /**
         * Getter for the size of the array that the node holds.
         * @return size of the array that the node holds.
         */
        public int size() { return used; }

        /**
         * Setter for the size of the array that the node holds.
         * @param size new size.
         */
        public void setSize(int size) { used = size; }
    }

    /**
     * LinkedArrayListIterator implements ListIterator generic interface. Implements ListIterator interface methods.
     */
    private final class LinkedArrayListIterator implements ListIterator<E>
    {
        /** The node that points next node */
        private Node nextNode = null;
        /** Index of next node's element */
        private int nextElementIndex = 0;
        /** The node that points previous node */
        private Node previousNode = null;
        /** Index of previous node's element */
        private int previousElementIndex = 0;
        /** The node that points last returned node */
        private Node lastReturnedNode = null;
        /** Index of last returned node's element */
        private int lastReturnedNodeIndex = 0;
        /** Index of point */
        private int position;

        /**
         * One parameter constructor. Update nodes and indexes.
         * @param index of point.
         * @throws IndexOutOfBoundsException if the index is out of range (index lower than 0 || index greater than size()).
         */
        public LinkedArrayListIterator(int index)
        {
            if(index < 0 || index > size())
                throw new IndexOutOfBoundsException();

            position = index;
            updateCursor();
        }

        /**
         * Update cursor.
         */
        private void updateCursor()
        {
            previousNode = null;
            nextNode = head;

            for(int i=0 ; i < position ; ++i)
            {
                previousElementIndex = nextElementIndex++;

                if(nextElementIndex != 0 && previousNode != nextNode)
                    previousNode = nextNode;

                if(nextElementIndex == nextNode.size())
                {
                    nextNode = nextNode.next;
                    nextElementIndex = 0;
                }
            }
        }

        /**
         * Returns true if this list iterator has more elements when traversing the list in the forward direction.
         * @return true if the list iterator has more elements when traversing the list in the forward direction.
         */
        @Override
        public boolean hasNext() { return position < size(); }

        /**
         * Returns the next element in the list and advances the cursor position.
         * @return the next element in the list.
         * @throws NoSuchElementException if the iteration has no next element.
         */
        @Override
        public E next()
        {
            if(!hasNext())
                throw new NoSuchElementException();

            ++position;
            lastReturnedNode = previousNode = nextNode;
            lastReturnedNodeIndex = previousElementIndex = nextElementIndex;

            if(++nextElementIndex == nextNode.size())
            {
                nextNode = nextNode.next;
                nextElementIndex = 0;
            }

            return lastReturnedNode.at(lastReturnedNodeIndex);
        }

        /**
         * Returns true if this list iterator has more elements when traversing the list in the reverse direction.
         * @return true if the list iterator has more elements when traversing the list in the reverse direction.
         */
        @Override
        public boolean hasPrevious() { return position > 0; }

        /**
         * Returns the previous element in the list and moves the cursor position backwards.
         * @return the previous element in the list.
         * @throws NoSuchElementException if the iteration has no previous element.
         */
        @Override
        public E previous()
        {
            if(!hasPrevious())
                throw new NoSuchElementException();

            --position;
            lastReturnedNode = nextNode = previousNode;
            lastReturnedNodeIndex = nextElementIndex = previousElementIndex;

            if(--previousElementIndex < 0)
            {
                previousNode = previousNode.previous;
                if(previousNode != null)
                    previousElementIndex = previousNode.size()-1;
                else
                    previousElementIndex = 0;
            }

            return lastReturnedNode.at(lastReturnedNodeIndex);
        }

        /**
         * Returns the index of the element that would be returned by a subsequent call to next().
         * @return the index of the element that would be returned by a subsequent call to next, or list size if the list iterator is at the end of the list.
         */
        @Override
        public int nextIndex() { return position; }

        /**
         * Returns the index of the element that would be returned by a subsequent call to previous().
         * @return the index of the element that would be returned by a subsequent call to previous, or -1 if the list iterator is at the beginning of the list.
         */
        @Override
        public int previousIndex() { return position-1; }

        /**
         * Removes from the list the last element that was returned by next() or previous().
         * @throws IllegalStateException if neither next nor previous have been called, or remove or add have been called after the last call to next or previous.
         */
        @Override
        public void remove()
        {
            if(lastReturnedNode == null)
                throw new IllegalStateException();

            setListSize(size()-1);

            for(int i = lastReturnedNodeIndex ; i < lastReturnedNode.size()-1 ; ++i)
                lastReturnedNode.setContent(i,lastReturnedNode.at(i+1));
            lastReturnedNode.setSize(lastReturnedNode.size()-1);

            if(lastReturnedNode == previousNode && lastReturnedNodeIndex == previousElementIndex)
            {
                --position;
                --previousElementIndex;
            }

            if(previousElementIndex < 0)
            {
                previousNode = previousNode.previous;
                if(previousNode != null) previousElementIndex = previousNode.size()-1;
                else    previousElementIndex = 0;
            }

            if(lastReturnedNode.size() == 0)
            {
                if(lastReturnedNode.next != null)
                    lastReturnedNode.next.previous = lastReturnedNode.previous;

                if(lastReturnedNode.previous != null)
                    lastReturnedNode.previous.next = lastReturnedNode.next;
                else
                    head = head.next;

                if(lastReturnedNode.next == null && lastReturnedNode.previous == null)
                    head = null;
            }

            if(previousNode == null)
            {
                nextNode = head;
                nextElementIndex = 0;
            }
            else
            {
                nextNode = previousNode;
                nextElementIndex = previousElementIndex;

                if(++nextElementIndex == nextNode.size())
                {
                    nextNode = nextNode.next;
                    nextElementIndex = 0;
                }
            }

            lastReturnedNode = null;
            lastReturnedNodeIndex = 0;
        }

        /**
         * Replaces the last element returned by next() or previous() with the specified element.
         * @param e the element with which to replace the last element returned by next or previous
         * @throws ClassCastException if the class of the specified element prevents it from being added to this list
         * @throws IllegalStateException if neither next nor previous have been called, or remove or add have been called after the last call to next or previous.
         */
        @Override
        public void set(E e)
        {
            if(lastReturnedNode == null)
                throw new IllegalStateException();

            lastReturnedNode.setContent(lastReturnedNodeIndex,e);
        }

        /**
         * Inserts the specified element into the list.
         * @param e the element to insert.
         * @throws ClassCastException if the class of the specified element prevents it from being added to this list.
         */
        @Override
        public void add(E e)
        {
            ++position;
            setListSize(size()+1);

            if(previousNode == null)
            {
                if(head == null)
                    head = new Node();
                else if(head.size() == getMaxNodeCapacity())
                {
                    Node newNode = new Node(head,head.next);
                    head.next = newNode;
                    if(newNode.next != null)
                        newNode.next.previous = newNode;

                    newNode.setContent(0,head.at(head.size()-1));
                    newNode.setSize(1);

                    head.setSize(head.size()-1);
                }

                for(int i = head.size() ; i > 0 ; --i)
                    head.setContent(i,head.at(i-1));
                head.setContent(0,e);
                head.setSize(head.size()+1);

                previousNode = head;
                previousElementIndex = 0;
            }
            else if(nextNode == null)
            {
                if(previousNode.size() == getMaxNodeCapacity())
                {
                    Node newNode = new Node(previousNode,previousNode.next);
                    previousNode.next = newNode;
                    if(newNode.next != null)
                        newNode.next.previous = newNode;

                    newNode.setContent(0,e);
                    newNode.setSize(1);

                    previousNode = newNode;
                    previousElementIndex = 0;
                }
                else
                {
                    previousNode.setContent(++previousElementIndex,e);
                    previousNode.setSize(previousElementIndex+1);
                }
            }
            else if(previousNode == nextNode)
            {
                if(previousNode.size() == getMaxNodeCapacity())
                {
                    Node newNode = new Node(previousNode,previousNode.next);
                    previousNode.next = newNode;
                    if(newNode.next != null)
                        newNode.next.previous = newNode;

                    newNode.setContent(0,previousNode.at(previousNode.size()-1));
                    newNode.setSize(1);
                    previousNode.setSize(previousNode.size()-1);

                    for(int i = previousNode.size() ; i > previousElementIndex ; --i)
                        previousNode.setContent(i,previousNode.at(i-1));
                    previousNode.setContent(++previousElementIndex,e);
                    previousNode.setSize(previousNode.size()+1);
                }
                else
                {
                    for(int i =  previousNode.size() ; i > previousElementIndex ; --i)
                        nextNode.setContent(i,nextNode.at(i-1));

                    previousNode.setContent(++previousElementIndex,e);
                    previousNode.setSize(previousNode.size()+1);

                }
            }
            else
            {
                if(previousNode.size() == getMaxNodeCapacity())
                {
                    if(nextNode.size() == getMaxNodeCapacity())
                    {
                        Node newNode = new Node(previousNode,previousNode.next);
                        previousNode.next = newNode;
                        if(newNode.next != null)
                            newNode.next.previous = newNode;

                        newNode.setContent(0,e);
                        newNode.setSize(1);
                    }
                    else
                    {
                        for(int i =  nextNode.size() ; i > 0 ; --i)
                            nextNode.setContent(i,nextNode.at(i-1));
                        nextNode.setContent(0,e);
                        nextNode.setSize(nextNode.size()+1);

                        previousNode = nextNode;
                        previousElementIndex = nextElementIndex;
                    }
                }
                else
                {
                    previousNode.setContent(++previousElementIndex,e);
                    previousNode.setSize(previousElementIndex+1);
                }
            }

            if(previousNode == null)
            {
                nextNode = head;
                nextElementIndex = 0;
            }
            else
            {
                nextElementIndex = previousElementIndex;
                nextNode = previousNode;

                if(++nextElementIndex == nextNode.size())
                {
                    nextElementIndex = 0;
                    nextNode = nextNode.next;
                }
            }
        }
    }
}