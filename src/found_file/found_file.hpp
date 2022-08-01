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
		uint64_t id = 0; // invisible id that tells me if found_file is listed
		std::filesystem::path filename;
		// occurences throughout all the dirs with 
		std::set<std::pair<bool, std::filesystem::path>> occurences;
		uint16_t get_occurence_count();
		std::filesystem::path get_filename();
		std::filesystem::path get_stem();
		
		found_file(std::filesystem::path);
		found_file(std::string);
		bool insert(std::filesystem::path);
		bool emplace(std::string);
		std::string print();
		// using std::filesystem::path::extension();
		// using std::filesystem::path::string();
		// using std::filesystem::path::c_str();
		uint16_t get_significant();
		bool operator == (std::filesystem::path rhs){
			// std::cout << ((rhs.filename().string().substr(0, *significant) == get_filename().string().substr(0, *significant))? "je stejne": "neni stejne") << std::endl;
			return rhs.stem().string().substr(0, *significant) 
				== get_stem().string().substr(0, *significant);
			}
	};

uint16_t * found_file::significant;

#endif // found_file