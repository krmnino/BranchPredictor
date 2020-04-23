#ifndef PRED
#define PRED 

#include <string>

void all_not_taken(std::ofstream &, std::string);
void all_taken(std::ofstream &, std::string);
void bimodal_1bit(std::ofstream &, std::string);
void bimodal_2bit(std::ofstream &, std::string);
void branch_target_buffer(std::ofstream &, std::string);
void gshare(std::ofstream &, std::string);
void tournament(std::ofstream &, std::string);

#endif