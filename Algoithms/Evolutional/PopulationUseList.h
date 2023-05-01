#ifndef hpp_PopulationUseList_hpp
#define hpp_PopulationUseList_hpp

#include "Population.h"
#include "..\Common\Solution.h"
#include <list>
using namespace std;

class PopulationUseList:public Population
{
    protected:
        list<Solution*> _Individ;
    public:
        PopulationUseList();
        PopulationUseList(const PopulationUseList&);
        void operator = (const PopulationUseList&);
        virtual ~PopulationUseList();

        virtual size_t iGetPopulationSize()const;
        virtual void SetPopulationSize(size_t);
        virtual Solution* pGetIndividPoint(size_t);
        virtual void SetIndividPoint(Solution*, size_t);
        virtual bool bHaveIndivid(Solution*);

        list<Solution*>::iterator GetIterator(size_t);

        virtual void GetMemory() = 0;
        void FreeMemory();

        virtual void Remove();

        // Унаследовано через Population
        virtual void AppendIndivid(Solution*) override;

        virtual void RemoveIndividByIndex(size_t) override;

};
#endif
