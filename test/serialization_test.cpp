

#include <iostream>

#include <myutil/tl/has_serialization.hpp>

class A
{
public:
	std::string serialize() const
	{
		return "A";
	}
};


class B
{
public:
	std::string to_string() const
	{
		return "B";
	}
};

class C
{
public:
	int i = 1;
};

std::string to_string(const C& c)
{
	return std::to_string(c.i);
}

class D 
{
public:
	int i = 2;
};

template<class T>
void print(const T &o)
{
	std::cout << myutil::tl::serialize(o) << std::endl;
}

int main()
{
	A a;
	B b;
	C c;
	D d;

	print(a);
	print(b);
	print(c);
	print(d);
	print(5);
}