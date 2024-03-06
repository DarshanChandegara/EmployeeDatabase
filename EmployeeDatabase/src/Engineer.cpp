#include "../include/Model/Engineer.h"

void Engineer::userInputEngineer() {
	userInputEmployee();
	setProgramming_language(input("Enter Programming Language: "));
	setSpecialization();
}

void Engineer::viewEngineer() {

}

void Engineer::insertEngineer() {

	userInputEngineer();  
	 
	insertEmployee(); 
	std::string query = "";
	query += "INSERT INTO Engineer VALUES ( " + to_string(getId()) + ", ' " + programming_language + " ' , ' " + specialization + " ') ;";
	Database::getInstance().executeQuery(query.c_str()); 
}

void Engineer::updateEngineer() {

}

void Engineer::deleteEngineer() {
	deleteEmployee();
}

void Engineer::action() {

}