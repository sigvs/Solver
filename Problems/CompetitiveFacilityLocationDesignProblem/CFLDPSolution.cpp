#include "CFLDPSolution.h"
#include <iomanip>
//************************************************************************************************/
CFLDPSolution::CFLDPSolution()
{
		_Size = 0;
		_CaptureShare = 0.0;
		_RobustRadius = 0.0;
};
//************************************************************************************************/
CFLDPSolution::CFLDPSolution(const CFLDPSolution& x)
{
		_Size = 0;
		_CaptureShare = 0.0;
		_RobustRadius = 0.0;
        *this = x;
};
//************************************************************************************************/
void CFLDPSolution::operator = (const CFLDPSolution& x)
{
    IterationSolution::operator = (x);
    if(_Size !=x._Size)SetSize(x._Size);
	for (int i = 0; i < _Size; i++)
	{
		_DesignVariant[i] = x._DesignVariant[i];
		_DeviationDemand[i] = x._DeviationDemand[i];
	}
	_CaptureShare = x._CaptureShare;
	_RobustRadius = x._RobustRadius;
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
	_DeviationDemand.resize(_Size);
};
//************************************************************************************************/
void CFLDPSolution::FreeMemory()
{
	_DesignVariant.clear();
	_DeviationDemand.clear();
	_CaptureShare = 0.0;
	_RobustRadius = 0.0;
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
	x->eSolve(&_DesignVariant,&_DeviationDemand,&_CaptureShare,&_RobustRadius);
};//************************************************************************************************/
void CFLDPSolution::Generate(void* x_, ...)
{
	void** hx = &x_;
	CFLDProblem* problem = (CFLDProblem*)(hx[0]);
	this->SetSize(problem->getN());

	int b = problem->getB(), 
		n = problem->getS();

	iVector indx = problem->getIndex();
	iVector index_tmp;
	for (int i = 0; i < indx.size(); i++)
		index_tmp.push_back(indx[i]);

	int in_tmp,vr_tmp;
	while (b > 0)
	{
		if (index_tmp.size() == 1)
		{
			this->_DesignVariant[index_tmp[0]] = std::min(b, 3);
			break;
		}
		else
		{
			in_tmp = rand() % index_tmp.size();
			vr_tmp = rand() % (std::min(b, 3) + 1);
			this->_DesignVariant[index_tmp[in_tmp]] = vr_tmp;
			b -= vr_tmp;
			auto pointer = index_tmp.cbegin() + in_tmp;
			index_tmp.erase(pointer, pointer + 1);
		}
	}

	for (int i = 0; i < problem->getS(); i++)
	{
		if(this->_DesignVariant[problem->getIndex()[i]] > 0)
			this->DeviationDemand(problem->getIndex()[i]) = rand() % (problem->getw(problem->getIndex()[i]) + 1);
		//this->DeviationDemand(i) = problem->getw(i);
	}


	this->SetValue((ISolver*)problem);
};
//************************************************************************************************/
bool CFLDPSolution::bEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	if(_Size!=y->_Size)return false;
	else
        if(_CaptureShare !=y->CaptureShare() || _RobustRadius != y->RobustRadius())return false;
	return true;
};
//************************************************************************************************/
int& CFLDPSolution::DesignVariant(int i)
{
	if (i < _Size)return _DesignVariant[i];
	else abort();
};
//************************************************************************************************/
int& CFLDPSolution::DeviationDemand(int i)
{
	if (i < _Size)return _DeviationDemand[i];
	else abort();
};
//************************************************************************************************/
double CFLDPSolution::CaptureShare()const
{
	return _CaptureShare;
};
//************************************************************************************************/
double CFLDPSolution::RobustRadius()const
{
	return _RobustRadius;
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
	return (_CaptureShare > y->CaptureShare() && _RobustRadius > y->RobustRadius());
};
//************************************************************************************************/
bool CFLDPSolution::bBetterOrEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare >= y->CaptureShare() && _RobustRadius >= y->RobustRadius());
};
//************************************************************************************************/
bool CFLDPSolution::bWorseOrEqual (void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	return (_CaptureShare <= y->CaptureShare() && _RobustRadius <= y->RobustRadius());

};
//************************************************************************************************/
bool CFLDPSolution::bIdentical(void* x)const
{
	CFLDPSolution* y = (CFLDPSolution*)(x);
	if(_Size!=y->_Size)return false;
	else
		for(int i=0;i< _Size;i++)
			if(_DesignVariant[i]!=y->DesignVariant(i) || _DeviationDemand[i]!=y->DeviationDemand(i))return false;
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
	out << x.RobustRadius() << ";" << x.CaptureShare() << ";";
	if (x._Size > 0)
	{
		for (int i = 0; i < x._Size; i++)
			out << x.DesignVariant(i) << ";";
		for (int i = 0; i < x._Size; i++)
			out << x.DeviationDemand(i) << ";";

	}
	out << endl;
	return out;
}
//************************************************************************************************/
ostream& operator <<(ostream& out , CFLDPSolution& x)
{
	out << x.RobustRadius() << ";" << x.CaptureShare() << ";";
	if (x._Size > 0)
	{
		for (int i = 0; i < x._Size; i++)
			out << x.DesignVariant(i) << ";";
		for (int i = 0; i < x._Size; i++)
			out << x.DeviationDemand(i) << ";";

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
//************************************************************************************************/
