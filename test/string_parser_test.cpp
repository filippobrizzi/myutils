
#include <iostream>
#include <string>
#include <myutil/parser/string_parser.h>

int main()
{
	std::string s = "a,bcd,ef,g,hil";

	std::cout << s << std::endl;
	for(auto p: myutil::parser::string_splitter(s,','))
		std::cout << p << std::endl;

	std::string s2 = "ab : cdef :ghi";

	std::cout << s2 << std::endl;
	for (auto p: myutil::parser::string_splitter(s2, ':'))
		std::cout << p << std::endl;
}