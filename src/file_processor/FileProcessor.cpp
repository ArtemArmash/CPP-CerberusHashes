#include "FileProcessor.h"
#include <fstream>
#include <iostream>
#define CHUNK_SIZE 1024

std::string read_chunk_from_file(const char* FILENAME)
{

	std::ifstream fin(FILENAME, std::ios::in | std::ios::binary);
	if (!fin.is_open()) {
		throw std::runtime_error("Cant opened this file\n");
	}
	char buffer[CHUNK_SIZE];
	
	std::string result;
	while (fin.read(buffer, CHUNK_SIZE) || fin.gcount() > 0)
	{
		result.append(buffer, fin.gcount());
	}
	fin.close();
	return result;
	
}

std::streamsize size_file(const char* FILENAME)
{
	std::ifstream fin(FILENAME, std::ios::binary | std::ios::ate);
	if (!fin.is_open()) {
		throw std::runtime_error("Cant opened this file\n");
	}
	std::streamsize size = fin.tellg();
	fin.close();
	
	return size;
}
