#ifndef variables_hpp
#define variables_hpp

#include <iostream>
#include <cinttypes>
#include <filesystem>
#include <string>
#include <algorithm>
#include <optional>
#include <set>

class variables {
	private:	
		std::filesystem::path settings;
		std::filesystem::path temporary;
		std::set<std::filesystem::path> directories;
		std::set<std::string> blacklist;
		enum mode: uint8_t {
			normal	 = 0,
			ignored	 = 1,
			all		 = 2
			} view_mode;
	public:
		bool block = 1;
		uint16_t significant;
		std::optional<std::vector<std::string>> whitelist;
		std::optional<std::vector<std::filesystem::path>> dir_list;
		std::optional<uint16_t> significant_tmp;
		bool operation; // insert 0 or remove 1
		variables() = default;
		bool init();
		bool loop();
		
		uint16_t get_significant(); // returns sig or 1 if sig is 0
		std::set<std::filesystem::path> get_directories();
		std::set<std::string> get_blacklist();
		
		void set_temporary(std::filesystem::path);
		void set_temporary(std::string);
		std::filesystem::path get_temporary();
		
		uint8_t get_view_mode();
		void set_view_mode(uint8_t);
		bool set_significant(uint16_t);
		void set_directories(std::set<std::string>);
		void set_directories(std::set<std::filesystem::path>);
		void set_directories(std::vector<std::filesystem::path>);
		void set_directories(std::vector<std::string>);

		void set_blacklist(std::set<std::string>);
		void set_blacklist(std::vector<std::string>);

		bool insert_directory(std::vector<std::filesystem::path>);
		bool insert_blacklist(std::vector<std::string>);

		bool remove_directory(std::vector<std::filesystem::path>);
		bool remove_blacklist(std::vector<std::string>);

		bool update_directory();
		bool update_blacklist();

	};


#endif // variables_hpp