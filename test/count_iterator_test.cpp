#include <iostream>
#include <vector>

#include <myutil/tl/count_iterator.hpp>

int main()
{

	std::vector<int> v = {1, 1, 2, 3, 5, 8, 13, 21, 34};

	for (auto it : myutil::tl::count_iteration(v))
	{
		std::cout << it.first << " " << it.second << std::endl;
		it.second = 1;
	}
	std::cout << " ..... " << std::endl;

	for (auto it : myutil::tl::count_iteration(v))
	{
		std::cout << it.first << " " << it.second << std::endl;
	}


	const std::vector<int> vv = {1, 2, 4, 8, 16, 32};


	std::cout << "-------------" << std::endl;
	for (auto it : myutil::tl::count_iteration(vv))
	{
		std::cout << it.first << " " << it.second << std::endl;
		//it.second = 1;
	}

	//int a = 1;

	{
		class A
		{
			int b;
		};
		A a;
		// auto b = myutil::tl::count_iteration(a); // ERROR static assert fail
	}


}

