#include "utilitieS.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <algorithm>
#include <cctype>
#include <limits>
#include <iomanip>
#include <sstream>


using namespace std;

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen and move cursor to home position
}

int randInt(int min, int max)
{
    //Stack overflowed this part... IDK
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
string toUpperCase(const string &str) {
  string result = str;
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

char getSpecificPlayerResponse(string m, char o1, char o2) 
{
  char res;
  if (m != "") {
    m = m + " ";
  }

  if (o1 != '\0') {
    if (o2 != '\0') {
      while (true) {
        cout << m << ">> ";
        cin >> res;

        if (res == o1 || res == o2) {
          return res;
        }
      }
    }

    while (true) {
      cout << m << ">> ";
      cin >> res;

      if (res == o1) {
        return res;
      }
    }
  }
  return res;
}


int getSpecificPlayerResponse(string m, int o1, int o2) {
  char res;
  if (m != "") {
    m = m + " ";
  }
  int x;
  while(true)
  {
    cout << m << ">> ";
    cin >> res;
        
        // Check if input is a digit
    if (isdigit(res)) {
        x = res - '0';
        
        // Check if the input is within the range
    if (x >= o1 && x <= o2) {
        break;
    }
  }

}
  return x;
}

void showMessage(string s1, string s2, int timeOut, string name) {
  if (name != "") {
    cout << name << ": ";
  } else {
    cout << name;
  }
  cout << s1 << endl;
  sleep(timeOut);
  if (s2 != "") {
    if (name != "") {
      cout << name << ": ";
    } else {
      cout << name;
    }
    cout << s2 << endl;
  }
}

void showDialogue(string author, string content, int timeout) {
  if (author != "") {
    cout << author << ": ";
  } else {
    cout << author;
  }
  cout << content << endl;

  if (timeout != 0) {
    if (content.size() / sizeof(char) > 10) {
      timeout = 3;
    } else if (content.size() / sizeof(char) > 25) {
      timeout = 4;
    } else if (content.size() / sizeof(char) > 40) {
      timeout = 6;
    }
    sleep(timeout);
  }
}

char getPlayerResponse(string s1) {
  char res;
  cout << s1 << "\n>> ";
  cin >> res;
  return res;
}

void achievementMessage(string s1) {
  cout << "\033[1;32m" << "[ " << s1 << " ]" << "\033[0m" << std::endl;
  return;
}

string moneyAsString(long double money, int precision,
                     string dollarSign) {
  ostringstream numStr;
  numStr << fixed << setprecision(precision) << money;
  string numStrStr = numStr.str();

  int n = numStrStr.find('.');
  string integerPart = (n == string::npos) ? numStrStr : numStrStr.substr(0, n);
  string fractionalPart = (n == string::npos) ? "" : numStrStr.substr(n);

  int insertPosition = integerPart.length() - 3;
  while (insertPosition > 0) {
    integerPart.insert(insertPosition, ",");
    insertPosition -= 3;
  }

  return dollarSign + integerPart + fractionalPart;
}