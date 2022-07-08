#include <filesystem>
#include <string>
#include <memory>
#include "../variables/variables.hpp"
#include <yaml-cpp/yaml.h>

#ifndef yaml_worker_hpp
#define yaml_worker_hpp


class yaml_worker {
	private:	
		std::filesystem::path settings;
	public:
		std::shared_ptr<variables> variable_table;
		yaml_worker(std::string file);
		void read();
		void init();
	};


#endif // yaml_worker_hpp