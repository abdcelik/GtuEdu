import tr.celik.abd.*;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class TestDriver
{
    public static void main(String[] args)
    {
        testGTUDeque();
        testGTUDequeWithIterator();
        testRemovedNodeOfGtuDeque();
    }

    public static void testGTUDeque()
    {
        GTUDeque<Character> deque;
        Iterator<Character> iter;

        System.out.println("Testing methods of GTUDeque\n");

        System.out.println("-----------------------------------------------");
        System.out.println("D01 - int size() method of GTUDeque class\n");
        System.out.println("When deque is empty");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("\nWhen deque has some elements");
        for(int i=0 ; i < 10 ; ++i)
            deque.addLast((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D02 - Iterator<E> iterator() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.iterator()");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("Iterator will created successfully!");
        System.out.println("\nWhen deque has some elements, method will be called as\n\tdeque.iterator()");
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("Iterator will created successfully!");

        System.out.println("-----------------------------------------------");
        System.out.println("D03 - Iterator<E> descendingIterator() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.descendingIterator()");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        System.out.println("Descending Iterator will created successfully!");
        System.out.println("\nWhen deque has some elements, method will be called as\n\tdeque.descendingIterator()");
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("Descending Iterator will created successfully!");

        System.out.println("-----------------------------------------------");
        System.out.println("D04 - boolean add(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively\n\t deque.add('X'), deque.add('Y'), deque.add('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before add method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.add('X');
        deque.add('Y');
        deque.add('Z');
        System.out.println("After add method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("\nWhen deque has some elements, method will be called respectively\n\t deque.add('K'), deque.add('L'), deque.add('M')");
        System.out.println("Before add method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.add('K');
        deque.add('L');
        deque.add('M');
        System.out.println("After add method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D05 - void addFirst(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty method will be called respectively as \n\tdeque.addFirst('X'), deque.addFirst('Y'), deque.addFirst('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before addFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.addFirst('X');
        deque.addFirst('Y');
        deque.addFirst('Z');
        System.out.println("After addFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.addFirst('K'), deque.addFirst('L'), deque.addFirst('M')");
        System.out.println("Before addFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.addFirst('K');
        deque.addFirst('L');
        deque.addFirst('M');
        System.out.println("After addFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D06 - void addLast(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.addLast('X'), deque.addLast('Y'), deque.addLast('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before addLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.addLast('X');
        deque.addLast('Y');
        deque.addLast('Z');
        System.out.println("After addLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.addLast('K'), deque.addLast('L'), deque.addLast('M')");
        System.out.println("Before addLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.addLast('K');
        deque.addLast('L');
        deque.addLast('M');
        System.out.println("After addLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D07 - boolean offer(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.offer('X'), deque.offer('Y'), deque.offer('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before offer method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offer 'X' result : " + deque.offer('X'));
        System.out.println("offer 'Y' result : " + deque.offer('Y'));
        System.out.println("offer 'Z' result : " + deque.offer('Z'));
        System.out.println("After offer method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.offer('K'), deque.offer('L'), deque.offer('M')");
        System.out.println("Before offer method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offer 'K' result : " + deque.offer('K'));
        System.out.println("offer 'L' result : " + deque.offer('L'));
        System.out.println("offer 'M' result : " + deque.offer('M'));
        System.out.println("After offer method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D08 - boolean offerFirst(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.offerFirst('X'), deque.offerFirst('Y'), deque.offerFirst('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before offerFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offerFirst 'X' result : " + deque.offerFirst('X'));
        System.out.println("offerFirst 'Y' result : " + deque.offerFirst('Y'));
        System.out.println("offerFirst 'Z' result : " + deque.offerFirst('Z'));
        System.out.println("After offerFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.offerFirst('K'), deque.offerFirst('L'), deque.offerFirst('M')");
        System.out.println("Before offerFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offerFirst 'K' result : " + deque.offerFirst('K'));
        System.out.println("offerFirst 'L' result : " + deque.offerFirst('L'));
        System.out.println("offerFirst 'M' result : " + deque.offerFirst('M'));
        System.out.println("After offerFirst method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D09 - boolean offerLast(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.offerLast('X'), deque.offerLast('Y'), deque.offerLast('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before offerLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offerLast 'X' result : " + deque.offerLast('X'));
        System.out.println("offerLast 'Y' result : " + deque.offerLast('Y'));
        System.out.println("offerLast 'Z' result : " + deque.offerLast('Z'));
        System.out.println("After offerLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.offerLast('K'), deque.offerLast('L'), deque.offerLast('M')");
        System.out.println("Before offerLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("offerLast 'K' result : " + deque.offerLast('K'));
        System.out.println("offerLast 'L' result : " + deque.offerLast('L'));
        System.out.println("offerLast 'M' result : " + deque.offerLast('M'));
        System.out.println("After offerLast method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D10 - E element() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called respectively as\n\tdeque.element()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.element());

        System.out.println("-----------------------------------------------");
        System.out.println("D11 - E element() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.element(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Element : " + deque.element());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.element() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D12 - E getFirst() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called respectively as\n\tdeque.getFirst()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.getFirst());

        System.out.println("-----------------------------------------------");
        System.out.println("D13 - E getFirst() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.getFirst(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Element : " + deque.getFirst());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.getFirst() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D14 - E getLast() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called respectively as\n\tdeque.getLast()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.getLast());

        System.out.println("-----------------------------------------------");
        System.out.println("D15 - E getLast() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.getLast(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Element : " + deque.getLast());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.getLast() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D16 - E peek() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.peek(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peek());
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.peek()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peek());

        System.out.println("-----------------------------------------------");
        System.out.println("D17 - E peekFirst() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.peekFirst(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peekFirst());
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.peekFirst()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peekFirst());

        System.out.println("-----------------------------------------------");
        System.out.println("D18 - E peekLast() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called respectively as\n\tdeque.peekLast(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peekLast());
        System.out.println("\nWhen deque has some elements, method will be called respectively as\n\tdeque.peekLast()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.peekLast());

        System.out.println("-----------------------------------------------");
        System.out.println("D19 - E remove() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called three times as\n\tdeque.remove()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Removed item : " + deque.remove());
        System.out.println("Removed item : " + deque.remove());
        System.out.println("Removed item : " + deque.remove());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D20 - E remove() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.remove(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Removed item : " + deque.remove());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.remove() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D21 - E removeFirst() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called three times as\n\tdeque.removeFirst()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Removed item : " + deque.removeFirst());
        System.out.println("Removed item : " + deque.removeFirst());
        System.out.println("Removed item : " + deque.removeFirst());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D22 - E removeFirst() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.removeFirst(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Removed item : " + deque.removeFirst());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.removeFirst() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D23 - E removeLast() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called three times as\n\tdeque.removeLast()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Removed item : " + deque.removeLast());
        System.out.println("Removed item : " + deque.removeLast());
        System.out.println("Removed item : " + deque.removeLast());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D24 - E removeLast() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.removeLast(). Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Removed item : " + deque.removeLast());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.removeLast() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D25 - E poll() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.poll(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.poll());
        System.out.println("\nWhen deque has some elements, method will be called three times as\n\tdeque.poll()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.poll());
        System.out.println("Element : " + deque.poll());
        System.out.println("Element : " + deque.poll());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D26 - E pollFirst() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.pollFirst(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.pollFirst());
        System.out.println("\nWhen deque has some elements, method will be called three times as\n\tdeque.pollFirst()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.pollFirst());
        System.out.println("Element : " + deque.pollFirst());
        System.out.println("Element : " + deque.pollFirst());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D27 - E pollLast() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.pollLast(). Expected return null");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.pollLast());
        System.out.println("\nWhen deque has some elements, method will be called three times as\n\tdeque.pollLast()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Element : " + deque.pollLast());
        System.out.println("Element : " + deque.pollLast());
        System.out.println("Element : " + deque.pollLast());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D28 - boolean remove(Object o) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.remove('X')");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("remove 'X' result : " + deque.remove('X'));
        System.out.println("\nWhen deque has some elements, method will be called respectively\n\tdeque.remove('B'), deque.remove('X'), deque.remove('D'), deque.remove('B')");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("remove 'B' result : " + deque.remove('B'));
        System.out.println("remove 'X' result : " + deque.remove('X'));
        System.out.println("remove 'D' result : " + deque.remove('D'));
        System.out.println("remove 'B' result : " + deque.remove('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D29 - boolean removeFirstOccurrence(Object o) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.removeFirstOccurrence('X')");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Remove 'X' result : " + deque.removeFirstOccurrence('X'));
        System.out.println("\nWhen deque has some elements, method will be called");
        deque = new GTUDeque<>();
        deque.add('A');
        deque.add('B');
        deque.add('A');
        deque.add('D');
        deque.add('B');
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'D' result : " + deque.removeFirstOccurrence('D'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'X' result : " + deque.removeFirstOccurrence('X'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'A' result : " + deque.removeFirstOccurrence('A'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'B' result : " + deque.removeFirstOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'A' result : " + deque.removeFirstOccurrence('A'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'B' result : " + deque.removeFirstOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeFirstOccurrence 'B' result : " + deque.removeFirstOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D30 - boolean removeLastOccurrence(Object o) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.removeLastOccurrence('X')");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Remove 'X' result : " + deque.removeLastOccurrence('X'));
        System.out.println("\nWhen deque has some elements, method will be called");
        deque = new GTUDeque<>();
        deque.add('A');
        deque.add('B');
        deque.add('A');
        deque.add('D');
        deque.add('B');
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'D' result : " + deque.removeLastOccurrence('D'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'X' result : " + deque.removeLastOccurrence('X'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'A' result : " + deque.removeLastOccurrence('A'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'B' result : " + deque.removeLastOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'A' result : " + deque.removeLastOccurrence('A'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'B' result : " + deque.removeLastOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("removeLastOccurrence 'B' result : " + deque.removeLastOccurrence('B'));
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D31 - boolean contains(Object o) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.contains('X')");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Is it contain ? " + deque.contains('X'));
        System.out.println("\nWhen deque has some elements, method will be called as\n\tdeque.contains('C')");
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Is it contain ? " + deque.contains('C'));

        System.out.println("-----------------------------------------------");
        System.out.println("D32 - E pop() method of GTUDeque class\n");
        System.out.println("When deque has some elements, method will be called three times as\n\tdeque.pop()");
        deque = new GTUDeque<>();
        for(int i=0 ; i < 5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        System.out.println("Pop method return : " + deque.pop());
        System.out.println("Pop method return : " + deque.pop());
        System.out.println("Pop method return : " + deque.pop());
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("-----------------------------------------------");
        System.out.println("D33 - E pop() method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called as\n\tdeque.pop()");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        try
        {
            System.out.println("Pop method return : " + deque.pop());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as deque.pop() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("D34 - void push(E e) method of GTUDeque class\n");
        System.out.println("When deque is empty, method will be called three times as\n\tdeque.push('X'), deque.push('Y'), deque.push('Z')");
        deque = new GTUDeque<>();
        System.out.println("Before push method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        deque.push('X');
        deque.push('Y');
        deque.push('Z');
        System.out.println("After push method");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
    }

    public static void testGTUDequeWithIterator()
    {
        GTUDeque<Character> deque;
        Iterator<Character> iter;

        System.out.println("\nTesting iterator class' methods.\n*** FIRSTLY Iterator<E> iterator() METHOD WILL BE CALLED EACH TEST ***");
        System.out.println("-----------------------------------------------");
        System.out.println("I01 - boolean hasNext() method of Iterator class\n");
        System.out.println("When deque is empty,\n\titerator method will be called as iter.hasNext()");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("hasNext method result : " + iter.hasNext());
        System.out.println("\nWhen deque has some elements,\n\titerator method will be called as iter.hasNext()");
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("hasNext method result : " + iter.hasNext());

        System.out.println("-----------------------------------------------");
        System.out.println("I02 - E next() method of Iterator class\n");
        System.out.println("When deque has some elements,\n\titerator method will be called three times as iter.next()");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("next method result : " + iter.next());
        System.out.println("next method result : " + iter.next());
        System.out.println("next method result : " + iter.next());

        System.out.println("\nI03 - E next() method of Iterator class\n");
        System.out.println("When deque is empty,\n\titerator method will be called as iter.next()");
        System.out.println("Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        try
        {
            System.out.println("hasNext method result : " + iter.next());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as iter.next() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("I04 - void remove() method of Iterator class\n");
        System.out.println("When deque has some elements\n\titer.next() method will be called\n\tthen void remove() method will be called");
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("\nI05 - void remove() method of Iterator class\n");
        System.out.println("When deque has some elements\n\titer.remove() method will be called before iter.add() method");
        System.out.println("Expected IllegalStateException to be thrown");
        deque = new GTUDeque<>();
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();

        try
        {
            iter.remove();
        }
        catch(IllegalStateException e)
        {
            System.out.println("Method will be called as iter.remove() and\n\tIllegalStateException was caught");
        }


        System.out.println("\n\nTesting iterator class' methods.\n*** FIRSTLY Iterator<E> descendingIterator() METHOD WILL BE CALLED EACH TEST ***");
        System.out.println("-----------------------------------------------");

        System.out.println("DI01 - boolean hasNext() method of Iterator class\n");
        System.out.println("When deque is empty,\n\titerator method will be called as iter.hasNext()");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        System.out.println("hasNext method result : " + iter.hasNext());
        System.out.println("\nWhen deque has some elements,\n\titerator method will be called as iter.hasNext()");
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        System.out.println("hasNext method result : " + iter.hasNext());

        System.out.println("-----------------------------------------------");
        System.out.println("DI02 - E next() method of Iterator class\n");
        System.out.println("When deque has some elements,\n\titerator method will be called three times as iter.next()");
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        System.out.println("next method result : " + iter.next());
        System.out.println("next method result : " + iter.next());
        System.out.println("next method result : " + iter.next());

        System.out.println("\nDI03 - E next() method of Iterator class\n");
        System.out.println("When deque is empty,\n\titerator method will be called as iter.next()");
        System.out.println("Expected NoSuchElementException to be thrown");
        deque = new GTUDeque<>();
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        try
        {
            System.out.println("hasNext method result : " + iter.next());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("Method will be called as iter.next() and\n\tNoSuchElementException was caught");
        }

        System.out.println("-----------------------------------------------");
        System.out.println("DI04 - void remove() method of Iterator class\n");
        System.out.println("When deque has some elements\n\titer.next() method will be called\n\tthen void remove() method will be called");
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Next item : " + iter.next());
        iter.remove();
        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("\nDI05 - void remove() method of Iterator class\n");
        System.out.println("When deque has some elements\n\titer.remove() method will be called before iter.add() method");
        System.out.println("Expected IllegalStateException to be thrown");
        deque = new GTUDeque<>();
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();

        try
        {
            iter.remove();
        }
        catch(IllegalStateException e)
        {
            System.out.println("Method will be called as iter.remove() and\n\tIllegalStateException was caught");
        }
        System.out.println("\n\n TESTING ITERATOR METHODS IS FINISHED!\n\n");


        System.out.println("M01\n");
        System.out.println("When deque has some elements,\n\tfirstly iterator() method will be called\n\tthen while iterator has next element, next method will be called");
        deque = new GTUDeque<>();
        for(int i=0 ; i<10 ; ++i)
            deque.add((char)('A'+i));
        iter = deque.iterator();

        while(iter.hasNext())
            System.out.print(iter.next() + " ");
        System.out.print("\n");

        System.out.println("\nM02\n");
        System.out.println("When deque has some elements,\n\tfirstly descendingIterator() method will be called\n\tthen while iterator has next element, next method will be called");
        iter = deque.descendingIterator();

        while(iter.hasNext())
            System.out.print(iter.next() + " ");
        System.out.print("\n");

        System.out.println("\nM03\n");
        System.out.println("When deque has some elements,\n\tfirstly iterator() method will be called\n\tthen while iterator has next element\n\tnext and remove method will be called");
        deque = new GTUDeque<>();
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.iterator();

        while(iter.hasNext())
        {
            System.out.println("Next Item : " + iter.next());
            iter.remove();
        }

        System.out.println("Size : " + deque.size() + " Element : " + deque);

        System.out.println("\nM04\n");
        System.out.println("When deque has some elements,\n\tfirstly descendingIterator() method will be called\n\tthen while iterator has next element\n\tnext and remove method will be called");
        deque = new GTUDeque<>();
        for(int i=0 ; i<5 ; ++i)
            deque.add((char)('A'+i));
        System.out.println("Size : " + deque.size() + " Element : " + deque);
        iter = deque.descendingIterator();

        while(iter.hasNext())
        {
            System.out.println("Next Item : " + iter.next());
            iter.remove();
        }
        System.out.println("Size : " + deque.size() + " Element : " + deque);
    }

    public static void testRemovedNodeOfGtuDeque()
    {
        GTUDeque<Character> deque = new GTUDeque<>();

        System.out.println("Testing removed node size using adding or removing methods\n");
        System.out.println("S01\n");
        System.out.println("Before process'");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque + "\n");

        deque.offer('A');
        System.out.println("offer method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);

        deque.offerFirst('B');
        System.out.println("offerFirst method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);

        deque.removeLast();
        System.out.println("removeLast method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);

        deque.remove();
        System.out.println("remove method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);

        deque.add('X');
        System.out.println("add method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);

        deque.addFirst('Y');
        System.out.println("addFirst method will be called");
        System.out.println("Size of deque : " + deque.size() + " | Size of removedNode : " + deque.sizeOfRemovedNode());
        System.out.println("Element : " + deque);
    }
}