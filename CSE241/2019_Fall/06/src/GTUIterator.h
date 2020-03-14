#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include "Node.h"
#include <memory>

namespace GTU
{
	template<typename T>
	class GTUIterator
	{
	public:
		GTUIterator();
		GTUIterator(std::shared_ptr<Node<T> >o);
		T& operator*(void);
		T* operator->(void);
		GTUIterator<T> operator++(void);
		GTUIterator<T> operator++(int);
		GTUIterator<T> operator--(void);
		GTUIterator<T> operator--(int);
		/* Default assignment is OK for this class */
		bool operator==(const GTUIterator<T>&)const;
		bool operator!=(const GTUIterator<T>&)const;
	private:
		std::shared_ptr<Node<T> > iter;
	};

	template<typename T>
	GTUIterator<T>::GTUIterator():iter(nullptr)
	{}

	template<typename T>
	GTUIterator<T>::GTUIterator(std::shared_ptr<Node<T> > o):iter(o)
	{}

	template<typename T>
	T& GTUIterator<T>::operator*(void)
	{
		return iter->data;
	}

	template<typename T>
	T* GTUIterator<T>::operator->(void)
	{
		return &(iter->data);
	}

	template<typename T>
	GTUIterator<T> GTUIterator<T>::operator++(void)
	{
		return iter=iter->next;
	}

	template<typename T>
	GTUIterator<T> GTUIterator<T>::operator++(int ignoreMe)
	{
		std::shared_ptr<Node<T> > temp = iter;
		iter = iter->next;
		return temp;
	}

	template<typename T>
	GTUIterator<T> GTUIterator<T>::operator--(void)
	{
		return iter=iter->previous;
	}

	template<typename T>
	GTUIterator<T> GTUIterator<T>::operator--(int ignoreMe)
	{
		std::shared_ptr<Node<T> > temp = iter;
		iter = iter->previous;
		return temp;
	}

	template<typename T>
	bool GTUIterator<T>::operator==(const GTUIterator<T>& other)const
	{
		return iter == other.iter;
	}

	template<typename T>
	bool GTUIterator<T>::operator!=(const GTUIterator<T>& other)const
	{
		return iter != other.iter;
	}
}

#endif