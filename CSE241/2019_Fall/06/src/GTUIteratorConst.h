#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include "Node.h"
#include <memory>

namespace GTU
{
	template<typename T>
	class GTUIteratorConst
	{
	public:
		GTUIteratorConst();
		GTUIteratorConst(std::shared_ptr<Node<T> >o);
		const T& operator*(void);
		const T* operator->(void);
		GTUIteratorConst<T> operator++(void);
		GTUIteratorConst<T> operator++(int);
		GTUIteratorConst<T> operator--(void);
		GTUIteratorConst<T> operator--(int);
		/* Default assignment is OK for this class */
		bool operator==(const GTUIteratorConst<T>&)const;
		bool operator!=(const GTUIteratorConst<T>&)const;
	private:
		std::shared_ptr<Node<T> > iter;
	};

	template<typename T>
	GTUIteratorConst<T>::GTUIteratorConst():iter(nullptr)
	{}

	template<typename T>
	GTUIteratorConst<T>::GTUIteratorConst(std::shared_ptr<Node<T> > o):iter(o)
	{}

	template<typename T>
	const T& GTUIteratorConst<T>::operator*(void)
	{
		return iter->data;
	}

	template<typename T>
	const T* GTUIteratorConst<T>::operator->(void)
	{
		return &(iter->data);
	}

	template<typename T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator++(void)
	{
		return iter=iter->next;
	}

	template<typename T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator++(int ignoreMe)
	{
		std::shared_ptr<Node<T> > temp = iter;
		iter = iter->next;
		return temp;
	}

	template<typename T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator--(void)
	{
		std::shared_ptr<Node<T> > temp = iter;
		iter = iter->previous;
		return temp;
	}

	template<typename T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator--(int ignoreMe)
	{
		return iter=iter->previous;
	}

	template<typename T>
	bool GTUIteratorConst<T>::operator==(const GTUIteratorConst<T>& other)const
	{
		return iter == other.iter;
	}

	template<typename T>
	bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst<T>& other)const
	{
		return iter != other.iter;
	}
}

#endif