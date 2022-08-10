#include <iostream>
#include <yaml-cpp/yaml.h>
#include <argumentum/argparse.h>

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/builder.h>
#include <glibmm/main.h>

#include <climits>
#include <numeric>
#include <string>
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <memory>
#include <optional>
#include <set>
#include <thread>
#include <map>
#include <cinttypes>




#include "./yaml_worker/yaml_worker.hpp"
#include "./variables/variables.hpp"
#include "./found_file/found_file.hpp"
#include "./file_list/file_list.hpp"

#include "./gui/elements/double_text.hpp"
#include "./gui/elements/list_operator.hpp"
#include "./gui/elements/list_file.hpp"
#include "./gui/elements/presets.hpp"
#include "./gui/window/window.hpp"
// using namespace argumentum;

int main(int argc, char** argv){
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	auto app = Gtk::Application::create(
		argc, argv, 
		"org.gtkmm.example.sample"
		);
	
	std::shared_ptr<variables> variable_table(new variables());
	std::shared_ptr<file_list> files(new file_list());
	std::shared_ptr<yaml_worker> worker(new yaml_worker("../settings.yaml"));
	// file_list files;

	worker -> variable_table = files -> variable_table = variable_table;
	worker -> read();
	
	
	for(auto i : variable_table -> get_blacklist())
		std::cout << i << std::endl;
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
		

	auto parser = argumentum::argument_parser{};
	parser.config().program(argv[0]).description("diesync");
	auto params = parser.params();
	// params.add_parameter(numbers, "N").minargs(1).metavar("INT").help("Integers");
	// params.add_parameter(isSum, "--sum", "-s")
	// 	.nargs(0)
	// 	.help("Sum the integers (default: find the max)");

	params.add_parameter(variable_table -> significant_tmp, "--important", "-i")
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
	parser.parse_args(argc, argv, 1);
	// if(!parser.parse_args(argc, argv, 1))
	// 	return 1;
	worker -> write();

	found_file::significant = &variable_table -> significant;
	files -> push_back();
	// printf(": %i\n", vars -> dir_list -> size());
	window hw(variable_table, files, worker);
	hw.fill();
	for(auto o: *files)
		std::cout << o.print() << std::endl;
	printf("\nsamostatnych souboru: %i\n", files -> size());

	return app->run(hw);
	}