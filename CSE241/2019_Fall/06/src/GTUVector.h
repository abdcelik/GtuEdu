#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include "GTUContainerDerived.h"

namespace GTU
{
	template<typename T>
	class GTUVector:public GTUContainerDerived<T>
	{
	public:
		GTUVector(int newSize=0);
		GTUVector(const GTUVector<T>&);
		const GTUVector<T>& operator=(const GTUVector<T>&);
		~GTUVector();

		GTUIterator<T> insert(T) throw(std::bad_pafram);
		GTUIterator<T> insert(GTUIterator<T>&,T) throw(std::bad_pafram);
		T& operator[](int);
		const T& operator[](int)const;
	};

	template<typename T>
	GTUVector<T>::GTUVector(int newSize):GTUContainerDerived<T>(newSize)
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
			this->tail = temp->next;
		}
	}

	template<typename T>
	GTUVector<T>::GTUVector(const GTUVector& other):GTUContainerDerived<T>(other)
	{}

	template<typename T>
	const GTUVector<T>& GTUVector<T>::operator=(const GTUVector<T>& other)
	{
		GTUContainerDerived<T>::operator=(other);
		return *this;
	}

	template<typename T>
	GTUVector<T>::~GTUVector()
	{
		this->clear();
	}

	template<typename T>
	GTUIterator<T> GTUVector<T>::insert(T newData) throw(std::bad_pafram)
	{
		if(this->size() == this->max_size())
			throw(std::bad_pafram("The vector has maximum capacity..."));

		std::shared_ptr<Node<T> > newNode(new Node<T>(newData));

		if(!this->size())
		{
			this->head = newNode;
			newNode->next = this->tail;
			this->tail->previous = newNode;
		}
		else
		{
			newNode->next = this->tail;
			newNode->previous = this->tail->previous;
			this->tail->previous->next = newNode;
			this->tail->previous = newNode;
		}

		this->setSize(this->size()+1);

		return GTUIterator<T>(this->head);
	}

	template<typename T>
	GTUIterator<T> GTUVector<T>::insert(GTUIterator<T>& target, T newData) throw(std::bad_pafram)
	{
		if(this->size() == this->max_size())
			throw(std::bad_pafram("The vector has maximum capacity..."));
		
		std::shared_ptr<Node<T> > newNode(new Node<T>(newData));

		if(target == this->begin())
		{
			if(!this->size())
				newNode->next = this->tail;
			else
				newNode->next = this->head;
			
			this->tail->previous = newNode;
			this->head = newNode;
		}
		else if(target == this->end())
		{
			insert(newData);
			this->setSize(this->size()-1);
		}
		else
		{
			std::shared_ptr<Node<T> > temp = this->head;

			for(auto it = this->begin() ; it != target ; ++it , temp = temp->next)
			{
				if(it == this->end());
					throw(std::bad_pafram("Invalid iterator...\n"));	
			}

			newNode->previous = temp->previous;
			newNode->next = temp;
			temp->previous->next = newNode;
			temp->previous = newNode;
		}

		this->setSize(this->size()+1);

		return GTUIterator<T>(this->head);
	}

	template<typename T>
	T& GTUVector<T>::operator[](int index)
	{
		std::shared_ptr<Node<T> > temp = this->head;

		for(int i=0 ; i < index ; ++i)
			temp = temp->next;

		return temp->data;
	}

	template<typename T>
	const T& GTUVector<T>::operator[](int index)const
	{
		std::shared_ptr<Node<T> > temp = this->head;

		for(int i=0 ; i < index ; ++i)
			temp = temp->next;

		return temp->data;
	}
}

#endif