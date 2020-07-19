import com.abdcelik.*;

public class DriverMain
{
    public static void main(String[] argv)
    {
        SkipList<Integer> list;

        System.out.println("------------------------------------");
        System.out.println("TEST01");
        System.out.println("When maximum number of element in a node is lower than 1");

        try
        {
            System.out.println("Maximum number of element: -5");
            list = new SkipList<>(-5);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println(e.getMessage());
            System.out.println("IndexOutOfBoundException was caught!");
        }

        try
        {
            System.out.println("\nMaximum number of element: 0");
            list = new SkipList<>(0);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println(e.getMessage());
            System.out.println("IndexOutOfBoundException was caught!");
        }

        System.out.println("\nTEST02");
        System.out.println("When maximum number of element in a node is greater or equal than 1");

        System.out.println("Maximum number of element: 1");
        list = new SkipList<>(1);
        System.out.println("Creating an skip list is successful!");

        System.out.println("\nMaximum number of element: 4");
        list = new SkipList<>(4);
        System.out.println("Creating an skip list is successful!");

        System.out.println("\n------------------------------------");
        System.out.println("Testing boolean add(E item) method");
        System.out.println("TEST03");
        System.out.println("When skip list is empty, method will be called respectively as\n\tlist.add(10),list.add(20),list.add(5)");
        System.out.println("Before adding, list:");
        System.out.println("List: " + list);

        System.out.println("Adding 10: " + list.add(10));
        System.out.println("Adding 20: " + list.add(20));
        System.out.println("Adding 5: " + list.add(5));

        System.out.println("After adding, list:");
        System.out.println("List: " + list);

        System.out.println("\nTEST04");
        System.out.println("When adding elements to skip list and node exceeds maximum node capacity");
        System.out.println("Before adding, list:");
        System.out.println("List: " + list);

        System.out.println("Adding 30: " + list.add(30));
        System.out.println("List: " + list);
        System.out.println("Adding 40: " + list.add(40));
        System.out.println("List: " + list);
        System.out.println("Adding 25: " + list.add(25));
        System.out.println("List: " + list);
        System.out.println("Adding 1: " + list.add(1));
        System.out.println("List: " + list);
        System.out.println("Adding 3: " + list.add(3));
        System.out.println("List: " + list);
        System.out.println("Adding 6: " + list.add(6));
        System.out.println("List: " + list);
        System.out.println("Adding 8: " + list.add(8));
        System.out.println("List: " + list);
        System.out.println("Adding 7: " + list.add(7));
        System.out.println("List: " + list);
        System.out.println("Adding 45: " + list.add(45));
        System.out.println("List: " + list);

        System.out.println("\nTEST05");
        System.out.println("When adding null element to skip list, method will be called as\n\tlist.add(null)");

        try
        {
            list.add(null);
        }
        catch(NullPointerException e)
        {
            System.out.println("NullPointerException was caught!");
        }

        System.out.println("\n------------------------------------");
        System.out.println("Testing E find(E target) method");
        System.out.println("TEST06");
        System.out.println("When skip list contains item, method will be called as\n\tlist.find(5), list.find(25), list.find(45)");
        System.out.println("List: " + list);
        System.out.println("Find 5: " + list.find(5));
        System.out.println("Find 25: " + list.find(25));
        System.out.println("Find 45: " + list.find(45));

        System.out.println("\nTEST07");
        System.out.println("When skip list doesn't contain item, method will be called as\n\tlist.find(0), list.find(50)");
        System.out.println("List: " + list);
        System.out.println("Find 0: " + list.find(0));
        System.out.println("Find 50: " + list.find(50));

        System.out.println("\nTEST08");
        System.out.println("When searching null element, method will be called as\n\tlist.find(null)");

        try
        {
            list.find(null);
        }
        catch(NullPointerException e)
        {
            System.out.println("NullPointerException was caught");
        }

        System.out.println("\n------------------------------------");
        System.out.println("Testing boolean remove(E item) method");
        System.out.println("TEST09");
        System.out.println("When a node contains greater than minimum element in a node, method will be called as\n\tlist.remove(10), list.remove(40)");
        System.out.println("Before removing, list:");
        System.out.println(list);
        System.out.println("Removing 10: " + list.remove(10));
        System.out.println("After removing, list:");
        System.out.println(list);
        System.out.println("Removing 40: " + list.remove(40));
        System.out.println("After removing, list:");
        System.out.println(list);

        System.out.println("\nTEST10");
        System.out.println("When a node contains equal than minimum element in a node, method will be called respectively as\n\tlist.remove(1), list.remove(7), list.remove(45)");
        System.out.println("Before removing, list:");
        System.out.println(list);
        System.out.println("Removing 1: " + list.remove(1));
        System.out.println("After removing, list:");
        System.out.println(list);
        System.out.println("Removing 7: " + list.remove(7));
        System.out.println("After removing, list:");
        System.out.println(list);
        System.out.println("Removing 45: " + list.remove(45));
        System.out.println("After removing, list:");
        System.out.println(list);

        System.out.println("\nTEST11");
        System.out.println("When null elements to be removed, remove method will be called as\n\tlist.remove(null)");
        try
        {
            list.remove(null);
        }
        catch(NullPointerException e)
        {
            System.out.println("NullPointerException was caught!");
        }
    }
}