#include "found_file.hpp"


found_file::found_file(std::filesystem::path p){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	if(insert(p))
		this -> filename = (this -> occurences.begin()) -> second.filename();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



found_file::found_file(std::string s){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	if(emplace(s))
		this -> filename = (this -> occurences.begin()) -> second.filename();
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	}



bool found_file::insert(std::filesystem::path p){
	printf("%s: %i\n", __PRETTY_FUNCTION__, __LINE__);
	return this -> occurences.insert({0, p}).second;
	}



bool found_file::emplace(std::string s){
	return this -> occurences.insert({0, std::filesystem::path(s)}).second;
	}



uint16_t found_file::get_occurence_count(){
	return this -> occurences.size();
	}



std::filesystem::path found_file::get_filename(){
	return this -> filename.filename();
	}



std::filesystem::path found_file::get_stem(){
	return this -> filename.stem();
	}



std::string found_file::print(){
	if(get_occurence_count() < 2)
		return ("|> " + std::to_string(get_occurence_count()) + " <|  name: " + filename.string());
	return ("|  " + std::to_string(get_occurence_count()) + "  |  name: " + filename.string());
	}



uint16_t found_file::get_significant(){
	return ((*significant)? *significant: 1);
	}



void found_file::tick_all(){
	for(auto &[a, b]: occurences)
		a = 1;
	}