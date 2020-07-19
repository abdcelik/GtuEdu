package com.abdcelik;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * User interface for the system.
 * @param <E> generic type for managing system. Generic type must implement MenuDrivenInterface
 * @author Abdullah Celik
 */
public class UserInterface<E extends MenuDrivenInterface>
{
    /** Keeps the system */
    private E menu;
    /** Keeps the administrator of the system */
    private MenuDrivenAdministratorInterface admin;

    /**
     * Constructor with one parameter for building user interface.
     * @param data given menu structure
     */
    public UserInterface(E data)
    {
        menu = data;
        admin = menu.getAdmin("admin");

        // System contains these softwares.
        admin.addSoftware("Adobe Photoshop 6.0",10,"100");
        admin.addSoftware("Adobe Photoshop 6.2",5,"200");
        admin.addSoftware("Norton 4.5",10,"80");
        admin.addSoftware("Norton 5.5",5,"160");
        admin.addSoftware("Adobe Flash 3.3",10,"60");
        admin.addSoftware("Adobe Flash 4.4",5,"120");
    }

    /**
     * Runs the user interface.
     */
    public void run()
    {
        changeAdminPassword("admin",getString("Please determine administrator password for managing software system: "));
        entranceMenu();
    }

    /**
     * Displays entrance menu.
     */
    private void entranceMenu()
    {
        boolean exit = false;

        while(!exit)
        {
            System.out.println("---- Welcome to Menu-Driven Program ----");
            System.out.println("1- Login to the system");
            System.out.println("2- Search software");
            System.out.println("0- Exit");
            String choice = getString("Choice: ");

            switch(choice)
            {
                case "1":
                    if(admin.getPassword().equals(getString("Password: ")))
                        adminMenu();
                    else
                        System.out.println("Wrong password!");
                    break;
                case "2":
                    Software item = menu.searchSoftware(getString("Software name:"));
                    if(item == null)
                        System.out.println("Software couldn't be founded!");
                    else
                        System.out.println(item);
                    break;
                case "0":
                    exit = true;
                    break;
            }
        }
    }

    /**
     * Displays administrator's menu
     */
    private void adminMenu()
    {
        boolean exit = false;

        while(!exit)
        {
            System.out.println("---- Welcome ----");
            System.out.println("1- Add a software");
            System.out.println("2- Delete a software");
            System.out.println("3- Update a software");
            System.out.println("4- Search a software");
            System.out.println("5- Change password");
            System.out.println("0- Exit");
            String choice = getString("Choice: ");

            switch(choice)
            {
                case "1":
                    if(admin.addSoftware(getString("Software Name: "),getDelimitedIntInput("Quantity: ",1),getString("Price: ")))
                        System.out.println("Adding software is successful!");
                    else
                        System.out.println("Adding software isn't successful!");
                    break;
                case "2":
                    if(admin.removeSoftware(getString("Software Name: ")))
                        System.out.println("Removing software is successful!");
                    else
                        System.out.println("Removing software isn't successful!");
                    break;
                case "3":
                    if(admin.updateSoftware(getString("Name: "),getString("New name: "),getDelimitedIntInput("New quantity(integer): ",0),getString("New price: ")))
                        System.out.println("Updating software is successful!");
                    else
                        System.out.println("Updating software isn't successful!");
                    break;
                case "4":
                    Software item = admin.searchSoftware(getString("Software name: "));
                    if(item == null)
                        System.out.println("Software couldn't be founded!");
                    else
                        System.out.println(item);
                    break;
                case "5":
                    if(changeAdminPassword(getString("Current password: "),getString("New password: ")))
                        System.out.println("Changing password is successful!");
                    else
                        System.out.println("Changing password isn't successful!");
                    break;
                case "0":
                    exit = true;
                    break;
            }
        }
    }

    /**
     * Changes administrator password only if old password is true.
     * @param oldPassword administrator's current password
     * @param newPassword administrator's new password
     * @return true if it can be changed. Otherwise false
     */
    private boolean changeAdminPassword(String oldPassword, String newPassword)
    {
        if(!admin.getPassword().equals(oldPassword))
            return false;

        admin.setPassword(newPassword);
        return true;
    }

    /**
     * Takes string from the user.
     * @param message printed message
     * @return taken message
     */
    private String getString(String message)
    {
        Scanner scan = new Scanner(System.in);
        System.out.println(message);
        return scan.nextLine();
    }

    /**
     * Checks whether parameter contains special characters
     * @param quantity given quantity
     * @return true if given quantity contains some special characters
     */
    private boolean checkQuantityInput(String quantity)
    {
        Pattern p = Pattern.compile("[^0-9]", Pattern.CASE_INSENSITIVE);
        Matcher m = p.matcher(quantity);
        return !m.find();
    }

    /**
     * Converts given string to integer
     * @param input given string
     * @return integer form of string
     */
    private int stringToInt(String input) { return Integer.parseInt(input); }

    /**
     * Prints message and takes string from user while input is greater than given lower bound.
     * @param message given message
     * @param lowerBound given lower bound
     * @return integer form of taken string
     */
    private int getDelimitedIntInput(String message, int lowerBound)
    {
        String str;
        int input = lowerBound-1;

        while(input < lowerBound)
        {
            while(!checkQuantityInput((str = getString(message))));
            input = stringToInt(str);
        }

        return input;
    }
}