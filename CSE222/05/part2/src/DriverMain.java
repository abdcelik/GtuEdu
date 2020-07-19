import com.abdcelik.*;

import java.util.Scanner;

public class DriverMain
{
    public static void main(String[] args)
    {
        System.out.println("-------------------------------------------------");
        System.out.println("\nTEST01 - Testing ExpressionTree constructor");
        System.out.println("When expression is valid prefix expression");
        String expression = "+ + 10 * 5 15 20";
        System.out.println("Expression : " + expression);
        ExpressionTree expTree = new ExpressionTree(expression);
        System.out.println("ExpressionTree was created successfully!");
        System.out.println("Prefix Expression(toString method) :");
        System.out.println(expTree.toString());
        System.out.println("Postfix Expression(toString2 method) :");
        System.out.println(expTree.toString2());

        System.out.println("\nTEST02 - Testing ExpressionTree constructor");
        System.out.println("When expression is valid postfix expression");
        String expression2 = "10 5 15 * + 20 +";
        System.out.println("Expression : " + expression2);
        ExpressionTree expTree2 = new ExpressionTree(expression2);
        System.out.println("ExpressionTree was created successfully!");
        System.out.println("Prefix Expression(toString method) :");
        System.out.println(expTree2.toString());
        System.out.println("Postfix Expression(toString2 method) :");
        System.out.println(expTree2.toString2());

        System.out.println("\nTEST03 - Testing ExpressionTree constructor");
        System.out.println("When expression is null");
        System.out.println("Expression : null");
        try
        {
            ExpressionTree expTree3 = new ExpressionTree(null);
        }
        catch(NullPointerException e)
        {
            System.out.println("NullPointerException was caught!");
        }

        System.out.println("\nTEST04 - Testing ExpressionTree constructor");
        System.out.println("When expression is invalid expression");
        String expression4 = "10 5 + ^ A .";
        System.out.println("Expression : " + expression4);
        try
        {
            ExpressionTree expTree4 = new ExpressionTree(expression4);
        }
        catch(IllegalArgumentException e)
        {
            System.out.println("IllegalArgumentException was caught!");
            System.out.println(e.getMessage());
        }

        System.out.println("-------------------------------------------------");
        System.out.println("\nTEST05 - Testing BinaryTree<String> readBinaryTree(Scanner scan)");
        System.out.println("When scanner scans valid prefix expression");
        String expression5 = "- * 10 + 3 2 20";
        System.out.println("Expression : " + expression5);
        BinaryTree<String> tree1 = null;
        System.out.println("Before method expression tree is :");
        System.out.println(tree1);
        tree1 = ExpressionTree.readBinaryTree(new Scanner(expression5));
        System.out.println("After method expression tree is :");
        System.out.println(tree1);

        System.out.println("\nTEST06 - Testing BinaryTree<String> readBinaryTree(Scanner scan)");
        System.out.println("When scanner scans valid postfix expression");
        String expression6 = "10 3 2 + * 20 -";
        System.out.println("Expression : " + expression6);
        BinaryTree<String> tree2 = null;
        System.out.println("Before method expression tree is :");
        System.out.println(tree2);
        tree2 = ExpressionTree.readBinaryTree(new Scanner(expression6));
        System.out.println("After method expression tree is :");
        System.out.println(tree2);

        System.out.println("\nTEST07 - Testing BinaryTree<String> readBinaryTree(Scanner scan)");
        System.out.println("When scanner is null");
        BinaryTree<String> tree3 = null;
        System.out.println("Before method expression tree is :");
        System.out.println(tree3);
        tree3 = ExpressionTree.readBinaryTree(null);
        System.out.println("After method expression tree is :");
        System.out.println(tree3);

        System.out.println("\nTEST08 - Testing BinaryTree<String> readBinaryTree(Scanner scan)");
        System.out.println("When scanner has no next element(expression is empty)");
        String expression7 = "";
        System.out.println("Expression : " + expression7);
        BinaryTree<String> tree4 = null;
        System.out.println("Before method expression tree is :");
        System.out.println(tree4);
        tree4 = ExpressionTree.readBinaryTree(new Scanner(expression7));
        System.out.println("After method expression tree is :");
        System.out.println(tree4);

        System.out.println("-------------------------------------------------");
        System.out.println("\nTEST09 - Testing toString()");
        System.out.println("Prefix Expression(toString method) :");
        System.out.println(expTree.toString());

        System.out.println("\nTEST10 - Testing toString2()");
        System.out.println("Postfix Expression(toString2 method) :");
        System.out.println(expTree.toString2());

        System.out.println("-------------------------------------------------");
        System.out.println("TEST11 - Testing int eval()");
        System.out.println("Prefix Expression(toString method) :");
        System.out.println(expTree.toString());
        System.out.println("Postfix Expression(toString2 method) :");
        System.out.println(expTree.toString2());
        System.out.println("Result : " + expTree.eval());
    }
}