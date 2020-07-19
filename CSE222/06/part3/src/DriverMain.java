import com.abdcelik.*;

public class DriverMain
{
    public static void main(String[] args)
    {
        LibraryAutomationSystem lib;

        System.out.println("--------------------------------------------");
        System.out.println("One parameter constructor");
        System.out.println("\nTEST01\nConstructor called when password is null");

        try
        {
            lib = new LibraryAutomationSystem(null);
        }
        catch(NullPointerException e)
        {
            System.out.println("NullPointerException was caught!");
            System.out.println(e.getMessage());
        }

        System.out.println("\nTEST02\nConstructor called when password is valid");
        System.out.println("Password: pswrd");
        lib = new LibraryAutomationSystem("pswrd");
        System.out.println("Library system was created successfully.");

        System.out.println("--------------------------------------------");
        System.out.println("Testing addBook method");

        System.out.println("\nTEST03\naddBook method will be called with wrong admin password");
        System.out.println("Trial password: wrongpassword");
        System.out.println("Adding: " + lib.addBook("wrongpassword","","","",""));

        System.out.println("\nTEST04\naddBook method will be called with correct password\n\tauthor, book, location aren't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Abdullah");
        System.out.println("Book title: Data Structure");
        System.out.println("Location: Corridor 1 Shelf 1");
        System.out.println("Before adding, library:\n" + lib);
        System.out.println("Adding: " + lib.addBook("pswrd","Abdullah","Data Structure","1","1"));
        System.out.println("After adding, library:\n" + lib);

        System.out.println("\nTEST05\naddBook method will be called with correct password\n\tauthor, book are available and location aren't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Abdullah");
        System.out.println("Book title: Data Structure");
        System.out.println("Location: Corridor 1 Shelf 2");
        System.out.println("Before adding, library:\n" + lib);
        System.out.println("Adding: " + lib.addBook("pswrd","Abdullah","Data Structure","1","2"));
        System.out.println("After adding, library:\n" + lib);

        System.out.println("\nTEST06\naddBook method will be called with correct password\n\tauthor is avaialble and book, location aren't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Abdullah");
        System.out.println("Book title: System Programming");
        System.out.println("Location: Corridor 2 Shelf 1");
        System.out.println("Before adding, library:\n" + lib);
        System.out.println("Adding: " + lib.addBook("pswrd","Abdullah","System Programming","2","1"));
        System.out.println("After adding, library:\n" + lib);

        System.out.println("\nTEST07\naddBook method will be called with correct password\n\tauthor, book, location are available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Abdullah");
        System.out.println("Book title: System Programming");
        System.out.println("Location: Corridor 2 Shelf 1");
        System.out.println("Before adding, library:\n" + lib);
        System.out.println("Adding: " + lib.addBook("pswrd","Abdullah","System Programming","2","1"));
        System.out.println("After adding, library:\n" + lib);

        lib.addBook("pswrd","Abdullah","Data Structure","1","4");

        System.out.println("--------------------------------------------");
        System.out.println("Testing removeBook method");

        System.out.println("\nTEST08\nremoveBook method will be called with wrong admin password");
        System.out.println("Trial password: wrongpassword");
        System.out.println("Removing: " + lib.removeBook("wrongpassword","","","",""));

        System.out.println("\nTEST09\nremoveBook method will be called with correct password\n\tauthor, book, location are available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Abdullah");
        System.out.println("Book title: System Programming");
        System.out.println("Location: Corridor 2 Shelf 1");
        System.out.println("Before removing, library:\n" + lib);
        System.out.println("Removing: " + lib.removeBook("pswrd","Abdullah","System Programming","2","1"));
        System.out.println("After removing, library:\n" + lib);

        System.out.println("\nTEST10\nremoveBook method will be called with correct password\n\t author, book are available and location isn't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Halit");
        System.out.println("Book title: C Programming");
        System.out.println("Location: Corridor 4 Shelf 0");
        System.out.println("Before removing, library:\n" + lib);
        System.out.println("Removing: " + lib.removeBook("pswrd","Halit","C Programming","4","0"));
        System.out.println("After removing, library:\n" + lib);

        System.out.println("\nTEST11\nremoveBook method will be called with correct password\n\tauthor is available and book isn't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: Halit");
        System.out.println("Book title: wrongbook");
        System.out.println("Location: Corridor 4 Shelf 1");
        System.out.println("Before removing, library:\n" + lib);
        System.out.println("Removing: " + lib.removeBook("pswrd","Halit","wrongbook","4","1"));
        System.out.println("After removing, library:\n" + lib);

        System.out.println("\nTEST12\nremoveBook method will be called with correct password\n\tauthor isn't available");
        System.out.println("Password: pswrd");
        System.out.println("Author: wrongauthor");
        System.out.println("Book title: C Programming");
        System.out.println("Location: Corridor 4 Shelf 1");
        System.out.println("Before removing, library:\n" + lib);
        System.out.println("Removing: " + lib.removeBook("pswrd","wrongauthor","C Programming","4","1"));
        System.out.println("After removing, library:\n" + lib);

        System.out.println("--------------------------------------------");
        System.out.println("Testing updateBook method");

        System.out.println("\nTEST13\nupdateBook method will be called with wrong admin password");
        System.out.println("Trial password: wrongpassword");
        System.out.println("Updating: " + lib.updateBook("wrongpassword","","","","","","","",""));

        System.out.println("\nTEST14\nupdateBook method will be called with correct password\n\t book is available");
        System.out.println("Password : pswrd");
        System.out.println("Old book author: Abdullah");
        System.out.println("Old book title: Data Structure");
        System.out.println("Old book location: Corridor 1 Shelf 1");
        System.out.println("New book author: Ismail");
        System.out.println("New book title: Data Structure 2");
        System.out.println("New book location: Corridor 1 Shelf 5");
        System.out.println("Before updating, library:\n" + lib);
        System.out.println("Updating: " + lib.updateBook("pswrd","Abdullah","Data Structure","1","1","Ismail","Data Structure 2","1","5"));
        System.out.println("After updating, library:\n" + lib);

        System.out.println("\nTEST15\nupdateBook method will be called with correct password\n\tbook isn't available");
        System.out.println("Password : pswrd");
        System.out.println("Old book author: wrong");
        System.out.println("Old book title: wrong");
        System.out.println("Old book location: wrong");
        System.out.println("New book author: Celik");
        System.out.println("New book title: Data Structure 3");
        System.out.println("New book location: Corridor 1 Shelf 6");
        System.out.println("Before updating, library:\n" + lib);
        System.out.println("Updating: " + lib.updateBook("pswrd","wrong","wrong","wrong","wrong","Celik","Data Structure 3","1","6"));
        System.out.println("After updating, library:\n" + lib);

        System.out.println("--------------------------------------------");
        System.out.println("Testing searchAuthor method");

        System.out.println("\nTEST16\nsearchAuthor method will be called with author that exist");
        System.out.println("Author: Abdullah");
        System.out.println("Before searching, library:\n" + lib);
        lib.searchAuthor("Abdullah");

        System.out.println("\nTEST17\nsearchAuthor method will be called with author that doesn't exist");
        System.out.println("Author: wrong");
        System.out.println("Before searching, library:\n" + lib);
        lib.searchAuthor("wrong");

        lib.addBook("pswrd","Celik","Data Structure","5","1");

        System.out.println("--------------------------------------------");
        System.out.println("Testing searchBook method");

        System.out.println("\nTEST18\nsearchBook method will be called with book that exist");
        System.out.println("Book title: Data Structure");
        System.out.println("Before searching, library:\n" + lib);
        lib.searchBook("Data Structure");

        System.out.println("\nTEST19\nsearchBook method will be called with book that doesn't exist");
        System.out.println("Book title: wrong");
        System.out.println("Before searching, library:\n" + lib);
        lib.searchBook("wrong");
    }
}