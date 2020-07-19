package com.abdcelik;

/**
 * Interface for menu driven program for managing a software store.
 * @author Abdullah Celik
 */
public interface MenuDrivenInterface
{
    /**
     * Searches an item in the system. It is a public feature.
     * @param name software name to be searched
     * @return searched item if it is found. Otherwise null
     */
    Software searchSoftware(String name);

    /**
     * Returns administrator if administrator password is true.
     * @param password administrator password
     * @return administrator if administrator password is ture. Otherwise null
     */
    MenuDrivenAdministratorInterface getAdmin(String password);
}