#ifndef _Salary_
#define _Salary_
#include <iostream>

class Salary {
public:

    Salary() = default;
    Salary(int id, int emp_id, float amount, float base_salary, const std::string& date, float bonus)
        : Sid(id), amount(amount), base_salary(base_salary), date(date), bonus(bonus) {}

    int getId() const { return Sid; }
    float getAmount() const { return amount; }
    float getBaseSalary() const { return base_salary; }
    std::string getDate() const { return date; }
    float getBonus() const { return bonus; }

    void setAmount(const float& figure) { amount = figure;  }
    void setBaseSalary(const float& bSalary) { base_salary = bSalary; }
    void setDate(const std::string& str) { date = str; }
    void setBonus(const float& figure) { bonus = figure; }

    void viewSalary();
    void insertSalary();
    void deleteSalary();
    void updateSalary();
    void action();

private:

    int Sid;
    float amount;    
    float base_salary;
    std::string date;
    float bonus;
};

#endif