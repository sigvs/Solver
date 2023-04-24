#ifndef hpp_NSGA2Solution_hpp
#define hpp_NSGA2Solution_hpp

#include "..\..\Problems\MachineLineProblem\MLPSolution.h"

using namespace std;

class NSGA2Solution:public MLPSolution
{
    protected:
        long _Rank;
        double _CrowdingDistance;
		size_t _BestIndividCount;
		vector<size_t> _WorseIndividIndex;
		size_t _WorseIndividCount;
	public:
		NSGA2Solution();
		NSGA2Solution(const NSGA2Solution&);
		void operator = (const NSGA2Solution&);
		virtual ~NSGA2Solution();

		bool IsDominant()const;

        long Rank()const;
        double CrowdingDistance()const;

		void SetRank(long);
		void SetCrowdingDistance(double);
		void AddCrowdingDistance(double);

		size_t BestIndividCount()const;
		void SetBestIndividCount(size_t);
		void IncrementBestIndividCount();
		void DecrementBestIndividCount();

		void AddWorseIndividIndex(size_t);
		size_t WorseIndividIndex(size_t);
		void ClearWorseIndivids();
		void SetWorseIndividMaxCount(size_t);
		size_t WorseIndividCount()const;

		virtual void Generate(void*, ...);

		virtual bool bWorse(void*)const;
		virtual bool bBetter(void*)const;
		virtual bool bWorseOrEqual(void*)const;
		virtual bool bBetterOrEqual(void*)const;


        friend ofstream& operator <<(ofstream& , NSGA2Solution&);
//        friend ifstream& operator >>(ifstream& , tpMLProblem&);
        friend ostream& operator <<(ostream& , NSGA2Solution&);

        virtual void Remove();
        virtual void Copy(const void*);
		virtual void* Clone()const;
};
#endif
