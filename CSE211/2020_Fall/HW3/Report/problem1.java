import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;

public class problem1
{
    public static void main(String[] args)
    {
        writeToFile(readFromFile("input.txt"),"output.txt");
    }

    /**
     * Reads set and relation from file using given file name.
     * @param fileName given file name
     * @return relations, if file name is valid. Otherwise null
     */
    public static Vector<problem1_POSET> readFromFile(String fileName)
    {
        Scanner scanner;
        Vector<problem1_POSET> relations = new Vector<>();

        try { scanner = new Scanner(new File(fileName)); } // Creates a scanner with given file name
        catch(FileNotFoundException e) { System.err.println("ERROR! No such file: " + fileName); return null; } // If file name is invalid, prints error message

        while(scanner.hasNext()) // Reads entire file
        {
            problem1_POSET relation = new problem1_POSET();
            int size = Integer.parseInt(scanner.next()); // Reads size of relation from file
            String[] elements = scanner.next().split(","); // Reads next line and splits this line with ','

            for(String element : elements) // Adds the read elements to relation
                relation.addElement(element);

            for(int i=0 ; i < size ; ++i) // Reads pairs up to read size
            {
                String line = scanner.next(); // Read a pair
                String[] pair = line.split(","); // Split this pair with ','
                if(pair.length != 2 || !relation.addRelation(pair[0],pair[1])) // If read pair is invalid format
                {
                    System.err.println("ERROR! No such relation: " + line); // Print error message
                    return null;
                }
            }
            relations.add(relation); // Add read pair to the relation
        }
        scanner.close();
        return relations;
    }

    /**
     * Writes properties of the given relations to the file using given file name.
     * @param relations given relation
     * @param fileName given file name
     */
    public static void writeToFile(Vector<problem1_POSET> relations, String fileName)
    {
        if(relations == null || fileName == null) // Checks null or not
            return;

        try
        {
            FileWriter fileWriter = new FileWriter(fileName); // Creates file writer
            for(problem1_POSET rel : relations) // All given relation
            {
                fileWriter.write("n\n");
                fileWriter.write(rel.toHasseDiagram()); // String representation of the relation(reflexive, symmetric, antisymmetric, transitive)
            }
            fileWriter.close();
        }
        catch(IOException e) { System.err.println("ERROR! File could not be opened: " + fileName); } // If file couldn't be opened, print error message
    }
}