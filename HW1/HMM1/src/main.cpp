#include <iostream>
#include <string>
#include <vector>
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
		++run;
	}	

}
int main(){
	std::cout << "Program start" << std::endl;
	std::vector<std::vector<std::string>> matrices(3);
	read_matrix_from_cin(&matrices);
	std::cout << "read done" << std::endl;
	for(unsigned int i = 0; i < matrices.size(); ++i){
		for(unsigned int j = 0; j < matrices[i].size();++j){
			std::cout << matrices[i][j] << " ";
		}
		std::cout << std::endl;
	}	

	std::cout << "Program end" << std::endl;
}