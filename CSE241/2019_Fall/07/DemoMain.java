import cse241_hw7.*;

/**
 * This class is only testing BoardArray1D, BoardArray2D and GlobalFunction.
 * @author Abdullah_Celik_171044002
 */
public class DemoMain
{
	public static void main(String[] args)
	{
		checkBoardArray1D();	
		checkBoardArray2D();
		checkGlobalFunction();
	}
	
	/**
	 * Prints board details.
	 * @param board
	 */
	public static void printBoardDetails(AbstractBoard board)
	{
		System.out.println("Row : " + board.getRow());
		System.out.println("Column : " + board.getColumn());
		System.out.println("Blank Position(x,y) : (" + board.getXPosition() + "," + board.getYPosition() + ")");
		System.out.println("Last moves : " + board.lastMove());
		System.out.println("Total moves : " + board.numberOfMoves() + "\n");
		System.out.println(board);
	}

	/**
	 * Testing BoardArray1D
	 */
	public static void checkBoardArray1D()
	{
		System.out.println("\n------------------ Test All Function of BoardArray1D ------------------\n");

		System.out.println("_______________  No parameter constructor testing  ________________");
		BoardArray1D a1 = new BoardArray1D();
		printBoardDetails(a1);
		
		System.out.println("_______________  Two parameter constructor testing  _______________");
		BoardArray1D a2 = new BoardArray1D(4,6);
		printBoardDetails(a2);
		
		System.out.println("___________________  Copy constructor testing  ____________________");
		BoardArray1D a3 = new BoardArray1D(a2);
		printBoardDetails(a3);
		
		System.out.println("__________________  Clone function testing  __________________");
		BoardArray1D a4 = new BoardArray1D();
		System.out.println("Before clone function :");
		printBoardDetails(a4);
		System.out.println("After clone function : ");
		try
		{
			a4 = (BoardArray1D)a3.clone();
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			printBoardDetails(a4);
		}
		
		System.out.println("________________  readFromFile function testing  _________________");
		BoardArray1D a5 = new BoardArray1D();
		System.out.println("Reading testBoard/board.txt");
		try
		{
			if(a5.readFromFile("testBoard/board.txt"))
				System.out.println("Reading is successful");
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			System.out.println("Reading is over");
			printBoardDetails(a5);
		}
		
		System.out.println("_________________  writeToFile function testing  _________________");
		System.out.println("Writing testBoard/writeBoard1D.txt");
		try
		{
			a5.writeToFile("testBoard/writeBoard1D.txt");
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			System.out.println("Writing is over");
			System.out.println(a5);
		}
		
		System.out.println("____________________  reset function testing  ____________________");
		System.out.println("Before reset function :");
		printBoardDetails(a5);
		System.out.println("\nAfter reset function :");
		a5.reset();
		printBoardDetails(a5);
		
		System.out.println("___________________  setSize function testing  ___________________");
		System.out.println("Before setSize function :");
		BoardArray1D a6 = new BoardArray1D();
		printBoardDetails(a6);
		System.out.println("\nAfter setSize function :");
		a6.setSize(5,5);
		printBoardDetails(a6);
		
		System.out.println("____________________  move function testing  ____________________");
		BoardArray1D a7 = new BoardArray1D(4,4);
		printBoardDetails(a7);
		a7.move('U');
		printBoardDetails(a7);
		a7.move('L');
		printBoardDetails(a7);
		a7.move('U');
		printBoardDetails(a7);
		
		System.out.println("___________________  equals function testing  ____________________");
		BoardArray1D a8 = new BoardArray1D(3,3);
		BoardArray1D a9 = new BoardArray1D(3,4);
		printBoardDetails(a8);
		printBoardDetails(a9);
		if(a8.equals(a9) == true)
			System.out.println("\n-> These board are equal\n");
		else
			System.out.println("\n-> These board are not equal\n");
		a9.setSize(3,3);
		printBoardDetails(a8);
		printBoardDetails(a9);
		if(a8.equals(a9) == true)
			System.out.println("\n-> These board are equal\n");
		else
			System.out.println("\n-> These board are not equal\n");

		System.out.println("\nNumber of Board objects created so far : " + AbstractBoard.NumberOfBoards());
	}
	
