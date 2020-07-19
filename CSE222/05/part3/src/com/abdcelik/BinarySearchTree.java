/**
 * BinarySearchTree class for a binary search tree that stores type E objects.
 * E object should implement Comparable interface.
 * @param <E> generic type of BinarySearchTree
 */
public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree<E> implements SearchTree<E>
{
    /** Return value from the public add method */
    protected boolean addReturn;
    /** Return value from the public delete method */
    protected E deleteReturn;

    /**
     * Starter method add.
     * pre: The object to insert must implement the Comparable interface.
     * @param item the object being inserted
     * @return true if the object is inserted, false if the object already exists in the tree
     */
    @Override
    public boolean add(E item)
    {
        root = add(root,item);
        return addReturn;
    }

    /**
     * Recursive add method.
     * post: The data field addReturn is set true if the item is added to the tree, false if the item is already in the three.
     * @param node the local root of the subtree
     * @param item the object to be inserted
     * @return the new local root that now contains the inserted item
     */
    private Node<E> add(Node<E> node, E item)
    {
        if(node == null)
        {
            addReturn = true;
            return new Node<>(item);
        }
        else
        {
            int comResult = item.compareTo(node.data);

            if(comResult == 0)
                addReturn = false;
            else if(comResult < 0)
                node.left = add(node.left,item);
            else
                node.right = add(node.right,item);

            return node;
        }
    }

    /**
     * Returns true if the target is found in the tree.
     * @param target the object to te searched
     * @return true if the target is found in the tree. Otherwise returns false
     */
    @Override
    public boolean contains(E target) { return find(root,target) != null; }

    /**
     * Starter method find.
     * pre: The target object must implement the Comparable interface.
     * @param target The Comparable object being sought
     * @return the object, if found, otherwise null
     */
    @Override
    public E find(E target)
    {
        if(target == null)
            return null;

        return find(root,target);
    }

    /**
     * Recursive find method.
     * @param node The local subtree's root
     * @param target The object being sought
     * @return the object, if found, otherwise null
     */
    private E find(Node<E> node, E target)
    {
        if(node == null)
            return null;

        int compResult = target.compareTo(node.data);

        if(compResult == 0)
            return node.data;
        else if(compResult < 0)
            return find(node.left,target);
        else
            return find(node.right,target);
    }

    /**
     * Starter method delete.
     * post: The object is not in the tree.
     * @param target the object to be deleted
     * @return The object deleted from the tree or null if the object was not in the tree
     * @throws ClassCastException if target does not implement Comparable
     */
    @Override
    public E delete(E target)
    {
        root = delete(root,target);
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
        else
        {
            deleteReturn = node.data;

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
                return node;
            }
        }
    }

    /**
     * Find the node that is the inorder predecessor and replace it with its left child(if any).
     * post: The inorder predecessor is removed from the tree.
     * @param parent the parent of possible inorder predecessor(ip)
     * @return the data in the ip
     */
    protected E findLargestChild(Node<E> parent)
    {
        if(parent.right.right == null)
        {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        }
        else
            return findLargestChild(parent.right);
    }

    /**
     * Removes target(if found) from tree and returns true.
     * @param target the object to be removed
     * @return true if found from tree. Otherwise return false
     */
    @Override
    public boolean remove(E target)
    {
        root = delete(root,target);
        return deleteReturn != null;
    }
}