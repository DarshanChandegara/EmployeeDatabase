
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
	//menu(); 
	Salary s1;
	//s1.userInputSalary();
	//s1.insertSalary(127);
	s1.viewSalary();
	s1.updateSalary();
	s1.viewSalary();


}
