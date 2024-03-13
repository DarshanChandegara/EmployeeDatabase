#include "../include/Model/Employee.h"

void Employee::viewEmployee() {

	try {

		std::string query = "select * from Employee where ";
		std::string all = "";
		std::string join = "";
		std::cout << "Select the Field on which you want to view the Employee\n";
		std::cout << "0. Go Back\n"; 
		std::cout << "1. Eid\n";
		std::cout << "2. fname\n";
		std::cout << "3. email\n";
		std::cout << "4. department name\n";
		std::cout << "5. Manager Id\n";
		std::cout << "6. ALL\n\n";
		int i;
		std::cout << "Enter choice: ";
		std::cin >> i;
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return;

			case 1:
				std::cout << "Enter Eid: ";
				std::cin >> tmp;
				query += "Eid = " + tmp + ";";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 2:
				std::cout << "Enter fname: ";
				std::cin >> tmp;
				query += "firstname = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 3:
				std::cout << "Enter email: ";
				std::cin >> tmp;
				query += "email = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 4:
				std::cout << "Enter departmaent name: ";
				std::cin >> tmp;
				join += "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + tmp + "' ;";
				//std::cout << join;
				Database::getInstance().selectQuery(join.c_str());
				break;
			case 5:
				std::cout << "Enter Manager Id: ";
				std::cin >> tmp;
				query += "manager_id = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 6:
				all += "select * from Employee";
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
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
	
}

void Employee::insertEmployee() {
	try {
		  
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
		s.insertSalary(getId());
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
} 

void Employee::updateEmployee() {
	try {


		std::string query = "update Employee set ";
		std::cout << "Enter the Eid to update Employee\n";
		std::string tmp;
		std::cin >> tmp;
		std::map<std::string, std::string> mp;
		bool check = true;
		int i;
		while (check) {
			std::cout << "Select the field you want to update \n";
			std::cout << "0. Go Back\n";  
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
			std::cin >> i;
			switch (i) {
			case 0:
				return;

			case 1:
				value = input(prompt);
				mp.insert({ "firstname" , value });
				break;

			case 2:
				value = input(prompt);
				mp.insert({ "lastname" , value });
				break;

			case 3:
				value = input(prompt, dateRegex);
				mp.insert({ "dob" , value });
				break;

			case 4:
				value = input(prompt, mobileRegex);
				mp.insert({ "mobile" , value });
				break;

			case 5:
				value = input(prompt, emailRegex);
				mp.insert({ "email" , value });
				break;

			case 6:
				setAddress();
				mp.insert({ "address" , address });
				break;

			case 7:
				value = input(prompt);
				mp.insert({ "gender" , value });
				break;

			case 8:
				value = input(prompt, dateRegex);
				mp.insert({ "doj" , value });
				break;

			case 9:
				value = input(prompt, idRegex);
				mp.insert({ "manager_id" , value });
				break;

			case 10:
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
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}



void Employee::deleteEmployee() {
	try {
		system("cls");  
		std::string query1 = "delete from Employee where ";
		std::string s;
		int count1 = 0;
		int count2 = 0;
		int i;
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n"; 
		std::cout << "1. Eid\n";
		std::cout << "2. email\n\n";
		std::cout << "Enter Choice: ";
		std::cin >> i;
		std::cout << "\n";
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return;

			case 1:
				std::cout << "Enter Eid: ";
				std::cin >> tmp;
				query1 += "Eid = " + tmp + ";";

				s += "select count(*) from Employee where Employee.manager_id = " + tmp + ";";

				count1 = 0;
				count1 = Database::getInstance().executeQuery(s.c_str(), count1);
				//std::cout << s << " \n"; 
				//std::cout << "Nunber of employee : " << count1 << "\n"; 

				s = "";
				s += "select count(*) from Department where manager_id = " + tmp + ";";

				count2 = 0;
				count2 = Database::getInstance().executeQuery(s.c_str(), count2);
				//std::cout << s << " \n"; 
				//std::cout << "Number of employee : "<< count2 << "\n";
				if (count1 + count2 != 0) {
					std::cout << "\nYou can't delete this user because he/she is manager of other employees. Please change the manager first\n";
					std::cout << "Press 0 To continue\n\n";
					std::cin >> i;
				}
				else {
					Database::getInstance().executeQuery(query1.c_str());
				}
				break;

			case 2:
				std::cout << "Enter email: ";
				std::cin >> tmp;
				query1 += "email = '" + tmp + "';";
				Database::getInstance().executeQuery(query1.c_str());
				break;

			default:
				std::cout << "Enter valid field to delete\n";
				deleteEmployee();
				break;
			}
			break;
		}
		std::cout << query1 << "\n";
		int change = sqlite3_changes(Database::getInstance().db);
		if (change == 0) {
			std::cout << "Selected Employee is not in database\n";
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}

void Employee::action() noexcept {

}

void Employee::userInputEmployee() {
	try {
		std::string msg = " Enter # to leave the field Empty\n";
		setId(stoi(input("Enter Eid: ", idRegex)));
		setFirstname(input("Enter FirstName: "+msg));
		setLastname(input("Enter LastName: "+msg));
		setDob(input("Enter DOB (dd-mm-yyyy): "+msg, dateRegex));
		setMobile(input("Enter Mobile: "+msg, mobileRegex));
		setEmail(input("Enter Email: "+msg, emailRegex));
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

		setDoj(input("Enter DOJ(dd-mm-yyyy): "+msg, dateRegex));
		setManagerId(stoi(input("Enter Manager Id: ")));
		setDepartmentId(stoi(input("Enter Department Id: ")));
		s.userInputSalary();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Press 0 To continue\n";
		int i;
		std::cin >> i;
	}
}