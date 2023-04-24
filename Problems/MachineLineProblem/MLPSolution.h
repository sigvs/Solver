#ifndef hpp_MLPSolution_hpp
#define hpp_MLPSolution_hpp

#include "..\..\Algoithms\Common\IterationSolution.h"
#include "..\..\Interface\IArray.h"
#include "MLProblem.h"

class MLPSolution:public IterationSolution, IArray<long>
{
    protected:
        int _BufferNumber;
        long* _BufferSize;
        double _Debit;
        double _AverageStock;
	public:
		MLPSolution();
		MLPSolution(const MLPSolution&);
		void operator = (const MLPSolution&);
		virtual ~MLPSolution();

		void GetMemory();
		void FreeMemory();

		virtual void SetValue(ISolver*);

		virtual void SetBufferNumber(int);
		virtual int GetBufferNumber()const;

        long& BufferSize(int);

        long BufferSumm()const;
        double Debit()const;
        double AverageStock()const;

        virtual bool bEqual (void*)const;
        virtual bool bNotEqual (void*)const;
        virtual bool bWorse (void*)const;
        virtual bool bBetter (void*)const;
        virtual bool bWorseOrEqual (void*)const;
        virtual bool bBetterOrEqual (void*)const;
        virtual bool bIdentical(void*)const;
        virtual bool bNotIdentical(void*)const;

		virtual void Generate(void*, ...);

        friend ofstream& operator <<(ofstream& , MLPSolution&);
//        friend ifstream& operator >>(ifstream& , tpMLProblem&);
        friend ostream& operator <<(ostream& , MLPSolution&);

        virtual void Remove();
        virtual void Copy(const void*);
		virtual void* Clone()const;

        // Унаследовано через IArray
        virtual long GetElement(size_t i) override;
        virtual void SetElement(size_t i, long v) override;
        virtual size_t GetElementCount();
};
#endif
