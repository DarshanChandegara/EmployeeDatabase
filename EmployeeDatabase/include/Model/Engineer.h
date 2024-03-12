#ifndef _Engineer_
#define _Engineer_

#include "Employee.h"
//#include "../DBmanage.h"
class Engineer : public Employee {
public:
    Engineer() = default;
    Engineer(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj,int manager_id, int department_id, const std::string& programming_language,
        const std::string& specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgramming_language(const std::string& lang) { programming_language = lang; }
    void setSpecialization() {
        std::string specs; 
        std::cout << "Enter Specialization: ";
        std::cin.ignore(); 
        std::getline(std::cin, specs); 
        specialization = specs; 
    }

    void viewEngineer();
    void insertEngineer();
    void deleteEngineer();
    void updateEngineer();
    void userInputEngineer();
    void action();

private:

    std::string programming_language;
    std::string specialization;
};
#endif