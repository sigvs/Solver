
#include <iomanip>
#include "../CFLDProblem.h"
#include "../../../Algoithms/Evolutional/RandomSelection.h"
#include "../../../Algoithms/SEMO/IncreasePopulationIfNotWorse.h"
#include "../../../Algoithms/Common/IterationTerminator.h"
#include "../CFLDPPopulationList.h"
#include "../CFLDPRandomOpenRandom.h"
#include "../CFLDPMutation.h"
using namespace std;

inline int cfldpSEMO(int argc, char* argv[])
{
	srand(time(0));

	ifstream in;
	string filename = "data.60.3_1.txt";
	if (argc > 1)filename = argv[1];
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
	mut.SetVariantParametr(5);
	mut.SetDeviationDemandMutationParametr(z.getN()/2);

	IncreasePopulationIfNotWorse add;

	//TimeTerminator ter;
	//ter.SetTime_sec(360);

	IterationTerminator ter;
	ter.SetIterationNumber(1000);


	EvolutionalAlgorithm alg;
	alg.pParents = &parents;
	alg.pChildren = &child;
	alg.pSelection = &sel;
	alg.pMutation = &mut;
	alg.pAdder = &add;
	alg.pTerminator = &ter;
	alg.eSolve(&z);

	ofstream myfile;
	myfile.open (filename +".result");

	myfile <<  "Debit;";
	for (int j = 0; j < z.getN(); j++)
		myfile << "Buffer_" << j << ';';
	for (int j = 0; j < z.getN(); j++)
		myfile << "Buffer_" << j << ';';

	myfile << endl;

/*
	for(int i = 0; i<parents.GetPopulationSize(); i++)
	{
		myfile<<((MLPSolution*) parents.pGetIndividPoint(i))->Debit()<<';';
		myfile<<((MLPSolution*) parents.pGetIndividPoint(i))->AverageStock()<<';';
		myfile<<((MLPSolution*) parents.pGetIndividPoint(i))->BufferSumm()<<';';
		for(int j = 0; j < ((MLPSolution*) parents.pGetIndividPoint(i))->GetBufferNumber(); j++)
			myfile<<((MLPSolution*) parents.pGetIndividPoint(i))->BufferSize(j)<<';';
		myfile<<endl;
	}

	myfile.close();
*/
	return 0;
}
