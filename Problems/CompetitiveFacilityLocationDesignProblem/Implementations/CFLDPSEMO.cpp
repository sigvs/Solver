
#include <iomanip>
#include "../CFLDProblem.h"
#include "../../../Algoithms/Evolutional/RandomSelection.h"
#include "../../../Algoithms/SEMO/IncreasePopulationIfNotWorse.h"
#include "../../../Algoithms/Common/IterationTerminator.h"
#include "../CFLDPPopulationList.h"
#include "../CFLDPRandomOpenRandom.h"
#include "../CFLDPMutation.h"
#include "../../../Algoithms/Common/TimeTerminator.h"
using namespace std;

inline int cfldpSEMO(int argc, char* argv[])
{
	srand(time(0));

	string filename = "data.60.3_1.txt";
	int mut_var = 5;
	int mut_dev = 5;
	string term_type = "i";
	int term_val = 1000;

	if (argc > 5)
	{
		filename = argv[1];
		mut_var = atoi(argv[2]);
		mut_dev = atoi(argv[3]);
		term_type = (string)argv[4];
		term_val = atoi(argv[5]);
	}


	ifstream in;
	in.open(filename, ifstream::in);

	CFLDProblem z;

	z.read_problem(in);

	in.close();


	CFLDPPopulationList parents;
	parents.SetPopulationSize(1);
	parents.Generate(&z);


	CFLDPPopulationList child;
	child.SetPopulationSize(1);

	RandomSelection sel;

	CFLDPMutation mut;
	mut.SetVariantParametr(mut_var);
	mut.SetDeviationDemandMutationParametr(mut_dev);

	IncreasePopulationIfNotWorse add;

	ISolver* terminator = NULL;
	if (term_type == "i")
	{
		IterationTerminator ter;
		ter.SetIterationNumber(term_val);
		terminator = &ter;
	}
	if (term_type == "t")
	{
		TimeTerminator ter;
		ter.SetTime_sec(term_val);
		terminator = &ter;
	}

	EvolutionalAlgorithm alg;
	alg.pParents = &parents;
	alg.pChildren = &child;
	alg.pSelection = &sel;
	alg.pMutation = &mut;
	alg.pAdder = &add;
	alg.pTerminator = terminator;
	alg.eSolve(&z);

	ofstream myfile;
	myfile.open (filename +".csv");

	myfile << "r;";
	myfile << "W;";
	for (int j = 0; j < z.getN(); j++)
		myfile << "v_" << j << ';';
	for (int j = 0; j < z.getN(); j++)
		myfile << "g_" << j << ';';

	myfile << endl;

	for(int i = 0; i<parents.GetPopulationSize(); i++)
		myfile << *((CFLDPSolution*)parents.pGetIndividPoint(i)) << endl;

	myfile.close();
	return 0;
}
