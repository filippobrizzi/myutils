#define USE_EIGEN

#include "csv_parser.h"



int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Pass a csv file to be parsed!\n";
		return -1;
	}

	std::string file_name = argv[1];

	std::cout << "Eigen test\n";
	std::cout << "Parse\n";
	std::vector<Eigen::VectorXd> values;
	if (myutil::CsvManager::parse(file_name, values) == 0)
	{
		for (auto v : values)
			std::cout << v.transpose() << std::endl;

		std::cout << "Eigen test SUCCESS\n";

		std::cout << "Write\n";
		if (myutil::CsvManager::write(file_name))	
	}
	else
	{
		std::cerr << "Eigen test FAIL\n";
	}

	

	std::cout << "std::vector test\n";
	std::vector

}

