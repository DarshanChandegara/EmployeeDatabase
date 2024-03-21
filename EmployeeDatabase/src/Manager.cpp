#include "../include/Model/Manager.h"

void Manager::userInputManager() {

	try {
		std::string msg = " Enter # to leave the field Empty\n";
		system("cls");
		userInputEmployee();
		setManagementExperience(std::stoi(input("Enter Management Experience: " + msg)));
		setProjectTile();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

bool Manager::viewManager() {

	try {
		system("cls");
		std::string query1 = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and ";
		std::string all = "";
		std::string join = "";
		std::cout << "Select the Field on which you want to view the Manager\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Mid\n";
		std::cout << "2. fname\n";
		std::cout << "3. email\n";
		std::cout << "4. department name\n";
		std::cout << "5. Project Title\n";
		std::cout << "6. ALL\n\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-6]" }));
		std::string tmp1;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Mid: ";
				cin >> tmp1;
				query1 += "Employee.Eid = " + tmp1 + ";";

				break;
			case 2:
				std::cout << "Enter fname: ";
				cin >> tmp1;
				query1 += "Employee.firstname = '" + tmp1 + "';";
				break;
			case 3:
				std::cout << "Enter email: ";
				cin >> tmp1;
				query1 += "Employee.email = '" + tmp1 + "';";
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
		if (i != 4 && i != 6) {
			int rc = Database::getInstance().selectQuery(query1.c_str());
		}
		if (Database::row == 0) {
			return false;
		}
		waitMenu();
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Manager::insertManager() {
	try {
		system("cls");
		std::cout << "If you want to go back press 0 Otherwise press 1\n"; 
		int i;
		if (std::cin >> i;  i == 0) {
			return true;
		}
		userInputManager();

		if (auto ch = insertEmployee(); ch) {
			std::string query = ""; 
			query += "INSERT INTO Manager VALUES ( " + to_string(getId()) + ", " + std::to_string(getManagementExperience()) + " , ' " + getProjectTitle() + " ') ;"; 
			//std::cout << query << "\n";
			int rc = Database::getInstance().executeQuery(query.c_str()); 
			if (rc == 0) {
				std::cout << "Manager inserted successfully\n\n";
				waitMenu(); 
				return true;
			}
			else if (rc == 19) {
				std::cout << "Entered Manager is already exist\n\n"; 
				waitMenu(); 
				return false;
			}
		}
		else {
			return false;
		}
		
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Manager::updateManager() {

	try {
		system("cls");
		std::string query1 = "update Employee set ";
		std::string query2 = "update Manager set ";
		setId(std::stoi(input("Enter the Mid to update Manager : ")));

		std::string select = "select * from Manager where id = " + std::to_string(getId()) + " ;"; 
		Database::getInstance().selectQuery(select.c_str()); 
		if (Database::row == 0) { 
			std::cout << "Entered Manager is not in database\n\n";
			std::cout << "Press 0 to continue\n";  
			int i;
			std::cin >> i; 
			return false;
		}
		else {
			std::map<std::string, std::string> mp1;
			std::map<std::string, std::string> mp2;
			bool check = true;
			int i;
			while (check) {
				system("cls");
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
				std::cout << "11. Project Title\n";
				std::cout << "12. managetment Experience \n";
				std::cout << "13. ToUpdateDatabase\n\n";
				std::string value;
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-3]$" }));
				switch (i) {
				case 0:
					return true;

				case 1:
					setFirstname(input("Enter firstname: ", alphaRegex));
					mp1.insert({ "firstname" , getFirstname() });
					break;

				case 2:
					setLastname(input("Enter LastName: ", alphaRegex)); 
					mp1.insert({ "lastname" ,  getLastname() }); 
					break;

				case 3:
					setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex)); 
					mp1.insert({ "dob" , getDob() }); 
					break;

				case 4:
					setMobile(input("Enter Mobile: ", mobileRegex)); 
					mp1.insert({ "mobile" , getMobile() }); 
					break;

				case 5:
					setEmail(input("Enter Email: ", emailRegex)); 
					mp1.insert({ "email" , getEmail() }); 
					break;

				case 6:
					setAddress(); 
					mp1.insert({ "address" , getAddress() }); 
					break;

				case 7:
					value = input("Enter Gender (Male/Female/Other: )", genderRegex); 
					mp1.insert({ "gender" , value });
					break;

				case 8:
					setDoj(input("Enter DOJ(dd-mm-yyyy): ", dateRegex));
					mp1.insert({ "doj" , getDoj() });
					break;

				case 9:
					setManagerId(stoi(input("Enter Manager Id: ", idRegex)));
					mp1.insert({ "manager_id" , std::to_string(getManagerId()) });
					break;

				case 10:
					setDepartmentId(stoi(input("Enter Department Id: ", idRegex)));
					mp1.insert({ "department_id" , std::to_string(getDepartmentId()) });
					break;

				case 11:
					setProjectTile();
					mp2.erase("project_title");
					mp2.insert({ "project_title" , project_title });
					break;

				case 12:
					setManagementExperience(std::stoi(input("Enter Management experience: "))); 
					mp2.erase("management_experience");
					mp2.insert({ "management_experience" , std::to_string(getManagementExperience())}); 
					break;

				case 13:
					check = false;
					break;
				}
			}

			auto itr1 = mp1.end();
			auto itr2 = mp2.end();
			if (mp1.size() != 0) itr1--;
			if (mp2.size() != 0) itr2--;
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
			 
			query1 += " where Eid = " + std::to_string(getId()) + " ;";
			query2 += " where id = " + std::to_string(getId()) + " ;"; 
			//std::cout << query1 << "\n"; 
			//std::cout << query2 << "\n"; 
			//std::cin >> query1;

			int rc{};
			if (mp1.size() != 0) {

				rc = Database::getInstance().executeQuery(query1.c_str());
			}

			if (mp2.size() != 0) {

				rc = Database::getInstance().executeQuery(query2.c_str());
			}

			if (rc == 0) {
				std::cout << "Manager updated successfully\n\n";
				waitMenu();
				return true;
			}
			else if (rc == 19) {
				std::cout << "You can not update that value Because entered manager or department is not in particular table\n\n";
				waitMenu();
				return false;
			}
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Manager::deleteManager() {

	try {
		system("cls");
		return deleteEmployee();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

void Manager::action() noexcept {
	/*auto check{ true };
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
			viewManager();
			break;

		case 2:
			insertManager();
			break;

		case 3:
			updateManager();
			break;

		case 4:
			deleteManager();
			break;

		case 5:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}*/
}