#ifndef GTUSET_H
#define GTUSET_H

#include "GTUContainerDerived.h"

namespace GTU
{
	template<typename T>
	class GTUSet:public GTUContainerDerived<T>
	{
	public:
		GTUSet(int newSize=0);
		GTUSet(const GTUSet<T>&);
		const GTUSet<T>& operator=(const GTUSet<T>&);
		~GTUSet();

		GTUIterator<T> insert(T) throw(std::bad_pafram);
	};

	template<typename T>
	GTUSet<T>::GTUSet(int newSize):GTUContainerDerived<T>(newSize)
	{
		if(this->size())
		{
			std::shared_ptr<Node<T> > newHead(new Node<T>());
			std::shared_ptr<Node<T> > temp = newHead;

			for(int i=0 ; i < this->size()-1 ; ++i)
			{
				std::shared_ptr<Node<T> > newNode(new Node<T>());
				temp->next = newNode;
				newNode->previous = temp;
				temp = temp->next;
			}

			this->head = newHead;
			this->tail = temp;
		}
	}

	template<typename T>
	GTUSet<T>::GTUSet(const GTUSet& other):GTUContainerDerived<T>(other)
	{}

	template<typename T>
	const GTUSet<T>& GTUSet<T>::operator=(const GTUSet<T>& other)
	{
		GTUContainerDerived<T>::operator=(other);
		return *this;
	}

	template<typename T>
	GTUSet<T>::~GTUSet()
	{
		this->clear();
	}

	template<typename T>
	GTUIterator<T> GTUSet<T>::insert(T newData) throw(std::bad_pafram)
	{
		if(this->size() == this->max_size())
			throw(std::bad_pafram("The set has maximum capacity..."));

		std::shared_ptr<Node<T> > newNode(new Node<T>(newData));
		bool hasData = false;

		if(!this->size())
		{
			this->head = newNode;
			newNode->next = this->tail;
			this->tail->previous = newNode;
		}
		else
		{
			GTUIterator<T> newIter = newNode;

			for(auto it = this->begin() ; it != this->end() && !hasData ; ++it)
				if(*newIter == *it)
					throw std::bad_pafram("The set already has data...\n");

			if(!hasData)
			{
				newNode->next = this->tail;
				newNode->previous = this->tail->previous;
				this->tail->previous->next = newNode;
				this->tail->previous = newNode;
			}
		}

		if(!hasData)
			this->setSize(this->size()+1);

		return GTUIterator<T>(this->head);
	}
}
#endif
