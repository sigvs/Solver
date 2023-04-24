#include "NSGA2Solution.h"
#include "NSGA2Population.h"
#include <iomanip>
//************************************************************************************************/
NSGA2Solution::NSGA2Solution()
{
	MLPSolution::MLPSolution();
	_Rank = 0;
	_CrowdingDistance = 0.0;
	_WorseIndividCount = 0;

};
//************************************************************************************************/
NSGA2Solution::NSGA2Solution(const NSGA2Solution& x)
{
        _BufferSize=NULL;
        _Debit=0.0;
        _AverageStock=0.0;
        _BufferNumber=0;
		_Rank = 0;
		_CrowdingDistance = 0.0;
		_WorseIndividCount = 0;
        *this = x;
};
//************************************************************************************************/
void NSGA2Solution::operator = (const NSGA2Solution& x)
{
	MLPSolution::operator = (x);
	this->SetWorseIndividMaxCount(x._WorseIndividIndex.size());
	for (size_t i = 0; i < _WorseIndividIndex.size(); i++)
		_WorseIndividIndex[i] = x._WorseIndividIndex[i];
	_Rank = x._Rank;
	_CrowdingDistance = x._CrowdingDistance;
	_WorseIndividCount = x._WorseIndividCount;
};
//************************************************************************************************/
NSGA2Solution::~NSGA2Solution()
{
    FreeMemory();
};
//************************************************************************************************/
bool NSGA2Solution::IsDominant()const
{
	return _BestIndividCount == 0;
};
//************************************************************************************************/
long NSGA2Solution::Rank()const
{
	return _Rank;
};
//************************************************************************************************/
double NSGA2Solution::CrowdingDistance()const
{
	return _CrowdingDistance;
};
//************************************************************************************************/
void NSGA2Solution::SetRank(long r)
{
	_Rank = r;
};
//************************************************************************************************/
void NSGA2Solution::SetCrowdingDistance(double d)
{
	_CrowdingDistance = d;
};//************************************************************************************************/
void NSGA2Solution::AddCrowdingDistance(double d)
{
	_CrowdingDistance += d;
};
//************************************************************************************************/
size_t NSGA2Solution::BestIndividCount()const
{
	return _BestIndividCount;
}
//************************************************************************************************/
void NSGA2Solution::SetBestIndividCount(size_t c)
{
	_BestIndividCount = c;
}
//************************************************************************************************/
void NSGA2Solution::IncrementBestIndividCount()
{
	_BestIndividCount++;
}//************************************************************************************************/
void NSGA2Solution::DecrementBestIndividCount()
{
	_BestIndividCount--;
}
//************************************************************************************************/
void NSGA2Solution::AddWorseIndividIndex(size_t i)
{
	if (_WorseIndividCount + 1 == _WorseIndividIndex.size())
		_WorseIndividIndex.push_back(i);
	else
		_WorseIndividIndex[_WorseIndividCount] = i;

	_WorseIndividCount++;
}
//************************************************************************************************/
size_t NSGA2Solution::WorseIndividIndex(size_t i)
{
	if (i >= _WorseIndividIndex.size()) throw new exception("¬ыход за границы массива доминируемых особей");
	return _WorseIndividIndex[i];
}
//************************************************************************************************/
void NSGA2Solution::SetWorseIndividMaxCount(size_t c)
{
	_WorseIndividIndex.resize(c);
	_WorseIndividCount = 0;
}
//************************************************************************************************/
void NSGA2Solution::ClearWorseIndivids() 
{
	for (size_t i = 0; i < 	_WorseIndividCount; i++)
		_WorseIndividIndex[i] = -1;
	_WorseIndividCount = 0;
}
//************************************************************************************************/
size_t NSGA2Solution::WorseIndividCount()const
{
	return _WorseIndividCount;
}
//************************************************************************************************/
void NSGA2Solution::Generate(void* x_, ...)
{
	void** hx = &x_;
	MLProblem* problem = (MLProblem*)(hx[0]);
	NSGA2Population* populaton = (NSGA2Population*)(hx[1]);
	this->SetWorseIndividMaxCount(populaton->GetPopulationSize()+ populaton->GetChildPopulationSize());
	MLPSolution::Generate(problem);
};
//************************************************************************************************/
void NSGA2Solution::Remove()
{
	FreeMemory();
	IterationSolution::Remove();
};
//************************************************************************************************/
void NSGA2Solution::Copy(const void*x)
{
    NSGA2Solution* y = (NSGA2Solution*)(x);
    *this = *y;
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , NSGA2Solution& x)
{
	out << setw(3) << left << x.Rank() << "; ";
	out << setw(6) << left << setprecision(3) << x.CrowdingDistance() << ";     ";
	out << setw(7) << left << setprecision(4) << x.Debit() << "; ";
	out << left << setprecision(5) << setw(7) << x.AverageStock() << ";";
	out << left << std::setw(3) << x.BufferSumm() << ";     ";
	if (x._BufferNumber > 0)
	{
		for (int i = 0; i < x._BufferNumber - 1; i++)
			out << left << std::setw(3) << x.BufferSize(i) << ";";
		out << left << std::setw(3) << x.BufferSize(x._BufferNumber - 1) << ";";
	}
	out << endl;
	return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , NSGA2Solution& x)
{
	out << setw(3) << left << x.Rank() << "; ";
	out << setw(6) << left << setprecision(3) << x.CrowdingDistance() << ";     ";
	out << setw(7) << left << setprecision(4) << x.Debit() << "; ";
	out << left << setprecision(5) << setw(7) << x.AverageStock() << ";";
	out << left << std::setw(3) << x.BufferSumm() << ";     ";
	if (x._BufferNumber > 0)
	{
		for (int i = 0; i < x._BufferNumber - 1; i++)
			out << left << std::setw(3) << x.BufferSize(i) << ";";
		out << left << std::setw(3) << x.BufferSize(x._BufferNumber - 1) << ";";
	}
	out << endl;
	return out;
}
//************************************************************************************************/
void* NSGA2Solution::Clone() const
{
    NSGA2Solution* p = new NSGA2Solution(*this);
    return p;
};
//************************************************************************************************
bool NSGA2Solution::bWorse(void* x)const
{
	NSGA2Solution* y = (NSGA2Solution*)(x);
	if (this->Rank() > y->Rank())return true;
	if (this->Rank() == y->Rank() && this->CrowdingDistance() < y->CrowdingDistance() )return true;
	return false;
}
//************************************************************************************************
bool NSGA2Solution::bBetter(void* x)const
{
	NSGA2Solution* y = (NSGA2Solution*)(x);
	if (this->Rank() < y->Rank())return true;
	if (this->Rank() == y->Rank() && this->CrowdingDistance() > y->CrowdingDistance())return true;
	return false;
}
//************************************************************************************************
bool NSGA2Solution::bWorseOrEqual(void* x)const
{
	NSGA2Solution* y = (NSGA2Solution*)(x);
	if (this->Rank() > y->Rank())return true;
	if (this->Rank() == y->Rank() && this->CrowdingDistance() <= y->CrowdingDistance())return true;
	return false;
}
//************************************************************************************************
bool NSGA2Solution::bBetterOrEqual(void* x)const
{
	{
		NSGA2Solution* y = (NSGA2Solution*)(x);
		if (this->Rank() < y->Rank())return true;
		if (this->Rank() == y->Rank() && this->CrowdingDistance() >= y->CrowdingDistance())return true;
		return false;
	}
}
//************************************************************************************************
