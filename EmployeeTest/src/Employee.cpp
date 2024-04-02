#include "../Fixtures/EmployeeFixture.h"
#include "gtest/gtest.h"

TEST_F(EmployeeFixture, constructionTest) {
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

TEST_F(EmployeeFixture, InsertTest) {
	ASSERT_TRUE(e1.insertEmployee());  // Success
	ASSERT_FALSE(e2.insertEmployee());  // Fail because Employee is already exist  
	ASSERT_FALSE(e3.insertEmployee()); // Fail Beacause Manager is not available  
	ASSERT_FALSE(e4.insertEmployee()); // Fail Beacause Department is not available   
}

TEST_F(EmployeeFixture, ViewTest) {
	ASSERT_TRUE(emp.viewEmployeeById("Eid","511")); //sucess
	ASSERT_FALSE(emp.viewEmployeeById("Eid","155")); //record not avilable    

	ASSERT_FALSE(emp.viewEmployeeById("manager_id","550")); //record not avilable     
	ASSERT_TRUE(emp.viewEmployeeById("manager_id","2")); //record not avilable 
	 
	ASSERT_TRUE(emp.viewEmployeByDepartmentName("C++")); //record not avilable      
	ASSERT_FALSE(emp.viewEmployeByDepartmentName("QA")); //record not avilable  
	
	ASSERT_TRUE(emp.viewEmloyeeByStringField("firstname" , "Darshan")); //record not avilable      
	ASSERT_FALSE(emp.viewEmloyeeByStringField("firstname", "tushar")); //record not avilable  
}


TEST_F(EmployeeFixture, UpdateTest) {
	ASSERT_FALSE(e6.updateEmployee()); //  updated manager id is not available 
	EXPECT_FALSE(e7.updateEmployee()); // Updated Department id is not avialable 
	EXPECT_FALSE(e8.updateEmployee()); // Enter Employee is not aviable   
	ASSERT_TRUE(e1.updateEmployee()); // Sucess     
}

TEST_F(EmployeeFixture, getEmployeeTest) {
	ASSERT_NE(Model::Employee::getEmployee("2") ,std::nullopt );   
	ASSERT_EQ(Model::Employee::getEmployee("500") ,std::nullopt );  
}

TEST_F(EmployeeFixture, DeleteTest) {
	ASSERT_FALSE(e9.deleteEmployee()); // Fail Beacuse  it is a manager of other employeees   
	ASSERT_FALSE(e8.deleteEmployee()); // Fail because Employee with given id is not available   

	ASSERT_TRUE(e1.deleteEmployee());  // Suceess   
}