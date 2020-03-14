package cse241_hw8;

/**
 * Vectors are sequence containers representing arrays that can change in size.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public class GTUVector<T> extends GTUContainerDerived<T>
{
	/**
	 * No parameter constructor. Capacity is set to 1.
	 */
	public GTUVector()
	{
		this(1);
	}
	
	/**
	 * One parameter constructor. Capacity is set.
	 * @param capacity
	 */
	public GTUVector(int capacity)
	{
		super(capacity);
	}
	
	/**
	 * Copy constructor. Other container is copied.
	 * @param o
	 */
	public GTUVector(GTUVector<T> o)
	{
		super(o.getCapacity());
		setUsed(o.size());
		
		for(int i=0 ; i < o.size() ; ++i)
			content[i] = o.content[i];
	}
	
	/**
	 * Insert element to back, throws exception java.lang.IllegalArgumentException if there is a problem with insertion.
	 * equals function must be override.
	 * @param newContent
	 * @return if the insertion is successful, returns true. Otherwise false.
	 * @throws IllegalArgumentException
	 * @throws Exception if the capacity is greater than max_size.
	 */
	public boolean insert(T newContent) throws IllegalArgumentException,Exception
	{
		if(newContent == null)
			throw new IllegalArgumentException("Illegal Argument!");
		
		fixCapacity();
		content[size()] = newContent;
		setUsed(size()+1);
		
		return true;
	}
	
	/**
	 * Insert element to specify index, throws exception java.lang.IllegalArgumentException if there is a problem with insertion.
	 * equals function must be override.
	 * @param newContent
	 * @return if the insertion is successful, returns true. Otherwise false.
	 * @throws IllegalArgumentException
	 * @throws Exception if the capacity is greater than max_size.
	 */
	public boolean insert(T newContent, int index) throws IllegalArgumentException,Exception
	{
		if(newContent == null)
			throw new IllegalArgumentException("Illegal Argument!");
		
		if(index < 0 || index > size()-1)
			return false;
		
		fixCapacity();
		
		@SuppressWarnings("unchecked")
		T[] temp = (T[])new Object[getCapacity()];
		
		for(int i=0 ; i < index ; ++i)
			temp[i] = content[i];
		
		temp[index] = newContent;
		
		for(int i=index ; i < size() ; ++i)
			temp[i+1] = content[i];
		
		content = temp;
		setUsed(size()+1);
		
		return true;
	}
	
	/**
	 * Makes a copy of itself.
	 * @return returns clone of this.
	 */
	@Override
	public Object clone()throws CloneNotSupportedException
	{
		return new GTUVector<T>(this);
	}
}