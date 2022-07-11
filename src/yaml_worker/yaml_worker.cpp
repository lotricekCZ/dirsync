#include <iostream>
#include "yaml_worker.hpp"



yaml_worker::yaml_worker(std::string file) {
	// printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	settings = std::filesystem::path(std::filesystem::current_path()/file);
	}



void yaml_worker::read(){
	YAML::Node config = YAML::LoadFile(settings);
	variable_table -> set_significant(config["significant"].as<uint16_t>());
	variable_table -> set_blacklist(config["blacklist"].as<std::vector<std::string>>());
	variable_table -> set_directories(config["directories"].as<std::vector<std::string>>());
	}



void yaml_worker::write(){
	uint16_t significant = variable_table -> get_significant();
	this -> read();
	variable_table -> set_significant(significant);
	YAML::Emitter out;
	std::ofstream f_out(settings);
	// out << config;
	variable_table -> loop();
	out.SetIndent(4);
	out.SetSeqFormat(YAML::Flow);
	out << YAML::BeginMap;
	out << YAML::Key << "directories";
	out << YAML::Value << variable_table -> get_directories();
	out << YAML::Key << "significant";
	out << YAML::Value << variable_table -> get_significant();
	out << YAML::Key << "blacklist";
	out << YAML::Value << variable_table -> get_blacklist();
	out << YAML::EndMap;
	// a << config;
	std::cout << out.c_str() << std::endl << std::endl;
	f_out << out.c_str();
	f_out.close();
	}