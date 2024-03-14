#include "../include/Model/Salary.h"
#include "../include/Helper.h"

void action(int j);

void menu() noexcept {
	auto flag{ true };
	Salary s;
	while (flag) { 
		system("cls");
		std::cout << "Select The Table You want to interact \n";
		std::cout << "1. Engineer \n"; 
		std::cout << "2. Manager \n";  
		std::cout << "3. Department \n";  
		std::cout << "4. Salary \n";  
		std::cout << "5. To exit \n\n"; 

		std::cout << "Enter Your Choice:  "; 
		int i;  
		std::cin >> i;  

		switch (i) { 
		case 1:  case 2:  case 3:
			action(i); 
			break;

		case 4:
			s.action(); 
			break;

		case 5:
			flag = false; 
			break;

		default:
			std::cout << "Enter valid table\n"; 
			flag = false; 
		} 
	}
}