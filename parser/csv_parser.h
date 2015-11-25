#include <fstream>
#include <vector>
#include <Eigen/Dense>

namespace myutil
{
class CsvParser
{
public:
	enum Error
	{
		NO_ERROR = 0,
		INVALID_FILE_NAME
	}

	static Error parse(const std::string file_name, 
					  std::vector<Eigen::VectorXd> &csv_values)
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
	        Eigen::VectorXd value(line_accumulator.size());
	        for (int i = 0; i < line_accumulator.size(); ++i)
	        	value[i] = std::stod(line_accumulator[i]);

	        csv_values.push_back(value);
    	}
	}

	static bool parse(const std::string file_name, 
					  std::vector<std::vector<double> > &csv_values)
	{

	}	

};


}