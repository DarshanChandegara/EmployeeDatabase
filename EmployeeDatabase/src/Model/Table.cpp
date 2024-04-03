#include "../../include/Model/Table.h"

bool Model::Table::createTable() {
	try {
		system("cls");
		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return false;
		}
		std::string tableName;
		std::optional<std::string> tmp;
		if (tmp = input("Enter table name: ", allRegex); tmp.has_value()) tableName = tmp.value();
		else return false;
		std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
		std::vector<std::string> columns;

		char choice;

		do {
			std::string columnName, columnType, constraints;
			if (tmp = input("Enter column name: ", allRegex); tmp.has_value()) columnName = tmp.value();
			else return false;

			if (tmp = input("Enter column type: ", allRegex); tmp.has_value()) columnType = tmp.value();
			else return false;

			if (tmp = input("Enter column constraints : ", allRegex); tmp.has_value()) constraints = tmp.value();
			else return false;

			columns.push_back(columnName + " " + columnType + " " + constraints);
		
			std::cout << "Add another column? (y/n): ";
			std::cin >> choice; 
			std::cin.get(); 

		} while (choice == 'y' || choice == 'Y');

		for (int i = 0; i < columns.size(); ++i) {
			sql += columns[i];
			if (i < columns.size() - 1) {
				sql += ",";
			}
		}

		auto flag{ true };
		int cnt{ 0 };
		std::string field, refrenceTableName , tableField; 
		while (flag) { 
			std::cout << "Do you want to add Foreign Key (Y/N)?: ";
			std::cin >> choice; 
			std::cin.get();
			if ( (choice == 'y' || choice == 'Y')) { 

				if (tmp = input("Enter the field: ", allRegex); tmp.has_value()) field = tmp.value();
				else return false;

				if (tmp = input("Enter the name of the table from which refrence is taken: ", allRegex); tmp.has_value()) refrenceTableName = tmp.value();
				else return false;

				if (tmp = input("Enter the field of the reference table: ", allRegex); tmp.has_value()) tableField = tmp.value();
				else return false;
				
				sql +=", FOREIGN KEY (" + field + ") REFERENCES " + refrenceTableName + "( " + tableField + ")";
				cnt++;
			}
			else {
				flag = false;
			}
		}
		if (cnt != 0) { 
			std::cout << "Do you want to add on delete cascade (Y/N)? "; 
			std::cin >> choice;
			std::cin.get();
			if (; (choice == 'Y' || choice == 'y')) { 
				sql += " ON DELETE CASCADE";
			}
		}
		
		sql += ");";
		int rc = DB::Database::getInstance().executeQuery(sql.c_str());  
		if (rc == 0) {
			std::cout << "\n\x1b[32mTable created Suceesfully\x1b[0m\n\n";
			logging::default_logger()->log(logging::Log::Level::LevelInfo, "[Sucess]", tableName + " created Sucessfully");
			waitMenu(); 
			return true;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}

} 

void Model::Table::showTables() noexcept {

	std::string showQuery = " SELECT name FROM sqlite_schema ;";

	int rc = DB::Database::getInstance().selectQuery(showQuery.c_str());

	waitMenu();
}
 
