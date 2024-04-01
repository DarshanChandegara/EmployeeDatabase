#pragma once

#include "../Model/Department.h"
#include<optional>
#include<utility>

std::optional<Model::Department> userinputDepartment();

std::optional<std::pair<std::string, std::string>> viewDepartmentController();

std::optional<Model::Department> updateDepartmentController();

std::optional<Model::Department> deleteDepartmentController();