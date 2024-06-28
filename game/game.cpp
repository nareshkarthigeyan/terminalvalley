#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(void){

    srand(time(0));

    float bankAccount = 1000;
    char response[2]; // +1 for the null terminator.
    response[1] = '\0';
    float gambleAmount;
    int luck = 0;
    float moneyAdded;
    while(true)
    {
        cout << "Bank balance: " << bankAccount << endl;
        cout << "Do you wanna gamble? (y/n): ";
        cin >> response[0];
        if (response[0] == 'n' || response[0] == 'N')
        {
            break;
        }
        else{
        cout << "How much do you want to gamble? ";
        cin >> gambleAmount;
        if (gambleAmount > bankAccount)
        {
            cout << "Insufficient Balance! Try again with less bet money." << endl;
            break;
        }
        bankAccount -= gambleAmount;
        cout << "SUMMARY:" << endl << "You are gambling " << gambleAmount / bankAccount* 100 << "% of your funds" << endl;
        int pf = rand();
            cout << "pf: " << pf << endl; 
        sleep(2);
        if (pf % 2 == 0){
            // Profit:
            while(pf >= gambleAmount * (0.67))
            {
                pf = pf / 2;
            }
            float profitAmout = pf / gambleAmount * 100;
            cout << "You made " << profitAmout << "% Profit! Congrats!" << endl;
            bankAccount += gambleAmount + pf;
        }
        else{
            while(pf >= gambleAmount * (0.67))
            {
                pf = pf / 2;
            }
            float profitAmout = pf / gambleAmount * 100;
            cout << "You made a loss of " << profitAmout << "%! Bad luck!" << endl << endl;
            bankAccount += gambleAmount - pf;
        }
    }
    }
    return 0;
}

/*
TO DO:
- Class of players with their own bank account for PvP?
- low risk, high risk, and meduim risk mode
- better stats
- ability to take loan from the bank + paying back.
- use money to buy upgrades.
- store the data in a file to retirve and use it to play again.
- auto gambling market (like universal paperclip model)
*/