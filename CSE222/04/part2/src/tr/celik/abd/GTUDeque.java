package tr.celik.abd;

import java.util.AbstractCollection;
import java.util.Deque;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * A linear collection that supports element insertion and removal at both ends. The name deque is short for "double ended queue" and is usually pronounced "deck".
 * @param <E> the type of elements held in this collection
 * @author Abdullah CELIK
 */
public class GTUDeque<E> extends AbstractCollection<E> implements Deque<E>
{
    /** first node of this collection */
    private Node head = null;
    /** last node of this collection */
    private Node tail = null;
    /** size of this collection */
    private int count = 0;
    /** removed nodes of this collection to use again these nodes */
    private Node removedNode = null;
    /** size of removed nodes */
    private int sizeOfRemoved = 0;

    /**
     * Adds the new node to the first of this collection.
     * @param e new item of new node
     */
    private void linkFirst(E e)
    {
        Node node = (sizeOfRemovedNode() == 0 ? new Node(e) : removeFirstOfRemovedNode(e));

        ++count;
        node.next = head;
        if(head != null) head.prev = node;
        head = node;
        if(tail == null) tail = node;
    }

    /**
     * Adds the new node to the last of this collection.
     * @param e new item of new node
     */
    private void linkLast(E e)
    {
        Node node = (sizeOfRemovedNode() == 0 ? new Node(e) : removeFirstOfRemovedNode(e));

        ++count;
        node.prev = tail;
        if(tail != null) tail.next = node;
        tail = node;
        if(head == null) head = tail;
    }

    /**
     * Removes the node which the first of this collection.
     * @return item of first node of this collection
     */
    private E unlinkFirst()
    {
        E item = null;

        if(head != null)
        {
            Node temp = head;
            item = head.item;
            head = head.next;
            temp.next = null;

            if(head != null) head.prev = null;
            else    tail = null;

            --count;

            addFirstOfRemovedNode(temp);
        }

        return item;
    }

    /**
     * Removes the node which the last of this collection.
     * @return item of last node of this collection
     */
    private E unlinkLast()
    {
        E item = null;

        if(tail != null)
        {
            Node temp = tail;
            item = tail.item;
            tail = tail.prev;

            if(tail != null) tail.next = null;
            else    head = null;

            --count;
            addFirstOfRemovedNode(temp);
        }

        return item;
    }

    /**
     * Removes node this collection.
     * @param node to be deleted
     */
    private void unlink(Node node)
    {
        Node p = node.prev;
        Node n = node.next;

        if(p == null)
            unlinkFirst();
        else if(n == null)
            unlinkLast();
        else
        {
            p.next = n;
            n.prev = p;
            --count;
            addFirstOfRemovedNode(node);
        }
    }

    /**
     * Adds a new node to the first of removedNode.
     * @param node to be added
     */
    private void addFirstOfRemovedNode(Node node)
    {
        node.next = removedNode;
        removedNode = node;
        ++sizeOfRemoved;
    }

    /**
     * Removes the node which the first of removedNode.
     * This method does not check whether there is a node.
     * @param newItem new item for returned node
     * @return first node of removedNode
     */
    private Node removeFirstOfRemovedNode(E newItem)
    {
        Node node = removedNode;
        node.item = newItem;

        removedNode = removedNode.next;
        node.next = null;
        --sizeOfRemoved;

        return node;
    }

    /**
     * Returns an iterator over the elements in this deque in proper sequence.
     * The elements will be returned in order from first (head) to last (tail).
     * @return an iterator over the elements in this deque in proper sequence
     */
    @Override
    public Iterator<E> iterator() { return new Iter(); }

    /**
     * Returns an iterator over the elements in this deque in reverse sequential order.
     * The elements will be returned in order from last (tail) to first (head).
     * @return an iterator over the elements in this deque in reverse sequence
     */
    @Override
    public Iterator<E> descendingIterator() { return new DescendingIter(); }

    /**
     * Inserts the specified element at the front of this deque.
     * This method is equivalent to offerFirst(E).
     * @param e the element to add
     */
    @Override
    public void addFirst(E e) { offerFirst(e); }

    /**
     * Inserts the specified element at the end of this deque.
     * This method is equivalent to offerLast(E).
     * @param e the element to add
     */
    @Override
    public void addLast(E e) { offerLast(e); }

    /**
     * Inserts the specified element at the front of this deque.
     * @param e the element to add
     * @return true if the element was added to this deque, else false
     */
    @Override
    public boolean offerFirst(E e)
    {
        linkFirst(e);
        return true;
    }

