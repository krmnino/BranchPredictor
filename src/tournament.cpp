#include <fstream>
#include <string>
#include <vector>

#include "predictors.h"

void tournament(std::ofstream &out_file, std::string file_name) {
	unsigned long long addr;
	std::string behavior;
	unsigned long long target;
	std::ifstream infile(file_name);
	int correct = 0;
	int total = 0;
	std::vector<short> table_bimodal_2bit;
	std::vector<short> table_gshare;
	std::vector<short> selector_table;
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
	infile.close();
	out_file << std::to_string(correct) << "," + std::to_string(total) << ";" << std::endl; 
}