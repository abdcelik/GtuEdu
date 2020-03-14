package cse241_hw8;

/**
 * An iterator class over a GTUContainer.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements returned by this iterator.
 */
public class GTUIterator<T>
{
	private T[] iter;
	private int index;
	private int size;
	
	/**
	 * No parameter constructor.
	 */
	public GTUIterator()
	{
		this(null,0);
	}
	
	/**
	 * Two parameter constructor.
	 * @param iter new content.
	 * @param size size of new content.
	 */
	public GTUIterator(T[] iter, int size)
	{
		this.iter = iter;
		index = 0;
		this.size = size;
	}
	
	/**
	 * Returns the next element in the iteration.
	 * @return the next element in the iteration.
	 */
	public T next()
	{
		return iter[index++];
	}
	
	/**
	 * Returns true if the iteration has more elements.
	 * @return true if the iteration has more elements.
	 */
	public boolean hasNext()
	{
		if(index < size)
			return true;
		return false;
	}
	
	/**
	 * Returns a string representation of the iterator.
	 * @return a string representation of the iterator.
	 */
	@Override
	public String toString()
	{
		String newString = new String();
		
		newString += next();
		return newString;
	}
}