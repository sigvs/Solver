#include "PMLPEvolutionalAlgorithmDBS.h"
//************************************************************************************************
bool PMLPEvolutionalAlgorithmDBS::_OpenDB(const char *filename) {
	bool rez = true;
	int  rc;
	if (!_db)
	{
		rc = sqlite3_open(filename, &_db);
		if (rc) _db = NULL;
	}

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(_db, "select name from sqlite_master where type = 'table' and name = 'POPULATION'", -1, &stmt, NULL);
	if (rc == 0)
	{
		rc = sqlite3_step(stmt);

		if (rc != SQLITE_ROW || (string)((const char*)(sqlite3_column_text(stmt, 0))) != "POPULATION")
		{
			rc = sqlite3_exec(_db, "CREATE TABLE POPULATION(CURRENTITERATION  INT NOT NULL, FIRSTITERATION  INT NOT NULL, TIME REAL NOT NULL, DATA TEXT NOT NULL, DEBIT REAL NOT NULL, AverageStock REAL NOT NULL, BufferSumm INT NOT NULL)", 0, 0, NULL);
			if (rc != SQLITE_OK) 
			{
				rez = false;
				_db = NULL;
			}
		}
		rc = sqlite3_finalize(stmt);
	}
	else 
	{
		rez = false;
		_db = NULL;
	}


	sqlite3_free(NULL);

	return rez;
}
//************************************************************************************************
bool PMLPEvolutionalAlgorithmDBS::_AddIndivid(int citer, int fiter, float time, MLPSolution *x) {
	int  rc;
	string data;

	for (int j = 0; j < x->GetBufferNumber(); j++)
		data += to_string(x->BufferSize(j)) + ';';

	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(
		_db,
		"INSERT INTO POPULATION(CURRENTITERATION, FIRSTITERATION, TIME, DATA, DEBIT, AverageStock, BufferSumm) VALUES (?,?,?,?,?,?,?)",  // stmt
		-1, // If than zero, then stmt is read up to the first nul terminator
		&stmt,
		0  // Pointer to unused portion of stmt
		)
		!= SQLITE_OK) {
		printf("\nCould not prepare statement.");
		return false;
	}

	if (sqlite3_bind_int(
		stmt,
		1,  // Index of wildcard
		citer
		)
		!= SQLITE_OK) {
		printf("\nCould not bind int.\n");
		return false;
	}

	if (sqlite3_bind_int(
		stmt,
		2,  // Index of wildcard
		fiter
		)
		!= SQLITE_OK) {
		printf("\nCould not bind int.\n");
		return false;
	}

	if (sqlite3_bind_double(
		stmt,
		3,  // Index of wildcard
		time
		)
		!= SQLITE_OK) {
		printf("\nCould not bind double.\n");
		return false;
	}

	if (sqlite3_bind_text(
		stmt,
		4,  // Index of wildcard
		data.c_str(),
		data.length(),
		SQLITE_STATIC
		)
		!= SQLITE_OK) {
		printf("\nCould not bind double.\n");
		return false;
	}

	if (sqlite3_bind_double(
		stmt,
		5,  // Index of wildcard
		x->Debit()
		)
		!= SQLITE_OK) {
		printf("\nCould not bind double.\n");
		return false;
	}

	if (sqlite3_bind_double(
		stmt,
		6,  // Index of wildcard
		x->AverageStock()
		)
		!= SQLITE_OK) {
		printf("\nCould not bind double.\n");
		return false;
	}

	if (sqlite3_bind_int(
		stmt,
		7,  // Index of wildcard
		x->BufferSumm()
		)
		!= SQLITE_OK) {
		printf("\nCould not bind int.\n");
		return false;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		printf("\nCould not step (execute) stmt.\n");
		return false;
	}

	sqlite3_finalize(stmt);

	return true;
}

//************************************************************************************************
void PMLPEvolutionalAlgorithmDBS::ViewCurrentValues(bool forced)
{
	if(forced || (!forced && (_uCurrentIteration%_IterationNumberResultSave==0 || _uCurrentIteration == 1)))
	{
		cout << "Iteration " << _uCurrentIteration << endl;
		cout << "Open DB " << endl;
		_db = NULL;
		if(!_OpenDB(_DBName.c_str())) exit(404);
		PMLPPopulation* parents = (PMLPPopulation*)this->pParents; 
		cout << "Save " << parents->iGetPopulationSize() <<" records"<<endl;
		sqlite3_exec(_db, "BEGIN TRANSACTION", NULL, NULL, NULL);
		for (int i = 0; i < parents->iGetPopulationSize(); i++)
			if (!_AddIndivid(_uCurrentIteration, ((IterationSolution*)parents->pGetIndividPoint(i))->uIterationNumber, ((IterationSolution*)parents->pGetIndividPoint(i))->fSecond(), (MLPSolution*)parents->pGetIndividPoint(i))) exit(403);
		sqlite3_exec(_db, "COMMIT TRANSACTION", NULL, NULL, NULL);
		cout << "Done... " << endl;
		sqlite3_close(_db);
	}

}
//************************************************************************************************
void PMLPEvolutionalAlgorithmDBS::setDBName(string name)
{
	_DBName = name;
};
//************************************************************************************************
void PMLPEvolutionalAlgorithmDBS::setIterationNumberResultSave(int num)
{
	_IterationNumberResultSave = num;
};
//************************************************************************************************
