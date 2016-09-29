[![Build Status](https://travis-ci.org/filippobrizzi/myutils.svg?branch=master)](https://travis-ci.org/filippobrizzi/myutils)

#Various C++ utilities#

## Parser ##
* csv_parser
	* Function to parse a csv file a produce a std::vector of std::vector or an Eigen matrix
* string_parser
	* `string_splitter`: split a string according to a given char and return an iterator to visit the 

##Template Library##
* count_iterator
	* utility to iterate over a container with the formula `for (auto i : contatiner)` while keeping loop count
* has_serialization 
	* Simple SFINAE implementation to inspect if a class a serialization function, can be easily adapted to the needed case
* is_some
	* `is_all<>`: Utility to test, in a variadic template, if all the instantiation type are the same.
	* `is_container<T>`: Utility to test if a type is a container
* `map_iterator`
	* `map_keys_iteration`: Utility to iterate just over the keys of a map or an unordered_map
	* `map_value_iteration`: Utility to iterate just over the values of a map or an unordered_map
