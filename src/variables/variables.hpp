#ifndef variables_hpp
#define variables_hpp

#include <iostream>
#include <cinttypes>
#include <filesystem>
#include <string>


class variables {
	private:	
		std::filesystem::path settings;
		uint16_t significant;
		std::vector<std::filesystem::path> directories;
		std::vector<std::string> blacklist;
	public:
		std::vector<std::string> whitelist;
		std::vector<std::filesystem::path> dir_list;
		variables() = default;
		void init();

		uint16_t get_significant(); // returns sig or 1 if sig is 0
		std::vector<std::filesystem::path> get_directories();
		std::vector<std::string> get_blacklist();

		void set_significant(uint16_t);
		void set_directories(std::vector<std::filesystem::path>);
		void set_blacklist(std::vector<std::string>);
	};


#endif // variables_hpp