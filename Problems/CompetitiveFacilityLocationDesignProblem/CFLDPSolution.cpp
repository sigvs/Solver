#include "CFLDPSolution.h"
#include <iomanip>
//************************************************************************************************/
CFLDPSolution::CFLDPSolution()
{
		_Size = 0;
		_CaptureShare = 0.0;
};
//************************************************************************************************/
CFLDPSolution::CFLDPSolution(const CFLDPSolution& x)
{
		_Size = 0;
		_CaptureShare = 0.0;
        *this = x;
};
//************************************************************************************************/
void CFLDPSolution::operator = (const CFLDPSolution& x)
{
    IterationSolution::operator = (x);
    if(_Size !=x._Size)SetSize(x._Size);
    for(int i=0;i< _Size;i++)
		_DesignVariant[i]=x._DesignVariant[i];
	_CaptureShare =x._CaptureShare;
};
//************************************************************************************************/
CFLDPSolution::~CFLDPSolution()
{
    FreeMemory();
};
//************************************************************************************************/
void CFLDPSolution::GetMemory()
{
	_DesignVariant.resize(_Size);
};
//************************************************************************************************/
void CFLDPSolution::FreeMemory()
{
	_DesignVariant.clear();
	_CaptureShare =0.0;
};
//************************************************************************************************/
void CFLDPSolution::SetSize(int s)
{
	_Size=s;
    GetMemory();
};
//************************************************************************************************/
int CFLDPSolution::GetSize()const
{
    return _Size;
};
//************************************************************************************************/
void CFLDPSolution::SetValue(ISolver* x)
{
	x->eSolve(&_DesignVariant,&_CaptureShare);
};//************************************************************************************************/
void CFLDPSolution::Generate(void* x_, ...)
{
	void** hx = &x_;
	CFLDProblem* problem = (CFLDProblem*)(hx[0]);
	this->SetSize(problem->getN());

	int b = problem->getB(), n = problem->getS();
	int k3 = std::min(b / 3, n);
	for (int i = 0; i < k3; ++i) {
		this->_DesignVariant[i] = 3;
	}
	b -= 3 * k3;
	n -= k3;
	if (n <= 0) {
		return;
	}
	int k2 = std::min(b / 2, n);
	for (int i = 0; i < k2; ++i) {
		this->_DesignVariant[k3 + i] = 2;
	}
	b -= 2 * k2;
	n -= k2;
	if (n <= 0) {
		return;
	}
	int k1 = std::min(b, n);
	for (int i = 0; i < k1; ++i) {
		this->_DesignVariant[k3 + k2 + i] = 1;
	}
	n -= k1;
	if (n <= 0) {
		return;
	}
	for (int i = k1 + k2 + k3; i < problem->getS(); ++i) {
		this->_DesignVariant[i] = 0;
	}

	this->SetValue((ISolver*)problem);
};
//************************************************************************************************/
bool CFLDPSolution::bEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	if(_Size!=y->_Size)return false;
	else
        if(_CaptureShare !=y->CaptureShare())return false;
	return true;
};
//************************************************************************************************/
int& CFLDPSolution::DesignVariant(int i)
{
     if(i<_Size)return _DesignVariant[i];
     else abort();
};
//************************************************************************************************/
double CFLDPSolution::CaptureShare()const
{
	return _CaptureShare;
};
//************************************************************************************************/
bool CFLDPSolution::bNotEqual (void* x)const
{
	return !bEqual(x);
};
//************************************************************************************************/
bool CFLDPSolution::bWorse (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare < y->CaptureShare() && _RobustRadius < y->RobustRadius());
};
//************************************************************************************************/
bool CFLDPSolution::bBetter (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare > y->CaptureShare());
};
//************************************************************************************************/
bool CFLDPSolution::bBetterOrEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare >= y->CaptureShare());
};
//************************************************************************************************/
bool CFLDPSolution::bWorseOrEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare <= y->CaptureShare());

};
//************************************************************************************************/
bool CFLDPSolution::bIdentical(void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	if(_Size!=y->_Size)return false;
	else
		for(int i=0;i< _Size;i++)
			if(_DesignVariant[i]!=y->DesignVariant(i))return false;
	return true;
};
//************************************************************************************************/
bool CFLDPSolution::bNotIdentical(void* x)const
{
	return !bIdentical(x);
};
//************************************************************************************************/
void CFLDPSolution::Remove()
{
	FreeMemory();
	IterationSolution::Remove();
};
//************************************************************************************************/
void CFLDPSolution::Copy(const void*x)
{
    CFLDPSolution* y = (CFLDPSolution*)(x);
    *this = *y;
};
//************************************************************************************************/
ofstream& operator <<(ofstream& out , CFLDPSolution& x)
{
	out << setw(7) << left << setprecision(4) << x.CaptureShare() << "; ";
	if (x._Size > 0)
	{
		for (int i = 0; i < x._Size; i++)
			out << left << std::setw(3) << x.DesignVariant(i) << ";";
	}
	out << endl;
  return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , CFLDPSolution& x)
{
	out << setw(7) << left << setprecision(4) << x.CaptureShare() << "; ";
	if (x._Size > 0)
	{
		for (int i = 0; i < x._Size; i++)
			out << left << std::setw(3) << x.DesignVariant(i) << ";";
	}
	out << endl;
	return out;
}
//************************************************************************************************/
void* CFLDPSolution::Clone() const
{
    CFLDPSolution* p = new CFLDPSolution(*this);
    return p;
}
long CFLDPSolution::GetElement(size_t i)
{
	return _DesignVariant[i];
}
void CFLDPSolution::SetElement(size_t i, long v)
{
	_DesignVariant[i] = v;
}
size_t CFLDPSolution::GetElementCount()
{
	return _Size;
}
;
//************************************************************************************************
