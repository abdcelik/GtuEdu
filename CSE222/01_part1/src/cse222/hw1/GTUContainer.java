package cse222.hw1;

/**
 * A generic interface.
 * @author Abdullah_Celik_171044002
 * @param <T> the type of elements stored by this container.
 */
public interface GTUContainer<T>
{
    boolean empty();
    int size();
    T at(int index) throws ArrayIndexOutOfBoundsException;
    boolean insert(T newContent);
    boolean erase(T content);
    void clear();
    int contains(Object o);
}
