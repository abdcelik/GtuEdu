package com.abdcelik;

/**
 * AgeData class keeps an age and how many people are at this age.
 * Implements AgeDataInterface.
 */
public class AgeData implements AgeDataInterface<AgeData>
{
    /** age of people */
    public int age;
    /** how many people ar at this age */
    public int numberOfPeople;

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
     * Increases number of people by one.
     */
    @Override
    public void increaseNumberOfPeople() { ++numberOfPeople; }

    /**
     * Decreases number of people by one.
     */
    @Override
    public void decreaseNumberOfPeople() { --numberOfPeople; }

    /**
     * Compares this object and given object.
     * @param o other object
     * @return 0 if this and other object is equal. Returns negative number if this object greater than other object. Otherwise returns positive number
     */
    @Override
    public int compareTo(AgeData o)
    {
        if(o == null)
            throw new NullPointerException();

        return age - o.getAge();
    }

    /**
     * Returns string representation of the AgeData object.
     * @return string representation of the AgeData object.
     */
    @Override
    public String toString() { return String.format("%d - %d",getAge(),getNumberOfPeople()); }
}