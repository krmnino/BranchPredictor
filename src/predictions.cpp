#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include <bitset>

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
	int prediction;
	int ghr = 0;
	while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
		int sb_index = addr % 2048;
		int g_index = (addr % 2048) ^ (ghr & 0x7FF);
		int gshare_prediction = table_gshare[(addr % 2048) ^ (ghr & 0x7FF)];
		int bimodal_prediction = table_bimodal_2bit[addr % 2048];
		int selector_prediction = selector_table[addr % 2048];
		if(0 <= selector_prediction && selector_prediction < 2){
			prediction = 0;
		}
		else if(2 <= selector_prediction && selector_prediction <= 3){
			prediction = 1;
		}
		if(prediction == 0){
			if(0 <= gshare_prediction && gshare_prediction < 3 && behavior == "NT"){
				if(gshare_prediction < 2){
					if(selector_prediction < 3){
						selector_table[addr % 2048]++;
					}
					correct++;
				}
				if(gshare_prediction > 0){
					table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]--;
				}
			}
			else if(0 < gshare_prediction && gshare_prediction <= 3 && behavior == "T"){
				if(gshare_prediction >= 2){
					if(selector_prediction > 0){
						selector_table[addr % 2048]--;
					}
					correct++;
				}
				if(gshare_prediction < 3){
					table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]++;
				}		
			}
			else{
				if(selector_table[addr % 2048] < 3){
					selector_table[addr % 2048]++;
				}
				if(behavior == "T"){
					if(gshare_prediction < 3){
						table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]++;
					}
					if(bimodal_prediction < 3){
						table_bimodal_2bit[(addr % 2048) ^ (ghr & 0x7FF)]++;
					}
				}
				else{
					if(gshare_prediction > 0){
						table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]--;
					}
					if(bimodal_prediction > 0){
						table_bimodal_2bit[(addr % 2048) ^ (ghr & 0x7FF)]--;
					}
				}
			}
			(behavior == "T") ? ghr = (ghr << 1 | 1) : ghr = ghr << 1;
			total++;
		}
		else if(prediction == 1){
			if(0 <= bimodal_prediction && bimodal_prediction < 3 && behavior == "NT"){
				if(bimodal_prediction < 2){
					if(selector_prediction < 3){
						selector_table[addr % 2048]++;
					}
					correct++;
				}
				table_bimodal_2bit[addr % 2048]--;
			}
			else if(0 < bimodal_prediction && bimodal_prediction <= 3 && behavior == "T"){
				if(bimodal_prediction >= 2){
					if(selector_prediction < 3){
						selector_table[addr % 2048]++;
					}
					correct++;
				}
				table_bimodal_2bit[addr % 2048]++;
			}
			else{
				if(selector_table[addr % 2048] > 0){
					selector_table[addr % 2048]--;
				}
				if(behavior == "T"){
					if(gshare_prediction < 3){
						table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]++;
					}
					if(bimodal_prediction < 3){
						table_bimodal_2bit[(addr % 2048) ^ (ghr & 0x7FF)]++;
					}
				}
				else{
					if(gshare_prediction > 0){
						table_gshare[(addr % 2048) ^ (ghr & 0x7FF)]--;
					}
					if(bimodal_prediction > 0){
						table_bimodal_2bit[(addr % 2048) ^ (ghr & 0x7FF)]--;
					}
				}
			}
			(behavior == "T") ? ghr = (ghr << 1 | 1) : ghr = ghr << 1;
			total++;
		}
	}
	cout << correct << "," << total << "; ";
	infile.close();
}

void branch_target_buffer() {

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
	tournament(name);
	//test_mod(name);
	cout << endl;
	return 0;
}
