#include "variables.hpp"


bool variables::init(){
	return loop();
	}


bool variables::loop(){
	return update_directory() | update_blacklist();
	}



uint16_t variables::get_significant(){
	return (this -> significant == 0) + this -> significant; 
	}



std::set<std::filesystem::path> variables::get_directories(){
	return this -> directories;
	}



std::set<std::string> variables::get_blacklist(){
	return this -> blacklist;
	}



bool variables::set_significant(uint16_t sig){
	bool r = (sig != this -> significant);
	this -> significant = ((sig == 0)? 1: sig);
	return r;
	}



void variables::set_directories(std::set<std::filesystem::path> dirs){
	this -> directories = dirs;
	}



void variables::set_directories(std::set<std::string> dirs){
	this -> directories.clear();
	for(auto i: dirs)
		this -> directories.emplace(i);
	}



void variables::set_directories(std::vector<std::string> dirs){
	this -> directories.clear();
	for(auto i: dirs)
		this -> directories.emplace(i);
	}



void variables::set_directories(std::vector<std::filesystem::path> dirs){
	this -> set_directories(std::set(dirs.begin(), dirs.end()));
	}



void variables::set_blacklist(std::set<std::string> list){
	this -> blacklist = list;
	}



void variables::set_blacklist(std::vector<std::string> list){
	this -> set_blacklist(std::set(list.begin(), list.end()));
	}



bool variables::insert_directory(std::vector<std::filesystem::path> dir){
	bool removed = false;
	auto p = std::filesystem::current_path();
	for(auto l: dir)
		removed |= this -> directories.insert(std::filesystem::absolute(l)).second;
	return removed;
	}



bool variables::insert_blacklist(std::vector<std::string> list){
	bool removed = false;
	for(auto l: list)
		removed |= this -> blacklist.insert(l).second;
	return removed;
	}



bool variables::update_blacklist(){
	if(whitelist)
		return ((operation)? remove_blacklist(*whitelist): insert_blacklist(*whitelist));
	whitelist.reset();
	return false;
	}



bool variables::update_directory(){
	if(dir_list)
		return ((operation)? remove_directory(*dir_list): insert_directory(*dir_list));
	dir_list.reset();
	return false;
	}



bool variables::remove_directory(std::vector<std::filesystem::path> dir){
	bool removed = false;
	auto p = std::filesystem::current_path();
	for(auto l: dir)
		removed |= directories.erase(std::filesystem::absolute(l));
	return removed;
	}



bool variables::remove_blacklist(std::vector<std::string> list){
	bool removed = false;
	for(auto l: list)
		removed |= blacklist.erase(l);
	return removed;
	}

