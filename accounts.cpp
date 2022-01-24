#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "accounts.h"


// Constructor definition
Accounts::Accounts() :
	username(""), 
	password(""),
	alpha_and_nums("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"),
	numbers("0123456789"),
	master_filename("usernames_and_passwords.txt"),
	required_username_length(8),
	required_letter_count(2),
	required_password_length(8) {}

int Accounts::letter_count(std::string word) const {
	int count = 0;
	for (unsigned int i = 0; i < word.size(); ++i) {
		if (isalpha(word[i]))
			++count;
	}
	return count;
}

bool Accounts::special_character(std::string word) const {
	bool special_character = false;
	for (char c : word) {
		if (ispunct(c)) {
			special_character = true;
			break;
		}
	}
	return special_character;
}

std::vector<std::string> Accounts::read_users() const {
	std::vector<std::string> accounts;
	std::ifstream infile(get_master_filename());
	if (infile) {
		std::string line;
		while (getline(infile, line)) {
			accounts.push_back(line);				// Copy accounts from the file to the vector
		}
	}
	infile.close();
	return accounts;
}

std::string Accounts::verify_username() const {
	std::string new_username;
	bool is_valid = true;
	do {
		is_valid = true;
		std::cout << "Enter a username: ";
		getline(std::cin, new_username);

		// Remove whitespace from front
		int first_char = new_username.find_first_not_of(" \n\t");
		if (first_char > -1)
			new_username = new_username.substr(first_char);

		// Check username length
		if (new_username.length() < get_required_username_length()) {
			std::cout << "Username must be at least " << get_required_username_length() << " characters." << std::endl;
			is_valid = false;
		}

		// Check that username only contains letters or numbers
		int index = new_username.find_first_not_of(get_alpha_and_nums());
		if (index != -1) {
			std::cout << "Username can only contain numbers and letters, with no spaces." << std::endl;
			is_valid = false;
		}

		// Check that username contains at least 2 letters
		if (get_letter_count(new_username) < get_required_letter_count()) {
			std::cout << "Username must contain at least " << get_required_letter_count() << " letters." << std::endl;
			is_valid = false;
		}
		if (!is_valid)
			std::cout << "Please try again." << std::endl << std::endl;

	} while (!is_valid);

	return new_username;
}

std::string Accounts::verify_password() const {
	std::string new_password;
	bool valid_password = true;
	do {
		valid_password = true;

		std::cout << "Enter a password: ";			// Will look into preventing password
		getline(std::cin, new_password);			// from echoing to the screen.

		if (new_password.length() < get_required_password_length()) {
			std::cout << "Password must be at least " << get_required_password_length() << " characters." << std::endl;
			valid_password = false;
		}

		// Check that password has a number
		int index = new_password.find_first_of(get_numbers());
		if (index == -1) {
			std::cout << "Password must contain a number." << std::endl;
			valid_password = false;
		}

		// Check for special character
		bool special_char = get_special_character(new_password);

		if (!special_char) {
			std::cout << "Password must contain a special character." << std::endl;
			valid_password = false;
		}
		if (!valid_password) {
			std::cout << "Please try again." << std::endl << std::endl;
		}
	} while (!valid_password);

	return new_password;
}

void Accounts::read_from_file() const {	
	std::ifstream input_file(get_master_filename());
	if (input_file) {
		bool valid = false;
		while (!valid) {
			std::string password_guess;						// Prompt user for master password
			std::cout << "Enter password to view accounts: ";
			getline(std::cin, password_guess);

			if (password_guess == get_master_password()) {
				valid = true;
				std::cout << "USERNAME\t\t"
						  << "PASSWORD" << std::endl;

				
				std::string line;
				while (getline(input_file, line)) {	       // Display usernames and passwords from file
					std::cout << line << std::endl;
				}
				input_file.close();
				std::cout << std::endl;
			}
			else {										  // If password entered is incorrect, restart loop
				std::cout << "Incorrect password. Try again." << std::endl;
			}
		}
	}
	else {												 // If file doesn't open
		std::cout << "Unable to open file." << std::endl << std::endl;	 
	}
}

void Accounts::write_to_file() const {
	std::ofstream output_file(get_master_filename(), std::ios::app);
	if (output_file) {
		output_file << get_username() << "\t\t"
					<< get_password() << "\n";
		output_file.close();
		std::cout << "The username " << get_username() << " has been added." << std::endl;
	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}
}

void Accounts::update_file(std::vector<std::string> accounts) const {
	std::ofstream outfile(get_master_filename(), std::ios::out);
	if (outfile) {
		for (unsigned int i = 0; i < accounts.size(); ++i) {
			outfile << accounts[i] << '\n';					// Update the file after erasing an account
		}
		outfile.close();
	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}
}

void Accounts::delete_item() const {		
	std::vector<std::string> accounts = get_users();	// Copy usernames and passwords from file to this vector
	bool accounts_updated = false;
	char again = 'y';
	while (again == 'y' || again == 'Y') {
		std::string item;
		std::cout << "Enter the username of the account to delete: ";
		getline(std::cin, item);

		for (unsigned int i = 0; i < accounts.size(); ++i) {
			int tab_index = accounts[i].find_first_of("\t");	// Get index of '\t' in each string in accounts since '\t'
																// separates usernames from their passwords on the same line.

			if (accounts[i].substr(0, tab_index) == item) {		// Erase username if user input matches in accounts vector. Since the username and password
				accounts_updated = true;						// are stored on the same line in file, separated by '\t', I'm using .substr to get just
				accounts.erase(accounts.begin() + i);			// the username, not the entire line. Is this an OK way to fix the edge case I had before?			
				std::cout << "Account was erased successfully." << std::endl;
				break;
			}
		}
		if (!accounts_updated)
			std::cout << "Username not found." << std::endl;

		std::cout << "Enter another username? (y/n): ";
		std::cin >> again;
		std::cin.ignore(1000, '\n');
	}
	if (accounts_updated)
		get_update_file(accounts);
}
