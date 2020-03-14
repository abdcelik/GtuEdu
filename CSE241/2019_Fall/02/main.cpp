#include "NP_base.h"

int main(int argc, char* argv[])
{
	auto puzzle = Create_Puzzle();

	srand(time(NULL));
	Check_Program_State(puzzle,argc,argv);

	cout << "Your initial board is\n";
	Print_Puzzle(puzzle);

	while(puzzle.state != State::QUIT)
	{
		Get_Event(puzzle);
		Print_Puzzle(puzzle);

		if(puzzle.state != State::QUIT)
			if(Is_Solved(puzzle) == true)
				puzzle.state = State::SOLVED;

		if(puzzle.state == State::QUIT)
			cout << "Problem couldn't be solved!\nTotal number of moves : " << puzzle.totalNumberOfMoves << endl;
		if(puzzle.state == State::SOLVED)
		{
			cout << "Problem Solved!\nTotal number of moves : " << puzzle.totalNumberOfMoves << endl;
			puzzle.state = State::QUIT;
		}
	}

	Delete_All(puzzle);
	return 0;
}