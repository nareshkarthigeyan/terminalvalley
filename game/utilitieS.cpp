#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <vector>
#include "utiliteS.h"

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