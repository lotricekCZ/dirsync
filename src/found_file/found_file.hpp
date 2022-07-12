#ifndef found_file_hpp
#define found_file_hpp

#include <string>
#include <filesystem>
#include <cinttypes>
#include <iostream>
#include <set>

class found_file {
	public:
		static uint16_t * significant;
		std::filesystem::path filename;
		// occurences throughout all the dirs with 
		std::set<std::pair<bool, std::filesystem::path>> occurences;
		uint16_t get_occurence_count();
		std::filesystem::path get_filename();
		
		found_file(std::filesystem::path);
		found_file(std::string);
		bool insert(std::filesystem::path);
		bool emplace(std::string);
		std::string print();
		// using std::filesystem::path::extension();
		// using std::filesystem::path::string();
		// using std::filesystem::path::c_str();
		bool operator == (std::filesystem::path rhs){
			// std::cout << ((rhs.filename().string().substr(0, *significant) == get_filename().string().substr(0, *significant))? "je stejne": "neni stejne") << std::endl;
			return rhs.filename().string().substr(0, *significant) 
				== get_filename().string().substr(0, *significant);
			}
	};

uint16_t * found_file::significant;

#endif // found_file