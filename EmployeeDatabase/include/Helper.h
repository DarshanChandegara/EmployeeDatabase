#ifndef _HELPER_
#define _HELPER_

#include<iostream>
#include<regex>

inline std::regex rg{ ".*" };

inline std::string input(const std::string_view& prompt, const std::regex& r = rg) {
	std::string input;
	while (true) {
		std::cout << prompt;
		std::cin >> input;

		if (!std::regex_match(input, r)) {
			std::cout << "\x1b[31mEnter valid input\x1b[0m\n";
		}
		else {
			break;
		}
	}
	if (input == "#") return "";
	return input;
}


#endif