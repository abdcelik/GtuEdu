package com.abdcelik;

/**
 * Keeps information about a software. Implements Comparable interface.
 * @author Abdullah Celik
 */
public class Software implements Comparable<Software>
{
    /** Keeps software's name */
    private String name;
    /** Keeps software's quantity*/
    private int quantity;
    /** Keeps software's price */
    private String price;
    /** Keeps default string for invalid information */
    private final String anonymous= "ANONYMOUS";

    /**
     * Constructor with three parameter for building a software.
     * @param name software's name
     * @param quantity software's quantitiy
     * @param price software's price
     */
    public Software(String name, int quantity, String price)
    {
        setName(name);
        setQuantity(quantity);
        setPrice(price);
    }

    /**
     * Returns software's name.
     * @return software's name
     */
    public String getName() { return name; }

    /**
     * Returns software's quantity.
     * @return software's quantity
     */
    public int getQuantity() { return quantity; }

    /**
     * Returns software's price.
     * @return software's price.
     */
    public String getPrice() { return price; }

    /**
     * Sets software's name to given new name.
     * @param name given new name. If given name is null, default string is set
     */
    public void setName(String name) { this.name = name == null ? anonymous : name; }

    /**
     * Sets software's quantity to given new quantity.
     * @param quantity given new quantity. If given quantity is lower than 0, 0 is set
     */
    public void setQuantity(int quantity) { this.quantity = quantity < 0 ? 0 : quantity; }

    /**
     * Sets software's price to given new price
     * @param price given new price. If given price is null, default string is set
     */
    public void setPrice(String price) { this.price = price == null ? anonymous : price; }

    /**
     * Compares software and given software object.
     * @param o given software object
     * @return 0 if software and given software are equal. Returns greater than 0 if software is greater than given software. Otherwise returns lower than 0
     */
    @Override
    public int compareTo(Software o) { return getName().compareTo(o.getName()); }

    /**
     * Checks whether given object is equal.
     * @param o given object
     * @return true if they are equal. Otherwise false
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof Software))
            return false;

        return getName().equals(((Software)o).getName());
    }

    /**
     * Returns string representation of the system.
     * @return string representation of the system.
     */
    @Override
    public String toString() { return "Name: " + getName() + ", Quantity: " + getQuantity() + ", Price: " + getPrice(); }
}