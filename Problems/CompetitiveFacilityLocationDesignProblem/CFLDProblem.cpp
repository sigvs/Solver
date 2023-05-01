#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "CFLDProblem.h"
//#include "gurobi_c++.h"
using namespace std;

CFLDProblem::CFLDProblem(std::istream& in, std::string file){
	filename = file;
}

CFLDProblem::CFLDProblem(const CFLDProblem &CFLDProblem){
	filename = CFLDProblem.filename;
	N = CFLDProblem.N;
	B = CFLDProblem.B;
	beta = CFLDProblem.beta;
	lambda = CFLDProblem.lambda;

	omega.resize(N);
	UC.resize(N);
	attr.resize(N);
	initial_r.resize(N);
	is_mine.resize(N);
	for (int i = 0; i < N; ++i) {
		omega[i] = CFLDProblem.omega[i];
	}

	S = CFLDProblem.S;

	for (int i = 0; i < N; ++i) {
		initial_r[i] = CFLDProblem.initial_r[i];
		is_mine[i] = CFLDProblem.is_mine[i];
	}

	for (int i = 0; i < N; ++i) {
		attr[i].resize(R);
	}

	for (int i = 0; i < N; ++i) {
		attr[i][0] = CFLDProblem.attr[i][0];
		attr[i][1] = CFLDProblem.attr[i][1];
		attr[i][2] = CFLDProblem.attr[i][2];
	}
	dist.resize(N);

	for (int i = 0; i < N; ++i) {
		dist[i].resize(N);
		for (int j = 0; j < N; ++j) {
			dist[i][j] = CFLDProblem.dist[i][j];
		}
	}
	for (int i = 0; i < N; ++i) {
		UC[i] = CFLDProblem.UC[i];
	}

	//посчитаем коэффициент K
	K.resize(N);
	for (int i = 0; i < N; ++i) {
		K[i].resize(N);
		for (int j = 0; j < N; ++j) {
			K[i][j].resize(3);
			for (int r = 0; r < 3; ++r) {
				K[i][j][r] = attr[j][r] * pow(1 + dist[i][j], -beta);
			}
		}
	}

	for(int i = 0; i < N; ++i){
		if(is_mine[i] == 1){
			index.push_back(i);
		}
	}
}

CFLDProblem& CFLDProblem::operator=(const CFLDProblem &CFLDProblem){
	if (this == &CFLDProblem){
		return *this;
	}
	filename = CFLDProblem.filename;
	N = CFLDProblem.N;
	B = CFLDProblem.B;
	beta = CFLDProblem.beta;
	lambda = CFLDProblem.lambda;

	omega.resize(N);
	UC.resize(N);
	attr.resize(N);
	initial_r.resize(N);
	is_mine.resize(N);
	for (int i = 0; i < N; ++i) {
		omega[i] = CFLDProblem.omega[i];
	}

	S = CFLDProblem.S;

	for (int i = 0; i < N; ++i) {
		initial_r[i] = CFLDProblem.initial_r[i];
		is_mine[i] = CFLDProblem.is_mine[i];
	}

	for (int i = 0; i < N; ++i) {
		attr[i].resize(R);
	}

	for (int i = 0; i < N; ++i) {
		attr[i][0] = CFLDProblem.attr[i][0];
		attr[i][1] = CFLDProblem.attr[i][1];
		attr[i][2] = CFLDProblem.attr[i][2];
	}
	dist.resize(N);

	for (int i = 0; i < N; ++i) {
		dist[i].resize(N);
		for (int j = 0; j < N; ++j) {
			dist[i][j] = CFLDProblem.dist[i][j];
		}
	}
	for (int i = 0; i < N; ++i) {
		UC[i] = CFLDProblem.UC[i];
	}

	//посчитаем коэффициент K
	K.resize(N);
	for (int i = 0; i < N; ++i) {
		K[i].resize(N);
		for (int j = 0; j < N; ++j) {
			K[i][j].resize(3);
			for (int r = 0; r < 3; ++r) {
				K[i][j][r] = attr[j][r] * pow(1 + dist[i][j], -beta);
			}
		}
	}

	for(int i = 0; i < N; ++i){
		if(is_mine[i] == 1){
			index.push_back(i);
		}
	}
	return *this;
}

bool operator==(const CFLDProblem &CFLDProblem1, const CFLDProblem &CFLDProblem2){
	return CFLDProblem1.filename == CFLDProblem2.filename;
}

CFLDProblem::CFLDProblem(){

}

double CFLDProblem::getGreedyObj(){
	return greedy_obj;
}

