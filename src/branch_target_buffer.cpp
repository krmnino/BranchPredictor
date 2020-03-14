#include <fstream>
#include <string>
#include <vector>

void branch_target_buffer(std::ofstream &out_file, std::string file_name) {
	int correct;
	int attempted;
	std::vector<unsigned long long> buffer; //second = target
	std::vector<short> table;
	buffer.resize(512);
	table.resize(512, 1);
	correct = 0;
	attempted = 0;
	unsigned long long addr;
	std::string behavior;
	unsigned long long target;
	std::ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (table[addr % 512] == 1) {
			attempted++;
			if(buffer[addr % 512] == target){
				correct++;
			}
		}
		if(behavior == "T") {
				buffer[addr % 512] = target;
		}
		if (table[addr % 512] == 1 && behavior == "NT") {
			table[addr % 512] = 0;
		}
		else if (table[addr % 512] == 0 && behavior == "T") {
			table[addr % 512] = 1;
		}
	}
	infile.close();
	out_file << std::to_string(correct) << "," << std::to_string(attempted) << ";" << std::endl;
}
