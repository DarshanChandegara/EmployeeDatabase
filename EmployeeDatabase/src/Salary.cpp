#include "../include/Model/Salary.h"

void Salary::userInputSalary() {
	setBaseSalary(std::stof(input("Enter Base Salary: ")));
	setBonus(std::stof(input("Enter Bonus: ")));
	setAmount(base_salary + bonus );
}

void Salary::increment(float percentage , std::string id) {
	float val = 0;
	std::string query = "select amount from Salary where Sid = " + id + " ;";
	int rc = sqlite3_prepare_v2(Database::getInstance().db, query.c_str(), -1, &Database::getInstance().stmt, nullptr);
	rc = sqlite3_step(Database::getInstance().stmt);
	if (rc == SQLITE_ROW) { 
		// Get the value of the 'amount' column
		val = sqlite3_column_double(Database::getInstance().stmt, 0);
		std::cout << "Amount: " << val << std::endl;
	}
	else {
		std::cerr << "No rows returned" << std::endl;
	}

	val = (val + ((val * percentage) / 100));
	amount = val;
	setAmount(val); 

	std::cout << amount << "\n";
}

void Salary::viewSalary() {
	system("cls");
	std::string query = "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee NATURAL JOIN Salary where Eid =  ";
	std::string tmp;
	std::cout << "Enter Eid to view salary :";
	std::cin >> tmp;
	query += tmp + " ;";
	Database::getInstance().selectQuery(query.c_str());
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Employee is not in database\n";
	}
	std::cout << "Press 0 button to go back to menu \n"; 
	int g;
	std::cin >> g;
}

void Salary::insertSalary(int id) {
	std::string query = "insert into Salary values(" + std::to_string(id) + " , " + std::to_string(getAmount()) + " , " + std::to_string(getBaseSalary()) + " ," + std::to_string(getBonus()) + ") ;";
	std::cout << query;
	Database::getInstance().executeQuery(query.c_str());
}

void Salary::updateSalary() {
	system("cls");
	std::string query = "update Salary set ";
	std::cout << "Enter the Eid to update Salary : ";
	std::string tmp;
	std::cin >> tmp;
	std::map<std::string, std::string> mp1;
	bool check = true;
	int i;
	while (check) {
		system("cls");
		std::cout << "Select the field you want to update \n";
		std::cout << "1. Base Salary\n";
		std::cout << "2. Bonus\n";
		std::cout << "3. Increment\n";
		std::cout << "4. ToUpdate\n";

		std::string promp1t = "Enter New Value\n";
		std::string value;
		std::cout << "Enter Choice: ";
		std::cin >> i;
		switch (i) {
		case 1:
			value = input(promp1t);
			setBaseSalary(std::stof(value));
			mp1.insert({ "base_salary" , value });
			break;

		case 2:
			value = input(promp1t);
			setBonus(std::stof(value));
			mp1.insert({ "bonus" , value });
			break; 

		case 3:
			value = input("Enter Percantage by which you want to increase the salary :");
			setAmount(base_salary + bonus);
			increment(std::stof(value) , tmp); 
			break;

		case 4:
			check = false;
			break;
		}
	}

	auto itr1 = mp1.end();
	if(mp1.size()!= 0){
		itr1--;
	}
	for (auto it = mp1.begin(); it != mp1.end(); ++it) {
		query += it->first + " = " + it->second + " ,";
	}
	if(mp1.size()!= 0) setAmount(base_salary+ + bonus ); 


	query += " amount = " + std::to_string(getAmount()) + " where Sid = " + tmp + " ;";
	std::cout << query << "\n";


	Database::getInstance().executeQuery(query.c_str());  
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Employee is not in database\n";
	}
}


void Salary::deleteSalary() {

}

void Salary::action() {

}