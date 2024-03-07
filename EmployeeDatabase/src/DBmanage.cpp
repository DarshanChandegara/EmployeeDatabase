#include "../include/DBmanage.h"

bool Database::open(const char* str) {
	int rc = sqlite3_open(str, &db);

	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
		return false;
	}
	else {
		std::cout << "Database Open Successfully \n";
	}


	const char* sql = "CREATE TABLE IF NOT EXISTS Employee ("
		"Eid INTEGER PRIMARY KEY,"
		"firstname VARCHAR,"
		"lastname VARCHAR,"
		"dob DATE,"
		"mobile VARCHAR,"
		"email VARCHAR,"
		"address VARCHAR,"
		"gender VARCHAR CHECK (gender IN ('Male', 'Female', 'Other')),"
		"doj DATE,"
		"manager_id INTEGER,"
		"department_id INTEGER,"
		"FOREIGN KEY (department_id) REFERENCES Department(id),"
		"FOREIGN KEY (manager_id) REFERENCES Employee(Eid));";

	rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		std::cout << "Table created successfully" << std::endl;
	}

	const char* sql2 = "CREATE TABLE IF NOT EXISTS Department ("
		"id INTEGER PRIMARY KEY,"
		"Dname VARCHAR,"
		"manager_id INTEGER,"
		"description VARCHAR,"
		"FOREIGN KEY (manager_id) REFERENCES Employee(Eid))";

	rc = sqlite3_exec(db, sql2, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		std::cout << "Table created successfully" << std::endl;
	}


	const char* sql3 = "CREATE TABLE IF NOT EXISTS Engineer ("
		"id INTEGER PRIMARY KEY,"
		"programming_language VARCHAR,"
		"specialization VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(Eid) ON DELETE CASCADE )";

	rc = sqlite3_exec(db, sql3, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		std::cout << "Table created successfully" << std::endl;
	}

	const char* sql4 = "CREATE TABLE IF NOT EXISTS Manager ("
		"id INTEGER PRIMARY KEY,"
		"management_experience INTEGER,"
		"project_title VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(Eid) ON DELETE CASCADE)";

	rc = sqlite3_exec(db, sql4, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		std::cout << "Table created successfully" << std::endl;
	}

	const char* sql5 = "CREATE TABLE IF NOT EXISTS Salary ("
		"Sid INTEGER PRIMARY KEY,"
		"amount INTEGER,"
		"base_salary INTEGER,"
		"bonus INTEGER,"
		"FOREIGN KEY (Sid) REFERENCES Employee(Eid) ON DELETE CASCADE)  ";

	rc = sqlite3_exec(db, sql5, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		std::cout << "Table created successfully" << std::endl;
	}

	const char*  pragmaQuery = { "PRAGMA foreign_keys = ON;" };
	executeQuery(pragmaQuery);

	return true;
}

int Database::executeQuery(const char* sql , int count)
{
	int rc = sqlite3_exec(db, sql, callbackOther, &count, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
		return false;
	}
	else
	{
		std::cout << "Query executed successfully" << std::endl;

		return count;
		//return true;
	}


}

bool Database::selectQuery(const char* sql)
{
	int rc = sqlite3_exec(db, sql, callback, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
		return false;
	}
	else
	{
		std::cout << "Query executed successfully" << std::endl;
		return true;
	}
}

bool Database::close() {
	int rc = sqlite3_close(db);

	if (rc != SQLITE_OK) {
		std::cerr << "Database Failed to close\n";
		return false;
	}
	else {
		std::cout << "Database closed Successfully\n";
	}
}

int Database::callback(void* data, int args, char** row, char** col) {
	//std::cout << "Hello from callback function\n";
	for (int i{ 0 }; i < args; i++) {
		std::cout << col[i] << " : " << (row[i] ? row[i] : NULL) << " | ";
	}
	std::cout << "\n";
	
	std::cout << "\n";
	return 0;
}

int Database::callbackOther(void* data, int argc, char** argv, char** azColName) {
	int* count = reinterpret_cast<int*>(data);
	*count = atoi(argv[0]);
	return 0;
}