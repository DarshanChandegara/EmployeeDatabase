
#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Model/Engineer.h"

int main(){
	Database::getInstance().open("employee.db");
	Engineer e1;
	//e1.insertEmployee();
	//e1.viewAllEmployee();
	e1.viewEmployee();
	e1.updateEmployee();
	e1.viewEmployee();
	//e1.deleteEmployee();
}
