
#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Model/Engineer.h"
#include "include/Model/Department.h"
#include "include/Model/Manager.h"
#include "include/Model/Salary.h"


void menu();

int main() {
	Database::getInstance().open("employee.db");
	menu();   
}
