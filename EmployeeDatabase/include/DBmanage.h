#ifndef _DB_
#define _DB_

#include<iostream>
#include <iomanip>
#include "../sqlite/sqlite3.h"

class Database {
	char* errorMsg = 0;

	Database() = default; 
	~Database() {
		//sqlite3_close(db);
		close();
	}
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

public:
	sqlite3* db{};
	sqlite3_stmt* stmt {};
	bool open(const char* str);
	bool close();
	int executeQuery(const char* sql , int count = 0);
	bool selectQuery(const char* sql);
	static Database& getInstance() {
		static Database db;
		return db;
	}
	static int callback(void* data, int args, char** row, char** col);
	static int callbackOther(void* data, int args, char** row, char** col);
};

#endif