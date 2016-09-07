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
	std::cout << "A" << std::endl;
	A.print();
	std::cout << std::endl;
	Matrix B(matrices[1]);
	std::cout << "B" << std::endl;
	B.print();
	std::cout << std::endl;


	Matrix PI(matrices[2]);
	std::cout << "PI" << std::endl;
	PI.print();
	std::cout << std::endl;
	PI.transpose();

	std::cout << "A*A:" << std::endl;
	Matrix C = A.mult(A);
	C.print();
	std::cout << std::endl;
	std::cout << "A*B:" << std::endl;
	C = A.mult(B);
	C.print();
	std::cout << std::endl;

	std::cout << "A*PI':" << std::endl;
	C = A.mult(PI);
	C.print();
	std::cout << std::endl;

	std::cout << "A+A" << std::endl;
	C = A.add(A);
	C.print();
	std::cout << std::endl;

	std::cout << "PI'+PI'" << std::endl;
	C = PI.add(PI);
	C.print();
	std::cout << std::endl;

	/*
	*/
	std::cout << "Program end" << std::endl;
}