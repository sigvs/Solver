#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "defs.h"
#include "neighborhoods.h"
#include "util.h"
#include "VNS.h"
#include "LK.h"
#include "ExchangeOfVariants.h"


using std::cout;
using std::endl;


int 		N;		// number of demand points
int 		B;		// the total budget available
double 		beta;	// the distance sensitivity parameter, beta > 0
double 		lambda;	// the elasticity parameter, lambda > 0
int			S;		// set of facilities controlled by the decision maker
iVector 	omega;	// the demand weight of point i
dVector		UC;		// the total utility for the customers in market i from the facilities controlled by the competitors
dMatrix 	dist;	// distance matrix
dMatrix 	K[3];	// N x N
iVector 	attr[3];// attractiveness
iVector		initial_r;
iVector		is_mine;
iVector		index;	// original index


bool verbose = false;


void readParameters(std::istream& in)
{
	in >> N >> B >> beta >> lambda;
	if (verbose) {
		cout << "N =\t" << N << endl;
		cout << "B =\t" << B << endl;
		cout << "beta =\t" << beta << endl;
		cout << "lambda =" << lambda << endl;
	}
	omega.resize(N);
	UC.resize(N);
	attr[0].resize(N); attr[1].resize(N); attr[2].resize(N);
	initial_r.resize(N);
	is_mine.resize(N);
	for (int i = 0; i < N; ++i) {
		in >> omega[i];
	}
	if (verbose) {
		cout << "omega =\t" << omega << endl;
	}
	in >> S;
	if (verbose) {
		cout << "S =\t" << S << endl;
	}
	for (int i = 0; i < N; ++i) {
		in >> initial_r[i] >> is_mine[i];
	}
	if (verbose) {
		cout << "r =\t" << initial_r << endl;
		cout << "my =\t" << is_mine << endl;
		cout << "attr:" << endl;
	}
	for (int i = 0; i < N; ++i) {
		in >> attr[0][i] >> attr[1][i] >> attr[2][i];
		if (verbose) {
			cout << attr[0][i] << ' ' << attr[1][i] << ' ' << attr[2][i] << endl;
		}
	}
	dist.resize(N);
	if (verbose) {
		cout << "dist:" << endl;
	}
	for (int i = 0; i < N; ++i) {
		dist[i].resize(N);
		for (int j = 0; j < N; ++j) {
			in >> dist[i][j];
		}
		if (verbose) {
			cout << dist[i] << endl;
		}
	}
	for (int i = 0; i < N; ++i) {
		in >> UC[i];
	}
	if (verbose) {
		cout << "UC = " << UC << endl;
	}
}


void evalK()
{
	for (int r = 0; r < 3; ++r) {
		K[r].resize(N);
		for (int i = 0; i < N; ++i) {
			K[r][i].resize(N);
			for (int j = 0; j < N; ++j) {
				K[r][i][j] = attr[r][j] * pow(1 + dist[i][j], -beta);
			}
		}
	}
}


double objectiveFunction(const iVector& fv)
{
	double z = 0;
	for (int i = 0; i < N; ++i) {
		double s = 0;
		for (int j = 0; j < S; ++j) {
			if (fv[j]) {
				s += K[fv[j] - 1][i][index[j]];
			}
		}
		z += omega[i] * (1 - exp(-lambda * (s + UC[i]))) * (s / (s + UC[i]));
	}
	// cout << "z = " << z << endl;
	return z;
}


iVector normal(const iVector& fv)
{
	iVector v(N);
	for (int i = 0; i < N; ++i) {
		v[index[i]] = fv[i];
	}
	return v;
}


void setInitialDistribution(iVector& fv)
{
	int b = B, n = S;
	int k3 = std::min(b / 3, n);
	for (int i = 0; i < k3; ++i) {
		fv[i] = 3;
	}
	b -= 3 * k3;
	n -= k3;
	if (n <= 0) {
		return;
	}
	int k2 = std::min(b / 2, n);
	for (int i = 0; i < k2; ++i) {
		fv[k3 + i] = 2;
	}
	b -= 2 * k2;
	n -= k2;
	if (n <= 0) {
		return;
	}
	int k1 = std::min(b, n);
	for (int i = 0; i < k1; ++i) {
		fv[k3 + k2 + i] = 1;
	}
	n -= k1;
	if (n <= 0) {
		return;
	}
	for (int i = k1 + k2 + k3; i < S; ++i) {
		fv[i] = 0;
	}
}


int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cerr << "Error: missing input file\n";
		return 1;
	}
	std::ifstream in(argv[1]);
	if (in.fail()) {
		std::cerr << "Error: unable to open input file\n";
		return 1;
	}
	std::srand((unsigned)std::time(0));
	readParameters(in);
	evalK();
	index.resize(N);
	std::vector<iPair> t(N);
	for (int i = 0; i < N; ++i) {
		t[i].first = initial_r[i];
		t[i].second = i;
	}
	std::sort(t.begin(), t.end(), [] (const iPair& a, const iPair& b) {
		int i = a.second, j = b.second;
		return (is_mine[i] == is_mine[j]) ? (omega[i] > omega[j]) : (is_mine[i] > is_mine[j]);
	});
	iVector fv(N), opt(N);
	for (int i = 0; i < N; ++i) {
		index[i] = t[i].second;
	}
	setInitialDistribution(fv);
	// cout << "fv =\t" << std::setprecision(8) << fv << endl;
	// cout << "F =\t" << objectiveFunction(fv) << endl;
	auto start = Clock::now();
	CloseFirstOpenBest cfob(S);
	CloseRandomOpenBest crob(S);
	CloseRandomOpenRandom cror;
	//RandomShuffle rs(S);
	ExchangeOfVariants ev;

	VNS vnsLK;
	LinKernighan lk(cror, objectiveFunction, 9);

	vnsLK += cfob;
	vnsLK += crob;
	vnsLK += ev;
	vnsLK += cror;
	vnsLK += lk;

	iVector fvLK = fv, optLK(N);
	//double z = vns.findMaximum(objectiveFunction, crob, fv, S, opt);
	double zLK = vnsLK.findMaximum(objectiveFunction, lk, fvLK, S, optLK);
	auto end = Clock::now();
	// cout << "opt =\t" << fv << endl;
	//cout << std::setprecision(8) << z << endl;
	cout << argv[1] << endl;
	cout << std::setprecision(8) << zLK << endl;
	cout << "time: " << difftime(start, end) << " sec"<< endl;

	iVector res = normal(fvLK);

	std::ofstream ofs_total("obj.txt", std::ios_base::app);
	ofs_total << std::setprecision(8) << zLK << endl;
	std::ofstream ofs_accept("time.txt", std::ios_base::app);
	ofs_accept << difftime(start, end) << std::endl;

	std::ofstream vec("vector.txt", std::ios_base::app);
	vec << argv[1] << std::endl;
	for (int i = 0; i < res.size(); ++i){
		vec << "X[" << i + 1 << "] = " << res[i] << std::endl;
	}
	vec << "---------------------------" << std::endl;

	return 0;
}
