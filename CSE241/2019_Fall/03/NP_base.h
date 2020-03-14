#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#ifndef NP_base
#define NP_base

class NPuzzle
{
public:
	NPuzzle() {}
	NPuzzle(int size) {NPuzzle(size,size);}
	NPuzzle(int,int);
	void print(void)const {board.print();}
	void printReport(void)const;
	bool readFromFile(std::string);
	bool writeToFile(std::string);
	void shuffle(int);
	void reset(void);
	void setSize(int,int);
	void moveRandom(void);
	void moveIntelligent(void);
	int move(char);
	void solvePuzzle(void);

	bool gameState(void);
	void checkProgramState(int,char*[]);
	void getEvent(void);
	int getInt(std::string,int=0,int=0)const;
	std::string getString(std::string)const;
	void deleteAll(void) {board.deleteAll();}
private:
	class Board
	{
	public:
		void print(void)const;
		bool readFromFile(std::string);
		bool writeToFile(std::string);
		void reset(void);
		void setSize(int,int);
		int move(char);
		int isSolved(void)const;
		int manhattanDistance(char);
		int getRowCol()const {return row*column;}
		void deleteAll(void);
	private:
		void initGoalBoard(bool=false);
		bool checkBoard(int*)const;
		bool canMove(char)const;
		int index(int,int)const;
		void swap(int,int);
		void setBlankPos(void);
		int stringToInt(char*)const;
		int power(int,int)const;
		int digitNumber(int)const;

		const int sizeLowerBound=2,sizeUpperBound=9;
		int *cur_board=NULL;
		int *goal_board=NULL;
		int row=0;
		int column=0;
		int blank_x=0;
		int blank_y=0;
	};

	enum class State{UNSOLVED,SOLVED,QUIT};

	Board board;
	int totalNumberOfMoves=0;
	char prevEvent=0;
	int eventFlag=0;
	State state = State::UNSOLVED;
};

#endif
