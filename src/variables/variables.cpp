#include "variables.hpp"

uint16_t variables::get_significant(){
	return (this -> significant == 0) + this -> significant; 
	}



std::vector<std::filesystem::path> variables::get_directories(){
	return this -> directories;
	}



std::vector<std::string> variables::get_blacklist(){
	return this -> blacklist;
	}



void variables::set_significant(uint16_t sig){
	this -> significant = ((sig == 0)? 1: sig);
	}



void variables::set_directories(std::vector<std::filesystem::path> dirs){
	this -> directories = dirs;
	}



void variables::set_blacklist(std::vector<std::string> list){
	this -> blacklist = list;
	}


