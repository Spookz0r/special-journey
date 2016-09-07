#pragma once
#include <map>
#include <iostream>
class Matrix{
public:
	Matrix(const int&x, const int&y);
	Matrix(const std::pair<int,int> & );
	~Matrix();
	double & access(const int &, const int &);
	void set(const int &x, const int& y, const double & val);
	double get(const int&x, const int& y)const;
	Matrix & cross(const Matrix &);
	Matrix add(const Matrix &);
	Matrix sub(const Matrix &);
	Matrix scale(const Matrix&);
	Matrix scale(const int&);
	Matrix dot(const Matrix &);  
	std::map<std::pair<int,int>, double> & matrix();
	const std::map<std::pair<int,int>, double> & matrix()const;
	const std::pair<int,int> & size()const;
private:
	std::map<std::pair<int,int>, double> m_matrix;
	std::pair<int,int> m_size;
};	