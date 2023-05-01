#include "CFLDPPopulationList.h"
#include <iomanip>
//************************************************************************************************/
void CFLDPPopulationList::GetMemory()
{
	for (int i = 0; i < _PopulationSize; i++)
	{
		CFLDPSolution* ns = new CFLDPSolution();
		_Individ.push_back(ns);
	}
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , CFLDPPopulationList& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(CFLDPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , CFLDPPopulationList& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(CFLDPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
