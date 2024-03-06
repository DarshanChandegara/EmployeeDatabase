#ifndef _Engineer_
#define _Engineer_

#include "Employee.h"
//#include "../DBmanage.h"
class Engineer : public Employee {
public:
    Engineer() = default;
    Engineer(int id, const std::string& firstname, const std::string& lastname, const std::string& dob,
        const std::string& mobile, const std::string& email, const std::string& address,
        Gender gender, const std::string& doj, float salary, int w_location_id,
        int manager_id, int department_id, const std::string& programming_language,
        const std::string& specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, salary,
             manager_id, department_id),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgramming_language(const std::string& lang) { programming_language = lang; }
    void setSpecialization(const std::string& str) { specialization = str; }


    void viewAllEngineer();
    void viewEngineer();
    void insertEngineer();
    void deleteEngineer();
    void updateEngineer();
    void action();

private:

    std::string programming_language;
    std::string specialization;
};
#endif