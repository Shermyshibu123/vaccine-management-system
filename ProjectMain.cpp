#include "Admin.h"
#include "user.h"
#include "Hospital.h"
#include <regex>
int main()
{
  Admin a;
  User u;
  Hospital h;
  std::string choice = "";
  std::cout << "\n\t\t\t\t*****************************************";
  std::cout << "\n\t\t\t\t   *    VACCINE MANAGEMENT SYSTEM    *";
  std::cout << "\n\t\t\t\t*****************************************";
  while (true)
  {
    std::cout << "\n\n\t\t -->> MAIN MENU <<--";
    std::cout << "\n\n\t\t -->>1. ADMIN";
    std::cout << "\n\t\t -->>2. USER";
    std::cout << "\n\t\t -->>3. HOSPITAL";
    std::cout << "\n\t\t -->>4. EXIT";
    std::cout << "\n\n\t\tEnter Choice: ";
    std::getline(std::cin >> std::ws, choice);
    std::regex s("^[1-4]{1}$");
    if (std::regex_match(choice, s))
    {
      switch (std::stoi(choice))
      {
      case 1:
        a.adminLogin();
        break;
      case 2:
       u.userLogin();
        break;
      case 3:
        h.hospitalLogin(); 
        break;
      case 4:
        exit(0);
      }
    }
    else
    {
      std::cout << "\n\n\t\tInvalid input....Please try again...\n\n";
    }
  }
  return 0;
}

