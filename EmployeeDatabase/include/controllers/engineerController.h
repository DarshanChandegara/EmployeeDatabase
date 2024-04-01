#pragma once
#include "../Model/Engineer.h"
#include "employeeController.h"

std::optional<std::pair<std::string, std::string>> viewEngineerController();

std::optional<Model::Engineer> updateEngineerController();