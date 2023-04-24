#ifndef hpp_NSGA2Population_hpp
#define hpp_NSGA2Population_hpp


#include "..\Evolutional\Population.h"
#include "NSGA2Solution.h"
#include <vector>
using namespace std;
enum Criteria {
	Debit,
    BufferSumm,
    AverageStock
};

class NSGA2Population:public Population
{
    protected:
		vector<size_t> _WorseIndividIndex;
		size_t _ChildPopulationSize;
		size_t _Size()const;

        vector<NSGA2Solution*> _Individs;

		vector<vector<size_t>> _Fronts;
		vector<size_t> _FrontSizes;
		size_t _FrontCount;

		void _FillFront(size_t);

		void _CrowdingDistanceByCriteria(Criteria);
		double _IndividDifferenceByCriteria(size_t, size_t, Criteria);
    public:
        NSGA2Population();
        NSGA2Population(const NSGA2Population&);
        void operator = (const NSGA2Population&);
        virtual ~NSGA2Population();

		virtual size_t GetChildPopulationSize()const;

        virtual void SetPopulationSize(size_t);
		virtual void SetChildPopulationSize(size_t);

		virtual Solution* pGetAllIndividPoint(size_t);
        virtual Solution* pGetIndividPoint(size_t);
        virtual void SetIndividPoint(Solution*, size_t);
        virtual bool bHaveIndivid(Solution*);

		virtual void AddIndividToFront(size_t, size_t);
		virtual size_t GetIndividFront(size_t, size_t);
		virtual void ClearFront(size_t);
		virtual size_t FrontSize(size_t);
		virtual size_t FrontCount();

        virtual void AddIndividPoint(Solution*);
        virtual void DeleteIndividPoint(size_t);

        void GetMemory();
        void FreeMemory();

        virtual void Remove();
        virtual void Copy(const void*);
        virtual void* Clone()const;

		friend ofstream& operator <<(ofstream& , NSGA2Population&);
		friend ifstream& operator >>(ifstream& , NSGA2Population&);
		friend ostream& operator <<(ostream& , NSGA2Population&);

		void NonDominatedSort();
		void CrowdingDistance();
		void ReplaceChildIndividsByWorseIndivids();
		void AddChildIndivids(Population*);
};

struct CompareIndividsIndex
{
	NSGA2Population * pop;
	Criteria crt;
	CompareIndividsIndex(NSGA2Population* p, Criteria c) { this->pop = p; this->crt = c; }
	bool operator()(const int& i, const int& j) const {
		NSGA2Solution* ind_i = (NSGA2Solution*)(pop->pGetAllIndividPoint(i));
		NSGA2Solution* ind_j = (NSGA2Solution*)(pop->pGetAllIndividPoint(j));
		switch (crt)
		{
		case Debit:
			return ind_i->Debit() < ind_j->Debit();
			break;
		case BufferSumm:
			return ind_i->BufferSumm() < ind_j->BufferSumm();
			break;
		case AverageStock:
			return ind_i->AverageStock() < ind_j->AverageStock();
			break;
		}
	}
};
#endif
