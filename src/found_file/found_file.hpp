#include <string>
#include <filesystem>
#include <cinttypes>

class found_file {
	public:
		std::string filename("");
		
		// occurences throughout all the dirs with 
		std::vector<std::pair<bool, std::filesystem::path>> occurences; 
		uint8_t is_ignored: 	1;
		uint16_t get_occurence_count();
		
		bool operator == (const std::filesystem::path &rhs){
			
			}
	};