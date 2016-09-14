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
	for(unsigned int i = 1; i < sequence.size(); ++i){
			
			if(sequence[i] != "" ){
			O.push_back(atoi(sequence[i].c_str()));
			//std::cout << "element: " << i << " value: " << sequence[i] << "\n" ;
		}
	}
	Matrix Deltas(A.rows(),O.size());
	Matrix DeltaIndex(A.rows(),O.size());

	// Matrices for storing
	// computation 
	//Step 1: initialize delta1(i)

	// pi * O(sequence_1)
	int temp_state = 0;
	double max_tmp = 0;
	std::vector<int> states;

	for(int i = 0; i < PI.columns(); ++i){
		PI.access(0,i)*=B.get(i,O[0]);
		if(PI.access(0,i) > max_tmp){
			max_tmp = PI.get(0,i);
			temp_state = i;
		}
	}
	states.push_back(temp_state);
	Matrix temp_PI = PI;
	//PI.print();

	// To get the first state, find the which element has max value in PI.
	
	// step 2: Loop through the sequence, take out max of each and save argmax state
	// rows cloumns
	// max of deltai-1(i)*A[j][i]*B[i][O[k]]

	int k  = 0;
	double max_max_tmp = 0;
	for(unsigned int L = 1; L < O.size(); ++L)
	{
		//std::cout << "L: " << L << " k: " << O[L] << std::endl;
		k = O[L];
		max_max_tmp = 0;
		//std::cout << "Time: " << L << std::endl;
		for(int i = 0; i < A.rows(); ++i){
			max_tmp=0;

			//std::cout << "\nNext row: \n\n";
			for(int j = 0; j < A.columns(); ++j){
				double val = PI.get(0,j)*A.get(i,j)*B.get(i,k);
				//std::cout << PI.get(0,j) << " * " << A.get(j,i) << " * " << B.get(i,k) << " = " << val <<std::endl;
				//std::cout << "val: " << val << " max_tmp: " << max_tmp << std::endl;
				if(val > max_tmp){
					max_tmp = val;
					if(max_tmp > max_max_tmp)
					{
						temp_state = i;
						max_max_tmp = max_tmp;
					}
					//temp_state = i;
					//std::cout << i << std::endl;
				}
			}
			
			temp_PI.access(0,i) = max_tmp;
			//std::cout << "tempstate: " << temp_state << std::endl;
		}

		states.push_back(temp_state);
		PI = temp_PI;
		//PI.print();
		
	}

	for(auto i: states){
		std::cout << i << " ";
	}




}