#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "CFLDProblem.h"
#include "defs.h"
//#include "gurobi_c++.h"
using namespace std;

CFLDProblem::CFLDProblem(std::istream& in, std::string file){
	filename = file;
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

	for(int i = 0; i < N; ++i){
		if(is_mine[i] == 1){
			index.push_back(i);
		}
	}
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

/*
fv_obj CFLDProblem::upper_bound_calculate(iMatrix &x_constrain) {
	fv_obj ub;
	GRBEnv* env = 0;
	env = new GRBEnv();
	//env.start();
	GRBModel model = GRBModel(*env);
	GRBVar* x_i = 0;
	x_i = model.addVars(N, GRB_CONTINUOUS);
	GRBVar** x = 0;

	x = new GRBVar* [S];

	for (int ss = 0; ss < S; ++ss){
		x[ss] = model.addVars(R, GRB_BINARY);
	}

	GRBVar ***z = new GRBVar** [N];

	for (int nn = 0; nn < N; ++nn){
		z[nn] = new GRBVar* [S];
		for (int ss = 0; ss < S; ++ss){
			z[nn][ss] = model.addVars(R, GRB_CONTINUOUS);
		}
		
	}

	double m_p = 0.0;

	model.set(GRB_IntParam_Threads, 1);
	model.set(GRB_IntParam_LogToConsole, 0);
	model.set(GRB_StringParam_LogFile, filename + "_GurobiLog.txt");
	try {
		for (int nn = 0; nn < N; ++nn){
			for (int ss = 0; ss < S; ++ss){
				for (int rr = 0; rr < R; ++rr){
					if (omega[nn] * K[nn][index[ss]][rr] / UC[nn] > m_p){
						m_p = omega[nn] * K[nn][index[ss]][rr] / UC[nn];
					}
				}
			}
		}

		for (int nn = 0; nn < N; ++nn) {
			for (int ss = 0; ss < S; ++ss) {
				for (int rr = 0; rr < R; ++rr) {
					model.addConstr(z[nn][ss][rr] <= K[nn][index[ss]][rr] * x_i[nn]);
				}
			}
		}

		for (int nn = 0; nn < N; ++nn) {
			for (int ss = 0; ss < S; ++ss) {
				for (int rr = 0; rr < R; ++rr) {
					model.addConstr(K[nn][index[ss]][rr] * x_i[nn] + m_p * (x[ss][rr] - 1) <= z[nn][ss][rr]);
				}
			}
		}

		for (int nn = 0; nn < N; ++nn) {
			for (int ss = 0; ss < S; ++ss) {
				for (int rr = 0; rr < R; ++rr) {
					model.addConstr(z[nn][ss][rr] <= x[ss][rr] * omega[nn]);
				}
			}
		}

		GRBLinExpr budget = 0;
		for (int ss = 0; ss < S; ++ss) {
			for (int rr = 0; rr < R; ++rr) {
				budget += x[ss][rr] * (rr + 1);
			}
		}
		model.addConstr(budget <= B);
		
		for (int nn = 0; nn < N; ++nn) {
			GRBLinExpr zz = 0;
			for (int ss = 0; ss < S; ++ss) {
				for (int rr = 0; rr < R; ++rr) {
					zz += z[nn][ss][rr];
				}
			}
			model.addConstr(zz + x_i[nn] * UC[nn] == omega[nn]);
		}

		if (x_constrain.size() > 0){
			for (int i = 0; i < x_constrain.size(); ++i){
				if (x_constrain[i][1] > 0){
					model.addConstr(x[x_constrain[i][0]][x_constrain[i][1] - 1] == 1);
				}
				else{
					for (int r = 0; r < R; ++r){
						model.addConstr(x[x_constrain[i][0]][r] == 0);
					}
				}
			}
		}

		GRBLinExpr obj = 0;
		for (int nn = 0; nn < N; ++nn) {
			for (int ss = 0; ss < S; ++ss) {
				for (int rr = 0; rr < R; ++rr) {
					obj += z[nn][ss][rr];
				}
			}
		}

		model.setObjective(obj, GRB_MAXIMIZE);
		model.optimize();

		upper_bound_obj = model.get(GRB_DoubleAttr_ObjVal);
		double runtime_upper_bound = model.get(GRB_DoubleAttr_Runtime);

		iVector fv;
		fv.resize(S);
		for (int j = 0; j < S; ++j){
			fv[j] = 0;
		}

		for (int ss = 0; ss < S; ++ss){
			for (int rr = 0; rr < R; ++rr)
				if (x[ss][rr].get(GRB_DoubleAttr_X) == 1){
					fv[ss] = rr + 1;
					//cout << ss << ":" << rr << endl;
				}
		}

		//cout << fv << endl;
		//std::pair <iVector,double> ub(fv, upper_bound_obj);
		ub.first = fv;
		ub.second = upper_bound_obj;
		//cout << fv << endl;
		//посчитать целевую функцию на исходной задачи
		// iVector fv;
		// fv.resize(S);

		// for (int j = 0; j < S; ++j){
		// 	fv[j] = 0;
		// }

		// if (x_constrain.size() > 0){
		// 	for (int i = 0; i < x_constrain.size(); ++i){
		// 		if (x_constrain[i][1] > 0){
		// 			fv[i] = x_constrain[i][1];
		// 		}
		// 	}
		// }

		// double of_fv = 0.0;
		//of_fv = objective_function(fv);
		// ofstream uplog("UpperBoundLog.txt", ios_base::app);
		// uplog << "File: " << filename << endl;
		// uplog << "Objective Function UB: " << setprecision(8) << upper_bound_obj << endl;
		// uplog << "Objective Function: " << setprecision(8) << of_fv << endl;
		// uplog << "Time: " << setprecision(8) << runtime_upper_bound << endl;
		// uplog << "Constrains: " <<  endl;

		// if (x_constrain.size() > 0) {
		// 	for (int i = 0; i < x_constrain.size(); ++i) {
		// 		if (x_constrain[i][1] > 0) {
		// 			uplog << "X[" << index[x_constrain[i][0]] + 1 << ", " << x_constrain[i][1] << "] = 1" << endl;
		// 		}
		// 		else {
		// 			uplog << "X[" << index[x_constrain[i][0]] + 1 << ", ] = 0" << endl;
		// 		}
		// 	}
		// }
		// else {
		// 	uplog << "Set of x constrains is epmty." << endl;
		// }
		// uplog << "Vector solutions: " << endl;
		// for (int ss = 0; ss < S; ++ss){
		// 	for (int rr = 0; rr < R; ++rr){
		// 		if (x[ss][rr].get(GRB_DoubleAttr_X)){
		// 			uplog << "X[" << index[ss] + 1 << ", " << rr + 1 <<"] = 1" << endl;
		// 		}
		// 	}
		// }
		// uplog << "--------------------------------" << endl;

		// std::string strNode;
		// std::string strParenth;

		// if (x_constrain.size() > 0) {
		// 	for (int i = 0; i < x_constrain.size(); ++i) {
		// 		if (i == 0) {
		// 			strNode = "X[" + std::to_string(index[x_constrain[i][0]] + 1) + "] = " + std::to_string(x_constrain[i][1]);
		// 		}
		// 		else {
		// 			strNode = strNode + ",X[" + std::to_string(index[x_constrain[i][0]] + 1) + "] = " + std::to_string(x_constrain[i][1]);
		// 		}
				
		// 	}
		// }

		// if (x_constrain.size() == 1) {
		// 	for (int i = 0; i < x_constrain.size(); ++i) {
		// 		strParenth = "Root";
		// 	}
		// }
		// else if (x_constrain.size() == 0) {}
		// else {
		// 	for (int i = 0; i < x_constrain.size() - 1; ++i) {
		// 		if (i == 0) {
		// 			strParenth = "X[" + std::to_string(index[x_constrain[i][0]] + 1) + "] = " + std::to_string(x_constrain[i][1]);
		// 		}
		// 		else {
		// 			strParenth = strParenth + ",X[" + std::to_string(index[x_constrain[i][0]] + 1) + "] = " + std::to_string(x_constrain[i][1]);
		// 		}
		// 	}
		// }

		// //node - last constrain, parenth - previous constrain, ofUB, of  
		// ofstream treelog("UpperBoundTreeLog.txt", ios_base::app);
		// if (x_constrain.size() == 0) {
		// 	treelog << "Root;;" << upper_bound_obj << ";" << of_fv << endl;
		// }
		// else {
		// 	if (x_constrain.size() == 1){
		// 		treelog << strNode << ";" << strParenth <<";" << upper_bound_obj << ";" << of_fv << endl;
		// 	}
		// 	else {
		// 		treelog << strNode << ";" << strParenth << ";" << upper_bound_obj << ";" << of_fv << endl;
		// 	}
		// }
		// strNode.clear();
		// strParenth.clear();
	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
	}

	delete[] x_i;
	for (int nn = 0; nn < N; ++nn)
	{
		for (int ss = 0; ss < S; ++ss){
			delete[] z[nn][ss];
		}
		delete[] z[nn];
	}
	delete[] z;
	return ub;
}
*/
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
	greedyLog << "Time: " << difftime(start, end) << " sec" << std::endl;
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

