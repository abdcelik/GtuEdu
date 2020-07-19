package com.abdcelik;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * FileSystemTree handle a file system hierarchy in a general tree structure.
 * @author Abdullah Celik
 */
public class FileSystemTree
{
    /** root directory */
    private FileNode root;

    /**
     * One parameter constructor to create a file system with a root directory.
     * @param nameOfRoot name of the root directory
     */
    public FileSystemTree(String nameOfRoot)
    {
        if(nameOfRoot.contains("/"))
            root = new FileNode("INVALID_NAME",FileNode.State.DIRECTORY);
        else
            root = new FileNode(nameOfRoot,FileNode.State.DIRECTORY);
    }

    /**
     * Adds new directory to the system.
     * Starter addDir method.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param path the path of the new directory
     */
    public void addDir(String path)
    {
        if(path == null)
            return;

        add(getRoot(),path.split("/"),0,FileNode.State.DIRECTORY);
    }

    /**
     * Adds new file to the system.
     * Starter addFile method.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param path the path of the new file
     */
    public void addFile(String path)
    {
        if(path == null)
            return;

        add(getRoot(),path.split("/"),0,FileNode.State.FILE);
    }

    /**
     * Adds new directory or file to the system recursively.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param node current node
     * @param paths paths array of the new directory or file
     * @param index paths array's index to direct paths array
     * @param state new node's state. State can be DIRECTORY OR FILE
     */
    private void add(FileNode node, String[] paths, int index, FileNode.State state)
    {
        if(!paths[index].equals(node.getName()))
            return;

        if(paths.length-2 == index)
            node.add(paths[index+1],state);
        else
            for(int i=0 ; node.getState() == FileNode.State.DIRECTORY && i < node.getChild().size() ; ++i)
                add(node.getChild().get(i),paths,index+1,state);
    }

    /**
     * Removes a directory or file from the system.
     * Starter remove method.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param path the path of the removed directory or file
     */
    public void remove(String path)
    {
        if(path == null)
            return;

        String[] paths = path.split("/");

        if(paths[0].equals(getRoot().getName()))
        {
            if(paths.length == 1)
                System.out.println("Root directory cannot be removed!");
            else
                remove(getRoot(),paths,1);
        }
        else
            System.out.println("Path cannot be founded!");
    }

    /**
     * Removes a directory or file from the system recursively.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param node current node
     * @param paths path array of the removed directory or file
     * @param index paths array's index to direct paths array
     */
    private void remove(FileNode node, String[] paths, int index)
    {
        if(paths.length-1 == index)
        {
            int i;

            if((i = node.getChild().indexOf(new FileNode(paths[index], FileNode.State.DIRECTORY))) == -1)
                System.out.println("Path cannot be founded!");
            else if(!node.getChild().get(i).isLeaf())
            {
                System.out.println("The removed directory is :");

                StringBuilder sb = new StringBuilder();
                toString(node.getChild().get(i),1,sb);
                System.out.println(sb.toString());
                System.out.println("Are you sure(y/n) : ");

                String buffer;
                Scanner scanner = new Scanner(System.in);
                buffer = scanner.next();

                if(buffer.equals("y") || buffer.equals("Y"))
                    node.remove(paths[index]);
                else
                    System.out.println("Removing process is unsuccessful.");
            }
            else
                node.remove(paths[index]);
        }
        else
        {
            boolean founded = false;

            for(int i=0 ; node.getState() == FileNode.State.DIRECTORY && i < node.getChild().size() ; ++i)
                if(node.getChild().get(i).getName().equals(paths[index]))
                {
                    remove(node.getChild().get(i),paths,index+1);
                    founded = true;
                }

            if(!founded)
                System.out.println("Path cannot be founded!");
        }
    }

    /**
     * Searches the entire file system for a directory or a file including the given search characters in its name.
     * Starter search method.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param searched the search characters
     */
    public void search(String searched)
    {
        if(searched == null)
            return;

        search(getRoot(),searched,new StringBuilder());
    }

