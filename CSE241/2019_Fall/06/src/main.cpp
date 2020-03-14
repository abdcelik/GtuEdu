#include <iostream>

#include "GTUVector.h"
#include "GTUSet.h"
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "GTUGlobalFunction.h"
#include "GTUException.h"

using namespace GTU;
using namespace std;

bool isOdd(int i) // only testing find_if function
{
	return (i%2==1);
}

bool isUpper(char c) // only testing find_if function
{
	return (c >= 65 && c <= 90);
}

template<typename T>
void print(T var) // only testing for_each function
{
	cout << var << " ";
}

int main()
{
	cout << "\n---------------- Test GTUVector Class ----------------\n"; 

	GTUVector<double> vec1;

	cout << "Size : " << vec1.size() << endl;
	cout << "Max Size : " << vec1.max_size() << endl;

	cout << "\nTesting GTUVector's 'GTUIterator<T> insert(T)' function\n";

	for(int i=0 ; i < 10 ; ++i)
	{
		cout << "Insert " << i << " to vector\n";
		vec1.insert(i);
	}

	cout << "\nVector elements : \n";
	for(auto it = vec1.begin() ; it != vec1.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUVector's 'void clear(void)' function __\n";
	cout << "Before clear function :\n";
	cout << "Size : " << vec1.size() << endl;
	cout << "After clear function :\n";
	vec1.clear();
	cout << "Size : " << vec1.size() << endl;

	cout << "\n__ Testing GTUVector's 'GTUIterator<T> insert(GTUIterator<T>&,T)' function __\n";
	
	GTUIterator<double> iter;

	for(int i=0 ; i < 10 ; ++i)
	{
		cout << "Insert " << i << " to vector's end\n";
		iter = vec1.end();
		vec1.insert(iter,i);
	}

	cout << "\nVector elements : \n";
	for(auto it = vec1.begin() ; it != vec1.end() ; ++it)
		cout << *it << " ";
	cout << endl;
	cout << "\n________________________________________________________\n";


	cout << "\n__ Testing GTUVector's copy constructor __\n";
	GTUVector<double> vec2(vec1);

	cout << "After copy constructor vector's elements :\n";
	cout << "Size : " << vec2.size() << endl;

	for(auto it = vec2.begin() ; it != vec2.end() ; ++it)
		cout << *it << " ";
	cout << endl;
	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUVector's assignment operator __\n";
	GTUVector<double> vec4;
	cout << "Before assignment operator :\n";
	cout << "Size : " << vec4.size() << endl;
	cout << "After assignment operator :\n";
	vec4 = vec1;
	cout << "Size : " << vec4.size() << endl;
	cout << "Elements :\n";
	for(auto it = vec4.begin() ; it != vec4.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n__ Testing insert's bad_pafram exception __\n";
	GTUVector<double> vec3;

	for(int i=0 ; i < 10 ; ++i)
		vec3.insert(i);

	GTUIterator<double> iter2 = vec2.begin();

	try
	{
		vec3.insert(iter2,1.0);
	}
	catch(const bad_pafram& obj)
	{
		obj.printMessage();
	}

	cout << "\n__ Testing insert's bad_pafram exception for max_size __\n";
	GTUVector<int> vec5;
	try
	{
		while(true)
			vec5.insert(1.0);
	}
	catch(const bad_pafram& obj)
	{
		obj.printMessage();
	}

	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUVector's 'void erase(GTUIterator<T>&)' function __\n";
	cout << "Before clear function : ";
	cout << "Size : " << vec3.size() << endl;
	cout << "Elements : \n";
	for(auto it = vec3.begin() ; it != vec3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "After clear function : \n";
	iter2 = vec3.begin();
	vec3.erase(iter2);
	cout << "Elements : \n";
	for(auto it = vec3.begin() ; it != vec3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n__ Testing clear's bad_pafram exception __\n";
	try
	{
		iter2 = vec3.end();
		vec3.erase(iter2);
	}
	catch(const bad_pafram& obj)
	{
		obj.printMessage();
	}

	cout << "\n__ Testing empty function __\n";
	while(vec3.empty() == false)
	{
		cout << "Erase first element\n";
		iter2 = vec3.begin();
		vec3.erase(iter2);
		cout << "Size : " << vec3.size() << endl;
		if(vec3.empty() == false)
		{
			cout << "Elements :\n";
			for(auto it = vec3.begin() ; it != vec3.end() ; ++it)
				cout << *it << " ";
			cout << endl;
		}
		else
			cout << "EMPTY!\n";
	}

	cout << "\n __ Testing Global Function __\n";

	GTUVector<int> vec6;

	for(int i=0 ; i<10 ; ++i)
		vec6.insert(i);

	cout << "find function :\n";
	cout << "elements :\n";
	for(auto it = vec6.begin() ; it != vec6.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	GTUIterator<int> iter5;
	cout << "Find 5 : \n";
	iter5 = find(vec6.begin(),vec6.end(),5);
	cout << *iter5 << endl;
	cout << "Find 3 : \n";
	iter5 = find(vec6.begin(),vec6.end(),3);
	cout << *iter5 << endl;

	cout << "\nfind_if function :\n";

	cout << "elements :\n";
	for(auto it = vec6.begin() ; it != vec6.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "Find If odd number : \n";
	iter5 = find_if(vec6.begin(),vec6.end(),isOdd);
	cout << *iter5 << endl;

	cout << "\nfor_each function :\n";
	cout << "Print all elements\n";
	for_each(vec6.begin(),vec6.end(),print<int>);
	cout << endl;


	cout << "\n---------------- Test GTUSet Class ----------------\n"; 

	GTUSet<char> set1;

	cout << "Size : " << set1.size() << endl;
	cout << "Max Size : " << set1.max_size() << endl;

	cout << "\nTesting GTUSet's 'GTUIterator<T> insert(T)' function\n";

	for(char i='a' ; i < 'a'+10 ; ++i)
	{
		cout << "Insert " << i << " to set\n";
		set1.insert(i);
	}

	cout << "\nSet elements :\n";
	for(auto it = set1.begin() ; it != set1.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUSet's copy constructor __\n";
	GTUSet<char> set2(set1);

	cout << "After copy constructor set's elements :\n";
	cout << "Size : " << set2.size() << endl;

	for(auto it = set2.begin() ; it != set2.end() ; ++it)
		cout << *it << " ";
	cout << endl;
	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUSet's assignment operator __\n";
	GTUSet<char> set4;
	cout << "Before assignment operator :\n";
	cout << "Size : " << set4.size() << endl;
	cout << "After assignment operator :\n";
	set4 = set1;
	cout << "Size : " << set4.size() << endl;
	cout << "Elements :\n";
	for(auto it = set4.begin() ; it != set4.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n__ Testing insert's bad_pafram exception __\n";
	GTUSet<char> set3;

	for(int i='a' ; i < 'a'+10 ; ++i)
		set3.insert(i);

	try
	{
		set3.insert('a');
	}
	catch(const bad_pafram& obj)
	{
		obj.printMessage();
	}

	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUSet's 'void erase(GTUIterator<T>&)' function __\n";
	cout << "Before clear function : ";
	cout << "Size : " << set3.size() << endl;
	cout << "Elements : \n";
	for(auto it = set3.begin() ; it != set3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "After clear function : \n";
	GTUIterator<char> iter3 = set3.begin();
	set3.erase(iter3);
	cout << "Elements : \n";
	for(auto it = set3.begin() ; it != set3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "\n__ Testing clear's bad_pafram exception __\n";
	try
	{
		iter3 = set3.end();
		set3.erase(iter3);
	}
	catch(const bad_pafram& obj)
	{
		obj.printMessage();
	}

	cout << "\n __ Testing Global Function __\n";

	cout << "find function :\n";
	cout << "elements :\n";
	for(auto it = set3.begin() ; it != set3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	GTUIterator<char> iter4;
	cout << "Find 'c' : \n";
	iter4 = find(set3.begin(),set3.end(),'c');
	cout << *iter4 << endl;
	cout << "Find 'e' : \n";
	iter4 = find(set3.begin(),set3.end(),'e');
	cout << *iter4 << endl;

	cout << "\nfind_if function :\n";
	set3.insert('A');

	cout << "elements :\n";
	for(auto it = set3.begin() ; it != set3.end() ; ++it)
		cout << *it << " ";
	cout << endl;

	cout << "Find If upper letter : \n";
	iter4 = find_if(set3.begin(),set3.end(),isUpper);
	cout << *iter4 << endl;

	cout << "\nfor_each function :\n";
	cout << "Print all elements\n";
	for_each(set3.begin(),set3.end(),print<char>);
	cout << endl;

	cout << "\n________________________________________________________\n";

	cout << "\n__ Testing GTUIterator Class __\n";

	GTUIterator<int> iter_1,iter_2;
	GTUVector<int> vec_1;

	for(int i=0 ; i<10 ; ++i)
		vec_1.insert(i);

	iter_1 = vec_1.begin();
	iter_2 = vec_1.begin();

	cout << "iter_1 points " << *iter_1 << endl;
	cout << "After prefix, iter_1 points " << *(++iter_1) << endl;
	cout << "After postfix, iter_1 points " << *(iter_1++) << endl;
	cout << "Result postfix iter_1 points " << *iter_1 << endl;
	*iter_1 = 25;
	cout << "After dereference operator iter_1 points " << *iter_1 << endl;
	
	cout << "\niter_1 points " << *iter_1 << " iter_2 points " << *iter_2 << endl;

	if(iter_1 == iter_2)
		cout << "iter_1 and iter_2 are equals\n";
	else if(iter_1 != iter_2)
		cout << "iter_1 and iter_2 are not equals\n";

	cout << "\nAfter negative prefix, iter_1 points " << *(--iter_1) << endl;
	cout << "After negative prefix, iter_1 points " << *(--iter_1) << endl;

	if(iter_1 == iter_2)
		cout << "iter_1 and iter_2 are equals\n";
	else if(iter_1 != iter_2)
		cout << "iter_1 and iter_2 are not equals\n";

	iter_1 = --vec_1.end();
	cout << "\niter_1 points " << *iter_1 << " iter_2 points " << *iter_2 << endl;
	iter_1 = iter_2;
	cout << "After assignment operator " << "iter_1 points " << *iter_1 << " iter_2 points " << *iter_2 << endl;
	cout << "\n________________________________________________________\n";
	
	return 0;
}