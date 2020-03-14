#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef NP_base
#define NP_base

class NPuzzle
{
public:
	NPuzzle() {}
	NPuzzle(int,int);
	void checkProgramState(int,char*[]);
	void getEvent(void);
	int getInt(const std::string&,int,int)const;
	std::string getString(const std::string&)const;

	void print(void)const {board.print();}
	void printReport(void)const;
	bool readFromFile(const std::string&);
	bool writeToFile(const std::string&);
	void shuffle(int);
	void reset(void);
	void setsize(int,int);
	void moveRandom(void);
	int move(char);
	void solvePuzzle(void);
	friend std::ostream& operator>>(std::ostream&,const NPuzzle&);
	friend std::istream& operator<<(std::istream&,NPuzzle&);

	bool gameState(void);
private:
	class Board
	{
	public:
		Board() {++totalNumberOfBoards;}
		Board(int,int);
		void print(void)const;
		bool readFromFile(const std::string&);
		bool writeToFile(const std::string&);
		void reset(void);
		void setSize(const int,const int);
		int move(char);
		int isSolved(void)const;
		int operator()(const int&,const int&)const;
		const bool operator==(const Board&)const;
		static int NumberOfBoards(void) {return totalNumberOfBoards;}
		char lastMove(void)const {return prevMove;}
		int numberOfMoves(void)const {return totalNumberOfMoves;}

		int getRow(void)const {return row;}
		int getCol(void)const {return column;}
		void setNumberOfMoves(void) {totalNumberOfMoves=0;}
		static void setNumberOfBoards(int num) {totalNumberOfBoards = num;}
		bool canMove(char)const;
	private:
		bool checkBoard(const std::vector<std::vector<int> >&)const;
		void initGoalBoard(void);
		void setBlankPos(void);
		int stringToInt(char*)const;
		int digitNumber(int)const;

		std::vector<std::vector<int> > cur;
		std::vector<std::vector<int> > goal;
		int row=0,column=0;
		int blank_x=0,blank_y=0;
		int totalNumberOfMoves=0;
		char prevMove='S';
		static int totalNumberOfBoards;
	};

	enum class State{UNSOLVED,SOLVED,QUIT};
	bool getChild(const Board&,char);
	bool checkChild(const Board&);

	Board board;
	std::vector<Board> boardVec;
	const int sizeLowerBound=2,sizeUpperBound=9;
	State state = State::UNSOLVED;
};

#endif