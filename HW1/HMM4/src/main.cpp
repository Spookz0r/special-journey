#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
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
std::vector<std::vector<std::vector<double>>> digammas;





int main(){

	int iters = 0;
	int maxIters = 100;
	double oldLogProb = -std::numeric_limits<double>::max();
	//std::cout << oldLogProb << std::endl;
	std::vector<std::vector<std::string>> matrices(4);
	read_matrix_from_cin(&matrices);
	Matrix A(matrices[0]);
	Matrix B(matrices[1]);
	Matrix PI(matrices[2]);
	std::vector<std::string> sequence = matrices[3];
	std::vector<int> O;
	std::vector<std::vector<double>> alphas;

	for(unsigned int i = 1; i < sequence.size()-1; ++i){
		O.push_back(atoi(sequence[i].c_str()));
	}
	/*
	std::cout << "A" << std::endl;
	A.print();
	std::cout << "B" << std::endl;
	B.print();
	std::cout << "PI" << std::endl;
	PI.print();
	*/
	int N = A.rows();
	int T = O.size();
	// forward algorithm
	alphas.resize(O.size()); //There is one alpha for each emission/timestep
	alphas[0].resize(N);
	betas.resize(T);
	gammas.resize(T);
	gammas[T-1].resize(N);
	digammas.resize(T);
	digammas[T-1].resize(N);
	std::vector<double> c;
	c.resize(O.size());

	//############ Alpha Pass 

	//Compute the alpha 0
	while(true){

		c[0] = 0;
		for(int i = 0; i < N; ++i){
			//std::cout << "PI: " << PI.get(0,i) << " B: " << B.get(i, O[0]) << std::endl;
			alphas[0][i] = PI.get(0,i)*B.get(i,O[0]); //PI is row vector
			c[0] += alphas[0][i];
		}
		//std::cout << "1" << std::endl;
		//Scale the alpha 0
		c[0] = 1/c[0];
		for(int i = 0; i < N; ++i){
			alphas[0][i] = c[0]*alphas[0][i];
		}
		
		//std::cout << "2" << std::endl;
		//Compute alpha t
		for(int t = 1; t < T; ++t){
			c[t] = 0; //Init c_t
			alphas[t].resize(N);
			for(int i = 0; i < N; ++i){
				alphas[t][i] = 0;
				for(int j = 0; j < N; ++j){
					alphas[t][i] = alphas[t][i] + alphas[t-1][j]*A.get(j,i);
				}
				alphas[t][i] = alphas[t][i]*B.get(i,O[t]);
				c[t] += alphas[t][i];
			}
			//Scale alpha 
			c[t] = 1/c[t];
			for(int i = 0; i < N; ++i){
				alphas[t][i] = c[t]*alphas[t][i];
			}
		}

		//std::cout << "3" << std::endl;
	//############ Beta pass

	//Scale b_T-1 by C_T-1
		betas[T-1].resize(N);
		for(int i = 0; i < N; ++i){
			betas[T-1][i] = c[T-1];
		}

	//Beta pass
		//std::cout << "4" << std::endl;
		for(int t = T-2; t >= 0; --t){
			betas[t].resize(N);
			for(int i = 0; i < N; ++i){
				betas[t][i] = 0;
				for(int j = 0; j < N; ++j){
					betas[t][i] = betas[t][i] + A.get(i,j)*B.get(j, O[t+1])*betas[t+1][j];
				}
			//Scale Beta_t_i with same scale fac as alpha_t_i
				betas[t][i] = c[t]*betas[t][i];
			}
		}
		//std::cout << "5" << std::endl;
	//######### Gamma och Di-gamma
		for(int t = 0; t < T-1; ++t){
			double denom = 0;
			for(int i = 0; i < N; ++i){
				for(int j = 0; j < N; ++j){
					denom = denom + alphas[t][i] * A.get(i,j) * B.get(j,O[t+1]) * betas[t+1][j];
				}
			}
			gammas[t].resize(N);
			digammas[t].resize(N);
			for(int i = 0; i < N; ++i){
				digammas[t][i].resize(N);
				gammas[t][i] = 0;
				for(int j = 0; j < N; ++j){
					digammas[t][i][j] = (alphas[t][i]*A.get(i,j)*B.get(j, O[t+1])*betas[t+1][j])/denom;
					gammas[t][i] = gammas[t][i] + digammas[t][i][j];
				}
			}
		}


		//std::cout << "6" << std::endl;
	//Special case for gamma_t-1_i
		double denom = 0;
		for(int i = 0; i < N; ++i){
			denom += alphas[T-1][i];
		}
		for(int i = 0; i < N; ++i){
			gammas[T-1][i] = alphas[T-1][i]/denom;
		}

		//std::cout << "7" << std::endl;
	//Re-estimate A, B and pi
	//pi
		for(int i = 0; i < N; ++i){
			PI.access(0,i) = gammas[0][i];
		}

	//A
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){
				double numer = 0;
				double denom = 0;
				for(int t = 0; t < T-1; ++t){
					numer += digammas[t][i][j];
					denom += gammas[t][i];
				}
				A.access(i,j) = numer/denom;
			}
		}
	//B
		int M = B.columns();
		for(int i = 0; i < N; ++i){
			for (int j = 0; j < M; ++j){
				double numer = 0;
				double denom = 0;
				for(int t = 0; t < T; ++t){
					if(O[t] == j){
						numer += gammas[t][i];
					}
					denom += gammas[t][i];
				}
				B.access(i,j) = numer/denom;
			}
		}
		//std::cout << "8" << std::endl;

	//Compute log(P(O|lambda))

		double logProb = 0;
		for(int i = 0; i < T; ++i){
			logProb += log(c[i]);
		}
		logProb = -logProb;
		/*
		std::cout << std::endl;
		std::cout << "Iteration: " << iters << std::endl;
		std::cout << std::endl;
		std::cout << "logProb " << logProb << std::endl;
		std::cout << "A" <<std::endl;
		A.get_str();
		std::cout << "B" <<std::endl;
		B.get_str();
		std::cout << std::endl;
		*/
		++iters;
		if(iters > maxIters || logProb < oldLogProb){
			//std::cout << std::endl;
			//std::cout << "Done" << std::endl;
			A.get_str();
			std::cout << std::endl;
			B.get_str();
			std::cout << std::endl;
			break;
		}else{
			oldLogProb = logProb;
		}
	}

}