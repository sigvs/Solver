#ifndef hpp_MLPPopulation_hpp
#define hpp_MLPPopulation_hpp

#include "..\..\Algoithms\Evolutional\Population.h"
#include "..\MachineLineProblem\MLPSolution.h"
#include <vector>
class MLPPopulation:public Population
{
    protected:
        vector<MLPSolution> _Individ;
    public:
        MLPPopulation();
        MLPPopulation(const MLPPopulation&);
        void operator = (const MLPPopulation&);
        virtual ~MLPPopulation();

        virtual size_t iGetPopulationSize()const;
        virtual void SetPopulationSize(size_t);
        virtual Solution* pGetIndividPoint(size_t);
        virtual void SetIndividPoint(Solution*, size_t);
        virtual bool bHaveIndivid(Solution*);

        void GetMemory();
        void FreeMemory();

        virtual void Remove();
        virtual void Copy(const void*);
        virtual void* Clone()const;

        friend ofstream& operator <<(ofstream& , MLPPopulation&);
        friend ifstream& operator >>(ifstream& , MLPPopulation&);
        friend ostream& operator <<(ostream& , MLPPopulation&);


        // Унаследовано через Population
        virtual void AppendIndivid(Solution*) override;
        virtual void RemoveIndividByIndex(size_t) override;

};
#endif
