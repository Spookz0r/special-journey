#include <iostream>
#include <string>
#include <vector>
#include "matrix.hpp"
#include <algorithm>
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

	// read file
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


	// computation 
	//Step 1: initialize delta1(i)

	// pi * O(sequence_1)
	std::vector<int> states;

	for(int i = 0; i < PI.columns(); ++i){
		PI.access(0,i)*=B.get(i,O[0]);
	}
	Matrix temp_PI = PI;

	std::cout << "A" << std::endl;
	A.print();
	std::cout << "B" << std::endl;
	B.print();
	std::cout << "PI" << std::endl;
	PI.print();

	std::vector<std::vector<std::pair<double, int>>> the_fucking_deltas;
	for(unsigned int i = 1; i < O.size(); ++i){
		std::cout << std::endl << "for emission: "<< i << std::endl << std::endl;;
		std::vector<std::pair<double,int>> delta;
		for(int j = 0; j < A.rows(); ++j){
			std::pair<double, int> temp_max = {0,0};
			std::vector<double> row_values;
			for(int k = 0; k < temp_PI.columns(); ++k){
				row_values.push_back(temp_PI.get(0,k)*A.get(k,j)*B.get(j,O[i]));
				std::cout <<"PI " <<temp_PI.get(0,k) <<" *A " <<A.get(k,j) << " *B " << B.get(j,O[i])<< "=" <<row_values[k]<< std::endl;
				if(row_values[k] > temp_max.first){
					std::cout << "A new max is found: " << row_values[k] << " at " << j <<std::endl;
					temp_max = std::make_pair(row_values[k], j);
				}
			}
			std::cout << std::endl;
			delta.push_back(temp_max);
			//std::cout <<"Max is: "<< temp_max.first <<" at: " << temp_max.second << std::endl;
		}

		the_fucking_deltas.push_back(delta);
		for(int j = 0; j < temp_PI.columns(); ++j){
			//std::cout << "i " << i << " j " << j << " = " <<the_fucking_deltas[i-1][j].second << std::endl;
			temp_PI.access(0,j) = the_fucking_deltas[i-1][j].first;
		}

	}

	double max = 0;
	int choice = 0;
	std::vector<int> choices;
	for(int j = 0; j < PI.columns(); ++j){
		if(the_fucking_deltas[the_fucking_deltas.size()-1][j].first > max){
			max = the_fucking_deltas[the_fucking_deltas.size()-1][j].first;
			choice = j;
		}
	}

	choices.push_back(choice);

	for(int i = the_fucking_deltas.size()-2; i >= 0; --i){
		choices.push_back(the_fucking_deltas[i][choices.back()].second);
	}
	std::cout << the_fucking_deltas[the_fucking_deltas.size()-1][choice].second << " ";
	for(int i = choices.size()-1; i >= 0; --i){
		std::cout << choices[i] << " ";
	}
}