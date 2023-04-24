#ifndef hpp_IterationSolution_hpp
#define hpp_IterationSolution_hpp

#include "solution.h"

class IterationSolution:public Solution
{
    private:
     void __FreeMemory();
    public:
        int uIterationNumber;

        IterationSolution();
        IterationSolution(const IterationSolution&);
        void operator = (const IterationSolution&);
        virtual ~IterationSolution();

        virtual void Remove();
        virtual void Copy (const void*);
};
#endif
