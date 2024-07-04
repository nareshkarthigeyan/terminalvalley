#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <vector>
#include "utiliteS.h"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#define MAX_MINE_LEVELS 12
#define WEIGHT 1

using namespace std;

void showMessage(string s1 = "", string s2 = "", int timeOut = 0, string name = "")
{
    if (name != "") {
        cout << name << ": ";
    }
    else{
        cout << name;
    }
    cout << s1 << endl;
    sleep(timeOut);
    if(s2 != "")
    {
        if (name != "") {
            cout << name << ": ";
        }
        else{
            cout << name;
        }
    cout << s2 << endl;
    }

}

char getPlayerResponse(string s1 = "")
{
    char res;
    cout << s1 << "\n>> ";
    cin >> res;
    return res;
}

void achievementMessage(string s1)
{
    cout << "\033[1;32m" << "[ " << s1 << " ]" << "\033[0m" << std::endl;
    return;
}

string moneyAsString(long double money, int precision = 2) 
{
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

    return integerPart + fractionalPart;
}

struct item
{
    string name;
    int count {0}; // change to 0
    float rareity {1};
    long double sellPrice;
    float luckFactor {1};
    float weight = WEIGHT / rareity;
    float buyPrice;
    
};

struct tool
{
    string name;
    int level {0};
    float health {100};
    int waitTimeByLevel[5] = {1, 5, 4, 3, 2}; //to change

};

struct event
{
    bool occured{true}; //change to false before game
    int timesOccured {0};
};

class NPC
{
    public:
    string name;
    string description;
    int interactionCount;
    vector<string> dialogues;

};

class Inventory
{
    public:
    bool hasPickaxe = false;

    tool pickaxe = {"Pickaxe", 0};
    tool fishingRod = {"Fishing Rod", 0};

    //Rarity - lower, the rarer
    item dirt = {"Dirt", 0, 0.85, 1.79};
    item rock = {"Rock", 0, 0.75, 2.75};
    item wood = {"Wood", 0, 0.68, 3.25};
    item coal = {"Coal", 0, 0.72, 5.60};
    item granite = {"Granite", 0, 0.58, 7.68};
    item iron = {"Iron", 0, 0.31, 25.11};
    item copper = {"Copper", 0, 0.28, 23.21};
    item silver = {"Silver", 0, 0.27, 69.69};
    item tin = {"Tin", 0, 0.23, 71.42};
    item hardRock = {"Hard Rock", 0, 0.29, 159.76};
    item gold = {"Gold", 0, 0.09, 595.23};
    item diamond = {"Diamond", 0, 0.06, 2800.53};
    item ruby = {"Ruby", 0, 0.04, 3500.77};
    item blackStone = {"Black Stone", 0, 0.10, 975.21};
    item magma = {"Magma", 0, 0.09, 7200.33};
    item bedrock = {"Bedrock", 0, 0.08, 10000.11};

    vector<item> getItems()
    {
        vector<item> items = {dirt, rock, wood, coal, granite, iron, copper, silver, tin, hardRock, gold, diamond, ruby, blackStone, magma, bedrock};
        return items;
    }

    vector<item*> getItemsByAddress()
    {
        vector<item*> items = {&dirt, &rock, &wood, &coal, &granite, &iron, &copper, &silver, &tin, &hardRock, &gold, &diamond, &ruby, &blackStone, &magma, &bedrock};
        return items;
    }

