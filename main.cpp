#include <iostream>
#include <limits>
#include "accounts.h"

#define CREATEACCOUNT 1
#define VIEWACCOUNTS 2
#define REMOVEACCOUNT 3
#define EXIT 4

void display_menu();


int main()
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Welcome to the accounts application!" << std::endl << std::endl;

    Accounts a;
    
    display_menu();

    int choice = CREATEACCOUNT;                                 
    while (choice != EXIT) {                           
        std::cout << "Enter an option: ";
        std::cin >> choice;
        if (std::cin.fail()) {                                                  // If user enters something other than a number
            std::cout << "Invalid entry. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining data in the buffer
        }
        else {            
            std::cin.ignore(1000, '\n');       
            switch (choice) {
            case CREATEACCOUNT:
                a.set_username(a.verify_username());
                a.set_password(a.verify_password());
                a.write_to_file();
                break;
            case VIEWACCOUNTS:
                a.read_from_file();
                break;
            case REMOVEACCOUNT:
                a.delete_item();
                break;
            case EXIT:
                break;
            default:
                std::cout << "Not a valid entry. Try again." << std::endl;
                break;
            }
        }
    }
    std::cout << "Goodbye!" << std::endl << std::endl;

    return 0;
}

void display_menu() {
    std::cout << "1.  Create new account" << std::endl
              << "2.  View current accounts" << std::endl
              << "3.  Remove an account" << std::endl
              << "4.  Exit" << std::endl << std::endl;
}