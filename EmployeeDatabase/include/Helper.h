#ifndef _HELPER_
#define _HELPER_

#include<iostream>
#include<regex>


inline std::regex rg{ ".*" };

inline std::string input(const std::string& prompt, const std::regex& r = rg) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (!std::regex_match(input, r)) {
            std::cout << "Enter valid input\n";
        }
        else {
            break; 
        }
    }
    return input;
}
#endif
