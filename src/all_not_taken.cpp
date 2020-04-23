#include <fstream>
#include <string>

#include "predictors.h"

void all_not_taken(std::ofstream &out_file, std::string file_name) {
	int correct = 0;
	int total = 0;
	unsigned long long addr;
	std::string behavior;
	unsigned long long target;
	std::ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (behavior == "NT") {
			correct++;
		}
		total++;
	}
	infile.close();
	out_file << std::to_string(correct) << "," + std::to_string(total) << ";" << std::endl; 
}