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




void file_list::update(){
	// std::vector<found_file> tmp = *this;
	this -> clear();
	this -> push_back();
	// while(tmp.size()){
	// 	for(auto a = this -> begin(); a != this -> end(); a++)
	// 		if(*a == tmp.back()){
	// 			a -> id = tmp.back().id;
	// 			break;
	// 			}
	// 	tmp.pop_back();
	// 	}
	}




void file_list::erase(std::vector<uint64_t> id){
	for(uint64_t i: id)
		for(uint32_t j = 0; j < this -> size(); j++)
			if(i == this -> at(j).id){

				this -> erase(this -> begin() + j--);
				}
	// erased.insert(erased.end(), id.begin(), id.end()); // this is here to pull
	}



std::vector<uint64_t> file_list::get_indexes(std::vector<uint64_t> id){
	std::vector<uint64_t> ret;
	for(uint64_t i: id)
		for(uint32_t j = 0; j < this -> size(); j++)
			if(i == this -> at(j).id){
				ret.push_back(j);
				}
	// erased.insert(erased.end(), id.begin(), id.end()); // this is here to pull
	std::sort(ret.begin(), ret.end());
	return ret;
	}
