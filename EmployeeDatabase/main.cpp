
#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Model/Engineer.h"
#include "include/Model/Department.h"

int main() {
	Database::getInstance().open("employee.db");
	//Employee e1;
	//e1.insertEmployee();
	//e1.insertEmployee(); 
	//e1.viewEmployee();
	//e1.updateEmployee();
	//e1.viewEmployee();
	//e1.deleteEmployee();

	Department d1;
	//d1.insertDepartment(); 
	// 
	//d1.viewDepartment();
	//d1.deleteDepartment();
	//d1.updateDepartment(); 

	Engineer e1;
	e1.insertEngineer();  
	//e1.deleteEngineer();
}
