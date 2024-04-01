#pragma once
#include "../Model/Salary.h"
#include<optional>

std::optional<Model::Salary> userInputSalary();

std::optional<Model::Salary> updateSalaryController();

std::optional<std::pair<std::string, std::string>> viewSalaryController();