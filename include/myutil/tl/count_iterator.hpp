#pragma once

#include <type_traits>
#include <functional>

#include <myutil/tl/is_any.hpp>

namespace myutil
{

namespace tl
{

template<class Container>
struct count_access
{
	static_assert(is_container<Container>::value,
				  "Template type not valid, is not a container");
	struct iterator
	{
		using iterator_t = typename std::conditional<std::is_const<Container>::value,
                                                     typename Container::const_iterator,
                                                     typename Container::iterator
                                                    >::type;

        using pre_value_t = typename Container::value_type;

        using value_t = typename std::conditional<std::is_const<Container>::value,
                                                  typename std::add_const<pre_value_t>::type,
                                                  pre_value_t
                                                 >::type;

        iterator(iterator_t itr)
        	: base_iterator(itr)
    	{}

    	bool operator != (const iterator & it) const
    	{
    		return base_iterator != it.base_iterator;
    	}
   	 
    	std::pair<unsigned int, typename std::add_lvalue_reference<value_t>::type> operator*()
    	{
    		return std::make_pair(count, std::ref(*base_iterator));
    	}

    	std::pair<unsigned int, typename std::add_pointer<value_t>::type> operator->()
    	{
    		return std::make_pair<unsigned int, typename std::add_pointer<value_t>::type>(count, &*base_iterator);
    	}

    	iterator & operator++()
        {
            ++base_iterator;
            ++count;
            return *this;
        }

        iterator operator++(int)
        {
            iterator itr(*this);
            ++base_iterator;
            ++count;
            return itr;
        }
    	
    	iterator_t base_iterator;
    	unsigned int count = 0;
	};

	count_access(Container & data)
		: data_(data)
	{}

	iterator begin() { return iterator(data_.begin()); }
	iterator end()   { return iterator(data_.end());   }
	std::size_t size() const { return data_.size(); }

private:
	Container & data_;
};

template<class Container>
count_access<Container> count_iteration(Container & data)
{
	return count_access<Container>(data);
}

template<class Container>
count_access<const Container> count_iteration(const Container & data)
{
	return count_access<const Container>(data);
}

}
}