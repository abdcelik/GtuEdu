package com.abdcelik;

import java.util.Scanner;
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.NoSuchElementException;

/**
 * LibraryAutomationSystem keeps books and its information as Map data structure.
 * @author Abdullah Celik
 */
public class LibraryAutomationSystem
{
    /** Keeps administrator's password of the system as Set data structure*/
    private Set<String> administrators;
    /** Keeps books and its information as Map data structure*/
    private Map<String,Map<String,Set<String>>> library;

    /**
     * No parameter constructor. Allocate memory for administrators and books.
     * If new constructor is created, this constructor must be called.
     */
    private LibraryAutomationSystem()
    {
        administrators = new HashSet<>();
        library = new HashMap<>();
    }

    /**
     * One parameter constructor. Construct library system
     * @param password administrator's password
     * @throws NoSuchElementException if password is null, throws exception
     */
    public LibraryAutomationSystem(String password) throws NoSuchElementException
    {
        this();

        if(password == null)
            throw new NullPointerException("Password should be passed!");

        administrators.add(password);
    }

    /**
     * Adds a new administrator password to the system.
     * @param adminPassword a password owned by the system
     * @param newPassword new password to add
     * @return true if password is added. Otherwise false
     */
    public boolean addAdministrator(String adminPassword, String newPassword)
    {
        if(!checkAdminPassword(adminPassword))
            return false;

        return administrators.add(newPassword);
    }

    /**
     * Changes an existing password with a given password.
     * @param previousPassword previous password
     * @param newPassword new password
     * @return true if password is set. Otherwise false
     */
    public boolean changeAdministratorPassword(String previousPassword, String newPassword)
    {
        if(!administrators.remove(previousPassword))
            return false;

        return addAdministrator(previousPassword,newPassword);
    }

    /**
     * All books of the author in the library will be listed on the screen.
     * Then, whichever book the user chooses, the location(s) of that book will be displayed.
     * @param author given author
     */
    public void searchAuthor(String author)
    {
        String text;

        if((text = searchAuthorBooks(author)).equals("null"))
            System.out.println("Author couldn't be founded!");
        else
        {
            System.out.println(text);
            System.out.println("Which book do you want to see?");
            Scanner scan = new Scanner(System.in);

            String loc = searchAuthorBookLocations(author,scan.nextLine());
            if(loc.equals("null"))
                System.out.println("The book couldn't be founded!");
            else
                System.out.println(loc);
        }

    }

    /**
     * Returns given author's books.
     * @param author given author
     * @return given author's books if author is exist. Otherwise returns "null"
     */
    private String searchAuthorBooks(String author)
    {
        Map<String,Set<String>> book;

        if((book = library.get(author)) == null)
            return "null";
        return book.keySet().toString();
    }

    /**
     * Returns given author's given book's location.
     * @param author given author
     * @param title given book title
     * @return given author's given book's location if location is exist. Otherwise returns "null"
     */
    private String searchAuthorBookLocations(String author, String title)
    {
        Map<String,Set<String>> book = library.get(author);
        Set<String> loc = book.get(title);

        if(loc == null)
            return "null";
        return loc.toString();
    }

    /**
     * Displays given book's author name, location.
     * @param title given book title
     */
    public void searchBook(String title)
    {
        boolean flag = false;

        for(Map.Entry<String, Map<String, Set<String>>> iter : library.entrySet())
            for(String books : iter.getValue().keySet())
                if(books.equals(title))
                {
                    flag = true;
                    System.out.println("Title: " + title);
                    System.out.println("Author: " + iter.getKey());
                    System.out.println("Location: ");
                    for(String loc : iter.getValue().get(title))
                        System.out.println("\t" + decodeLocation(loc));
                    System.out.println();
                }

        if(!flag)
            System.out.println("The book couldn't be founded!");
    }

    /**
     * Adds book with given parameters.
     * @param password administrator password
     * @param author author's name
     * @param title book's title
     * @param corridor book's location
     * @param shelf book's location
     * @return true if book is added. Otherwise false
     */
    public boolean addBook(String password, String author, String title, String corridor, String shelf)
    {
        if(!checkAdminPassword(password))
            return false;

        Map<String,Set<String>> book;
        Set<String> s = new HashSet<>();
        String encodingLoc = encodeLocation(corridor,shelf);
        s.add(encodingLoc);

        if((book = library.get(author)) == null)
        {
            Map<String,Set<String>> m = new HashMap<>();
            m.put(title,s);
            return library.putIfAbsent(author,m) == null;
        }

        Set<String> loc;

        if((loc = book.get(title)) == null)
            return book.putIfAbsent(title,s) == null;

        if(!loc.contains(encodingLoc))
            return loc.add(encodingLoc);
        else
            return false;
    }

    /**
     * Removes book with given parameters.
     * @param password administrator password
     * @param author author's name
     * @param title book's title
     * @param corridor book's location
     * @param shelf book's location
     * @return true if book is removed. Otherwise false
     */
    public boolean removeBook(String password, String author, String title, String corridor, String shelf)
    {
        if(!checkAdminPassword(password))
            return false;

        Map<String,Set<String>> book;

        if((book = library.get(author)) == null)
            return false;

        Set<String> loc;

        if((loc = book.get(title)) == null)
            return false;

        String encodingLoc = encodeLocation(corridor,shelf);

        if(!loc.contains(encodingLoc))
            return false;
        else
            loc.remove(encodingLoc);

        if(loc.size() == 0)
        {
            book.remove(title);

            if(book.size() == 0)
                library.remove(author);
        }

        return true;
    }

    /**
     * Updates book with given parameters.
     * @param password administrator password
     * @param oldAuthor current author
     * @param oldTitle current book's title
     * @param oldCorridor current corridor
     * @param oldShelf current shelf
     * @param newAuthor new author
     * @param newTitle new title
     * @param newCorridor new corridor
     * @param newShelf new shelf
     * @return true if it can be updated. Otherwise false
     */
    public boolean updateBook(String password, String oldAuthor, String oldTitle, String oldCorridor, String oldShelf, String newAuthor, String newTitle, String newCorridor, String newShelf)
    {
        if(!checkAdminPassword(password))
            return false;

        if(removeBook(password,oldAuthor,oldTitle,oldCorridor,oldShelf))
            return addBook(password,newAuthor,newTitle,newCorridor,newShelf);
        return false;
    }

    /**
     * Encodes location. For example Corridor 1 Shelf 1 is c1s1.
     * @param corridor given corridor
     * @param shelf given shelf
     * @return coded location
     */
    private String encodeLocation(String corridor, String shelf) { return "c" + corridor + "s" + shelf; }

    /**
     * Decodes given location. For example c1s1, Corridor 1 Shelf 1.
     * @param location given location
     * @return location
     */
    private String decodeLocation(String location)
    {
        String[] arr = location.split("[cs]+");
        return "Corridor: " + arr[1] + " Shelf: " + arr[2];
    }

    /**
     * Checks administrator passwords.
     * @param password administrator password
     * @return true if password is available.
     */
    private boolean checkAdminPassword(String password) { return administrators.contains(password); }

    /**
     * Returns string representation of the library system.
     * @return string representation of the library system
     */
    @Override
    public String toString() { return library.toString(); }
}