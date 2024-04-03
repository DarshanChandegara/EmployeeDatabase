#include "../../include/Model/Manager.h"
#include "../../include/controllers/managerController.h"

bool Model::Manager::viewManagerById(const std::string& id, const std::string& value) const {
	try {
		std::string query = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and " + id + " = " + value + " ;";

		DB::Database::getInstance().selectQuery(query.c_str());
		if (DB::Database::row == 0) {
			logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Manager with " + id + ": " + value + " is not in database");
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

bool Model::Manager::viewManagerByDepartmentName(const std::string& value) const {
	try {
		std::string query = "SELECT e.*, eng.* FROM Employee e INNER JOIN Manager eng ON e.Eid = eng.id INNER JOIN Department dept ON e.department_id = dept.id WHERE dept.Dname = '" + value + "' ;";

		DB::Database::getInstance().selectQuery(query.c_str());
		if (DB::Database::row == 0) {
			logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Manager with Department Name: " + value + " is not in database");
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

bool Model::Manager::viewAllManager() const {
	try {
		std::string query = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid;";
		DB::Database::getInstance().selectQuery(query.c_str());
		if (DB::Database::row == 0) {
			logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Managers are not in database");
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

bool Model::Manager::viewManagerByStringField(const std::string& id, const std::string& value) const {
	try {
		std::string query = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and " + id + " = '" + value + "' ;";

		DB::Database::getInstance().selectQuery(query.c_str());
		if (DB::Database::row == 0) {
			logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Manager with " + id + ": " + value + " is not in database");
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

bool Model::Manager::viewManager() const {

	try {
		std::string query;

		auto tmp = viewManagerController(); 

		if (tmp.has_value()) { 
			auto& [field, value] = tmp.value(); 
			if (field == "Eid" || field == "manager_id") {
				viewManagerById(field , value);
				//query += "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and " + field + " = " + value + " ;";
			}
			else if (field == "all") {
				viewAllManager();
				//query += "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid;";
			}
			else if (field == "Dname") {
				viewManagerByDepartmentName(value);
				//query += "SELECT e.*, eng.* FROM Employee e INNER JOIN Manager eng ON e.Eid = eng.id INNER JOIN Department dept ON e.department_id = dept.id WHERE dept.Dname = '" + value + "' ;";
			}
			else {
				viewManagerByStringField(field , value);
				//query += "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and " + field + " = '" + value + "' ;";
			}

			return true;
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

bool Model::Manager::insertManager() const {
	try {

		if (auto ch = insertEmployee(); ch) {  
			std::string query = ""; 
			query += "INSERT INTO Manager VALUES ( " + to_string(getId()) + ", " + std::to_string(management_experience) + " , ' " + project_title + " ') ;";

			int rc = DB::Database::getInstance().executeQuery(query.c_str()); 

			if (rc == 0) {
				std::cout << "\x1b[32m Manager Inserted successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("[Success]", "Manager Added for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33m Entered Manager is already exist\x1b[0m\n\n";
				logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Manager with Id: " + std::to_string(getId()) + " is failed to insert");
				waitMenu(); 
				return false;
			}
		}
		else {
			return false;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
	return false;
}

bool Model::Manager::updateManager() const {
	try { 
		if (auto ch = updateEmployee(); ch) {  

			std::string query = "update Manager set management_experience = " + std::to_string(management_experience)+" , project_title = '" + project_title + "' where id = " + std::to_string(getId()) + " ;"; 

			int rc = DB::Database::getInstance().executeQuery(query.c_str()); 

			if (rc == 0) {
				std::cout << "\x1b[32m Manager updated successfully\x1b[0m\n\n"; 
				waitMenu();
				logging::Info("[Success]", "Manager updated for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33m  You can not assign value beacuse entered manager or department is not in particular table \x1b[0m\n\n";
				logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", "Manager with Id: " + std::to_string(getId()) + " is failed to update");
				waitMenu();
				return false;
			}
			return false;
		}
		else {
			std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
			waitMenu();
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
	return false;
}

bool Model::Manager::deleteManager() const {

	try {
		return deleteEmployee();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
} 
	
std::optional<Model::Manager> Model::Manager::getManager(const std::string & id) {
	Manager e; 
	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		Manager* e1 = static_cast<Manager*>(data);
		e1->setId(argv[0] ? std::stoi(argv[0]) : -1);
		e1->setFirstname(argv[1] ? argv[1] : "");
		e1->setLastname(argv[2] ? argv[2] : "");
		e1->setDob(argv[3] ? argv[3] : "");
		e1->setMobile(argv[4] ? argv[4] : "");
		e1->setEmail(argv[5] ? argv[5] : "");
		e1->setAddress(argv[6] ? argv[6] : "");
		if (argv[7] == "Male") e1->setGender(Gender::Male);
		else if (argv[7] == "Female") e1->setGender(Gender::Female);
		else e1->setGender(Gender::Other);
		e1->setDoj(argv[8] ? argv[8] : "");
		e1->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
		e1->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);
		e1->setManagementExperience(argv[12] ? std::stoi(argv[12]) : -1);
		e1->setProjectTile(argv[13] ? argv[13] : "");  

		return 0;
		};

	std::string selectQuery = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and Employee.Eid = " + id + " ;";

	try {
		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &e, 0);
		if (e.getId() == 0) return std::nullopt;
	}
	catch (...) {
		return std::nullopt;
	}

	//std::cout << e.getId(); 
	return e;
}