#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void all_taken(string file_name) {
	int correct = 0;
	int total = 0;
	unsigned long long addr;
	string behavior;
	unsigned long long target;
	ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (behavior == "T") {
			correct++;
		}
		total++;
	}
	infile.close();
	cout << correct << "," << total << "; ";
}

void all_not_taken(string file_name) {
	int correct = 0;
	int total = 0;
	unsigned long long addr;
	string behavior;
	unsigned long long target;
	ifstream infile(file_name);
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		if (behavior == "NT") {
			correct++;
		}
		total++;
	}
	infile.close();
	cout << correct << "," << total << "; ";
}

void bimodal_1bit(string file_name) {
	int correct = 0;
	int total = 0;
	for (int i = 4; i < 12; i++) {
		if (i == 6) {
			continue;
		}
		int table_size = pow(2, i);
		vector<short> table;
		table.resize(table_size, 1);
		correct = 0;
		total = 0;
		unsigned long long addr;
		string behavior;
		unsigned long long target;
		ifstream infile(file_name);
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
		cout << correct << "," << total << "; ";
		infile.close();
	}
}

void bimodal_2bit(string file_name) {
	int correct = 0;
	int total = 0;
	for (int i = 4; i < 12; i++) {
		if (i == 6) {
			continue;
		}
		int table_size = pow(2, i);
		vector<short> table;
		table.resize(table_size, 3);
		correct = 0;
		total = 0;
		unsigned long long addr;
		string behavior;
		unsigned long long target;
		ifstream infile(file_name);
		while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
			if (0 < table[addr % table_size] && table[addr % table_size] <= 3 && behavior == "NT") {
				if(table[addr % table_size] < 2){
					correct++;
				}
				table[addr % table_size]--;
			}
			else if (0 <= table[addr % table_size] && table[addr % table_size] < 3 && behavior == "T") {
				if(table[addr % table_size] >= 2){
					correct++;
				}
				table[addr % table_size]++;
			}
			else {
				correct++;
			}
			total++;
		}
		cout << correct << "," << total << "; ";
		infile.close();
	}
}

void gshare() {

}

void tournament() {

}

void branch_target_buffer() {

}

void test_mod(string file_name) {
	for (int i = 4; i < 12; i++) {
		if (i == 6) continue;
		cout << pow(2, i) << endl;
	}
}

int main(int argc, char* argv[]) {
	//string name = "short_trace1.txt";
	string name = "short_trace1.txt";
	//all_taken(name);
	//all_not_taken(name);
	//bimodal_1bit(name);
	bimodal_2bit(name);
	//test_mod(name);
	cout << endl;
	return 0;
}
