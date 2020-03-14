#ifndef NODE_H
#define NODE_H

#include <memory>

namespace GTU
{
	template<typename T>
	class Node
	{
	public:
		Node(){}
		Node(T&);
		T data;
		std::shared_ptr<Node<T> > previous;
		std::shared_ptr<Node<T> > next;
	};

	template<typename T>
	Node<T>::Node(T& newData):data(newData),previous(nullptr),next(nullptr)
	{}
}

#endif