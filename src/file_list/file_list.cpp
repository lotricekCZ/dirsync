#include "file_list.hpp"

file_list::file_list() : std::vector<found_file>(){

	}



void file_list::print(){
	for(auto o: *this)
		std::cout << o.print() << std::endl;
	}



void file_list::push_back(std::filesystem::path path){
	file_list::iterator index = this -> end();
	// std::vector<found_file>
	bool ok = false;
	for(auto extension: variable_table -> get_blacklist())
		if(extension == path.extension().string())
			ok = true;
	// if the file extension isn't among ignored
	if(!ok){
		for(file_list::iterator j = this -> begin(); j != this -> end(); j++){
			found_file found = *j;
			if(found == path)
				index = j;
			}
		if(index == this -> end()){
			this -> emplace_back(path);
			} else {
				index -> insert(path);
				}
		}
	}



void file_list::push_back(std::set<std::filesystem::path> paths){
	for(auto i: paths)
		for(auto const& o: std::filesystem::directory_iterator{i})
			this -> push_back(std::filesystem::path(o));
	}



void file_list::push_back(){
	this -> push_back(variable_table -> get_directories());
	}
