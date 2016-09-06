#pragma once

#include <fstream>
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
	enum class Error
	{
		NO_ERROR = 0,
		INVALID_FILE_NAME
	}

#ifdef USE_EIGEN
	static Error parse(const std::string &file_name, 
					  std::vector<Eigen::VectorXd> &csv_values)
	{
		return parse<Eigen::VectorXd>(file_name, csv_values);
	}
	;
	static Error write(const std::string &file_name,
					  const std::vector<Eigen::VectorXd> &csv_values)
	{
		return write<Eigen::VectorXd>(file_name, csv_values);
	}
#endif

	static Error parse(const std::string &file_name, 
					  std::vector<std::vector<double> > &csv_values)
	{
		return parse<std::vector<double>(file_name, csv_values);
	}
	static Error write(const std::string &file_name,
					  const std::vector<std::vector<double> > &csv_values)
	{
		return write<std::vector<double> >(file_name, csv_values);
	}
private:
	template<class T>
	static Error parse(const std::string &file_name, 
					  std::vector<class T> &csv_values)
	{
		std::ifstream file(file_name);
		if (!file.is_open())
		{
			return INVALID_FILE_NAME;
		}

		csv_values.clear();

		std::string line;
	    while (std::getline(file, line))
    	{
    		std::istringstream ss(line);
	        std::string field;
	        std::vector<std::string> line_accumulator;
	        while(std::getline(ss, filed, ','))
	        {
	        	line_accumulator.push_back(filed);
	        }
	        T value(line_accumulator.size());
	        for (int i = 0; i < line_accumulator.size(); ++i)
	        	value[i] = std::stod(line_accumulator[i]);

	        csv_values.push_back(value);
    	}
    	file.close()
    	return NO_ERROR;
	}

	template<class T>
	static Error write(const std::string &file_name,
					  const std::vector<T> &csv_values)
	{
		std::ofstream file(file_name);
		if (!file.is_open())
		{
			return INVALID_FILE_NAME;
		}

		for (auto values : csv_values)
		{
			file << values[0];
			for (int i = 1; i < values; ++i)
				file << "," << values[i];
			file << std::endl;
		}
		file.close();

		return NO_ERROR;
	}
};

}
}