#include "BoardVector.h"
#include "BoardArray1D.h"
#include "BoardArray2D.h"

using namespace GTU_Board;
using std::cout;
using std::endl;

void printBoardDetails(const AbstractBoard*);
void checkBoardArray1D(void);
void checkBoardArray2D(void);
void checkBoardVector(void);
void checkGlobalFunction(void);

int main(void)
{
	checkBoardArray1D();
	checkBoardArray2D();
	checkBoardVector();
	checkGlobalFunction();
	return 0;
}

void printBoardDetails(const AbstractBoard* board)
{
	cout << "Row : " << board->getRow() << endl;
	cout << "Column : " << board->getColumn() << endl;
	cout << "Blank Position(x,y) : (" << board->getPosX() << "," << board->getPosY() << ")" << endl;
	cout << "Last moves : " << board->lastMove() << endl;
	cout << "Total moves : " << board->numberOfMoves() << endl << endl;
	board->print();
}

void checkBoardArray1D(void)
{
	cout << "\n\n------------------ Test All Function of BoardArray1D ------------------\n\n";

	cout << "_______________  No parameter constructor testing  ________________\n";
	BoardArray1D arr1D_1;
	printBoardDetails(&arr1D_1);

	cout << "_______________  One parameter constructor testing  _______________\n";
	BoardArray1D arr1D_2(3);
	printBoardDetails(&arr1D_2);

	cout << "_______________  Two parameter constructor testing  _______________\n";
	BoardArray1D arr1D_3(4,6);
	printBoardDetails(&arr1D_3);

	cout << "___________________  Copy constructor testing  ____________________\n";
	BoardArray1D arr1D_4(arr1D_3);
	printBoardDetails(&arr1D_4);

	cout << "__________________  Assignment operator testing  __________________\n";
	BoardArray1D arr1D_5;
	cout << "Before assignment operator : \n";
	printBoardDetails(&arr1D_5);
	cout << "\nAfter assignment operator : \n";
	arr1D_5 = arr1D_4;
	printBoardDetails(&arr1D_5);

	cout << "________________  readFromFile function testing  _________________\n";
	BoardArray1D arr1D_6;
	cout << "Reading testBoard/board.txt\n";
	if(arr1D_6.readFromFile("testBoard/board.txt"))
		cout << "Reading is successful\n";
	printBoardDetails(&arr1D_6);

	cout << "_________________  writeToFile function testing  _________________\n";
	cout << "Writing testBoard/writeBoard1D.txt\n";
	arr1D_6.writeToFile("testBoard/writeBoard1D.txt");

	cout << "____________________  reset function testing  ____________________\n";
	cout << "Before reset function : \n";
	printBoardDetails(&arr1D_6);
	cout << "\nAfter reset function : \n";
	arr1D_6.reset();
	printBoardDetails(&arr1D_6);

	cout << "___________________  setSize function testing  ___________________\n";
	cout << "Before setSize function : \n";
	BoardArray1D arr1D_7(2,2);
	printBoardDetails(&arr1D_7);
	cout << "\nAfter setSize function : \n";
	arr1D_7.setSize(5,5);
	printBoardDetails(&arr1D_7);

	cout << "____________________  move function testing  ____________________\n";
	BoardArray1D arr1D_8(4,4);
	printBoardDetails(&arr1D_8);
	arr1D_8.move('U');
	printBoardDetails(&arr1D_8);
	arr1D_8.move('L');
	printBoardDetails(&arr1D_8);
	arr1D_8.move('U');
	printBoardDetails(&arr1D_8);

	cout << "____________________  == operator testing  _____________________\n";
	BoardArray1D arr1D_9(3,3),arr1D_10(3,4);
	printBoardDetails(&arr1D_9);
	printBoardDetails(&arr1D_10);
	if(arr1D_9 == arr1D_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";
	arr1D_10.setSize(3,3);
	printBoardDetails(&arr1D_9);
	printBoardDetails(&arr1D_10);
	if(arr1D_9 == arr1D_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";


	cout << "\nNumber of Board objects created so far : " << AbstractBoard::NumberOfBoards() << endl;
}

void checkBoardArray2D(void)
{
	cout << "\n\n------------------ Test All Function of BoardArray2D ------------------\n\n";

	cout << "_______________  No parameter constructor testing  ________________\n";
	BoardArray2D arr2D_1;
	printBoardDetails(&arr2D_1);

	cout << "_______________  One parameter constructor testing  _______________\n";
	BoardArray2D arr2D_2(3);
	printBoardDetails(&arr2D_2);

	cout << "_______________  Two parameter constructor testing  _______________\n";
	BoardArray2D arr2D_3(4,6);
	printBoardDetails(&arr2D_3);

	cout << "___________________  Copy constructor testing  ____________________\n";
	BoardArray2D arr2D_4(arr2D_3);
	printBoardDetails(&arr2D_4);

	cout << "__________________  Assignment operator testing  __________________\n";
	BoardArray2D arr2D_5;
	cout << "Before assignment operator : \n";
	printBoardDetails(&arr2D_5);
	cout << "\nAfter assignment operator : \n";
	arr2D_5 = arr2D_4;
	printBoardDetails(&arr2D_5);

	cout << "________________  readFromFile function testing  _________________\n";
	BoardArray2D arr2D_6;
	cout << "Reading testBoard/board.txt\n";
	if(arr2D_6.readFromFile("testBoard/board.txt"))
		cout << "Reading is successful\n";
	printBoardDetails(&arr2D_6);

	cout << "_________________  writeToFile function testing  _________________\n";
	cout << "Writing testBoard/writeBoard2D.txt\n";
	arr2D_6.writeToFile("testBoard/writeBoard2D.txt");

	cout << "____________________  reset function testing  ____________________\n";
	cout << "Before reset function : \n";
	printBoardDetails(&arr2D_6);
	cout << "\nAfter reset function : \n";
	arr2D_6.reset();
	printBoardDetails(&arr2D_6);

	cout << "___________________  setSize function testing  ___________________\n";
	cout << "Before setSize function : \n";
	BoardArray2D arr2D_7(2,2);
	printBoardDetails(&arr2D_7);
	cout << "\nAfter setSize function : \n";
	arr2D_7.setSize(5,5);
	printBoardDetails(&arr2D_7);

	cout << "____________________  move function testing  ____________________\n";
	BoardArray2D arr2D_8(4,4);
	printBoardDetails(&arr2D_8);
	arr2D_8.move('U');
	printBoardDetails(&arr2D_8);
	arr2D_8.move('L');
	printBoardDetails(&arr2D_8);
	arr2D_8.move('U');
	printBoardDetails(&arr2D_8);

	cout << "____________________  == operator testing  _____________________\n";
	BoardArray2D arr2D_9(3,3),arr2D_10(3,4);
	printBoardDetails(&arr2D_9);
	printBoardDetails(&arr2D_10);
	if(arr2D_9 == arr2D_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";
	arr2D_10.setSize(3,3);
	printBoardDetails(&arr2D_9);
	printBoardDetails(&arr2D_10);
	if(arr2D_9 == arr2D_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";


	cout << "\nNumber of Board objects created so far : " << AbstractBoard::NumberOfBoards() << endl;
}

void checkBoardVector(void)
{
	cout << "\n\n------------------ Test All Function of BoardVector ------------------\n\n";

	cout << "_______________  No parameter constructor testing  ________________\n";
	BoardVector vec_1;
	printBoardDetails(&vec_1);

	cout << "_______________  One parameter constructor testing  _______________\n";
	BoardVector vec_2(3);
	printBoardDetails(&vec_2);

	cout << "_______________  Two parameter constructor testing  _______________\n";
	BoardVector vec_3(4,6);
	printBoardDetails(&vec_3);

	cout << "___________________  Copy constructor testing  ____________________\n";
	BoardVector vec_4(vec_3);
	printBoardDetails(&vec_4);

	cout << "__________________  Assignment operator testing  __________________\n";
	BoardVector vec_5;
	cout << "Before assignment operator : \n";
	printBoardDetails(&vec_5);
	cout << "\nAfter assignment operator : \n";
	vec_5 = vec_4;
	printBoardDetails(&vec_5);

	cout << "________________  readFromFile function testing  _________________\n";
	BoardVector vec_6;
	cout << "Reading testBoard/board.txt\n";
	if(vec_6.readFromFile("testBoard/board.txt"))
		cout << "Reading is successful\n";
	printBoardDetails(&vec_6);

	cout << "_________________  writeToFile function testing  _________________\n";
	cout << "Writing testBoard/writeBoardVec.txt\n";
	vec_6.writeToFile("testBoard/writeBoardVec.txt");

	cout << "____________________  reset function testing  ____________________\n";
	cout << "Before reset function : \n";
	printBoardDetails(&vec_6);
	cout << "\nAfter reset function : \n";
	vec_6.reset();
	printBoardDetails(&vec_6);

	cout << "___________________  setSize function testing  ___________________\n";
	cout << "Before setSize function : \n";
	BoardVector vec_7(2,2);
	printBoardDetails(&vec_7);
	cout << "\nAfter setSize function : \n";
	vec_7.setSize(5,5);
	printBoardDetails(&vec_7);

	cout << "____________________  move function testing  ____________________\n";
	BoardVector vec_8(4,4);
	printBoardDetails(&vec_8);
	vec_8.move('U');
	printBoardDetails(&vec_8);
	vec_8.move('L');
	printBoardDetails(&vec_8);
	vec_8.move('U');
	printBoardDetails(&vec_8);

	cout << "____________________  == operator testing  _____________________\n";
	BoardVector vec_9(3,3),vec_10(3,4);
	printBoardDetails(&vec_9);
	printBoardDetails(&vec_10);
	if(vec_9 == vec_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";
	vec_10.setSize(3,3);
	printBoardDetails(&vec_9);
	printBoardDetails(&vec_10);
	if(vec_9 == vec_10)
		cout << "\n-> These board are equal\n\n";
	else
		cout << "\n-> These board are not equal\n\n";


	cout << "\nNumber of Board objects created so far : " << AbstractBoard::NumberOfBoards() << endl;
}

void checkGlobalFunction(void)
{
	BoardVector *vec1,*vec2,*vec3;
	BoardArray1D *arr1D_1,*arr1D_2,*arr1D_3;
	BoardArray2D *arr2D_1,*arr2D_2,*arr2D_3;
	int size=9;

	vec1 = new BoardVector; vec1->readFromFile("testBoard/test1.txt");
	vec2 = new BoardVector; vec2->readFromFile("testBoard/test2.txt");
	vec3 = new BoardVector; vec3->readFromFile("testBoard/test3.txt");

	arr1D_1 = new BoardArray1D; arr1D_1->readFromFile("testBoard/test4.txt");
	arr1D_2 = new BoardArray1D; arr1D_2->readFromFile("testBoard/test5.txt");
	arr1D_3 = new BoardArray1D; arr1D_3->readFromFile("testBoard/test6.txt");

	arr2D_1 = new BoardArray2D; arr2D_1->readFromFile("testBoard/test7.txt");
	arr2D_2 = new BoardArray2D; arr2D_2->readFromFile("testBoard/test8.txt");
	arr2D_3 = new BoardArray2D; arr2D_3->readFromFile("testBoard/test9.txt");

	AbstractBoard *boards[size] = {vec1,vec2,vec3,arr1D_1,arr1D_2,arr1D_3,arr2D_1,arr2D_2,arr2D_3};

	cout << "\n\n------------------  Test the validity of the sequence  ------------------\n\n";
	cout << "-->(1)\n\n";

	for(int i=0 ; i < size ; ++i)
		printBoardDetails(boards[i]);

	if(checkValidSequence(boards,size))
		cout << "\n->The sequence is valid\n";
	else
		cout << "\n->The sequence is not valid\n\n";

	delete vec1;
	delete vec2;
	delete vec3;
	delete arr1D_1;
	delete arr1D_2;
	delete arr1D_3;
	delete arr2D_1;
	delete arr2D_2;
	delete arr2D_3;

	vec1 = new BoardVector; vec1->readFromFile("testBoard/test1.txt");
	vec2 = new BoardVector; vec2->readFromFile("testBoard/test2.txt");
	vec3 = new BoardVector; vec3->readFromFile("testBoard/test3.txt");

	arr1D_1 = new BoardArray1D; arr1D_1->readFromFile("testBoard/test4.txt");
	arr1D_2 = new BoardArray1D; arr1D_2->readFromFile("testBoard/test5_1.txt");
	arr1D_3 = new BoardArray1D; arr1D_3->readFromFile("testBoard/test6.txt");

	arr2D_1 = new BoardArray2D; arr2D_1->readFromFile("testBoard/test7.txt");
	arr2D_2 = new BoardArray2D; arr2D_2->readFromFile("testBoard/test8.txt");
	arr2D_3 = new BoardArray2D; arr2D_3->readFromFile("testBoard/test9.txt");

	AbstractBoard *boards2[size] = {vec1,vec2,vec3,arr1D_1,arr1D_2,arr1D_3,arr2D_1,arr2D_2,arr2D_3};

	cout << "\n\n-->(2)\n\n";

	for(int i=0 ; i < size ; ++i)
		printBoardDetails(boards2[i]);

	if(checkValidSequence(boards2,size))
		cout << "\n->The sequence is valid\n";
	else
		cout << "\n->The sequence is not valid\n";

	cout << "\nNumber of Board objects created so far : " << AbstractBoard::NumberOfBoards() << endl;

	delete vec1;
	delete vec2;
	delete vec3;
	delete arr1D_1;
	delete arr1D_2;
	delete arr1D_3;
	delete arr2D_1;
	delete arr2D_2;
	delete arr2D_3;
}