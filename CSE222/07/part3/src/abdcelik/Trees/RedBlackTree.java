package abdcelik.Trees;

/**
 * Implementation of a Red-Black Tree Data Structure
 * @param <E> The data type of items stored in the tree. Must be Comparable
 */
@SuppressWarnings("serial")
public class RedBlackTree<E extends Comparable<E>> extends BinarySearchTreeWithRotate<E>
{
    /** Flag to indicate success of adding an item */
    private boolean addReturn;

    private boolean fixupRequired = false;

    @Override
    public boolean add(E item)
    {
        if(root == null)
        {
            root = new RedBlackNode<>(item);
            ((RedBlackNode<E>) root).isRed = false;
            return true;
        }
        else
        {
            root = add((RedBlackNode<E>)root,item);
            ((RedBlackNode<E>) root).isRed = false;
            return addReturn;
        }
    }

    /**
     * Recursive add method
     * @param localRoot The local root of the Red Black Tree
     * @param item The item to be inserted
     * @return The new local root
     */
    private Node<E> add(RedBlackNode<E> localRoot, E item)
    {
        int compare = item.compareTo(localRoot.data);

        if(compare == 0)
        {
            addReturn = false;
            return localRoot;
        }
        else if(compare < 0)
        {
            if(localRoot.left == null)
            {
                //Create new left child
                localRoot.left = new RedBlackNode<E>(item);
                addReturn = true;
                return localRoot;
            }
            else
            { //Need to search
                //Check for two red children, swap colors if found
                moveBlackDown(localRoot);
                //Recursively add on the left
                localRoot.left = add((RedBlackNode<E>) localRoot.left, item);
                //See whether the left child is now red
                if(((RedBlackNode<E>) localRoot.left).isRed)
                {
                    if(localRoot.left.left != null && ((RedBlackNode<E>) localRoot.left.left).isRed)
                    {
                        // Left-left grand-child is also red
                        // Single rotation is necessary; change colors
                        ((RedBlackNode<E>) localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return rotateRight(localRoot);
                    }
                    else if(localRoot.left.right != null && ((RedBlackNode<E>) localRoot.left.right).isRed)
                    {
                        // Left-right grand-child is also red
                        // Double rotation is necessary; change colors
                        localRoot.left = rotateLeft(localRoot.left);
                        ((RedBlackNode<E>) localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return rotateRight(localRoot);
                    }
                }
                return localRoot;
            }
        }
        else
        {
            //item is greater than localRoot.data
            if(localRoot.right == null)
            {
                //Create new right child
                localRoot.right = new RedBlackNode<E>(item);
                addReturn = true;
                return localRoot;
            }
            else
            { //Need to search
                //Check for two red children, swap if needed
                moveBlackDown(localRoot);
                //Recursively add on the right
                localRoot.right = add((RedBlackNode<E>) localRoot.right, item);
                //See whether right child is now red
                if(((RedBlackNode<E>) localRoot.right).isRed)
                {
                    if(localRoot.right.right != null && ((RedBlackNode<E>) localRoot.right.right).isRed)
                    {
                        //Right-right grand-child is also red
                        //Single rotation is necessary, change colors
                        ((RedBlackNode<E>) localRoot.right).isRed = false;
                        localRoot.isRed = true;
                        return rotateLeft(localRoot);
                    }
                    else if (localRoot.right.left != null && ((RedBlackNode<E>) localRoot.right.left).isRed)
                    {
                        //Right-left grand-child is also red
                        //Double rotation is necessary; change colors
                        localRoot.right = rotateRight(localRoot.right);
                        ((RedBlackNode<E>) localRoot.right).isRed = false;
                        localRoot.isRed = true;
                        return rotateLeft(localRoot);
                    }
                }
                return localRoot;
            }
        }
    }

    @Override
    public boolean remove(E item)
    {
        delete(item);
        return deleteReturn == item;
    }

    @Override
    public E delete(E item)
    {
        fixupRequired = false;
        root = delete((RedBlackNode<E>)root,item);
        if(root != null)
            ((RedBlackNode<E>)root).isRed = false;
        return deleteReturn;
    }

    private RedBlackNode<E> delete(RedBlackNode<E> localRoot,E item)
    {
        if(localRoot == null)
        {
            deleteReturn = null;
            return localRoot;
        }

        int compResult = item.compareTo(localRoot.data);

        if(compResult < 0)
        {
            localRoot.left = delete((RedBlackNode<E>)localRoot.left,item);
            if(fixupRequired)
                localRoot = fixupLeft(localRoot);
            return localRoot;
        }
        else if(compResult > 0)
        {
            localRoot.right = delete((RedBlackNode<E>)localRoot.right,item);
            if(fixupRequired)
                localRoot = fixupRight(localRoot);
            return localRoot;
        }
        else
        {
            deleteReturn = localRoot.data;

            if(!localRoot.isRed)
                fixupRequired = true;

            if(localRoot.left == null)
                return (RedBlackNode<E>)localRoot.right;
            else if(localRoot.right == null)
                return (RedBlackNode<E>)localRoot.left;
            else
            {
                if(localRoot.left.right == null)
                {
                    fixupRequired = false;
                    localRoot.data = localRoot.left.data;
                    if(!((RedBlackNode<E>)localRoot.left).isRed)
                        fixupRequired = true;
                    localRoot.left = localRoot.left.left;
                    if(fixupRequired)
                        localRoot = fixupLeft(localRoot);
                    return localRoot;
                }
                else
                {
                    fixupRequired = false;
                    Pair<E> pair = findLargestChild(localRoot.left);
                    localRoot.data = pair.data;
                    if(!pair.isRed)
                        localRoot = fixupLeft(localRoot);
                    return localRoot;
                }
            }
        }
    }

    private RedBlackNode<E> fixupLeft(RedBlackNode<E> localRoot)
    {
        fixupRequired = false;

        if(localRoot.isRed)
        {
            if(leftChildIsRed((RedBlackNode<E>)localRoot.right))
            {
                localRoot.right = rotateRight(localRoot.right);
                localRoot.isRed = false;
                return (RedBlackNode<E>)rotateLeft(localRoot);
            }
            else if(rightChildIsRed((RedBlackNode<E>)localRoot.right))
            {
                localRoot.isRed = false;
                ((RedBlackNode<E>)localRoot.right).isRed = true;
                ((RedBlackNode<E>)localRoot.right.right).isRed = false;
                return (RedBlackNode<E>)rotateLeft(localRoot);
            }
            else
            {
                localRoot.isRed = false;
                ((RedBlackNode<E>)localRoot.right).isRed = true;
                return localRoot;
            }
        }
        else
        {
            if(rightChildIsRed(localRoot))
            {
                ((RedBlackNode<E>)localRoot.right).isRed = false;
                localRoot.right = rotateRight(localRoot.right);
                localRoot.isRed = true;
                localRoot = (RedBlackNode<E>)rotateLeft(localRoot);
                return (RedBlackNode<E>)rotateLeft(localRoot);
            }
            else
            {
                localRoot.isRed = true;
                return (RedBlackNode<E>)rotateLeft(localRoot);
            }
        }
    }

    private RedBlackNode<E> fixupRight(RedBlackNode<E> localRoot)
    {
        fixupRequired = false;

        if(localRoot.isRed)
        {
            if(rightChildIsRed((RedBlackNode<E>)localRoot.left))
            {
                localRoot.left = rotateLeft(localRoot.left);
                localRoot.isRed = false;
                return (RedBlackNode<E>)rotateRight(localRoot);
            }
            else if(leftChildIsRed((RedBlackNode<E>)localRoot.left))
            {
                localRoot.isRed = false;
                ((RedBlackNode<E>)localRoot.left).isRed = true;
                ((RedBlackNode<E>)localRoot.left.left).isRed = false;
                return (RedBlackNode<E>)rotateRight(localRoot);
            }
            else
            {
                localRoot.isRed = false;
                ((RedBlackNode<E>)localRoot.left).isRed = true;
                return localRoot;
            }
        }
        else
        {
            if(leftChildIsRed(localRoot))
            {
                ((RedBlackNode<E>)localRoot.left).isRed = false;
                localRoot.left = rotateLeft(localRoot.left);
                localRoot.isRed = true;
                localRoot = (RedBlackNode<E>)rotateRight(localRoot);
                return (RedBlackNode<E>)rotateRight(localRoot);
            }
            else
            {
                localRoot.isRed = true;
                return (RedBlackNode<E>)rotateRight(localRoot);
            }
        }
    }

    private boolean leftChildIsRed(RedBlackNode<E> localRoot)
    {
        return localRoot != null && localRoot.left != null && ((RedBlackNode<E>)localRoot.left).isRed;
    }

    private boolean rightChildIsRed(RedBlackNode<E> localRoot)
    {
        return localRoot != null && localRoot.right != null && ((RedBlackNode<E>)localRoot.right).isRed;
    }

    private Pair<E> findLargestChild(Node<E> parent)
    {
        if(parent.right.right == null)
        {
            Pair<E> pair = new Pair<>(parent.right.data,((RedBlackNode<E>)parent.right).isRed);
            parent.right = parent.right.left;
            return pair;
        }
        else
            return findLargestChild(parent.right);
    }

    /**
     * Check to see whether both children of the given node are red.
     * If so, make them black and change the localRoot's color to red.
     * @param localRoot The node to check whether both children are red or not
     */
    private void moveBlackDown(RedBlackNode<E> localRoot)
    {
        if(localRoot.left != null && localRoot.right != null) //If a child is null, it is black
            if(((RedBlackNode<E>) localRoot.left).isRed && ((RedBlackNode<E>) localRoot.right).isRed)
            { //if both children are red, swap colors
                ((RedBlackNode<E>) localRoot.left).isRed = false;
                ((RedBlackNode<E>) localRoot.right).isRed = false;
                localRoot.isRed = true;
            }
    }

    private static class Pair<E>
    {
        public E data;
        public boolean isRed;

        public Pair(E data, boolean isRed)
        {
            this.data = data;
            this.isRed = isRed;
        }
    }

    /**
     * Class to represent a Red-Black node
     * @param <E> The data type of items stored in the node. Must be Comparable
     */
    private static class RedBlackNode<E> extends Node<E>
    {
        /** Color indicator; true if red, false if black */
        private boolean isRed;

        /**
         * Constructor to create a node with the default color of red with the given data
         * @param data The data item to be stored in the node
         */
        public RedBlackNode(E data)
        {
            super(data);
            isRed = true;
        }

        /**
         * Return a String representation of the node
         * @return A String representation of the node
         */
        @Override
        public String toString()
        {
            if(isRed)
                return "Red: " + super.toString();
            return "Black: " + super.toString();
        }
    }
}