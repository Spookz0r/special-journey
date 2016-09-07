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
Matrix::~Matrix(){

}
Matrix Matrix::add(const Matrix & right){
	Matrix c(size());
	if(size() != right.size()){ //Throw exeption
		std::cout << "Waah" << std::endl;
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
	Matrix c(size());
	if(size()!= right.size()){ //Throw exep
		std::cout << "Waah" << std::endl;
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
	Matrix c(size());
	if(size()!= right.size()){ //Throw exep
		std::cout << "Waah" << std::endl;
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
	Matrix c(size());
	
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
		std::cout << "Waah" << std::endl;
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