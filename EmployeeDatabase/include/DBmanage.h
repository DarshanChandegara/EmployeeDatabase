#ifndef _DB_
#define _DB_

#include<iostream>
#include "../sqlite/sqlite3.h"

class Database {
	char* errorMsg = 0;

	Database() {}
	~Database() {
		//sqlite3_close(db);
		close();
	}
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

public:
	sqlite3* db{};
	bool open(const char* str);
	bool close();
	bool executeQuery(const char* sql);
	bool selectQuery(const char* sql);
	static Database& getInstance() {
		static Database db;
		return db;
	}
	static int callback(void* data, int args, char** row, char** col);
};

#endif