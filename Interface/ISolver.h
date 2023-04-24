#ifndef h_Solver_h
#define h_Solver_h

enum SolverResult {
	SolutionFound,
	SolutionNotFound,
    Unsolvable
};

class ISolver
{
 public:
  virtual SolverResult eSolve(void*, ...)=0;
};
#endif
