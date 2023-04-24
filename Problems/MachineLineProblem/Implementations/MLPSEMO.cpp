
#include"..\MLPSolution.h"
#include"..\MLProblem.h"
#include <iomanip>
#include "../MLPPopulationList.h"
#include "../../../Algoithms/Evolutional/RandomSelection.h"
#include "../MLPDeltaPlusMutation.h"
#include "../../../Algoithms/SEMO/IncreasePopulationIfNotWorse.h"
#include "../../../Algoithms/Common/TimeTerminator.h"
#include "../../../Algoithms/Common/IterationTerminator.h"
using namespace std;

inline int mlpSEMO(int argc, char* argv[])
{
	srand(time(0));

	ifstream in;
	string filename = "ancelin1.prb";
	if (argc > 1)filename = argv[1];
	in.open(filename, ifstream::in);

	MLProblem z;
	in >> z;

	in.close();

	cout<<z;


	MLPPopulationList parents;
	parents.SetPopulationSize(1);
	parents.Generate(&z);


	MLPPopulationList child;
	child.SetPopulationSize(1);

	RandomSelection sel;

	MLPDeltaPlusMutation mut;
	mut.SetDeltaMutation(5);

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

	myfile <<  "Debit;AverageStock;BufferSumm;";
	for (int j = 0; j < z.GetSize(); j++)
		myfile << "Buffer_" << j << ';';
	myfile << endl;


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

	return 0;
}
