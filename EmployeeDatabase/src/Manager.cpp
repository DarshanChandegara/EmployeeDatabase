#include "../include/Model/Manager.h"

void Manager::userInputManager() {
	userInputEmployee();
	setManagementExperience(std::stoi(input("Enter Management Experience: ")));
	setProjectTile(input("Enter Project Title: "));
}

void Manager::viewManager() {
	std::string query1 = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and ";
	std::string all = "";
	std::string join = "";
	std::cout << "Select the Field on which you want to view the Manager\n";
	std::cout << "1. Mid\n";
	std::cout << "2. fname\n";
	std::cout << "3. email\n";
	std::cout << "4. department name\n";
	std::cout << "5. Project Title\n";
	std::cout << "6. ALL\n";
	int i;
	cin >> i;
	std::string tmp1;
	while (1) {
		switch (i) {
		case 1:
			std::cout << "Enter Mid: ";
			cin >> tmp1;
			query1 += "Employee.Eid = " + tmp1 + ";";
			Database::getInstance().selectQuery(query1.c_str());
			break;
		case 2:
			std::cout << "Enter fname: ";
			cin >> tmp1;
			query1 += "Employee.firstname = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query1.c_str());
			break;
		case 3:
			std::cout << "Enter email: ";
			cin >> tmp1;
			query1 += "Employee.email = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query1.c_str());
			break;
		case 4:
			std::cout << "Enter departmaent name: ";
			cin >> tmp1;
			join += "SELECT Emp1loyee.* FROM Emp1loyee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + tmp1 + "' ;";
			//std::cout << join;
			Database::getInstance().selectQuery(join.c_str());
			break;
		case 5:
			std::cout << "Enter Project title: ";
			cin >> tmp1;
			query1 += "Employee.project_title = '" + tmp1 + "';";
			Database::getInstance().selectQuery(query1.c_str());
			break;
		case 6:
			all += "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid";
			Database::getInstance().selectQuery(all.c_str());
			break;
		default:
			std::cout << "Enter valid field\n";
			viewManager(); 
			break;
		}
		break;
	}
}

void Manager::insertManager() {
	userInputManager(); 

	insertEmployee(); 
	std::string query = ""; 
	query += "INSERT INTO Manager VALUES ( " + to_string(getId()) + ", " + std::to_string(getManagementExperience()) + " , ' " + getProjectTitle() + " ') ;"; 
	//std::cout << query << "\n";
	Database::getInstance().executeQuery(query.c_str());  
}

void Manager::updateManager() {
	std::string query1 = "update Employee set ";
	std::string query2 = "update Manager set ";
	std::cout << "Enter the Eid to update Employee\n";
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
		std::cout << "11. Project Title\n";
		std::cout << "12. managetment Experience \n";
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
			mp2.insert({ "project_title" , value });
			break;

		case 12:
			value = input(promp1t); 
			mp2.insert({ "management_experience" , value });
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
		query2 += it->first + " = "; 
		if (it->first == "management_experience") {
			query2 += it->second + " "; 
		}
		else { 
			query2 += "'" + it->second + "' "; 
		}
		if (it != itr2)
			query2 += ",";
	}

	query1 += " where Eid = " + tmp1 + " ;";
	query2 += " where id = " + tmp1 + " ;";
	//std::cout << query1 << "\n";
	//std::cout << query2 << "\n";

	Database::getInstance().executeQuery(query1.c_str()); 
	Database::getInstance().executeQuery(query2.c_str()); 
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Emp1loyee is not in database\n";
	}
}

void Manager::deleteManager() {
	deleteEmployee(); 
}

void Manager::action() {

}