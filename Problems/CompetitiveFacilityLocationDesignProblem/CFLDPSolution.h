#ifndef hpp_CFLDPSolution_hpp
#define hpp_CFLDPSolution_hpp

#include "..\..\Algoithms\Common\IterationSolution.h"
#include "..\..\Interface\IArray.h"
#include "CFLDProblem.h"
using namespace std;

class CFLDPSolution :public IterationSolution
{
    protected:
        int _Size;
        iVector _DesignVariant;
        iVector _DeviationDemand;

        double _RobustRadius;
        double _CaptureShare;
	public:
        CFLDPSolution();
        CFLDPSolution(const CFLDPSolution&);
		void operator = (const CFLDPSolution&);
		virtual ~CFLDPSolution();

		void GetMemory();
		void FreeMemory();

		virtual void SetValue(ISolver*);

		virtual void SetSize(int);
		virtual int GetSize()const;

        int& DesignVariant(int);
        int& DeviationDemand(int);

        double CaptureShare()const;
        double RobustRadius()const;

        virtual bool bEqual (void*)const;
        virtual bool bNotEqual (void*)const;
        virtual bool bWorse (void*)const;
        virtual bool bBetter (void*)const;
        virtual bool bWorseOrEqual (void*)const;
        virtual bool bBetterOrEqual (void*)const;
        virtual bool bIdentical(void*)const;
        virtual bool bNotIdentical(void*)const;

		virtual void Generate(void*, ...);

        friend ofstream& operator <<(ofstream& , CFLDPSolution&);
//        friend ifstream& operator >>(ifstream& , tpMLProblem&);
        friend ostream& operator <<(ostream& , CFLDPSolution&);

        virtual void Remove();
        virtual void Copy(const void*);
		virtual void* Clone()const;

};
#endif
