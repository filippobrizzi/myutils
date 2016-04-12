
#include <iostream>
#include <string>
#include "string_parser.h"

int main()
{
	std::string s = "a,bcd,ef,g,hil";

	std::cout << s << std::endl;
	for(auto p: myutil::string_splitter(s,','))
		std::cout << p << std::endl;

	std::string s2 = "ab : cdef :ghi";

	std::cout << s2 << std::endl;
	for (auto p: myutil::string_splitter(s2, ':'))
		std::cout << p << std::endl;
}