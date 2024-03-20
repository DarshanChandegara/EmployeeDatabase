#include "pch.h"
#include "include/Helper.h"
#include "include/Model/Employee.h"
#include "Fixtures/EmployeeFixture.h"


TEST(TestCaseName, TestName) {    
  EXPECT_EQ(1, 1);
  ASSERT_EQ(fun(), "darshan");
}

TEST_F(EmployeeFixture , constructionTest) {  
	ASSERT_EQ(emp.getId(), 1);
	ASSERT_EQ(emp.getFirstname(), "Darshan");
	ASSERT_EQ(emp.getLastname(), "Chandegara");
	ASSERT_EQ(emp.getEmail(), "darshan@gmail.com");
	ASSERT_EQ(emp.getMobile(), "8469557424");
	ASSERT_EQ(emp.getDob(), "26-08-2002"); 
	ASSERT_EQ(emp.getDoj(), "01-01-2024"); 
	ASSERT_EQ(emp.getManagerId(), 1); 
	ASSERT_EQ(emp.getDepartmentId(), 1); 
	ASSERT_EQ(emp.getGender(), Gender::Male);
}

TEST_F(EmployeeFixture , View_test) {  
	ASSERT_TRUE(emp.viewEmployee());    
}

TEST_F(EmployeeFixture, InsertTest) {
	//ASSERT_TRUE(e1.insertEmployee());
	ASSERT_FALSE(e1.updateEmployee()); 
}

int main(int argv, char** argc) {
	Database::getInstance().open("employee.db"); 
	testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}