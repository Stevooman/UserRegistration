#pragma once	

#include <string>
#include <vector>

/// <summary>
/// This class allows the user to create and store usernames and passwords for accounts in a file.
/// </summary>
/// The Accounts class allows users to store usernames and passwords for an account and write them to a file, but only after the
/// username and password meet certain criteria. The username must contain at least n letters and be at least n characters in length.
/// The password must contain at least 1 number, be at least n characters in length, and contain at least 1 special character.
/// The user can view all of the stored usernames and passwords by inputting the master password for access to the file info.
/// The user can also delete any of the stored accounts from the file by typing the desired username exactly as it's written.
///
class Accounts {
private:
	/// <summary>
	/// Stores the username entered by the user.
	/// </summary>
	std::string username;

	/// <summary>
	/// Stores the password entered by the user.
	/// </summary>
	std::string password;

	/// <summary>
	/// Stores a string of the entire upper and lower case alphabet and all digits.
	/// </summary>
	std::string alpha_and_nums;

	/// <summary>
	/// Stores a string of all numbers 0-9.
	/// </summary>
	std::string numbers;

	/// <summary>
	/// Stores the password that allows users to view a file.
	/// </summary>
	const std::string master_password = "Boiseisnotastate";

	/// <summary>
	/// Stores the file name of the file used to read and write accounts.
	/// </summary>
	std::string master_filename;

	/// <summary>
	/// Stores the minimum number of characters required for a username.
	/// </summary>
	int required_username_length;

	/// <summary>
	/// Stores the minimum number of letters required in a username.
	/// </summary>
	int required_letter_count;

	/// <summary>
	/// Stores the minimum number of characters required for a password.
	/// </summary>
	int required_password_length;

	// Private methods
	int letter_count(std::string word) const;
	bool special_character(std::string word) const;
	std::vector<std::string> read_users() const;
	void update_file(std::vector<std::string> accounts) const;
public:
	// Constructor declaration
	Accounts();

	/// <summary>
	/// Gets the username stored in the class.
	/// </summary>
	/// <returns>The username.</returns>
	std::string get_username() const { return username; }

	/// <summary>
	/// Gets the password stored in the class.
	/// </summary>
	/// <returns>The password.</returns>
	std::string get_password() const { return password; }

	/// <summary>
	/// Gets the string of the entire alphabet (upper and lower case) and all digits.
	/// </summary>
	/// <returns>The alpha_and_nums string.</returns>
	std::string get_alpha_and_nums() const { return alpha_and_nums; }

	/// <summary>
	/// Gets the string that contains all numbers 0-9.
	/// </summary>
	/// <returns>The numbers string.</returns>
	std::string get_numbers() const { return numbers; }

	/// <summary>
	/// Gets the master password needed to access the I/O file.
	/// </summary>
	/// <returns>The master_password string.</returns>
	std::string get_master_password() const { return master_password; }		
																		
	/// <summary>
	/// Gets the file name of the master file.
	/// </summary>
	/// <returns>The master_filename string.</returns>
	std::string get_master_filename() const { return master_filename; }

	/// <summary>
	/// Gets the required length of the username.
	/// </summary>
	/// <returns>The required_username_length number.</returns>
	int get_required_username_length() const { return required_username_length; }

	/// <summary>
	/// Gets the required number of letters for a username.
	/// </summary>
	/// <returns>The required_letter_count for a username.</returns>
	int get_required_letter_count() const { return required_letter_count; }

	/// <summary>
	/// Gets the required length of a password.
	/// </summary>
	/// <returns>The required_password_length number.</returns>
	int get_required_password_length() const { return required_password_length; }

	/// <summary>
	/// Gets the function that gives the number of letters in the supplied word parameter.
	/// </summary>
	/// <param name="word">is the word that will be passed to letter_count().</param>
	/// <returns>The letter_count() function.</returns>
	int get_letter_count(std::string word) const { return letter_count(word); }

	/// <summary>
	/// Gets the special_character() function.
	/// </summary>
	/// <param name="word">is the word to be tested.</param>
	/// <returns>The special_character() function.</returns>
	bool get_special_character(std::string word) const { return special_character(word); }

	/// <summary>
	/// Gets the read_users() function.
	/// </summary>
	/// <returns>The read_users() function.</returns>
	std::vector<std::string> get_users() const { return read_users(); }

	/// <summary>
	/// Gets the update_file() function.
	/// </summary>
	/// <param name="accounts">is the vector of accounts that will be written to the file.</param>
	void get_update_file(std::vector<std::string> accounts) const { return update_file(accounts); }
	
	/// <summary>
	/// This function sets the username variable equal to the supplied username_p parameter.
	/// </summary>
	/// <param name="username_p">is the user name to be assigned to `username`.</param>
	void set_username(std::string username_p) {
		username = username_p;
	}

	/// <summary>
	/// This function sets the password variable equal to the supplied password_p parameter.
	/// </summary>
	/// <param name="password_p">is the password to be assigned to `password`.</param>
	void set_password(std::string password_p) {
		password = password_p;
	}

	/// <summary>
	/// This function sets the alpha_and_nums variable equal to the supplied alpha_and_nums_p parameter.
	/// </summary>
	/// <param name="alpha_and_nums_p">is the string to be set to alpha_and_nums</param>
	void set_alpha_and_nums(std::string alpha_and_nums_p) {
		alpha_and_nums = alpha_and_nums_p;
	}

	/// <summary>
	/// This function sets the numbers variable equal to the supplied numbers_p parameter.
	/// </summary>
	/// <param name="numbers_p">is the string to be set to numbers</param>
	void set_numbers(std::string numbers_p) {
		numbers = numbers_p;
	}

	/// <summary>
	/// This function sets the master_filename variable equal to the supplied master_file_p parameter.
	/// </summary>
	/// <param name="master_file_p">is the name of a file to be set to master_filename</param>
	void set_master_filename(std::string master_file_p) {
		master_filename = master_file_p;
	}

	/// <summary>
	/// This function sets the required_username_length variable equal to the supplied required_length_p parameter.
	/// </summary>
	/// <param name="required_length_p">is number to be set to required_username_length</param>
	void set_required_username_length(int required_length_p) {
		required_username_length = required_length_p;
	}

	/// <summary>
	/// This function sets the required_letter_count variable equal to the supplied num_p parameter.
	/// </summary>
	/// <param name="num_p">is the number to be set to required_letter_count</param>
	void set_required_letter_count(int num_p) {
		required_letter_count = num_p;
	}

	/// <summary>
	/// This function sets the required_password length equal to the supplied num_p parameter.
	/// </summary>
	/// <param name="num_p">is the number to be set to required_password_length</param>
	void set_required_password_length(int num_p) {
		required_password_length = num_p;
	}

	// member function declarations
	std::string verify_username() const;
	std::string verify_password() const;
	void read_from_file() const;
	void write_to_file() const;
	void delete_item() const;
};
