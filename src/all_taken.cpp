#include <fstream>
#include <string>

#include "predictors.h"

void all_taken(std::ofstream &out_file, std::string file_name) {
	long correct = 0;
	long total = 0;
	unsigned long long addr;
	std::string behavior;
	unsigned long long target;
	std::ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (behavior == "T") {
			correct++;
		}
		total++;
	}
	infile.close();
	out_file << std::to_string(correct) << "," + std::to_string(total) << ";" << std::endl; 
}