import com.abdcelik.*;

public class DriverMain
{
    public static void main(String[] args)
    {
        AgeSearchTree<AgeData> tree = new AgeSearchTree<>();

        System.out.println("---------------------------------------");
        System.out.println("TEST01 - boolean add(E item)");
        System.out.println("When tree is empty, method will be called as\n\ttree.add(new AgeData(10))");
        System.out.println("Before adding");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Add 10 : " + tree.add(new AgeData(10)));
        System.out.println("After adding");
        System.out.println("AgeSearchTree :\n" + tree);

        System.out.println("When tree has some elements, method will be called respectively as\n\ttree.add(new AgeData(5)), tree.add(new AgeData(15)),\n\ttree.add(new AgeData(5)), tree.add(new AgeData(20)),\n\ttree.add(new AgeData(null))");
        System.out.println("Before adding");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Add 5 : " + tree.add(new AgeData(5)));
        System.out.println("Add 15 : " + tree.add(new AgeData(15)));
        System.out.println("Add 5 : " + tree.add(new AgeData(5)));
        System.out.println("Add 20 : " + tree.add(new AgeData(20)));
        System.out.println("Add null : " + tree.add(null));
        System.out.println("After adding");
        System.out.println("AgeSearchTree :\n" + tree);

        System.out.println("---------------------------------------");
        System.out.println("TEST02 - boolean remove(E item)");
        System.out.println("When tree has some elements, method will be called respectively as\n\ttree.remove(new AgeData(15)), tree.remove(new AgeData(10)),\n\ttree.remove(new AgeData(5)), tree.remove(new AgeData(5)),\n\ttree.remove(new AgeData(null))");
        System.out.println("Before removing");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Remove 15 : " + tree.remove(new AgeData(15)));
        System.out.println("After removing");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Remove 10 : " + tree.remove(new AgeData(10)));
        System.out.println("After removing");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Remove 5 : " + tree.remove(new AgeData(5)));
        System.out.println("After removing");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Remove 5 : " + tree.remove(new AgeData(5)));
        System.out.println("After removing");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Remove null : " + tree.remove(null));
        System.out.println("After removing");
        System.out.println("AgeSearchTree :\n" + tree);

        System.out.println("---------------------------------------");
        System.out.println("TEST03 - E find(E e)");
        tree.add(new AgeData(5));
        tree.add(new AgeData(20));
        tree.add(new AgeData(25));
        tree.add(new AgeData(15));
        System.out.println("When tree has some elements, method will be called respectively as\n\ttree.find(new AgeData(20)), tree.find(new AgeData(10)),\n\ttree.find(null)");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("Find 20 : " + tree.find(new AgeData(20)));
        System.out.println("Find 10 : " + tree.find(new AgeData(10)));
        System.out.println("Find null : " + tree.find(null));

        System.out.println("---------------------------------------");
        System.out.println("TEST04 - int youngerThan(int age)");
        System.out.println("When tree has some elements, method will be called respectively as\n\ttree.youngerThan(25), tree.youngerThan(10)");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("There are " + tree.youngerThan(25) + " people younger than 25");
        System.out.println("There are " + tree.youngerThan(10) + " people younger than 10");

        System.out.println("---------------------------------------");
        System.out.println("TEST05 - int olderThan(int age)");
        System.out.println("When tree has some elements, method will be called respectively as\n\ttree.olderThan(5), tree.olderThan(15)");
        System.out.println("AgeSearchTree :\n" + tree);
        System.out.println("There are " + tree.olderThan(5) + " people younger than 5");
        System.out.println("There are " + tree.olderThan(15) + " people younger than 15");
    }
}