bool Model::Table::deleteTable() {

	try {
		system("cls");
		int i;
		int rc;
		std::cout << "Select the operation\n";
		std::cout << "0. To Go Back \n";
		std::cout << "1. Drop Table\n";
		std::cout << "2. Delete Data within table\n\n";
		i = std::stoi(input("Enter choice:", std::regex{ "[0-2]" }).value_or("0"));
		std::string deleteQuery;
		std::string tableName;

		switch (i) {
		case 0:
			return false;
			break;
		case 1:
			if (auto tmp = input("Enter table name: ", allRegex); tmp.has_value()) tableName = tmp.value(); 
			else return false;
			if (tableName == "Employee" || tableName == "Salary" || tableName == "Engineer" || tableName == "Manager" || tableName == "Department") {
				std::cout << " \x1b[31mYou can not delete this Table\x1b[0m\n";
				logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", tableName + " can not deletd");

				waitMenu();
				break;
			}
			deleteQuery = "DROP TABLE " + tableName + ";";
			rc = DB::Database::getInstance().executeQuery(deleteQuery.c_str());

			if (rc == 0) {
				std::cout << "\x1b[32mTable Dropped Succesfully !\x1b[0m \n\n";
				logging::default_logger()->log(logging::Log::Level::LevelInfo, "[Sucess]", tableName + " dropped Sucessfully");

				waitMenu();
				return true;
			}
			break;

		case 2:

			if (auto tmp = input("Enter table name: ", allRegex); tmp.has_value()) tableName = tmp.value();
			else return false;
			if (tableName == "Employee" || tableName == "Salary" || tableName == "Engineer" || tableName == "Manager" || tableName == "Department") {
				std::cout << "\x1b[31mYou can not delete this Table\x1b[0m\n";
				logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", tableName + " can not deletd");

				waitMenu();
				break;
			}
			deleteQuery = "DELETE FROM " + tableName + ";";
			//std::cout << deleteQuery << "\n\n";
			rc = DB::Database::getInstance().executeQuery(deleteQuery.c_str());
			if (rc == 0) {

				std::cout << "\x1b[32mTable Deleted Succesfully !\x1b[0m \n\n";
				logging::default_logger()->log(logging::Log::Level::LevelInfo, "[Sucess]", tableName + " Deleted Sucessfully");

				waitMenu();
				return true;
			}
			break;

		default:
			std::cout << "Wrong Input..!\n\n";
			break;

		}

		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}


}

void Model::Table::infoTable() noexcept {
	std::cout << "\n" << name << "\n";

	std::cout << "+--------------------------+----------------------------------------+" << std::endl;
	for (auto& [key, value] : columnType) {
		std::cout << "|" << std::setw(25) << std::left << key << " | " << std::setw(38) << std::left << (value) << " |" << std::endl;
	}
	std::cout << "+--------------------------+----------------------------------------+" << std::endl;
	waitMenu();
} 

std::optional<Model::Table> Model::Table::getTable(const std::string& tableName) {

	try {
		std::string query = "PRAGMA table_info ( " + tableName + " ) ;";

		Table t;
		t.name = tableName;

		sqlite3_exec(DB::Database::getInstance().db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) mutable -> int {

			auto columns = static_cast<std::map<std::string, std::string>*> (data);

			columns->insert({ argv[1] , argv[2] ? argv[2] : "NULL" });

			return 0;
			}, &t.columnType, &DB::Database::getInstance().errorMsg);

		if (t.columnType.size() == 0) return {};

		return t;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return {};
	}

}

std::vector<Model::Table> Model::Table::getAllTables() {

	std::vector<Model::Table> tables;
	try {

		std::string query = "SELECT name FROM sqlite_master WHERE type = 'table';";

		int rc = sqlite3_exec(DB::Database::getInstance().db, query.c_str(), [](void* data, int argc, char** argv, char** col) mutable -> int {
			auto list = static_cast<std::vector<Model::Table>*>(data);

			auto t = Model::Table::getTable(argv[0]);
			if (t.has_value()) {
				list->push_back(t.value());
			}
			return 0;
			}
		, &tables, &DB::Database::getInstance().errorMsg);

		return tables;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return tables;
	}
}

void Model::Table::writeCSV() {
	//std::filesystem::path p{ "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++\\EmployeeDatabase\\EmployeeDatabase\\BackUp\\" };
	std::filesystem::path p{ "BackUp\\" }; 

	auto tables = getAllTables(); 
	for (auto& table : tables) { 
		std::filesystem::path path = p;  
		path /= table.getname() + ".csv"; 
		//std::cout << path << "\n";  
		if (!exportToCsv(table.getname(), path)) {   
			return; 
		}
	}
	std::cout << "\n\x1b[32m Table BackUp successfull!!!!!\x1b[0m\n\n";
	logging::Info("Table BackUp successfull!!!!!!");
	waitMenu();
}

