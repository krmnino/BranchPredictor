#include <fstream>
#include <string>
#include <vector>
#include <cmath>

void bimodal_1bit(std::ofstream &out_file, std::string file_name) {
	std::string out = "";
	int correct;
	int total;
	for (int i = 4; i < 12; i++) {
		if (i == 6) {
			continue;
		}
		int table_size = pow(2, i);
		std::vector<short> table;
		table.resize(table_size, 1);
		correct = 0;
		total = 0;
		unsigned long long addr;
		std::string behavior;
		unsigned long long target;
		std::ifstream infile(file_name);
		while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
			if (table[addr % table_size] == 1 && behavior == "NT") {
				table[addr % table_size] = 0;
			}
			else if (table[addr % table_size] == 0 && behavior == "T") {
				table[addr % table_size] = 1;
			}
			else {
				correct++;
			}
			total++;
		}
		infile.close();
		out_file << std::to_string(correct) << "," + std::to_string(total) << "; "; 
	}
	out_file << std::endl;
}