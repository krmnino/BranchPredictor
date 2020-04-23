#include <fstream>
#include <string>
#include <vector>

#include "predictors.h"

void gshare(std::ofstream &out_file, std::string file_name) {
	std::string out = "";
	int correct;
	int total;
	for (int i = 2; i < 11; i++) {
		unsigned short extractor = 0;
		for (int j = 0; j <= i; j++) {
			extractor = (extractor << 1) | 1;
		}
		correct = 0;
		total = 0;
		int ghr = 0;
		std::vector<short> table;
		table.resize(2048, 3);
		unsigned long long addr;
		std::string behavior;
		unsigned long long target;
		std::ifstream infile(file_name);
		while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
			int index = (addr % 2048) ^ (ghr & extractor);
			(behavior == "T") ? ghr = (ghr << 1 | 1) : ghr = ghr << 1;
			if (0 < table[index] && table[index] <= 3 && behavior == "NT") {
				if (table[index] < 2) {
					correct++;
				}
				table[index]--;
			}
			else if (0 <= table[index] && table[index] < 3 && behavior == "T") {
				if (table[index] >= 2) {
					correct++;
				}
				table[index]++;
			}
			else {
				correct++;
			}
			total++;
		}
		infile.close();
		out_file << std::to_string(correct) << "," + std::to_string(total) << ";";
		if(i != 10){
			out_file << " ";
		}
	}
	out_file << std::endl;
}
