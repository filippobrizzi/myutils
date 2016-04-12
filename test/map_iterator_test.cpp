#include <iostream>
#include <unordered_map>

#include "map_iterator.hpp"

int main()
{

	std::unordered_map<int, std::string> umap = {{0, "a"},
												 {1, "b"},
												 {2, "c"},
												 {3, "d"}};

 	for (auto & kv : umap)
 		std::cout << kv.first << " " << kv.second << std::endl;

 	std::cout << "\nKeys:\n";

 	for (auto k : myutil::tl::map_keys_iteration(umap))
 		std::cout << k << std::endl;

 	std::cout << "\nValues:\n";

 	for (auto v : myutil::tl::map_values_iteration(umap))
 		std::cout << v << std::endl;

}