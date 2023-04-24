#ifndef hpp_PMLPEvolutionalAlgorithmDBS_hpp
#define hpp_PMLPEvolutionalAlgorithmDBS_hpp

#include "..\BaseSolver\EvolutionalAlgorithm.h"
#include "..\PMLPHeuristic\PMLPPopulation.h"
#include "..\svsutil\SVSutil.h"
#include "..\SQLite3\sqlite3.h"

class PMLPEvolutionalAlgorithmDBS:public EvolutionalAlgorithm
{
 protected:
	sqlite3* _db;
	string _DBName;
	int _IterationNumberResultSave;
	bool _OpenDB(const char *);
	bool _AddIndivid(int, int, float, MLPSolution *);
 public:
  virtual void ViewCurrentValues(bool forced);
  void setDBName(string name);
  void setIterationNumberResultSave(int num);
};
#endif
