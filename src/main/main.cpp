#include "FileProcessor.h"
#include "md5.h"
#include "sha256.h"
#include <string>
#include <thread>


void result_hashes_and_read(const char* FILENAME) {
	std::cout << "File: " << FILENAME << std::endl;
	std::cout << "Bytes: " << size_file(FILENAME) << std::endl;
	std::string data_from_file = read_chunk_from_file(FILENAME);
	MD5 md5;
	std::thread th1(&MD5::update, std::ref(md5), reinterpret_cast<const unsigned char*>(data_from_file.c_str()), data_from_file.size());
	th1.join();
	std::cout << "MD5: " << md5.finalize() << std::endl;
	SHA256 sha256;
	std::thread th2(&SHA256::update, std::ref(sha256), reinterpret_cast<const unsigned char*>(data_from_file.c_str()), data_from_file.size());
	th2.join();
	std::cout << "SHA256: " << sha256.finalize() << std::endl;
}


int main() {
	
	result_hashes_and_read("D:/ProjectC++/CerberusHashes/gg.txt");

}