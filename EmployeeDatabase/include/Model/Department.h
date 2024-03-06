#ifndef _Dep_
#define _Dep_


#include <iostream>
#include <string>
#include <map>
#include "../DBmanage.h"
#include "../Helper.h"
#include"../Regex.h"
class Department {
public:
    Department() {}
    Department(int id, const std::string& name, int manager_id, const std::string& description)
        : Did(id), Dname(name), manager_id(manager_id), description(description) {}

    int getId() const { return Did; }
    std::string getName() const { return Dname; }
    int getManagerId() const { return manager_id; }
    std::string getDescription() const { return description; }

    void setId(const int& id1) {
        Did = id1;
    }

    void setName(const std::string& str) {
        Dname = str;
    }

    void setManagerId(const int& mId) {
        manager_id = mId;
    }

    void setDescription() {
        std::string desc;
        std::cout << "Enter description: ";
        std::cin.ignore();
        std::getline(std::cin, desc);
        description = desc;
    }

    void viewDepartment();
    void insertDepartment();
    void deleteDepartment();
    void updateDepartment();
    void userInput();
    void action();

private:

    int Did;
    std::string Dname;
    int manager_id;
    std::string description;
};
#endif