package cse222.hw1;

/**
 * A generic container class. Implement GTUContainer.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public class container<T> implements GTUContainer<T>,Cloneable
{
    private T[] content;
    private int used=0;
    private int capacity=0;

    /**
     * No parameter constructor. Capacity is set to 1.
     */
    public container()
    {
        this(1);
    }

    /**
     * One parameter constructor. If capacity is less than 0, capacity is set to 1.
     * @param capacity New container capacity.
     */
    public container(int capacity)
    {
        setUsed(0);
        setCapacity(capacity);
    }

    /**
     * Copy constructor. Other container is copied.
     * @param other to be copied
     */
    public container(container<T> other)
    {
        setCapacity(other.getCapacity());
        setUsed(other.size());

        for(int i = 0; i < size(); ++i)
            content[i] = other.at(i);
    }

    /**
     * Test whether container is empty.
     * This function does not modify the container in any way. To clear the content of a container.
     * @return whether the set container is empty.
     */
    public boolean empty() { return size() == 0; }

    /**
     * Returns the number of elements in the container.
     * @return the number of elements in the container.
     */
    public int size() { return used; }

    /**
     * Makes indexing process.
     * @param index of container.
     * @return the data if index is valid. Otherwise returns false.
     * @throws ArrayIndexOutOfBoundsException if index is invalid, throws exception.
     */
    public T at(int index) throws ArrayIndexOutOfBoundsException
    {
        if(index < 0 || index >= size())
            throw new ArrayIndexOutOfBoundsException("Invalid index!");

        return content[index];
    }

    /**
     * Insert element. 'equals' function must be override.
     * @param newContent new content to add the container.
     * @return true if the insert operation is successful. Otherwise return false.
     */
    public boolean insert(T newContent)
    {
        if(newContent == null || contains(newContent) >= 0)
            return false;

        fixCapacity();
        content[size()] = newContent;
        setUsed(size()+1);

        return true;
    }

    /**
     * Removes from the container a single element.
     * @param content The element to be deleted.
     * @return true if erase operation is successful. Otherwise return false.
     */
    public boolean erase(T content)
    {
        if(content == null || contains(content) == -1)
            return false;

        boolean flag = true;

        for(int i=0 ; i < size() && flag; ++i)
            if(at(i).equals(content))
            {
                this.content[i] = at(size()-1);
                flag = false;
            }

        setUsed(size()-1);
        return true;
    }

    /**
     * Removes all elements from the container (which are destroyed), leaving the container with a size of 0.
     */
    public void clear()
    {
        content = null;
        setUsed(0);
        setCapacity(1);
    }

    /**
     * Check if there is object in the container.
     * @param o element whose presence in this collection is to be tested.
     * @return index if this collection contains the specified element. Otherwise return -1.
     */
    public int contains(Object o)
    {
        if(o == null)
            return -1;

        for(int i=0 ; i < size() ; ++i)
            if(content[i].equals(o))
                return i;
        return -1;
    }

    /**
     * Fix the capacity. If size equals capacity, capacity multiplied by 2.
     */
    protected void fixCapacity()
    {
        if(size() == getCapacity())
            setCapacity(getCapacity()*2);
    }

    /**
     * Getter function for container capacity.
     * @return the capacity of the container.
     */
    public int getCapacity() { return capacity; }

    private void setCapacity(int capacity)
    {
        if(capacity < 0)
            capacity = 1;

        @SuppressWarnings("unchecked")
        T[] temp = (T[])new Object[capacity];

        for(int i=0 ; i < temp.length && i < size() ; ++i)
            temp[i] = at(i);

        setUsed(temp.length > size() ? size() : temp.length-1);
        content = temp;
        this.capacity = capacity;
    }

    private void setUsed(int used) { this.used = used; }

    /**
     * Returns a string representation of the container.
     * @return a string representation of the container.
     */
    @Override
    public String toString()
    {
        String newString = "";

        for(int i=0 ; i < size() ; ++i)
            newString += content[i] + "\n";

        return newString;
    }

    /**
     * Check if the containers are same.
     * @param o other object to compare them.
     * @return true if they are same capacity and elements. Otherwise return false.
     */
    @SuppressWarnings("unchecked")
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof container))
            return false;

        container<T> temp = ((container<T>)o);

        if(size() != temp.size())
            return false;

        for(int i=0 ; i < size() ; ++i)
            if(content[i] != temp.content[i])
                return false;

        return true;
    }

    /**
     * Makes a copy of itself.
     * @return returns clone of this.
     */
    @Override
    public Object clone()throws CloneNotSupportedException
    {
        return new container<T>(this);
    }
}