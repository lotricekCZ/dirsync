#include "variables.hpp"


bool variables::init(){
	return loop();
	}


bool variables::loop(){
	return update_directory() | update_blacklist() | update_temporary();
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
	bool inserted = false;
	for(auto l: list)
		inserted |= this -> blacklist.insert(l).second;
	return inserted;
	}



bool variables::update_blacklist(){
	if(whitelist || whitelist -> size() != 0){
		auto tmp = *whitelist;
	 	whitelist -> clear();
		return ((operation)? remove_blacklist(tmp): insert_blacklist(tmp));
		}
	whitelist.reset();
	return false;
	}



bool variables::update_directory(){
	if(dir_list.has_value() || dir_list -> size() != 0){
		auto tmp = *dir_list;
		dir_list -> clear();
		return ((operation)? remove_directory(tmp): insert_directory(tmp));
		}
	dir_list.reset();
	return false;
	}



bool variables::update_temporary(){
	if(temporary_tmp.has_value() || temporary_tmp -> size() != 0){
		temporary = *temporary_tmp;
		}
	temporary_tmp.reset();
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



uint8_t variables::get_view_mode(){
	return view_mode;
	}



void variables::set_view_mode(uint8_t v){
	view_mode = (mode)v;
	}



void variables::set_temporary(std::filesystem::path tmp, bool force){
	this -> temporary = ((std::filesystem::exists(tmp))? tmp: std::filesystem::temp_directory_path());
	if(force)
		this -> temporary_tmp = this -> temporary;
	}



void variables::set_temporary(std::string tmp, bool force){
	set_temporary(std::filesystem::path(tmp), force	);
	}



std::filesystem::path variables::get_temporary(){
	return temporary;	
	}



		