package com.abdcelik;

/**
 * AgeSearchTree class keeps a binary search tree.
 * Generic type should implement AgeDataInterface.
 * Each node has an age and number of people at this age.
 * @param <E> generic type of AgeSearchTree
 */
public class AgeSearchTree<E extends AgeDataInterface<E>> extends BinarySearchTree<E>
{
    /**
     * Adding a new element to AgeSearchTree.
     * Starter method add.
     * @param item the object to be inserted
     * @return true if the item is inserted, false if the object is null
     */
    @Override
    public boolean add(E item)
    {
        if(item == null)
            return false;

        root = add(root,item);
        return true;
    }

    /**
     * Recursive add method.
     * @param node the local root of the subtree
     * @param item the object to be inserted
     * @return the new local root that now contains the inserted item
     */
    private Node<E> add(Node<E> node, E item)
    {
        if(node == null)
            return new Node<>(item);
        else
        {
            int comResult = item.compareTo(node.data);

            if(comResult == 0)
                node.data.increaseNumberOfPeople();
            else if(comResult < 0)
                node.left = add(node.left,item);
            else
                node.right = add(node.right,item);

            return node;
        }
    }

    /**
     * Deleting an item from AgeSearchTree.
     * Starter method delete.
     * @param item the item to be deleted
     * @return The object deleted from the tree or null if the object was not in the tree
     */
    @Override
    public E delete(E item)
    {
        if(item == null)
            return deleteReturn = null;

        root = delete(root,item);
        return deleteReturn;
    }

    /**
     * Recursive delete method.
     * post: The item is not in the tree; deleteReturn is equal to the deleted item as it was stored in the tree or null if the item was not found
     * @param node The root of the current subtree
     * @param item the item to be deleted
     * @return the modified local root that does not contain the item
     */
    private Node<E> delete(Node<E> node, E item)
    {
        if(node == null)
        {
            deleteReturn = null;
            return null;
        }

        int compResult = item.compareTo(node.data);

        if(compResult < 0)
        {
            node.left = delete(node.left,item);
            return node;
        }
        else if(compResult > 0)
        {
            node.right = delete(node.right,item);
            return node;
        }

        node.data.decreaseNumberOfPeople();
        deleteReturn = node.data;

        if(node.data.getNumberOfPeople() == 0)
        {
            if(node.left == null)
                return node.right;
            else if(node.right == null)
                return node.left;
            else
            {
                if(node.left.right == null)
                {
                    node.data = node.left.data;
                    node.left = node.left.left;
                }
                else
                    node.data = findLargestChild(node.left);

            }
        }

        return node;
    }

    /**
     * Removes target(if found) from tree and returns true.
     * @param item the object to be removed
     * @return true if found from tree. Otherwise return false
     */
    @Override
    public boolean remove(E item)
    {
        delete(item);
        return deleteReturn != null;
    }

    /**
     * Returns the number of people younger than given age.
     * Starter method youngerThan
     * @param age given age
     * @return the number of people younger than given age
     */
    public int youngerThan(int age) { return youngerThan(root,age); }

    /**
     * Recursion youngerThan method.
     * @param node The root of the current subtree
     * @param age given age
     * @return the number of people younger than given age
     */
    private int youngerThan(Node<E> node, int age)
    {
        if(node == null)
            return 0;

        if(node.data.getAge() < age)
            return node.data.getNumberOfPeople() + calculateTree(node.left) + youngerThan(node.right,age);

        return youngerThan(node.left,age);
    }

    /**
     * Returns the number of people older than given age.
     * Starter method olderThan
     * @param age given age
     * @return the number of people older than given age
     */
    public int olderThan(int age) { return olderThan(root, age); }

    /**
     * Recursion olderThan method.
     * @param node The root of the current subtree
     * @param age given age
     * @return the number of people older than given age
     */
    private int olderThan(Node<E> node, int age)
    {
        if(node == null)
            return 0;

        if(node.data.getAge() > age)
            return node.data.getNumberOfPeople() + olderThan(node.left,age) + calculateTree(node.right);

        return olderThan(node.right,age);
    }

    /**
     * Calculates how many people are in tree.
     * @param node The root of the current subtree
     * @return number of people in tree
     */
    private int calculateTree(Node<E> node)
    {
        if(node == null)
            return 0;

        return node.data.getNumberOfPeople() + calculateTree(node.left) + calculateTree(node.right);
    }
}