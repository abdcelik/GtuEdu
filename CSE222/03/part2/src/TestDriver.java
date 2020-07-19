import HW03.cse222.*;
import java.util.logging.Logger;
import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;

public class TestDriver
{
    public static void main(String[] args) throws Exception
    {
        AbstractTextEditor ArrayListWithoutIter = new TextEditorUsingArrayList();
        AbstractTextEditor ArrayListWithIter = new TextEditorUsingArrayList();
        AbstractTextEditor LinkedListWithoutIter = new TextEditorUsingLinkedList();
        AbstractTextEditor LinkedListWithIter = new TextEditorUsingLinkedList();
        Logger logger = null;

        if((logger = open()) == null)
            throw new Exception("Logger couldn't be opened!");

        testList(logger,ArrayListWithoutIter,ArrayListWithIter,"text1.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
        //testList(logger,ArrayListWithoutIter,ArrayListWithIter,"text2.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
        //testList(logger,ArrayListWithoutIter,ArrayListWithIter,"text3.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
        //testList(logger,LinkedListWithoutIter,LinkedListWithIter,"text1.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
        //testList(logger,LinkedListWithoutIter,LinkedListWithIter,"text2.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
        //testList(logger,LinkedListWithoutIter,LinkedListWithIter,"text3.txt","ADDEDMESSAGE","adipiscin ",'A','X',"-- Now Testing Array List with iterator and without iterator --");
    }

    public static void testList(Logger logger, AbstractTextEditor testWithoutIter, AbstractTextEditor testWithIter, String fileName, String addWord, String findWord, char replaceWord, char newWord, String message)
    {
        long startTime,endTime;

        logger.info("-----------------------------------------------------------------------\n");
        logger.info(message);
        logger.info("File Name : " + fileName + "\n");

        startTime = System.nanoTime();
        testWithoutIter.read(fileName);
        endTime = System.nanoTime();

        logger.info("T01 -  read(\"" + fileName + "\") and size : " + testWithoutIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithoutIter + "\n");

        startTime = System.nanoTime();
        testWithIter.read(fileName);
        endTime = System.nanoTime();

        logger.info("T02 -  readWithIterator(\"" + fileName + "\") and size : " + testWithIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithIter + "\n");



        logger.info("-----------------------------------------------------------------------\n");

        startTime = System.nanoTime();
        testWithoutIter.add(testWithoutIter.size()-5,addWord);
        endTime = System.nanoTime();

        logger.info("T03 - add(" + (testWithoutIter.size()-5) + ",\"" + addWord + "\") and size : " + testWithoutIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithoutIter + "\n");

        startTime = System.nanoTime();
        testWithIter.addWithIterator(testWithIter.size()-5,addWord);
        endTime = System.nanoTime();

        logger.info("T04 - addWithIterator(" + (testWithIter.size()-5) + ",\"" + addWord + "\") and size : " + testWithIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithIter + "\n");



        logger.info("-----------------------------------------------------------------------\n");

        startTime = System.nanoTime();
        int index = testWithoutIter.find(findWord);
        endTime = System.nanoTime();

        logger.info("T05 - find(\"" + findWord + "\") and size : " + testWithoutIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        logger.info(findWord + " index : " + index);
        System.out.println("Text is : " + testWithoutIter + "\n");


        startTime = System.nanoTime();
        index = testWithIter.findWithIterator(findWord);
        endTime = System.nanoTime();

        logger.info("T06 - findWithIterator(\"" + findWord + "\") and size : " + testWithIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        logger.info(findWord + " index : " + index);
        System.out.println("Text is : " + testWithIter + "\n");



        logger.info("-----------------------------------------------------------------------\n");

        startTime = System.nanoTime();
        testWithoutIter.replace(replaceWord,newWord);
        endTime = System.nanoTime();

        logger.info("T07 - replace('" + replaceWord + "','" + newWord + "') and size : " + testWithoutIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithoutIter + "\n");


        startTime = System.nanoTime();
        testWithIter.replaceWithIterator(replaceWord,newWord);
        endTime = System.nanoTime();

        logger.info("T08 - replaceWithIterator('" + replaceWord + "','" + newWord + "') and size : " + testWithIter.size() + " method called and executed in " + (endTime - startTime)/1000 + " microsecond\n");
        System.out.println("Text is : " + testWithIter + "\n");



        System.out.println("-----------------------------------------------------------------------\n");
        System.out.println("T09 - add(-1,\"" + addWord + "\") method called with invalid index");

        try
        {
            testWithIter.add(-1,addWord);
        }
        catch(Exception e)
        {
            System.out.println("Exception was caught!");
            System.out.println(e);
        }

        System.out.println("-----------------------------------------------------------------------\n");
        System.out.println("T10 - addWithIterator(-1,\"" + addWord + "\") method called with invalid index");

        try
        {
            testWithoutIter.add(-1,addWord);
        }
        catch(Exception e)
        {
            System.out.println("Exception was caught!");
            System.out.println(e);
        }


        System.out.println("-----------------------------------------------------------------------\n");
        System.out.println("T11 - read(\"WrongFileName.txt\") method called with invalid file name");

        testWithoutIter.read("WrongFileName.txt");

        System.out.println("-----------------------------------------------------------------------\n");
        System.out.println("T12 - readWithIterator(\"WrongFileName.txt\") method called with invalid file name");

        testWithIter.readWithIterator("WrongFileName.txt");

    }

    public static Logger open()
    {
        FileHandler handler = null;

        try
        {
            handler = new FileHandler("default.log", true);
        }
        catch(Exception e)
        {
            return null;
        }

        SimpleFormatter formatter = new SimpleFormatter();
        handler.setFormatter(formatter);
        Logger logger = Logger.getLogger("HW03.cse222.AbstractTextEditor");
        logger.addHandler(handler);

        return logger;
    }
}