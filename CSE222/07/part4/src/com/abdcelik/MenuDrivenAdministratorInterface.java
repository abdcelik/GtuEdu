package com.abdcelik;

/**
 * Interface for menu driven program's administrator for managing a software store.
 * @author Abdullah Celik
 */
public interface MenuDrivenAdministratorInterface
{
    /**
     * Returns administrator password.
     * @return administrator password
     */
    String getPassword();

    /**
     * Sets administrator password to given password.
     * @param password given password. If given password is null, initially administrator password is set "admin"
     */
    void setPassword(String password);

    /**
     * Adds a software to the system.
     * @param name software's name
     * @param quantity software's quantity
     * @param price software's price
     * @return true if software can be added. Otherwise false
     */
    boolean addSoftware(String name, int quantity, String price);

    /**
     * Removes a software from the system.
     * @param name software's name
     * @return true if software can be removed. Otherwise false
     */
    boolean removeSoftware(String name);

    /**
     * Updates a software in the system.
     * @param name old software's name to be updated
     * @param newName new software's name
     * @param newQuantity new software's quantity
     * @param newPrice new software's price
     * @return true if software can be updated. Otherwise false
     */
    boolean updateSoftware(String name, String newName, int newQuantity, String newPrice);

    /**
     * Searches a software in the system.
     * @param name software' name to be searched
     * @return software if it can be found. Otherwise null
     */
    Software searchSoftware(String name);
}