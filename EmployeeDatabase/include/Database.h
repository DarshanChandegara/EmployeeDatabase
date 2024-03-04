#ifndef _DB_
#define _DB_

#include<iostream>
#include "../sqlite/sqlite3.h"

class Database {
	sqlite3* db;
	char* errorMsg = 0;
	int rc;


	bool open(const char* str) {
		rc = sqlite3_open(str, &db);

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
			"FOREIGN KEY (id) REFERENCES Employee(Eid))";

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
			"FOREIGN KEY (id) REFERENCES Employee(Eid))";

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
			"FOREIGN KEY (Sid) REFERENCES Employee(Eid))";

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

		return true;
	}

	bool executeQuery(const char* sql)
	{
		rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);

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

};


#endif