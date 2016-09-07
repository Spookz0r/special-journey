#pragma once
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdexcept>
#include <exception>

/*
https://en.wikipedia.org/wiki/Kahan_summation_algorithm
https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
*/
class Matrix{
public:
	Matrix(const int&r, const int&c);
	Matrix(const std::vector<std::string>&);
	~Matrix();
	double & access(const int &, const int &);
	void set(const int &x, const int& y, const double & val);
	double get(const int&x, const int& y)const;
	Matrix & cross(const Matrix &);
	Matrix add(const Matrix &);
	Matrix sub(const Matrix &);
	Matrix scale(const Matrix&);
	Matrix scale(const int&);
	Matrix mult(const Matrix &); 
	int rows();
	int rows()const;
	int columns();
	int columns()const;
	void transpose();
	void print(); 
	std::map<std::pair<int,int>, double> & matrix();
	const std::map<std::pair<int,int>, double> & matrix()const;
	const std::pair<int,int> & size()const;
private:	
	std::map<std::pair<int,int>, double> m_matrix;
	std::pair<int,int> m_size;
};	