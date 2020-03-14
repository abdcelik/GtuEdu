#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef NP_base
#define NP_base

enum class Event{UP,DOWN,LEFT,RIGHT,INTELLIGENT,SHUFFLE,EXIT,SOLVE,REPORT,EXPORT,LOAD,NONE};
enum class State{QUIT,UNSOLVED,SOLVED};

struct Puzzle
{
	int *cur_puzzle;
	int *goal_puzzle;
	int row,column;
	int blank_x,blank_y;
	int totalNumberOfMoves;
	State state;
	Event prev_event;
	int event_flag;
};

Puzzle Create_Puzzle(void);
// Postcondition : Create a puzzle and return it

void Check_Program_State(Puzzle&,int,char*[]);
// Precondition : The puzzle and command line arguments are sent to the function
// Postcondition : If the file name is sent as command line argument, the file is read. If not, the user will be prompted for n * n and the puzzle will be created.

int Get_Size(int,int);
// Precondition : Lower and upper bound are sent to the function and the function create a number in these bounds
// Postcondition : Created number is returned

void Init_Random_Puzzle(Puzzle&);
// Postcondition : A random n*n size puzzle is created and assigned to the puzzle.cur_puzzle array

void Init_Goal_Puzzle(Puzzle&);
// Postcondition : A goal puzzle is created and assigned to the puzzle.goal_puzzle array

void Set_Blank_Position(Puzzle&);
// Postcondition : The coordinates of the blank in our current puzzle are found and assigned to the blank_x,blank_y variables.

bool Is_Solvable(const Puzzle&);
// Postcondition : If current puzzle is solvable, true is returned. Else false is returned

bool Is_Solved(const Puzzle&);
// Postcondition : If current puzzle is the desired goal puzzle, true is returned. Otherwise false is returned

void Print_Puzzle(const Puzzle&);
// Postcondition : Print the current puzzle on the screen

void Get_Event(Puzzle&);
// Postcondition : The user enters the input and if this input can be performed, it is performed

bool Can_Move(const Puzzle&,Event);
// Precondition : Current puzzle and the desired movement are sent to the function
// Postcondition : If this event can be performed, true is returned. Else false is returned

void Do_Event(Puzzle&,Event);
// Precondition : Current puzzle and the desired movement are sent to the function
// Postcondition : This event is performed

void Shuffle_Puzzle(Puzzle&);
// Postcondition : Current puzzle is shuffled row*column times

void Move_Intelligent(Puzzle&);
// Postcondition : The best moves are made for current puzzle.

int Manhattan_Distance(Puzzle&,Event);
// Precondition : Current puzzle and the desired movement are sent to the function
// Postcondition : As a result of the desired movement, distance which is between current puzzle and goal puzzle is returned

void Solve_Puzzle(Puzzle&);
// Postcondition : Current puzzle is solved.

void Check_Prev_Event(Puzzle& puzzle);
// Postcondition : Ensures that the previous move is not made again

void Print_Report(const Puzzle&);
// Postcondition : It prints how many moves were made and whether or not it was solved

int Export_File(const Puzzle&);
// Postcondition : The current puzzle is written to the desired file

int Load_File(Puzzle&,char*);
// Precondition : Current puzzle and file name are sent to the function
// Postcondition : The requested file is read and assigned to current puzzle

int String_to_Integer(char*);
// Postcondition : The sent string is converted to integer.

int Power(int,int);
// Postcondition : Exponential operation is done and return

int Digit_Number(int);
// Postcondition : The digits of number is returned

void Delete_All(Puzzle&);
// Postcondition : Current and goal puzzle are deallocated in memory

#endif