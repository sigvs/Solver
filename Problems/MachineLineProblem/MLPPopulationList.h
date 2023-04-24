#ifndef hpp_MLPPopulationList_hpp
#define hpp_MLPPopulationList_hpp

#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\MachineLineProblem\MLPSolution.h"
#include <list>
class MLPPopulationList:public Population
{
    protected:
        list<MLPSolution*> _Individ;
    public:
        MLPPopulationList();
        MLPPopulationList(const MLPPopulationList&);
        void operator = (const MLPPopulationList&);
        virtual ~MLPPopulationList();

        virtual size_t iGetPopulationSize()const;
        virtual void SetPopulationSize(size_t);
        virtual Solution* pGetIndividPoint(size_t);
        virtual void SetIndividPoint(Solution*, size_t);
        virtual bool bHaveIndivid(Solution*);

        list<MLPSolution*>::iterator GetIterator(size_t);

        void GetMemory();
        void FreeMemory();

        virtual void Remove();
        virtual void Copy(const void*);
        virtual void* Clone()const;

        friend ofstream& operator <<(ofstream& , MLPPopulationList&);
        friend ifstream& operator >>(ifstream& , MLPPopulationList&);
        friend ostream& operator <<(ostream& , MLPPopulationList&);


        // Унаследовано через Population
        virtual void AppendIndivid(Solution*) override;

        virtual void RemoveIndividByIndex(size_t) override;

};
#endif
