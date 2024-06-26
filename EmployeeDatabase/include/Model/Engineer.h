#ifndef _Engineer_
#define _Engineer_

#include <optional>
#include <utility>
#include "Employee.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

namespace Model {
    class Engineer : public Model::Employee {
    public:
        Engineer() = default;
        Engineer(int id, const std::string_view& firstname, const std::string_view& lastname, const std::string_view& dob,
            const std::string_view& mobile, const std::string_view& email, const std::string_view& address,
            Gender gender, const std::string_view& doj, int manager_id, int department_id, Salary s, const std::string_view& programming_language,
            const std::string_view& specialization)
            : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id, s),
            programming_language(programming_language), specialization(specialization) {}


        std::string getProgrammingLanguage() const { return programming_language; }
        std::string getSpecialization() const { return specialization; }

        void setProgramming_language(const std::string_view& lang) { programming_language = lang; }
        void setSpecialization(const std::string_view& specs) { specialization = specs; }

        bool viewEngineerById(const std::string&, const std::string&) const;
        bool viewEngineerByDepartmentName(const std::string&) const;
        bool viewAllEngineer() const;
        bool viewEngineerByStringField(const std::string&, const std::string&)const;
        bool viewEngineer() const;
        bool insertEngineer() const;
        bool deleteEngineer() const;
        bool updateEngineer() const;
        static std::optional<Engineer> getEngineer(const std::string&);

    private:
        std::string programming_language;
        std::string specialization;
    };
}

#endif