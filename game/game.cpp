#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Player
{
    public:
    string name;
    float bankBalance;
    float luck = 0;

    void createPlayer()
    {
        cout << "Enter the name of the player: ";
        getline(cin, name);
        bankBalance = 10000.0;
    }
};

class Gamble
{
    public:
    float lowRisk(float money)
    {
        float x = rand() % 22;
        float y = rand() % 78;
        float profit;
            profit = ((x/(x + y))*money);
        return profit;
    }
};

int main(void){
    Player  player;
    player.createPlayer();
    char response[2]; // +1 for the null terminator.
    response[1] = '\0';
    float gambleAmount;
    int luck = 0;
    float moneyAdded;
    // while(true)
    // {
    //     cout << "Bank balance: " << player.bankBalance << endl;
    //     cout << "Do you wanna gamble? (y/n): ";
    //     cin >> response[0];
    //     if (response[0] == 'n' || response[0] == 'N')
    //     {
    //         break;
    //     }
    //     else{
    //         do {    
    //             cout << "Enter gamble amount: ";
    //             cin >> gambleAmount;
    //             if (gambleAmount > player.bankBalance)
    //             {
    //                 cout << "Insufficient Balance! Try again with less bet money." << endl;
    //             }
    //         } while (gambleAmount > player.bankBalance);
    //     cout << "SUMMARY:" << endl << "You are gambling " << gambleAmount / player.bankBalance* 100 << "% of your funds" << endl;
    //     player.bankBalance -= gambleAmount;

    //     sleep(2);
    //     Gamble session;
    //     float profit = session.lowRisk(gambleAmount);
    //     int pf = randint(0, 10);
    //     if (pf % 2 == 0){
    //         // Profit:
    //         cout << "You made " << profit << " Profit! Thats a " << (profit)/gambleAmount*100 <<  "% increase! Congrats!" << endl;
    //         player.bankBalance += gambleAmount + profit;
    //     }
    //     else{
    //         while(pf >= gambleAmount * (0.67))
    //         {
    //             pf = pf / 2;
    //         }
    //         float profitAmout = pf / gambleAmount * 100;
    //         cout << "You made a loss of "  << profit <<  "! Thats a " << (profit)/gambleAmount*100 <<  "\% decrease. Bad luck!" << endl << endl;
    //         player.bankBalance += gambleAmount - profit;
    //     }
    // }
    // }

    //FUN:
    gambleAmount = player.bankBalance;
    float initialAmount =  gambleAmount;
    for (int i = 0; i < 100; i++){
    srand(time(0));
        player.bankBalance -= gambleAmount;

        sleep(1);
        Gamble session;
        float profit = session.lowRisk(gambleAmount);
        int pf = rand();
        if (pf % 2 == 0){
            // Profit:
            player.bankBalance += gambleAmount + profit;
            cout << i << ". \t" <<  player.bankBalance << "\tProfit: " << profit << "\t" << (profit)/gambleAmount*100 <<  "%" << endl;
        }
        else{
            player.bankBalance += gambleAmount - profit;
            cout << i << ". \t" << player.bankBalance << "\tLoss: " << profit << "\t" << (profit)/gambleAmount*100 <<  "%" << endl;
        }
    }
    float finalAmount = player.bankBalance;
    cout << "SUMMARY" << endl << "Intiial Amount: " << initialAmount << endl << "Final Amount: " << finalAmount << endl << "\% increase/decrease = " << initialAmount / finalAmount * 100 << endl;
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