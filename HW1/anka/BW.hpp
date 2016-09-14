#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include "matrix.hpp"
#include "Player.hpp"
/*
Martin Favre
Gabriel Andersson Santiago
*/
void backward();
void forward();
void update();

void read_matrix_from_cin(std::vector<std::vector<std::string>> *matrix);

double BW(std::vector<std::vector<double>> &,std::vector<std::vector<double>> &,std::vector<std::vector<double>> &,std::vector<int>&);
