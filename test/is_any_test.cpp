#include <iostream>
#include <vector>
#include <myutil/tl/is_any.hpp>


template<class...T>
void is_all_int(T ... vars)
{
	//static_assert(myutil::tl::is_all<int, T...>::value, "not all of type int");
	// ...
}



int main()
{
	is_all_int(1, 2, 3, 4 ,5);
	is_all_int(2.0, 2.1);


	std::vector<int> vi;

	static_assert(myutil::tl::is_container<decltype(vi)>::value, "is not a container");


	int i;
	//static_assert(myutil::tl::is_container<decltype(i)>::value, "is not a container");

}