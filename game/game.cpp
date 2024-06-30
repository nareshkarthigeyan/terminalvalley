#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iterator>
#include <vector>

#define MAX_MINE_LEVELS 12

using namespace std;

struct item
{
    string name;
    int count {0};
    float rareity;
};

struct tool
{
    string name;
    int level {0};
    float health {100};
};

class Inventory
{
    public:
    bool hasPickaxe = false;

    tool pickaxe = {"Pickaxe", 0};
    tool fishingRod = {"Fishin Rod", 0};
    item dirt = {"Dirt", 0, 0.1};
    item rock = {"Rock", 0, 0.2};
    item iron = {"Iron", 0, 0.5};


    vector<item> getItems()
    {
        vector<item> items = {dirt, rock, iron};
        return items;
    }
    vector<tool> getTools()
    {
        vector<tool> tools = {pickaxe, fishingRod};
        return tools;
    }

    void displayInventory(){
        vector<item> items = getItems();
        vector<tool> tools = getTools();
        for (int i =0; i < items.size(); i++)
        {
            if(items[i].count > 0)
            {
                cout << items[i].name << ": " << items[i].count << endl;
            }
        }
    }

    
};

class Player : public Inventory
{
    public:
    string name;
    float bankBalance;
    float luck = 0;
    int timesMined;

    void createPlayer()
    {
        cout << "Enter the name of the player: ";
        getline(cin, name);
        bankBalance = 1000.0;
        timesMined = 0;
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

class Mine
{
    public:
    int mineLevels[MAX_MINE_LEVELS] = {0, 55, 127, 377, 695, 889, 780, 1001, 2350, 3978, 5111, 7500};


    void getMineLevel(Player &player)
    {
        for (int i = 0; i < 8; i++)
        {
            if(player.timesMined == mineLevels[i])
            {
                cout << "You are at mine level " << i << "." << endl;
            }
        }
    }

    void display(Player &player)
    {
        int currentMineLevel = 0;
        int minesLeft;
        for (int i = 1; i < MAX_MINE_LEVELS - 2; i++)
        {
            if(player.timesMined < mineLevels[0])
            {
                currentMineLevel = 0;
                break;
            }
            else if (player.timesMined > mineLevels[MAX_MINE_LEVELS - 1])
            {
                currentMineLevel = MAX_MINE_LEVELS;
                break;
            }
            
            if (player.timesMined > mineLevels[i - 1] && player.timesMined < mineLevels[i + 1])
            {
                currentMineLevel = i - 1;
            }

        }
        minesLeft = mineLevels[currentMineLevel + 1] - player.timesMined;
        minesLeft = minesLeft == 0 ? mineLevels[currentMineLevel + 1] : minesLeft;
        cout << "Times Mined: " << player.timesMined << endl;
        cout << "Current Mine Level: " << currentMineLevel << endl;
        cout << "Mines left to reach next mine level: " << minesLeft << endl;

    }

    void mine(Player &player)
    {
        vector<item> items = player.getItems();
        int x = rand() % 101;

        if (x < 30)
        {
            cout << "You found dirt!" << endl;
            player.dirt.count++;
        }
        else if (x < 85)
        {
            cout << "You found rock!" << endl;
            player.rock.count++;
        }
        else
        {
            cout << "You found Iron!" << endl;
            player.iron.count++;
        }

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
    Mine mine;
    cout << "You have entered the mine. Enter 'm' to mine the ground. and 'd' to show your current status, and 'i' to view inventory.\n";
    char res = 'a';
    while(true)
    {
        cout << ">> ";
        cin >> res;
        if (res == 'd')
        {
            mine.display(player);
            continue;
        }
        if (res == 'i')
        {
            player.displayInventory();
            continue;
        }
        if (res != 'm')
        {
            break;     
        }
        cout << "mining..." << endl;
        player.timesMined++;
        mine.getMineLevel(player);
        sleep(1);
        mine.mine(player);
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