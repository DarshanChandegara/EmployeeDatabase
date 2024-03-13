#include "../include/Model/Manager.h"
#include "../include/Model/Engineer.h"
#include "../include/Model/Department.h"
#include "../include/Model/Salary.h"

void menu() noexcept {
	auto flag{ true };
	while (flag) {
		system("cls");
		std::cout << "Select The Table You want to interact \n";
		std::cout << "1. Engineer \n";
		std::cout << "2. Manager \n"; 
		std::cout << "3. Department \n"; 
		std::cout << "4. Salary \n"; 
		std::cout << "5. To exit \n\n";
		Engineer e; 
		Manager m; 
		Department d; 
		Salary s;

		std::cout << "Enter Your Choice:  ";
		int i; 
		cin >> i; 
		switch (i) {
		case 1:
			e.action(); 
			break;

		case 2:
			m.action(); 
			break;

		case 3:
			d.action(); 
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