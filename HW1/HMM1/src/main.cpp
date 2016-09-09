#include <iostream>
#include <string>
#include <vector>
#include "matrix.hpp"
/*
Martin Favre
Gabriel Andersson Santiago
*/

void read_matrix_from_cin(std::vector<std::vector<std::string>> *matrix){
	//Read input matrices
	std::string input_line;
	int run = 0;
	while(getline(std::cin, input_line)){
		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		while ((pos = input_line.find(delimiter)) != std::string::npos) {
			token = input_line.substr(0, pos);
			(*matrix)[run].push_back(token);
			input_line.erase(0, pos + delimiter.length());
		}
		token = input_line.substr(0, pos);
		(*matrix)[run].push_back(token);
		input_line.erase(0, pos + delimiter.length());
		++run;
	}	
}


int main(){
	std::vector<std::vector<std::string>> matrices(3);
	read_matrix_from_cin(&matrices);
	Matrix A(matrices[0]);
	Matrix B(matrices[1]);
	Matrix PI(matrices[2]);

	//PI*A*B
	Matrix C = PI.mult(A);
	C = C.mult(B);
	C.get_str();
}