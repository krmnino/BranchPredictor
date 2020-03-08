#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

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
	int correct;
	int total;
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
	int correct;
	int total;
	for (int i = 4; i < 11; i++) {
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
		cout << correct << "," << total << "; ";
		infile.close();
	}
}

void gshare(string file_name) {
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
		vector<short> table;
		table.resize(2048, 3);
		unsigned long long addr;
		string behavior;
		unsigned long long target;
		ifstream infile(file_name);
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
		cout << correct << "," << total << "; ";
		infile.close();
	}
}

void tournament(string file_name) {
	unsigned long long addr;
	string behavior;
	unsigned long long target;
	ifstream infile(file_name);
	int correct = 0;
	int total = 0;
	vector<short> table_bimodal_2bit;
	vector<short> table_gshare;
	vector<short> selector_table;
	table_bimodal_2bit.resize(2048, 3);
	table_gshare.resize(2048, 3);
	selector_table.resize(2048, 0);
	int ghr = 0;
	int sb_index; //holds index of selector table and bimodal predictor table 
	int g_index; //holds index of gshare
	int gshare_prediction; //holds prediction of gshare table at g_index
	int bimodal_prediction; //holds prediction of bimodal table at sb_index
	int selector_prediction; //holds prediction of selector table at sb_index
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		sb_index = addr % 2048;
		g_index = (addr % 2048) ^ (ghr & 0x7FF);
		gshare_prediction = table_gshare[g_index];
		bimodal_prediction = table_bimodal_2bit[sb_index];
		selector_prediction = selector_table[sb_index];
		if (0 <= selector_prediction && selector_prediction < 2) { //if selector prefers gshare
			if ((0 <= gshare_prediction && gshare_prediction < 2 && behavior == "NT") || (2 <= gshare_prediction && gshare_prediction <= 3 && behavior == "T")) { //if selected predictor is correct
				correct++;
				if ((0 <= gshare_prediction && gshare_prediction < 2) && !(0 <= bimodal_prediction && bimodal_prediction < 2) && behavior == "NT") { //if gshare correct and bimodal wrong when behavior is not taken
					if (selector_table[sb_index] > 0) {
						selector_table[sb_index]--;
					}
				}
				else if ((2 <= gshare_prediction && gshare_prediction <= 3) && !(2 <= bimodal_prediction && bimodal_prediction <= 3) && behavior == "T") {  //if gshare correct and bimodal wrong when behavior is taken
					if (selector_table[sb_index] > 0) {
						selector_table[sb_index]--;
					}
				}
			}
			else { //if selected predictor is wrong
				if (!(0 <= gshare_prediction && gshare_prediction < 2) && (0 <= bimodal_prediction && bimodal_prediction < 2) && behavior == "NT") { //if gshare wrong and bimodal correct when behavior is not taken
					if (selector_table[sb_index] < 3) {
						selector_table[sb_index]++;
					}
				}
				else if (!(2 <= gshare_prediction && gshare_prediction <= 3) && (2 <= bimodal_prediction && bimodal_prediction <= 3) && behavior == "T") { //if gshare wrong and bimodal correct when behavior is taken
					if (selector_table[sb_index] < 3) {
						selector_table[sb_index]++;
					}
				}
			}
		}
		else if (2 <= selector_prediction && selector_prediction <= 3) { //if selector prefers bimodal
			if ((0 <= bimodal_prediction && bimodal_prediction < 2 && behavior == "NT") || (2 <= bimodal_prediction && bimodal_prediction <= 3 && behavior == "T")) { //if selected predictor is correct
				correct++;
				if ((0 <= bimodal_prediction && bimodal_prediction < 2) && !(0 <= gshare_prediction && gshare_prediction < 2) && behavior == "NT") { //if bimodal correct and gshare wrong when behavior is not taken
					if (selector_table[sb_index] < 3) {
						selector_table[sb_index]++;
					}
				}
				else if ((2 <= bimodal_prediction && bimodal_prediction <= 3) && !(2 <= gshare_prediction && gshare_prediction <= 3) && behavior == "T") { //if bimodal correct and gshare wrong when behavior is taken
					if (selector_table[sb_index] < 3) {
						selector_table[sb_index]++;
					}
				}
			}
			else { //if selected predictor is wrong
				if (!(0 <= bimodal_prediction && bimodal_prediction < 2) && (0 <= gshare_prediction && gshare_prediction < 2) && behavior == "NT") { //if bimodal wrong and gshare correct when behavior is not taken
					if (selector_table[sb_index] > 0) {
						selector_table[sb_index]--;
					}
				}
				else if (!(2 <= bimodal_prediction && bimodal_prediction <= 3) && (2 <= gshare_prediction && gshare_prediction <= 3) && behavior == "T") { //if bimodal wrong and gshare correct when behavior is taken
					if (selector_table[sb_index] > 0) {
						selector_table[sb_index]--;
					}
				}
			}
		}
		if (behavior == "NT") {
			if (table_gshare[g_index] > 0) {
				table_gshare[g_index]--;
			}
			if (table_bimodal_2bit[sb_index] > 0) {
				table_bimodal_2bit[sb_index]--;
			}
		}
		else if (behavior == "T") {
			if (table_gshare[g_index] < 3) {
				table_gshare[g_index]++;
			}
			if (table_bimodal_2bit[sb_index] < 3) {
				table_bimodal_2bit[sb_index]++;
			}
		}
		(behavior == "T") ? ghr = (ghr << 1 | 1) : ghr = ghr << 1;
		total++;
	}
	cout << correct << "," << total << "; ";
	infile.close();
}

void branch_target_buffer(string file_name) {
	int accesses;
	int correct;
	vector<pair<unsigned long long, unsigned long long>> buffer; //first = addr, second = target
	vector<short> table;
	buffer.resize(128);
	table.resize(512, 1);
	accesses = 0;
	correct = 0;
	unsigned long long addr;
	string behavior;
	unsigned long long target;
	ifstream infile(file_name);
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
	cout << accesses << "," << correct << "; ";
	infile.close();
}

void test_mod(string file_name) {
	for (int i = 2; i < 11; i++) {
		unsigned short extractor = 0;
		for (int j = 0; j <= i; j++) {
			extractor = extractor << 1 | 1;
		}
		cout << extractor << endl;
	}
}

int main(int argc, char* argv[]) {
	//string name = "short_trace1.txt";
	string name = "short_trace1.txt";
	//all_taken(name);
	//all_not_taken(name);
	//bimodal_1bit(name);
	//bimodal_2bit(name);
	//gshare(name);
	//tournament(name);
	branch_target_buffer(name);
	//test_mod(name);
	cout << endl;
	return 0;
}
