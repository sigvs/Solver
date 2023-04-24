#include "MLPPopulationList.h"
#include <iomanip>
//************************************************************************************************/
  MLPPopulationList::MLPPopulationList()
 {
	  _PopulationSize =0;
 };
//************************************************************************************************/
  MLPPopulationList::MLPPopulationList(const MLPPopulationList& x)
 {
	  _PopulationSize =0;
    *this = x;
 };
//************************************************************************************************/
void  MLPPopulationList::operator = (const MLPPopulationList& x)
{
    Population::operator = (x);
    for(MLPSolution* sol : x._Individ)
		_Individ.push_back((MLPSolution*)sol->Clone());
};
//************************************************************************************************/
  MLPPopulationList::~MLPPopulationList()
 {
	 FreeMemory();
 };
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
list<MLPSolution*>::iterator MLPPopulationList::GetIterator(size_t n)
{
	list<MLPSolution*>::iterator result;
	size_t i = 0;
	for (list<MLPSolution*>::iterator it = _Individ.begin(); it != _Individ.end(); ++it)
	{
		if (i == n)
		{
			result = it;
			break;
		}
		i++;
	}
	return result;
}
//************************************************************************************************/
void MLPPopulationList::FreeMemory()
{
	for(MLPSolution* sol : _Individ)
		sol->Remove();
	_Individ.clear();
	_PopulationSize =0;
};
//************************************************************************************************/
Solution* MLPPopulationList::pGetIndividPoint(size_t i)
{
     if(i<_PopulationSize)return *GetIterator(i);
     else return NULL;
};
//************************************************************************************************/
void MLPPopulationList::SetPopulationSize(size_t x)
{
	_PopulationSize =x;
    GetMemory();
};
//************************************************************************************************/
 void MLPPopulationList::Remove()
 {
     FreeMemory();
 };
//************************************************************************************************/
 void MLPPopulationList::Copy(const void* x)
 {
    MLPPopulationList* y = (MLPPopulationList*)(x);
    *this = *y;
 };
//************************************************************************************************/
void* MLPPopulationList::Clone()const
{
    MLPPopulationList* p = new MLPPopulationList(*this);
    return p;
}
void MLPPopulationList::AppendIndivid(Solution* x)
{
	_Individ.push_back((MLPSolution*)x->Clone());
	_PopulationSize++;
}
//************************************************************************************************/
void MLPPopulationList::RemoveIndividByIndex(size_t i)
{
	_Individ.erase(GetIterator(i));
	_PopulationSize--;
}
//************************************************************************************************/
size_t MLPPopulationList::iGetPopulationSize()const
{
	return _PopulationSize;
};
//************************************************************************************************/
void MLPPopulationList::SetIndividPoint(Solution* x, size_t i)
{
	pGetIndividPoint(i)->Copy(x);
};
//************************************************************************************************/
bool MLPPopulationList::bHaveIndivid(Solution* x)
{
	for(MLPSolution* sol : _Individ)
		if(sol->bIdentical(x))
			return true;
	return false;
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
//ifstream& operator >>(ifstream& in , MLPPopulationList& x)
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
