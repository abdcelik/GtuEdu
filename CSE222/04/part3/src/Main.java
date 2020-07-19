import com.abdcelik.Problems;

public class Main
{
    public static void main(String[] args)
    {
        testProblem1();
        testProblem2();
        testProblem3();
        testProblem4();
        testProblem5();
        testProblem6();
    }

    public static void testProblem1()
    {
        System.out.println("--- Problem 1 ---");
        System.out.println("Testing reverse method");

        System.out.println("TEST01\n");
        System.out.println("When string's length is 0");
        String str1 = "";
        System.out.println("Before reverse method");
        System.out.println("String : " + str1 + "  Size : " + str1.length());
        System.out.println("After reverse method");
        System.out.println(Problems.reverse(str1));

        System.out.println("TEST02\n");
        System.out.println("When string's length is greater than 0 but contains one word");
        String str2 = "DATA";
        System.out.println("Before reverse method");
        System.out.println("String : " + str2 + "  Size : " + str2.length());
        System.out.println("After reverse method");
        System.out.println(Problems.reverse(str2));

        System.out.println("TEST03\n");
        System.out.println("When string's length is greater than 0 and contains several words");
        String str3 = "this function writes the sentence in reverse";
        System.out.println("Before reverse method");
        System.out.println("String : " + str3 + "  Size : " + str3.length());
        System.out.println("After reverse method");
        System.out.println(Problems.reverse(str3));

        System.out.println("\n\n");
    }

    public static void testProblem2()
    {
        System.out.println("--- Problem 2 ---");
        System.out.println("Testing elfishOrNot method");

        System.out.println("TEST04\n");
        System.out.println("When word is not elfish");
        String str1 = "elise";
        System.out.println("Word : " + str1);
        System.out.println("It is elfish ? " + Problems.elfishOrNot(str1));

        System.out.println("TEST05\n");
        System.out.println("When word is elfish");
        String str2 = "tasteful";
        System.out.println("Word : " + str2);
        System.out.println("It is elfish ? " + Problems.elfishOrNot(str2));

        System.out.println("\n\n");
    }

    public static void testProblem3()
    {
        System.out.println("--- Problem 3 ---");
        System.out.println("Testing sortArray method");

        System.out.println("TEST06");
        System.out.println("When array is unsorted");
        int[] arr1 = {5,2,6,9,-1,4,-4,0,3,12,1,8,-10};

        System.out.println("Array size : " + arr1.length);
        for (int value : arr1) System.out.print(value + " ");
        System.out.print("\n");

        System.out.println("After sortArray method");
        Problems.sortArray(arr1);

        for (int value : arr1) System.out.print(value + " ");
        System.out.print("\n");

        System.out.println("TEST07");
        System.out.println("When array is sorted");
        int[] arr2 = {0,1,3,5,6,7,9};

        System.out.println("Array size : " + arr2.length);
        for (int value : arr2) System.out.print(value + " ");
        System.out.print("\n");

        System.out.println("After sortArray method");
        Problems.sortArray(arr2);

        for (int value : arr2) System.out.print(value + " ");
        System.out.print("\n");

        System.out.println("\n\n");
    }

    public static void testProblem4()
    {
        System.out.println("--- Problem 4 ---");
        System.out.println("Testing evaluatePrefix method");
        System.out.println("TEST08");
        String str1 = "+ 2 + / - 8 * 2 3 2 - 8 / 10 5";
        System.out.println("Prefix expression : " + str1);

        try
        {
            System.out.println("Result : " + Problems.evaluatePrefix(str1));
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }

        System.out.println("TEST09");
        System.out.println("When prefix expression contains invalid characters");
        String str2 = "+ 2 - / - 8 < 9";

        System.out.println("Prefix expression : " + str2);

        try
        {
            System.out.println("Result : " + Problems.evaluatePrefix(str2));
        }
        catch(Exception e)
        {
            System.out.println("Exception was caught!");
            System.out.println(e.getMessage());
        }

        System.out.println("\n\n");
    }

    public static void testProblem5()
    {
        System.out.println("--- Problem 5 ---");
        System.out.println("Testing evaluatePostfix method");
        System.out.println("TEST10");
        String str1 = "2 8 2 3 * - 2 / + 8 + 10 5 / -";
        System.out.println("Postfix expression : " + str1);

        try
        {
            System.out.println("Result : " + Problems.evaluatePostfix(str1));
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }

        System.out.println("TEST11");
        System.out.println("When postfix expression contains invalid characters");
        String str2 = "2 8 2 3 < - 2 / + 8 + 10 5 / -";
        System.out.println("Postfix expression : " + str2);

        try
        {
            System.out.println("Result : " + Problems.evaluatePostfix(str2));
        }
        catch(Exception e)
        {
            System.out.println("Exception was caught!");
            System.out.println(e.getMessage());
        }

        System.out.println("\n\n");
    }

    public static void testProblem6()
    {
        System.out.println("--- Problem 6 ---");
        System.out.println("Testing printElementsClockwise method");
        System.out.println("TEST12");
        System.out.println("When array has only one row");
        int[][] arr1 = new int[1][4];
        System.out.println("Array :");
        for(int i=0 ; i < 1 ; ++i)
            for(int j=0 ; j< 4 ; ++j)
                arr1[i][j] = i*4+j+1;

        for(int i=0 ; i < 1 ; ++i)
        {
            for(int j=0 ; j< 4 ; ++j)
                System.out.print(arr1[i][j] + " ");
            System.out.print("\n");
        }
        System.out.println("After printElementsClockwise method");
        Problems.printElementsClockwise(arr1,1,4);
        System.out.println("\n\n");


        System.out.println("TEST13");
        System.out.println("When array has only one column");
        int[][] arr2 = new int[5][1];
        System.out.println("Array :");
        for(int i=0 ; i < 5 ; ++i)
            for(int j=0 ; j< 1 ; ++j)
                arr2[i][j] = i+j+1;

        for(int i=0 ; i < 5 ; ++i)
        {
            for(int j=0 ; j< 1 ; ++j)
                System.out.print(arr2[i][j] + " ");
            System.out.print("\n");
        }
        System.out.println("After printElementsClockwise method");
        Problems.printElementsClockwise(arr2,5,1);
        System.out.println("\n\n");


        System.out.println("TEST14");
        System.out.println("When array has some rows and columns");
        int[][] arr3 = new int[5][4];
        System.out.println("Array :");
        for(int i=0 ; i < 5 ; ++i)
            for(int j=0 ; j< 4 ; ++j)
                arr3[i][j] = i*4+j+1;

        for(int i=0 ; i < 5 ; ++i)
        {
            for(int j=0 ; j< 4 ; ++j)
                System.out.print(arr3[i][j] + " ");
            System.out.print("\n");
        }
        System.out.println("After printElementsClockwise method");
        Problems.printElementsClockwise(arr3,5,4);
        System.out.println("\n\n");
    }
}
