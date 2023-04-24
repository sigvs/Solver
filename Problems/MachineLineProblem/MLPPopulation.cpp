#include "MLPPopulation.h"
#include <iomanip>
//************************************************************************************************/
  MLPPopulation::MLPPopulation()
 {
	  _PopulationSize =0;
 };
//************************************************************************************************/
  MLPPopulation::MLPPopulation(const MLPPopulation& x)
 {
	  _PopulationSize =0;
    *this = x;
 };
//************************************************************************************************/
void  MLPPopulation::operator = (const MLPPopulation& x)
{
    Population::operator = (x);
    if(_PopulationSize !=x._PopulationSize)
		SetPopulationSize(x._PopulationSize);
    for(int i=0;i<_PopulationSize;i++)
		pGetIndividPoint(i)->Copy(&x._Individ[i]);
};
//************************************************************************************************/
  MLPPopulation::~MLPPopulation()
 {
	 FreeMemory();
 };
//************************************************************************************************/
void MLPPopulation::GetMemory()
{
	_Individ.resize(_PopulationSize);
};
//************************************************************************************************/
void MLPPopulation::FreeMemory()
{
	for(int i=0;i<_PopulationSize;i++)
		_Individ[i].Remove();
	_Individ.clear();
	_PopulationSize =0;
};
//************************************************************************************************/
Solution* MLPPopulation::pGetIndividPoint(size_t i)
{
     if(i<_PopulationSize)return &_Individ[i];
     else return NULL;
};
//************************************************************************************************/
void MLPPopulation::AppendIndivid(Solution* p)
{
	MLPSolution ns(*((MLPSolution*)p));
	_Individ.push_back(ns);
	_PopulationSize++;
}
//************************************************************************************************/
void MLPPopulation::RemoveIndividByIndex(size_t ind)
{
	_Individ.erase(_Individ.begin()+ind);
	_PopulationSize--;
}
//************************************************************************************************/
void MLPPopulation::SetPopulationSize(size_t x)
{
	_PopulationSize =x;
    GetMemory();
};
//************************************************************************************************/
 void MLPPopulation::Remove()
 {
     FreeMemory();
 };
//************************************************************************************************/
 void MLPPopulation::Copy(const void* x)
 {
    MLPPopulation* y = (MLPPopulation*)(x);
    *this = *y;
 };
//************************************************************************************************/
void* MLPPopulation::Clone()const
{
    MLPPopulation* p = new MLPPopulation(*this);
    return p;
}
//************************************************************************************************/
size_t MLPPopulation::iGetPopulationSize()const
{
	return _PopulationSize;
};
//************************************************************************************************/
void MLPPopulation::SetIndividPoint(Solution* x, size_t i)
{
	pGetIndividPoint(i)->Copy(x);
};
//************************************************************************************************/
bool MLPPopulation::bHaveIndivid(Solution* x)
{
	for(int i=0;i<_PopulationSize;i++)
		if(_Individ[i].bIdentical(x))
			return true;
	return false;
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , MLPPopulation& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(MLPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , MLPPopulation& x)
{
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(MLPSolution*)x.pGetIndividPoint(i);
	out << endl;
  return out;
}
//************************************************************************************************/
//ifstream& operator >>(ifstream& in , MLPPopulation& x)
//{
//  string s,sv;
//  int ind;
//
//  while(true)
//  {
//		if(in.eof()==true)break;
//
//        getline(in,s);
//
//		ind = s.find_first_of(';');
//		if (ind ==  string::npos) break;
//		s.erase(s.begin(),s.begin()+ind+1);
//
//		ind = s.find_first_of(';');
//		if (ind ==  string::npos) break;
//		s.erase(s.begin(),s.begin()+ind+1);
//
//		ind = s.find_first_of(';');
//		if (ind ==  string::npos) break;
//		s.erase(s.begin(),s.begin()+ind+1);
//
//		MLPSolution nx;
//		nx.SetBufferNumber(x.GetIndividSize());
//
//		for(int i = 0; i<nx.GetBufferNumber(); i++)
//		{
//    		ind = s.find_first_of(';');
//			if (ind ==  string::npos) break;
//			nx.BufferSize(i)=(long) atoi(s.substr(0,ind).c_str());
//			s.erase(s.begin(),s.begin()+ind+1);
//		}
//
//		x.AddIndividPoint(&nx);
//  }
//  return in;
//}
