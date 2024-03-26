#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Helper.h"
#include "include/LOG/log.h"
#include "include/LOG/logger.h"

using namespace utility;

void menu();

int main() {
	logging::default_logger()->setFileFlag(true); 
	DB::Database::getInstance().open("employee.db");
	auto ch{ true };
	while (ch) {
		system("cls");
		std::cout << "------------------------------------> WELCOME TO EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------\n";
		std::cout << "Enter the Opertaion you want to perform\n";
		std::cout << "1. Create Tables\n";
		std::cout << "2. Show Tables\n";
		std::cout << "3. Delete Tables\n";
		std::cout << "4. Access Table\n";
		std::cout << "5. Exit\n\n";

		int i;
		i = std::stoi(input("Enter Choice: " , std::regex{"[1-5]"}));
		switch (i) {
		case 1 :
			DB::Database::getInstance().createTableQuery();
			break;

		case 2:
			DB::Database::getInstance().showTables();
			break;

		case 3:
			DB::Database::getInstance().deleteTableQuery();
			break;

		case 4:
			menu();
			break;

		case 5:
			ch = false;
			break;

		default:
			std::cout << "Enter valid input: \n";
		}
	}
}
