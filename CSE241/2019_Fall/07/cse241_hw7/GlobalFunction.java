package cse241_hw7;

/**
 * This class is for some functions
 * @author Abdullah_Celik_171044002
 */
public class GlobalFunction
{
	/**
	 * Checks if the array contains a valid sequence of moves for a solution.
	 * @param arr
	 * @return if the array contains a valid sequence, returns true. Otherwise returns false.
	 */
	public static boolean isValidSequence(AbstractBoard[] arr)
	{
		if(arr.length == 0 || arr[arr.length-1].isSolved() == false)
			return false;
		
		for(int i=0 ; i < arr.length-1 ; ++i)
			if(isValid(arr[i],arr[i+1]) == false)
				return false;
		
		return true;
	}
	
	/**
	 * Checks if the first puzzle can reach the second puzzle in one move.
	 * @param firstBoard
	 * @param secondBoard
	 * @return if the first puzzle can reach the second puzzle in one move, returns true. Otherwise returns false.
	 */
	private static boolean isValid(AbstractBoard firstBoard, AbstractBoard secondBoard)
	{
		if(firstBoard.getRow() != secondBoard.getRow() || firstBoard.getColumn() != secondBoard.getColumn())
			return false;
		
		int distance_x = firstBoard.getXPosition() - secondBoard.getXPosition();
		int distance_y = firstBoard.getYPosition() - secondBoard.getYPosition();
		
		if(distance_x < 0) distance_x *= -1;
		if(distance_y < 0) distance_y *= -1;
		
		if(distance_x + distance_y != 1)
			return false;
		
		return true;
	}
}