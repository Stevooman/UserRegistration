#pragma once	// Include guard

#include <string>
#include <vector>

class Accounts {
private:
	std::string username;
	std::string password;
	std::string alpha_and_nums;
	std::string numbers;
	const std::string master_password = "Boiseisnotastate";
	std::string master_filename;
	int required_username_length;
	int required_letter_count;
	int required_password_length;

	// Private methods
	int letter_count(std::string word) const;
	bool special_character(std::string word) const;
	std::vector<std::string> read_users() const;
	void update_file(std::vector<std::string> accounts) const;
public:
	// Constructor declaration
	Accounts();

	// inline getter functions
	std::string get_username() const { return username; }

	std::string get_password() const { return password; }

	std::string get_alpha_and_nums() const { return alpha_and_nums; }

	std::string get_numbers() const { return numbers; }

	std::string get_master_password() const { return master_password; }				// Not including a setter for this master password so the user
																					// can't change the password... ?
	std::string get_master_filename() const { return master_filename; }

	int get_required_username_length() const { return required_username_length; }

	int get_required_letter_count() const { return required_letter_count; }

	int get_required_password_length() const { return required_password_length; }

	int get_letter_count(std::string word) const { return letter_count(word); }

	bool get_special_character(std::string word) const { return special_character(word); }

	std::vector<std::string> get_users() const { return read_users(); }

	void get_update_file(std::vector<std::string> accounts) const { return update_file(accounts); }
	
	// inline setter functions
	void set_username(std::string username_p) {
		username = username_p;
	}

	void set_password(std::string password_p) {
		password = password_p;
	}

	void set_alpha_and_nums(std::string alpha_and_nums_p) {
		alpha_and_nums = alpha_and_nums_p;
	}

	void set_numbers(std::string numbers_p) {
		numbers = numbers_p;
	}

	void set_master_filename(std::string master_file_p) {
		master_filename = master_file_p;
	}

	void set_required_username_length(int required_length_p) {
		required_username_length = required_length_p;
	}

	void set_required_letter_count(int num_p) {
		required_letter_count = num_p;
	}

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
