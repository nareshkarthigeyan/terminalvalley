#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <vector>

#define MAX_MINE_LEVELS 12
#define WEIGHT 1

using namespace std;

int randInt(int min, int max)
{
    //Stack overflowed this part... IDK
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void showMessage(string s1, string s2, int timeOut)
{
    cout << s1;
    sleep(timeOut);
    cout << s2;
}

struct item
{
    string name;
    int count {0};
    float rareity {1};
    float luckFactor {1};
    float weight = WEIGHT / rareity;
    
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
    item dirt = {"Dirt", 0, 0.80};
    item rock = {"Rock", 0, 0.75};
    item wood = {"Wood", 0, 0.45};
    item coal = {"Coal", 0, 0.70};
    item granite = {"Granite", 0, 0.380};
    item iron = {"Iron", 0, 0.15};
    item copper = {"Copper", 0, 0.15};
    item hardRock = {"Hard Rock", 0, 0.12};
    item gold = {"Gold", 0, 0.08};
    item diamond = {"Diamond", 0, 0.05};
    item ruby = {"Ruby", 0, 0.04};
    item blackStone = {"Black Stone", 0, 0.10};
    item magma = {"Magma", 0, 0.07};
    item bedrock = {"Bedrock", 0, 0.03};

    vector<item> getItems()
    {
        vector<item> items = {dirt, rock, wood, coal, granite, iron, copper, hardRock, gold, diamond, ruby, blackStone, magma, bedrock};
        return items;
    }

    vector<item*> getItemsByAddress()
    {
        vector<item*> items = {&dirt, &rock, &wood, &coal, &granite, &iron, &copper, &hardRock, &gold, &diamond, &ruby, &blackStone, &magma, &bedrock};
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

    void incrementItemCount(string itemName, int byThis)
    {
        vector<item*> items = getItemsByAddress(); 
        for (auto &item : items)
        {
            if (itemName == item->name)
            {
                item->count += byThis;
                break;
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

    bool firstTime = true;

    void createPlayer()
    {
        cout << "Enter the name of the player: ";
        getline(cin, name);
        bankBalance = 0;
        timesMined = 0;
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
        if (player.firstTime)
        {
            showMessage("...\n", "*blink* *blink*\n", 2);
            sleep(2);
            showMessage("[looks around] ", "Where am I?\n", 2);
            sleep(2);
            showMessage("in a...", " terminal?\n", 3);
            sleep(3);
        }
        player.firstTime = false;

        for (int i = 0; i < MAX_MINE_LEVELS; i++)
        {
            if(player.timesMined == mineLevels[i])
            {
                cout << "You are at mine level " << i << "." << endl;
            }
        }

        switch(player.timesMined)
        {
            case 0:
            showMessage("Click 'm' to start mining...\n", "", 0);
            break;
            case 3:
            showMessage("The items you mine would be stored in your inventory...\n", "click 'i' on the prompt menu to access it.\n", 1);
            break;
            case 6:
            showMessage("Mining takes so long...\n", "If only there was a way to speed things up...\n", 1);
            break;
            case 9:
            showMessage("To get details about your position in the mine, enter 'd' into the terminal when in the mine.\n", "", 0);
            break;
            case 10:
            showMessage("oh... and you can quit the mine by entering 'q'\n", "", 0);
        }
    }

    int getMineLevelAsInt(Player &player)
    {
        int currentMineLevel = 0;
        for (int i = 0; i < MAX_MINE_LEVELS - 1; i++)
        {
            if(player.timesMined < mineLevels[i])
            {
                currentMineLevel = i - 1;
                break;
            }
        }
        if (player.timesMined >= mineLevels[MAX_MINE_LEVELS - 1])
        {
            currentMineLevel = MAX_MINE_LEVELS - 1;
        }

        return currentMineLevel;
    }

    void display(Player &player)
    {
        int currentMineLevel = getMineLevelAsInt(player);
        int minesLeft;
        int nextLevel = currentMineLevel + 1 < MAX_MINE_LEVELS ? currentMineLevel + 1: currentMineLevel;
        minesLeft = mineLevels[nextLevel] - player.timesMined;
        minesLeft = minesLeft == 0 ? mineLevels[currentMineLevel + 1] : minesLeft;
        cout << "Times Mined: " << player.timesMined << endl;
        cout << "Current Mine Level: " << currentMineLevel << endl;
        if (minesLeft >= 0)
        {
        cout << "Mines left to reach next mine level: " << minesLeft << endl;
        } else {
            cout << "Mines left to reach next mine level: " << "???" << endl;
        }
    }

    void mine(Player &player)
    {

        int mineLevel = getMineLevelAsInt(player);
        item mineable[25];
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
            mineableCount[0] = 0;
            mineableCount[1] = 5;
            break;
        case 3:
            mineableCount[0] = 0;
            mineableCount[1] = 6;
            break;
        case 4:
            mineableCount[0] = 0;
            mineableCount[1] = 6;
            break;
        case 5:
            mineableCount[0] = 0;
            mineableCount[1] = 7;
            break;
        case 6:
            mineableCount[0] = 0;
            mineableCount[1] = 8;
            break;
        case 7:
            mineableCount[0] = 0;
            mineableCount[1] = 9;
            break;
        case 8:
            mineableCount[0] = 0;
            mineableCount[1] = 9;
            break;
        case 9:
            mineableCount[0] = 0;
            mineableCount[1] = 10;
            break;
        case 10:
            mineableCount[0] = 0;
            mineableCount[1] = 11;
            break;
        case 11:
            mineableCount[0] = 0;
            mineableCount[1] = 12;
            break;
        case 12:
            mineableCount[0] = 0;
            mineableCount[1] = 13;
            break;
        default:
            break;
        }

        for (int i = 0, j = mineableCount[0]; i < mineableCount[1]; i++, j++)
        {
            mineable[i] = items[j];
        }

        // float random = randInt(1, 8);
        // int randomIndex = randInt(0, (mineableCount[1] - mineableCount[0]) - 1);
        // float rariety = (randomIndex + 1) * mineable[randomIndex].rareity;
        // int count = random * rariety;

        //mining logic here:

        float totalWeight = 0;
        for (int i = 0; i < mineableCount[1]; i++)
        {
            totalWeight += mineable[i].weight;
        }
        float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * totalWeight;
        item selecteditem;

        float accWeight = 0;
        for(int i = 0; i < mineableCount[1]; i++)
        {
            accWeight += mineable[i].weight;
            if(random < accWeight)
            {
                selecteditem = mineable[i];
                break;
            }
            random -= mineable[i].weight;
        }
        int count = (randInt(1, 15) * selecteditem.rareity) + 1;
        
        cout << "You got " << count  << " pieces of " << selecteditem.name << endl;
        player.incrementItemCount(selecteditem.name, count);

    }

    void enter(Player &player)
    {
        getMineLevel(player);
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
            if (res == 'q')
            {
                break;     
            }
            if (res != 'm')
            {
                continue;
            }
            cout << "mining..." << endl;
            player.timesMined++;
            getMineLevel(player);
            sleep(player.pickaxe.waitTimeByLevel[player.pickaxe.level]);
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
    cout << "GAME ACTIONS" << "\nm) mine\ng) gamble\ni) view inventory\nb) bank\nw) check weather\n>> ";
    char response[2] = {'a', '\0'};
    cin >> response[0];

    switch (response[0])
    {
    case 'g':
        gamble(player);
        break;

    case 'm':
        mine(player);

    case 'i':
        player.displayInventory();
    
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

    if(player.firstTime)
    {
        mine(player);
        player.firstTime = false;
    }

    while(true)
    {
        mainmenu(player);
    }
    return 0;
}

/*
TO DO:
- Make better monologue (maybe a guide talking to you and getting your name, uk.)
- introduce market (to sell and buy)
- introuce weather system (that determines luck, cannot be changed for next 7 - 15 mines);
- introduce bank (40% of the time there will be a lunch break)
- introduce to buy pickaxe - level one, increases weight  of iron, granite by 0.2, reduce wait time by 1 second. price: 750;
- introduce missions (like side quests)
- event based main menu... so fun!!!
SO MANY IDEAS
*/