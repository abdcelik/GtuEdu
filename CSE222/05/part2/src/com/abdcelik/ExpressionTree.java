package com.abdcelik;

import java.util.Scanner;
import java.util.function.Consumer;

/**
 * ExpressionTree class of arithmetic operations which extends the BinaryTree class.
 */
public class ExpressionTree extends BinaryTree<String>
{
    /**
     * Initialize the tree structure with the given expression string.
     * The expressions will include integer operands and arithmetic operators.
     * @param expression given expression
     * @throws NullPointerException if given expression is null
     * @throws IllegalArgumentException if given expression is invalid expression
     */
    public ExpressionTree(String expression)
    {
        if(expression == null)
            throw new NullPointerException();
        if(!isValid(expression))
            throw new IllegalArgumentException("Invalid token!");

        BinaryTree<String> binaryTree = readBinaryTree(new Scanner(expression));
        root = binaryTree == null ? null : binaryTree.root;
    }

    /**
     * Checks whether given expression is valid.
     * Valid characters : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /
     * @param expression given expression
     * @return true if expression is valid. Otherwise returns false
     */
    private boolean isValid(String expression)
    {
        for(int i=0 ; i < expression.length() ; ++i)
        {
            char chr = expression.charAt(i);

            if(chr == 44 || chr == 46 || ((chr < 42 || chr > 57) && chr != 32))
                return false;
        }
        return true;
    }

    /**
     * Create an expression tree by reading both prefix and postfix expressions.
     * @param scan given scanner to read an expression
     * @return null if scanner is null or scanner has no elements. Otherwise returns BinaryTree
     */
    public static BinaryTree<String> readBinaryTree(Scanner scan)
    {
        if(scan == null || !scan.hasNext())
            return null;

        StringBuilder sb = new StringBuilder();
        String first = scan.next();
        sb.append(first).append(" ");

        if(isOperator(first))
        {
            while(scan.hasNext())
                sb.append(scan.next()).append(" ");

            return readPrefixExpression(new Scanner(sb.toString()));
        }
        else
        {
            while(scan.hasNext())
                sb.insert(0,scan.next() + " ");

            return readPostfixExpression(new Scanner(sb.toString()));
        }
    }

    /**
     * Creates an expression tree by reading prefix expression.
     * @param scan given scanner to read a prefix expression
     * @return BinaryTree which is a expression tree
     */
    private static BinaryTree<String> readPrefixExpression(Scanner scan)
    {
        String data;

        if(scan.hasNext())
            data = scan.next();
        else
            return null;

        BinaryTree<String> leftTree = null, rightTree = null;

        if(isOperator(data))
        {
            leftTree = readPrefixExpression(scan);
            rightTree = readPrefixExpression(scan);
        }

        return new BinaryTree<>(data,leftTree,rightTree);
    }

    /**
     * Creates an expression tree by reading postfix expression.
     * @param scan given scanner to read a postfix expression
     * @return BinaryTree which is a expression tree
     */
    private static BinaryTree<String> readPostfixExpression(Scanner scan)
    {
        String data;

        if(scan.hasNext())
            data = scan.next();
        else
            return null;

        BinaryTree<String> leftTree = null, rightTree = null;

        if(isOperator(data))
        {
            rightTree = readPostfixExpression(scan);
            leftTree = readPostfixExpression(scan);
        }

        return new BinaryTree<>(data,leftTree,rightTree);
    }

    /**
     * Checks whether input is operator.
     * Valid operators : +, -, /, *
     * @param input given string to check
     * @return true if given string is operator. Otherwise returns false
     */
    private static boolean isOperator(String input) { return input.equals("+") || input.equals("-") || input.equals("/") || input.equals("*"); }

    /**
     * Returns prefix representation of the ExpressionTree
     * @return prefix representation of the ExpressionTree
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        preOrderTraverse(e -> sb.append(e).append(" "));
        return sb.toString();
    }

    /**
     * Starter preOrderTraverse method.
     * @param consumer an object that instantiates the Consumer interface. Its method implements abstract method apply.
     */
    public void preOrderTraverse(Consumer<String> consumer) { preOrderTraverse(root,consumer); }

    /**
     * Performs a recursive pre-order traversal of the three, applying the action specified in the consumer object.
     * @param node the local root
     * @param consumer an object whose accept method specifies the action to be performed on each node
     */
    private void preOrderTraverse(Node<String> node, Consumer<String> consumer)
    {
        if(node != null)
        {
            consumer.accept(node.data);
            preOrderTraverse(node.left,consumer);
            preOrderTraverse(node.right,consumer);
        }
    }

    /**
     * Returns postfix representation of the ExpressionTree
     * @return postfix representation of the ExpressionTree
     */
    public String toString2()
    {
        StringBuilder sb = new StringBuilder();

        postOrderTraverse(e -> sb.append(e).append(" "));
        return sb.toString();
    }

    /**
     * Starter postOrderTraverse method.
     * @param consumer an object that instantiates the Consumer interface. Its method implements abstract method apply.
     */
    public void postOrderTraverse(Consumer<String> consumer) { postOrderTraverse(root,consumer); }

    /**
     * Performs a recursive post-order traversal of the three, applying the action specified in the consumer object.
     * @param node the local root
     * @param consumer an object whose accept method specifies the action to be performed on each node
     */
    private void postOrderTraverse(Node<String> node, Consumer<String> consumer)
    {
        if(node != null)
        {
            postOrderTraverse(node.left,consumer);
            postOrderTraverse(node.right,consumer);
            consumer.accept(node.data);
        }
    }

    /**
     * Evaluates the expression and returns the result.
     * Starter eval method.
     * @return result of the expression
     */
    public int eval() { return eval(root); }

    /**
     * Evaluates the expression and returns the result.
     * @param node the local root
     * @return result of the expression
     */
    private int eval(Node<String> node)
    {
        if(node == null)
            return 0;

        if(!isOperator(node.data))
            return Integer.parseInt(node.data);
        else
            return calculate(node.data,eval(node.left),eval(node.right));
    }

    /**
     * Calculates result of given integer numbers according to given operator.
     * Valid operator: +, - , *, /
     * @param op given operator
     * @param n1 given number
     * @param n2 give number
     * @return result of given integer numbers according to given operator. If operator is invalid returns 0
     */
    private int calculate(String op, int n1, int n2)
    {
        switch(op)
        {
            case "+":   return n1 + n2;
            case "-":   return n1 - n2;
            case "/":   return n1 / n2;
            case "*":   return n1 * n2;
            default:    return 0;
        }
    }
}
