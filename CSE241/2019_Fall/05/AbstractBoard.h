#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <string>

namespace GTU_Board
{
	class AbstractBoard
	{
	public:
		AbstractBoard() {++totalNumberOfBoards;}
		void print(void)const;
		bool readFromFile(const std::string&);
		bool writeToFile(const std::string&)const;
		void reset(void);
		virtual bool setSize(int,int);
		bool move(char);
		bool canMove(char)const;
		bool isSolved(void)const;
		virtual const int operator()(const int&,const int&)const=0;
		virtual int& operator()(const int&,const int&)=0;
		const bool operator==(const AbstractBoard&)const;
		static int NumberOfBoards(void) {return totalNumberOfBoards;}
		char lastMove(void)const {return prevMove;}
		int numberOfMoves(void)const {return totalNumberOfMoves;}

		int getRow(void)const {return row;}
		int getColumn(void)const {return column;}
		int getPosX(void)const {return blank_x;}
		int getPosY(void)const {return blank_y;}

		virtual ~AbstractBoard()=default;
	protected:
		bool setRow(int);
		bool setColumn(int);
		void setTotalMoves(int num) {totalNumberOfMoves=num;}
		void setPrevMove(char event) {prevMove = event;}

		int row=0,column=0;
		int blank_x=0,blank_y=0;
		static int totalNumberOfBoards;
		int totalNumberOfMoves=0;
		char prevMove=0;
	};

	bool checkValidSequence(const AbstractBoard* const arr[], int size);
}

#endif