bool Model::Table::exportToCsv(const std::string_view& tableName, const std::filesystem::path& path) {

	std::ofstream file{ path, std::ios::app};

	auto tmp = Model::Table::getTable(std::string{ tableName }); 
	if (!tmp.has_value()) {
		std::cout << "\x1b[33mTable is not available !!!!\x1b[0m\n";
		logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", std::string{ tableName } + "is not in database");

		waitMenu();
		return false;
	}

	if (!file.is_open()) {
		std::cout << "\x1b[33mFile is unable to open!!!!\x1b[0m\n";
		logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", " csv file of"+ std::string{ tableName } + "is unable to open");

		waitMenu();
		return false;
	}

	std::string query = "select * from " + std::string{ tableName } + ";";
	int rc = DB::Database::getInstance().executeQuery(query.c_str());

	if (rc != 0) {
		std::cout << "\x1b[31mError msg: " << DB::Database::getInstance().errorMsg << "\x1b[0m\n";				
		logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", DB::Database::getInstance().errorMsg);


		waitMenu();
		return false;
	}

	DB::Database::getInstance().stmt = nullptr;

	rc = sqlite3_prepare_v2(DB::Database::getInstance().db, query.c_str(), -1, &DB::Database::getInstance().stmt, nullptr);
	if (rc != 0) {
		std::cout << "\x1b[31mError msg: " << DB::Database::getInstance().errorMsg << "\x1b[0m\n";
		logging::default_logger()->log(logging::Log::Level::LevelError, "[Failure]", DB::Database::getInstance().errorMsg);

		waitMenu();
		return false;
	}

	int columnsCount = sqlite3_column_count(DB::Database::getInstance().stmt);


	file << "\n" << string_rep() << "\n\n";

	for (auto i{ 0 }; i < columnsCount; i++) {
		file << sqlite3_column_name(DB::Database::getInstance().stmt, i);
		if (i != columnsCount - 1) {
			file << ",";
		}
	}
	file << ";\n";

	while (rc = sqlite3_step(DB::Database::getInstance().stmt), rc == 100) {
		for (auto i{ 0 }; i < columnsCount; i++) {
			file << sqlite3_column_text(DB::Database::getInstance().stmt, i);
			if (i != columnsCount - 1) {
				file << ",";
			}
		}
		file << ";\n";
	}

	if (rc == 101) {
		//std::cout << "Table " + std::string{ tableName } + " backup successfull!!!!\n"; 
		logging::Info("Table " + std::string{ tableName } + " backup successfull!!!!");
		return true;
	}
	return false;
}

bool Model::Table::insertRecord() {
	system("cls");

	try {

		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return true;
		}
		row.clear();

		for (auto& [field, type] : columnType) {
			if (std::find(numericType.begin(), numericType.end(), type) != numericType.end()) {
				if (auto tmp = input("Enter " + field + ": ", idRegex); tmp.has_value()) row.insert({ field , tmp.value()}); 
				else {
					std::cout << "\x1b[33m Insertion Failed!!! \x1b[0m\n"; 
					waitMenu(); 
					return false;
				}
			}
			else {
				if (auto tmp = input("Enter " + field + ": ", alphaRegex); tmp.has_value()) row.insert({ field , tmp.value() }); 
				else {
					std::cout << "\x1b[33m Insertion Failed!!! \x1b[0m\n"; 
					waitMenu(); 
					return false;
				}
			}
		}

		std::string query = "insert into " + name + " (";

		for (auto& [field, type] : columnType) {
			query += field + ",";
		}

		query.erase(query.find_last_of(','), 1);

		query += " ) values ( ";

		for (auto& [field, value] : row) {
			if (std::find(numericType.begin(), numericType.end(), columnType[field]) != numericType.end()) {
				query += value + ",";
			}
			else {
				query += "'" + value + "' ,";
			}
		}
		query.erase(query.find_last_of(','), 1);
		query += " ) ; ";

		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 0) {
			std::cout << "\x1b[32mIn " + name + ": Record Inserted successfully!!!!\x1b[0m\n";
			logging::Info("[Success]", name + ": Record Inserted successfully!!!!");
			waitMenu();
			return true;
		}
		else if (rc == 19) {
			std::cout << "\x1b[33mEntered Data is not available in particular table Or entered Record is already exist \x1b[0m\n\n";
			logging::Error("[Failure]", "Entered Data is not available in particular table Or entered Record is already exist in " + getname());
			waitMenu(); 
			return false;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Insertion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}

}

