package com.abdcelik;

import java.io.Serializable;
import java.util.Scanner;
import java.util.function.BiConsumer;

/** Class for a binary tree that stores type E objects. */
public class BinaryTree<E> implements Serializable
{
    /** The root of the binary tree */
    protected Node<E> root;

    /**
     * No parameter constructor to set data field root to null.
     */
    public BinaryTree() { root = null; }

    /**
     * One parameter constructor to set data field root to given root.
     * @param root given root
     */
    protected BinaryTree(Node<E> root) { this.root = root; }

    /**
     * Constructs a new binary tree with data in its root leftTree as its left subtree and rightTree as its right subtree.
     * @param data given data
     * @param leftTree given left tree
     * @param rightTree given right tree
     */
    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree)
    {
        root = new Node<>(data);
        if(leftTree != null)
            root.left = leftTree.root;
        else
            root.left = null;

        if(rightTree != null)
            root.right = rightTree.root;
        else
            root.right = null;
    }

    /**
     * Method to read a binary tree.
     * pre: The input consist of a pre-order traversal of the binary tree. The line "null" indicates a null tree.
     * @param scan the Scanner attached to the input file
     * @return the binary tree
     */
    public static BinaryTree<String> readBinaryTree(Scanner scan)
    {
        // Read a line and trim leading and trailing spaces.
        String data = scan.nextLine().trim();
        if(data.equals("null"))
            return null;
        else
        {
            BinaryTree<String> leftTree = readBinaryTree(scan);
            BinaryTree<String> rightTree = readBinaryTree(scan);
            return new BinaryTree<>(data, leftTree, rightTree);
        }
    }

    /**
     * Returns the left subtree.
     * @return the left subtree or null if either the root or the left subtree is null
     */
    public BinaryTree<E> getLeftSubtree() { return root != null && root.left != null ? new BinaryTree<>(root.left) : null; }

    /**
     * Returns the right subtree.
     * @return the right subtree or null if either the root or the left subtree is null
     */
    public BinaryTree<E> getRightSubtree() { return root != null && root.right != null ? new BinaryTree<>(root.right) : null; }

    /**
     * Returns the data in the root.
     * @return the data in the root if root is not null. Otherwise returns null
     */
    public E getData() { return root != null ? root.data : null; }

    /**
     * Determine whether this tree is a leaf.
     * @return true if the root has no children
     */
    public boolean isLeaf() { return root.left == null && root.right == null; }

    /**
     * Returns string representation of the binary tree.
     * @return string representation of the binary tree
     */
    @Override
    public String toString()
    {
        final StringBuilder sb = new StringBuilder();

        preOrderTraverse((e,d) ->
        {
            for(int i=1 ; i < d ; ++i)
                sb.append("   ");
            sb.append(e);
            sb.append("\n");
        });

        return sb.toString();
    }

    /**
     * Starter method for pre-order traversal
     * @param consumer an object that instantiates the BiConsumer interface. Its method implements abstract method apply.
     */
    public void preOrderTraverse(BiConsumer<E, Integer> consumer) { preOrderTraverse(root,1,consumer); }

    /**
     * Performs a recursive pre-order traversal of the three, applying the action specified in the consumer object.
     * @param node the local root
     * @param depth the depth
     * @param consumer an object whose accept method specifies the action to be performed on each node
     */
    private void preOrderTraverse(Node<E> node, int depth, BiConsumer<E, Integer> consumer)
    {
        if(node == null)
            consumer.accept(null,depth);
        else
        {
            consumer.accept(node.data,depth);
            preOrderTraverse(node.left,depth+1,consumer);
            preOrderTraverse(node.right,depth+1,consumer);
        }
    }

    /** Class to encapsulate a tree node. */
    protected static class Node<E> implements Serializable
    {
        /** The information stored in this node. */
        protected E data;
        /** Reference to the left child. */
        protected Node<E> left;
        /** Reference to the right child. */
        protected Node<E> right;

        /**
         * Construct a node with given data and no children.
         * @param data The data to store in this node
         */
        public Node(E data)
        {
            this.data = data;
            left = right = null;
        }

        /**
         * Returns a string representation of the node.
         * @return a string representation of the data fields
         */
        @Override
        public String toString() { return data.toString(); }
    }
}