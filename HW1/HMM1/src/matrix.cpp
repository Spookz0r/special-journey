#include "matrix.hpp"


Matrix::Matrix(const int & r, const int & c){
	m_size = std::make_pair(r,c);
	for(int y = 0; y < columns(); ++y){
		for(int x = 0; x < rows(); ++x){
			matrix().insert(std::make_pair(std::make_pair(y,x),0)); //2meta4u
		}
	}
}

Matrix::Matrix(const std::vector<std::string> & input_line){
	m_size = std::make_pair(stoi(input_line[0]), stoi(input_line[1]));
	int n = 2;
	for(int y = 0; y < rows();++y){
		for(int x = 0; x < columns(); ++x){
			double val = atof(input_line[n].c_str());
			matrix().insert(std::make_pair(std::make_pair(y,x),val));
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
		for(int y = 0; y < rows() ; ++y){
			for(int x = 0; x < columns(); ++x){
				c.access(x,y) += right.get(x,y);
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
		for(int y = 0; y < rows() ; ++y){
			for(int x = 0; x < columns(); ++x){
				c.access(x,y) -= right.get(x,y);
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
		for(int y = 0; y < rows() ; ++y){
			for(int x = 0; x < columns(); ++x){
				c.access(x,y) *= right.get(x,y);
			}
		}
	}
	return c;
}

Matrix Matrix::scale(const int & n){
	Matrix c(*this);
	for(int y = 0; y < rows() ; ++y){
		for(int x = 0; x < columns(); ++x){
			c.access(x,y) *=n;
		}
	}
	return c;
}


/*
[ a*e + b*g, a*f + b*h]
[ c*e + d*g, c*f + d*h]
4x4 + 4x1 = 4x1

 */

Matrix Matrix::mult(const Matrix & right){
	//std::cout << "input is size " << right.rows() << "x" << right.columns() << std::endl;
	//std::cout << "my size is" << rows() << "x" << columns() << std::endl;
	Matrix c(rows(), right.columns());
	if(columns() != right.rows()){ //Throw exeption
		std::string s = "In Matrix Matrix::mult(const Matrix & right): attempting " + std::to_string( rows()) + "x" + std::to_string( columns())
		+ " (dot) " + std::to_string(right.rows()) + "x" + std::to_string( right.columns());
		throw(std::out_of_range(s));
	}else{
		double sum;
		for(int i = 0; i < rows(); ++i){
			for(int j = 0; j < right.columns(); ++j){
				sum = 0;
				for(int k = 0; k < right.rows(); ++k){
					//std::cout << "A: " << i << "x" << k << " B: " << k << "x" << j << std::endl;
					//std::cout << get(i,k) << "*" << right.get(k,j) << std::endl;
					sum += get(i,k)*right.get(k,j);
					//std::cout << get(i,k) << "*" << right.get(k,j) << "=" << sum << std::endl;
				}
				//std::cout << "endsum: " << sum << std::endl;
				//std::cout << "placing in" << i << "x" << j << std::endl;
				c.access(i,j) = sum;
			}
		}
	}
	return c;
}



double & Matrix::access(const int & r, const int & c){
	return matrix()[std::make_pair(r,c)];
}

void Matrix::set(const int &r, const int& c, const double & val){
	matrix()[std::make_pair(r,c)] = val;
}
double Matrix::get(const int&r, const int& c)const{
	std::pair<int,int> k = std::make_pair(r,c);
	return m_matrix.at(k);
}
Matrix & Matrix::cross(const Matrix &){
	return *this;
}

int Matrix::rows(){
	return size().first;
}

int Matrix::rows()const{
	return size().first;
}
int Matrix::columns(){
	return size().second;
}

int Matrix::columns()const{
	return size().second;
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
	for(int y = 0; y < columns();++y){
		for(int x = 0; x < rows(); ++x){
			new_matrix[std::make_pair(y,x)] = matrix()[std::make_pair(x,y)];
		}
	}
	matrix() = new_matrix;
	m_size = std::make_pair(columns(), rows());
}

void Matrix::print(){
	std::string s;
	for(int y = 0; y < rows(); ++y){
		s = "|";
		for(int x = 0; x < columns(); ++x){
			std::string tmp = std::to_string(get(y,x));
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