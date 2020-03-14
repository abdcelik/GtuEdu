package cse241_hw8;

/**
 * A generic Abstract container class. Extends GTUContainer.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public abstract class GTUContainerDerived<T> extends GTUContainer<T>
{
	private final int maxSize = 4096;
	private int used;
	private int capacity;
	protected T[] content;
	
	/**
	 * One parameter constructor. If capacity is less than 0 or greater than max_size, capacity is set to 1.
	 * @param capacity New container capacity.
	 */
	public GTUContainerDerived(int capacity)
	{
		if(capacity <= 0 || capacity > max_size())
			capacity = 1;
		
		setUsed(0);
		setCapacity(capacity);
		
		@SuppressWarnings("unchecked")
		T[] temp = (T[])new Object[getCapacity()];
		content = temp;
	}
	
	/**
	 * Test whether container is empty.
	 * This function does not modify the container in any way. To clear the content of a container.
	 * @return Returns whether the set container is empty.
	 */
	public boolean empty()
	{
		if(size() == 0)
			return true;
		return false;
	}
	
	/**
	 * Returns the number of elements in the container.
	 * @return The number of elements in the container.
	 */
	public int size()
	{
		return used;
	}
	
	/**
	 * Returns the maximum number of elements that the set container can hold.
	 * @return The maximum number of elements a container can hold as content.
	 */
	public int max_size()
	{
		return maxSize;
	}
	
	/**
	 * Insert element, throws exception java.lang.IllegalArgumentException if there is a problem with insertion.
	 * @throws Exception if the capacity is greater than max_size.
	 */
	public abstract boolean insert(T newContent) throws IllegalArgumentException, Exception;
	
	/**
	 * Removes from the container a single element.
	 * @param index The index of the element to be deleted.
	 * @return Return the element to be deleted.
	 * @throws Exception If the index is out of bounds.
	 */
	public T erase(int index) throws Exception
	{
		if(size() == 0 || index < 0 || index > size()-1)
			throw new Exception("Invalid Index!");
		
		T tempContent = content[index];
		
		setUsed(size()-1);
		for(int i=index ; i < size() ; ++i)
			content[i] = content[i+1];
		
		return tempContent;
	}
	
	/**
	 * Removes all elements from the container (which are destroyed), leaving the container with a size of 0.
	 */
	public void clear()
	{
		content = null;
		setUsed(0);
		setCapacity(1);
		
		@SuppressWarnings("unchecked")
		T[] temp = (T[])new Object[getCapacity()];
		content = temp;
	}
	
	/**
	 * Returns an iterator referring to the first element in the container.
	 * @return Iterator to beginning.
	 */
	public GTUIterator<T> iterator()
	{
		if(size() == 0)
			return new GTUIterator<T>();
		else
			return new GTUIterator<T>(content,size());
	}
	
	/**
	 * Returns true if this collection contains the specified element.
	 * @param o element whose presence in this collection is to be tested.
	 * @return true if this collection contains the specified element.
	 */
	public boolean contains(Object o)
	{
		if(o == null)
			return false;
		
		for(int i=0 ; i < size() ; ++i)
			if(content[i].equals(o))
				return true;
		return false;
	}
	
	/**
	 * Returns a string representation of the container.
	 * @return a string representation of the container.
	 */
	@Override
	public String toString()
	{
		String newString = new String();
		
		for(int i=0 ; i < size() ; ++i)
			newString += content[i] + "\n";
		
		return newString;
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object o)
	{
		if(o == null)
			return false;
		
		if(!(o instanceof GTUContainerDerived))
			return false;
		
		if(size() != ((GTUContainerDerived<T>)o).size())
			return false;
		
		for(int i=0 ; i < size() ; ++i)
			if(content[i] != ((GTUContainerDerived<T>)o).content[i])
				return false;
		
		return true;
	}
	
	/**
	 * Fix the capacity. If size equals capacity, capacity multiplied by 2.
	 * @throws Exception if the capacity is greater than max_size.
	 */
	protected void fixCapacity() throws Exception
	{
		if(getCapacity() == max_size() && size() == getCapacity())
			throw new Exception("Capacity is full!");
		
		if(size() == getCapacity())
		{
			setCapacity(getCapacity()*2);
			
			@SuppressWarnings("unchecked")
			T[] temp = (T[])new Object[getCapacity()];
			
			for(int i=0 ; i < size() ; ++i)
				temp[i] = content[i];
			content = temp;
		}
	}
	
	public int getCapacity()
	{
		return capacity;
	}
	
	protected void setUsed(int used)
	{
		this.used = used;
	}
	
	protected void setCapacity(int capacity)
	{
		this.capacity = capacity;
	}
}