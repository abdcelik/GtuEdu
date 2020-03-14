#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include "AbstractBoard.h"
#include <vector>

namespace GTU_Board
{
	class BoardVector:public AbstractBoard
	{
	public:
		BoardVector();
		BoardVector(int);
		BoardVector(int,int);
		BoardVector(const BoardVector&);

		BoardVector& operator=(const BoardVector&);

		virtual bool setSize(int,int);
		virtual const int operator()(const int&,const int&)const;
		virtual int& operator()(const int&,const int&);

		virtual ~BoardVector();
	protected:
		std::vector<std::vector<int> > board;
	};
}

#endif