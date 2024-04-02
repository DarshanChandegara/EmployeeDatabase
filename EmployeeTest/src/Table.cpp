#include "../Fixtures/TableFixture.h"
#include "gtest/gtest.h"

TEST_F(TableFixture, exportTest) {
	ASSERT_TRUE(t1.exportToCsv("Employee" , "BackUp/Employee.csv"));
	ASSERT_TRUE(t1.exportToCsv("Department" , "BackUp/Department.csv"));
	ASSERT_FALSE(t1.exportToCsv("emp" , "BackUp/emp.csv"));
}

TEST_F(TableFixture, getTableTest) {
	ASSERT_NE(Model::Table::getTable("Employee"), std::nullopt);
	ASSERT_NE(Model::Table::getTable("Department"), std::nullopt);
	ASSERT_EQ(Model::Table::getTable("demo"), std::nullopt);
	ASSERT_EQ(Model::Table::getTable("darshan"), std::nullopt);
	ASSERT_NE(Model::Table::getTable("employee"), std::nullopt);
}

TEST_F(TableFixture, getAllTableTest) {
	auto v = Model::Table::getAllTables();

	ASSERT_GE(v.size(), 5);
}