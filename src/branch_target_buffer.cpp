#include <fstream>
#include <string>
#include <vector>

void branch_target_buffer(std::ofstream &out_file, std::string file_name) {
	int accesses;
	int correct;
	std::vector<std::pair<unsigned long long, unsigned long long>> buffer; //first = addr, second = target
	std::vector<short> table;
	buffer.resize(128);
	table.resize(512, 1);
	accesses = 0;
	correct = 0;
	unsigned long long addr;
	std::string behavior;
	unsigned long long target;
	std::ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (table[addr % 512] == 1) {
			accesses++;
			int buffer_index = addr % 128;
			if (buffer[addr % 128].first != addr) {
				buffer[addr % 128].first = addr;
				buffer[addr % 128].second = target;
			}
			else {
				if (buffer[addr % 128].second == target) {
					correct++;
				}
			}
		}
		if (table[addr % 512] == 1 && behavior == "NT") {
			table[addr % 512] = 0;
		}
		else if (table[addr % 512] == 0 && behavior == "T") {
			table[addr % 512] = 1;
		}
	}
	infile.close();
	out_file << std::to_string(accesses) << "," << std::to_string(correct) << ";" << std::endl;
}