package com.abdcelik;

import java.util.Stack;

/**
 * This class includes some static methods for homework 04-part3
 */
public class Problems
{
    /**
     * Returns reverse given string.
     * This method calls reverseString(string,index) method as reverseString(string,0)
     * @param str given string
     * @return reverse given string
     */
    public static String reverse(String str) { return reverseString(str,0); }

    /**
     * Returns reverse given string.
     * @param str given string
     * @param index that string is reversed this point.
     * @return reverse given string
     */
    private static String reverseString(String str, int index)
    {
        StringBuilder sb = new StringBuilder();
        int i;

        if((i = str.indexOf(' ',index)) == -1)
            return str.substring(index,str.length());

        sb.append(reverseString(str,i+1));

        return sb.append(" ").append(str.substring(index,i)).toString();
    }

    /**
     * Checks whether given string is elfish or not.
     * This method calls elfOrNot(string,letter) method as elfOrNot(string,"elf")
     * @param str given string
     * @return true if given string is elfish. Otherwise returns false.
     */
    public static boolean elfishOrNot(String str) { return elfOrNot(str,"elf"); }

    /**
     * Checks whether given string is elfish or not.
     * @param str given string
     * @param letter given letter
     * @return true if given string is elfish. Otherwise returns false.
     */
    private static boolean elfOrNot(String str, String letter)
    {
        if(letter.length() == 0)
            return true;
        if(str.length() == 0)
            return false;

        int index = checkLetter(str,letter);

        if(index != -1)
            letter = letter.replace(String.format("%c",letter.charAt(index)),"");

        return elfOrNot(str.substring(1),letter);
    }

    /**
     * Check whether given string's index 0 is equal letters.
     * @param str given string
     * @param letter given letter
     * @return letter index if given string's index 0 is equal any letters. Otherwise returns -1
     */
    private static int checkLetter(String str, String letter)
    {
        if(letter.length() == 0)
            return -1;

        if(str.charAt(0) == letter.charAt(0))
            return 0;

        int index = checkLetter(str,letter.substring(1));

        if(index != -1)
            return index+1;
        else
            return index;
    }

    /**
     * Sort array using insertion sort.
     * This method calls insertionSort(array,index) as insertionSort(array,0)
     * @param arr array to sort
     */
    public static void sortArray(int[] arr) { insertionSort(arr,0); }

    /**
     * Sort array using insertion sort.
     * @param arr array to sort
     * @param index the point from which the array will be sorted
     */
    private static void insertionSort(int[] arr, int index)
    {
        if(index >= arr.length-1)
            return;

        int minIndex = findMinimumIndex(arr,index);
        int temp = arr[index];
        arr[index] = arr[minIndex];
        arr[minIndex] = temp;

        insertionSort(arr,index+1);
    }

    /**
     * Returns the smallest number'index from index to the end of the array.
     * @param arr given array
     * @param index given index
     * @return minimum number's index
     */
    private static int findMinimumIndex(int[] arr, int index)
    {
        if(index == arr.length-1)
            return index;

        int minimumIndex = findMinimumIndex(arr,index+1);
        return arr[index] < arr[minimumIndex] ? index : minimumIndex;
    }

    /**
     * Evaluates prefix expression and returns the result.
     * This method calls evaluatePrefix(prefix,index,stack) as evaluatePrefix(prefix,prefix.length-1,stack).
     * @param prefix given prefix expression
     * @return result of prefix expression
     * @throws Exception if prefix expression contains invalid character.
     */
    public static int evaluatePrefix(String prefix) throws Exception
    {
        String[] prefixExpression = prefix.split("\\s+");
        return evaluatePrefix(prefixExpression,prefixExpression.length-1,new Stack<Integer>());
    }

    /**
     * Evaluates prefix expression and returns the result.
     * @param prefix given prefix expression
     * @param index of the expression examined
     * @param stack that push operand
     * @return result of prefix expression
     * @throws Exception if prefix expression contains invalid character.
     */
    private static int evaluatePrefix(String[] prefix, int index, Stack<Integer> stack) throws Exception
    {
        if(index < 0)
            return stack.pop();

        int chr = 0;

        if((chr = isOperator(prefix[index])) != 0)
            stack.push(evalOpPrefix((char)chr,stack));
        else if(isDigit(prefix[index]))
            stack.push(Integer.parseInt(prefix[index]));
        else
            throw new Exception("Invalid character!");

        return evaluatePrefix(prefix,index-1,stack);
    }

