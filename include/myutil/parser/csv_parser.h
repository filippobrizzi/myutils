#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifdef USE_EIGEN
	#include <Eigen/Dense>
#endif

namespace myutil
{
namespace parser
{
class CsvManager
{
public:
	

//private:
	template<class T>
	static bool parse(const std::string &file_name, 
					  std::vector<T> &csv_values)
	{
		std::ifstream file(file_name);
		if (!file.is_open())
		{
			return false;
		}

		csv_values.clear();

		std::string line;
	    while (std::getline(file, line))
    	{
    		std::istringstream ss(line);
	        std::string field;
	        std::vector<std::string> line_accumulator;
	        while(std::getline(ss, field, ','))
	        {
	        	line_accumulator.push_back(field);
	        }
	        T value(line_accumulator.size());
	        for (int i = 0; i < line_accumulator.size(); ++i)
	        	value[i] = std::stod(line_accumulator[i]);

	        csv_values.push_back(value);
    	}
    	file.close();
    	return true;
	}

	template<class T>
	static bool write(const std::string &file_name,
					  const std::vector<T> &csv_values)
	{
		std::ofstream file(file_name);
		if (!file.is_open())
		{
			return false;
		}

		for (auto values : csv_values)
		{
			file << values[0];
			for (int i = 1; i < values.size(); ++i)
				file << "," << values[i];
			file << std::endl;
		}
		file.close();

		return true;
	}
};

#ifdef USE_EIGEN
static bool csvParse(const std::string &file_name, 
				  std::vector<Eigen::VectorXd> &csv_values)
{
	return CsvManager::parse<Eigen::VectorXd>(file_name, csv_values);
}
;
static bool csvWrite(const std::string &file_name,
				  const std::vector<Eigen::VectorXd> &csv_values)
{
	return CsvManager::write<Eigen::VectorXd>(file_name, csv_values);
}
#endif

static bool csvParse(const std::string &file_name, 
				  std::vector<std::vector<double> > &csv_values)
{
	return CsvManager::parse<std::vector<double> >(file_name, csv_values);
}
static bool csvWrite(const std::string &file_name,
				  const std::vector<std::vector<double> > &csv_values)
{
	return CsvManager::write<std::vector<double> >(file_name, csv_values);
}

}
}