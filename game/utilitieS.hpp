// utilities.hpp
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

void clearScreen();
int randInt(int min, int max);
void clearInputBuffer();
std::string toUpperCase(const std::string &str);
char getSpecificPlayerResponse(std::string m = "", char o1 = 0, char o2 = 0);
int getSpecificPlayerResponse(std::string m = "", int o1 = '\0', int o2 = '\0');
void showMessage(std::string s1 = "", std::string s2 = "", int timeOut = 0, std::string name = "");
void showDialogue(std::string author = "", std::string content = "", int timeout = 1);
char getPlayerResponse(std::string s1 = "");
void achievementMessage(std::string s1);
std::string moneyAsString(long double money, int precision = 2, std::string dollarSign = "");

#endif // UTILITIES_HPP
