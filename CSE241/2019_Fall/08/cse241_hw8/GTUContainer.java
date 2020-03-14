package cse241_hw8;

/**
 * A generic Abstract container class. 
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public abstract class GTUContainer<T>
{
	public abstract boolean empty();
	public abstract int size();
	public abstract int max_size();
	public abstract boolean insert(T newContent) throws IllegalArgumentException, Exception;
	public abstract T erase(int index) throws Exception;
	public abstract void clear();
	public abstract GTUIterator<T> iterator();
	public abstract boolean contains(Object o);
}