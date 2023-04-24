#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "defs.h"

class CFLDProblem
{
private:
	int 			N;		// number of demand points
	int 			B;		// the total budget available
	double 			beta;	// the distance sensitivity parameter, beta > 0
	double 			lambda;	// the elasticity parameter, lambda > 0
	int				S;		// set of facilities controlled by the decision maker
	iVector 		omega;	// the demand weight of point i
	dVector			UC;		// the total utility for the customers in market i from the facilities controlled by the competitors
	dMatrix 		dist;	// distance matrix
	ddMatrix 		K;	// N x N
	dMatrix 		attr;// attractiveness
	iVector			initial_r;
	iVector			is_mine;
	iVector			index;	// original index
	bool 			verbose = true;
	int 			R = 3;
	iVector			upper_bound_fv;
	double 			upper_bound_obj;
	double			greedy_obj;
	iVector			greedy_fv;
	std::string		filename;
public:
	CFLDProblem(std::istream& in, std::string file);
	CFLDProblem();
	CFLDProblem(const CFLDProblem &CFLDProblem);
	CFLDProblem & operator=(const CFLDProblem &CFLDProblem);
	friend bool operator==(const CFLDProblem &CFLDProblem1, const CFLDProblem &CFLDProblem2);
	~CFLDProblem();
	void print_problem();
	double objective_function(const iVector& fv);
	//fv_obj upper_bound_calculate(iMatrix &x_constrain);
	void greedy();
	double getGreedyObj();
	iVector getGreedyFv();
	iVector getIndex();
	std::string getFileName();
	int getB();
	int getN();
	int getS();
};