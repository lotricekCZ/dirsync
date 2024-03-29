#ifndef file_list_hpp
#define file_list_hpp

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <numeric>
#include "../found_file/found_file.hpp"
#include "../variables/variables.hpp"

class file_list: public std::vector<found_file> {
	public:
		std::shared_ptr<variables> variable_table;

		using std::vector<found_file>::pop_back;
		using std::vector<found_file>::emplace_back;
		using std::vector<found_file>::push_back;
		using std::vector<found_file>::back;
		using std::vector<found_file>::front;
		using std::vector<found_file>::begin;
		using std::vector<found_file>::end;
		using std::vector<found_file>::cbegin;
		using std::vector<found_file>::cend;
		using std::vector<found_file>::rbegin;
		using std::vector<found_file>::rend;
		using std::vector<found_file>::assign;
		using std::vector<found_file>::get_allocator;
		using std::vector<found_file>::at;
		using std::vector<found_file>::operator[];
		using std::vector<found_file>::empty;
		using std::vector<found_file>::size;
		using std::vector<found_file>::reserve;
		using std::vector<found_file>::capacity;
		using std::vector<found_file>::shrink_to_fit;
		using std::vector<found_file>::clear;
		using std::vector<found_file>::data;
		using std::vector<found_file>::insert;
		using std::vector<found_file>::iterator;
		using std::vector<found_file>::erase;
		std::vector<uint64_t> erased;
		file_list();
		void print();
		void update();
		bool changed();
		std::vector<uint64_t> get_erased();
		std::vector<uint64_t> get_indexes(std::vector<uint64_t> id);
		void erase(std::vector<uint64_t> id);
		void push_back(std::filesystem::path);
		void push_back(std::set<std::filesystem::path>);
		void push_back();
	};

#endif // file_list_hpp