package cse241_hw8;

/**
 * Sets are containers that store unique elements following a specific order.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public class GTUSet<T> extends GTUContainerDerived<T> implements Cloneable
{
	/**
	 * No parameter constructor. Capacity is set to 1.
	 */
	public GTUSet()
	{
		this(1);
	}
	
	/**
	 * One parameter constructor. Capacity is set.
	 * @param capacity
	 */
	public GTUSet(int capacity)
	{
		super(capacity);
	}
	
	/**
	 * Copy constructor. Other container is copied.
	 * @param o
	 */
	public GTUSet(GTUSet<T> o)
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
	public boolean insert(T newContent) throws IllegalArgumentException, Exception
	{
		if(newContent == null)
			throw new IllegalArgumentException("Illegal Argument!");
		
		if(contains(newContent) == true)
			return false;
		
		fixCapacity();
		content[size()] = newContent;
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
		return new GTUSet<T>(this);
	}
}