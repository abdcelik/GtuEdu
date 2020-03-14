#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include "GTUIterator.h"
#include "GTUException.h"

namespace GTU
{
	template<typename T>
	class GTUContainer
	{
	public:
		virtual bool empty(void)const=0;
		virtual int size(void)const=0;
		virtual const int max_size(void)const=0;
		virtual GTUIterator<T> insert(T)=0;
		virtual void erase(GTUIterator<T>&)=0;
		virtual void clear()=0;
		virtual GTUIterator<T> begin(void)=0;
		virtual GTUIterator<T> end(void)=0;
		virtual ~GTUContainer(){};
	};
}

#endif