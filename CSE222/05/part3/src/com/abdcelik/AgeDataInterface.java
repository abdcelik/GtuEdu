package com.abdcelik;

/**
 * AgeDataInterface provides some methods for AgeData class.
 */
public interface AgeDataInterface<E> extends Comparable<E>
{
    /**
     * Returns age.
     * @return age
     */
    int getAge();

    /**
     * Returns number of people.
     * @return number of people.
     */
    int getNumberOfPeople();

    /**
     * Increases number of people by one.
     */
    void increaseNumberOfPeople();

    /**
     * Decreases number of people by one.
     */
    void decreaseNumberOfPeople();
}