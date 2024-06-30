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
        bankBalance = 1000.0;
        cout << "Created " << name << " with initial Bank Balance: " << bankBalance << endl;
    }
};

class Gamble
{
    private:
    float gambleAtRisk(float money, int riskLevel)
    {
        const int riskFactor[3] = {22000, 54000, 111000};
        float x = (rand() % riskFactor[riskLevel]);
        float profit;
            profit = ((x/(100000))*money);
        return profit;
    }

    public:
    int chooseGameMode()
    {
        string gamemode;
        char res[2] = {'a', '\0'};
        cout << "Choose Risk Level: " << endl << "a) low risk (0 - 22% returns)\nb) medium risk (0 - 54% returns)\nc) high risk (0 - 110% returns)\n>> ";
        cin >> res[0];
        if (tolower(res[0]) == 'a')
        {
            return 0;
        }
        else if (tolower(res[0]) == 'b')
        {
            return 1;
        }
        else if (tolower(res[0]) == 'c')
        {
            return 2;
        }
        return 1;
    }
    int gamble(float gambleAmount, int gamemode)
    {
        if (gamemode < 0 || gamemode > 2)
        {
            gamemode = 1;
        }
        return gambleAtRisk(gambleAmount, gamemode);
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
    while(true)
    {
        cout << "Bank balance: " << player.bankBalance << endl;
        cout << "Do you wanna gamble? (y/n): ";
        cin >> response[0];
        if (response[0] == 'n' || response[0] == 'N')
        {
            break;
        }
        else{
            do {    
                cout << "Enter gamble amount: ";
                cin >> gambleAmount;
                if (gambleAmount > player.bankBalance)
                {
                    cout << "Insufficient Balance! Try again with less bet money." << endl;
                }
            } while (gambleAmount > player.bankBalance);
        player.bankBalance -= gambleAmount;

        Gamble session;
        int gamemode = session.chooseGameMode();
        cout << "You are gambling " << gambleAmount / player.bankBalance* 100 << "% of your total funds" << endl;
        float profit = session.gamble(gambleAmount, gamemode);
        int pf = rand();
        cout << "gambling...";
        sleep(2);
        if (pf % 2 == 0){ // 50% chance only - add more randomness.... TO DO
            // Profit:
            cout << "You made " << profit << " Profit for " << gambleAmount << " Thats a " << (profit)/gambleAmount*100 <<  "% increase! Congrats!" << endl;
            player.bankBalance += gambleAmount + profit;
        }
        else{
            cout << "You made a loss of "  << profit <<  " for " << gambleAmount << " Thats a " << (profit)/gambleAmount*100 <<  "\% decrease. Bad luck!" << endl << endl;
            player.bankBalance += gambleAmount - profit;
        }
    }
    }

    // //FUN:
    // gambleAmount = player.bankBalance;
    // float initialAmount =  gambleAmount;
    // for (int i = 0; i < 100; i++){
    // srand(time(0));
    //     player.bankBalance -= gambleAmount;

    //     sleep(1);
    //     Gamble session;
    //     float profit = session.highRisk(gambleAmount);
    //     int pf = rand();
    //     if (pf % 2 == 0){
    //         // Profit:
    //         player.bankBalance += gambleAmount + profit;
    //         cout << i << ". \t" <<  player.bankBalance << "\tProfit: " << profit << "\t" << (profit)/gambleAmount*100 <<  "%" << endl;
    //     }
    //     else{
    //         player.bankBalance += gambleAmount - profit;
    //         cout << i << ". \t" << player.bankBalance << "\tLoss: " << profit << "\t" << (profit)/gambleAmount*100 <<  "%" << endl;
    //     }
    // }
    // float finalAmount = player.bankBalance;
    // cout << "SUMMARY" << endl << "Intiial Amount: " << initialAmount << endl << "Final Amount: " << finalAmount << endl << "\% increase/decrease = " << initialAmount / finalAmount * 100 << endl;
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