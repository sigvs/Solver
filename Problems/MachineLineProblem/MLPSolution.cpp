#include "MLPSolution.h"
#include <iomanip>
//************************************************************************************************/
MLPSolution::MLPSolution()
{
        _BufferSize=NULL;
        _Debit=0.0;
        _AverageStock=0.0;
        _BufferNumber=0;
};
//************************************************************************************************/
MLPSolution::MLPSolution(const MLPSolution& x)
{
        _BufferSize=NULL;
        _Debit=0.0;
        _AverageStock=0.0;
        _BufferNumber=0;
        *this = x;
};
//************************************************************************************************/
void MLPSolution::operator = (const MLPSolution& x)
{
    IterationSolution::operator = (x);
    if(_BufferNumber!=x._BufferNumber)SetBufferNumber(x._BufferNumber);
    for(int i=0;i<_BufferNumber;i++)
        _BufferSize[i]=x._BufferSize[i];
    _Debit=x._Debit;
    _AverageStock=x._AverageStock;
};
//************************************************************************************************/
MLPSolution::~MLPSolution()
{
    FreeMemory();
};
//************************************************************************************************/
void MLPSolution::GetMemory()
{
	if(_BufferSize)delete[] _BufferSize;
	_BufferSize=new long[_BufferNumber];
};
//************************************************************************************************/
void MLPSolution::FreeMemory()
{
	if(_BufferSize)delete[] _BufferSize;
	_BufferSize=NULL;
    _Debit=0.0;
    _AverageStock=0.0;
    _BufferNumber=0;
};
//************************************************************************************************/
void MLPSolution::SetBufferNumber(int s)
{
    _BufferNumber=s;
    GetMemory();
};
//************************************************************************************************/
int MLPSolution::GetBufferNumber()const
{
    return _BufferNumber;
};
//************************************************************************************************/
void MLPSolution::SetValue(ISolver* x)
{
	x->eSolve(_BufferSize,&_Debit,&_AverageStock);
};//************************************************************************************************/
void MLPSolution::Generate(void* x_, ...)
{
	void** hx = &x_;
	MLProblem* problem = (MLProblem*)(hx[0]);
	this->SetBufferNumber(problem->GetSize());
	int LowBound = 0;
	int UpBound = 0;
	for (int i = 0; i< this->GetBufferNumber(); i++)
	{
		UpBound = problem->FMachineLine.getBuffer(i + 1)->Volume;
		LowBound = 0;
		this->BufferSize(i) = LowBound + rand() % (UpBound - LowBound + 1);
	}
	this->SetValue(problem);
};
//************************************************************************************************/
bool MLPSolution::bEqual (void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	if(_BufferNumber!=y->_BufferNumber)return false;
	else
        if(_Debit!=y->Debit())return false;
        else
            if(_AverageStock!=y->AverageStock())return false;
            else
            {
                if(BufferSumm()!=y->BufferSumm())return false;
            }
	return true;
};
//************************************************************************************************/
long& MLPSolution::BufferSize(int i)
{
     if(i<_BufferNumber)return _BufferSize[i];
     else abort();
};
//************************************************************************************************/
long MLPSolution::BufferSumm()const
{
    long summ = 0;
    for(int i=0;i<_BufferNumber;i++)
        summ+=_BufferSize[i];
    return summ;
};
//************************************************************************************************/
double MLPSolution::Debit()const
{
	return _Debit;
};
//************************************************************************************************/
double MLPSolution::AverageStock()const
{
	return _AverageStock;
};
//************************************************************************************************/
bool MLPSolution::bNotEqual (void* x)const
{
	return !bEqual(x);
};
//************************************************************************************************/
bool MLPSolution::bWorse (void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	return (_Debit<y->Debit() && _AverageStock>=y->AverageStock() && BufferSumm()>=y->BufferSumm()) 
		|| (_Debit<=y->Debit() && _AverageStock>y->AverageStock() && BufferSumm()>=y->BufferSumm())
		|| (_Debit<=y->Debit() && _AverageStock>=y->AverageStock() && BufferSumm()>y->BufferSumm());
};
//************************************************************************************************/
bool MLPSolution::bBetter (void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	return (_Debit>y->Debit() && _AverageStock<=y->AverageStock() && BufferSumm()<=y->BufferSumm())
		|| (_Debit>=y->Debit() && _AverageStock<y->AverageStock() && BufferSumm()<=y->BufferSumm())
		|| (_Debit>=y->Debit() && _AverageStock<=y->AverageStock() && BufferSumm()<y->BufferSumm());
};
//************************************************************************************************/
bool MLPSolution::bBetterOrEqual (void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	return (_Debit>=y->Debit() && _AverageStock<=y->AverageStock() && BufferSumm()<=y->BufferSumm());
};
//************************************************************************************************/
bool MLPSolution::bWorseOrEqual (void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	return (_Debit<=y->Debit() && _AverageStock>=y->AverageStock() && BufferSumm()>=y->BufferSumm());

};
//************************************************************************************************/
bool MLPSolution::bIdentical(void* x)const
{
	MLPSolution* y = (MLPSolution*)(x);
	if(_BufferNumber!=y->_BufferNumber)return false;
	else
		for(int i=0;i<_BufferNumber;i++)
			if(_BufferSize[i]!=y->BufferSize(i))return false;
	return true;
};
//************************************************************************************************/
bool MLPSolution::bNotIdentical(void* x)const
{
	return !bIdentical(x);
};
//************************************************************************************************/
void MLPSolution::Remove()
{
	FreeMemory();
	IterationSolution::Remove();
};
//************************************************************************************************/
void MLPSolution::Copy(const void*x)
{
    MLPSolution* y = (MLPSolution*)(x);
    *this = *y;
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , MLPSolution& x)
{
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
ostream& operator <<(ostream& out , MLPSolution& x)
{
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
void* MLPSolution::Clone() const
{
    MLPSolution* p = new MLPSolution(*this);
    return p;
}
long MLPSolution::GetElement(size_t i)
{
	return _BufferSize[i];
}
void MLPSolution::SetElement(size_t i, long v)
{
	_BufferSize[i] = v;
}
size_t MLPSolution::GetElementCount()
{
	return _BufferNumber;
}
;
//************************************************************************************************
