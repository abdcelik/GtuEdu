import com.SearchTree.BinarySearchTree;
import com.abdcelik.*;

public class DriverMain
{
    public static boolean runUserInterface = true;
    public static boolean testMenuDriven = false;

    public static void main(String[] args)
    {
        // If data structure for storing is to be changed, don't break the structre below.
        // UserInterface<MenuDriven<"CHANGEHERE"<Software>>userInterface = new UserInterface<>(new MenuDriven<>(new "CHANGEHERE"));

        if(runUserInterface)
        {
            UserInterface<MenuDriven<BinarySearchTree<Software>>> userInterface = new UserInterface<>(new MenuDriven<>(new BinarySearchTree<>()));
            userInterface.run();
        }

        if(testMenuDriven)
            testMenuDriven();
    }

    public static void testMenuDriven()
    {
        BinarySearchTree<Software> bst = new BinarySearchTree<>();
        MenuDriven<BinarySearchTree<Software>> menu;
        MenuDrivenAdministratorInterface admin;

        System.out.println("------------------------------------------");
        System.out.println("Menu Driven will be test by using BinarySearchTree implementation(in the book)");

        System.out.println("TEST01");
        System.out.println("Constructor with one parameter will be tested. Constructor will be called as\n\tnew MenuDriven(bst)");
        menu = new MenuDriven<>(bst);
        System.out.println("Menu Driven was created successfully!");

        System.out.println("TEST02");
        System.out.println("Constructor with two parameter will be tested. Constructor will be called as\n\tnew MenuDriven(\"psw\",bst)");
        menu = new MenuDriven<>("psw",bst);
        System.out.println("Menu Driven was created successfully!");

        System.out.println("\n------------------------------------------");
        System.out.println("Testing boolean addSoftware(String name, int quantity, String price");
        System.out.println("This feature isn't public. So, firstly getAdmin method will be called");
        System.out.println("If password is true, adding process is start");
        System.out.println("If password is false, getAdmin method returns null");

        System.out.println("\nTEST03");
        System.out.println("When administrator password is wrong, method will be called as\n\tmenu.getAdmin(\"worngpsw\")");
        admin = menu.getAdmin("wrongpsw");
        if(admin == null)
            System.out.println("Login process isn't successful! Password is wrong");

        System.out.println("\nTEST04");
        System.out.println("When administrator password is correct and system doesn't include software to add");
        System.out.println("Firstly, getAdmin(\"psw\") method will be called");
        System.out.println("Secondly, addSoftware method will be called respectively as\n\tadmin.addSoftware(\"Office 365\",5,\"$100\"),admin.addSoftware(\"Adobe Photoshop 6.0\",10,\"$200\"),\n\tadmin.addSoftware(\"Adobe Photoshop 6.2\",5,\"$100\"),admin.addSoftware(\"Skype\",3,\"$15\")");
        admin = menu.getAdmin("psw");
        if(admin != null)
            System.out.println("Calling administrator is successful! Password is correct");
        System.out.println("\nBefore adding, bst:");
        System.out.println(bst);
        System.out.println("Adding process for Office 365: " + admin.addSoftware("Office 365",5,"100"));
        System.out.println("Adding process for Adobe Photoshop 6.0: " + admin.addSoftware("Adobe Photoshop 6.0",10,"$200"));
        System.out.println("Adding process for Adobe Photoshop 6.2: " + admin.addSoftware("Adobe Photoshop 6.2",5,"$100"));
        System.out.println("Adding process for Skype: " + admin.addSoftware("Skype",3,"$15"));
        System.out.println("\nAfter adding, bst:");
        System.out.println(bst);

        System.out.println("\nTEST05");
        System.out.println("When administrator password is correct and system includes software to add");
        System.out.println("Firstly, getAdmin(\"psw\") method will be called");
        System.out.println("Secondly, addSoftware method will be called as admin.addSoftware(\"Office 365\",5,\"$100\")");

        admin = menu.getAdmin("psw");
        if(admin != null)
            System.out.println("Calling administrator is successful! Password is correct");
        System.out.println("\nBefore adding, bst:");
        System.out.println(bst);
        System.out.println("Adding process: " + admin.addSoftware("Office 365",5,"$100"));
        System.out.println("\nAfter adding, bst:");
        System.out.println(bst);

        System.out.println("\n------------------------------------------");
        System.out.println("Testing Software searchSoftware(String name) method");
        System.out.println("TEST06");
        System.out.println("When system contains software, method will be called as\n\tmenu.searchSoftware(\"Adobe Photoshop 6.0\")");
        System.out.println("Finding: " + menu.searchSoftware("Adobe Photoshop 6.0"));

        System.out.println("\nTEST07");
        System.out.println("When system doesn't contain software, method will be called as\n\tmenu.searchSoftware(\"Norton 4.5\")");
        System.out.println("Finding: " + menu.searchSoftware("Norton 4.5"));

        System.out.println("\n------------------------------------------");
        System.out.println("Testing boolean removeSoftware(String name) method");
        System.out.println("This feature isn't public. So, firstly getAdmin method will be called");
        System.out.println("If password is true, removing process is start");
        System.out.println("If password is false, getAdmin method returns null");

        System.out.println("\nTEST08");
        System.out.println("When administrator password is wrong, method will be called as\n\tmenu.getAdmin(\"worngpsw\")");
        admin = menu.getAdmin("wrongpsw");
        if(admin == null)
            System.out.println("Login process isn't successful! Password is wrong");

        System.out.println("\nTEST09");
        System.out.println("When administrator password is correct and system contains software,\nmethod will be called respectively as\n\tadmin.removeSoftware(\"Adobe Photoshop 6.0\"), admin.removeSoftware(\"Adobe Photoshop 6.2\")");
        admin = menu.getAdmin("psw");
        if(admin != null)
            System.out.println("Calling administrator is successful! Password is correct");
        System.out.println("\nBefore removing, bst:");
        System.out.println(bst);
        System.out.println("Removing Adobe Photoshop 6.0: " + admin.removeSoftware("Adobe Photoshop 6.0"));
        System.out.println("\nAfter removing, bst:");
        System.out.println(bst);
        System.out.println("Removing Adobe Photoshop 6.0: " + admin.removeSoftware("Adobe Photoshop 6.2"));
        System.out.println("\nAfter removing, bst:");
        System.out.println(bst);

        System.out.println("\nTEST10");
        System.out.println("When administrator password is correct and system doesn't contain software,\nmethod will be called respectively as\n\tadmin.removeSoftware(\"Netflix\")");
        System.out.println("\nBefore removing, bst:");
        System.out.println(bst);
        System.out.println("Removing Adobe Photoshop 6.0: " + admin.removeSoftware("Netflix"));
        System.out.println("\nAfter removing, bst:");
        System.out.println(bst);

        System.out.println("\n------------------------------------------");
        System.out.println("Testing boolean updateSoftware(String name, String newName, int newQuantity, String newPrice) method");
        System.out.println("This feature isn't public. So, firstly getAdmin method will be called");
        System.out.println("If password is true, removing process is start");
        System.out.println("If password is false, getAdmin method returns null");

        System.out.println("TEST11");
        System.out.println("When administrator password is true and system contains software, method will be called as\n\tadmin.updateSoftware(\"Office 365\",\"Office 365\",1,\"$1\")");
        admin = menu.getAdmin("psw");
        if(admin != null)
            System.out.println("Calling administrator is successful! Password is correct");
        System.out.println("\nBefore updating, bst:");
        System.out.println(bst);
        System.out.println("Updating process: " + admin.updateSoftware("Office 365","Office 365",1,"$1"));
        System.out.println("\nAfter updating, bst:");
        System.out.println(bst);

        System.out.println("TEST12");
        System.out.println("When administrator password is true and system doesn't contain software, method will be called as\n\tadmin.updateSoftware(\"Adobe Flash\",\"Adobe Flash\",1,\"$1\")");
        System.out.println("\nBefore updating, bst:");
        System.out.println(bst);
        System.out.println("Updating process: " + admin.updateSoftware("Adobe Flash","Adobe Flash",1,"$1"));
        System.out.println("\nAfter updating, bst:");
        System.out.println(bst);

        System.out.println("TEST13");
        System.out.println("When administrator password is true and system contains software, method will be called as\n\tadmin.updateSoftware(\"Office 365\",\"Office 365\",0,$10)");
        System.out.println("\nBefore updating, bst:");
        System.out.println(bst);
        System.out.println("Updating process: " + admin.updateSoftware("Office 365","Office 365",0,"$10"));
        System.out.println("\nAfter updating, bst:");
        System.out.println(bst);
    }
}