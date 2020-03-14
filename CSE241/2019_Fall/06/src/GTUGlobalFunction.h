#ifndef GTUGLOBALFUNCTION_H
#define GTUGLOBALFUNCTION_H

namespace GTU
{
	template<typename InputIterator,typename InputValue>
	InputIterator find(InputIterator first, InputIterator last, const InputValue& val)
	{
		for(; first != last ; ++first)
			if(val == *first)
				return first;
		return last;
	}

	template<typename InputIterator,typename InputFunc>
	InputIterator find_if(InputIterator first, InputIterator last, InputFunc func)
	{
		for(; first != last ; ++first)
			if(func(*first))
				return first;
		return last;
	}

	template<typename InputIterator, typename InputFunc>
	InputFunc for_each(InputIterator first, InputIterator last, InputFunc func)
	{
		for(; first != last ; ++first)
			func(*first);
		return func;
	}
}

#endif