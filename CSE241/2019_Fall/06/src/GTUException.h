#ifndef GTUEXCEPTION_H
#define GTUEXCEPTION_H

#include <iostream>
#include <string>

namespace std
{
	class bad_pafram
	{
	public:
		bad_pafram(const string& errorMessage):message(errorMessage){}
		void printMessage(void)const {std::cout << message;}
	private:
		string message;
	};
}

#endif