#include "../include/Model/Department.h"

void Department::userInput() {
	try {
		std::string msg = " Enter # to leave the field Empty\n"; 
		system("cls");
		setId(stoi(input("Enter Department ID: ", idRegex)));
		setName(input("Enter Department Name: "));
		setManagerId(stoi(input("Enter Department Manager ID: ", idRegex)));
		setDescription();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i; 
	}
}

void Department::viewDepartment() {
	try {
		system("cls");
		std::string query = "select * from Department where ";
		std::string all = "";
		std::cout << "Select the Field on which you want to view the Department\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. id\n";
		std::cout << "2. Dname\n";
		std::cout << "3. manager_id\n";
		std::cout << "4. ALL\n\n";
		int i;
		std::cout << "Enter Choice: ";
		std::cin >> i;
		std::cout << "\n\n";
		std::string tmp;
		while (1) {

			switch (i) {
			case 0:
				return;
				break;
			case 1:
				std::cout << "Enter Did: ";
				std::cin >> tmp;
				query += "id = " + tmp + ";";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 2:
				std::cout << "Enter Dname: ";
				std::cin >> tmp;
				query += "Dname = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 3:
				std::cout << "Enter manager Id: ";
				std::cin >> tmp;
				query += "manager_id = " + tmp + ";";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 4:
				all += "select * from Department ;";
				Database::getInstance().selectQuery(all.c_str());
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				viewDepartment();
				break;
			}
			break;
		}
		int change = sqlite3_changes(Database::getInstance().db);
		if (change == 0) {
			std::cout << "Selected Department is not in database\n";
		}
		std::cout << "Press 0 button to go back to menu \n";
		int g;
		std::cin >> g;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}

void Department::insertDepartment() {
	try { 
		userInput();
		std::string query = "INSERT INTO Department "
			"(id, Dname, manager_id, description) "
			"VALUES (" + std::to_string(Did) + ", '" + Dname + "'," + std::to_string(manager_id) + ", '" + description + "');";
		std::cout << query;   
		Database::getInstance().executeQuery(query.c_str());   
		std::cin >> query;   
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}

void Department::updateDepartment() {

	try {
		system("cls");
		std::string query = "update Department set ";
		std::cout << "Enter the id to update Department\n";
		std::string tmp;
		std::cin >> tmp;
		std::map<std::string, std::string> mp;
		bool check = true;
		int i;
		while (check) {
			system("cls");
			std::cout << "Select the field you want to update \n";
			std::cout << "0. Go Back\n"; 
			std::cout << "1. Department name\n";
			std::cout << "2. manager id\n";
			std::cout << "3. description\n";
			std::cout << "4. toUpdateDatabase\n\n";
			std::string prompt = "Enter the changed value\n";
			std::string value;
			std::cout << "Enter Choice: ";
			std::cin >> i;
			switch (i) {
			case 0:
				return;

			case 1:
				value = input(prompt);
				mp.insert({ "Dname" , value });
				break;

			case 2:
				value = input(prompt, idRegex);
				mp.insert({ "manager_id" , value });
				break;

			case 3:
				setDescription();
				mp.insert({ "description" , description });
				break;

			case 4:
				check = false;
				break;
			}
		}

		auto itr = mp.end();
		itr--;
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			query += it->first + " = ";
			if (it->first == "manager_id") {
				query += it->second + " ";
			}
			else {
				query += "'" + it->second + "' ";
			}

			if (it != itr)
				query += ",";
		}
		query += "where id = " + tmp + " ;";
		//std::cout << query << "\n";

		Database::getInstance().executeQuery(query.c_str());
		int change = sqlite3_changes(Database::getInstance().db);
		if (change == 0) {
			std::cout << "Selected Department is not in database\n";
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}

void Department::deleteDepartment() {

	try {
		system("cls");
		std::string query = "delete from Department where ";
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n";  
		std::cout << "1. Did\n";
		std::cout << "2. Dname\n";
		int i;
		std::cout << "Enter choice: ";
		std::cin >> i;
		std::cout << "\n";
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return; 
			
			case 1:
				std::cout << "Enter Did: ";
				std::cin >> tmp;
				query += "id = " + tmp + ";";
				//std::cout << query; 
				Database::getInstance().executeQuery(query.c_str());
				std::cout << "Press 0 To continue\n";  
				std::cin >> i;  
				break;
			case 2:
				std::cout << "Enter Dname: ";
				std::cin >> tmp;
				query += "Dname = '" + tmp + "';";
				//std::cout << query;
				Database::getInstance().executeQuery(query.c_str());
				std::cout << "Press 0 To continue\n";
				std::cin >> i;
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				deleteDepartment();
				break;
			}
			break;
		}
		int change = sqlite3_changes(Database::getInstance().db);
		if (change == 0) {
			std::cout << "Selected Department is not in database\n";
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}

void Department::action() noexcept {
	auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Insert\n";
		std::cout << "3. Update\n";
		std::cout << "4. Delete\n";
		std::cout << "5. Go to Main Menu\n\n";

		std::cout << "Enter Choice : ";
		int i;
		std::cin >> i;
		switch (i) {
		case 1:
			viewDepartment();
			break;

		case 2:
			insertDepartment();
			break;

		case 3:
			updateDepartment();
			break;

		case 4:
			deleteDepartment();
			break;

		case 5:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}
}