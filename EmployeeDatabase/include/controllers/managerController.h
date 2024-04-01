#pragma once

#include "../Model/Manager.h"
#include "employeeController.h"

std::optional<std::pair<std::string, std::string>> viewManagerController();

std::optional<Model::Manager> updateManagerController();