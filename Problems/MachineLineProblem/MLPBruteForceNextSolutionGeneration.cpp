#include "MLPBruteForceNextSolutionGeneration.h"
//************************************************************************************************
MLPBruteForceNextSolutionGeneration::MLPBruteForceNextSolutionGeneration()
{
};
//************************************************************************************************
MLPBruteForceNextSolutionGeneration::MLPBruteForceNextSolutionGeneration(const MLPBruteForceNextSolutionGeneration& x)
{
	*this=x;
};
//************************************************************************************************
MLPBruteForceNextSolutionGeneration::~MLPBruteForceNextSolutionGeneration()
{
};
//************************************************************************************************
void MLPBruteForceNextSolutionGeneration::operator = (const MLPBruteForceNextSolutionGeneration& x)
{
};
//************************************************************************************************
SolverResult MLPBruteForceNextSolutionGeneration::eSolve(void* x_, ...)
{
    void** x= &x_;
    MLProblem* problem = (MLProblem*)(x[0]);
    MLPSolution* solution = (MLPSolution*)(x[1]);
	int i=0;

	while(true)
	{
		if(solution->BufferSize(i) >= problem->FMachineLine.getBuffer(i+1)->Volume)
		{
			if(i==solution->GetBufferNumber()-1)
			{
				return SolutionNotFound;
			}
			else
			{
				solution->BufferSize(i) = 0;
				i++;
			}
		}
		else
		{
			solution->BufferSize(i) += 1;
			solution->SetValue(problem);
			break;
		}
	}
	return SolutionFound;
};
////************************************************************************************************
// void MLPBruteForceNextSolutionGeneration::Copy(const void* x)
// {
//    MLPBruteForceNextSolutionGeneration* y = (MLPBruteForceNextSolutionGeneration*)(x);
//    *this = *y;
// };
////************************************************************************************************
//string MLPBruteForceNextSolutionGeneration::TypeName()const
//{
//	return "MLPBruteForceNextSolutionGeneration";
//};
////************************************************************************************************
//void MLPBruteForceNextSolutionGeneration::FreeAllMemory()
//{
//};
////************************************************************************************************
//BaseObject* MLPBruteForceNextSolutionGeneration::pClone()const
//{
//   MLPBruteForceNextSolutionGeneration* p = new MLPBruteForceNextSolutionGeneration(*this);
//   return p;
//};
////************************************************************************************************
//
