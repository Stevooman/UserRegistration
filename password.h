#pragma once
#ifndef OMAN_PASSWORD_H
#define OMAN_PASSWORD_H

#include <string>

class Password {
private:
	std::string password = "Unclerico2!";
public:
	// Constructor
	Password(std::string password);

	// Inline getter function
	std::string get_password() const { return password; };

	// Inline setter function
	void set_password(std::string password_param) {
		password = password_param;
	}
};
#endif // !OMAN_PASSWORD_H

