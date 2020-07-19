package com.abdcelik;

import com.SearchTree.SearchTree;

/**
 * Manages a software store. Generic type must be implements SearchTree interface.
 * @param <E> generic type of storing data
 * @author Abdullah Celik
 */
public class MenuDriven<E extends SearchTree<Software>> implements MenuDrivenInterface
{
    /** Keeps administrator of system */
    private MenuDriven<SearchTree<Software>>.Administrator admin;
    /** Keeps storing data structure */
    private E store;

    /**
     * Constructor with one parameter for building system.
     * @param data given data structure for storing software
     */
    public MenuDriven(E data) { this(null,data); }

    /**
     * Constructor with two parameter for building system.
     * @param password initial administrator password
     * @param data given data structure for storing data software
     */
    public MenuDriven(String password, E data)
    {
        admin = new MenuDriven<SearchTree<Software>>.Administrator(password);
        store = data;
    }

    /**
     * Adds a software to the system. It's not a public feature. Administrator can add only.
     * @param item item to be added
     * @return true if item can be added. Otherwise false
     */
    private boolean addSoftware(Software item) { return store.add(item); }

    /**
     * Removes a software from the system. It's not a public feature. Administrator can remove only.
     * @param item item to be removed
     * @return true if item can be removed. Otherwise false
     */
    private boolean removeSoftware(Software item) { return store.remove(item); }

    /**
     * Updates existing software. It's not a public feature. Administrator can update only.
     * @param oldItem old item to be updated
     * @param newItem new item
     * @return true if item can be updated. Otherwise false
     */
    private boolean updateSoftware(Software oldItem, Software newItem)
    {
        Software soft = store.find(oldItem);

        if(soft == null || !store.find(oldItem).equals(oldItem))
            return false;

        if(soft.getName().equals(newItem.getName()))
        {
            soft.setPrice(newItem.getPrice());
            soft.setQuantity(newItem.getQuantity());
        }
        else
            store.remove(oldItem);

        return store.add(newItem);
    }

    /**
     * Searches an item in the system. It is a public feature.
     * @param name software name to be searched
     * @return searched item if it is found. Otherwise null
     */
    @Override
    public Software searchSoftware(String name) { return store.find(new Software(name,0,null)); }

    /**
     * Returns administrator if administrator password is true.
     * @param password administrator password
     * @return administrator if administrator password is ture. Otherwise null
     */
    @Override
    public MenuDrivenAdministratorInterface getAdmin(String password) { return admin.getPassword().equals(password) ? admin : null; }

    /**
     * Keeps administrator of the system. Administrator can add,remove and update item.
     */
    private class Administrator implements MenuDrivenAdministratorInterface
    {
        /** Keeps administrator password */
        private String password;

        /**
         * Constructor with one parameter for building administrator instance.
         * @param password administrator password. If password is null, initially password is set "admin"
         */
        public Administrator(String password) { setPassword(password); }

        /**
         * Returns administrator password.
         * @return administrator password
         */
        @Override
        public String getPassword() { return password; }

        /**
         * Sets administrator password to given password.
         * @param password given password. If given password is null, initially administrator password is set "admin"
         */
        @Override
        public void setPassword(String password) { this.password = password == null ? "admin" : password; }

        /**
         * Adds a software to the system.
         * @param name software's name
         * @param quantity software's quantity
         * @param price software's price
         * @return true if software can be added. Otherwise false
         */
        @Override
        public boolean addSoftware(String name, int quantity, String price) { return MenuDriven.this.addSoftware(new Software(name,quantity,price)); }

        /**
         * Removes a software from the system.
         * @param name software's name
         * @return true if software can be removed. Otherwise false
         */
        @Override
        public boolean removeSoftware(String name) { return MenuDriven.this.removeSoftware(new Software(name,0,null)); }

        /**
         * Updates a software in the system.
         * @param name old software's name to be updated
         * @param newName new software's name
         * @param newQuantity new software's quantity
         * @param newPrice new software's price
         * @return true if software can be updated. Otherwise false
         */
        @Override
        public boolean updateSoftware(String name, String newName, int newQuantity, String newPrice)
        {
            boolean returned = MenuDriven.this.updateSoftware(new Software(name,0,null),new Software(newName,newQuantity,newPrice));

            if(newQuantity == 0)
                removeSoftware(name);
            return returned;
        }

        /**
         * Searches a software in the system.
         * @param name software' name to be searched
         * @return software if it can be found. Otherwise null
         */
        @Override
        public Software searchSoftware(String name) { return MenuDriven.this.searchSoftware(name); }
    }
}