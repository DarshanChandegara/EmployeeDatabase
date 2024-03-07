#include "../include/Model/Engineer.h"

void Engineer::userInputEngineer() {
	userInputEmployee();
	setProgramming_language(input("Enter Programming Language: "));
	setSpecialization();
}

void Engineer::viewEngineer() {
	std::string query = "SELECT * FROM Emp1loyee INNER JOIN Engineer ON Engineer.id = Emp1loyee.Eid and ";
	std::string all = "";
	std::string join = "";
	std::cout << "Select the Field on which you want to view the Emp1loyee\n";
	std::cout << "1. Eid\n";
	std::cout << "2. fname\n";
	std::cout << "3. email\n";
	std::cout << "4. department name\n";
	std::cout << "5. Manager Id\n";
	std::cout << "6. ALL\n";
	int i;
	cin >> i;
	std::string tmp1;
	while (1) {
		switch (i) {
		case 1:
			std::cout << "Enter Eid: ";
			cin >> tmp1;
			query += "Emp1loyee.Eid = " + tmp1 + ";";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 2:
			std::cout << "Enter fname: ";
			cin >> tmp1;
			query += "Emp1loyee.firstname = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 3:
			std::cout << "Enter email: ";
			cin >> tmp1;
			query += "Emp1loyee.email = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 4:
			std::cout << "Enter departmaent name: ";
			cin >> tmp1;
			join += "SELECT Emp1loyee.* FROM Emp1loyee JOIN Department ON Emp1loyee.department_id = Department.id WHERE Dname = '" + tmp1 + "' ;";
			//std::cout << join;
			Database::getInstance().selectQuery(join.c_str());
			break;
		case 5:
			std::cout << "Enter Manager Id: ";
			cin >> tmp1;
			query += "Emp1loyee.manager_id = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 6:
			all += "SELECT * FROM Emp1loyee INNER JOIN Engineer ON Engineer.id = Emp1loyee.Eid";
			Database::getInstance().selectQuery(all.c_str());
			break;
		default:
			std::cout << "Enter valid field\n";
			viewEmployee();
			break;
		}
		break;
	}
}

void Engineer::insertEngineer() {

	userInputEngineer();

	insertEmployee();
	std::string query = "";
	query += "INSERT INTO Engineer VALUES ( " + to_string(getId()) + ", ' " + programming_language + " ' , ' " + specialization + " ') ;";
	Database::getInstance().executeQuery(query.c_str());
}

void Engineer::updateEngineer() {
	std::string query1 = "update Employee set ";
	std::string query2 = "update Engineer set ";
	std::cout << "Enter the Eid to update Emp1loyee\n";
	std::string tmp1;
	cin >> tmp1;
	std::map<std::string, std::string> mp1;
	std::map<std::string, std::string> mp2;
	bool check = true;
	int i;
	while (check) {
		std::cout << "Select the field you want to update \n";
		std::cout << "1. FirstName\n";
		std::cout << "2. lastName\n";
		std::cout << "3. DOB\n";
		std::cout << "4. mobile\n";
		std::cout << "5. email\n";
		std::cout << "6. address\n";
		std::cout << "7. gender\n";
		std::cout << "8. doj\n";
		std::cout << "9. managerId\n";
		std::cout << "10. departmentId\n";
		std::cout << "11. programming Language\n";
		std::cout << "12. Specification \n";
		std::cout << "13. ToUpdateDatabase\n";
		std::string promp1t = "Enter New Value\n";
		std::string value;
		cin >> i;
		switch (i) {
		case 1:
			value = input(promp1t);
			mp1.insert({ "firstname" , value });
			break;

		case 2:
			value = input(promp1t);
			mp1.insert({ "lastname" , value });
			break;

		case 3:
			value = input(promp1t, dateRegex);
			mp1.insert({ "dob" , value });
			break;

		case 4:
			value = input(promp1t, mobileRegex);
			mp1.insert({ "mobile" , value });
			break;

		case 5:
			value = input(promp1t, emailRegex);
			mp1.insert({ "email" , value });
			break;

		case 6:
			setAddress();
			mp1.insert({ "address" , getAddress() });
			break;

		case 7:
			value = input(promp1t);
			mp1.insert({ "gender" , value });
			break;

		case 8:
			value = input(promp1t, dateRegex);
			mp1.insert({ "doj" , value });
			break;

		case 9:
			value = input(promp1t, idRegex);
			mp1.insert({ "manager_id" , value });
			break;

		case 10:
			value = input(promp1t, idRegex);
			mp1.insert({ "department_id" , value });
			break;

		case 11:
			value = input(promp1t);
			mp2.insert({ "programming_language" , value });
			break;

		case 12:
			setSpecialization();
			mp2.insert({ "specialization" , getSpecialization() });
			break;

		case 13:
			check = false;
			break;
		}
	}

	auto itr1 = mp1.end();
	auto itr2 = mp2.end();
	itr1--;
	itr2--;
	for (auto it = mp1.begin(); it != mp1.end(); ++it) {
		query1 += it->first + " = ";
		if (it->first == "manager_id" || it->first == "department_id") {
			query1 += it->second + " ";
		}
		else {
			query1 += "'" + it->second + "' ";
		}
		if (it != itr1)
			query1 += ",";
	}

	for (auto it = mp2.begin(); it != mp2.end(); ++it) {
		query2 += it->first + " = '" + it->second + "' ";
		if (it != itr2)
			query2 += ",";
	}

	query1 += " where Eid = " + tmp1 + " ;";
	query2 += " where id = " + tmp1 + " ;";
	std::cout << query1 << "\n";
	std::cout << query2 << "\n";

	Database::getInstance().executeQuery(query1.c_str()); 
	Database::getInstance().executeQuery(query2.c_str()); 
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Emp1loyee is not in database\n";
	}
}

void Engineer::deleteEngineer() {
	deleteEmployee();
}

void Engineer::action() {

}