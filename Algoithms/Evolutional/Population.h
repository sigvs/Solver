#ifndef hpp_Population_hpp
#define hpp_Population_hpp

#include "..\..\Interface\IGenerative.h"
#include "..\..\Interface\ISolver.h"
#include "..\..\Interface\IArray.h"
#include "..\Common\Solution.h"

class Population:public IGenerative, IArray<Solution*>, IRemoveable
{
	protected:
		size_t _PopulationSize;
		size_t _WorseSolutionIndex;
		size_t _BestSolutionIndex;

    public:
		Solution* pWorseSolution;
		Solution* pBestSolution;

		virtual void SearchBestSolution() {
			if (_PopulationSize > 0)
			{
				pBestSolution = pGetIndividPoint(0);
				_BestSolutionIndex = 0;
				for (size_t i = 0; i < _PopulationSize; i++)
					if (pGetIndividPoint(i)->bBetter(pBestSolution))
					{
						pBestSolution = pGetIndividPoint(i);
						_BestSolutionIndex = i;
					}
			}
		}

		virtual void SearchWorseSolution() {
			if (_PopulationSize > 0)
			{
				pWorseSolution = pGetIndividPoint(0);
				_WorseSolutionIndex = 0;
				for (size_t i = 0; i < _PopulationSize; i++)
					if (pGetIndividPoint(i)->bWorse(pWorseSolution))
					{
						pWorseSolution = pGetIndividPoint(i);
						_WorseSolutionIndex = i;
					}
			}
		}

		size_t GetWorseSolutionIndex()const {
			return _WorseSolutionIndex;
		};

		size_t GetBestSolutionIndex()const {
			return _BestSolutionIndex;
		};

		virtual size_t GetPopulationSize()const {
			return _PopulationSize;
		};

		virtual void Generate(void* x_, ...)
		{
			void** hx = &x_;
			ISolver* problem = (ISolver*)(hx[0]);
			for (size_t i = 0; i < _PopulationSize; i++)
				pGetIndividPoint(i)->Generate(problem, this);
		}

        virtual void SetPopulationSize(size_t) = 0;

        virtual Solution* pGetIndividPoint(size_t)=0;
        virtual void SetIndividPoint(Solution*, size_t)=0;
		virtual void AppendIndivid(Solution*) = 0;
		virtual void RemoveIndividByIndex(size_t) = 0;

        virtual bool bHaveIndivid(Solution*)=0;


		// Унаследовано через IArray
		virtual Solution* GetElement(size_t i) 
		{
			return pGetIndividPoint(i);
		};

		virtual size_t GetElementCount()
		{
			return _PopulationSize;
		};

		virtual void SetElement(size_t i, Solution* v)
		{
			SetIndividPoint(v, i);
		};

};
#endif
