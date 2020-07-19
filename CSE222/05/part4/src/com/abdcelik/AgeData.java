package com.abdcelik;

/**
 * AgeData class keeps an age and how many people are at this age.
 * Implements AgeDataInterface.
 */
public class AgeData implements AgeDataInterface
{
    /** age of people */
    private int age;
    /** how many people ar at this age */
    private int numberOfPeople;

    /**
     * One parameter constructor to build a AgeData object with given age.
     * Number of people is set 1.
     * @param age age of people
     */
    public AgeData(int age)
    {
        this.age = age;
        numberOfPeople = 1;
    }

    /**
     * Returns age of people.
     * @return age of people
     */
    @Override
    public int getAge() { return age; }

    /**
     * Returns number of people at this age.
     * @return number of people at this age
     */
    @Override
    public int getNumberOfPeople() { return numberOfPeople; }

    /**
     * Increases number of people by one and return it.
     * @return number of people
     */
    @Override
    public int increaseNumberOfPeople() { return ++numberOfPeople; }

    /**
     * Decreases number of people by one and returns it.
     * @return number of people
     */
    @Override
    public int decreaseNumberOfPeople() { return --numberOfPeople; }

    /**
     * Check whether given object and this object are equal.
     * @param o other object
     * @return true if other object is equal this object. Otherwise false
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof AgeData))
            return false;

        return getAge() == ((AgeData)o).getAge();
    }

    /**
     * Returns string representation of the AgeData object.
     * @return string representation of the AgeData object.
     */
    @Override
    public String toString() { return String.format("%d - %d",getAge(),getNumberOfPeople()); }
}