import HW03.cse222.*;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class TestDriver
{
    public static void main(String[] args)
    {
        testLinkedArrayListWithoutUsingIterator();
        testLinkedArrayListWithUsingIterator();
    }

    public static void testLinkedArrayListWithoutUsingIterator()
    {
        System.out.println("---------------------------------------------------------------");
        System.out.println("T01 - Creating a character LinkedArrayList\n");
        LinkedArrayList<Character> list = new LinkedArrayList<>();
        System.out.println("Process is successful.");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T02 - 'int size()' method\n");
        System.out.println("When list is empty\n\tmethod will be called as list.size()");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("\nWhen list has some elements, method will be called as list.size()");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T03 - 'ListIterator<E> listIterator(int index)' method\n");
        System.out.println("When LinkedArrayList is empty, method will be called as list.listIterator(0)");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        ListIterator<Character> iter = list.listIterator(list.size());
        System.out.println("List iterator was in 0. index");
        System.out.println("\nWhen LinkedArrayList has some elements\n\tmethod will be called respectively as list.listIterator(0), list.listIterator(5), list.listIterator(10)");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(0);
        iter = list.listIterator(5);
        iter = list.listIterator(10);
        System.out.println("List iterator was in 0., 5. and 10. index");

        System.out.println("---------------------------------------------------------------");
        System.out.println("T04\n\nWhen LinkedArrayList is empty\n\tmethod will be called respectively as list.listIterator(-1), list.listIterator(1).\n\tExpected for IndexOutOfBoundsException to be thrown.");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            iter = list.listIterator(-1);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.listIterator(-1).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            iter = list.listIterator(1);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.listIterator(1).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("\nWhen LinkedArrayList has some elements\n\tmethod will be called respectively as list.listIterator(-1), list.listIterator(11).\n\tExpected for IndexOutOfBoundsException to be thrown.");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            iter = list.listIterator(-1);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.listIterator(-1).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            iter = list.listIterator(list.size()+1);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.listIterator(11).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T05 - Testing 'E get(int index)' method\n");
        System.out.println("When list have some elements\n\tmethod will be called respectively as list.get(0), list.get(5), list.get(9)");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("0. index : " + list.get(0));
        System.out.println("5. index : " + list.get(list.size()/2));
        System.out.println("9. index : " + list.get(list.size()-1));

        System.out.println("---------------------------------------------------------------");
        System.out.println("T06\n\nWhen list is empty\n\tmethod will be called respectively as list.get(-1), list.get(0), list.get(1).\n\tExpected for IndexOutOfBoundsException to be thrown.");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.get(-1));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.get(-1).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            System.out.println(list.get(0));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.get(0).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            System.out.println(list.get(1));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.get(1).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("\nWhen list has some elements\n\tmethod will be called respectively as list.get(-1), list.get(10).\n\tExpected for IndexOutOfBoundsException to be thrown.");

        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.get(-1));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.get(-1).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            System.out.println(list.get(10));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.get(10).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T07 - Testing 'void add(int index, E e)' method\n");
        System.out.println("When list is empty\n\tmethod will called as list.add(0,'X')");
        list = new LinkedArrayList<>();
        System.out.println("Before adding");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("After adding");
        list.add(0,'X');
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("\nWhen list has some elements\n\tmethod will be called respectively as list.add(0,'X'), list.add(5,'Y'), list.add(12,'Z')");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        System.out.println("Before adding");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("After adding");
        list.add(0,'X');
        list.add(5,'Y');
        list.add(12,'Z');
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T08\n\nWhen list is empty\n\tmethod will be called respectively as list.add(-1,'X'), list.add(1,'Y')\n\tExpected for IndexOutOfBoundsException to be thrown.");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            list.add(-1,'X');
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.add(-1,'X').\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            list.add(1,'Y');
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.add(1,'Y').\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("\nWhen list has some elements\n\tmethod will be called respectively as list.add(-1,'X'), list.add(11,'Y').\n\tExpected for IndexOutOfBoundsException to be thrown.");

        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        try
        {
            list.add(-1,'X');
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.add(-1,'X')\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            list.add(11,'Y');
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.add(11,'Y')\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T09 - Testing 'E remove(int index)' method\n");
        System.out.println("When list has some elements\n\tmethod will be called respectively as list.remove(0), list.remove(4), list.remove(7)");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Removed 0. index : " + list.remove(0));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Removed 4. index : " + list.remove(4));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Removed 7. index : " + list.remove(7));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T10\n\nWhen list is empty\n\tmethod will be called as list.remove(0).\n\tExpected for IndexOutOfBoundsException to be thrown.");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.remove(0));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.remove(0).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("\nWhen list has some elements\n\tmethod will be called respectively as list.remove(-1), list.remove(10).\n\tExpected for IndexOutOfBoundsException to be thrown.");

        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.remove(-1));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.remove(-1).\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            System.out.println(list.remove(10));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.remove(10).\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T11 - Testing 'E set(int index, E e)' method\n");
        System.out.println("When list has some elements\n\tmethod was called respectively as list.set(0,'X'), list.set(5,'Y'), list.set(9,'Z')");

        System.out.println("Before set method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("After set method : ");
        System.out.println("Previous 0. index : " + list.set(0,'X'));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("Before set method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("After set method : ");
        System.out.println("Previous 5. index : " + list.set(5,'Y'));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("Before set method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("After set method : ");
        System.out.println("Previous 9. index : " + list.set(9,'Z'));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T12\n\nWhen list is empty\n\tmethod will be called as list.set(0,'X').\n\tExpected for IndexOutOfBoundsException to be thrown.");
        list = new LinkedArrayList<>();
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.set(0,'X'));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.set(0,'X').\n\tIndexOutOfBoundsException was caught.");
        }

        System.out.println("\nWhen list has some elements\n\tmethod will be called respectively as list.set(-1,'X'), list.set(10,'Y').\n\tExpected for IndexOutOfBoundsException to be thrown.");

        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));

        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(list.set(-1,'X'));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.set(-1,'X').\n\tIndexOutOfBoundsException was caught.");
        }

        try
        {
            System.out.println(list.set(10,'Y'));
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("Method was called as list.set(10,'Y').\n\tIndexOutOfBoundsException was caught.");
        }
    }

    public static void testLinkedArrayListWithUsingIterator()
    {
        LinkedArrayList<Character> list;
        ListIterator<Character> iter;

        System.out.println("---------------------------------------------------------------");
        System.out.println("T13 - Testing 'boolean hasNext()' method\n");
        System.out.println("When list is empty and iterator is at index 0\n\tmethod will be called as iter.hasNext()");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("has next? " + iter.hasNext());

        System.out.println("\nWhen list has some elements and iterator respectively is at index 0, 5, 10\n\tmethod will be called as iter.hasNext().");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(0);
        System.out.println("0. index has next? " + iter.hasNext());
        iter = list.listIterator(5);
        System.out.println("5. index has next? " + iter.hasNext());
        iter = list.listIterator(10);
        System.out.println("10. index has next? " + iter.hasNext());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T14 - Testing 'boolean hasPrevious()' method\n");
        System.out.println("When list is empty and iterator is at index 0\n\tmethod will be called as iter.hasPrevious()");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("0. has previous ? " + iter.hasPrevious());

        System.out.println("\nWhen list has some elements and iterator is at index 0., 5., 10.\n\tmethod will be called as iter.hasPrevious()");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(0);
        System.out.println("0. has previous ? " + iter.hasPrevious());
        iter = list.listIterator(5);
        System.out.println("5. has previous ? " + iter.hasPrevious());
        iter = list.listIterator(10);
        System.out.println("10. has previous ? " + iter.hasPrevious());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T15 - Testing 'int nextIndex()' method\n");
        System.out.println("When list has some elements and iterator is at index 5\n\tmethod will be called as iter.nextIndex()");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(5);
        System.out.println("\nWhen iterator is at 5. index, next element's index : " + iter.nextIndex());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T16 - Testing 'int previousIndex()' method\n");
        System.out.println("When list has some elements and iterator is at index 5\n\tmethod will be called as iter.previousIndex()");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(5);
        System.out.println("\nWhen iterator is at 5. index, previous element's index : " + iter.previousIndex());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T17 - Testing 'E next()' method\n");
        System.out.println("When list has some elements, and iterator is at indexes 0., 5. and 9.\n\tmethod will be called as iter.next()");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(0);
        System.out.println("Iterator is at 0. index and value : " + iter.next());
        iter = list.listIterator(5);
        System.out.println("Iterator is at 5. index and value : " + iter.next());
        iter = list.listIterator(9);
        System.out.println("Iterator is at 9. index and value : " + iter.next());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T18\n\nWhen list is empty and iterator is at index 0\n\tmethod will be called as iter.next().\n\tExpected NoSuchElementException to be thrown.");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(iter.next());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("When iterator is at 0. index and list is empty\n\tmethod was called as iter.next().\n\tNoSuchElementException was caught.");
        }

        System.out.println("\nWhen list has some elements and iterator is at index 10\n\tmethod will be called as iter.next().\n\tExpected NoSuchElementException to be thrown. ");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        iter = list.listIterator(list.size());
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(iter.next());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("When iterator is at 10. index and list has some elements\n\tmethod was called as iter.next().\n\tNoSuchElementException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T19 - Testing 'E previous()' method\n");
        System.out.println("When list has some elements and iterator is at respectively index 1., 5. and 10.\n\tmethod will be as called iter.previous().");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(1);
        System.out.println("Iterator was at 1. index and value : " + iter.previous());
        iter = list.listIterator(list.size()/2);
        System.out.println("Iterator was at 5. index and value : " + iter.previous());
        iter = list.listIterator(list.size());
        System.out.println("Iterator was at 10. index and value : " + iter.previous());

        System.out.println("---------------------------------------------------------------");
        System.out.println("T20\n\nWhen list is empty and iterator is at index 0\n\tmethod will be called as iter.previous().\n\tExpected NoSuchElementException to be thrown.");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(iter.previous());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("When iterator is at 0. index and list is empty\n\tmethod was called as iter.previous().\n\tNoSuchElementException was caught.");
        }

        System.out.println("\nWhen list has some elements and iterator is at index 0\n\tmethod will be called as iter.previous().\n\tExpected for NoSuchElementException to be thrown.");
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        try
        {
            System.out.println(iter.previous());
        }
        catch(NoSuchElementException e)
        {
            System.out.println("When iterator is at 0. index and list has some elements\n\tmethod was called as iter.previous().\n\tNoSuchElementException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T21 - 'void add(E e)' method\n");
        System.out.println("When list is empty and iterator is at index 0\n\tmethod will be called consecutive.");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        System.out.println("Before adding method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        for(int i=0 ; i < 3 ; ++i)
            iter.add((char)('A'+i));
        System.out.println("After adding method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T22\n\nWhen list has some elements and iterator is respectively at indexes 0., 5, 12.\n\tmethod will be called as iter.add().");
        list = new LinkedArrayList<>();
        iter = list.listIterator(0);
        for(int i=0 ; i < 10 ; ++i)
            iter.add((char)('A'+i));
        System.out.println("Before adding method : ");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(0);
        iter.add('X');
        System.out.println("After adding method : ");
        System.out.println("Added 'X' 0. index of iterator");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(5);
        iter.add('Y');
        System.out.println("After adding method : ");
        System.out.println("Added 'Y' 5. index of iterator");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        iter = list.listIterator(12);
        iter.add('Z');
        System.out.println("After adding method : ");
        System.out.println("Added 'Z' 12. index of iterator");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T23 - Testing 'void remove()' method\n");
        System.out.println("When list has some elements and iterator is at index 0., 4. and 7.\n\tmethod will be called first iter.next() then iter.remove()");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(0);
        System.out.println("Before remove, iterator is at index 0 next item : " + iter.next());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(4);
        System.out.println("Before remove, iterator is at index 4 next item : " + iter.next());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(7);
        System.out.println("Before remove, iterator is at index 7 next item : " + iter.next());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T24\n\nWhen list has some elements and iterator is at index 10., 5. and 1.\n\tmethod will be called first iter.previous() then iter.remove()");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(10);
        System.out.println("Before remove, iterator is at index 10 previous item : " + iter.previous());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(5);
        System.out.println("Before remove, iterator is at index 5 previous item : " + iter.previous());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(1);
        System.out.println("Before remove, iterator is at index 1 previous item : " + iter.previous());
        iter.remove();
        System.out.println("After remove");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);


        System.out.println("---------------------------------------------------------------");
        System.out.println("T25\n\nWhen list has some elements and iterator is at index 0, 5, 10\n\tmethod will be called as iter.remove() before iter.next(), iter.previous() and iter.add() methods.\nExpected for IllegalStateException to be thrown");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(0);
        try
        {
            iter.remove();
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 0 and list has some elements\n\tmethod was called as iter.remove() before iter.next(), iter.previous() and iter.add() methods.\n\tIllegalStateException was caught.");
        }

        iter = list.listIterator(5);
        try
        {
            iter.remove();
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 5 and list has some elements\n\tmethod was called as iter.remove() before iter.next(), iter.previous() and iter.add() methods.\n\tIllegalStateException was caught.");
        }

        iter = list.listIterator(10);
        try
        {
            iter.remove();
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 10 and list has some elements\n\tmethod was called as iter.remove() before iter.next(), iter.previous() and iter.add() methods.\n\tIllegalStateException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T26 - Testing 'void set(E e)' method\n");
        System.out.println("When list has some elements and iterator is at index 0., 5 and 9.\n\titer.next() method will be called first and then iter.set('X').");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(0);
        System.out.println("Before setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Iterator is at index 0. iter.next() : " + iter.next());
        iter.set('X');
        System.out.println("After setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(5);
        System.out.println("Before setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Iterator is at index 5. iter.next() : " + iter.next());
        iter.set('X');
        System.out.println("After setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(9);
        System.out.println("Before setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);
        System.out.println("Iterator is at index 9. iter.next() : " + iter.next());
        iter.set('X');
        System.out.println("After setting");
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        System.out.println("---------------------------------------------------------------");
        System.out.println("T27\n\nWhen list has some elements and iterator is at indexes 0., 5. and 9.\n\tmethod will be called as iter.set('X') method before next, previous and add methods.\nExpected for IllegalStateException to be thrown.");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        System.out.println("Size of list : " + list.size() + " Elements : " + list);

        iter = list.listIterator(0);
        try
        {
            iter.set('X');
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 0 and list has some elements\n\tmethod was called as iter.set('X') before next, previous and iter.add methods.\n\tIllegalStateException was caught.");
        }

        iter = list.listIterator(5);
        try
        {
            iter.set('X');
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 5 and list has some elements\n\tmethod was called as iter.set('X') before next, previous and iter.add methods.\n\tIllegalStateException was caught.");
        }

        iter = list.listIterator(9);
        try
        {
            iter.set('X');
        }
        catch(IllegalStateException e)
        {
            System.out.println("When iterator is at index 9 and list has some elements\n\tmethod was called as iter.set('X') before next, previous and iter.add methods.\n\tIllegalStateException was caught.");
        }

        System.out.println("---------------------------------------------------------------");
        System.out.println("T28\n\nWhen list has some elements and iterator is at indexes 0.\n\tWhile iter has next element, iter.next() method will be called");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        iter = list.listIterator(0);
        System.out.println("Size of list : " + list.size());
        System.out.println("The list will be printed on the screen from start to end.");
        while(iter.hasNext())
            System.out.print(iter.next() + " ");
        System.out.print("\n");

        System.out.println("---------------------------------------------------------------");
        System.out.println("T29\n\nWhen list has some elements and iterator is at indexes 10.\n\tWhile iter has previous element, iter.previous() method will be called");
        list = new LinkedArrayList<>();
        for(int i=0 ; i < 10 ; ++i)
            list.add(i,(char)('A'+i));
        iter = list.listIterator(10);
        System.out.println("Size of list : " + list.size());
        System.out.println("The list will be printed on the screen from end to start.");
        while(iter.hasPrevious())
            System.out.print(iter.previous() + " ");
        System.out.print("\n");
    }
}