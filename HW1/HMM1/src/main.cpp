#include <iostream>
#include <string>
#include <vector>
#include "matrix.hpp"
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
	std::cout << "Program start" << std::endl;
	std::vector<std::vector<std::string>> matrices(3);
	read_matrix_from_cin(&matrices);
	std::cout << "read done" << std::endl;
	Matrix A(matrices[0]);
	A.print();
	std::cout << std::endl;

	Matrix B(matrices[1]);
	B.print();
	std::cout << std::endl;

	Matrix C = A.dot(A);
	C.print();
	std::cout << std::endl;
	Matrix PI(matrices[2]);
	PI.print();
	std::cout << std::endl;

	PI.transpose();
	PI.print();
	std::cout << std::endl;

	A.transpose();
	A.print();

	std::cout << "Program end" << std::endl;
}