bool Model::Table::updateRecord() {
	system("cls");

	try {

		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return true;
		}
		row.clear();

		auto id = input("Enter id to Update records:", idRegex); 
		if (!id.has_value()) { 
			std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
			waitMenu(); 
			return false;
		}

		std::string select = "select * from "+ name +" where id = " + id.value() + " ;"; 
		DB::Database::getInstance().selectQueryForChecking(select.c_str());  
		if (DB::Database::row == 0) { 
			std::cout << "Entered Record is not in table"+name+"\n\n";
			waitMenu();
			return false;
		}
		else {
			system("cls");
			std::cout << "Enter # to keep the field as it is \n\n";
			std::string tmp;
			for (auto& [field, type] : columnType) {

				if (field == "id") continue;
				if (std::find(numericType.begin(), numericType.end(), type) != numericType.end()) {

					if (auto tmp = input("Enter " + field + ": ", idRegex); tmp.has_value()) {
						if (tmp == "0") continue;
						row.insert({ field , tmp.value() });
					}
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}

				}
				else {
					if (auto tmp = input("Enter " + field + ": ", alphaRegex); tmp.has_value()) {
						if (tmp == "0") continue;
						row.insert({ field , tmp.value() });
					}
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
				}
			}

			std::string query;
			if (row.size() != 0) {
				query += "update " + name + " set ";
				for (auto& [field, value] : row) {
					if (std::find(numericType.begin(), numericType.end(), columnType[field]) != numericType.end()) {
						if (field == "id") continue;
						query += field + "=" + value + ",";
					}
					else {
						query += field + "= '" + value + "' ,";
					}
				}

				query.erase(query.find_last_of(','), 1);

				query += " where id = " + id.value() + ";";
			}


			int rc = DB::Database::getInstance().executeQuery(query.c_str());

			if (rc == 0) {
				std::cout << "\x1b[32min " + name + ": Record updated successfully with id " + id.value() + "\x1b[0m\n";
				logging::Info("[Success]", name + ": Record updated successfully with id " + id.value());
				waitMenu();
				return true;
			}
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}

}

bool Model::Table::deleteRecord() const{
	system("cls");

	try {

		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return true;
		}

		auto id = input("Enter id to delete records:", idRegex);  
		if (!id.has_value()) {
			std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n"; 
			waitMenu(); 
			return false;
		}

		std::string select = "select * from " + name + " where id = " + id.value() + " ;"; 
		DB::Database::getInstance().selectQuery(select.c_str()); 
		if (DB::Database::row == 0) { 
			std::cout << "Entered Record is not in table " + name +"\n\n";
			waitMenu(); 
			return false;
		}
		else {
			std::string query = "delete from " + name + " where id = " + id.value() + " ;"; 

			int rc = DB::Database::getInstance().executeQuery(query.c_str()); 
			if (rc == 0) { 
				int change = sqlite3_changes(DB::Database::getInstance().db); 
				if (change == 0) { 
					std::cout << "\x1b[33m Entered Record is not in database\x1b[0m\n"; 
					waitMenu(); 
					return false;
				}
				else { 
					std::cout << "\x1b[32m Record deleted successfully from " + name + "\x1b[0m\n"; 
					logging::Info("[Success]", name + ": Record deleted successfully with id " + id.value());
					waitMenu(); 
					return true;
				}
			}
			else if (rc == 19) {
				std::cout << "\x1b[33m You can not delete Record because Some other records are dependent on it \x1b[0m\n\n"; 
				logging::Error("[Failure]", "Deletion fail in " + name + "with id " + id.value_or(""));
				waitMenu(); 
				return false;
			}
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}

}

bool Model::Table::viewRecord() const {
	system("cls");
	try {
		auto id = input("Enter id to view records: ", idRegex).value_or("0"); 
		std::string query = "select * from " + name + " where id = " + id + " ;";
		int rc = DB::Database::getInstance().selectQuery(query.c_str());
		waitMenu();
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Table::viewAllRecords()const{
	system("cls");
	try {
		std::string query = "select * from " + name + "; ";
		int rc = DB::Database::getInstance().selectQuery(query.c_str());
		waitMenu();
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

