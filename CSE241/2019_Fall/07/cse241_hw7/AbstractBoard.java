package cse241_hw7;

import java.io.*;
import java.util.Scanner;

/**
 * This class keeps some board informations.
 * @author Abdullah_Celik_171044002
 */
public abstract class AbstractBoard
{
	private int row=0,column=0;
	private int blank_x=0,blank_y=0;
	private int totalNumberOfMoves=0;
	private char lastMove='S';
	private static int totalNumberOfBoards=0;
	
	/**
	 * Increase total number of boards.
	 */
	public AbstractBoard()
	{
		++totalNumberOfBoards;
	}
	
	/**
	 * Returns a string representation of the object.
	 * @return a string representation of the object.
	 */
	@Override
	public String toString()
	{
		String newString = new String();
		
		for(int i=0 ; i < getRow() ; ++i)
		{
			for(int j=0 ; j < getColumn() ; ++j)
			{
				switch(cell(j,i))
				{
					case 0:		newString += "X\t";		break;
					case -1:	newString += " \t";		break;
					default:	newString += cell(j,i) + "\t";	break;
				}
			}
			newString += "\n";
		}
		
		return newString;
	}
	
	/**
	 * Writes to given file name.
	 * @param fileName file name to write.
	 * @return if writing is successful, returns true. Otherwise throws exception.
	 * @throws Exception if file could not be opened, throws exception.
	 */
	
	/**
	 * Reads from given file name.
	 * @param fileName file name to read.
	 * @return if reading is successful, returns true. Otherwise throws exception.
	 * @throws Exception if file could not be opened throws exception.
	 */
	public boolean readFromFile(String fileName)throws Exception
	{
		try
		{
			File file = new File(fileName);
			BufferedReader br = new BufferedReader(new FileReader(file));
			
			setSize(0,0);
			
			String st;
			String[] words;
			int line = 0;
			
			st = br.readLine();
			for( words = st.split(" ") ; st != null ; ++line , st = br.readLine());
			
			setSize(line,words.length);
			br.close();
			
			Scanner input = new Scanner(file);
			
			for(int i=0 ; i < getRow() ; ++i)
				for(int j=0 ; j < getColumn() ; ++j)
					setCell(j,i,Integer.parseInt(input.next().replaceFirst("b","-1").replaceAll("b","")));
			
			input.close();
			
			for(int i=0 ; i < getRow() ; ++i)
				for(int j=0 ; j < getColumn() ; ++j)
					if(cell(j,i) == -1)
					{
						setXPosition(j);
						setYPosition(i);
					}
			
			setNumberOfMoves(0);
			setLastMove('S');
		}
		catch(IOException e)
		{
			throw new Exception("Reading file couldn't be successfully!");
		}
		
		return true;
	}
	
	/**
	 * Writes to given file name.
	 * @param fileName file name to write.
	 * @return if writing is successful, returns true. Otherwise throws exception.
	 * @throws Exception if file could not be opened, throws exception.
	 */
	public boolean writeToFile(String fileName)throws Exception
	{
		try
		{
			PrintWriter p = new PrintWriter(new FileOutputStream(fileName));
			
			int maxDigit = 0;
			
			for(int i=0 ; i < getRow() ; ++i)
				for(int j=0 ; j < getColumn() ; ++j)
					if(maxDigit < digitNumber(cell(j,i)))
						maxDigit = digitNumber(cell(j,i));
			
			for(int i=0 ; i < getRow() ; ++i)
			{
				for(int j=0 ; j < getColumn() ; ++j)
				{
					for(int k = digitNumber(cell(j,i)) ; k < maxDigit ; ++k)
					{
						if(cell(j,i) == -1)
							p.print('b');
						else
							p.print('0');
					}
					
					if(cell(j,i) == -1)	p.print('b');
					else	p.print(cell(j,i));

					if(j < getColumn()-1) p.print(' ');
				}
				p.print("\n");
			}
			
			p.close();
		}
		catch(IOException e)
		{
			throw new Exception("Writing file couldn't be successfully!");
		}
		
		return true;
	}
	
	/**
	 * Resets the current board to the solution.
	 */
	public void reset()
	{
		int digitValue = 1;
		
		setNumberOfMoves(0);
		setLastMove('S');
		
		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if(cell(j,i) != 0)
					setCell(j,i,digitValue++);
		
		if(getRow() != 0 && getColumn() != 0)
		{
			setXPosition(getColumn()-1);
			setYPosition(getRow()-1);
			setCell(blank_x,blank_y,-1);
		}
	}
	
	/**
	 * Sets the board size to given values. The board is reset after this operation.
	 * @param newRow newRow should be greater than 3.
	 * @param newColumn newColumn should be greater than 3.
	 * @return if setting is true, returns true. Otherwise returns false;
	 */
	public boolean setSize(int newRow, int newColumn)
	{
		if(!setRow(newRow) || !setColumn(newColumn))
			return false;
		return true;
	}
	
