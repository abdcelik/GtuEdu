#ifndef GTUCONTAINERDERIVED_H
#define GTUCONTAINERDERIVED_H

#include "GTUContainer.h"
#include "Node.h"

namespace GTU
{
	template<typename T>
	class GTUContainerDerived:public GTUContainer<T>
	{
	public:
		GTUContainerDerived(int newSize=0);
		GTUContainerDerived(const GTUContainerDerived<T>&);
		const GTUContainerDerived<T>& operator=(const GTUContainerDerived<T>&);
		virtual ~GTUContainerDerived();

		virtual bool empty(void)const;
		virtual int size(void)const;
		virtual const int max_size(void)const;
		virtual GTUIterator<T> insert(T)=0;
		virtual void erase(GTUIterator<T>&) throw(std::bad_pafram);
		virtual void clear(void);
		virtual GTUIterator<T> begin(void) {return GTUIterator<T>(head);}
		virtual GTUIterator<T> end(void) {return GTUIterator<T>(tail);}

	protected:
		void setSize(int);
		std::shared_ptr<Node<T> > head;
		std::shared_ptr<Node<T> > tail;
		const int MAX_SIZE=10000;
		int capacity;
	};

	template<typename T>
	GTUContainerDerived<T>::GTUContainerDerived(int newSize)
	{
		tail = std::make_shared<Node<T> >();
		setSize(newSize);
	}

	template<typename T>
	GTUContainerDerived<T>::GTUContainerDerived(const GTUContainerDerived<T>& other)
	{
		tail = std::make_shared<Node<T> >();
		setSize(other.size());

		if(size())
		{
			std::shared_ptr<Node<T> > newHead(new Node<T>());
			std::shared_ptr<Node<T> > temp = newHead;

			for(int i=0 ; i < size()-1 ; ++i)
			{
				std::shared_ptr<Node<T> > newNode(new Node<T>());
				temp->next = newNode;
				newNode->previous = temp;
				temp = temp->next;
			}

			head = newHead;
			tail = temp->next;

			std::shared_ptr<Node<T> > myHead = head;
			std::shared_ptr<Node<T> > otherHead = other.head;
			for(int i=0 ; i < size() ; ++i)
			{
				myHead->data = otherHead->data;
				myHead = myHead->next;
				otherHead = otherHead->next;
			}
		}
	}

	template<typename T>
	const GTUContainerDerived<T>& GTUContainerDerived<T>::operator=(const GTUContainerDerived<T>& other)
	{
		clear();
		setSize(other.size());

		if(size())
		{
			std::shared_ptr<Node<T> > newHead(new Node<T>());
			std::shared_ptr<Node<T> > temp = newHead;

			for(int i=0 ; i < size()-1 ; ++i)
			{
				std::shared_ptr<Node<T> > newNode(new Node<T>());
				temp->next = newNode;
				newNode->previous = temp;
				temp = temp->next;
			}

			head = newHead;
			tail = temp->next;

			std::shared_ptr<Node<T> > myHead = head;
			std::shared_ptr<Node<T> > otherHead = other.head;
			for(int i=0 ; i < size() ; ++i)
			{
				myHead->data = otherHead->data;
				myHead = myHead->next;
				otherHead = otherHead->next;
			}
		}

		return *this;
	}
	template<typename T>
	GTUContainerDerived<T>::~GTUContainerDerived()
	{
		tail = nullptr;
	}

	template<typename T>
	bool GTUContainerDerived<T>::empty(void)const
	{
		if(!size())
			return true;
		return false;
	}

	template<typename T>
	int GTUContainerDerived<T>::size(void)const
	{
		return capacity;
	}

	template<typename T>
	const int GTUContainerDerived<T>::max_size(void)const
	{
		return MAX_SIZE;
	}

	template<typename T>
	void GTUContainerDerived<T>::erase(GTUIterator<T>& target) throw(std::bad_pafram)
	{
		if(size() == 1)
		{
			if(target == begin() || target == end())
			{
				head = nullptr , tail->previous = nullptr;
				setSize(size()-1);
			}
		}
		else if(size() > 0)
		{
			if(target == begin())
			{
				head->next->previous = nullptr;
				head = head->next;
				setSize(size()-1);
			}
			else
			{
				std::shared_ptr<Node<T> > temp = head;

				for(auto it = begin() ; it != target ; ++it , temp = temp->next)
					if(it == end());
						throw(std::bad_pafram("The container does not contain this data...\n"));

				temp->previous->next = temp->next;
				temp->next->previous = temp->previous;
				temp->next = nullptr;
				temp->previous = nullptr;
				setSize(size()-1);
			}
		}
	}

	template<typename T>
	void GTUContainerDerived<T>::clear(void)
	{
		std::shared_ptr<Node<T> > temp;

		while(head != nullptr)
		{
			temp = head;
			head = head->next;
			temp->previous = nullptr;
			temp->next = nullptr;
		}

		head = nullptr;
		setSize(0);
	}

	template<typename T>
	void GTUContainerDerived<T>::setSize(int newSize)
	{
		if(newSize < 0 || newSize > max_size())
			newSize = 0;

		capacity = newSize;
	}
}

#endif