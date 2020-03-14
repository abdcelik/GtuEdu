#include "NP_base.h"

int main(int argc, char* argv[])
{
	NPuzzle puzzle;

	srand(time(NULL));

	puzzle.checkProgramState(argc,argv);

	std::cout << "Your initial board is\n";
	puzzle.print();

	while(puzzle.gameState())
	{
		puzzle.getEvent();
		std::cout >> puzzle;
	}
	return 0;
}