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
	
	// To get the first state, find the which element has max value in PI.
	
	// step 2: Loop through the sequence, take out max of each and save argmax state
	// rows cloumns
	// max of deltai-1(i)*A[j][i]*B[i][O[k]]

	int k  = 0;
	for(int L = 1; L < O.size(); ++L)
	{
		k = O[L];
		//std::cout << "Time: " << L << std::endl;
		for(int i = 0; i < A.rows(); ++i){
			max_tmp=0;

			
			for(int j = 0; j < A.columns(); ++j){
				double val = PI.get(0,j)*A.get(j,i)*B.get(i,k);
				if(val > max_tmp){
					max_tmp = val;
					temp_state = i;
					//std::cout << i << std::endl;
				}
			}
			
			temp_PI.access(0,i) = max_tmp;

		}

		states.push_back(temp_state);
		PI = temp_PI;
		//PI.print();
		
	}

	for(auto i: states){
  		std::cout << i << " ";
	}




	/*
	Matrix tmp_vec(A.rows(), 1);
	tmp_vec.transpose();
	
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
	*/

}