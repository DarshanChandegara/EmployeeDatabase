#include "gtest/gtest.h"
#include "include/Helper.h"
#include "include/DBmanage.h"
#include "include/LOG/log.h"
#include "include/LOG/logger.h"

TEST(TestCaseName, TestName) {    
  EXPECT_EQ(1, 1);
  ASSERT_EQ(fun(), "darshan");
}

 
int main(int argv, char** argc) {
	auto l = std::make_shared<logging::Log>("User" , "log.txt");
	logging::set_default_logger(l);
	DB::Database::getInstance().open("employee.db");  
	DB::Database::getInstance().createDefaultTables();  
	testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}