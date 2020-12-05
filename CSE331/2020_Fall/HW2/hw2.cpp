#include <iostream>
using namespace std;

typedef struct
{
	int *arr;
	int size;
	int capacity;
}Vector;

Vector in;
Vector out;

int CheckSumPossibility(int num, int arr[], int size);
int getNonNegIntWithText(const char*,const char*);
void printArray(int*,int);
void initializeVector(Vector*,int);
void addItemToVector(Vector*,int);
void freeMemory(Vector*);

int main()
{
	int size = getNonNegIntWithText("Size: ", "Number should be non-negative! Please enter non-negative integer: ");
	int num = getNonNegIntWithText("Target number: ", "Number should be non-negative! Please enter non-negative integer: ");
	int returnVal;

	initializeVector(&in,size);
	initializeVector(&out,0);

	for(int i=0 ; i < in.capacity ; ++i)
	{
		cout << i+1;
		addItemToVector(&in,getNonNegIntWithText(". element: ", "Number should be non-negative! Please enter non-negative integer: "));
	}

	returnVal = CheckSumPossibility(num,in.arr,in.size);

	if(returnVal == 1)
		cout << "Possible!";
	else
		cout << "Not possible!";


	printArray(out.arr,out.size);
	cout << endl;

	freeMemory(&in);
	freeMemory(&out);
	return 0;
}

int CheckSumPossibility(int num, int arr[], int size)
{
    if(num == 0)
	    return 1;
    if(size == 0)
		return 0;
	
	if(num - *arr >= 0 && CheckSumPossibility(num - *arr, arr+1, size-1))
	{
	    addItemToVector(&out,*arr);
	    return 1;
	}
	
	return CheckSumPossibility(num, arr+1, size-1);
}

int getNonNegIntWithText(const char* t1, const char* t2)
{
	int var;

	cout << t1;
	cin >> var;

	while(var < 0)
	{
		cout << t2;
		cin >> var;
	}

	return var;
}

void printArray(int* arr, int size)
{
	for(int i=0 ; i < size ; ++i)
		cout << " " << arr[i];
}

void initializeVector(Vector* vec, int capacity)
{
	if(capacity <= 0)
		capacity = 1;

	vec->arr = new int[capacity];
	vec->size = 0;
	vec->capacity = capacity;
}

void addItemToVector(Vector* vec, int item)
{
	if(vec->size == vec->capacity)
	{
		vec->capacity *= 2;
		int* arr = new int[vec->capacity];

		for(int i=0 ; i < vec->size ; ++i)
			arr[i] = vec->arr[i];
		delete[] vec->arr;
		vec->arr = arr;
	}

	vec->arr[vec->size] = item;
	++(vec->size);
}

void freeMemory(Vector* vec)
{
	delete[] vec->arr;
}