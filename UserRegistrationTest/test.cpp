#include "pch.h"

#include "../UserRegistration/accounts.cpp"
#include "../UserRegistration/accounts.h"


// Test fixture
class AccountsTest : public ::testing::Test {		
protected:
	Accounts *a;
	void SetUp() override { a = new Accounts(); }
	void TearDown() override { delete a; }
};

/// <summary>
/// This test checks to see that get_letter_count() accepts a string as an argument and 
/// returns the correct number of letters contained in that string.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(AccountsTest, ShouldOnlyCountLetters) {										
	EXPECT_EQ(a->get_letter_count("Peach"), 5);										
	EXPECT_EQ(a->get_letter_count("EnCyCloPedIa"), 12);								
	EXPECT_EQ(a->get_letter_count("The Wellerman! "), 12);							
	EXPECT_EQ(a->get_letter_count("The little engine said, I think I can."), 29);   
	EXPECT_EQ(a->get_letter_count("0254656767897"), 0);
	EXPECT_EQ(a->get_letter_count("4 32! ! ??56"), 0);
	EXPECT_EQ(a->get_letter_count(""), 0);
	EXPECT_EQ(a->get_letter_count("madden2001"), 6);
	EXPECT_EQ(a->get_letter_count("phill6y75@#!"), 6);
	EXPECT_EQ(a->get_letter_count("   \n\t  \r"), 0);
	EXPECT_EQ(a->get_letter_count("hi\x42ob\0!"), 5);
	EXPECT_EQ(a->get_letter_count("\u104E"), 0);
}																					

/// <summary>
/// This test checks to see if get_special_character() correctly detects a special character
/// located in its provided string argument.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(AccountsTest, ShouldDetectSpecialChar) {
	EXPECT_TRUE(a->get_special_character("Middleearth@soman"));
	EXPECT_TRUE(a->get_special_character("940398%sdfo oih"));
	EXPECT_FALSE(a->get_special_character("435soidfSOIH"));
	EXPECT_FALSE(a->get_special_character("Stephen Oman3902"));
}

/// <summary>
/// This test checks to see if all of the getter functions return the values of the corresponding
/// private variables.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(AccountsTest, ShouldGetPrivateVariables) {
	EXPECT_EQ(a->get_username(), "");
	EXPECT_EQ(a->get_password(), "");
	EXPECT_EQ(a->get_alpha_and_nums(), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	EXPECT_EQ(a->get_numbers(), "0123456789");
	EXPECT_EQ(a->get_master_password(), "Boiseisnotastate");
	EXPECT_EQ(a->get_master_filename(), "usernames_and_passwords.txt");
	EXPECT_EQ(a->get_required_username_length(), 8);
	EXPECT_EQ(a->get_required_letter_count(), 2);
	EXPECT_EQ(a->get_required_password_length(), 8);
}

/// <summary>
/// This test checks to see if all of the setter functions correctly assign values to the corresponding
/// private variables.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(AccountsTest, ShouldSetPrivateVariables) {
	std::string user1 = a->get_username();
	ASSERT_EQ(user1, "");
	a->set_username("steveoman");
	std::string user2 = a->get_username();
	EXPECT_NE(user1, user2);

	std::string pass1 = a->get_password();
	ASSERT_EQ(pass1, "");
	a->set_password("ferrari45$");
	std::string pass2 = a->get_password();
	EXPECT_NE(pass1, pass2);

	std::string alpha1 = a->get_alpha_and_nums();
	ASSERT_EQ(alpha1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	a->set_alpha_and_nums("abc123");
	std::string alpha2 = a->get_alpha_and_nums();
	EXPECT_NE(alpha1, alpha2);

	std::string nums1 = a->get_numbers();
	ASSERT_EQ(nums1, "0123456789");
	a->set_numbers("3849");
	std::string nums2 = a->get_numbers();
	EXPECT_NE(nums1, nums2);

	std::string name1 = a->get_master_filename();
	ASSERT_EQ(name1, "usernames_and_passwords.txt");
	a->set_master_filename("new_accounts.txt");
	std::string name2 = a->get_master_filename();
	EXPECT_NE(name1, name2);

	int user_length1 = a->get_required_username_length();
	ASSERT_EQ(user_length1, 8);
	a->set_required_username_length(10);
	int user_length2 = a->get_required_username_length();
	EXPECT_NE(user_length1, user_length2);

	int letter_count1 = a->get_required_letter_count();
	ASSERT_EQ(letter_count1, 2);
	a->set_required_letter_count(6);
	int letter_count2 = a->get_required_letter_count();
	EXPECT_NE(letter_count1, letter_count2);

	int pass_length1 = a->get_required_password_length();
	ASSERT_EQ(pass_length1, 8);
	a->set_required_password_length(10);
	int pass_length2 = a->get_required_password_length();
	EXPECT_NE(pass_length1, pass_length2);
}

/// <summary>
/// This test checks to see if write_to_file() correctly writes usernames and passwords to a file
/// and that get_users() correctly reads usernames and passwords from the file.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST_F(AccountsTest, ShouldReadAndWriteToFile) {
	std::string user1 = "PhantomWalrus";
	std::string user2 = "DrDisrespect";
	a->set_username(user1);
	a->set_password("Chilis432!");
	a->write_to_file();
	a->set_username(user2);
	a->set_password("SpeedMomentum34$");
	a->write_to_file();

	std::vector<std::string> users = a->get_users();
	bool user1_exists = false;
	bool user2_exists = false;
	for (int i = 0; i < users.size(); ++i) {
		int tab_index = users[i].find_first_of("\t");
		if (users[i].substr(0, tab_index) == user1)
			user1_exists = true;
		if (users[i].substr(0, tab_index) == user2)
			user2_exists = true;
	}
	EXPECT_TRUE(user1_exists);
	EXPECT_TRUE(user2_exists);
}