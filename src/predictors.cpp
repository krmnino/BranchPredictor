#include <iostream>
#include <fstream>

#include "predictors.h"

int main(int argc, char* argv[]) {
	if(argc != 3){
		std::cout << "usage: ./predictions [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return 0;
	}
	std::ofstream out_file(argv[2]);
	all_taken(out_file, argv[1]);
	all_not_taken(out_file, argv[1]);
	bimodal_1bit(out_file, argv[1]);
	bimodal_2bit(out_file, argv[1]);
	gshare(out_file, argv[1]);
	tournament(out_file, argv[1]);
	branch_target_buffer(out_file, argv[1]);
	out_file.close();
	return 0;
}
