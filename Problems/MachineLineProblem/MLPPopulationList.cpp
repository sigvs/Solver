#include "MLPPopulationList.h"
#include <iomanip>
//************************************************************************************************/
void MLPPopulationList::GetMemory()
{
	for (int i = 0; i < _PopulationSize; i++)
	{
		MLPSolution* ns = new MLPSolution();
		_Individ.push_back(ns);
	}
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , MLPPopulationList& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(MLPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , MLPPopulationList& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(MLPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
