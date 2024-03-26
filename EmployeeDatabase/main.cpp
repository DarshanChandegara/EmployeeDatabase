#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Helper.h"
#include "include/LOG/log.h"
#include "include/LOG/logger.h"
#include "include/Model/Table.h"

using namespace utility;

void menu();

int main() {
	//logging::default_logger()->setFileFlag(true); 
	DB::Database::getInstance().open("employee.db");
	auto ch{ true };
	//Model::Table t;
	std::optional< Model::Table> t = Model::Table::getTable("demo"); 
	if (t.has_value()) { 
		//t.value().infoTable();  
		//t.value().insertRecord(); 
		//t.value().deleteRecord();  
		//t.value().viewAllRecords();
		t.value().viewRecord();
	}

	
	
	/*while (ch) {
		system("cls");
		std::cout << "------------------------------------> WELCOME TO EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------\n";
		std::cout << "Enter the Opertaion you want to perform\n";
		std::cout << "1. Create Tables\n";
		std::cout << "2. Show Tables\n";
		std::cout << "3. Delete Tables\n";
		std::cout << "4. Access Table\n";
		std::cout << "5. Backup Table\n";
		std::cout << "6. Exit\n\n";

		int i;
		i = std::stoi(input("Enter Choice: " , std::regex{"[1-6]"}));
		switch (i) {
		case 1 :
			t.createTable();
			break;

		case 2:
			t.showTables();
			break;

		case 3:
			t.deleteTable();
			break;

		case 4:
			menu();
			break;
		
		case 5:
			DB::Database::getInstance().writeCSV(); 
			break;

		case 6:
			ch = false;
			break;

		default:
			std::cout << "Enter valid input: \n";
		}
	}*/
}