    vector <item*> getActiveItems()
    {
        vector<item*> items = getItemsByAddress();
        vector<item*> activeItems;

        for (int i = 0; i < items.size(); i++)
        {
           // items[i]->count = 1; //remove this
            if(items[i]->count != 0)
            {
                activeItems.push_back(items[i]);
            }
        }
        return activeItems;
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

    void caluclateWeights(vector<item*> items)
    {
        for (int i = 0; i < items.size(); i++)
        {
            items[i]->weight = WEIGHT / items[i]->rareity;
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



class PlayerEvents
{
    public:
    //Event List
    //boot event:
    event firstBoot;

    //mine events
    event inventoryUnlock;
    event mineDetailsUnlock;
    event quitMineUnlock;
    event dualItems;
    event shopUnlock;

    //bank events:
    event bankBoot;
    event bankOnLunchBreak;
    event loansUnlocked;

    //market events
    event sellerMarketBoot;
};


class Player : public Inventory, public PlayerEvents
{
    public:
    string name;
    long double bankBalance;
    float luck {1};
    int timesMined;

    bool firstTime = true;


    void createPlayer(string namePrompt)
    {
        name = namePrompt;
        bankBalance = 0;
        timesMined = 0;
    }

    void display()
    {
        cout << "Name: " << name << "\nBank Balance: $" << moneyAsString(bankBalance) << "\nLuck: " << luck << endl;
    }
};

//NPC INIT:
NPC Vivian = {"Vivian", "Bank Handler", 0};
NPC Manjunath = {"Manjunath", "Buyer. Likes Dad Jokes", 0};
NPC HomelessMan = {"Homeless Man", "Asks for spare change. Claims to be your guardian angel", 0};
NPC Redacted = {"???", "Player guide.", 0};
NPC System42 = {"System42", "Prevents 4th wall breaks.", 0};
NPC BillMurry = {"Bill Murry", "Weather reporter.", 0};
NPC Rick = {"Rick", "Guild Master", 0};

void npcDialogueInit(Player &player)
{
    Vivian.dialogues = {"Heyy... What's up!", "You know, sometimes, the bank manager says I need to be more polite, but I don't understand - aren't I poilite enough?", "I wonder what's for lunch today... spheggati would be nice!",
                        "Do you need a loan?", "Don't you think pinapple pizza is a crime?", "The best food is eaten when you're the most hungry!", "I have so much paperwork left...! It's making me so hungry!!",
                        "I'm really looking forward to my lunch today!", "I went to my best friend's marriage the other day, and the food was awful!", "The bank manager is such as ass sometimes, he calls me to his cabin for no reason...",
                        "I'll go check out the restaurant across the road after dealing with you.", "If the universe started from big bang, what's before big bang? What's the something that made nothing into not-nothing?",
                        "I'm not it the mood to talk now, tell me what you want...", "The best way to ask me out on a date is offer me food.", "Sometimes I think I'm not good enough, but then I see other people who are worse than me, and then I feel better.",
                        "Am I married? Uh....", "...", "[picks nose]", "My last boyfriend was a jerk, but he was the best chef in town though...", "Why does imaginary use of numbers in economy hold so much power?", "Do you think the terminal universe also has inflation?",
                        "It has been 3 hours not thinking about food.... oh... I just did.", "Nothing makes sense in life.", "Between you and me, the credit card system is rigged to make you poor, but that's just me though.", 
                        "You won't believe me, but when I walked into the bank manager while he was changing, I swear he wore panties!", "The Indian filter coffee has got to be the best coffee in the world!", "Uhm, why haven't I accepted your request on Instagram...? uh...",
                        "Hey, have you got any gossip?", "Do I manupilate tax papers? How rude...", "I could really do for a cake right now.", "A few years back, I use to like a guy named Oscar, too bad he was gay."};
}

string getDialogue(NPC npc)
{
    int size = npc.dialogues.size();
    string dialogue;
    int random = randInt(0, size - 1);

    dialogue = npc.dialogues[random];
    npc.interactionCount++;
    return dialogue;
}

class Events 
{
    public:
    void FirstBoot(Player &player)
    {
        clearScreen();
        showMessage("...","*blinks*", 2, "???");
        sleep(2);
        showMessage("[looks around]","Where am I?", 2, "???");
        sleep(2);
        showMessage("I'm in a...","I'm in a terminal?", 2, "???");
        sleep(2);
        showMessage("ahhhhhhhhhhhh","How could I forget...", 2, "???");
        sleep(3);
        showMessage("HELLO DEAR WANDERE-*cough* *cough*","sorry, I can be such a klutz sometimes.", 2, "???");
        sleep(3);
        showMessage("You know, it really wasn't supposed to be like this","but ever since *that* thing happened-", 4, "???");
        sleep(2);
        showMessage("Well, where are my manners!","My name is [redacted]... and I will be your guide to your [redacted] journey through the-", 3, "???"); // replace with gibberish
        sleep(3);
        showMessage("What?","You don't know why you're here?", 3, "???");
        sleep(3);
        showMessage("That's strange","This has never happened before...", 2, "???");
        sleep(3);
        showMessage("Oh, OH, maybe...","", 0, "???");
        sleep(3);
        showMessage("the \033[33mprohphecy\033[0m...","it can't be..... can it....?", 0, "???");
        sleep(5);
        showMessage("TELL ME YOUR NAME WANDERER! AT THIS INSTANT!", "", 0, "???");
        string name;
        cout << ">> ";
        getline(cin, name);
        player.createPlayer(name);
        showMessage("checking database....","really checking database.....", 2);
        sleep(3);
        showMessage("This is really strange...","I can't seem to find your name.", 2, "???");
        sleep(3);
        showMessage("\033[32m[DATABASE BREACH. SEARCHING UNAUTHORIZED INFORMATION. SELF-DESTRUCT INITIATE]\033[0m", "", 2, "SYSTEM42");
        sleep(2);
        showMessage("Oh no... run away, wanderer.","You are not supposed to be here.. the prophecy...", 2, "???");
        sleep(2);
        showMessage("", name, 0, "???");
        showMessage("!! GET AWAY FROM THIS PLACE -- CLOSE THE TERMINAL! AT THIS INSTANT-","", 0, "???");


        sleep(1);
        showMessage("\ni̴̡̛̲͍̪̞̞̠̥̘͈̳̙̠̘͖̲̫̦̮̠͙̦̋̔̔̑̔̈̂͜͜b̸̡̧̖̯̹̗̜̫̻̫͇̖̩̲͕̗̼̎̍̑̅̒̌̒̀̕͜e̶̡̡͖̞̥̯͍͚̲̖̥̬̩͎͉͙̪̳͛͋̀̓̏̏͋̏̐̓̉͊͊͠͝͠a̴̠͓̓̀́̈̅̓̈́k̴̢͇̩̹͇̮̭̪̗̙̼̟̲͇̦̼͗͜į̶̼͙̺̥̗͓̙̜̙̭̬̙̇̓̆́͋̒͗̀͒͗̽̕͝͠͝b̸͎̰̠͓̪̤͕͈̙͊̔́͋͊͆͛͌̿͋́̎͆̋̏̐̆̚̚̕͘͠l̸̨̢̛̛̘͈͔̞͍̳̼͉̘̺͔̦̦͉̫͂̿̾̿̃̔̒͑̊̆̔̉͐̔̄̌̕̚͘͝į̷̨̛͈̥̼̹̂̊̈́̅͗̉̉̔̆́̋̀̋̅͑̈́̑͜ͅͅw̴̼̰̺̤̤͈̼̻͈̗̼͖̘̉̐̊̊͑̈̑͂̈́͗͐̊͂̍̀̍̃͠ḙ̴̡̢͇̭̤̲̘͙͑͒̊̄̔̂͆́̑̅̈̈́̆͂͛̈́͑͐̏̎̕̚̚͝ͅư̷͖̮̩͈͓͕̭̯̻̯̘̖̙̳̻̖̆̓̉͂̔̓́̒͑̅̓͊̂̕̚ą̴̧̻͖̘̰͙͙͂̂͐̑͐̈͂b̶̧̠̳͚̘̠̭̼̮͖͓̦̰̝̝͚̹͑̾͑̀͛̒̌͛́̇͒́̕͠i̵̤͙͈̫̠̥̟̱͙̮͎̋̑̋i̴̛͍̠̤̼͇̜̠͙̩͖̳̰̭̍̋̋̐͆̃̈́̏͒̈́̒͌̽̿͘̚̕w̸̟͛̈́͌̏͋́̍́͛̑͗́̕̚͝͝e̷̡̫͖̣͇̻̙͖̫̹͕͍̜̳̰̟̐̆͂̂͘͠͝b̸̨̢̠̺̩̺̭̮͉͍̥̮̺̳͈̳̑̿̌͋̎͑̿̇͊̕͜͠͝ͅͅͅl̸̡̢̯͚͖͍̮̹̱͓̬͚̩͎̮̃î̶̡͓̱͕̠̦̭͜q̶̿̿́̃͛͐̍̓̿̀̾̋̐̔̀͌̈͊̈́͆͝ͅą̵̪̥̹̞̥̠̺̥̟̰͙͓̤͔͚̪̲͚̅̃̊̎͂͌͊̂̃͊̃̒̚ͅȩ̵̬͍̩̱͖̮̪̔̌̉̇̊́̈́b̵̻̩̦̔́͆̒̆̓̃͐̚̕͝l̴͈̝̮͎͙̟̊̃͋̊̎͊̚ĭ̶̢̛͍̤͔͈̜͔̣̖͙̖͉͍̟̝͕̦͙̝̈̋̀͂̉̉̃̔̔͒͜ͅu̵̹̗̥͂͑͆̌̇̽̔̒̿̌̍̀̓̈̇̚͠͝v̶̛̛̼̗̦̖̲̹̩̫̩͎̠̖̪̥̻͓̼̠͖̺̓͗̐͆̿̽͌̎̅͋͗͋̃͌̌̓͐̊̚͠͝ḃ̷̨̛̖͈̜̥͚͓̳͙̫͔͉̩̹̫̀͋̔̓̆͛̕͠ͅͅq̵̣̟̲̎͊̀̆̿̒́̍̋̽̄̇̌͠w̶̧͔̯͉̺̅̂̑̎̑̉͒̎́v̷͚̀̀̓̏̍͆̃̀́̑͒͐̀̑̕͠e̵̱͐̌̔̂͌̋̃͑̄̒̒́̂̕̚͝͝į̷̧̢͚͈̟̙̻͓͕̙̘̙̘̮̼̘͔̙͉̯̐͜͜ͅu̵̡̢̧̫̗̳̲͇̜͚̤̠̲̞̟̟͌́̃͐̅̐͆̾̔͑̆̏̂́͋̀̒͋̆̕͝b̵̡̩͕̥̟̲̤̻̙͉̠͑̇̐̎̈̃̉̓̿̌̈́̊́͌̚v̷̨̮̤͙͓̣̭̫͓̞͔̰̼͍͖̭̲̈̉͊̒̓̒́͑̕͠ͅḭ̵͇̻̱̩̗̟͕̥̗͖͉̗̩̹̖̈̇̾̾̓̕u̸̢̹͊̿̓̂̀̈́̉b̷̨̖͚͖̬̰̪͕̻̞̮̠͙͕̻̫̖͓̹͉̟́͂́͛̽̄͊̇͆̚̚͠ͅḯ̷̢̢̡͓͚͕̖̠̳̖̓͜͜͠ȇ̵̢̢̞͕̰̻̫͎͎̦̖͍̈́̍̓̃̌͆̀̾͑͆̄̅̉̀͋̅̀̈́͂͝͝į̵͓̺̈́̒̅̆̾̾͘w̵̗̭̖̻̪̰̺̗̜̩̼̩̜͉̗̺͌̈́̏̒̆̌͌͂͋̑̊̀́̊̓̀̅̔̕͠͠c̴̯͈͚̓̂̈́̐̋̂̑͊̏͗̃̏͊̀̾͘͠͠d̶̢̢̗̯̬̳͇̜̬͍͔͎͇͚͔̭̃̎̄̋̾̂̑́͂̏̄͊͂̅̀́̾̇̃̕̚͜b̸̨̨̡͉̮̖̮͎̟͔̯̯̞͖̞̾̏̄͆̅́̾̍͗̒̊͂̏̈́̽̔͌̇̀̂̚w̴̺̬̦̺̦͙͖͊d̷̡̧̮̗͔̩͎̯̪̻̖̟̀͗̈́͗͋̕͝ĺ̶̛̺̯͕̦̣̭̥̠̭͎̩͎̼̹̝̲̭͉̤͔̿̏̆̾̿́̈́̑̌͘̕͝ç̸̧̢̧͔̙̦̩̭͙͖̺͍̦̭̱̟̍̍̏̓͊͆͑̕͜͜͝ͅȉ̷̢̛̺͎̹̟̗̹͙̼̜͖̈́̆̿̓̉́̏͂͌͐b̴̢͓̱̣̰̟̲͍̯͖̲̪̙͎̻̪͓̠̳͕̦̝̄̂̑̐̍́͒̚͠ͅͅi̷̛̯̗̰̺̟͓̰̟̤͈͊͆̍̈́̐̈́̍̋̀̈̇̆͂̀̈́́͛͘͜ͅb̵̧̬̘̦̺̦̙͕̦͉̙̩̲̗̖̤̅̎̉̈́̉͑́̏̈́̿̿͛̅͐̍͋̇̈́͘̚͜͝ͅͅv̸̡̢̧̧̞̣͓̱̣̖̪͈̖̲͇̠͍̠͎̱̙͇̑̍̈́̚͘͜q̸̧̨̩̮̜̣̲̠̺͍̌͌̑̀̏͌͒̕ḯ̶̧̳̳̳͉͒͗̀̑̕ư̸̡̧̧̮̗̠͓̬͚͈̪̻̦̻̙͔̦̖͕͔̈́́̃̉̊̎́̂̊̂̽̃̉͝͝͝b̶̤͕͉̤̰̼͕̼͉̻͚̮̲͕͉͂̃͛͜ͅͅķ̶̡̳͖̞̜̻͉͈͕̪̜̗̼̠̥̹̩̲̝͌̓̔͛͗̏̆̈͋̀̓̑̈́̚̚s̵̢̛͎̱̟̻͎̞̩̖̓̈́̂͌̀͛̉̀̀̚͝j̸̡͉̹̤̪̮̣̱͉͇͇͈̞̬̰͕̯́̊̄̔͂̚̚͘͜͝͝b̸̛͈̮͉̩͑̀̓̀̒̀́͑͒͂̋͋̈́̄͛̕͘͠͝͝͠à̶̢̼̜͆͐̀͆̔̃͒̐̃̾͌̕l̴̠̝̼̈͠͝k̸̡͙̗̠͖̞̝͙͈̩͎̹̮̣̹̠͐̽̈́̊̐̅̃͝ś̷̛̪͈͈̖͚̝̼͔̥̬͎̝̱͖̹̞̠̯̞́͌͒̊́b̵̘̯̫̜̌̍͗͊̒͊͑̽̌̒̾̔̈̂̒̐̀k̴̘͕̝̐́̈́͑̋͘͘s̸̡͔͚̥̯͕̯̤̳̈̆͌͋̈́̉͘d̵̡̧̢̞̟͉̞̟̩̘̝͍͎͔̮͍͎̝̞̠̻́̋̓̏͋̎̄̉͒͗̀̊́̀̕̚͜͠v̷̮̣̌̈́͆͗́̈́̕̕b̴̛͕̬̰͎̬̳̜̮̯͕͎͇͉̘͓̲̱͎̩̖͙̈́͌̓̈́̃̋͆̉́͜ķ̵̨̡̛͓̙̮͎̼̞͓̳̩̠̝͇̱̲̱͂͒͒̆̋̊̿̄̏̈̾͊̌̾̂̀̆̍͝w̵̢̧̨̛͕̦̹̹̦͉͍͓͕̜͙̺̬̻̐̓̂́̀̏̐̔̅̐͑̿̚ͅͅş̷̛͙͔̲̟̻̱̹̯̻̮͉̟̣͌͒̂̋̓̾͑̈́͋͠d̸̡͖̪̰̯̜̺̤͉̥̹̘̱͓̜̋̅̍̏͛̄̓̂̏͆̊͛͐̀͝͠͝v̶̨̭̩̯̘̜̝̬̩̲͍̰̱̮̔͐͐b̴̠̞̘̥̗̦̦͇̦̘̘̦̠̙̘̤̜̥͍̋̓͐̓͐͒́̈̍̂̽͊̕l̶̫̜̞̗̹̺̮̖̬̦͉̅̽̉̌̇̂̀̾͛̌̚̕͘͝͝k̵̛̛̛͉͈̝̳͉̻̝̜̼̥͎͍͙̫͚̺̊͌͆̈́̎̚̕̕͜s̵͚͕̅̀͐̑̚d̴͉̙̄͂̽͘͝b̶̛̻̭̮̣͈͗̎͐͋̃͆̒̍͆́̾̒͛ķ̵̨̧̡̗̥̬͈̱͔̦̤̬͚̲̫͉̠̪̰͔̠́ṡ̸̡̨̡̛̮̰̙̮̹͚̜̺͖̘̫̳̹̲̩̞͇͙̉͑̆̄̉̔̑̇̓͒̐̾̔͘͜͠͝ͅd̷̢̘̰̰̺̞̦̝̠͚̝̟̼͖̿̐̈́̈́͐́̃̍͌́̉̈́̌͋͌͘̚͜ͅḅ̵̛̰̝̰̫͙̬̠̺̩̺̺͛̄͒̍̍́̂̍͒̈́̀̀́̅̏̀́̚͠ͅļ̶̨̢̹̬̰̳͕͙͈̞͙̠̜̗̰͌̀̃̈͛͗͊̏̄́̄̆̊̒̋̍̓͆̈́̕͠͠͝s̷̞͖̣͖̝̐͒̇v̴̧̨̛̭͍̭̦̖͍͉̈́͊̋̆́͊̔͆͒̍̔̑̄́̀͛͑̿̉͘͝k̵̡̡̡̳̘̬̜͔̲͈̠̂̊̓̈́̀̊͋̿̈́̇͘̕͘͝j̸͕͇̲͚̜̟̤͈͕͕̠̦̹̬̲̫̪̩̮̫̿̒̒̓͌͊̐̏̑̊̀̃̃̒͝͝b̶̨͓̠͚̖͕̻̦̙̼̲̗͇̳͕̙̦̦͈̍͒͒̽́̐̏́̈́͂̇͛͒̓̓͆̆̆̕͘͝ṡ̵̡̨͔̝̱̖̰͖̦̹̰͍̯̦̟̬̭̏̅̄̓̍͌͜ͅl̷̝̠̗̻͖̰̱͎͔̹̠̣̤̱̣͚͍̞̪̲͓͆̒̔͐͛͜k̶̄̀͜d̷̢͙̬̞̅̈́̍͒͆̃̅̈́̀̀̉͗̋̋̈́͐̚͠͠j̷̪͙̳͓͙͇͖̥͙͉̼̩̪̩̖͗̽̈́b̴̤͉̥̩̾̉͂̔k̷̨͎͚̻̣̭͔̤͇̜̱̳̫͇̫̝̐̅̎̈́̍̅͠ͅͅs̴̛͚̜͓̻͙̦̞̏͗̐̆̆̇͊̏̇̄̿̆̊̆̃̑̇̀̿̍̏̚ͅb̵̨̛̜͍͉̆̄̍̉̐̿̀̇͐̔͘͠l̸̡͍̰͔̝̂͑̌̌̚v̷͙̦̥͓̙̫̲̥̘̖̯̰̬͇̓́̈́̉͜͠s̵̨̢̨̛̱̞̻͇̤͎͕͖̟̝͓̼̮̻̤̾̋̏͋̈̽̊̃̊́̈́̀͊̊̋̏̑̀̕̚k̷̢̢̘̳̮̰͍̘͙͔͕̘͍̯̣͐̃̾͗̎͗̌͂̀̔͋͒͑̌̇̾͒͌͘̚͜͜j̵̡͓̫͇̩̬̮͕̰͍̹̮̣̩̎̅̊̽̐̎̇͒̀̈́̄̀̕̚͜͜͝b̴̢̛͚͉̣̱̦̜̭̗͕̹́͊͛̍̌͂̈́͊̈́̾̈́͘͠͝l̷͚̰̳̭̜̩̇́̍̇͆̿͆͑̈́͘͘͘̕ṣ̶̢̢̣͚̗̭͖͚͌̈̾̓̽̆͐͌̿̾̃̃́̚͝͠k̸̛̖̻̼̰̭͍̘̭̳̞̭̤͔͚̲̦̄́̾͂͗́͐̆͂̑͊̀͌̈́͑͗̌̊̾͊̆͘͘͜ͅj̴̡̛̞͙̘̳͍͉͕̞̱̝̯̤̾͐̾͊̈́̌̃̋̽͌̎́̏̔̓͒͑̓̈͘͜͠͝b̴̨͎̞͈̳̥̝͕͈̙̝̼̥͎̖̟̪́̾̃̑̃̾̿̍̐̕͘͜͜͜ş̸̡͔̘̹̪̪̖͇̩͉͇͚͈̹͍̱̟͚̆̆l̸̨͔̱͖̟̭̯̠͖͍͚̼̭̙̐ͅd̵̛͚̯͙̦̓̄̈́͑̿̀͌͛̃͑͛͂͛̚͘͝ͅk̷̖͊͐͆̊̃̓͌͗́̍̈͐͒̈̌͑̋͐͊͝j̶̢̢̢̢͖̝͙̭͉̦͖̠̩̭͑͒̈́̔̆̐̄̈̀̀̀̽͗̊̃̇̆̓̆͂̂͘̕͘b̸̨̳̰̻̪̘̬̭͎̩̙̜̳̰̮̼͔̯̥̔̾̈́͂̅̔͝v̶̛̝͔̝͍͕̹͎̼̯̟̏͒͜͜͜s̷̡̛̠̦̠̤̘̤̙͙̯̙̿̾̌͑̊̉̇͗̉̀̓̋̎̎̉̔͛̚͜͝͝͝l̵̰͙̣̬͛̓̂̈́̀́́͑͗͒͊̉͋͑̒͊͠k̸̡̮̰̟̠̬̭̰͒́́͠ͅj̴̨̲͕̰̗̗͚̠̗̰͚̜̬̮̬͍̫̗̹̯͐̊͜͜s̵̨̨͔̥̣̯̜̻̪͖͕̥̬̓͑̔̃̌̔̀b̷̢̛̟͓̞̗̻̹͈͙̺̗̲̖̓͂͊͛̓͐̊͗̅̋̍̉̀̊̊̎̿̓́͘̕̕ļ̶̛͈̯̙͇̮̬̖̱͎̭͔̬̺͎̰̹͈̱̰̆̿̍̋͛̾̂̋̒̍̑͌̕͝k̷̨̨̧̰͉̖̪͚̳̩̱̘̜͔̮̽̉̀͋̿̈s̷̢͚̦̘͈̞̍͂̂̏̈́̇̂̓͗͛̑̃̅͂͒͂̍̈́̚͘͝͝d̶̨͚̙̟͇̩̜̪̯̞̩͓̝͎̩̞̩̗͓͙̀̊̌̀̓͛̆͐͂̄̿͑j̸̛͚̳̹̰̮̰̺̆̈́̄̅̂̉̀͊̾̏̕͘͝b̷̢͙͓̪̳͈̺̜̥̼͈̽͆͋͒̃̎̓̆͛̐́̓̓̽̆̈̚̚͘͝͠͝v̴̢̨̰̰̺̰̭̼̗̼̞͚̯̯̾͒͑̂͛͆̈́̌̿͂́́̃̎̑̑̾̚͜͝͝͝͝͝ͅl̴̮̮̠̞̟̥̰̫̹̝̹͓̠̣͔̟̠̯͔̾͆̀́̒̉͛̚k̷̛̯̓͌̋̀́̅̓͂͗͆́͂̆̌̀̈́̾̚v̴̛͔͎̘̦͌̑́̎͐̍͒͊͑̋̏́̔̓͝j̷̨̗̝̰̦̣̫̲͉̹͚͇͔͈͕̱͖̟̊̄͒́̓̓̆̎́͐̂̏͒̅̾́͐̂͜͝b̷̛͔̣̦̗̊͆͆̊̀̐̑̌̌̿͊͒͘͝ͅl̵̢̢̹̥̹̻͔̠͎̳̤͔̣̳̦̱̪͉̜̟̲͊̾̒́͂̀̿̈́͊́̀͐̀̊̃͛̂͝k̶̡̡̪̻̜͛̅̈́̅̈̐͛̈́͊͌̂̆̒̎͋̒͛̊͘͘͝s̸̢̨̨̧͓͔̖͖̻̜̞̼̱͇͕̣̪̪͙̠̟̖͎̈͋̌̃̓́̾͛̑͆̏̀̍̄̓͂̒͝ͅj̵̡̛̰̬̰͈̪̦̦̞̐̇̈́̌͗̏͠͝ͅb̶̜͚̀̈̍͐̐̊̋̔̍͆̈́͠ḽ̴̤̬̗͎̙͒̏͆̍͆́͆̈͝ȃ̴̡͕̩͔̤̮̘̮̱̻̺͓͚̭̟͚͕̰̹̦̠͜͠ͅk̸̛̟̪̈́s̸̛͓͕̤̻͎̺̼̪̗̝͈͖͂̈̅̕͜͜d̵̛̳͖̱̰͍̔̀́̋͗̆͋̽̅̂̍͆̔̀̚̚͜͝ͅj̶̢̧̟̤̤̳͇͍͍͙͍̫̥͆͒̆̏̓́̽̐̕͘͜b̶̮̪͖͚̠̝̠̬͖̩̻̈͑̇̒̇̈́͑͊̆̇̓̃͆̔̐͋̅͋̀̌͜͝͝͠͝ͅl̴͔͍̜̬͚̬͕̼͇͖̟͚̝̯̮͉̻̖̪̪̬͖̫͐̄̓́̓̇̚͝k̴̨̼̩͈̺̪̩̜̣̪͔̮̩̺̱̫̝̜̐ͅͅs̸̛͔̺͐͐̄͋͗̊̇̓͝͝j̵͉͔͈̫̯̔̃̑͊̀͑̋̌̚͘̚b̵̨͓̥̺͔͕͍̣͍̝̻̙̲̩̗̬̳͉̖̤̬̺̊̀̽̐͂͗̃̕͘͜͜v̷̛̛̩̪̄͛̃͆̓̈́̊͗͂͑̅͒̽͆̐̎̈͂͘͝͝l̶͈͎͂̓̎̔ķ̶̡̢̛̛̺̪̣͖̣̠͔̳̟͓͖͉͗̈́̈́͐̌̊̓̐͋̀̀̊̀̍̌͗̄̆͘͘͜͝s̶̡̧̡͔̠̲͈̲͎͖̺̥̯̺̬̻͍̠̦̞̳̖̭̀̇̓̂͊̄̅͝ͅa̶͙̱̥̜͓̖͇͔͚͓̲̙̻̟͈͙̙̞̟̜͚͘ͅj̸̫̰̯̬̮́̓̏̌̚b̸̡̡͇̹͉̦̘̩͉͚͎̠̩̪̥̱̬̘̳̓̆̏̍͊̾̽͜ͅȧ̴̛̼̜̥́̄̎̈́͂̅̂̓̿͘̚͝͝l̷͙̹͔̮͚͖̰͓͉͒̾̌̿̓̀̎̂̏̅͆̊̆̕͝͠ͅş̸̨̨̺̫̦̾͒͌̌̅̎͂̉͘͜k̸̨͈̠͕̞͈͔̺̦̳͑͑̊̆̍͛̿̉̀̀̃͆̑̚̕j̷̨̨͇̤͍͔̩̻̙͉̬̫͙̺̪̤̻̯͚̬͓̏͝ͅͅb̷͎͎͎̞͓͉̜͚̯̰͚͒̄̅͊̎̇́͐͋͆͐̅͑͆̀̚͜͝͝͠ạ̷̹̮̮̭͍̼͓̭̰̖̈̀̎̿͑̌͑͒̒̇͒̏̃̔͌͊̚ş̸̨̦̘̝̼͔͓͚̭̠̝̝̝̮̖̜̣͈̻͍̱̼͗͑̔͋̑͑̇̅̄͆̈͆̅̊͠v̶̢͍̺̆͜d̵̼̲̖̯̤̰̱́͗͒ķ̸͓̻̭̯͈̟̪̝̬̬̥̗̱͇̹̮̈̊̄̍͛̊̈́̄̕ͅj̶̢̧̢̢̩̫̗̦͕̝̩̩͎̹̭̏̇͒̎̾́̃̊̒͐̀̈́̒̉͋̾͗̽̈́̕͝͝͝͝b̸̨̢̛̠̳̣̮͚̦̯̯̬͖̈́̅͗͑͆̿̍̽̎͗͒̈́̈͂̑̈͋̓͘̚͜l̵̡̡̛͖̦̗̹͖̺̲͇͙͍̱͗̍̋̎̊͆̈́̀͐̇̓͐̽͛̌̓̋̔͑̿̊̔͝ͅͅs̶̢̡̰̰͇̺͍̹̞̝͖̙̟̩͖̼̟̺̥̿̍̕͝ͅd̴̨̨̼̪̞̻̞͇̰̻̠̗̣̼̦̮̑̾͂͜͝ͅa̴̧̧̢͕̤̙̬͙̞̻̜̙͓̥̗̽͂̈̃͒̐̔̾̊̂̅̃̊̐͌̓̕͘͝ǩ̸̮̼͈̠̩̱͖̳̜̝̞̥̞͈̺̬̹̠̗̎͐͆̒͌̂̉͒͆̕͝j̸̨̡͔̟͈̖̠̥͔̟͙̞̮͍̟͉̫̠͍̤̹̭̰̆͒̎̋͗́͗̆̔̈́̚͘͠͠͝ͅb̶̨̛̖͎͔̮̳͔͈̦͉̤̤̣̩̜̥͙̽̓̾̆̒̇̏͛̌̀̓̅̊̌̚̚͘͘͝ͅv̴̧̨͔̠͖̺̥̬͈̲͇̱̹̤͔̭͔͈̦̟̳̆̾͒̾̃̉͊̾͆͜͝ĺ̶̨̝͕͓̘͖͕̟̩̝͙̰̰̳͗͛̒͌̽͛̃͂͂̆̿̉͐͛́́͑̾̈́͘̚̚͝ḑ̵̯̗̜̮̞̼̱̜̜͚͓̱̯̺̯̪̲͕̳͚͔̌͌͆̀̓͒͂́̐̈́̈́̀͋̇̄̀̈́͝ŝ̶̹̳̦̝͉̩̠̄̔̊͂̂͆̂͑̓̽̊͂͠ͅķ̷̳̲̙̖̻̑͑͒̊͂̄̀͑̃̎͂̄̿́͆̔̽̎̅̒̾̿͘̚͜d̶͚̬͔̳̖͙͇͉̜͙͗̉̇̏͌̽͜j̵̧̖̟͉͚̮͑́̓̇̿̍͂̀̋̈̅̆̾̈́̀̾̓̆͒͝͠b̷̦̫̲̻͈̪͍̩̳̱̋̾̑̊̄͗̓͐͐̄̊͋̊̾̈́̎̒͐̕͜͝͝͠͠v̷̢̧̛̞̬̘̭͈̹̣̱̮̽͛͊͊͆͌͛̽̽̏̉̽͌͛̚͜͝͝͝l̵͍̲̰̥̙̭̻͇͎̞̺̹̝͎͕͇͛̚͜͝k̶̨̤̪̜̻̣̰̜̤͙̼̼͔̓̇̈́̅͌͊̽s̷̪̝̠͚̣͈̤͔̙͒̐̆̈́͊̇̇̆̀́͋͆͂̽̏͆̇̒̚ã̴͔͓̯̤͉̹̘̱͉̤̝͋͊͗̿̆̾̕j̸̡̧̢̙̝͙͖̪̭̋̊́̏́b̶̭̰̲͙̮͙̙͔͉̹͓̐͗̚͜͝ͅͅͅĺ̶̢̯͖̗̗̳͇̦͚̮̲͔̪̜̣͓͕̰̬̈̑̓̍̀̓́͛̅͗͐̕͘k̶̞̭͊̄̌̋̀̚s̶̛̛̼̹̗̙̩̈́͒͋͛̓́͋̏̑͊̍̔͒͋̽͐̈́̇̚͠͠͝j̵̭̥̱̙͕̋͌̓̒͐̒̅͆̒́b̴͚̋̽̀̍͐͛͂͊͐̆̈́́̈́̂̂̿̓̓̾̊̕̕͘s̴̠̼̰̺͇̩̞͖͓̰̤͔̹̟̹͇̣̫̲͖̫͖̖͓̉̂̆̃̄͗͛͗͂͐̿̓̓̈́a̸̻̙̖̰͎̰̲͊̾̀̋̍͋̿̎̿̀̂̍̒̀̎̚̕͠͝͝͠l̴̪̩̜͉̮̹͚̳̐̓͒̑̐̐̂̃͛̃̓̐͜͠k̵̡̛̛̠̭͈͔͍̰͎̟̱̥̟̑̏̉͛̏͗͗̊͑̌͊̀̉̅́͒̿̐̓̕͠͠j̶̡̨̧̧̛̛͓͍̱̟͈̘̳̱̦͍̝̜̰̣͈͉͔̫͈̿̃̈́͒͂̍̈s̶̡̛͙̪̟͇͍̲̘͇͚̅̎̾̆̿̾͐̀͒̇́̾̃̒̕͘͠͠b̸͕̻͎̦̻̻͓̬̗̦́̄̀͑̕͝ĺ̵̠̼̱̫͚̩͓͎͚̼̱̰̦̮̹͖͖̼̼̱̲̲̅̃̓̅͋͒̈́̓̔̏̀̿̉̃̃̉̈́̒͜͠k̸̢̨̡̛̦̩̗͖͚̹̯̠̟̮̣̬̬̬̯͈̺͔̊̋̂̓́̀̍͒̂̿̌̆̂̚͜ͅͅa̸͕̯̟͙̮̬̫̲͓̞̜͙̘͙̤̮̯̥̠͈̯͑̍̽̍̽̅͗̑̿̉̏̐̎́̀̈͜ṣ̶̺͈̮̠͕͎̜́̔̽̅̉̐̈́̄̋͌̀͊̓͗̀͗̓̎͝ͅd̴̨͚͎͓̿ͅṽ̶͙̺̭̊̉̈̎̃͐͑̂̈́̿͗̎̓̎̒̉̍͊͜b̷̤͓̭̲̑̅̃͂̅̂͘ḽ̸̡̡̛͖̘͚͚́̽̌͂̆̋̈̊̅̄̎̐͗̾̑̓k̴̛͇͍̤͇̙͎̼͔̗͙̮͕͙͈̯̼̹̱̘̣̑͊̒͋͂́̓͌͛̃̏̂̍́̽v̸͓͚̻̩̦̻͉͈̯̲̭̼̣̬͚͔̫̙̩̮̂̅́̅͒̈̊̉͆̍̇̆̐̌̈́̌ͅͅs̷̨̲̪̱͈̮͕̱͍͕͖̦̞̥̱̜̓͗̓ḑ̴̦̹̗͖̠̳̭͓̠͇͌͛̊̈̈̓̒̋̐͂̅̾̊͘̚̕͝͝ą̸̟̮̙͕͙̗̺͓̟̭̘͓͈̋͌̍̅͌͛̉̉̋̔̊͂̌̑̾̚͝b̸̰͇̞̗̹͉̳͉͎̙͍͎̪̮̟͔̮̼͒̈́͋̃͌̄̚ͅs̶̛͓̯̗̲̰̗̮͖̦̘͙̬͈͔͎̠͉̬̫̓̐̉̃̃͂͗̈́̇́̚̕͘̚̕l̴͉͚̩̎̈̈́̐͆̓̈́̏͘d̴͓̣͈͇̠̙̳̎͊͂͒̀̅̈́̎́͋k̶̙̘̆̈́͂͋͒̂͆̔͑̋͋̄͛͛̐̚͘̕̕͠͝b̸͕̗̳̫̲͒̉̈́͊̑́̉̑̌̈̓̾̌͒ś̵̢̡̢͕̜̰̥̥͎͖͎̺̺̠͉̆̅̓̐̌̅͝ͅļ̸̨̠̝̬͈̬̦͈̙̲̼͇͙̦̠̭̺͐̉̇̐̀̉̅͘͜͜ͅk̸̡̡͓̦̥̬̣͍͓̲̒̀̔̋̔̊̚̚s̵̡̖̤̙̝̠̺͚͎̼͈̝̗͈̞̲̮̈̅̈́̉͐̓̃̈́̎́͑̋̽̂̃̋̏̕͘͘͝͝a̴̧̨̛̮͇̟͕̣̹̙̖̥̜͇̱̦̗̫̠̘͔̩̅̆̓͊̎̿̅͌̾̋̿̓̌͋̂̈͗̄̓̕̚͜͠ͅb̵̢̰̞̝̥͉͙̟̜̘͕̜͆̈́̾͐̔̆͛̉̚̚ͅͅs̷̙͚͈͙̽̅̏̓̈́̊̊͂͑́͊̐̄̇̀̾̊͝͠a̵̛̛̲̜̟̜̻̺̠͖̣̤͖̲̍̆̐͋̋͐̃̆̔̅̊v̸͚̬̮̉̍́̀ķ̸͎̠̺͖̮̯̦̠̺͓͉̠̟̜͓̖̗̫͛̍̾̾̍̉͌́̌̾̽̊͘ḏ̴͙̎̈́̅̎́͛͊͒̀̄̍̿̈́͐̆͘͝j̷͔̠̥̩̗̩̍̿̽̇̐̃͂͌̚͝͠b̵͉̻̟̺͙͗̍̈́̆̋̀̆͋̐͋̈͗͑͊ͅḇ̸̛͈̟̮̺̙͈̹̘̬̭̥̻͈̲̻̓̿̌̊͂͐̎͐͊́͝b̸̡̧̖̯̹̗̜̫̻̫͇̖̩̲͕̗̼̎̍̑̅̒̌̒̀̕͜e̶̡̡͖̞̥̯͍͚̲̖̥̬̩͎͉͙̪̳͛͋̀̓̏̏͋̏̐̓̉͊͊͠͝͠a̴̠͓̓̀́̈̅̓̈́k̴̢͇̩̹͇̮̭̪̗̙̼̟̲͇̦̼͗͜į̶̼͙̺̥̗͓̙̜̙̭̬̙̇̓̆́͋̒͗̀͒͗̽̕͝͠͝b̸͎̰̠͓̪̤͕͈̙͊̔́͋͊͆͛͌̿͋́̎͆̋̏̐̆̚̚̕͘͠l̸̨̢̛̛̘͈͔̞͍̳̼͉̘̺͔̦̦͉̫͂̿̾̿̃̔̒͑̊̆̔̉͐̔̄̌̕̚͘͝į̷̨̛͈̥̼̹̂̊̈́̅͗̉̉̔̆́̋̀̋̅͑̈́̑͜ͅͅw̴̼̰̺̤̤͈̼̻͈̗̼͖̘̉̐̊̊͑̈̑͂̈́͗͐̊͂̍̀̍̃͠ḙ̴̡̢͇̭̤̲̘͙͑͒̊̄̔̂͆́̑̅̈̈́̆͂͛̈́͑͐̏̎̕̚̚͝ͅư̷͖̮̩͈͓͕̭̯̻̯̘̖̙̳̻̖̆̓̉͂̔̓́̒͑̅̓͊̂̕̚ą̴̧̻͖̘̰͙͙͂̂͐̑͐̈͂b̶̧̠̳͚̘̠̭̼̮͖͓̦̰̝̝͚̹͑̾͑̀͛̒̌͛́̇͒́̕͠i̵̤͙͈̫̠̥̟̱͙̮͎̋̑̋i̴̛͍̠̤̼͇̜̠͙̩͖̳̰̭̍̋̋̐͆̃̈́̏͒̈́̒͌̽̿͘̚̕w̸̟͛̈́͌̏͋́̍́͛̑͗́̕̚͝͝e̷̡̫͖̣͇̻̙͖̫̹͕͍̜̳̰̟̐̆͂̂͘͠͝b̸̨̢̠̺̩̺̭̮͉͍̥̮̺̳͈̳̑̿̌͋̎͑̿̇͊̕͜͠͝ͅͅͅl̸̡̢̯͚͖͍̮̹̱͓̬͚̩͎̮̃î̶̡͓̱͕̠̦̭͜q̶̿̿́̃͛͐̍̓̿̀̾̋̐̔̀͌̈͊̈́͆͝ͅą̵̪̥̹̞̥̠̺̥̟̰͙͓̤͔͚̪̲͚̅̃̊̎͂͌͊̂̃͊̃̒̚ͅȩ̵̬͍̩̱͖̮̪̔̌̉̇̊́̈́b̵̻̩̦̔́͆̒̆̓̃͐̚̕͝l̴͈̝̮͎͙̟̊̃͋̊̎͊̚ĭ̶̢̛͍̤͔͈̜͔̣̖͙̖͉͍̟̝͕̦͙̝̈̋̀͂̉̉̃̔̔͒͜ͅu̵̹̗̥͂͑͆̌̇̽̔̒̿̌̍̀̓̈̇̚͠͝v̶̛̛̼̗̦̖̲̹̩̫̩͎̠̖̪̥̻͓̼̠͖̺̓͗̐͆̿̽͌̎̅͋͗͋̃͌̌̓͐̊̚͠͝ḃ̷̨̛̖͈̜̥͚͓̳͙̫͔͉̩̹̫̀͋̔̓̆͛̕͠ͅͅq̵̣̟̲̎͊̀̆̿̒́̍̋̽̄̇̌͠w̶̧͔̯͉̺̅̂̑̎̑̉͒̎́v̷͚̀̀̓̏̍͆̃̀́̑͒͐̀̑̕͠e̵̱͐̌̔̂͌̋̃͑̄̒̒́̂̕̚͝͝į̷̧̢͚͈̟̙̻͓͕̙̘̙̘̮̼̘͔̙͉̯̐͜͜ͅu̵̡̢̧̫̗̳̲͇̜͚̤̠̲̞̟̟͌́̃͐̅̐͆̾̔͑̆̏̂́͋̀̒͋̆̕͝b̵̡̩͕̥̟̲̤̻̙͉̠͑̇̐̎̈̃̉̓̿̌̈́̊́͌̚v̷̨̮̤͙͓̣̭̫͓̞͔̰̼͍͖̭̲̈̉͊̒̓̒́͑̕͠ͅḭ̵͇̻̱̩̗̟͕̥̗͖͉̗̩̹̖̈̇̾̾̓̕u̸̢̹͊̿̓̂̀̈́̉b̷̨̖͚͖̬̰̪͕̻̞̮̠͙͕̻̫̖͓̹͉̟́͂́͛̽̄͊̇͆̚̚͠ͅḯ̷̢̢̡͓͚͕̖̠̳̖̓͜͜͠ȇ̵̢̢̞͕̰̻̫͎͎̦̖͍̈́̍̓̃̌͆̀̾͑͆̄̅̉̀͋̅̀̈́͂͝͝į̵͓̺̈́̒̅̆̾̾͘w̵̗̭̖̻̪̰̺̗̜̩̼̩̜͉̗̺͌̈́̏̒̆̌͌͂͋̑̊̀́̊̓̀̅̔̕͠͠c̴̯͈͚̓̂̈́̐̋̂̑͊̏͗̃̏͊̀̾͘͠͠d̶̢̢̗̯̬̳͇̜̬͍͔͎͇͚͔̭̃̎̄̋̾̂̑́͂̏̄͊͂̅̀́̾̇̃̕̚͜b̸̨̨̡͉̮̖̮͎̟͔̯̯̞͖̞̾̏̄͆̅́̾̍͗̒̊͂̏̈́̽̔͌̇̀̂̚w̴̺̬̦̺̦͙͖͊d̷̡̧̮̗͔̩͎̯̪̻̖̟̀͗̈́͗͋̕͝ĺ̶̛̺̯͕̦̣̭̥̠̭͎̩͎̼̹̝̲̭͉̤͔̿̏̆̾̿́̈́̑̌͘̕͝ç̸̧̢̧͔̙̦̩̭͙͖̺͍̦̭̱̟̍̍̏̓͊͆͑̕͜͜͝ͅȉ̷̢̛̺͎̹̟̗̹͙̼̜͖̈́̆̿̓̉́̏͂͌͐b̴̢͓̱̣̰̟̲͍̯͖̲̪̙͎̻̪͓̠̳͕̦̝̄̂̑̐̍́͒̚͠ͅͅi̷̛̯̗̰̺̟͓̰̟̤͈͊͆̍̈́̐̈́̍̋̀̈̇̆͂̀̈́́͛͘͜ͅb̵̧̬̘̦̺̦̙͕̦͉̙̩̲̗̖̤̅̎̉̈́̉͑́̏̈́̿̿͛̅͐̍͋̇̈́͘̚͜͝ͅͅv̸̡̢̧̧̞̣͓̱̣̖̪͈̖̲͇̠͍̠͎̱̙͇̑̍̈́̚͘͜q̸̧̨̩̮̜̣̲̠̺͍̌͌̑̀̏͌͒̕ḯ̶̧̳̳̳͉͒͗̀̑̕ư̸̡̧̧̮̗̠͓̬͚͈̪̻̦̻̙͔̦̖͕͔̈́́̃̉̊̎́̂̊̂̽̃̉͝͝͝b̶̤͕͉̤̰̼͕̼͉̻͚̮̲͕͉͂̃͛͜ͅͅķ̶̡̳͖̞̜̻͉͈͕̪̜̗̼̠̥̹̩̲̝͌̓̔͛͗̏̆̈͋̀̓̑̈́̚̚s̵̢̛͎̱̟̻͎̞̩̖̓̈́̂͌̀͛̉̀̀̚͝j̸̡͉̹̤̪̮̣̱͉͇͇͈̞̬̰͕̯́̊̄̔͂̚̚͘͜͝͝b̸̛͈̮͉̩͑̀̓̀̒̀́͑͒͂̋͋̈́̄͛̕͘͠͝͝͠à̶̢̼̜͆͐̀͆̔̃͒̐̃̾͌̕l̴̠̝̼̈͠͝k̸̡͙̗̠͖̞̝͙͈̩͎̹̮̣̹̠͐̽̈́̊̐̅̃͝ś̷̛̪͈͈̖͚̝̼͔̥̬͎̝̱͖̹̞̠̯̞́͌͒̊́b̵̘̯̫̜̌̍͗͊̒͊͑̽̌̒̾̔̈̂̒̐̀k̴̘͕̝̐́̈́͑̋͘͘s̸̡͔͚̥̯͕̯̤̳̈̆͌͋̈́̉͘d̵̡̧̢̞̟͉̞̟̩̘̝͍͎͔̮͍͎̝̞̠̻́̋̓̏͋̎̄̉͒͗̀̊́̀̕̚͜͠v̷̮̣̌̈́͆͗́̈́̕̕b̴̛͕̬̰͎̬̳̜̮̯͕͎͇͉̘͓̲̱͎̩̖͙̈́͌̓̈́̃̋͆̉́͜ķ̵̨̡̛͓̙̮͎̼̞͓̳̩̠̝͇̱̲̱͂͒͒̆̋̊̿̄̏̈̾͊̌̾̂̀̆̍͝w̵̢̧̨̛͕̦̹̹̦͉͍͓͕̜͙̺̬̻̐̓̂́̀̏̐̔̅̐͑̿̚ͅͅş̷̛͙͔̲̟̻̱̹̯̻̮͉̟̣͌͒̂̋̓̾͑̈́͋͠d̸̡͖̪̰̯̜̺̤͉̥̹̘̱͓̜̋̅̍̏͛̄̓̂̏͆̊͛͐̀͝͠͝v̶̨̭̩̯̘̜̝̬̩̲͍̰̱̮̔͐͐b̴̠̞̘̥̗̦̦͇̦̘̘̦̠̙̘̤̜̥͍̋̓͐̓͐͒́̈̍̂̽͊̕l̶̫̜̞̗̹̺̮̖̬̦͉̅̽̉̌̇̂̀̾͛̌̚̕͘͝͝k̵̛̛̛͉͈̝̳͉̻̝̜̼̥͎͍͙̫͚̺̊͌͆̈́̎̚̕̕͜s̵͚͕̅̀͐̑̚d̴͉̙̄͂̽͘͝b̶̛̻̭̮̣͈͗̎͐͋̃͆̒̍͆́̾̒͛ķ̵̨̧̡̗̥̬͈̱͔̦̤̬͚̲̫͉̠̪̰͔̠́ṡ̸̡̨̡̛̮̰̙̮̹͚̜̺͖̘̫̳̹̲̩̞͇͙̉͑̆̄̉̔̑̇̓͒̐̾̔͘͜͠͝ͅd̷̢̘̰̰̺̞̦̝̠͚̝̟̼͖̿̐̈́̈́͐́̃̍͌́̉̈́̌͋͌͘̚͜ͅḅ̵̛̰̝̰̫͙̬̠̺̩̺̺͛̄͒̍̍́̂̍͒̈́̀̀́̅̏̀́̚͠ͅļ̶̨̢̹̬̰̳͕͙͈̞͙̠̜̗̰͌̀̃̈͛͗͊̏̄́̄̆̊̒̋̍̓͆̈́̕͠͠͝s̷̞͖̣͖̝̐͒̇v̴̧̨̛̭͍̭̦̖͍͉̈́͊̋̆́͊̔͆͒̍̔̑̄́̀͛͑̿̉͘͝k̵̡̡̡̳̘̬̜͔̲͈̠̂̊̓̈́̀̊͋̿̈́̇͘̕͘͝j̸͕͇̲͚̜̟̤͈͕͕̠̦̹̬̲̫̪̩̮̫̿̒̒̓͌͊̐̏̑̊̀̃̃̒͝͝b̶̨͓̠͚̖͕̻̦̙̼̲̗͇̳͕̙̦̦͈̍͒͒̽́̐̏́̈́͂̇͛͒̓̓͆̆̆̕͘͝ṡ̵̡̨͔̝̱̖̰͖̦̹̰͍̯̦̟̬̭̏̅̄̓̍͌͜ͅl̷̝̠̗̻͖̰̱͎͔̹̠̣̤̱̣͚͍̞̪̲͓͆̒̔͐͛͜k̶̄̀͜d̷̢͙̬̞̅̈́̍͒͆̃̅̈́̀̀̉͗̋̋̈́͐̚͠͠j̷̪͙̳͓͙͇͖̥͙͉̼̩̪̩̖͗̽̈́b̴̤͉̥̩̾̉͂̔k̷̨͎͚̻̣̭͔̤͇̜̱̳̫͇̫̝̐̅̎̈́̍̅͠ͅͅs̴̛͚̜͓̻͙̦̞̏͗̐̆̆̇͊̏̇̄̿̆̊̆̃̑̇̀̿̍̏̚ͅb̵̨̛̜͍͉̆̄̍̉̐̿̀̇͐̔͘͠l̸̡͍̰͔̝̂͑̌̌̚v̷͙̦̥͓̙̫̲̥̘̖̯̰̬͇̓́̈́̉͜͠s̵̨̢̨̛̱̞̻͇̤͎͕͖̟̝͓̼̮̻̤̾̋̏͋̈̽̊̃̊́̈́̀͊̊̋̏̑̀̕̚k̷̢̢̘̳̮̰͍̘͙͔͕̘͍̯̣͐̃̾͗̎͗̌͂̀̔͋͒͑̌̇̾͒͌͘̚͜͜j̵̡͓̫͇̩̬̮͕̰͍̹̮̣̩̎̅̊̽̐̎̇͒̀̈́̄̀̕̚͜͜͝b̴̢̛͚͉̣̱̦̜̭̗͕̹́͊͛̍̌͂̈́͊̈́̾̈́͘͠͝l̷͚̰̳̭̜̩̇́̍̇͆̿͆͑̈́͘͘͘̕ṣ̶̢̢̣͚̗̭͖͚͌̈̾̓̽̆͐͌̿̾̃̃́̚͝͠k̸̛̖̻̼̰̭͍̘̭̳̞̭̤͔͚̲̦̄́̾͂͗́͐̆͂̑͊̀͌̈́͑͗̌̊̾͊̆͘͘͜ͅj̴̡̛̞͙̘̳͍͉͕̞̱̝̯̤̾͐̾͊̈́̌̃̋̽͌̎́̏̔̓͒͑̓̈͘͜͠͝b̴̨͎̞͈̳̥̝͕͈̙̝̼̥͎̖̟̪́̾̃̑̃̾̿̍̐̕͘͜͜͜ş̸̡͔̘̹̪̪̖͇̩͉͇͚͈̹͍̱̟͚̆̆l̸̨͔̱͖̟̭̯̠͖͍͚̼̭̙̐ͅd̵̛͚̯͙̦̓̄̈́͑̿̀͌͛̃͑͛͂͛̚͘͝ͅk̷̖͊͐͆̊̃̓͌͗́̍̈͐͒̈̌͑̋͐͊͝j̶̢̢̢̢͖̝͙̭͉̦͖̠̩̭͑͒̈́̔̆̐̄̈̀̀̀̽͗̊̃̇̆̓̆͂̂͘̕͘b̸̨̳̰̻̪̘̬̭͎̩̙̜̳̰̮̼͔̯̥̔̾̈́͂̅̔͝v̶̛̝͔̝͍͕̹͎̼̯̟̏͒͜͜͜s̷̡̛̠̦̠̤̘̤̙͙̯̙̿̾̌͑̊̉̇͗̉̀̓̋̎̎̉̔͛̚͜͝͝͝l̵̰͙̣̬͛̓̂̈́̀́́͑͗͒͊̉͋͑̒͊͠k̸̡̮̰̟̠̬̭̰͒́́͠ͅj̴̨̲͕̰̗̗͚̠̗̰͚̜̬̮̬͍̫̗̹̯͐̊͜͜s̵̨̨͔̥̣̯̜̻̪͖͕̥̬̓͑̔̃̌̔̀b̷̢̛̟͓̞̗̻̹͈͙̺̗̲̖̓͂͊͛̓͐̊͗̅̋̍̉̀̊̊̎̿̓́͘̕̕ļ̶̛͈̯̙͇̮̬̖̱͎̭͔̬̺͎̰̹͈̱̰̆̿̍̋͛̾̂̋̒̍̑͌̕͝k̷̨̨̧̰͉̖̪͚̳̩̱̘̜͔̮̽̉̀͋̿̈s̷̢͚̦̘͈̞̍͂̂̏̈́̇̂̓͗͛̑̃̅͂͒͂̍̈́̚͘͝͝d̶̨͚̙̟͇̩̜̪̯̞̩͓̝͎̩̞̩̗͓͙̀̊̌̀̓͛̆͐͂̄̿͑j̸̛͚̳̹̰̮̰̺̆̈́̄̅̂̉̀͊̾̏̕͘͝b̷̢͙͓̪̳͈̺̜̥̼͈̽͆͋͒̃̎̓̆͛̐́̓̓̽̆̈̚̚͘͝͠͝v̴̢̨̰̰̺̰̭̼̗̼̞͚̯̯̾͒͑̂͛͆̈́̌̿͂́́̃̎̑̑̾̚͜͝͝͝͝͝ͅl̴̮̮̠̞̟̥̰̫̹̝̹͓̠̣͔̟̠̯͔̾͆̀́̒̉͛̚k̷̛̯̓͌̋̀́̅̓͂͗͆́͂̆̌̀̈́̾̚v̴̛͔͎̘̦͌̑́̎͐̍͒͊͑̋̏́̔̓͝j̷̨̗̝̰̦̣̫̲͉̹͚͇͔͈͕̱͖̟̊̄͒́̓̓̆̎́͐̂̏͒̅̾́͐̂͜͝b̷̛͔̣̦̗̊͆͆̊̀̐̑̌̌̿͊͒͘͝ͅl̵̢̢̹̥̹̻͔̠͎̳̤͔̣̳̦̱̪͉̜̟̲͊̾̒́͂̀̿̈́͊́̀͐̀̊̃͛̂͝k̶̡̡̪̻̜͛̅̈́̅̈̐͛̈́͊͌̂̆̒̎͋̒͛̊͘͘͝s̸̢̨̨̧͓͔̖͖̻̜̞̼̱͇͕̣̪̪͙̠̟̖͎̈͋̌̃̓́̾͛̑͆̏̀̍̄̓͂̒͝ͅj̵̡̛̰̬̰͈̪̦̦̞̐̇̈́̌͗̏͠͝ͅb̶̜͚̀̈̍͐̐̊̋̔̍͆̈́͠ḽ̴̤̬̗͎̙͒̏͆̍͆́͆̈͝ȃ̴̡͕̩͔̤̮̘̮̱̻̺͓͚̭̟͚͕̰̹̦̠͜͠ͅk̸̛̟̪̈́s̸̛͓͕̤̻͎̺̼̪̗̝͈͖͂̈̅̕͜͜d̵̛̳͖̱̰͍̔̀́̋͗̆͋̽̅̂̍͆̔̀̚̚͜͝ͅj̶̢̧̟̤̤̳͇͍͍͙͍̫̥͆͒̆̏̓́̽̐̕͘͜b̶̮̪͖͚̠̝̠̬͖̩̻̈͑̇̒̇̈́͑͊̆̇̓̃͆̔̐͋̅͋̀̌͜͝͝͠͝ͅl̴͔͍̜̬͚̬͕̼͇͖̟͚̝̯̮͉̻̖̪̪̬͖̫͐̄̓́̓̇̚͝k̴̨̼̩͈̺̪̩̜̣̪͔̮̩̺̱̫̝̜̐ͅͅs̸̛͔̺͐͐̄͋͗̊̇̓͝͝j̵͉͔͈̫̯̔̃̑͊̀͑̋̌̚͘̚b̵̨͓̥̺͔͕͍̣͍̝̻̙̲̩̗̬̳͉̖̤̬̺̊̀̽̐͂͗̃̕͘͜͜v̷̛̛̩̪̄͛̃͆̓̈́̊͗͂͑̅͒̽͆̐̎̈͂͘͝͝l̶͈͎͂̓̎̔ķ̶̡̢̛̛̺̪̣͖̣̠͔̳̟͓͖͉͗̈́̈́͐̌̊̓̐͋̀̀̊̀̍̌͗̄̆͘͘͜͝s̶̡̧̡͔̠̲͈̲͎͖̺̥̯̺̬̻͍̠̦̞̳̖̭̀̇̓̂͊̄̅͝ͅa̶͙̱̥̜͓̖͇͔͚͓̲̙̻̟͈͙̙̞̟̜͚͘ͅj̸̫̰̯̬̮́̓̏̌̚b̸̡̡͇̹͉̦̘̩͉͚͎̠̩̪̥̱̬̘̳̓̆̏̍͊̾̽͜ͅȧ̴̛̼̜̥́̄̎̈́͂̅̂̓̿͘̚͝͝l̷͙̹͔̮͚͖̰͓͉͒̾̌̿̓̀̎̂̏̅͆̊̆̕͝͠ͅş̸̨̨̺̫̦̾͒͌̌̅̎͂̉͘͜k̸̨͈̠͕̞͈͔̺̦̳͑͑̊̆̍͛̿̉̀̀̃͆̑̚̕j̷̨̨͇̤͍͔̩̻̙͉̬̫͙̺̪̤̻̯͚̬͓̏͝ͅͅb̷͎͎͎̞͓͉̜͚̯̰͚͒̄̅͊̎̇́͐͋͆͐̅͑͆̀̚͜͝͝͠ạ̷̹̮̮̭͍̼͓̭̰̖̈̀̎̿͑̌͑͒̒̇͒̏̃̔͌͊̚ş̸̨̦̘̝̼͔͓͚̭̠̝̝̝̮̖̜̣͈̻͍̱̼͗͑̔͋̑͑̇̅̄͆̈͆̅̊͠v̶̢͍̺̆͜d̵̼̲̖̯̤̰̱́͗͒ķ̸͓̻̭̯͈̟̪̝̬̬̥̗̱͇̹̮̈̊̄̍͛̊̈́̄̕ͅj̶̢̧̢̢̩̫̗̦͕̝̩̩͎̹̭̏̇͒̎̾́̃̊̒͐̀̈́̒̉͋̾͗̽̈́̕͝͝͝͝b̸̨̢̛̠̳̣̮͚̦̯̯̬͖̈́̅͗͑͆̿̍̽̎͗͒̈́̈͂̑̈͋̓͘̚͜l̵̡̡̛͖̦̗̹͖̺̲͇͙͍̱͗̍̋̎̊͆̈́̀͐̇̓͐̽͛̌̓̋̔͑̿̊̔͝ͅͅs̶̢̡̰̰͇̺͍̹̞̝͖̙̟̩͖̼̟̺̥̿̍̕͝ͅd̴̨̨̼̪̞̻̞͇̰̻̠̗̣̼̦̮̑̾͂͜͝ͅa̴̧̧̢͕̤̙̬͙̞̻̜̙͓̥̗̽͂̈̃͒̐̔̾̊̂̅̃̊̐͌̓̕͘͝ǩ̸̮̼͈̠̩̱͖̳̜̝̞̥̞͈̺̬̹̠̗̎͐͆̒͌̂̉͒͆̕͝j̸̨̡͔̟͈̖̠̥͔̟͙̞̮͍̟͉̫̠͍̤̹̭̰̆͒̎̋͗́͗̆̔̈́̚͘͠͠͝ͅb̶̨̛̖͎͔̮̳͔͈̦͉̤̤̣̩̜̥͙̽̓̾̆̒̇̏͛̌̀̓̅̊̌̚̚͘͘͝ͅv̴̧̨͔̠͖̺̥̬͈̲͇̱̹̤͔̭͔͈̦̟̳̆̾͒̾̃̉͊̾͆͜͝ĺ̶̨̝͕͓̘͖͕̟̩̝͙̰̰̳͗͛̒͌̽͛̃͂͂̆̿̉͐͛́́͑̾̈́͘̚̚͝ḑ̵̯̗̜̮̞̼̱̜̜͚͓̱̯̺̯̪̲͕̳͚͔̌͌͆̀̓͒͂́̐̈́̈́̀͋̇̄̀̈́͝ŝ̶̹̳̦̝͉̩̠̄̔̊͂̂͆̂͑̓̽̊͂͠ͅķ̷̳̲̙̖̻̑͑͒̊͂̄̀͑̃̎͂̄̿́͆̔̽̎̅̒̾̿͘̚͜d̶͚̬͔̳̖͙͇͉̜͙͗̉̇̏͌̽͜j̵̧̖̟͉͚̮͑́̓̇̿̍͂̀̋̈̅̆̾̈́̀̾̓̆͒͝͠b̷̦̫̲̻͈̪͍̩̳̱̋̾̑̊̄͗̓͐͐̄̊͋̊̾̈́̎̒͐̕͜͝͝͠͠v̷̢̧̛̞̬̘̭͈̹̣̱̮̽͛͊͊͆͌͛̽̽̏̉̽͌͛̚͜͝͝͝l̵͍̲̰̥̙̭̻͇͎̞̺̹̝͎͕͇͛̚͜͝k̶̨̤̪̜̻̣̰̜̤͙̼̼͔̓̇̈́̅͌͊̽s̷̪̝̠͚̣͈̤͔̙͒̐̆̈́͊̇̇̆̀́͋͆͂̽̏͆̇̒̚ã̴͔͓̯̤͉̹̘̱͉̤̝͋͊͗̿̆̾̕j̸̡̧̢̙̝͙͖̪̭̋̊́̏́b̶̭̰̲͙̮͙̙͔͉̹͓̐͗̚͜͝ͅͅͅĺ̶̢̯͖̗̗̳͇̦͚̮̲͔̪̜̣͓͕̰̬̈̑̓̍̀̓́͛̅͗͐̕͘k̶̞̭͊̄̌̋̀̚s̶̛̛̼̹̗̙̩̈́͒͋͛̓́͋̏̑͊̍̔͒͋̽͐̈́̇̚͠͠͝j̵̭̥̱̙͕̋͌̓̒͐̒̅͆̒́b̴͚̋̽̀̍͐͛͂͊͐̆̈́́̈́̂̂̿̓̓̾̊̕̕͘s̴̠̼̰̺͇̩̞͖͓̰̤͔̹̟̹͇̣̫̲͖̫͖̖͓̉̂̆̃̄͗͛͗͂͐̿̓̓̈́a̸̻̙̖̰͎̰̲͊̾̀̋̍͋̿̎̿̀̂̍̒̀̎̚̕͠͝͝͠l̴̪̩̜͉̮̹͚̳̐̓͒̑̐̐̂̃͛̃̓̐͜͠k̵̡̛̛̠̭͈͔͍̰͎̟̱̥̟̑̏̉͛̏͗͗̊͑̌͊̀̉̅́͒̿̐̓̕͠͠j̶̡̨̧̧̛̛͓͍̱̟͈̘̳̱̦͍̝̜̰̣͈͉͔̫͈̿̃̈́͒͂̍̈s̶̡̛͙̪̟͇͍̲̘͇͚̅̎̾̆̿̾͐̀͒̇́̾̃̒̕͘͠͠b̸͕̻͎̦̻̻͓̬̗̦́̄̀͑̕͝ĺ̵̠̼̱̫͚̩͓͎͚̼̱̰̦̮̹͖͖̼̼̱̲̲̅̃̓̅͋͒̈́̓̔̏̀̿̉̃̃̉̈́̒͜͠k̸̢̨̡̛̦̩̗͖͚̹̯̠̟̮̣̬̬̬̯͈̺͔̊̋̂̓́̀̍͒̂̿̌̆̂̚͜ͅͅa̸͕̯̟͙̮̬̫̲͓̞̜͙̘͙̤̮̯̥̠͈̯͑̍̽̍̽̅͗̑̿̉̏̐̎́̀̈͜ṣ̶̺͈̮̠͕͎̜́̔̽̅̉̐̈́̄̋͌̀͊̓͗̀͗̓̎͝ͅd̴̨͚͎͓̿ͅṽ̶͙̺̭̊̉̈̎̃͐͑̂̈́̿͗̎̓̎̒̉̍͊͜b̷̤͓̭̲̑̅̃͂̅̂͘ḽ̸̡̡̛͖̘͚͚́̽̌͂̆̋̈̊̅̄̎̐͗̾̑̓k̴̛͇͍̤͇̙͎̼͔̗͙̮͕͙͈̯̼̹̱̘̣̑͊̒͋͂́̓͌͛̃̏̂̍́̽v̸͓͚̻̩̦̻͉͈̯̲̭̼̣̬͚͔̫̙̩̮̂̅́̅͒̈̊̉͆̍̇̆̐̌̈́̌ͅͅs̷̨̲̪̱͈̮͕̱͍͕͖̦̞̥̱̜̓͗̓ḑ̴̦̹̗͖̠̳̭͓̠͇͌͛̊̈̈̓̒̋̐͂̅̾̊͘̚̕͝͝ą̸̟̮̙͕͙̗̺͓̟̭̘͓͈̋͌̍̅͌͛̉̉̋̔̊͂̌̑̾̚͝b̸̰͇̞̗̹͉̳͉͎̙͍͎̪̮̟͔̮̼͒̈́͋̃͌̄̚ͅs̶̛͓̯̗̲̰̗̮͖̦̘͙̬͈͔͎̠͉̬̫̓̐̉̃̃͂͗̈́̇́̚̕͘̚̕l̴͉͚̩̎̈̈́̐͆̓̈́̏͘d̴͓̣͈͇̠̙̳̎͊͂͒̀̅̈́̎́͋k̶̙̘̆̈́͂͋͒̂͆̔͑̋͋̄͛͛̐̚͘̕̕͠͝b̸͕̗̳̫̲͒̉̈́͊̑́̉̑̌̈̓̾̌͒ś̵̢̡̢͕̜̰̥̥͎͖͎̺̺̠͉̆̅̓̐̌̅͝ͅļ̸̨̠̝̬͈̬̦͈̙̲̼͇͙̦̠̭̺͐̉̇̐̀̉̅͘͜͜ͅk̸̡̡͓̦̥̬̣͍͓̲̒̀̔̋̔̊̚̚s̵̡̖̤̙̝̠̺͚͎̼͈̝̗͈̞̲̮̈̅̈́̉͐̓̃̈́̎́͑̋̽̂̃̋̏̕͘͘͝͝a̴̧̨̛̮͇̟͕̣̹̙̖̥̜͇̱̦̗̫̠̘͔̩̅̆̓͊̎̿̅͌̾̋̿̓̌͋̂̈͗̄̓̕̚͜͠ͅb̵̢̰̞̝̥͉͙̟̜̘͕̜͆̈́̾͐̔̆͛̉̚̚ͅͅs̷̙͚͈͙̽̅̏̓̈́̊̊͂͑́͊̐̄̇̀̾̊͝͠a̵̛̛̲̜̟̜̻̺̠͖̣̤͖̲̍̆̐͋̋͐̃̆̔̅̊v̸͚̬̮̉̍́̀ķ̸͎̠̺͖̮̯̦̠̺͓͉̠̟̜͓̖̗̫͛̍̾̾̍̉͌́̌̾̽̊͘ḏ̴͙̎̈́̅̎́͛͊͒̀̄̍̿̈́͐̆͘͝j̷͔̠̥̩̗̩̍̿̽̇̐̃͂͌̚͝͠b̵͉̻̟̺͙͗̍̈́̆̋̀̆͋̐͋̈͗͑͊ͅḇ̸̛͈̟̮̺̙͈̹̘̬̭̥̻͈̲̻̓̿̌̊͂͐̎͐͊́͝b̸̡̧̖̯̹̗̜̫̻̫͇̖̩̲͕̗̼̎̍̑̅̒̌̒̀̕͜e̶̡̡͖̞̥̯͍͚̲̖̥̬̩͎͉͙̪̳͛͋̀̓̏̏͋̏̐̓̉͊͊͠͝͠a̴̠͓̓̀́̈̅̓̈́k̴̢͇̩̹͇̮̭̪̗̙̼̟̲͇̦̼͗͜į̶̼͙̺̥̗͓̙̜̙̭̬̙̇̓̆́͋̒͗̀͒͗̽̕͝͠͝b̸͎̰̠͓̪̤͕͈̙͊̔́͋͊͆͛͌̿͋́̎͆̋̏̐̆̚̚̕͘͠l̸̨̢̛̛̘͈͔̞͍̳̼͉̘̺͔̦̦͉̫͂̿̾̿̃̔̒͑̊̆̔̉͐̔̄̌̕̚͘͝į̷̨̛͈̥̼̹̂̊̈́̅͗̉̉̔̆́̋̀̋̅͑̈́̑͜ͅͅw̴̼̰̺̤̤͈̼̻͈̗̼͖̘̉̐̊̊͑̈̑͂̈́͗͐̊͂̍̀̍̃͠ḙ̴̡̢͇̭̤̲̘͙͑͒̊̄̔̂͆́̑̅̈̈́̆͂͛̈́͑͐̏̎̕̚̚͝ͅư̷͖̮̩͈͓͕̭̯̻̯̘̖̙̳̻̖̆̓̉͂̔̓́̒͑̅̓͊̂̕̚ą̴̧̻͖̘̰͙͙͂̂͐̑͐̈͂b̶̧̠̳͚̘̠̭̼̮͖͓̦̰̝̝͚̹͑̾͑̀͛̒̌͛́̇͒́̕͠i̵̤͙͈̫̠̥̟̱͙̮͎̋̑̋i̴̛͍̠̤̼͇̜̠͙̩͖̳̰̭̍̋̋̐͆̃̈́̏͒̈́̒͌̽̿͘̚̕w̸̟͛̈́͌̏͋́̍́͛̑͗́̕̚͝͝e̷̡̫͖̣͇̻̙͖̫̹͕͍̜̳̰̟̐̆͂̂͘͠͝b̸̨̢̠̺̩̺̭̮͉͍̥̮̺̳͈̳̑̿̌͋̎͑̿̇͊̕͜͠͝ͅͅͅl̸̡̢̯͚͖͍̮̹̱͓̬͚̩͎̮̃î̶̡͓̱͕̠̦̭͜q̶̿̿́̃͛͐̍̓̿̀̾̋̐̔̀͌̈͊̈́͆͝ͅą̵̪̥̹̞̥̠̺̥̟̰͙͓̤͔͚̪̲͚̅̃̊̎͂͌͊̂̃͊̃̒̚ͅȩ̵̬͍̩̱͖̮̪̔̌̉̇̊́̈́b̵̻̩̦̔́͆̒̆̓̃͐̚̕͝l̴͈̝̮͎͙̟̊̃͋̊̎͊̚ĭ̶̢̛͍̤͔͈̜͔̣̖͙̖͉͍̟̝͕̦͙̝̈̋̀͂̉̉̃̔̔͒͜ͅu̵̹̗̥͂͑͆̌̇̽̔̒̿̌̍̀̓̈̇̚͠͝v̶̛̛̼̗̦̖̲̹̩̫̩͎̠̖̪̥̻͓̼̠͖̺̓͗̐͆̿̽͌̎̅͋͗͋̃͌̌̓͐̊̚͠͝ḃ̷̨̛̖͈̜̥͚͓̳͙̫͔͉̩̹̫̀͋̔̓̆͛̕͠ͅͅq̵̣̟̲̎͊̀̆̿̒́̍̋̽̄̇̌͠w̶̧͔̯͉̺̅̂̑̎̑̉͒̎́v̷͚̀̀̓̏̍͆̃̀́̑͒͐̀̑̕͠e̵̱͐̌̔̂͌̋̃͑̄̒̒́̂̕̚͝͝į̷̧̢͚͈̟̙̻͓͕̙̘̙̘̮̼̘͔̙͉̯̐͜͜ͅu̵̡̢̧̫̗̳̲͇̜͚̤̠̲̞̟̟͌́̃͐̅̐͆̾̔͑̆̏̂́͋̀̒͋̆̕͝b̵̡̩͕̥̟̲̤̻̙͉̠͑̇̐̎̈̃̉̓̿̌̈́̊́͌̚v̷̨̮̤͙͓̣̭̫͓̞͔̰̼͍͖̭̲̈̉͊̒̓̒́͑̕͠ͅḭ̵͇̻̱̩̗̟͕̥̗͖͉̗̩̹̖̈̇̾̾̓̕u̸̢̹͊̿̓̂̀̈́̉b̷̨̖͚͖̬̰̪͕̻̞̮̠͙͕̻̫̖͓̹͉̟́͂́͛̽̄͊̇͆̚̚͠ͅḯ̷̢̢̡͓͚͕̖̠̳̖̓͜͜͠ȇ̵̢̢̞͕̰̻̫͎͎̦̖͍̈́̍̓̃̌͆̀̾͑͆̄̅̉̀͋̅̀̈́͂͝͝į̵͓̺̈́̒̅̆̾̾͘w̵̗̭̖̻̪̰̺̗̜̩̼̩̜͉̗̺͌̈́̏̒̆̌͌͂͋̑̊̀́̊̓̀̅̔̕͠͠c̴̯͈͚̓̂̈́̐̋̂̑͊̏͗̃̏͊̀̾͘͠͠d̶̢̢̗̯̬̳͇̜̬͍͔͎͇͚͔̭̃̎̄̋̾̂̑́͂̏̄͊͂̅̀́̾̇̃̕̚͜b̸̨̨̡͉̮̖̮͎̟͔̯̯̞͖̞̾̏̄͆̅́̾̍͗̒̊͂̏̈́̽̔͌̇̀̂̚w̴̺̬̦̺̦͙͖͊d̷̡̧̮̗͔̩͎̯̪̻̖̟̀͗̈́͗͋̕͝ĺ̶̛̺̯͕̦̣̭̥̠̭͎̩͎̼̹̝̲̭͉̤͔̿̏̆̾̿́̈́̑̌͘̕͝ç̸̧̢̧͔̙̦̩̭͙͖̺͍̦̭̱̟̍̍̏̓͊͆͑̕͜͜͝ͅȉ̷̢̛̺͎̹̟̗̹͙̼̜͖̈́̆̿̓̉́̏͂͌͐b̴̢͓̱̣̰̟̲͍̯͖̲̪̙͎̻̪͓̠̳͕̦̝̄̂̑̐̍́͒̚͠ͅͅi̷̛̯̗̰̺̟͓̰̟̤͈͊͆̍̈́̐̈́̍̋̀̈̇̆͂̀̈́́͛͘͜ͅb̵̧̬̘̦̺̦̙͕̦͉̙̩̲̗̖̤̅̎̉̈́̉͑́̏̈́̿̿͛̅͐̍͋̇̈́͘̚͜͝ͅͅv̸̡̢̧̧̞̣͓̱̣̖̪͈̖̲͇̠͍̠͎̱̙͇̑̍̈́̚͘͜q̸̧̨̩̮̜̣̲̠̺͍̌͌̑̀̏͌͒̕ḯ̶̧̳̳̳͉͒͗̀̑̕ư̸̡̧̧̮̗̠͓̬͚͈̪̻̦̻̙͔̦̖͕͔̈́́̃̉̊̎́̂̊̂̽̃̉͝͝͝b̶̤͕͉̤̰̼͕̼͉̻͚̮̲͕͉͂̃͛͜ͅͅķ̶̡̳͖̞̜̻͉͈͕̪̜̗̼̠̥̹̩̲̝͌̓̔͛͗̏̆̈͋̀̓̑̈́̚̚s̵̢̛͎̱̟̻͎̞̩̖̓̈́̂͌̀͛̉̀̀̚͝j̸̡͉̹̤̪̮̣̱͉͇͇͈̞̬̰͕̯́̊̄̔͂̚̚͘͜͝͝b̸̛͈̮͉̩͑̀̓̀̒̀́͑͒͂̋͋̈́̄͛̕͘͠͝͝͠à̶̢̼̜͆͐̀͆̔̃͒̐̃̾͌̕l̴̠̝̼̈͠͝k̸̡͙̗̠͖̞̝͙͈̩͎̹̮̣̹̠͐̽̈́̊̐̅̃͝ś̷̛̪͈͈̖͚̝̼͔̥̬͎̝̱͖̹̞̠̯̞́͌͒̊́b̵̘̯̫̜̌̍͗͊̒͊͑̽̌̒̾̔̈̂̒̐̀k̴̘͕̝̐́̈́͑̋͘͘s̸̡͔͚̥̯͕̯̤̳̈̆͌͋̈́̉͘d̵̡̧̢̞̟͉̞̟̩̘̝͍͎͔̮͍͎̝̞̠̻́̋̓̏͋̎̄̉͒͗̀̊́̀̕̚͜͠v̷̮̣̌̈́͆͗́̈́̕̕b̴̛͕̬̰͎̬̳̜̮̯͕͎͇͉̘͓̲̱͎̩̖͙̈́͌̓̈́̃̋͆̉́͜ķ̵̨̡̛͓̙̮͎̼̞͓̳̩̠̝͇̱̲̱͂͒͒̆̋̊̿̄̏̈̾͊̌̾̂̀̆̍͝w̵̢̧̨̛͕̦̹̹̦͉͍͓͕̜͙̺̬̻̐̓̂́̀̏̐̔̅̐͑̿̚ͅͅş̷̛͙͔̲̟̻̱̹̯̻̮͉̟̣͌͒̂̋̓̾͑̈́͋͠d̸̡͖̪̰̯̜̺̤͉̥̹̘̱͓̜̋̅̍̏͛̄̓̂̏͆̊͛͐̀͝͠͝v̶̨̭̩̯̘̜̝̬̩̲͍̰̱̮̔͐͐b̴̠̞̘̥̗̦̦͇̦̘̘̦̠̙̘̤̜̥͍̋̓͐̓͐͒́̈̍̂̽͊̕l̶̫̜̞̗̹̺̮̖̬̦͉̅̽̉̌̇̂̀̾͛̌̚̕͘͝͝k̵̛̛̛͉͈̝̳͉̻̝̜̼̥͎͍͙̫͚̺̊͌͆̈́̎̚̕̕͜s̵͚͕̅̀͐̑̚d̴͉̙̄͂̽͘͝b̶̛̻̭̮̣͈͗̎͐͋̃͆̒̍͆́̾̒͛ķ̵̨̧̡̗̥̬͈̱͔̦̤̬͚̲̫͉̠̪̰͔̠́ṡ̸̡̨̡̛̮̰̙̮̹͚̜̺͖̘̫̳̹̲̩̞͇͙̉͑̆̄̉̔̑̇̓͒̐̾̔͘͜͠͝ͅd̷̢̘̰̰̺̞̦̝̠͚̝̟̼͖̿̐̈́̈́͐́̃̍͌́̉̈́̌͋͌͘̚͜ͅḅ̵̛̰̝̰̫͙̬̠̺̩̺̺͛̄͒̍̍́̂̍͒̈́̀̀́̅̏̀́̚͠ͅļ̶̨̢̹̬̰̳͕͙͈̞͙̠̜̗̰͌̀̃̈͛͗͊̏̄́̄̆̊̒̋̍̓͆̈́̕͠͠͝s̷̞͖̣͖̝̐͒̇v̴̧̨̛̭͍̭̦̖͍͉̈́͊̋̆́͊̔͆͒̍̔̑̄́̀͛͑̿̉͘͝k̵̡̡̡̳̘̬̜͔̲͈̠̂̊̓̈́̀̊͋̿̈́̇͘̕͘͝j̸͕͇̲͚̜̟̤͈͕͕̠̦̹̬̲̫̪̩̮̫̿̒̒̓͌͊̐̏̑̊̀̃̃̒͝͝b̶̨͓̠͚̖͕̻̦̙̼̲̗͇̳͕̙̦̦͈̍͒͒̽́̐̏́̈́͂̇͛͒̓̓͆̆̆̕͘͝ṡ̵̡̨͔̝̱̖̰͖̦̹̰͍̯̦̟̬̭̏̅̄̓̍͌͜ͅl̷̝̠̗̻͖̰̱͎͔̹̠̣̤̱̣͚͍̞̪̲͓͆̒̔͐͛͜k̶̄̀͜d̷̢͙̬̞̅̈́̍͒͆̃̅̈́̀̀̉͗̋̋̈́͐̚͠͠j̷̪͙̳͓͙͇͖̥͙͉̼̩̪̩̖͗̽̈́b̴̤͉̥̩̾̉͂̔k̷̨͎͚̻̣̭͔̤͇̜̱̳̫͇̫̝̐̅̎̈́̍̅͠ͅͅs̴̛͚̜͓̻͙̦̞̏͗̐̆̆̇͊̏̇̄̿̆̊̆̃̑̇̀̿̍̏̚ͅb̵̨̛̜͍͉̆̄̍̉̐̿̀̇͐̔͘͠l̸̡͍̰͔̝̂͑̌̌̚v̷͙̦̥͓̙̫̲̥̘̖̯̰̬͇̓́̈́̉͜͠s̵̨̢̨̛̱̞̻͇̤͎͕͖̟̝͓̼̮̻̤̾̋̏͋̈̽̊̃̊́̈́̀͊̊̋̏̑̀̕̚k̷̢̢̘̳̮̰͍̘͙͔͕̘͍̯̣͐̃̾͗̎͗̌͂̀̔͋͒͑̌̇̾͒͌͘̚͜͜j̵̡͓̫͇̩̬̮͕̰͍̹̮̣̩̎̅̊̽̐̎̇͒̀̈́̄̀̕̚͜͜͝b̴̢̛͚͉̣̱̦̜̭̗͕̹́͊͛̍̌͂̈́͊̈́̾̈́͘͠͝l̷͚̰̳̭̜̩̇́̍̇͆̿͆͑̈́͘͘͘̕ṣ̶̢̢̣͚̗̭͖͚͌̈̾̓̽̆͐͌̿̾̃̃́̚͝͠k̸̛̖̻̼̰̭͍̘̭̳̞̭̤͔͚̲̦̄́̾͂͗́͐̆͂̑͊̀͌̈́͑͗̌̊̾͊̆͘͘͜ͅj̴̡̛̞͙̘̳͍͉͕̞̱̝̯̤̾͐̾͊̈́̌̃̋̽͌̎́̏̔̓͒͑̓̈͘͜͠͝b̴̨͎̞͈̳̥̝͕͈̙̝̼̥͎̖̟̪́̾̃̑̃̾̿̍̐̕͘͜͜͜ş̸̡͔̘̹̪̪̖͇̩͉͇͚͈̹͍̱̟͚̆̆l̸̨͔̱͖̟̭̯̠͖͍͚̼̭̙̐ͅd̵̛͚̯͙̦̓̄̈́͑̿̀͌͛̃͑͛͂͛̚͘͝ͅk̷̖͊͐͆̊̃̓͌͗́̍̈͐͒̈̌͑̋͐͊͝j̶̢̢̢̢͖̝͙̭͉̦͖̠̩̭͑͒̈́̔̆̐̄̈̀̀̀̽͗̊̃̇̆̓̆͂̂͘̕͘b̸̨̳̰̻̪̘̬̭͎̩̙̜̳̰̮̼͔̯̥̔̾̈́͂̅̔͝v̶̛̝͔̝͍͕̹͎̼̯̟̏͒͜͜͜s̷̡̛̠̦̠̤̘̤̙͙̯̙̿̾̌͑̊̉̇͗̉̀̓̋̎̎̉̔͛̚͜͝͝͝l̵̰͙̣̬͛̓̂̈́̀́́͑͗͒͊̉͋͑̒͊͠k̸̡̮̰̟̠̬̭̰͒́́͠ͅj̴̨̲͕̰̗̗͚̠̗̰͚̜̬̮̬͍̫̗̹̯͐̊͜͜s̵̨̨͔̥̣̯̜̻̪͖͕̥̬̓͑̔̃̌̔̀b̷̢̛̟͓̞̗̻̹͈͙̺̗̲̖̓͂͊͛̓͐̊͗̅̋̍̉̀̊̊̎̿̓́͘̕̕ļ̶̛͈̯̙͇̮̬̖̱͎̭͔̬̺͎̰̹͈̱̰̆̿̍̋͛̾̂̋̒̍̑͌̕͝k̷̨̨̧̰͉̖̪͚̳̩̱̘̜͔̮̽̉̀͋̿̈s̷̢͚̦̘͈̞̍͂̂̏̈́̇̂̓͗͛̑̃̅͂͒͂̍̈́̚͘͝͝d̶̨͚̙̟͇̩̜̪̯̞̩͓̝͎̩̞̩̗͓͙̀̊̌̀̓͛̆͐͂̄̿͑j̸̛͚̳̹̰̮̰̺̆̈́̄̅̂̉̀͊̾̏̕͘͝b̷̢͙͓̪̳͈̺̜̥̼͈̽͆͋͒̃̎̓̆͛̐́̓̓̽̆̈̚̚͘͝͠͝v̴̢̨̰̰̺̰̭̼̗̼̞͚̯̯̾͒͑̂͛͆̈́̌̿͂́́̃̎̑̑̾̚͜͝͝͝͝͝ͅl̴̮̮̠̞̟̥̰̫̹̝̹͓̠̣͔̟̠̯͔̾͆̀́̒̉͛̚k̷̛̯̓͌̋̀́̅̓͂͗͆́͂̆̌̀̈́̾̚v̴̛͔͎̘̦͌̑́̎͐̍͒͊͑̋̏́̔̓͝j̷̨̗̝̰̦̣̫̲͉̹͚͇͔͈͕̱͖̟̊̄͒́̓̓̆̎́͐̂̏͒̅̾́͐̂͜͝b̷̛͔̣̦̗̊͆͆̊̀̐̑̌̌̿͊͒͘͝ͅl̵̢̢̹̥̹̻͔̠͎̳̤͔̣̳̦̱̪͉̜̟̲͊̾̒́͂̀̿̈́͊́̀͐̀̊̃͛̂͝k̶̡̡̪̻̜͛̅̈́̅̈̐͛̈́͊͌̂̆̒̎͋̒͛̊͘͘͝s̸̢̨̨̧͓͔̖͖̻̜̞̼̱͇͕̣̪̪͙̠̟̖͎̈͋̌̃̓́̾͛̑͆̏̀̍̄̓͂̒͝ͅj̵̡̛̰̬̰͈̪̦̦̞̐̇̈́̌͗̏͠͝ͅb̶̜͚̀̈̍͐̐̊̋̔̍͆̈́͠ḽ̴̤̬̗͎̙͒̏͆̍͆́͆̈͝ȃ̴̡͕̩͔̤̮̘̮̱̻̺͓͚̭̟͚͕̰̹̦̠͜͠ͅk̸̛̟̪̈́s̸̛͓͕̤̻͎̺̼̪̗̝͈͖͂̈̅̕͜͜d̵̛̳͖̱̰͍̔̀́̋͗̆͋̽̅̂̍͆̔̀̚̚͜͝ͅj̶̢̧̟̤̤̳͇͍͍͙͍̫̥͆͒̆̏̓́̽̐̕͘͜b̶̮̪͖͚̠̝̠̬͖̩̻̈͑̇̒̇̈́͑͊̆̇̓̃͆̔̐͋̅͋̀̌͜͝͝͠͝ͅl̴͔͍̜̬͚̬͕̼͇͖̟͚̝̯̮͉̻̖̪̪̬͖̫͐̄̓́̓̇̚͝k̴̨̼̩͈̺̪̩̜̣̪͔̮̩̺̱̫̝̜̐ͅͅs̸̛͔̺͐͐̄͋͗̊̇̓͝͝j̵͉͔͈̫̯̔̃̑͊̀͑̋̌̚͘̚b̵̨͓̥̺͔͕͍̣͍̝̻̙̲̩̗̬̳͉̖̤̬̺̊̀̽̐͂͗̃̕͘͜͜v̷̛̛̩̪̄͛̃͆̓̈́̊͗͂͑̅͒̽͆̐̎̈͂͘͝͝l̶͈͎͂̓̎̔ķ̶̡̢̛̛̺̪̣͖̣̠͔̳̟͓͖͉͗̈́̈́͐̌̊̓̐͋̀̀̊̀̍̌͗̄̆͘͘͜͝s̶̡̧̡͔̠̲͈̲͎͖̺̥̯̺̬̻͍̠̦̞̳̖̭̀̇̓̂͊̄̅͝ͅa̶͙̱̥̜͓̖͇͔͚͓̲̙̻̟͈͙̙̞̟̜͚͘ͅj̸̫̰̯̬̮́̓̏̌̚b̸̡̡͇̹͉̦̘̩͉͚͎̠̩̪̥̱̬̘̳̓̆̏̍͊̾̽͜ͅȧ̴̛̼̜̥́̄̎̈́͂̅̂̓̿͘̚͝͝l̷͙̹͔̮͚͖̰͓͉͒̾̌̿̓̀̎̂̏̅͆̊̆̕͝͠ͅş̸̨̨̺̫̦̾͒͌̌̅̎͂̉͘͜k̸̨͈̠͕̞͈͔̺̦̳͑͑̊̆̍͛̿̉̀̀̃͆̑̚̕j̷̨̨͇̤͍͔̩̻̙͉̬̫͙̺̪̤̻̯͚̬͓̏͝ͅͅb̷͎͎͎̞͓͉̜͚̯̰͚͒̄̅͊̎̇́͐͋͆͐̅͑͆̀̚͜͝͝͠ạ̷̹̮̮̭͍̼͓̭̰̖̈̀̎̿͑̌͑͒̒̇͒̏̃̔͌͊̚ş̸̨̦̘̝̼͔͓͚̭̠̝̝̝̮̖̜̣͈̻͍̱̼͗͑̔͋̑͑̇̅̄͆̈͆̅̊͠v̶̢͍̺̆͜d̵̼̲̖̯̤̰̱́͗͒ķ̸͓̻̭̯͈̟̪̝̬̬̥̗̱͇̹̮̈̊̄̍͛̊̈́̄̕ͅj̶̢̧̢̢̩̫̗̦͕̝̩̩͎̹̭̏̇͒̎̾́̃̊̒͐̀̈́̒̉͋̾͗̽̈́̕͝͝͝͝b̸̨̢̛̠̳̣̮͚̦̯̯̬͖̈́̅͗͑͆̿̍̽̎͗͒̈́̈͂̑̈͋̓͘̚͜l̵̡̡̛͖̦̗̹͖̺̲͇͙͍̱͗̍̋̎̊͆̈́̀͐̇̓͐̽͛̌̓̋̔͑̿̊̔͝ͅͅs̶̢̡̰̰͇̺͍̹̞̝͖̙̟̩͖̼̟̺̥̿̍̕͝ͅd̴̨̨̼̪̞̻̞͇̰̻̠̗̣̼̦̮̑̾͂͜͝ͅa̴̧̧̢͕̤̙̬͙̞̻̜̙͓̥̗̽͂̈̃͒̐̔̾̊̂̅̃̊̐͌̓̕͘͝ǩ̸̮̼͈̠̩̱͖̳̜̝̞̥̞͈̺̬̹̠̗̎͐͆̒͌̂̉͒͆̕͝j̸̨̡͔̟͈̖̠̥͔̟͙̞̮͍̟͉̫̠͍̤̹̭̰̆͒̎̋͗́͗̆̔̈́̚͘͠͠͝ͅb̶̨̛̖͎͔̮̳͔͈̦͉̤̤̣̩̜̥͙̽̓̾̆̒̇̏͛̌̀̓̅̊̌̚̚͘͘͝ͅv̴̧̨͔̠͖̺̥̬͈̲͇̱̹̤͔̭͔͈̦̟̳̆̾͒̾̃̉͊̾͆͜͝ĺ̶̨̝͕͓̘͖͕̟̩̝͙̰̰̳͗͛̒͌̽͛̃͂͂̆̿̉͐͛́́͑̾̈́͘̚̚͝ḑ̵̯̗̜̮̞̼̱̜̜͚͓̱̯̺̯̪̲͕̳͚͔̌͌͆̀̓͒͂́̐̈́̈́̀͋̇̄̀̈́͝ŝ̶̹̳̦̝͉̩̠̄̔̊͂̂͆̂͑̓̽̊͂͠ͅķ̷̳̲̙̖̻̑͑͒̊͂̄̀͑̃̎͂̄̿́͆̔̽̎̅̒̾̿͘̚͜d̶͚̬͔̳̖͙͇͉̜͙͗̉̇̏͌̽͜j̵̧̖̟͉͚̮͑́̓̇̿̍͂̀̋̈̅̆̾̈́̀̾̓̆͒͝͠b̷̦̫̲̻͈̪͍̩̳̱̋̾̑̊̄͗̓͐͐̄̊͋̊̾̈́̎̒͐̕͜͝͝͠͠v̷̢̧̛̞̬̘̭͈̹̣̱̮̽͛͊͊͆͌͛̽̽̏̉̽͌͛̚͜͝͝͝l̵͍̲̰̥̙̭̻͇͎̞̺̹̝͎͕͇͛̚͜͝k̶̨̤̪̜̻̣̰̜̤͙̼̼͔̓̇̈́̅͌͊̽s̷̪̝̠͚̣͈̤͔̙͒̐̆̈́͊̇̇̆̀́͋͆͂̽̏͆̇̒̚ã̴͔͓̯̤͉̹̘̱͉̤̝͋͊͗̿̆̾̕j̸̡̧̢̙̝͙͖̪̭̋̊́̏́b̶̭̰̲͙̮͙̙͔͉̹͓̐͗̚͜͝ͅͅͅĺ̶̢̯͖̗̗̳͇̦͚̮̲͔̪̜̣͓͕̰̬̈̑̓̍̀̓́͛̅͗͐̕͘k̶̞̭͊̄̌̋̀̚s̶̛̛̼̹̗̙̩̈́͒͋͛̓́͋̏̑͊̍̔͒͋̽͐̈́̇̚͠͠͝j̵̭̥̱̙͕̋͌̓̒͐̒̅͆̒́b̴͚̋̽̀̍͐͛͂͊͐̆̈́́̈́̂̂̿̓̓̾̊̕̕͘s̴̠̼̰̺͇̩̞͖͓̰̤͔̹̟̹͇̣̫̲͖̫͖̖͓̉̂̆̃̄͗͛͗͂͐̿̓̓̈́a̸̻̙̖̰͎̰̲͊̾̀̋̍͋̿̎̿̀̂̍̒̀̎̚̕͠͝͝͠l̴̪̩̜͉̮̹͚̳̐̓͒̑̐̐̂̃͛̃̓̐͜͠k̵̡̛̛̠̭͈͔͍̰͎̟̱̥̟̑̏̉͛̏͗͗̊͑̌͊̀̉̅́͒̿̐̓̕͠͠j̶̡̨̧̧̛̛͓͍̱̟͈̘̳̱̦͍̝̜̰̣͈͉͔̫͈̿̃̈́͒͂̍̈s̶̡̛͙̪̟͇͍̲̘͇͚̅̎̾̆̿̾͐̀͒̇́̾̃̒̕͘͠͠b̸͕̻͎̦̻̻͓̬̗̦́̄̀͑̕͝ĺ̵̠̼̱̫͚̩͓͎͚̼̱̰̦̮̹͖͖̼̼̱̲̲̅̃̓̅͋͒̈́̓̔̏̀̿̉̃̃̉̈́̒͜͠k̸̢̨̡̛̦̩̗͖͚̹̯̠̟̮̣̬̬̬̯͈̺͔̊̋̂̓́̀̍͒̂̿̌̆̂̚͜ͅͅa̸͕̯̟͙̮̬̫̲͓̞̜͙̘͙̤̮̯̥̠͈̯͑̍̽̍̽̅͗̑̿̉̏̐̎́̀̈͜ṣ̶̺͈̮̠͕͎̜́̔̽̅̉̐̈́̄̋͌̀͊̓͗̀͗̓̎͝ͅd̴̨͚͎͓̿ͅṽ̶͙̺̭̊̉̈̎̃͐͑̂̈́̿͗̎̓̎̒̉̍͊͜b̷̤͓̭̲̑̅̃͂̅̂͘ḽ̸̡̡̛͖̘͚͚́̽̌͂̆̋̈̊̅̄̎̐͗̾̑̓k̴̛͇͍̤͇̙͎̼͔̗͙̮͕͙͈̯̼̹̱̘̣̑͊̒͋͂́̓͌͛̃̏̂̍́̽v̸͓͚̻̩̦̻͉͈̯̲̭̼̣̬͚͔̫̙̩̮̂̅́̅͒̈̊̉͆̍̇̆̐̌̈́̌ͅͅs̷̨̲̪̱͈̮͕̱͍͕͖̦̞̥̱̜̓͗̓ḑ̴̦̹̗͖̠̳̭͓̠͇͌͛̊̈̈̓̒̋̐͂̅̾̊͘̚̕͝͝ą̸̟̮̙͕͙̗̺͓̟̭̘͓͈̋͌̍̅͌͛̉̉̋̔̊͂̌̑̾̚͝b̸̰͇̞̗̹͉̳͉͎̙͍͎̪̮̟͔̮̼͒̈́͋̃͌̄̚ͅs̶̛͓̯̗̲̰̗̮͖̦̘͙̬͈͔͎̠͉̬̫̓̐̉̃̃͂͗̈́̇́̚̕͘̚̕l̴͉͚̩̎̈̈́̐͆̓̈́̏͘d̴͓̣͈͇̠̙̳̎͊͂͒̀̅̈́̎́͋k̶̙̘̆̈́͂͋͒̂͆̔͑̋͋̄͛͛̐̚͘̕̕͠͝b̸͕̗̳̫̲͒̉̈́͊̑́̉̑̌̈̓̾̌͒ś̵̢̡̢͕̜̰̥̥͎͖͎̺̺̠͉̆̅̓̐̌̅͝ͅļ̸̨̠̝̬͈̬̦͈̙̲̼͇͙̦̠̭̺͐̉̇̐̀̉̅͘͜͜ͅk̸̡̡͓̦̥̬̣͍͓̲̒̀̔̋̔̊̚̚s̵̡̖̤̙̝̠̺͚͎̼͈̝̗͈̞̲̮̈̅̈́̉͐̓̃̈́̎́͑̋̽̂̃̋̏̕͘͘͝͝a̴̧̨̛̮͇̟͕̣̹̙̖̥̜͇̱̦̗̫̠̘͔̩̅̆̓͊̎̿̅͌̾̋̿̓̌͋̂̈͗̄̓̕̚͜͠ͅb̵̢̰̞̝̥͉͙̟̜̘͕̜͆̈́̾͐̔̆͛̉̚̚ͅͅs̷̙͚͈͙̽̅̏̓̈́̊̊͂͑́͊̐̄̇̀̾̊͝͠a̵̛̛̍̆̐͋̋͐̃̆̔̅̊");
        


        sleep(2);
        clearScreen();
        sleep(2);
        cout << endl;
        sleep(2);

    }

    void bankBoot(Player &player)
    {
        showMessage("Hello there, wanderer. Look's like you are just in time!", "We were just about to go on a lunch break!", 3, "Vivian");
        sleep(3);
        showMessage("My name is Vivian, and I am the local bank handler", "The best one at that, you could say!", 3, "Vivian");
        sleep(2);
        showMessage("[Vivian chuckles to herself]", "", 1);
        sleep(2);
        showMessage("Oh, the lunch break? That happens once a while, don't worry!", "Anyways, you must be the new one in town!", 3, "Vivian");
        sleep(2);
        ostringstream welcomeMessage;
        welcomeMessage << player.name << "... right? Welcome!";
        showMessage(welcomeMessage.str(), "So as per procedure, you will be given a default Savings Bank account. Should I proceed?", 2, "Vivian");
        sleep(3);
        showMessage("Savings acoount for... " + player.name + " ...aaand, done!", "", 0, "Vivian");
        sleep(1);
        achievementMessage("Bank account Created");
        sleep(2);
        achievementMessage("Selling Unlocked");
        sleep(3);
        showMessage("However, I would recommend you take our credit card plans they are much more benificial to us- I mean, you.", "Or, you could take a loan, at very low intrest rates starting at just 20.8%", 4, "Vivian");
        sleep(3);
        showMessage("[ Vivian checks her watch ]");
        sleep(3);
        ostringstream welcomeMessage2;
        welcomeMessage2 << player.name << ", I would love to tell you more about our plans...";
        showMessage(welcomeMessage2.str(), "But I need to have lunch now, so apologies, the bank must close!", 2, "Vivian");
        sleep(2);
        showMessage("You can always come back to the bank, to check your balance", "and maybe when you are rich enough, you can take loans from us! Assuming we are open, ofcourse, but, [in a hurry], bye for now!", 3, "Vivian");
        sleep(6);
        cout << "exiting bank..." << endl;
        sleep(3);
        cout << endl;

        
    }

    void sellerMarketBoot(Player &player)
    {
        string name = Manjunath.name;
        sleep(1);
        showMessage("[Puffs out smoke]", "*cough* *cough*", 2, name);
        sleep(2);
        showMessage("Ahoy there, what do we have here...", "Looks like a miner, by the outfit, I suppose", 2, name);
        sleep(2);
        showMessage("[Laughs at his own joke]", "You know, I really ought to look forward to this", 2, name);
        sleep(2);
        showMessage("My knees have given up on me", "I can no longer go up those cave no more, mine them diamonds...", 3, name);
        sleep(2);
        showMessage("But alas, you, young soul, can do it!", "Better than me, I suppose, ha ha ha", 2, name);
        sleep(2);
        showMessage("And I'll do you one better, why not...", "You can always come to me and I would buy your findings from the mine", 3, name);
        sleep(2);
        showMessage("For a reasonable cost, ofcourse!", "So make sure you have a bank account that I can pay you to..", 2, name);
        sleep(2);
        achievementMessage("Selling Unlocked");
        achievementMessage("Bank Unlocked");
        sleep(2);
        showMessage("Or you could just show up to have a conversation...", "This not-so-old man can really do with some companionship...", 2, name);
        sleep(2);
        showMessage("exiting market...");
        sleep(3);
        player.sellerMarketBoot.occured = true;
        player.sellerMarketBoot.timesOccured++;

    }
};

class Market
{
    public:
    double basePrice = 0.25;
    double priceMultiplyer = 10.0;

    vector<item*> setPrices(vector<item*> items)
    {
        for(int i = 0; i < items.size(); i++)
        {
            items[i]->sellPrice *= basePrice * pow(priceMultiplyer, 1 - items[i]->rareity);
        }
        return items;
    }

    void resetPrices(vector<item*> items)
    {
        for(int i = 0; i < items.size(); i++)
        {
            items[i]->sellPrice /= basePrice * pow(priceMultiplyer, 1 - items[i]->rareity);
        }
        return;
    }

    void menu(Player &player)
    {
        if(!player.sellerMarketBoot.occured)
        {
            achievementMessage("Seller's Market Unlocked");
            Events event;
            event.sellerMarketBoot(player);
            return;
        }

        if(!player.bankBoot.occured)
        {
            cout << "You do not have a bank account to recieve money to. Go to bank!" << endl;
            return;
        }
        basePrice *= player.luck;
        priceMultiplyer *= player.luck;
        cout << "You have entered the market... buckle up!" << endl;
        sleep(1);
        cout << "s) SELL\nb) BUY\nq) quit market\n>> ";
        char res[2] = {'a', '\n'};
        cin >> res[0];

        if (res[0] == 's')
        {
            while (true)
            {
                sell(player);

                char r;
                cout << "Do you want to continue selling? (y)\n>> ";
                cin >> r;

                if(r != 'y')
                {
                    break;
                }

            }
            
        }
        else if (res[0] == 'b')
        {
            buy();
        }
    }
    void sell(Player &player)
    {
        // vector<item*> activeItems = player.getActiveItems(); //
        // cout << "active items recieved to sell fn" << endl;
        vector<item*> items = setPrices(player.getActiveItems());

        if (items.size() > 0)
        {
            for (int i = 0; i < items.size(); i++)
            {
                cout <<  i + 1 << ") " << items[i]->name << ": $" << items[i]->sellPrice << " per unit \t|\t You have: " << items[i]->count << "." << endl;
            }

            cout <<  "0) Quit"<< endl;
            int res;
            do
            {
            cout << "Sell Item by index >> ";
            cin >> res;
            } while (res > items.size() || res < 0);
            
            res--;

            if(res == -1)
            {
                return;
            }

            for (int i = 0; i < items.size(); i++)
            {
                if(items[i] == items[res])
                {
                    cout << "You have: [" << items[res]->name << " - " << items[res]->count << "] - Sell price: [$" << items[res]->sellPrice << "] per unit." << " (Max profit: [" << moneyAsString(items[res]->sellPrice * items[res]->count) << "])" << endl;

                    int countSelling;
                    do
                    {
                        cout << "Enter Quantity >> ";
                        cin >> countSelling;

                    } while(countSelling < 0 || countSelling > items[res]->count);

                    player.bankBalance += items[res]->sellPrice * countSelling;
                    cout << "selling..." << endl;
                    items[res]->count -= countSelling;
                    sleep(2);
                    cout << "Business sucessful!\n\t+ " << moneyAsString(items[res]->sellPrice * countSelling) << "$.\tKa-ching!" << endl;
                    sleep(1);
                }
            }

            resetPrices(items);
            return;

            
        }
    }
    void buy()
    {

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
    int mineLevels[MAX_MINE_LEVELS] = {0, 55, 127, 377, 695, 889, 780, 1001, 2350, 3978, 5112, 7500};


    void getMineLevel(Player &player)
    {
        for (int i = 0; i < MAX_MINE_LEVELS; i++)
        {
            if(player.timesMined == mineLevels[i])
            {
                cout << "You are at mine level " << i << "." << endl;
            }
        }

        switch(player.timesMined)
        {
            case 1:
            showMessage("This might take a while...", "", 0);
            break;
            case 3:
            showMessage("The items you mine would be stored in your inventory...", "click 'i' on the prompt menu to access it.", 1);
            player.inventoryUnlock.occured = true;
            break;
            case 6:
            showMessage("Mining takes so long...", "If only there was a way to speed things up...", 1);
            break;
            case 9:
            showMessage("To get details about your position in the mine, enter 'd' into the terminal when in the mine.", "", 0);
            player.mineDetailsUnlock.occured = true;
            break;
            case 10:
            showMessage("And you can quit the mine by entering 'q'.", "", 0);
            player.quitMineUnlock.occured = true;
            break;
            case 15:
            if(!player.sellerMarketBoot.occured)
            {
                showMessage("You can sell the items you mine in the seller's market.");
                achievementMessage("Seller's Market Unlocked");
                char res;
                while(res != 's')
                {
                    res = getPlayerResponse("Click 's' to enter seller's market.");
                }
                Events event;
                event.sellerMarketBoot(player);

                cout << "Back to mine..." << endl;
            }
            //seller's market cutscene
            break;
            

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
            if (i == MAX_MINE_LEVELS - 2 && player.timesMined >= mineLevels[i]) {
                currentMineLevel = i;
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
        vector<item*> mineable;
        int mineableCount[2] = {0, 3};           //                         0    1      2    3      4       5       6       7       8       9       10      11      12      13
        vector<item*> items = player.getItemsByAddress();  // vector<item> items = {dirt, rock, wood, coal, granite, iron, copper, silver, tin,   hardRock, gold, diamond, ruby, blackStone, magma, bedrock}; vector<item*> items = {&dirt, &rock, &wood, &coal, &granite, &iron, &copper, &silver, &tin, &hardRock, &gold, &diamond, &ruby, &blackStone, &magma, &bedrock};
        player.caluclateWeights(items);
        switch (mineLevel)
        {
        case 0:
            mineableCount[0] = 0;
            mineableCount[1] = 4;
            break;
        case 1:
            mineableCount[0] = 0;
            mineableCount[1] = 5;
            break;
        case 2:
            mineableCount[0] = 0;
            mineableCount[1] = 6;
            break;
        case 3:
            mineableCount[0] = 0;
            mineableCount[1] = 7;
            break;
        case 4:
            mineableCount[0] = 0;
            mineableCount[1] = 8;
            break;
        case 5:
            mineableCount[0] = 0;
            mineableCount[1] = 9;
            break;
        case 6:
            mineableCount[0] = 0;
            mineableCount[1] = 10;
            break;
        case 7:
            mineableCount[0] = 0;
            mineableCount[1] = 11;
            break;
        case 8:
            mineableCount[0] = 0;
            mineableCount[1] = 12;
            break;
        case 9:
            mineableCount[0] = 0;
            mineableCount[1] = 13;
            break;
        case 10:
            mineableCount[0] = 0;
            mineableCount[1] = 14;
            break;
        case 11:
        case 12:
            mineableCount[0] = 0;
            mineableCount[1] = 16;
            break;
        default:
            break;
        }

        for (int i = 0, j = mineableCount[0]; i < mineableCount[1]; i++, j++)
        {
            mineable.push_back(items[j]);
        }

        float totalWeight = 0;
        for (int i = 0; i < mineableCount[1]; i++)
        {
            totalWeight += mineable[i]->weight;
        }

        int itemRepeatCount = player.dualItems.occured ? randInt(2,3) : 1;
        cout << "You got: " << endl;

        for(int i = 0; i < itemRepeatCount; i++){
            float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * totalWeight;
            item* selecteditem;

            float accWeight = 0;
            for(int i = 0; i < mineableCount[1]; i++)
            {
                accWeight += mineable[i]->weight;
                if(random < accWeight)
                {
                    selecteditem = mineable[i];
                    break;
                }
                random -= mineable[i]->weight;
            }
            int itemCountByLevel = 7;
            int count = (randInt(1, itemCountByLevel) * selecteditem->rareity) + 1;
            
            cout << count  << " pieces of " << selecteditem->name << endl;
            player.incrementItemCount(selecteditem->name, count);

             auto it = find(mineable.begin(), mineable.end(), selecteditem);
                if (it != mineable.end())
                {
                    mineable.erase(it);
                    // Recalculate total weight after removal
                    totalWeight = 0;
                    for (auto& itemPtr : mineable)
                    {
                        totalWeight += itemPtr->weight;
                    }
                }
        }


    }

    void enter(Player &player)
    {
        if(player.firstBoot.occured)
        {
        getMineLevel(player);
        }
        else {
            cout << "It's dark. You are now in a mine. Enter 'm' to mine it..." << endl;
        }
        char res = 'a';
        while(true)
        {
            cout << ">> ";
            cin >> res;
            if (res == 'd' && player.mineDetailsUnlock.occured)
            {
                display(player);
                continue;
            }
            if (res == 'i' && player.inventoryUnlock.occured)
            {
                player.displayInventory();
                continue;
            }
            if (res == 'q' && player.quitMineUnlock.occured)
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

class Bank
{
    public:
    long double bankBalance;

    void bankBoot(Player &player)
    {
        cout << "Welcome to the city bank!" << endl;
        sleep(1);
        Events event;
        event.bankBoot(player);

    }

    void enter(Player &player)
    {
        if(!player.bankBoot.occured)
        {
            bankBoot(player);
            player.bankBoot.occured = true;
            player.bankBoot.timesOccured++;
            player.bankOnLunchBreak.occured = false;
            return;
        }
        cout << "Welcome to the city bank!" << endl;
        bankBalance = player.bankBalance;
        
        sleep(1);
        int x = randInt(0, 100);

        if (x <= 15)
        {
            player.bankOnLunchBreak.occured = true;
            player.bankOnLunchBreak.timesOccured++;
        }
        
        if(player.bankOnLunchBreak.occured)
        {
            achievementMessage( "The bank is on a lunch break. Come back in a while!" );

        } else {

            showMessage(getDialogue(Vivian), "", 2, Vivian.name);

            while(true)
            {    
            cout << "a) Check Balance\nb) Get a Loan\nq) Quit Bank\n>> ";
            char res;
            cin >> res;

            if (res == 'a')
            {
                cout << "Name: " << player.name << endl;
                cout << "Bank Balance: $" << moneyAsString( player.bankBalance ) << endl;

            }
            if (res == 'b')
            {
                if(!player.loansUnlocked.occured)
                {
                    achievementMessage("You are not eligible for bank loans as of now");
                }
            }
            if (res == 'q')
            {
                goto quitBank;
            }
                cout << "Back to main screen (b)\nQuit (q)\n>> ";
                cin >> res;
                if(res == 'q')
                {
                    goto quitBank;
                }
                else if (res != 'b')
                {
                    break;
                }

            // create debt scene later
            }
        }
        cout << "q) Quit Bank\n>> ";
        char res;
        cin >> res;
        
        quitBank:
        player.bankOnLunchBreak.occured = false;
        cout << "exiting bank..." << endl;
        sleep(1);
        return;
    }
};

void gamble(Player &player);
void mine(Player &player);

void mainmenu(Player &player)
{
    // cout << "Player: " << player.name << "\nBank Balance: $" << moneyAsString(player.bankBalance) << endl << endl;
    cout << "GAME ACTIONS" << "\nm) mine\ng) gamble\ni) view inventory\ns) Market\nb) bank\nw) check weather\n>> ";
    char response[2] = {'a', '\0'};
    cin >> response[0];

    switch (response[0])
    {
    case 'g':
        gamble(player);
        break;

    case 'm':
        mine(player);
        break;

    case 'i':
        player.displayInventory();
        break;

    case 's':
    {
        Market market;
        market.menu(player);
        break;
    }
    case 'b':
    {
        Bank bank;
        bank.enter(player);
        break;
    }
    
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
        cout << "Current Bank balance: " << moneyAsString( player.bankBalance ) << endl;
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
        cout << "You are gambling " << (gambleAmount / player.bankBalance) * 100 << "% of your total funds" << endl;
        float profit = session.gamble(gambleAmount, gamemode);
        int pf = rand();
        cout << "gambling...";
        sleep(2);
        if (pf % 2 == 0){ // 50% chance only - add more randomness.... TO DO
            // Profit:
            cout << "You made " << moneyAsString(profit) << " Profit for " << moneyAsString( gambleAmount ) << " Thats a " << ((profit)/gambleAmount)*100 <<  "% increase! Congrats!" << endl;
            player.bankBalance += gambleAmount + profit;
        }
        else{
            cout << "You made a loss of "  << moneyAsString(profit) <<  " for " << moneyAsString(gambleAmount) << " Thats a " << (profit/gambleAmount)*100 <<  "\% decrease. Bad luck!" << endl << endl;
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

    if (!player.firstBoot.occured)
    {
        Events event;
        event.FirstBoot(player);
        mine(player);
    }
    player.firstBoot.occured = true;
    player.firstBoot.timesOccured++;

    npcDialogueInit(player);

    player.name = "Naresh";
    player.bankBoot.occured = false;
    player.sellerMarketBoot.occured = false;
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

- introduce shop at 20 mines
- in the shop, as soon as you sell, introduce banks
SO MANY IDEAS
*/