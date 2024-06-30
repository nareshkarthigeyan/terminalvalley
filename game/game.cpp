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
    int waitTimeByLevel[5] = {5, 3, 2, 1, 0};

};

class Inventory
{
    public:
    bool hasPickaxe = false;

    tool pickaxe = {"Pickaxe", 0};
    tool fishingRod = {"Fishing Rod", 0};

    //Rarity - lower, the rarer
    item dirt = {"Dirt", 0, 0.99};
    item rock = {"Rock", 0, 0.98};
    item wood = {"Iron", 0, 0.87};
    item coal = {"Coal", 0, 0.69};
    item granite = {"Granite", 0, 0.76};
    item iron = {"Iron", 0, 0.38};
    item copper = {"Copper", 0, 0.47};
    item hardRock = {"Hard Rock", 0, 0.68};
    item gold = {"Gold", 0, 0.145};
    item diamond = {"Diamond", 0, 0.09};
    item ruby = {"Ruby", 0, 0.08};
    item blackStone = {"Black Stone", 0, 0.58};
    item magma = {"Magma", 0, 0.17};
    item bedrock = {"Bedrock", 0, 0.25};

    vector<item> getItems()
    {
        vector<item> items = {dirt, rock, wood, coal, granite, iron, copper, hardRock, gold, diamond, ruby, blackStone, magma, bedrock};
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
    float luck {1};
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

    int getMineLevelAsInt(Player &player)
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
        return currentMineLevel;
    }

    void display(Player &player)
    {
        int currentMineLevel = getMineLevelAsInt(player);
        int minesLeft;
        minesLeft = mineLevels[currentMineLevel + 1] - player.timesMined;
        minesLeft = minesLeft == 0 ? mineLevels[currentMineLevel + 1] : minesLeft;
        cout << "Times Mined: " << player.timesMined << endl;
        cout << "Current Mine Level: " << currentMineLevel << endl;
        cout << "Mines left to reach next mine level: " << minesLeft << endl;

    }

    void mine(Player &player)
    {
        int mineLevel = getMineLevelAsInt(player);
        int x = rand() % 101;
        int y = ((rand() % 14)) * player.luck;
        string mineable[10];
        float mineableRarity[10];
        int mineableCount[2] = {0, 3};           //                         0    1      2    3      4       5       6       7       8       9       10      11      12      13
        vector<item> items = player.getItems();  // vector<item> items = {dirt, rock, wood, coal, granite, iron, copper, hardRock, gold, diamond, ruby, blackStone, magma, bedrock};
        switch (mineLevel)
        {
        case 0:
            mineableCount[0] = 0;
            mineableCount[1] = 3;
            break;
        case 1:
            mineableCount[0] = 0;
            mineableCount[1] = 4;
            break;
        case 2:
            mineableCount[0] = 1;
            mineableCount[1] = 5;
            break;
        case 3:
            mineableCount[0] = 1;
            mineableCount[1] = 6;
            break;
        case 4:
            mineableCount[0] = 2;
            mineableCount[1] = 6;
            break;
        case 5:
            mineableCount[0] = 3;
            mineableCount[1] = 7;
            break;
        case 6:
            mineableCount[0] = 4;
            mineableCount[1] = 8;
            break;
        case 7:
            mineableCount[0] = 4;
            mineableCount[1] = 9;
            break;
        case 8:
            mineableCount[0] = 5;
            mineableCount[1] = 9;
            break;
        case 9:
            mineableCount[0] = 5;
            mineableCount[1] = 10;
            break;
        case 10:
            mineableCount[0] = 5;
            mineableCount[1] = 11;
            break;
        case 11:
            mineableCount[0] = 5;
            mineableCount[1] = 12;
            break;
        case 12:
            mineableCount[0] = 5;
            mineableCount[1] = 13;
            break;
        default:
            break;
        }

        for (int i = 0, j = mineableCount[0]; i < mineableCount[1]; i ++, j++)
        {
            mineable[i] = items[mineableCount[j]].name;
            mineableRarity[i] = items[mineableCount[j]].rareity * player.luck;
        }

        //mining logic here:

    }

    void enter(Player player)
    {
        cout << "You have entered the mine. Enter 'm' to mine the ground. and 'd' to show your current status, and 'i' to view inventory.\n";
        char res = 'a';
        while(true)
        {
            cout << ">> ";
            cin >> res;
            if (res == 'd')
            {
                display(player);
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
            getMineLevel(player);
            // sleep(player.pickaxe.waitTimeByLevel[player.pickaxe.level]);
            mine(player);
            //mining logic
        }
        cout << "exiting mine..." << endl;
        sleep(2);
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
    mine.enter(player);
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