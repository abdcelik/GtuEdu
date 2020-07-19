import com.abdcelik.*;

public class DriverMain
{
    public static void main(String[] args)
    {
        MaxHeap<AgeData> heap = null;

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST01 - No parameter constructor\n");
        heap = new MaxHeap<>();
        System.out.println("Successfully created a heap!");
        System.out.println("The key of heap is number of people");

        heap.add(new AgeData(10));
        heap.add(new AgeData(5));
        heap.add(new AgeData(70));
        heap.add(new AgeData(10));
        heap.add(new AgeData(50));
        heap.add(new AgeData(5));
        heap.add(new AgeData(15));

        System.out.println("Some object will be added!");
        System.out.println("Heap :\n" + heap);

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST02 - One parameter constructor\n");
        heap = new MaxHeap<>((e,t) -> e.getAge() - t.getAge());
        System.out.println("Successfully created a heap with its comparator!");
        System.out.println("The key of heap is max age");

        heap.add(new AgeData(10));
        heap.add(new AgeData(5));
        heap.add(new AgeData(70));
        heap.add(new AgeData(10));
        heap.add(new AgeData(50));
        heap.add(new AgeData(5));
        heap.add(new AgeData(15));

        System.out.println("Some object will be added!");
        System.out.println("Heap :\n" + heap);

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST03 - boolean add(E e) method");
        System.out.println("The key of heap is number of people\n");

        System.out.println("When heap is empty, method will be called as\n\theap.add(new AgeData(10))");
        heap = new MaxHeap<>();
        System.out.println("Before adding");
        System.out.println("Heap :\n" + heap);
        System.out.println("Add 10 : " + heap.add(new AgeData(10)));
        System.out.println("After adding");
        System.out.println("Heap :\n" + heap);

        System.out.println("When heap has some elements, method will be called respectively as\n\theap.add(new AgeData(5)), heap.add(new AgeData(15)),\n\theap.add(new AgeData(5)), heap.add(null)");

        System.out.println("Before adding");
        System.out.println("Heap :\n" + heap);
        System.out.println("Add 5 : " + heap.add(new AgeData(5)));
        System.out.println("Add 15 : " + heap.add(new AgeData(15)));
        System.out.println("Add 5 : " + heap.add(new AgeData(5)));
        System.out.println("Add null : " + heap.add(null));
        System.out.println("After adding");
        System.out.println("Heap :\n" + heap);

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST04 - boolean remove(E e)");
        System.out.println("The key of heap is number of people\n");

        System.out.println("When heap has some elements, method will be called respectively as\n\theap.remove(new AgeData(5)), heap.remove(new AgeData(5)),\n\theap.remove(new AgeData(10)), heap.remove(new AgeData(15)),\n\theap.remove(new AgeData(null))");
        heap.add(new AgeData(10));
        System.out.println("Before removing");
        System.out.println("Heap :\n" + heap);
        System.out.println("Remove 5 : " + heap.remove(new AgeData(5)));
        System.out.println("After removing age 5");
        System.out.println("Heap :\n" + heap);
        System.out.println("Remove 5 : " + heap.remove(new AgeData(5)));
        System.out.println("After removing age 5");
        System.out.println("Heap :\n" + heap);
        System.out.println("Remove 10 : " + heap.remove(new AgeData(10)));
        System.out.println("After removing age 10");
        System.out.println("Heap :\n" + heap);
        System.out.println("Remove 15 : " + heap.remove(new AgeData(15)));
        System.out.println("After removing age 15");
        System.out.println("Heap :\n" + heap);
        System.out.println("Remove null : " + heap.remove(null));
        System.out.println("After removing null");
        System.out.println("Heap :\n" + heap);

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST05 - E find(E e)\n");

        System.out.println("When list has some elements, method will be called respectively\n\theap.find(new AgeData(10)), heap.find(new AgeData(20)),\n\theap.find(null)");
        heap.add(new AgeData(5));
        heap.add(new AgeData(70));
        heap.add(new AgeData(10));
        heap.add(new AgeData(50));
        heap.add(new AgeData(5));
        heap.add(new AgeData(15));
        System.out.println("Heap :\n" + heap);
        System.out.println("Is Age 10 exist? " + heap.find(new AgeData(10)));
        System.out.println("Is Age 20 exist? " + heap.find(new AgeData(20)));
        System.out.println("Is null exist? " + heap.find(null));

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST06 - int youngerThan(int age)\n");

        System.out.println("When list has some elements, method will be called\n\theap.youngerThan(50)");
        System.out.println("Heap :\n" + heap);
        System.out.println("There are " + heap.youngerThan(50) + " people younger than 50!");

        System.out.println("------------------------------------------------");
        System.out.println("\nTEST07 - int olderThan(int age)\n");

        System.out.println("When list has some elements, method will be called\n\theap.olderThan(10)");
        System.out.println("Heap :\n" + heap);
        System.out.println("There are " + heap.olderThan(10) + " people younger than 10!");
    }
}