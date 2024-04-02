#include "gtest/gtest.h"
#include "include/Helper.h"
#include "include/DBmanage.h"

TEST(TestCaseName, TestName) {    
  EXPECT_EQ(1, 1);
  ASSERT_EQ(fun(), "darshan");
}

 
int main(int argv, char** argc) {
	DB::Database::getInstance().open("employee.db");  
	DB::Database::getInstance().createDefaultTables();  
	testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}