#include "../Fixtures/ManagerFixture.h"
#include "gtest/gtest.h"

TEST_F(ManagerFixture, insertTest) {
	ASSERT_TRUE(m2.insertManager());    // Success    
	ASSERT_TRUE(m3.insertManager());    // Success   

	ASSERT_FALSE(m1.insertManager());  // Fail because Employee is already exist     
	ASSERT_FALSE(m6.insertManager()); // Fail Beacause Department is not available   
	ASSERT_FALSE(m7.insertManager()); // Fail Beacause Manager is not available   
}

TEST_F(ManagerFixture, UpdateTest) {
	ASSERT_FALSE(m6.updateManager()); //  updated department id is not available  
	EXPECT_FALSE(m7.updateManager()); // Updated manager id is not avialable    
	EXPECT_FALSE(m8.updateManager()); // Enter Employee is not aviable      
	ASSERT_TRUE(m9.updateManager()); // Sucess
}

TEST_F(ManagerFixture, ViewTest) {
	ASSERT_TRUE(m1.viewManagerById("Eid", "511")); //sucess
	ASSERT_FALSE(m1.viewManagerById("Eid", "155")); //record not avilable    

	ASSERT_FALSE(m1.viewManagerById("manager_id", "550")); //record not avilable     
	ASSERT_TRUE(m1.viewManagerById("manager_id", "2")); //record not avilable 

	ASSERT_TRUE(m1.viewManagerByDepartmentName("C++")); //record not avilable      
	ASSERT_FALSE(m1.viewManagerByDepartmentName("QA")); //record not avilable  

	ASSERT_TRUE(m1.viewManagerByStringField("firstname", "Zeal")); //record not avilable      
	ASSERT_FALSE(m1.viewManagerByStringField("firstname", "tushar")); //record not avilable  
}

TEST_F(ManagerFixture, getManagerTest) {
	ASSERT_NE(Model::Manager::getManager("511"), std::nullopt); 
	ASSERT_EQ(Model::Manager::getManager("100"), std::nullopt);
}

TEST_F(ManagerFixture, DelelteTest) {
	ASSERT_FALSE(m1.deleteManager()); // Fail beacuse this is a manager of other emloyees 
	ASSERT_FALSE(m10.deleteManager()); // Fail becuse such manager is not available  

	ASSERT_TRUE(m2.deleteManager()); // Success ID
	ASSERT_TRUE(m3.deleteManager()); // Success ID

}