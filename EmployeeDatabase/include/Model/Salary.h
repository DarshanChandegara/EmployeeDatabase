#ifndef _Salary_
#define _Salary_
#include <iostream>
#include <map>
#include "../Helper.h"
#include "../DBmanage.h"

class Salary {
public:

    Salary() = default;
    Salary(int id, int emp_id, float amount, float base_salary, float bonus)
        : Sid(id), amount(amount), base_salary(base_salary),  bonus(bonus) {}

    int getId() const { return Sid; }
    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    float getBonus() const { return bonus; }

    void setAmount(float figure) { 
        amount = figure;
    }
    void setBaseSalary(const float& bSalary) { base_salary = bSalary; }
    void setBonus(const float& figure) { bonus = figure; }

    void viewSalary();
    void userInputSalary();
    void insertSalary(int id); 
    void increment(float , std::string);
    void deleteSalary();
    void updateSalary();
    void action();

private:

    int Sid;
    float amount;    
    float base_salary;
    float bonus;
};

#endif