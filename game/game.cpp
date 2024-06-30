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
    int mineLevel;

    void createPlayer()
    {
        cout << "Enter the name of the player: ";
        getline(cin, name);
        bankBalance = 1000.0;
        mineLevel = 0;
        cout << "Created " << name << " with initial Bank Balance: " << bankBalance << endl;
    }

    void display()
    {
        cout << "Name: " << name << "\nBank Balance: $" << bankBalance << "\nLuck: " << luck << endl;
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
void gamble(Player &player);
void mine(Player &player);

void mainmenu(Player &player)
{
    cout << "Player: " << player.name << "\nBank Balance: $" << player.bankBalance << endl << endl;
    cout << "GAME ACTIONS" << "\na) Gamble\nm) mine\n>> ";
    char response[2] = {'a', '\0'};
    cin >> response[0];

    switch (response[0])
    {
    case 'a':
        gamble(player);
        break;

    case 'm':
        mine(player);
    
    default:
        break;
    }

}

void gamble(Player &player)
{
    char response[2]; // +1 for the null terminator.
    response[1] = '\0';
    float gambleAmount;
    while(true)
    {
        cout << "Current Bank balance: " << player.bankBalance << endl;
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
        cout << "Do you want to gamble again? (y/n): ";
        cin >> response[0];
        if (response[0] == 'n' || response[0] == 'N')
        {
            break;
        }
    }
}

void mine(Player &player)
{
    cout << "You have entered the mine at mine level " << player.mineLevel << ". Enter 'm' to mine the ground.\n";
    char res = 'a';
    while(true)
    {
        cout << ">> ";
        cin >> res;
        if (res != 'm')
        {
            break;     
        }
        cout << "mining the ground..." << endl;
        sleep(1);
        //mining logic
    }
    cout << "exiting mine..." << endl;
    sleep(2);
}

int main(void){
    Player  player;
    player.createPlayer();

    while(true)
    {
        mainmenu(player);
        cout << "Details: \n";
        player.display();
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