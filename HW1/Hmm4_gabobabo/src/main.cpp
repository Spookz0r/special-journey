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
	int T = sequence.size();
	int N = A.rows();
	int M = B.rows();



	//1: Initialize Gamma = (A,B,pi)


	std::vector<Matrix> digammas;
	std::vector<Matrix> alphas;
	std::vector<Matrix> betas;
	std::vector<Matrix> gammas;


	//2: Compute alpha_t(i), beta_t(i), gamma_t(i,j) and gamma_t(i)
	int k = 0;
	int iter = 0;
	while(iter < 1){
		++iter;

		//Alphas
		for(int i = 0; i < PI.columns(); ++i){
			PI.access(0,i)*= B.get(i,O[0]);
		}
		Matrix alpha = PI;
		alphas.push_back(alpha);
		PI.print();


		for(unsigned int i=1; i< O.size();++i){
			k = O[i];
			Matrix tmp_vec = PI;
			for(int q=0; q < A.rows();++q){
				for(int j=0;j < A.columns();++j){
					double temp_val = alpha.get(0,j)*A.get(j,q)*B.get(q,k);
					tmp_vec.access(q,j) = temp_val;
				}
			}
			alphas.push_back(tmp_vec);


		}

		//betas

		Matrix beta = PI;
		betas.push_back(beta);
		int k  = 0;
	double max_max_tmp = -1;
	double val = 0;
	for(unsigned int L = 1; L < O.size(); ++L)
	{
		k = O[L];
		max_max_tmp = -1;
		Matrix temp_PI(PI.rows(),PI.columns());
		for(int i = 0; i < A.columns(); ++i){
			for(int j = 0; j < A.rows(); ++j){
				val = PI.get(0,i)*A.get(i,j)*B.get(j,k);
				if(val > temp_PI.get(0,j)){

					temp_PI.access(0,j) = val;
					if(val > max_max_tmp)
					{
						max_max_tmp = val;
					}
				}
				
			}
		}
		betas.push_back(temp_PI);
		
	}

		//gamma(i,j)

	for(unsigned int t = 0; t< sequence.size()-3; ++t){
		k = O[t+1];
		Matrix di_gamma(A.rows(),A.columns());
		Matrix tmp_mat(digammas.size(),1);
		for(int i = 0; i < A.columns(); ++i){

			for(int j =0; j < A.rows(); ++j){
		//std::cout << t << " " << i << " " << j  << std::endl;

				
				di_gamma.access(i,j) = alphas[t].get(0,i)*A.get(i,j)*B.get(j,k)*betas[t+1].get(0,j);
			}
		}
		digammas.push_back(di_gamma);
		for(int i = 0; i < A.rows(); ++i){
				
				for(int j=0; j < A.columns(); ++j){
					tmp_mat.access(i,0) += digammas[t].get(i,j);
				}
			}
		gammas.push_back(tmp_mat);
	}
		//gamma(i)

		// for(unsigned int t = 0; t < digammas.size()-1;++t){
		// 		Matrix tmp_mat(digammas.size(),1);
		// 	for(int i = 0; i < A.rows(); ++i){
				
		// 		for(int j=0; j < A.columns(); ++j){
		// 			tmp_mat.access(i,0) += digammas[t].get(i,j);
		// 		}
		// 	}
		// 	gammas.push_back(tmp_mat);
		// }
	
	//3: Re-estimate the model gamma = (A,B,pi);
		//Re-estimate PI
		for(int i =0;i < PI.rows(); ++i){
			PI.access(0,i) = gammas[0].get(i,0);

		}
		//Re-estimate A
		for(int i = 0; i < A.rows(); ++i){
				for(int j = 0; j < A.columns(); ++j){

			double temp_sum_di_gamma= 0;
			double temp_sum_gamma= 0;
					for(unsigned int t = 0; t < digammas.size()-1;++t){

						//std::cout << t << " " << i << " " << j  << std::endl;
						temp_sum_di_gamma += digammas[t].get(i,j);
						temp_sum_gamma += gammas[t].get(j,0);
				}
					A.access(i,j) = temp_sum_di_gamma/temp_sum_gamma;
			}

		}

		//Re-estimate B

		for( int i = 0; i < B.rows(); ++i){

			for( int j = 0; j < B.rows(); ++j){
				double temp_gamma = 0;
				double temp_gamma2 = 0;
				for(unsigned int t = 0; t < digammas.size()-1;++t){
					if(O[t] == j){
						temp_gamma += gammas[t].get(j,0);
					}
					temp_gamma2 += gammas[t].get(j,0);
				}
				B.access(i,j) = temp_gamma/temp_gamma2;
			}
		}
			//4: If P(O|gamma) increases go to 2.

	//Might be desiarble to stop if P(O|gamma) does not increase by at least some 
	// predetermined threshold and/or to set a maximum number of iterations
	}
		A.get_str();
		std::cout << "\n\n";
		B.get_str();
}