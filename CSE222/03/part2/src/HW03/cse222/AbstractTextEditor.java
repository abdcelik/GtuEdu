package HW03.cse222;

import java.util.List;
import java.util.ListIterator;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;

/**
 * An abstract class for text editor.
 */
public abstract class AbstractTextEditor
{
    /** Character container to keep data. */
    protected List<Character> list;
    private int size_ = 0;

    public int size() { return list.size(); }

    /**
     * Read method to read in a text file and construct the text without using the iterator.
     * @param fileName file name to read
     */
    public void read(String fileName)
    {
        list.clear();

        try
        {
            File file = new File(fileName);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferReader = new BufferedReader(fileReader);
            int content;

            while((content = bufferReader.read()) != -1)
                if(content != '\r')
                    list.add((char)content);
        }
        catch(java.io.FileNotFoundException e)
        {
            System.out.println("Exception caught!\nError! File could not founded!");
        }
        catch(java.io.IOException e)
        {
            System.out.println("Input Output Exception!");
        }
    }

    /**
     * Read method to read in a text file and construct the text with using the iterator.
     * @param fileName file name to read
     */
    public void readWithIterator(String fileName)
    {
        list.clear();

        try
        {
            ListIterator<Character> iter = list.listIterator();
            File file = new File(fileName);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferReader = new BufferedReader(fileReader);
            int content;

            while((content = bufferReader.read()) != -1)
                if(content != '\r')
                    iter.add((char)content);
        }
        catch(java.io.FileNotFoundException e)
        {
            System.out.println("Error! File could not founded!");
        }
        catch(java.io.IOException e)
        {
            System.out.println("Input Output Exception!");
        }
    }

    /**
     * Add one or more characters (given as a string) at the specified position(given as an integer index) in your text without using the iterator.
     * @param index specified position.
     * @param text given text.
     * @throws IndexOutOfBoundsException if index is invalid.
     */
    public void add(int index, String text)
    {
        if(index < 0 || index > size())
            throw new IndexOutOfBoundsException("Invalid Index!");

        for(int i=0 ; i < text.length() ; ++i)
            list.add(index+i,text.charAt(i));
    }

    /**
     * Add one or more characters (given as a string) at the specified position(given as an integer index) in your text with using the iterator.
     * @param index specified position.
     * @param text given text.
     * @throws IndexOutOfBoundsException if index is invalid.
     */
    public void addWithIterator(int index, String text)
    {
        if(index < 0 || index > size())
            throw new IndexOutOfBoundsException("Invalid Index!");

        ListIterator<Character> iter = list.listIterator(index);

        for(int i=0 ; i < text.length() ; ++i)
            iter.add(text.charAt(i));
    }

    /**
     * Return the start index of the first occurrence of the searched group of characters without using the iterator.
     * @param text given text.
     * @return index of first occurrence of the searched string.
     */
    public int find(String text)
    {
        int equality;
        int firstOccurrenceIndex;

        for(int i=0 ; i < list.size() ; ++i)
            if(text.charAt(0) == list.get(i))
            {
                firstOccurrenceIndex = i;

                for(int j = equality = 0 ; i < list.size() && j < text.length() && text.charAt(j) == list.get(i) ; ++j , ++i, ++equality);

                if(equality == text.length())
                    return firstOccurrenceIndex;
            }

        return -1;
    }

    /**
     * Return the start index of the first occurrence of the searched group of characters with using the iterator.
     * @param text given text.
     * @return index of first occurrence of the searched string.
     */
    public int findWithIterator(String text)
    {
        int equality;
        int firstOccurrenceIndex;
        char element;

        for(ListIterator<Character> iter = list.listIterator() ; iter.hasNext() ;)
        {
            if(text.charAt(0) == (element = iter.next()))
            {
                firstOccurrenceIndex = iter.previousIndex();

                for(int j = equality = 0 ; iter.hasNext() && j < text.length() && text.charAt(j) == element ; ++j , element = iter.next() , ++equality);

                if(equality == text.length())
                    return firstOccurrenceIndex;
            }
        }

        return -1;
    }

    /**
     * Replace all occurrences of a character with another character without using the iterator.
     * @param target character to be changed.
     * @param newChar new character to be wanted.
     */
    public void replace(char target, char newChar)
    {
        for(int index ; (index = list.indexOf(target)) != -1 ; list.set(index,newChar));
    }

    /**
     * Replace all occurrences of a character with another character with using the iterator.
     * @param target character to be changed.
     * @param newChar new character to be wanted.
     */
    public void replaceWithIterator(char target, char newChar)
    {
        for(ListIterator<Character> iter = list.listIterator(); iter.hasNext() ;)
            if(iter.next() == target)
                iter.set(newChar);
    }

    /**
     * Create string version of the text.
     * @return string that represent text.
     */
    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();

        for (Character character : list) builder.append(character);

        return builder.toString();
    }
}