	/**
	 * Makes a move according to the given char parameter. If the parameter is ‘L’ then the blank tiles moves left, ..., etc.
	 * @param event Event should be 'L','R','U','D'.
	 * @return if moving is true, returns true. Otherwise returns false;
	 */
	public boolean move(char event)
	{
		int dirX=0,dirY=0;

		switch(event)
		{
			case 'U':	dirX = 0	; dirY = -1;	break;
			case 'D':	dirX = 0	; dirY = 1;		break;
			case 'L':	dirX = -1	; dirY = 0;		break;
			case 'R':	dirX = 1	; dirY = 0;		break;
			default: return false;
		}

		if(canMove(event))
		{
			int temp = cell(getXPosition(),getYPosition());
			setCell(getXPosition(),getYPosition(),cell(getXPosition()+dirX,getYPosition()+dirY));
			setCell(getXPosition()+dirX,getYPosition()+dirY,temp);
			
			setNumberOfMoves(numberOfMoves()+1);
			setLastMove(event);
			setXPosition(getXPosition()+dirX);
			setYPosition(getYPosition()+dirY);
			return true;
		}
		return false;
	}
	
	/**
	 * Checks if the board is the solution.
	 * @return Returns true if the board is a solution.
	 */
	public boolean isSolved()
	{
		int digitValue = 0 , relation = 0;
		
		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if(cell(j,i) != 0)
				{
					++digitValue;
					if(cell(j,i) == digitValue)
						++relation;
				}
		
		if(relation == digitValue-1)
			return true;
		else
			return false;
	}
	
	/**
	 * Returns the corresponding cell content.
	 * @param x_pos
	 * @param y_pos
	 * @return cell content.
	 */
	public abstract int cell(int x_pos, int y_pos);
	
	/**
	 * Set the corresponding cell content with newVal.
	 * @param x_pos
	 * @param y_pos
	 * @param newVal
	 */
	public abstract void setCell(int x_pos, int y_pos, int newVal);
	
	/**
	 * Two boards are equal, if the boards are the same. This operator does.
	 * not consider last move or the number of steps.
	 * @param other other board.
	 */
	@Override
	public boolean equals(Object other)
	{
		if(other == null)
			return false;
		
		if(!(other instanceof AbstractBoard))
			return false;
		
		if(this == other)
			return true;
		
		if(getRow() != ((AbstractBoard)other).getRow() || getColumn() != ((AbstractBoard)other).getColumn())
			return false;
		
		boolean equality = true;
		
		for(int i=0 ; i < getRow() && equality ; ++i)
			for(int j=0 ; j < getColumn() && equality ; ++j)
				if(this.cell(j,i) != ((AbstractBoard)other).cell(j,i))
					equality = false;
		
		if(equality == true)
			return true;
		else
			return false;
	}
	
	/**
	 * Returns the last move, if there is no last move, returns ‘S’.
	 * @return returns last move.
	 */
	public char lastMove()
	{
		return lastMove;
	}
	
	/**
	 * Returns the number of Board objects created so far.
	 * @return total number of boards.
	 */
	public static int NumberOfBoards()
	{
		return totalNumberOfBoards;
	}
	
	/**
	 * Returns the number of steps (moves) this board made.
	 * @return total number of moves.
	 */
	public int numberOfMoves()
	{
		return totalNumberOfMoves;
	}
	
	private boolean canMove(char event)
	{	
		if(	(event == 'U' && getYPosition() > 0 			&& cell(getXPosition(),getYPosition()-1) != -2) ||
			(event == 'D' && getYPosition() < getRow()-1	&& cell(getXPosition(),getYPosition()+1) != -2) ||
			(event == 'L' && getXPosition() > 0 			&& cell(getXPosition()-1,getYPosition()) != -2) ||
			(event == 'R' && blank_x < getColumn()-1 		&& cell(getXPosition()+1,getYPosition()) != -2))
			return true;
		else
			return false;
	}
	
	private int digitNumber(int num)
	{
		int digit=0;

		if(num == 0)
			return 1;

		for(; num != 0 ; ++digit,num/=10);
		return digit;
	}

	public int getRow()
	{
		return row;
	}
	
	public int getColumn()
	{
		return column;
	}
	
	public int getXPosition()
	{
		return blank_x;
	}
	
	public int getYPosition()
	{
		return blank_y;
	}
	
	private boolean setRow(int row)
	{
		if(row < 3)
		{
			this.row = 3;
			return false;
		}
		
		this.row = row;
		return true;
	}

	private boolean setColumn(int column)
	{
		if(column < 3)
		{
			this.column = 3;
			return false;
		}
		
		this.column = column;
		return true;
	}
	
	protected void setXPosition(int blank_x)
	{
		this.blank_x = blank_x;
	}
	
	protected void setYPosition(int blank_y)
	{
		this.blank_y = blank_y;
	}
	
	protected void setNumberOfMoves(int totalNumberOfMoves)
	{
		this.totalNumberOfMoves = totalNumberOfMoves;
	}
	
	protected void setLastMove(char lastMove)
	{
		this.lastMove = lastMove;
	}
}