    /**
     * Evaluates postfix expression and returns the result.
     * This method calls evaluatePostfix(postfix,index,stack) as evaluatePrefix(postfix,0,stack).
     * @param postfix given postfix expression
     * @return result of postfix expression
     * @throws Exception if postfix expression contains invalid character.
     */
    public static int evaluatePostfix(String postfix) throws Exception
    {
        String[] postfixExpression = postfix.split("\\s+");
        return evaluatePostfix(postfixExpression,0,new Stack<Integer>());
    }

    /**
     * Evaluates postfix expression and returns the result.
     * @param postfix given postfix expression
     * @param index of the expression examined
     * @param stack that push operand
     * @return result of postfix expression
     * @throws Exception if postfix expression contains invalid character.
     */
    private static int evaluatePostfix(String[] postfix, int index, Stack<Integer> stack) throws Exception
    {
        if(index >= postfix.length)
            return stack.pop();

        int chr = 0;

        if((chr = isOperator(postfix[index])) != 0)
            stack.push(evalOpPostfix((char)chr,stack));
        else if(isDigit(postfix[index]))
            stack.push(Integer.parseInt(postfix[index]));
        else
            throw new Exception("Invalid character!");

        return evaluatePostfix(postfix,index+1,stack);
    }

    /**
     * Returns operator character if given string is a operator. Otherwise returns 0
     * @param str given string
     * @return operator character if given string is a operator. Otherwise returns 0
     */
    private static char isOperator(String str)
    {
        if(str.length() != 1)
            return 0;

        switch(str.charAt(0))
        {
            case '+': return '+';
            case '-': return '-';
            case '*': return '*';
            case '/': return '/';
            default: return 0;
        }
    }

    /**
     * Check whether given string is a number or not
     * @param str given string
     * @return true if given string is a number. Otherwise returns false
     */
    private static boolean isDigit(String str)
    {
        if(str.length() == 0)
            return true;

        if(str.charAt(0) >= '0' && str.charAt(0) <= '9')
            return isDigit(str.substring(1));
        else
            return false;
    }

    /**
     * Calculates result given operator and returns it for prefix expression.
     * @param operator given operator
     * @param stack to pop number
     * @return result of given operator and returns it.
     */
    private static int evalOpPrefix(char operator, Stack<Integer> stack)
    {
        int n1 = stack.pop();
        int n2 = stack.pop();

        switch(operator)
        {
            case '+': return n1+n2;
            case '-': return n1-n2;
            case '*': return n1*n2;
            case '/': return n1/n2;
            default: return 0;
        }
    }

    /**
     * Calculates result given operator and returns it for postfix expression.
     * @param operator given operator
     * @param stack to pop number
     * @return result of given operator and returns it.
     */
    private static int evalOpPostfix(char operator, Stack<Integer> stack)
    {
        int n1 = stack.pop();
        int n2 = stack.pop();

        switch(operator)
        {
            case '+': return n1+n2;
            case '-': return n2-n1;
            case '*': return n1*n2;
            case '/': return n2/n1;
            default: return 0;
        }
    }

    /**
     * Prints elements of given array clockwise on the screen.
     * This method calls printElementsClockwise(array,xPos,yPos,row,column) as printElementsClockwise(array,0,0,row,column)
     * @param arr given array
     * @param row given array's row number
     * @param column given array's column number
     */
    public static void printElementsClockwise(int[][] arr, int row, int column) { printElementsClockwise(arr,0,0,row,column); }

    /**
     * Prints elements of given array clockwise on the screen.
     * @param arr given array
     * @param xPos starting point's x position
     * @param yPos starting point's y position
     * @param row given array's row number
     * @param column given array's column number
     */
    private static void printElementsClockwise(int[][] arr, int xPos, int yPos, int row, int column)
    {
        if(xPos >= column || yPos >= row)
            return;

        for(int i = xPos ; i < column ; ++i)
            System.out.print(arr[yPos][i] + " ");

        for(int i = yPos+1 ; i < row ; ++i)
            System.out.print(arr[i][column-1] + " ");

        if(row-1 != xPos)
            for(int i = column-2 ; i >= yPos ; --i)
                System.out.print(arr[row-1][i] + " ");

        if(column-1 != yPos)
            for(int i = row-2 ; i > xPos ; --i)
                System.out.print(arr[i][yPos] + " ");

        printElementsClockwise(arr,xPos+1,yPos+1,row-1,column-1);
    }
}
