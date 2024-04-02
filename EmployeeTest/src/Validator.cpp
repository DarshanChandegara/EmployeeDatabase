#include "include/Helper.h"
#include "include/Regex.h"
#include "gtest/gtest.h"

using namespace utility;

TEST(Validator, mobileValidation) {
	EXPECT_TRUE(validate("8469557424", mobileRegex));
	EXPECT_TRUE(validate("9824412772", mobileRegex));
	EXPECT_FALSE(validate("879865322145", mobileRegex));
	EXPECT_FALSE(validate("879865322", mobileRegex));
}

TEST(Validator, emailValidation) {
	EXPECT_FALSE(validate("", emailRegex));
	EXPECT_FALSE(validate("darshan#gmail.comesd", emailRegex));
	EXPECT_TRUE(validate("darshan@gmail.com", emailRegex));
	EXPECT_TRUE(validate("darshan@ac.in", emailRegex));
}

TEST(Validator, genderValidation) {
	EXPECT_TRUE(validate("Male", genderRegex));
	EXPECT_TRUE(validate("Female", genderRegex));
	EXPECT_TRUE(validate("Other", genderRegex));
	EXPECT_TRUE(validate("male", genderRegex));
	EXPECT_TRUE(validate("other", genderRegex));
	EXPECT_TRUE(validate("female", genderRegex));
	EXPECT_FALSE(validate("mAle", genderRegex));
	EXPECT_FALSE(validate("feMale", genderRegex));
}

TEST(validator, dateValidation) {
	EXPECT_TRUE(validate("1-2-2021", dateRegex));
	EXPECT_TRUE(validate("01-2-2021", dateRegex));
	EXPECT_TRUE(validate("1-02-2021", dateRegex));
	EXPECT_TRUE(validate("26-08-2002", dateRegex));
	EXPECT_FALSE(validate("01-02-021", dateRegex));
	EXPECT_FALSE(validate("32-02-2021", dateRegex));
	EXPECT_FALSE(validate("28-13-2021", dateRegex));
	EXPECT_FALSE(validate("30-02-2021", dateRegex));
}

TEST(Validator, idValidation) {
	EXPECT_TRUE(validate("302", idRegex));
	EXPECT_TRUE(validate("501", idRegex));
	EXPECT_TRUE(validate("1", idRegex));
	EXPECT_TRUE(validate("12", idRegex));
	EXPECT_FALSE(validate("1245", idRegex));
	EXPECT_FALSE(validate("65565", idRegex));
}

TEST(Validator, alphaValidation) {
	EXPECT_FALSE(validate("fsdhshgf0hghjfdgffd", alphaRegex));
	EXPECT_FALSE(validate("darshan@", alphaRegex));
	EXPECT_FALSE(validate("dars.han", alphaRegex));
	EXPECT_TRUE(validate("darshan", alphaRegex));
	EXPECT_TRUE(validate("DAARshan", alphaRegex));
}


TEST(Validator, digitValidation) {
	EXPECT_FALSE(validate("65465d44654454", digitRegex));
	EXPECT_FALSE(validate("654545454@", digitRegex));
	EXPECT_FALSE(validate("545.5465", digitRegex));
	EXPECT_TRUE(validate("98653245", digitRegex));
	EXPECT_TRUE(validate("321", digitRegex));
}

TEST(Validator, salaryValidation) {
	EXPECT_TRUE(validate("65454445", salaryRegex));
	EXPECT_TRUE(validate("65454445.54121", salaryRegex));
	EXPECT_TRUE(validate("0.0", salaryRegex));
	EXPECT_TRUE(validate("0", salaryRegex));
}