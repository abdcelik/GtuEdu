import com.abdcelik.*;

public class TestDriver
{
    public static void main(String[] args)
    {
        FileSystemTree fileSys = null;

        System.out.println("----------------------------------------------------");
        System.out.println("TEST01 - Constructor of FileSystemTree");
        System.out.println("When root name does not contain / character");
        System.out.println("name of root = \"root\"");
        fileSys = new FileSystemTree("root");
        System.out.println("The file system was created successfully!");
        System.out.println("The File System");
        System.out.println(fileSys);

        System.out.println("TEST02 - Constructor of FileSystemTree");
        System.out.println("When root name contains / character");
        System.out.println("name of root = \"root/dir1\"");
        fileSys = new FileSystemTree("root/dir1");
        System.out.println("The file system was created successfully!");
        System.out.println("The File System");
        System.out.println(fileSys);

        System.out.println("----------------------------------------------------");
        System.out.println("TEST03 - void addDir(String path)");
        System.out.println("Adding a directory to directory with valid path");
        System.out.println("Paths : \"root/dir1\",\"root/dir2\",\"root/dir1/dir3\"");
        System.out.println("Before adding the directory to the system");
        fileSys = new FileSystemTree("root");
        System.out.println(fileSys);
        fileSys.addDir("root/dir1");
        fileSys.addDir("root/dir2");
        fileSys.addDir("root/dir1/dir3");
        System.out.println("After adding the directory to the system");
        System.out.println(fileSys);

        System.out.println("TEST04 - void addDir(String path)");
        System.out.println("Adding a directory to directory with invalid path");
        System.out.println("Path : \"root1/dir1\"");
        System.out.println("Before adding the directory to the system");
        System.out.println(fileSys);
        fileSys.addDir("root1/dir1");
        System.out.println("After adding the directory to the system");
        System.out.println(fileSys);

        System.out.println("TEST05 - void addDir(String path)");
        System.out.println("Adding the existing directory again");
        System.out.println("Path : \"root/dir1\"");
        System.out.println("Before adding the directory to the system");
        System.out.println(fileSys);
        fileSys.addDir("root/dir1");
        System.out.println("After adding the directory to the system");
        System.out.println(fileSys);

        System.out.println("TEST06 - void addDir(String path)");
        System.out.println("Adding null using addDir method");
        System.out.println("Path : null");
        System.out.println("Before adding the directory to the system");
        System.out.println(fileSys);
        fileSys.addDir(null);
        System.out.println("After adding the directory to the system");
        System.out.println(fileSys);

        System.out.println("----------------------------------------------------");
        System.out.println("TEST07 - void addFile(String path)");
        System.out.println("Adding a file to directory with valid path");
        System.out.println("Paths : \"root/file1.txt\",\"root/dir1/file2.txt\",\n\t\"root/dir1/dir3/file3.txt\"");
        System.out.println("Before adding the file to the system");
        System.out.println(fileSys);
        fileSys.addFile("root/file1.txt");
        fileSys.addFile("root/dir1/file2.txt");
        fileSys.addFile("root/dir1/dir3/file3.txt");
        System.out.println("After adding the file to the system");
        System.out.println(fileSys);

        System.out.println("TEST08 - void addFile(String path)");
        System.out.println("Adding a file to directory with invalid path");
        System.out.println("Path : \"root/dir4/file4.txt\"");
        System.out.println("Before adding the file to the system");
        System.out.println(fileSys);
        fileSys.addFile("root/dir4/file4.txt");
        System.out.println("After adding the file to the system");
        System.out.println(fileSys);

        System.out.println("TEST09 - void addFile(String path)");
        System.out.println("Adding the existing file again");
        System.out.println("Path : \"root/dir1/file2.txt\"");
        System.out.println("Before adding the file to the system");
        System.out.println(fileSys);
        fileSys.addFile("root/dir1/file2.txt");
        System.out.println("After adding the file to the system");
        System.out.println(fileSys);

        System.out.println("TEST10 - void addFile(String path)");
        System.out.println("Adding null using addFile method");
        System.out.println("Path : null");
        System.out.println("Before adding the file to the system");
        System.out.println(fileSys);
        fileSys.addFile(null);
        System.out.println("After adding the file to the system");
        System.out.println(fileSys);


        System.out.println("----------------------------------------------------");
        System.out.println("TEST11 - void search(String searched)");
        System.out.println("Testing search method");
        System.out.println("Searching a valid characters");
        System.out.println("Searched characters : \"2\"");
        System.out.println("The file system");
        System.out.println(fileSys);
        fileSys.search("2");

        System.out.println("TEST12 - void search(String searched)");
        System.out.println("Searching a invalid characters");
        System.out.println("Searched characters : \"5\"");
        System.out.println("The file system");
        System.out.println(fileSys);
        fileSys.search("5");

        System.out.println("TEST13 - void search(String searched)");
        System.out.println("Searching null using search method");
        System.out.println("Searched characters : null");
        System.out.println("The file system");
        System.out.println(fileSys);
        fileSys.search(null);

        System.out.println("----------------------------------------------------");
        System.out.println("TEST14 - void remove(String path)");
        System.out.println("Removing a invalid directory");
        System.out.println("Path : \"root/dir1/dir5\"");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove("root/dir1/dir5");
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("TEST15 - void remove(String path)");
        System.out.println("Removing a leaf directory");
        System.out.println("Path : \"root/dir2\"");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove("root/dir2");
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("TEST16 - void remove(String path)");
        System.out.println("Removing a non-leaf directory");
        System.out.println("Path : \"root/dir1/dir3\"");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove("root/dir1/dir3");
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("TEST17 - void remove(String path)");
        System.out.println("Removing a invalid file");
        System.out.println("Path : \"root/file3.txt\"");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove("root/dir1/dir3/file3.txt");
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("TEST18 - void remove(String path)");
        System.out.println("Removing a valid file");
        System.out.println("Path : \"root/file1.txt\"");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove("root/file1.txt");
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("TEST19 - void remove(String path)");
        System.out.println("Removing null using remove method");
        System.out.println("Path : null");
        System.out.println("Before removing method the system is");
        System.out.println(fileSys);
        fileSys.remove(null);
        System.out.println("After removing method the system is");
        System.out.println(fileSys);

        System.out.println("----------------------------------------------------");
        System.out.println("TEST20 - void printFileSystem()");
        fileSys.printFileSystem();
    }
}
