#include "../include/Model/Employee.h"

void Employee::viewEmployee() {
	std::string query = "select * from Employee where ";
	std::string all = "";
	std::string join = "";
	std::cout << "Select the Field on which you want to view the Employee\n";
	std::cout << "1. Eid\n";
	std::cout << "2. fname\n";
	std::cout << "3. email\n";
	std::cout << "4. department name\n";
	std::cout << "5. ALL\n";
	int i;
	cin >> i;
	std::string tmp;
	while (1) {
		switch (i) {
		case 1:
			std::cout << "Enter Eid: ";
			cin >> tmp;
			query += "Eid = " + tmp + ";";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 2:
			std::cout << "Enter fname: ";
			cin >> tmp;
			query += "firstname = '" + tmp + "';";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 3:
			std::cout << "Enter email: ";
			cin >> tmp;
			query += "email = '" + tmp + "';";
			Database::getInstance().selectQuery(query.c_str());
			break;
		case 4: 
			std::cout << "Enter departmaent name: "; 
			cin >> tmp; 
			join += "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + tmp + "' ;";
			//std::cout << join;
			Database::getInstance().selectQuery(join.c_str());  
			break;
		case 5:
			all += "select * from Employee"; 
			Database::getInstance().selectQuery(all.c_str()); 
			break;
		default:
			std::cout << "Enter valid field to delete\n";
			viewEmployee();
			break;
		}
		break;
	}
	
}

void Employee::insertEmployee() {
	//userInputEmployee();  
	std::string query = "INSERT INTO Employee "
		"(Eid, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id) "
		"VALUES (" + std::to_string(Eid) + ", '" + firstname + "', '" + lastname + "', '" + dob + "', '" + mobile + "', '" + email + "', '" + address + "' , '";
	if (gender == Gender::Male) {
		query += "Male";
	}
	else if (gender == Gender::Female) {
		query += "Female";
	}
	else {
		query += "Other";
	}
	query += "' , '" + doj + "', " + std::to_string(manager_id) + ", " + std::to_string(department_id) + "); ";
	
	Database::getInstance().executeQuery(query.c_str()); 
} 

void Employee::updateEmployee() {
	std::string query = "update Employee set ";
	std::cout << "Enter the Eid to update Employee\n";
	std::string tmp;
	cin >> tmp;
	std::map<std::string, std::string> mp;
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
		std::cout << "11. toUpdateDatabase\n";
		std::string prompt = "Enter New Value\n";
		std::string value;
		cin >> i;
		switch (i) {
		case 1:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt); 
			mp.insert({ "firstname" , value });
			break;
			 
		case 2:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt);
			mp.insert({ "lastname" , value });
			break;

		case 3:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, dateRegex); 
			mp.insert({ "dob" , value });
			break;

		case 4:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, mobileRegex); 
			mp.insert({ "mobile" , value });
			break;

		case 5:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, emailRegex); 
			mp.insert({ "email" , value });
			break;

		case 6:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			setAddress();
			mp.insert({ "address" , address });
			break;

		case 7:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt);
			mp.insert({ "gender" , value });
			break;

		case 8:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, dateRegex);  
			mp.insert({ "doj" , value });
			break;

		case 9:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, idRegex);  
			mp.insert({ "manager_id" , value });
			break;

		case 10:
			/*std::cout << "Enter the changed value\n";
			cin >> value;*/
			value = input(prompt, idRegex);  
			mp.insert({ "department_id" , value });
			break;

		case 11:
			check = false;
			break;
		}
	}

	auto itr = mp.end();
	itr--;
	for (auto it = mp.begin(); it != mp.end(); ++it) {
		query += it->first + " = ";
		if (it->first == "manager_id" || it->first == "department_id") {
			query += it->second + " ";
		}
		else {
			query += "'" + it->second + "' ";
		}

		if (it != itr)
			query += ",";
	}
	query += "where Eid = " + tmp + " ;";
	//std::cout << query << "\n";

	Database::getInstance().executeQuery(query.c_str());
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Employee is not in database\n";
	}
}



void Employee::deleteEmployee() {
	std::string query1 = "delete from Employee where ";
	std::string query2 = "delete from Engineer where ";
	//std::string query3 = "delete from Manager where ";
	std::cout << "Select the Field on which you want to perform delete Operation\n";
	std::cout << "1. Eid\n";
	//std::cout << "2. fname\n";
	//std::cout << "3. email\n";
	int i;
	cin >> i;
	std::string tmp;
	while (1) {
		switch (i) {
		case 1:
			std::cout << "Enter Eid: ";
			cin >> tmp;
			query1 += "Eid = " + tmp + ";";
			query2 += "id = " + tmp + ";";
			//query3 += "id = " + tmp + ";";
			Database::getInstance().executeQuery(query1.c_str());
			Database::getInstance().executeQuery(query2.c_str());
			//Database::getInstance().executeQuery(query3.c_str());
			break;
		case 2:
			std::cout << "Enter fname: ";
			cin >> tmp;
			query1 += "firstname = '" + tmp + "';";
			Database::getInstance().executeQuery(query1.c_str());
			break;
		case 3:
			std::cout << "Enter email: ";
			cin >> tmp;
			query1 += "email = '" + tmp + "';";
			query2 += " id = ( select Eid from Employee where Employee.email = '" + tmp + "' );";
			//Database::getInstance().executeQuery(query1.c_str()); 
			//Database::getInstance().executeQuery(query2.c_str());
			break;
		default:
			std::cout << "Enter valid field to delete\n";
			deleteEmployee();
			break;
		}
		break;
	}
	//std::cout << query1 << "\n"; 
	std::cout << query2 << "\n"; 
	//std::cout << query3 << "\n"; 
	int change = sqlite3_changes(Database::getInstance().db);
	if (change == 0) {
		std::cout << "Selected Employee is not in database\n";
	}
}

void Employee::action() {

}

void Employee::userInputEmployee() {
	setId(stoi(input("Enter Eid: ", idRegex)));
	setFirstname(input("Enter FirstName: "));
	setLastname(input("Enter LastName: "));
	setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex));
	setMobile(input("Enter Mobile: ", mobileRegex));
	setEmail(input("Enter Email: ", emailRegex));
	setAddress();

	string gender = input("Enter Gender(Male / Female / Other): ");
	if (gender == "Male") {
		setGender(Gender::Male);
	}
	else if (gender == "Female") {
		setGender(Gender::Female);
	}
	else {
		setGender(Gender::Other);
	}

	setDoj(input("Enter DOJ(dd-mm-yyyy): ", dateRegex));
	setManagerId(stoi(input("Enter Manager Id: ")));
	setDepartmentId(stoi(input("Enter Department Id: ")));
}