    /**
     * Inserts the specified element at the end of this deque.
     * @param e the element to add
     * @return true if the element was added to this deque, else false
     */
    @Override
    public boolean offerLast(E e)
    {
        linkLast(e);
        return true;
    }

    /**
     * Retrieves and removes the first element of this deque.
     * This method differs from pollFirst only in that it throws an exception if this deque is empty.
     * @return the head of this deque
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E removeFirst()
    {
        E item = pollFirst();

        if(item == null)
            throw new NoSuchElementException();

        return item;
    }

    /**
     * Retrieves and removes the last element of this deque.
     * This method differs from pollLast only in that it throws an exception if this deque is empty.
     * @return the tail of this deque
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E removeLast()
    {
        E item = pollLast();

        if(item == null)
            throw new NoSuchElementException();

        return item;
    }

    /**
     * Retrieves and removes the first element of this deque, or returns null if this deque is empty.
     * @return the head of this deque, or null if this deque is empty
     */
    @Override
    public E pollFirst() { return unlinkFirst(); }

    /**
     * Retrieves and removes the last element of this deque, or returns null if this deque is empty.
     * @return the tail of this deque, or null if this deque is empty
     */
    @Override
    public E pollLast() { return unlinkLast(); }

    /**
     * Retrieves, but does not remove, the first element of this deque.
     * This method differs from peekFirst only in that it throws an exception if this deque is empty.
     * @return the head of this deque
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E getFirst()
    {
        E item = peekFirst();

        if(item == null)
            throw new NoSuchElementException();

        return item;
    }

    /**
     * Retrieves, but does not remove, the last element of this deque.
     * This method differs from peekLast only in that it throws an exception if this deque is empty.
     * @return the tail of this deque
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E getLast()
    {
        E item = peekLast();

        if(item == null)
            throw new NoSuchElementException();

        return item;
    }

    /**
     * Retrieves, but does not remove, the first element of this deque, or returns null if this deque is empty.
     * @return the head of this deque, or null if this deque is empty
     */
    @Override
    public E peekFirst() { return head == null ? null : head.item; }

    /**
     * Retrieves, but does not remove, the last element of this deque, or returns null if this deque is empty.
     * @return the tail of this deque, or null if this deque is empty
     */
    @Override
    public E peekLast() { return tail == null ? null : tail.item; }

    /**
     * Removes the first occurrence of the specified element from this deque.
     * If the deque does not contain the element, it is unchanged.
     * @param o element to be removed from this deque, if present
     * @return true if an element was removed as a result of this call
     */
    @Override
    public boolean removeFirstOccurrence(Object o)
    {
        for(Iterator<E> iter = iterator() ; iter.hasNext() ;)
            if(iter.next() == o)
            {
                iter.remove();
                return true;
            }

        return false;
    }

    /**
     * Removes the last occurrence of the specified element from this deque.
     * If the deque does not contain the element, it is unchanged.
     * @param o element to be removed from this deque, if present
     * @return true if an element was removed as a result of this call
     */
    @Override
    public boolean removeLastOccurrence(Object o)
    {
        for(Iterator<E> iter = descendingIterator() ; iter.hasNext() ;)
            if(iter.next() == o)
            {
                iter.remove();
                return true;
            }

        return false;
    }

    /**
     * Inserts the specified element into the queue represented by this deque (in other words, at the tail of this deque).
     * This method is equivalent to offerLast(E).
     * @param e the element to add
     * @return true if the element was added to this deque, else false
     */
    @Override
    public boolean add(E e) { return offerLast(e); }

    /**
     * Inserts the specified element into the queue represented by this deque (in other words, at the tail of this deque).
     * This method is equivalent to offerLast(E).
     * @param e the element to add
     * @return true if the element was added to this deque, else false
     */
    @Override
    public boolean offer(E e) { return offerLast(e); }

    /**
     * Retrieves and removes the head of the queue represented by this deque (in other words, the first element of this deque).
     * This method differs from poll only in that it throws an exception if this deque is empty.
     * This method is equivalent to removeFirst().
     * @return the head of the queue represented by this deque
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E remove() { return removeFirst(); }

    /**
     * Retrieves and removes the head of the queue represented by this deque (in other words, the first element of this deque), or returns null if this deque is empty.
     * This method is equivalent to pollFirst().
     * @return the first element of this deque, or null if this deque is empty
     */
    @Override
    public E poll() { return pollFirst(); }