	/**
	 * Testing BoardArray2D
	 */
	public static void checkBoardArray2D()
	{
		System.out.println("\n------------------ Test All Function of BoardArray2D ------------------\n");

		System.out.println("_______________  No parameter constructor testing  ________________");
		BoardArray2D a1 = new BoardArray2D();
		printBoardDetails(a1);
		
		System.out.println("_______________  Two parameter constructor testing  _______________");
		BoardArray2D a2 = new BoardArray2D(4,6);
		printBoardDetails(a2);
		
		System.out.println("___________________  Copy constructor testing  ____________________");
		BoardArray2D a3 = new BoardArray2D(a2);
		printBoardDetails(a3);
		
		System.out.println("__________________  Clone function testing  __________________");
		BoardArray2D a4 = new BoardArray2D();
		System.out.println("Before clone function :");
		printBoardDetails(a4);
		System.out.println("After clone function : ");
		try
		{
			a4 = (BoardArray2D)a3.clone();
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			printBoardDetails(a4);
		}
		
		System.out.println("________________  readFromFile function testing  _________________");
		BoardArray2D a5 = new BoardArray2D();
		System.out.println("Reading testBoard/board.txt");
		try
		{
			if(a5.readFromFile("testBoard/board.txt"))
				System.out.println("Reading is successful");
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			System.out.println("Reading is over");
			printBoardDetails(a5);
		}
		
		System.out.println("_________________  writeToFile function testing  _________________");
		System.out.println("Writing testBoard/writeBoard2D.txt");
		try
		{
			a5.writeToFile("testBoard/writeBoard2D.txt");
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		finally
		{
			System.out.println("Writing is over");
			System.out.println(a5);
		}
		
		System.out.println("____________________  reset function testing  ____________________");
		System.out.println("Before reset function :");
		printBoardDetails(a5);
		System.out.println("\nAfter reset function :");
		a5.reset();
		printBoardDetails(a5);
		
		System.out.println("___________________  setSize function testing  ___________________");
		System.out.println("Before setSize function :");
		BoardArray2D a6 = new BoardArray2D();
		printBoardDetails(a6);
		System.out.println("\nAfter setSize function :");
		a6.setSize(5,5);
		printBoardDetails(a6);
		
		System.out.println("____________________  move function testing  ____________________");
		BoardArray2D a7 = new BoardArray2D(4,4);
		printBoardDetails(a7);
		a7.move('U');
		printBoardDetails(a7);
		a7.move('L');
		printBoardDetails(a7);
		a7.move('U');
		printBoardDetails(a7);
		
		System.out.println("___________________  equals function testing  ____________________");
		BoardArray2D a8 = new BoardArray2D(3,3);
		BoardArray2D a9 = new BoardArray2D(3,4);
		printBoardDetails(a8);
		printBoardDetails(a9);
		if(a8.equals(a9) == true)
			System.out.println("\n-> These board are equal\n");
		else
			System.out.println("\n-> These board are not equal\n");
		a9.setSize(3,3);
		printBoardDetails(a8);
		printBoardDetails(a9);
		if(a8.equals(a9) == true)
			System.out.println("\n-> These board are equal\n");
		else
			System.out.println("\n-> These board are not equal\n");

		System.out.println("\nNumber of Board objects created so far : " + AbstractBoard.NumberOfBoards());
	}
	
	/**
	 * Testing GlobalFunction
	 */
	public static void checkGlobalFunction()
	{
		BoardArray1D a1,a2,a3,a4,a5;
		BoardArray2D a6,a7,a8,a9;
		int size=9;
		AbstractBoard[] boards = new AbstractBoard[size];
		
		try
		{
			a1 = new BoardArray1D(); a1.readFromFile("testBoard/test1.txt");
			a2 = new BoardArray1D(); a2.readFromFile("testBoard/test2.txt");
			a3 = new BoardArray1D(); a3.readFromFile("testBoard/test3.txt");
			a4 = new BoardArray1D(); a4.readFromFile("testBoard/test4.txt");
			a5 = new BoardArray1D(); a5.readFromFile("testBoard/test5.txt");
			
			a6 = new BoardArray2D(); a6.readFromFile("testBoard/test6.txt");
			a7 = new BoardArray2D(); a7.readFromFile("testBoard/test7.txt");
			a8 = new BoardArray2D(); a8.readFromFile("testBoard/test8.txt");
			a9 = new BoardArray2D(); a9.readFromFile("testBoard/test9.txt");
			
			boards[0] = a1;
			boards[1] = a2;
			boards[2] = a3;
			boards[3] = a4;
			boards[4] = a5;
			boards[5] = a6;
			boards[6] = a7;
			boards[7] = a8;
			boards[8] = a9;
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		
		System.out.println("\n\n------------------  Test the validity of the sequence  ------------------\n");
		System.out.println("-->(1)\n");

		for(int i=0 ; i < size ; ++i)
			printBoardDetails(boards[i]);

		if(GlobalFunction.isValidSequence(boards))
			System.out.println("\n->The sequence is valid");
		else
			System.out.println("\n->The sequence is not valid\n");

		a1 = a2 = a3 = a4 = a5 = null;
		a6 = a7 = a8 = a9 = null;
		
		
		try
		{
			a1 = new BoardArray1D(); a1.readFromFile("testBoard/test1.txt");
			a2 = new BoardArray1D(); a2.readFromFile("testBoard/test2.txt");
			a3 = new BoardArray1D(); a3.readFromFile("testBoard/test3.txt");
			a4 = new BoardArray1D(); a4.readFromFile("testBoard/test4.txt");
			a5 = new BoardArray1D(); a5.readFromFile("testBoard/test5_1.txt");
			
			a6 = new BoardArray2D(); a6.readFromFile("testBoard/test6.txt");
			a7 = new BoardArray2D(); a7.readFromFile("testBoard/test7.txt");
			a8 = new BoardArray2D(); a8.readFromFile("testBoard/test8.txt");
			a9 = new BoardArray2D(); a9.readFromFile("testBoard/test9.txt");

			boards[0] = a1;
			boards[1] = a2;
			boards[2] = a3;
			boards[3] = a4;
			boards[4] = a5;
			boards[5] = a6;
			boards[6] = a7;
			boards[7] = a8;
			boards[8] = a9;
		}
		catch(Exception e)
		{
			e.getMessage();
		}

		System.out.println("\n\n-->(2)\n");

		for(int i=0 ; i < size ; ++i)
			printBoardDetails(boards[i]);

		if(GlobalFunction.isValidSequence(boards))
			System.out.println("\n->The sequence is valid");
		else
			System.out.println("\n->The sequence is not valid\n");
		
		System.out.println("\nNumber of Board objects created so far : " + AbstractBoard.NumberOfBoards());
	}
}