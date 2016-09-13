#include <iostream>
#include <string>
#include <vector>
#include "matrix.hpp"
/*
Martin Favre
Gabriel Andersson Santiago
*/

void backward();
void forward();
void update();

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

std::vector<std::vector<double>> alphas;
std::vector<std::vector<double>> betas;
std::vector<std::vector<double>> gammas;


void backwards(){

}

void forward(){

}

void update(){

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
	std::cout << "A" << std::endl;
	A.print();
	std::cout << "B" << std::endl;
	B.print();
	std::cout << "PI" << std::endl;
	PI.print();

	// forward algorithm
	alphas.resize(O.size()); //There is one alpha for each emission/timestep
	/*
	initiate the first set of alphas. alpha_1(i) = pi_i*b_i(O_1). 
	b_i(O_1) = iterate through row in B that corresponds to the first emission. 
	Amount if iterations is equal to rows in B
	*/
	//Step 1
	for(int i = 0; i < B.rows(); ++i){
		alphas[0].push_back(PI.get(0,i)*B.get(i,O[0])); //PI is row vector
	}

	//Step 2
	for(int i = 1; i < O.size(); ++i){
		for(int j = 0; j < A.rows(); ++j){
			double a_val = 0;
			for(int k = 0; k < A.columns(); ++k){
				a_val += PI.get(0,k)*A.get(k,j);
				
			}
			double b_val = B.get(j,O[i]); 
			alphas[i].push_back(a_val*b_val);
		}
	}

	std::vector<double> super_alpha;
	super_alpha.resize(alphas[0].size());

	for(int i = 0 ; i < alphas.size(); ++i){
		for(int j = 0; j < alphas[i].size(); ++j){
			super_alpha[j] += alphas[i][j];
		}
	}
	for(auto i = super_alpha.begin(); i != super_alpha.end(); ++i){
		std::cout << *i << std::endl;
	}
}