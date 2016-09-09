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
	std::vector<std::vector<std::string>> matrices(4);
	read_matrix_from_cin(&matrices);
	Matrix A(matrices[0]);
	Matrix B(matrices[1]);
	Matrix PI(matrices[2]);
	std::vector<std::string> sequence = matrices[3];
	std::vector<int> O;
	for(unsigned int i = 1; i < sequence.size()-1; ++i){
		O.push_back(atoi(sequence[i].c_str()));
	}

	Matrix tmp_vec(A.rows(), 1);
	tmp_vec.transpose();
	//PI.print();
	for(int i = 0; i < PI.columns(); ++i){
		PI.access(0,i)*= B.get(i,O[0]);
	}
	//PI.print();
	int k;
	for(int L = 1; L < O.size(); ++L)
	{
		k = O[L];
		//std::cout << "K: " << k << std::endl;
		//std::cout << "########################" << std::endl;
		for(int i = 0; i < A.rows(); ++i){
			double tmp = 0;
			//std::cout << "-------------" << std::endl;
			for(int j = 0; j < A.columns(); ++j){
				//std::cout << "A: " << PI.get(0,j) << std::endl;
				double val = PI.get(0,j)*A.get(j,i);
				tmp += val;
			}
			tmp_vec.access(0,i) = tmp;
		}
		for(int i = 0; i < tmp_vec.columns(); ++i){
			//std::cout << "B: " << B.get(i,k) << std::endl;
			tmp_vec.access(0,i)*= B.get(i,k);
		}
		PI = tmp_vec;
	}
	double result = 0;
	for(int i = 0; i < PI.columns(); ++i){
		result +=PI.get(0,i);
		//std::cout << PI.get(0,i) << std::endl;
		//std::cout << result << std::endl;
	}
	std::cout << result << std::endl;
	//PI*A*B

}