iVector CFLDProblem::getGreedyFv(){
	return greedy_fv;
}

int CFLDProblem::getB(){
	return B;
}
int CFLDProblem::getN(){
	return N;
}

int CFLDProblem::getS(){
	return S;
}

SolverResult CFLDProblem::eSolve(void* x_, ...)
{
	/*
	void** hx = &x_;
	IVector* fv = (IVector*)(hx[0]);
	double* _CaptureShare = (double*)(hx[1]);

	_CaptureShare = objective_function(fv);
	*/
	return SolutionFound;
}

iVector CFLDProblem::getIndex(){
	return index;
}


void CFLDProblem::print_problem(){
	cout << "N =\t" << N << endl;
	cout << "B =\t" << B << endl;
	cout << "beta =\t" << beta << endl;
	cout << "lambda =" << lambda << endl;
	cout << "filename = " << filename << endl;
}

void CFLDProblem::read_problem(ifstream& in)
{
	in >> N >> B >> beta >> lambda;

	omega.resize(N);
	UC.resize(N);
	attr.resize(N);
	initial_r.resize(N);
	is_mine.resize(N);
	for (int i = 0; i < N; ++i) {
		in >> omega[i];
	}

	in >> S;

	for (int i = 0; i < N; ++i) {
		in >> initial_r[i] >> is_mine[i];
	}

	for (int i = 0; i < N; ++i) {
		attr[i].resize(R);
	}

	for (int i = 0; i < N; ++i) {
		in >> attr[i][0] >> attr[i][1] >> attr[i][2];
	}
	dist.resize(N);

	for (int i = 0; i < N; ++i) {
		dist[i].resize(N);
		for (int j = 0; j < N; ++j) {
			in >> dist[i][j];
		}
	}
	for (int i = 0; i < N; ++i) {
		in >> UC[i];
	}

	//посчитаем коэффициент K
	K.resize(N);
	for (int i = 0; i < N; ++i) {
		K[i].resize(N);
		for (int j = 0; j < N; ++j) {
			K[i][j].resize(3);
			for (int r = 0; r < 3; ++r) {
				K[i][j][r] = attr[j][r] * pow(1 + dist[i][j], -beta);
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		if (is_mine[i] == 1) {
			index.push_back(i);
		}
	}
}


double CFLDProblem::objective_function(const iVector& fv){
	double z = 0;
	for (int i = 0; i < N; ++i) {
		double s = 0;
		for (int j = 0; j < S; ++j) {
			if (fv[j]) {
				s += K[i][index[j]][fv[j] - 1];
			}
		}
		z += omega[i] * (1 - exp(-lambda * (s + UC[i]))) * (s / (s + UC[i]));
	}
	return z;
}

void CFLDProblem::greedy(){
	auto start = Clock::now();
	greedy_fv.resize(S);
	int b = B;
	while (b > 0){
		int index_delta_max = -1;
		double delta_max = 0;
		double curVal = 0;
		double tcurVal = 0;
		for (int i = 0; i < S; ++i){
			if (greedy_fv[i] < 3){
				greedy_fv[i] += 1;
				double delta = objective_function(greedy_fv);
				if ((delta - curVal) > delta_max){
					delta_max = delta - curVal;
					index_delta_max = i;
					tcurVal = delta;
				}
				greedy_fv[i] -= 1;
			}
		}
		if (index_delta_max != -1){
			greedy_fv[index_delta_max] += 1;
			curVal = tcurVal;
			b -= 1;
		}
	}
	greedy_obj = objective_function(greedy_fv);

	auto end = Clock::now();
	//char *cstr = &filename[0];
	//strcat_s(cstr, sizeof cstr, "_logGreedy.txt");
	std::string str = filename + "_logGreedy.txt";
	ofstream greedyLog(str, std::ios_base::app);
	greedyLog << "File: " << filename << std::endl;
	greedyLog << "Objective Function: " << std::setprecision(8) << greedy_obj << endl;
	//greedyLog << "Time: " << difftime(start, end) << " sec" << std::endl;
	greedyLog << "Vector solutions: " << std::endl;

	for (int i = 0; i < greedy_fv.size(); ++i) {
		if (greedy_fv[i]) {
			greedyLog << "X[" << index[i] + 1 << ", " << greedy_fv[i] << "] = 1" << std::endl;
		}
	}
	greedyLog << "---------------------------" << std::endl;
}

std::string CFLDProblem::getFileName(){
	return filename;
}

CFLDProblem::~CFLDProblem(){
	
}

//************************************************************************************************/
