#include "PopulationUseList.h"
#include <iomanip>

//************************************************************************************************/
  PopulationUseList::PopulationUseList()
 {
	  _PopulationSize =0;
 };
//************************************************************************************************/
  PopulationUseList::PopulationUseList(const PopulationUseList& x)
 {
	  _PopulationSize =0;
    *this = x;
 };
//************************************************************************************************/
void  PopulationUseList::operator = (const PopulationUseList& x)
{
    Population::operator = (x);
    for(Solution* sol : x._Individ)
		_Individ.push_back((Solution*)sol->Clone());
};
//************************************************************************************************/
  PopulationUseList::~PopulationUseList()
 {
	 FreeMemory();
 };
//************************************************************************************************/
list<Solution*>::iterator PopulationUseList::GetIterator(size_t n)
{
	list<Solution*>::iterator result;
	size_t i = 0;
	for (list<Solution*>::iterator it = _Individ.begin(); it != _Individ.end(); ++it)
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
void PopulationUseList::FreeMemory()
{
	for(Solution* sol : _Individ)
		sol->Remove();
	_Individ.clear();
	_PopulationSize =0;
};
//************************************************************************************************/
Solution* PopulationUseList::pGetIndividPoint(size_t i)
{
     if(i<_PopulationSize)return *GetIterator(i);
     else return NULL;
};
//************************************************************************************************/
void PopulationUseList::SetPopulationSize(size_t x)
{
	_PopulationSize =x;
    GetMemory();
};
//************************************************************************************************/
 void PopulationUseList::Remove()
 {
     FreeMemory();
 };
//************************************************************************************************/
void PopulationUseList::AppendIndivid(Solution* x)
{
	_Individ.push_back((Solution*)x->Clone());
	_PopulationSize++;
}
//************************************************************************************************/
void PopulationUseList::RemoveIndividByIndex(size_t i)
{
	_Individ.erase(GetIterator(i));
	_PopulationSize--;
}
//************************************************************************************************/
size_t PopulationUseList::iGetPopulationSize()const
{
	return _PopulationSize;
};
//************************************************************************************************/
void PopulationUseList::SetIndividPoint(Solution* x, size_t i)
{
	pGetIndividPoint(i)->Copy(x);
};
//************************************************************************************************/
bool PopulationUseList::bHaveIndivid(Solution* x)
{
	for(Solution* sol : _Individ)
		if(sol->bIdentical(x))
			return true;
	return false;
};
//************************************************************************************************/
