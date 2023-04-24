#include "NSGA2Population.h"
//************************************************************************************************/
  NSGA2Population::NSGA2Population()
 {
    _PopulationSize=0;
 };
//************************************************************************************************/
  NSGA2Population::NSGA2Population(const NSGA2Population& x)
 {
	  _PopulationSize = 0;
    *this = x;
 };
//************************************************************************************************/
void  NSGA2Population::operator = (const NSGA2Population& x)
{
    Population::operator = (x);
	if (_Size() != x._Size())
	{
		SetPopulationSize(x._PopulationSize);
		SetChildPopulationSize(x._ChildPopulationSize);
	}
    for(int i=0;i<_Size();i++)
		pGetIndividPoint(i)->Copy(&x._Individs[i]);
};
//************************************************************************************************/
  NSGA2Population::~NSGA2Population()
 {
	 FreeMemory();
 };
//************************************************************************************************/
void NSGA2Population::GetMemory()
{
	_WorseIndividIndex.resize(_ChildPopulationSize);
	size_t ls = _Individs.size();
	_Individs.resize(_Size());
	_Fronts.resize(_Size());
	_FrontSizes.resize(_Size());
	for (size_t i = 0; i < _Size(); i++)
	{
		if(i>=ls)
			_Individs[i] = new NSGA2Solution();
		_FrontSizes[i] = 0;
		_Fronts[i].resize(_Size());
	}
};
//************************************************************************************************/
void NSGA2Population::FreeMemory()
{
	for (int i = 0; i < _Size(); i++)
	{
		_Individs[i]->Remove();
		delete _Individs[i];
	}
	_Individs.clear();
	_WorseIndividIndex.clear();
	_PopulationSize = 0;
};
//************************************************************************************************/
size_t NSGA2Population::GetChildPopulationSize()const {
	return _ChildPopulationSize;
};
//************************************************************************************************/
void NSGA2Population::AddIndividPoint(Solution* p)
{
	_Individs.push_back((NSGA2Solution*)p);
	_PopulationSize++;
}
//************************************************************************************************/
void NSGA2Population::DeleteIndividPoint(size_t ind)
{
	_Individs.erase(_Individs.begin()+ind);
	_PopulationSize--;
}
//************************************************************************************************/
size_t NSGA2Population::_Size()const
{
	return _ChildPopulationSize + _PopulationSize;
}
//************************************************************************************************/
void NSGA2Population::SetChildPopulationSize(size_t s)
{
	_ChildPopulationSize = s;
	GetMemory();
}
//************************************************************************************************/
void NSGA2Population::SetPopulationSize(size_t x)
{
	_PopulationSize =x;
    GetMemory();
};
//************************************************************************************************/
 void NSGA2Population::Remove()
 {
     FreeMemory();
 };
//************************************************************************************************/
  void NSGA2Population::AddIndividToFront(size_t fr, size_t in)
  {
	  _Fronts[fr][_FrontSizes[fr]] = in;
	  _FrontSizes[fr]++;
  }
//************************************************************************************************/
  size_t NSGA2Population::GetIndividFront(size_t fr, size_t in)
  {
	  if (fr >= _Fronts.size() || in >= _FrontSizes[fr]) throw new exception("Выход за пределы размера фронта");

	  return _Fronts[fr][in];
  }
//************************************************************************************************/
 void NSGA2Population::ClearFront(size_t fr)
 {
	 _FrontSizes[fr] = 0;

 }
 //************************************************************************************************/
 size_t NSGA2Population::FrontSize(size_t i)
 {
	 return _FrontSizes[i];
 }
 //************************************************************************************************/
 size_t NSGA2Population::FrontCount()
 { 
	 return _FrontCount;
 }
 //************************************************************************************************/
 void NSGA2Population::Copy(const void* x)
 {
    NSGA2Population* y = (NSGA2Population*)(x);
    *this = *y;
 };
