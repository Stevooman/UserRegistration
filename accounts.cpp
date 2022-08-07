#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "accounts.h"



/// <summary>
/// The constructor initializes each private variable using a member initialization list.
/// </summary>
Accounts::Accounts() :
	// Member initialization list
	username(""), 
	password(""),
	alpha_and_nums("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"),
	numbers("0123456789"),
	master_filename("usernames_and_passwords.txt"),
	required_username_length(8),
	required_letter_count(2),
	required_password_length(8) {}


/// This function counts the number of letters in a word.
/// 
/// This function retrieves the number of letters in the provided string parameter
/// by looping through each character in the word, and incrementing a count variable
/// if the character at index *i* is an alphabet character.
/// The function then returns the int count variable.
/// 
/// @param word is the word whose letters will be counted.
/// 
/// @returns The number of letters in the word.
/// 
int Accounts::letter_count(std::string word) const {
	int count = 0;
	for (unsigned int i = 0; i < word.size(); ++i) {
		if (isalpha(word[i]))
			++count;
	}
	return count;
}

/// <summary>
/// This function checks if there's a special character within a word.
/// </summary>
/// 
/// This function takes a string parameter and initially sets `special_character` to `false`. The for loop iterates over each character
/// in the `word` and checks to see if it's a special character. If it is, `special_character` is set to `true` and the loop ends.
/// If no character in the word is a special character, `special_character` remains `false`. 
/// <param name="word"> is the word to be tested.</param>
/// <returns>`true` if the word contains a special character. Otherwise returns `false`.</returns>
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

/// <summary>
/// This function reads the usernames and passwords stored in a file
/// </summary>
/// The function starts by creating a vector of strings accounts. Then through the ifstream it opens the filename specified in the class.
/// If the file opens correctly, it gets each line in the file (which each contain a username and password that are separated by '\t\t')
/// and stores it in the line variable. It then adds each line to the back of the accounts vector. Once every line in the file is read,
/// the function closes the file.
/// <returns>The accounts vector.</returns>
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

/// <summary>
/// This function prompts the user to enter a username and verifies the username's format.
/// </summary>
/// This function uses a do-while loop that prompts the user to enter a username while `is_valid` is false.
/// The loop uses `getline()` to store the entered username in the `new_username` variable. Once done, all whitespace is removed
/// (if necessary) from the front of the username by obtaining the index of the first character in the name and using `.substr()`
/// with this index as its parameter. This is done in case the user entered spaces before typing the username. Next, the username
/// length is compared to the required length that is set in the class. If the username length is less than the required length, an error message 
/// is displayed. Then the index of the first special character is retrieved to determine if the username contains a special character. 
/// If it does, an error message is displayed. Next, the number of letters in the username is counted to make sure it is greater than or 
/// equal to the required length that is set in the class.
/// <returns>The username entered by the user.</returns>
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

/// <summary>
/// This function prompts the user for a password and verifies its format.
/// </summary>
/// This function uses a do-while loop that prompts the user to enter a username while `valid_password` is `false`.
/// The password is retrieved with `getline()` and stored in the `new_password` string variable. Then if the password length
/// is less than the required length set in the class, an error message is displayed. Next, `find_first_of()` is used to 
/// get the index of the first number in the password. If there is no number, an error message is displayed. Then,
/// `get_special_character()` is called with the password as its parameter to check for a special character within the password.
/// If there isn't a special character, an error message is displayed. The user is prompted to try again if `valid_password` is `false`.
/// <returns>The password entered by the user.</returns>
std::string Accounts::verify_password() const {
	std::string new_password;
	bool valid_password = true;
	do {
		valid_password = true;

		std::cout << "Enter a password: ";			// Will look into preventing password
		getline(std::cin, new_password);			// from echoing to the screen. Unsure how to do it right now

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

/// <summary>
/// This function displays all of the accounts in a file after the user enters the correct master password.
/// </summary>
/// 
/// This function begins by opening the file using the master filename stored in the class. If it opens correctly, a while loop runs
/// while the bool `valid` is `false`. The user is prompted to enter the master password in order to view the accounts in the file.
/// If it's correct, each line in the file is displayed via a nested while loop. Once each line is displayed, the file is closed
/// and the function ends. Appropriate error messages are displayed if the password is incorrect or the file doesn't open properly.
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

/// <summary>
/// This function writes the username and password stored in the class to a file.
/// </summary>
/// This function begins by opening the file to be written to. If the file opens correctly, the username and password is written
/// to the file via `get_username()` and `get_password()`. Once done, the file is closed and a confirmation message is
/// displayed. An appropriate error message is displayed if the file doesn't open correctly.
/// 
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

/// <summary>
/// This function opens and rewrites the file using the accounts found in the supplied parameter.
/// </summary>
/// 
/// This function begins by opening the file and uses `std::ios::out` to rewrite the entire file. If the file opens successfully,
/// a for loop iterates over `accounts` vector and writes each string to the file. Once complete, the file is closed. An appropriate
/// error message is displayed if the file doesn't open properly.
/// <param name="accounts">is the vector of usernames/passwords to be written to the file.
/// </param>
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

/// <summary>
/// This function allows the user to delete an account from the file.
/// </summary>
/// This function begins by creating a vector of the stored usernames and passwords in the file. A while loop prompts the user
/// for the username of the account to delete. If it's spelled correctly (case sensitive), the account is deleted from the vector.
/// This is accomplished by looping through the vector and seeing if a username matches the input from the user. Since each item
/// in the vector is a string of the username and password separated by '\t\t', the index of the first '\t' is found and is used
/// within `.substr()` to get a string of *only* the username in the vector. A success message is displayed if successful, and an
/// error message is displayed if the inputted username doesn't exist in the file. The user is then prompted to enter another
/// username to delete, if they'd like. Finally, the file is updated with the new change(s).
/// 
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
			if (tab_index != std::string::npos) {
				if (accounts[i].substr(0, tab_index) == item) {		// Erase username if user input matches in accounts vector. Since the username and password
					accounts_updated = true;						// are stored on the same line in file, separated by '\t', I'm using .substr to get just
					accounts.erase(accounts.begin() + i);			// the username, not the entire line.		
					std::cout << "Account was erased successfully." << std::endl;
					break;
				}
			}
		}
		if (!accounts_updated) {
			std::cout << "Username not found." << std::endl;
		}

		std::cout << "Enter another username? (y/n): ";
		std::cin >> again;
		std::cin.ignore(1000, '\n');
		
		if (again == 'y' || again == 'Y')
			accounts_updated = false;	// Reset accounts_updated if user wants to go again
	}

	get_update_file(accounts);	
}
