#ifndef __TableFixture_h__
#define __TableFixture_h__

#include "include/Model/Table.h"
#include "include/DBmanage.h" 
#include "gtest/gtest.h"

class TableFixture : public ::testing::Test {
protected:
	void SetUp() override {
		table = std::make_unique<Model::Table>(); 

		table->setName("Salary"); 
		std::vector<std::array<std::string, 3>> columns;
		columns.reserve(3);

		columns.emplace_back(std::move(std::array<std::string, 3>{"ID", "INT", "NOT NULL UNIQUE PRIMARY KEY"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"baseSalary", "REAL", "NOT NULL"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"bonus", "REAL", "NOT NULL"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"allowance", "REAL"}));
	}

	void TearDown() override {
		std::string_view queryString = "DROP TABLE IF EXISTS Roles";
		DB::Database::getInstance().executeQuery(queryString.data());

		queryString = "DROP TABLE IF EXISTS Salary";
		DB::Database::getInstance().executeQuery(queryString.data()); 
	}

	std::unique_ptr<Model::Table> table; 


	Model::Table t1; 
};

#endif // !__TableFixture_h__