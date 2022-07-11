#include <iostream>
#include <yaml-cpp/yaml.h>
#include <argumentum/argparse.h>
#include <climits>
#include <numeric>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <memory>
#include <optional>

#include "./yaml_worker/yaml_worker.hpp"
#include "./variables/variables.hpp"

// using namespace argumentum;

int main(int argc, char** argv){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::shared_ptr<variables> variable_table(new variables());
	yaml_worker worker("../settings.yaml");
	worker.variable_table = variable_table;
	worker.read();
	for(auto i : variable_table -> get_blacklist())
		std::cout << i << std::endl;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	std::vector<int> numbers;
	// std::vector<std::string> numbers;
	bool isSum = false;
	

	auto parser = argumentum::argument_parser{};
	parser.config().program(argv[0]).description("Accumulator");
	auto params = parser.params();
	// params.add_parameter(numbers, "N").minargs(1).metavar("INT").help("Integers");
	// params.add_parameter(isSum, "--sum", "-s")
	// 	.nargs(0)
	// 	.help("Sum the integers (default: find the max)");

	params.add_parameter(variable_table -> significant, "--important", "-i")
		.nargs(1)
		.metavar("int")
		.help("Overwrites current number of significant characters.");

	params.add_parameter(variable_table -> whitelist, "--list", "-l")
		.minargs(1)
		.metavar("ext")
		.help("Adds file extensions to list of ignored.\n\tRemoves file extensions from list of ignored if -r is passed.\n\tRemoves all if no arguments are passed.");
		
	params.add_parameter(variable_table -> dir_list, "--dirs", "-d")
		.minargs(1)
		.metavar("dir")
		.help("Appends directories to current selection.\n\tRemoves from selection if -r is passed.");
		
	params.add_parameter(variable_table -> operation, "--remove", "-r")
		.nargs(0)
		.help("Toggles remove flag.");
	
	// std::filesystem::path p("../A");
	// for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{p}){
    //     std::cout << dir_entry << " je soubor\n";
    // 	}
	if(!parser.parse_args(argc, argv, 1))
		return 1;
	worker.write();
	// auto mmax = [](auto&& a, auto&& b) {return std::max(a, b);};
	// auto acc = isSum ? accumulate(numbers.begin(), numbers.end(), 0)
	// 				: accumulate(numbers.begin(), numbers.end(), INT_MIN, mmax);
	// std::cout << acc << "\n";
	return 0;
	}