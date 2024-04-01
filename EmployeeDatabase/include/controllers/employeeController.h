#pragma once
#include "../Model/Employee.h"
#include "salaryController.h"
#include<optional>
#include<utility>

std::optional<Model::Employee> userInputEmployee();

bool userInput(Model::Employee*);

std::optional<std::pair<string, string>> viewEmployeeController();

std::optional<Model::Employee> updateEmployeeController();

std::optional<Model::Employee> deleteEmployeeController();