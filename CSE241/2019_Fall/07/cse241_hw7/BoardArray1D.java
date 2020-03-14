package cse241_hw7;

/**
 * This class keeps the AbstractBoard class as one dimension integers array.
 * Extends AbstractBoard, implements Cloneable.
 * @author Abdullah_Celik_171044002
 */
public class BoardArray1D extends AbstractBoard implements Cloneable
{
	private int[] board;
	
	/**
	 * No parameter constructor calls two parameter constructor
	 */
	public BoardArray1D()
	{
		this(3,3);
	}
	
	/**
	 * Creates a board with given parameters
	 * @param newRow
	 * @param newColumn
	 */
	public BoardArray1D(int newRow, int newColumn)
	{
		super();
		setSize(newRow,newColumn);
	}
	
	/**
	 * Creates a board with given other board
	 * @param other
	 */
	public BoardArray1D(BoardArray1D other)
	{
		super();
		setSize(other.getRow(),other.getColumn());
		
		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				setCell(j,i,other.cell(j,i));
		
		setXPosition(other.getXPosition());
		setYPosition(other.getYPosition());
		setNumberOfMoves(other.numberOfMoves());
		setLastMove(other.lastMove());
	}
	
	/**
	 * Returns the corresponding cell content.
	 * @param x_pos
	 * @param y_pos
	 * @return cell content.
	 */
	@Override
	public int cell(int x_pos, int y_pos)
	{
		if(x_pos < 0 || x_pos > getColumn()-1 || y_pos < 0 || y_pos > getRow()-1)
		{
			System.err.println("Invalid index!");
			System.exit(-1);
		}
		
		return board[getColumn()*y_pos + x_pos];
	}
	
	/**
	 * Set the corresponding cell content with newVal.
	 * @param x_pos
	 * @param y_pos
	 * @param newVal
	 */
	@Override
	public void setCell(int x_pos, int y_pos, int newVal)
	{
		if(x_pos < 0 || x_pos > getColumn()-1 || y_pos < 0 || y_pos > getRow()-1)
		{
			System.err.println("Invalid index!");
			System.exit(-1);
		}
		
		board[getColumn()*y_pos + x_pos] = newVal;
	}
	
	/**
	 * Sets the board size to given values. The board is reset after this operation.
	 * @param newRow newRow should be greater than 3.
	 * @param newColumn newColumn should be greater than 3.
	 * @return if setting is true, returns true. Otherwise returns false;
	 */
	@Override
	public boolean setSize(int newRow, int newColumn)
	{
		if(board != null)
			board = null;
		
		if(!super.setSize(newRow,newColumn))
			return false;

		board = new int[getRow()*getColumn()];
		
		for(int i=0 ; i < getRow()*getColumn() ; ++i)
			board[i] = -1;

		reset();
		return true;
	}
	
	/**
	 * Makes a copy of itself.
	 * @return returns clone of this .
	 */
	@Override
	public Object clone()throws CloneNotSupportedException
	{
		return new BoardArray1D(this);
	}
}