    /**
     * Searches the entire file system for a directory or a file including the given search characters in its name recursively.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param node current node
     * @param searched the search characters
     * @param sb StringBuilder instance for appending path for each recursion call and if searched character is founded, path will be printed
     */
    private void search(FileNode node, String searched, StringBuilder sb)
    {
        if(node == null)
            return;

        sb.append(node);

        if(node.getName().contains(searched))
        {
            if(node.getState() == FileNode.State.DIRECTORY) System.out.println("dir - " + sb.toString());
            else System.out.println("file - " + sb.toString());
        }

        for(int i=0 ; node.getState() == FileNode.State.DIRECTORY && i < node.getChild().size() ; ++i)
            search(node.getChild().get(i),searched,new StringBuilder(sb).append("/"));
    }

    /**
     * Prints the file system.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * This method calls toString method.
     */
    public void printFileSystem() { System.out.println(toString()); }

    /**
     * Returns string representation of the file system.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @return string representation of the file system
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        toString(getRoot(),1,sb);
        return sb.toString();
    }

    /**
     * Returns string representation of the file system recursively.
     * Method use pre-order(root - left subtree - right subtree) traversal algorithm.
     * @param node current node
     * @param depth current node's depth
     * @param sb StringBuilder instance for appending file system for each recursion call
     */
    private void toString(FileNode node, int depth, StringBuilder sb)
    {
        if(node == null)
            return;

        sb.append("   ".repeat(Math.max(0, depth - 1)));
        sb.append(node.toString()).append("\n");
        for(int i=0 ; node.getState() == FileNode.State.DIRECTORY && i < node.getChild().size() ; ++i)
            toString(node.getChild().get(i),depth+1,sb);
    }

    /**
     * Returns root node.
     * @return root node
     */
    private FileNode getRoot() { return root; }

    /**
     * FileNode class for the file system's node.
     */
    private static class FileNode
    {
        /** Each node can be directory or file. */
        enum State {DIRECTORY,FILE}

        /** name of the node */
        private String name;
        /** state of the node */
        private State state;
        /** children of the node */
        private ArrayList<FileNode> child = null;

        /**
         * Two parameter constructor. Constructs a node with its name and state
         * @param name name of the node
         * @param state state of the node
         */
        public FileNode(String name, State state)
        {
            this.name = name;
            this.state = state;

            if(state == State.DIRECTORY)
                child = new ArrayList<>();
        }

        /**
         * Adds new child. Child can be DIRECTORY or FILE.
         * @param name name of the child
         * @param state state of the child
         */
        public void add(String name, State state)
        {
            if(getState() == State.FILE)
                return;

            FileNode node = new FileNode(name,state);

            if(!getChild().contains(node))
                getChild().add(node);
        }

        /**
         * Removes the directory or file in the given name.
         * @param name name of the removed node
         * @return true if removing process is successful. Otherwise returns false
         */
        public boolean remove(String name)
        {
            FileNode node = new FileNode(name,state);
            int index;

            if((index = getChild().indexOf(node)) == -1)
                return false;

            getChild().remove(index);
            return true;
        }

        /**
         * Checks whether the node is leaf node.
         * @return true if the node is leaf node. Otherwise returns false
         */
        public boolean isLeaf() { return getChild() == null || getChild().size() == 0; }

        /**
         * Returns node's name.
         * @return node's name
         */
        public String getName() { return name; }

        /**
         * Returns node's state.
         * @return node's state
         */
        public State getState() { return state; }

        /**
         * Returns node's children.
         * @return node's children
         */
        public ArrayList<FileNode> getChild() { return child; }

        /**
         * Checks whether the node equals given object.
         * @param o other object
         * @return true if the node equals given object. Otherwise returns false
         */
        @Override
        public boolean equals(Object o)
        {
            if(o == null)
                return false;
            if(!(o instanceof FileNode))
                return false;

            return getName().equals(((FileNode)o).getName());
        }

        /**
         * Returns string representation of the node.
         * @return string representation of the node
         */
        @Override
        public String toString() { return getName(); }
    }
}
