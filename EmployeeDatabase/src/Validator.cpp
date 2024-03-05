#/*include "../include/Validator.h"

bool Validator::validateEmail(const std::string& email) {
	std::regex emailFormat("(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$)");
	return std::regex_match(email, emailFormat);
}

bool Validator::validateMobile(const std::string& mobile) {
	std::regex mobileFormat("(^ [0] {1}[2] {1}[0 - 9] {7, 9}$)");
	return std::regex_match(mobile, mobileFormat);
}

bool Validator::validateDate(const std::string& date) {
	std::regex dateFormat("^((2000|2400|2800|(19|2[0-9](0[48]|[2468][048]|[13579][26])))-02-29)$|^(((19|2[0-9])[0-9]{2})-02-(0[1-9]|1[0-9]|2[0-8]))$|^(((19|2[0-9])[0-9]{2})-(0[13578]|10|12)-(0[1-9]|[12][0-9]|3[01]))$|^(((19|2[0-9])[0-9]{2})-(0[469]|11)-(0[1-9]|[12][0-9]|30))$");
	return std::regex_match(date, dateFormat);
}*/