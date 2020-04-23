#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "predictors.h"

void bimodal_2bit(std::ofstream &out_file, std::string file_name) {
	std::string out = "";
	int correct;
	int total;
	for (int i = 4; i < 12; i++) {
		if (i == 6) {
			continue;
		}
		int table_size = pow(2, i);
		std::vector<short> table;
		table.resize(table_size, 3);
		correct = 0;
		total = 0;
		unsigned long long addr;
		std::string behavior;
		unsigned long long target;
		std::ifstream infile(file_name);
		while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
			if (0 < table[addr % table_size] && table[addr % table_size] <= 3 && behavior == "NT") {
				if (table[addr % table_size] < 2) {
					correct++;
				}
				table[addr % table_size]--;
			}
			else if (0 <= table[addr % table_size] && table[addr % table_size] < 3 && behavior == "T") {
				if (table[addr % table_size] >= 2) {
					correct++;
				}
				table[addr % table_size]++;
			}
			else {
				correct++;
			}
			total++;
		}
		infile.close();
		out_file << std::to_string(correct) << "," + std::to_string(total) << ";";
		if(i != 11){
			out_file << " ";
		}
	}
	out_file << std::endl;
}