    /**
     * Retrieves, but does not remove, the head of the queue represented by this deque (in other words, the first element of this deque).
     * This method differs from peek only in that it throws an exception if this deque is empty.
     * This method is equivalent to getFirst().
     * @return the head of the queue represented by this deque
     */
    @Override
    public E element() { return getFirst(); }

    /**
     * Retrieves, but does not remove, the head of the queue represented by this deque (in other words, the first element of this deque), or returns null if this deque is empty.
     * This method is equivalent to peekFirst().
     * @return the head of the queue represented by this deque, or null if this deque is empty
     */
    @Override
    public E peek() { return peekFirst(); }

    /**
     * Pushes an element onto the stack represented by this deque (in other words, at the head of this deque).
     * This method is equivalent to offerFirst(E).
     * @param e the element to push
     */
    @Override
    public void push(E e) { offerFirst(e); }

    /**
     * Pops an element from the stack represented by this deque.
     * In other words, removes and returns the first element of this deque.
     * This method is equivalent to removeFirst().
     * @return the element at the front of this deque (which is the top of the stack represented by this deque)
     * @throws NoSuchElementException if this deque is empty
     */
    @Override
    public E pop() { return removeFirst(); }

    /**
     * Returns the number of elements in this deque.
     * @return the number of elements in this deque
     */
    @Override
    public int size() { return count; }

    /**
     * Returns the number of elements in removed node.
     * @return the number of elements in removed node
     */
    public int sizeOfRemovedNode() { return sizeOfRemoved; }

    /**
     * Inner node class for GTUDeque class. This class keeps item, previous point and next point.
     */
    private final class Node
    {
        // these fields are package private.
        /** Item of this node*/
        E item;
        /** previous point of this node */
        Node prev;
        /** next point of this node */
        Node next;

        /**
         * One parameter constructor. Constructs a node which has a item.
         * @param item new item of the node
         */
        public Node(E item) { this.item = item; }
    }

    /**
     * AbstractIter abstract class for Iterator and DescendingIterator class.
     * Implements Iterator interface.
     */
    private abstract class AbstractIter implements Iterator<E>
    {
        /** next point of iterator */
        private Node next;
        /** last returned point of iterator */
        private Node lastReturned = null;

        /**
         * No parameter constructor. Constructs next point as first node.
         */
        public AbstractIter() { next = firstNode(); }

        /**
         * Returns first node of collection.
         * @return first node of collection
         */
        abstract Node firstNode();

        /**
         * Returns next point of node.
         * @param node to point next node
         * @return next point of node
         */
        abstract Node nextNode(Node node);

        /**
         * Returns true if the iteration has more elements.
         * @return true if the iteration has more elements
         */
        @Override
        public boolean hasNext() { return next != null; }

        /**
         * Returns the next element in the iteration.
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public E next()
        {
            if(next == null)
                throw new NoSuchElementException();

            lastReturned = next;
            E item = next.item;
            next = nextNode(next);

            return item;
        }

        /**
         * Removes from the underlying collection the last element returned by this iterator.
         * This method can be called only once per call to next().
         * The behavior of an iterator is unspecified if the underlying collection is modified while the iteration is in progress in any way other than by calling this method.
         * @throws IllegalStateException if the next method has not yet been called, or the remove method has already been called after the last call to the next method
         */
        @Override
        public void remove()
        {
            if(lastReturned == null)
                throw new IllegalStateException();

            unlink(lastReturned);
            lastReturned = null;
        }
    }

    /**
     * Iterator over the elements in this deque in proper sequence. The elements will be in order from first (head) to last (tail).
     */
    private class Iter extends AbstractIter
    {
        /**
         * Returns head of this collection.
         * @return head of this collection
         */
        Node firstNode() { return head; }

        /**
         * Returns next point of node.
         * @param node to point next node
         * @return next point of node
         */
        Node nextNode(Node node) { return node.next; }
    }

    /**
     * Iterator over the elements in this deque in reverse sequential order. The elements will be in order from last (tail) to first (head).
     */
    private class DescendingIter extends AbstractIter
    {
        /**
         * Returns tail of this collection.
         * @return tail of this collection
         */
        Node firstNode() { return tail; }

        /**
         * Returns next point of node.
         * @param node to point next node
         * @return next point of node
         */
        Node nextNode(Node node) { return node.prev; }
    }
}