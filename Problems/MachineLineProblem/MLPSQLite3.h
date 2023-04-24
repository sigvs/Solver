#ifndef hpp_MLPSQLite3_hpp
#define hpp_MLPSQLite3_hpp

#include "..\BaseSolver\Common.h"
#include "..\SQLite3\sqlite3.h"
#include "MLPSolution.h"

sqlite3* OpenDB(const char *filename) {
	sqlite3 *db;
	int  rc;
	rc = sqlite3_open(filename, &db);
	if (rc) db = NULL;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, "select name from sqlite_master where type = 'table' and name = 'PARETO'", -1, &stmt, NULL);
	if (rc == 0)
	{
		rc = sqlite3_step(stmt);

		if (rc != SQLITE_ROW || (string)((const char*)(sqlite3_column_text(stmt, 0))) != "PARETO")
		{
			rc = sqlite3_exec(db, "CREATE TABLE PARETO(ITERATION  INT NOT NULL, TIME REAL NOT NULL, DATA TEXT NOT NULL, DEBIT REAL NOT NULL, AverageStock REAL NOT NULL, BufferSumm INT NOT NULL)", 0, 0, NULL);
			if (rc != SQLITE_OK) db = NULL;
		}
		rc = sqlite3_finalize(stmt);
	}
	else db = NULL;

	sqlite3_free(NULL);
	return db;
}

#endif
