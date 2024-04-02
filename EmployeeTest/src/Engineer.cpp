#include "../Fixtures/EngineerFixture.h" 
#include "gtest/gtest.h"



TEST_F(EngineerFixture, InsertTest) {
	ASSERT_TRUE(eg1.insertEngineer());    // Success  
	ASSERT_FALSE(eng.insertEngineer());  // Fail because Engineer is already exist  
	ASSERT_FALSE(eg2.insertEngineer()); // Fail Beacause Manager is not available  
	ASSERT_FALSE(eg3.insertEngineer()); // Fail Beacause Department is not available  
}

TEST_F(EngineerFixture, ViewTest) {
	ASSERT_TRUE(eg1.viewEngineerById("Eid", "310")); //sucess
	ASSERT_FALSE(eg1.viewEngineerById("Eid", "155")); //record not avilable    

	ASSERT_FALSE(eg1.viewEngineerById("manager_id", "550")); //record not avilable     
	ASSERT_TRUE(eg1.viewEngineerById("manager_id", "2")); //record not avilable 

	ASSERT_TRUE(eg1.viewEngineerByDepartmentName("C++")); //record not avilable      
	ASSERT_FALSE(eg1.viewEngineerByDepartmentName("QA")); //record not avilable  

	ASSERT_TRUE(eg1.viewEngineerByStringField("firstname", "Kalpesh")); //record not avilable      
	ASSERT_FALSE(eg1.viewEngineerByStringField("firstname", "tushar")); //record not avilable  
}

TEST_F(EngineerFixture, UpdateTest) {
	ASSERT_FALSE(eg4.updateEngineer()); //  updated manager id is not available  
	EXPECT_FALSE(eg5.updateEngineer()); // Updated Department id is not avialable      
	EXPECT_FALSE(eg4.updateEngineer()); // Enter Engineer is not aviable      
	ASSERT_TRUE(eng.updateEngineer()); // Sucess         
}

TEST_F(EngineerFixture, getEngineerTest) {
	ASSERT_NE(Model::Engineer::getEmployee("310"), std::nullopt); 
	ASSERT_EQ(Model::Engineer::getEmployee("500"), std::nullopt); 
}

TEST_F(EngineerFixture, DeleteTest) {
	ASSERT_FALSE(eg6.deleteEngineer()); // Fail because Engineer with given id is not available    

	ASSERT_TRUE(eg1.deleteEngineer());  // Suceess  ID     
}

