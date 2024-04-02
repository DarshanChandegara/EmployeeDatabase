#include "../Fixtures/SalaryFixture.h"
#include "gtest/gtest.h"

TEST_F(SalaryFixture, IncrementTest) {
	double d1 = s1.getBaseSalary();
	s1.increment(25, s1.getId());

	double d2 = d1 + (d1 * 0.25);
	ASSERT_DOUBLE_EQ(s1.getBaseSalary(), d2);
	ASSERT_DOUBLE_EQ(s1.getAmount(), s1.getBaseSalary() + s1.getBonus());
}

TEST_F(SalaryFixture, ViewTest) {
	ASSERT_TRUE(s1.viewSalaryById("511"));
	ASSERT_FALSE(s1.viewSalaryById("550"));
}

TEST_F(SalaryFixture,getSalaryTest) {
	ASSERT_NE(Model::Salary::getSalary("511"), std::nullopt);
	ASSERT_EQ(Model::Salary::getSalary("100"), std::nullopt);
}

TEST_F(SalaryFixture, UpdateTest) {
	ASSERT_FALSE(s3.updateSalary()); // Fail beacuse Sid is not in table
	s2.updateSalary();
	ASSERT_DOUBLE_EQ(s2.getAmount(), s2.getBaseSalary() + s2.getBonus()); // Success base_salary  
	s4.updateSalary();
	ASSERT_DOUBLE_EQ(s4.getAmount(), s4.getBaseSalary() + s4.getBonus()); // Success bonus 
}
