#include "matrix.hpp"


Matrix::Matrix(const int & x, const int & y){
	for(int i = 0; i < y; ++i){
		for(int j = 0; j < x; ++j){
			matrix().insert(std::make_pair(std::make_pair(j,i),0)); //2meta4u
		}
	}
	m_size = std::make_pair(x,y);
}
Matrix::Matrix(const std::pair<int,int> & nsize):m_size(nsize){
	for(int i = 0; i < size().second; ++i){
		for(int j = 0; j < size().first; ++j){
			matrix().insert(std::make_pair(std::make_pair(j,i),0)); //2meta4u
		}
	}
}

Matrix::Matrix(const std::vector<std::string> & input_line){
	m_size = std::make_pair(stoi(input_line[0]), stoi(input_line[1]));
	int n = 2;
	for(int y = 0; y < m_size.second;++y){
		for(int x = 0; x < m_size.first; ++x){
			double val = atof(input_line[n].c_str());
			matrix().insert(std::make_pair(std::make_pair(x,y),val));
			++n;
		}
	}
}


Matrix::~Matrix(){

}
Matrix Matrix::add(const Matrix & right){
	Matrix c(*this);
	if(size() != right.size()){ //Throw exeption
		std::string s = "In Matrix Matrix::add(const Matrix & right): attempting " + std::to_string( size().first) + "x" + std::to_string( size().second)
		+ " + " + std::to_string(right.size().first) + "x" + std::to_string( right.size().second);
		throw(std::out_of_range(s));
	}else{
		for(int i = 0; i < size().first ; ++i){
			for(int j = 0; j < size().second; ++j){
				c.access(i,j) += right.get(i,j);
			}
		}
	}
	return c;	
}
Matrix Matrix::sub(const Matrix & right ){
	Matrix c(*this);
	if(size()!= right.size()){ //Throw exep
		std::string s = "In Matrix Matrix::sub(const Matrix & right ): attempting " + std::to_string( size().first) + "x" + std::to_string( size().second)
		+ " - " + std::to_string(right.size().first) + "x" + std::to_string( right.size().second);
		throw(std::out_of_range(s));
	}else{
		for(int i = 0; i < size().first ; ++i){
			for(int j = 0; j < size().second; ++j){
				c.access(i,j) -= right.get(i,j);
			}
		}
	}
	return c;
}

Matrix Matrix::scale(const Matrix& right){
	Matrix c(*this);
	if(size()!= right.size()){ //Throw exep
		std::string s = "In Matrix Matrix::scale(const Matrix& right): attempting " + std::to_string( size().first) + "x" + std::to_string( size().second)
		+ " scaled with " + std::to_string(right.size().first) + "x" + std::to_string( right.size().second);
		throw(std::out_of_range(s));
	}else{
		for(int i = 0; i < size().first ; ++i){
			for(int j = 0; j < size().second; ++j){
				c.access(i,j) *= right.get(i,j);
			}
		}
	}
	return c;
}

Matrix Matrix::scale(const int & n){
	Matrix c(*this);
	for(int i = 0; i < size().first ; ++i){
		for(int j = 0; j < size().second; ++j){
			c.access(i,j) *=n;
		}
	}
	return c;
}

Matrix Matrix::dot(const Matrix & right){
	Matrix c(size().first, right.size().second);
	if(right.size().first != size().second){ //Throw exeption
		std::string s = "In Matrix Matrix::dot(const Matrix & right): attempting " + std::to_string( size().first) + "x" + std::to_string( size().second)
		+ " (dot) " + std::to_string(right.size().first) + "x" + std::to_string( right.size().second);
		throw(std::out_of_range(s));
	}else{
		int sum;
		for(int i = 0; i < size().first; ++i){
			for(int j = 0; j < right.size().second; ++j){
				sum = 0;
				for(int k = 0; k < right.size().first; ++k){
					sum += get(i,j)*right.get(k,j);
				}
				c.access(i,j) = sum;
			}
		}
	}
	return c;
}

double & Matrix::access(const int & x, const int & y){
	return matrix()[std::make_pair(x,y)];
}

void Matrix::set(const int &x, const int& y, const double & val){
	matrix()[std::make_pair(x,y)] = val;
}
double Matrix::get(const int&x, const int& y)const{
	std::pair<int,int> k = std::make_pair(x,y);
	return m_matrix.at(k);
}
Matrix & Matrix::cross(const Matrix &){
	return *this;
}


const std::pair<int,int> & Matrix::size()const{
	return m_size;
}

std::map<std::pair<int,int>, double> & Matrix::matrix(){
	return m_matrix;
}

const std::map<std::pair<int,int>, double> & Matrix::matrix()const{
	return m_matrix;
}

void Matrix::transpose(){
	std::map<std::pair<int,int>, double> new_matrix;
	for(int y = 0; y < size().second;++y){
		for(int x = 0; x < size().first; ++x){
			new_matrix[std::make_pair(y,x)] = matrix()[std::make_pair(x,y)];
		}
	}
	matrix() = new_matrix;
	m_size = std::make_pair(size().second, size().first);
}

void Matrix::print(){
	std::string s;
	for(int i = 0; i < size().second; ++i){
		s = "|";
		for(int j = 0; j < size().first; ++j){
			std::string tmp = std::to_string(get(j,i));
			if(tmp.length() == 1) tmp += "  ";
			s += tmp[0];
			s += tmp[1];
			s += tmp[2];
			s += " | ";
		}
		std::cout << s;
		std::cout << std::endl;
	}
}