//************************************************************************************************/
void* NSGA2Population::Clone()const
{
    NSGA2Population* p = new NSGA2Population(*this);
    return p;
}
//************************************************************************************************/
Solution* NSGA2Population::pGetIndividPoint(size_t i)
{
	if (i >= _PopulationSize) return NULL;
	else return _Individs[i];
}
//************************************************************************************************/
Solution* NSGA2Population::pGetAllIndividPoint(size_t i)
{
	if (i >= _PopulationSize + _ChildPopulationSize) return NULL;
	else return _Individs[i];
}
//************************************************************************************************/
void NSGA2Population::SetIndividPoint(Solution* x, size_t i)
{
	pGetIndividPoint(i)->Copy(x);
};
//************************************************************************************************/
bool NSGA2Population::bHaveIndivid(Solution* x)
{
	for(size_t i=0;i<_PopulationSize;i++)
		if(_Individs[i]->bIdentical(x))
			return true;
	return false;
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , NSGA2Population& x)
{
	//for(size_t i=0;i<x._PopulationSize+x._ChildPopulationSize;i++)
	//	out << "#" << left << setw(3) << i << "	" << *(NSGA2Solution*)x.pGetAllIndividPoint(i);
	for (size_t i = 0; i<x._PopulationSize; i++)
		out << "#" << left << setw(3) << i << "	" << *(NSGA2Solution*)x.pGetIndividPoint(i);
   out<<endl;
  return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , NSGA2Population& x)
{
	for(size_t i=0;i<x._PopulationSize + x._ChildPopulationSize;i++)
		out << "#" << left<<setw(3) << i <<"	"<< *(NSGA2Solution*)x.pGetAllIndividPoint(i);
   out<<endl;
  return out;
}
//************************************************************************************************/
//ifstream& operator >>(ifstream& in , NSGA2Population& x)
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
//************************************************************************************************
void NSGA2Population::NonDominatedSort()
{
	for (size_t i = 0; i < _Size(); i++)
	{
		ClearFront(i);
		_Individs[i]->SetBestIndividCount(0);
		_Individs[i]->ClearWorseIndivids();
	}

	for (size_t i = 0; i<_Size(); i++)
	{
		for (size_t j = i + 1; j<_Size(); j++)
		{
			if (_Individs[i]->MLPSolution::bBetter(_Individs[j]))
			{
				_Individs[i]->AddWorseIndividIndex(j);
				_Individs[j]->IncrementBestIndividCount();

			}
			if (_Individs[j]->MLPSolution::bBetter(_Individs[i]))
			{
				_Individs[j]->AddWorseIndividIndex(i);
				_Individs[i]->IncrementBestIndividCount();
			}
		}
	}
	for (size_t i = 0; i < _Size(); i++)
	{
		if (_Individs[i]->BestIndividCount() == 0)
		{
			AddIndividToFront(0, i);
			_Individs[i]->SetRank(0);
		}
	}
	_FrontCount = 1;
	_FillFront(1);
};
//************************************************************************************************
void NSGA2Population::_FillFront(size_t fr)
{
	size_t fs = _FrontSizes[fr - 1];
	bool b = false;
	for (size_t i = 0; i < fs; i++)
	{
		NSGA2Solution* dom = _Individs[_Fronts[fr - 1][i]];
		size_t dom_worse_size = dom->WorseIndividCount();
		for (size_t j = 0; j < dom_worse_size; j++)
		{
			size_t inx = dom->WorseIndividIndex(j);
			NSGA2Solution* ind = _Individs[inx];
			ind->DecrementBestIndividCount();
			if (ind->BestIndividCount() == 0)
			{
				AddIndividToFront(fr, inx);
				ind->SetRank(fr);
				b = true;
			}
		}
	}
	if (b)
	{
		_FrontCount = fr + 1;
		_FillFront(fr + 1);
	}
}
//************************************************************************************************
void NSGA2Population::_CrowdingDistanceByCriteria(Criteria crt)
{
	for (int i = 0; i < _Size(); i++)
	{
		if (_FrontSizes[i] == 0) break;
		sort(_Fronts[i].begin(), _Fronts[i].begin() + _FrontSizes[i], CompareIndividsIndex(this, crt));
		//for(int j = 0; j < _FrontSizes[i]; j++)	cout << _Fronts[i][j] << " ";
		//cout << endl;
		double max_diff = abs(_IndividDifferenceByCriteria(_Fronts[i][_FrontSizes[i] - 1], _Fronts[i][0], crt));
		if (max_diff > 1e-6)
		{
			_Individs[_Fronts[i][0]]->SetCrowdingDistance(INFINITY);
			_Individs[_Fronts[i][_FrontSizes[i] - 1]]->SetCrowdingDistance(INFINITY);
			for (size_t j = 1; j < _FrontSizes[i] - 1; j++)
			{
				double diff = abs(_IndividDifferenceByCriteria(_Fronts[i][j + 1], _Fronts[i][j - 1], crt));
				_Individs[_Fronts[i][j]]->AddCrowdingDistance(diff/max_diff);
			}
		}
	}
}
//************************************************************************************************
double NSGA2Population::_IndividDifferenceByCriteria(size_t i, size_t j, Criteria crt)
{
	switch (crt)
	{
	case Debit:
		return _Individs[i]->Debit() - _Individs[j]->Debit();
		break;
	case BufferSumm:
		return _Individs[i]->BufferSumm() - _Individs[j]->BufferSumm();
		break;
	case AverageStock:
		return _Individs[i]->AverageStock() - _Individs[j]->AverageStock();
		break;
	default:
		return false;
		break;
	}
}
//************************************************************************************************
void NSGA2Population::CrowdingDistance()
{
	for (size_t i = 0; i < _Size(); i++)
		_Individs[i]->SetCrowdingDistance(0);
	_CrowdingDistanceByCriteria(Debit);
	_CrowdingDistanceByCriteria(BufferSumm);
	_CrowdingDistanceByCriteria(AverageStock);
}
//************************************************************************************************
void NSGA2Population::ReplaceChildIndividsByWorseIndivids()
{
	NSGA2Solution* _tmp = new NSGA2Solution();
	size_t ind, cur, nxt, t;
	size_t n = _ChildPopulationSize;
	for (size_t i = 0; i < n; i++)
		_WorseIndividIndex[i] = -1;

	for (int i = _FrontCount - 1; i >-1; i--)
	{
		if (n == 0) break;
		for (size_t j = 0; j < _FrontSizes[i]; j++)
		{
			for (size_t k = 0; k < _ChildPopulationSize; k++)
			{
				if (_WorseIndividIndex[k] == -1)
				{
					_WorseIndividIndex[k] = _Fronts[i][j];
					n--;
					break;
				}
				else
				{
					if (_Individs[_Fronts[i][j]]->bWorse(_Individs[_WorseIndividIndex[k]]))
					{
						cur = _WorseIndividIndex[k];
						_WorseIndividIndex[k] = _Fronts[i][j];
						t = k + 1;
						while (t < _ChildPopulationSize)
						{
							if (_WorseIndividIndex[t] == -1)
							{
								_WorseIndividIndex[t] = cur;
								break;
							}
							else
							{
								nxt = _WorseIndividIndex[t];
								_WorseIndividIndex[t] = cur;
								cur = nxt;
							}
							t++;
						}
						n--;
						break;
					}
				}
			}
		}
	}

	for (size_t k = 0; k < _ChildPopulationSize; k++)
	{
		if (_WorseIndividIndex[k] < _PopulationSize)
		{
			_tmp = _Individs[_WorseIndividIndex[k]];
			_Individs[_WorseIndividIndex[k]] = _Individs[_PopulationSize+k];
			_Individs[_PopulationSize + k] = _tmp;
		}
	}
}
//************************************************************************************************
void NSGA2Population::AddChildIndivids(Population* p)
{
	if (p->GetPopulationSize() > _ChildPopulationSize) throw new exception("Входящая популяция имеет потомков больше чем надо");
	for (size_t i = 0; i < p->GetPopulationSize(); i++)
	{
		_Individs[_PopulationSize + i]->Copy(p->pGetIndividPoint(i));
	}
	NonDominatedSort();
	//cout << *this;
	CrowdingDistance();
	//cout << *this;
	ReplaceChildIndividsByWorseIndivids();
}
//************************************************************************************************