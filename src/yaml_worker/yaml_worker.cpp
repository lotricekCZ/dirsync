#include <iostream>
#include "yaml_worker.hpp"



yaml_worker::yaml_worker(std::string file) {
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	settings = std::filesystem::path(std::filesystem::current_path()/file);
	}


void yaml_worker::read(){
	YAML::Node config = YAML::LoadFile(settings);
	variable_table -> set_significant(config["significant"].as<uint16_t>());
	variable_table -> set_blacklist(std::vector<std::string>(config["blacklist"].as<std::vector<std::string>>()));
	for (auto i: config["blacklist"].as<std::vector<std::string>>()){
		std::cout << i << std::endl;
		}
	}