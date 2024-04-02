#ifndef _REG_
#define _REG_

#include<regex>

namespace utility {
	inline std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,3})");
	inline std::regex mobileRegex(R"([0-9]{10})");
	inline std::regex dateRegex(R"(^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[13-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$)");
	inline std::regex idRegex(R"(\b\d{1,3}\b)");
	inline std::regex alphaRegex(R"(^[a-zA-Z\s]*$)");
	inline std::regex digitRegex(R"(^[0-9]*$)");
	inline std::regex genderRegex(R"(^(Male|Female|Other|male|female|other)$)");
	inline std::regex salaryRegex(R"(^[0-9]+(\.[0-9]+)?$)");
	inline std::regex allRegex{ ".*" };
}


#endif