package com.abdcelik;

/**
 * AgeDataInterface provides some methods for AgeData class.
 */
public interface AgeDataInterface
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
     * Increases number of people by one and returns it.
     * @return number of people
     */
    int increaseNumberOfPeople();

    /**
     * Decreases number of people by one and returns it.
     * @return number of people
     */
    int decreaseNumberOfPeople();
}