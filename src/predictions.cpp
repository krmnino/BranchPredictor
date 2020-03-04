#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void all_taken(string file_name){
  int correct = 0;
  int total = 0;
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  ifstream infile(file_name);
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    if(behavior == "T"){
      correct++;
    }
    total++;
  }
  infile.close();
  cout << (double)correct / total * 100 << "%" << endl;
}

void all_not_taken(string file_name){
  int correct = 0;
  int total = 0;
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  ifstream infile(file_name);
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    if(behavior == "NT"){
      correct++;
    }
    total++;
  }
  infile.close();
  cout << (double)correct / total * 100 << "%" << endl;
}

void bimodal_1bit(){

}

void bimodal_2bit(){

} 

void gshare(){

}

void tournament(){

}

void branch_target_buffer(){

}

int main(int argc, char *argv[]) {
  string name = "../project1/traces/short_trace1.txt";
  all_taken(name);
  all_not_taken(name);
  return 0;
}
