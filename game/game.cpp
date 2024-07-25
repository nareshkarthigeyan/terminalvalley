#include "dependancies/nlohmann/json.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <atomic>
#include <thread>
#include "utilitieS.hpp"
#include "gameClasses.hpp"


using namespace std;

void gamble(Player &player);
void mine(Player &player);

class Savefile {
public:
  void help() {
    // Help thing here;
  }

  void mainScreen() {
    string balls = " _____                   _             _  __     __    _ _ "
                   "           \n"
                   "|_   _|__ _ __ _ __ ___ (_)_ __   __ _| | \\ \\   / /_ _| "
                   "| | ___ _   _ \n"
                   "  | |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |  \\ \\ / / _` "
                   "| | |/ _ \\ | | |\n"
                   "  | |  __/ |  | | | | | | | | | | (_| | |   \\ V / (_| | | "
                   "|  __/ |_| |\n"
                   "  |_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|    \\_/ "
                   "\\__,_|_|_|\\___|_, |\n"
                   "                          a game by K V Naresh Karthigeyan "
                   "     |___/ \n"
                   "Version 0.01\n";

    cout << balls << endl;

    cout << "\t\t[play game - (p)]\t[help - (h)]" << endl;
    char res = getSpecificPlayerResponse("", 'p', 'h');
    switch (res) {
    case 'p':
      // case here;
      return;
    case 'b':
      // case here;
      help();
      break;
    }
    return;
  }

  void saveGameState(const Player &player) {
    nlohmann::json j = player;
    std::ofstream file("savefile/" + player.name + ".json");
    if (file.is_open()) {
      file << j.dump(4); // Pretty print with an indent of 4 spaces
      file.close();
      //std::cout << "Game state saved successfully." << std::endl;
    } else {
      //std::cerr << "Failed to save game state." << std::endl;
    }
  }


  // Load the game state from a JSON file
  Player loadGameState() {
  tryagain:
    mainScreen();
    std::string path = "savefile/";
    vector<string> files;
    int i = 0;
    cout << "Load an existing save or Create a New Game..." << endl;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      string path = entry.path().string();
      path.erase(path.find("savefile/"), sizeof("savefile/") - 1);
      path.erase(path.find(".json"), sizeof(".json") - 1);
      i++;
      cout << "[" << i << "] " << path << endl;
      files.push_back(path);
    }
    char res;
    cout << "[" << ++i << "] New Game\n>> ";
    cin >> res;
    int ress = res - '0';
    Player player;
    string name;
    if (ress - 1 < files.size()) {
      name = files[ress - 1];
      cout << name << endl;
    } else if (ress == i) {
      cin.ignore();
      cout << "Enter name of the player\n>> ";
      getline(cin, name);
      player.name = name;
    } else {
      cout << "Invalid selection. Try again..." << endl;
      goto tryagain;
      exit(0);
    }

    string fname = path + name + ".json";
    std::ifstream file(fname);
    if (file.is_open()) {
      nlohmann::json j;
      file >> j;
      player = j.get<Player>();
      player.name = name;
      file.close();
      std::cout << "Game File loaded successfully." << std::endl;
      sleep(1);
      clearScreen();
    } else {
      std::cerr << "Created a new game!" << std::endl;
    }
    return player;
  }
};

class menu {
public:
  string name;
  char command;

  void trigger(Player &player) // add all menu items here!
  {
    if (player.currentCity.name == Terminille.name) {

      switch (command) {
      case 'g':
        gamble(player);
        break;

      case 'm':
        mine(player);
        break;

      case 'i':
        player.displayInventory();
        break;

      case 's': {
        Market market;
        market.menu(player);
        break;
      }
      case 'b': {
        Bank bank;
        bank.enter(player);
        break;
      }
      case 'c':
        Guild guild;
        guild.enter(player);
        break;

      case 'p':
        player.display();
        sleep(1);
        break;

      case 'r': {
        RailwayStation rs;
        rs.init();
        rs.enter(player);
      } break;
      case 'q': {
        Savefile save;
        save.saveGameState(player);
      }
        cout << "Game saved!" << endl;
        sleep(1);
        exit(0);
        break;
      }
    }

    if (player.currentCity.name == SyntaxCity.name) {
      switch (command) {
      case 'p':
        player.display();
        sleep(1);
        break;

      case 'w': {
        Pond pond;
        pond.enter(player);
      } break;
      case 'r': {
        RailwayStation rs;
        rs.init();
        rs.enter(player);
      } break;
      case 'i':
        player.displayInventory();
        break;
      case 'q': {
        Savefile save;
        save.saveGameState(player);
        exit(0);
      } break;
      }
    }
  }
};

void mainmenu(Player &player) {
  // cout << "Player: " << player.name << "\nBank Balance: $" <<
  // moneyAsString(player.bankBalance) << endl << endl;
  vector<menu> menu;

  if (player.currentCity.name == Terminille.name) {
    if (player.firstBoot.occured) {
      menu.push_back({"m) mine", 'm'});
    }
    if (player.inventoryUnlock.occured) {
      menu.push_back({"i) inventory", 'i'});
    }
    if (player.sellerMarketBoot.occured || player.bankBoot.occured) {
      menu.push_back({"b) bank", 'b'});
      menu.push_back({"s) market", 's'});
    }
    if (player.guildUnlocked.occured && player.level > 0) {
      menu.push_back({"c) guild", 'c'});
    }
  }

  if (player.currentCity.name == SyntaxCity.name) {
    if (player.inventoryUnlock.occured) {
      menu.push_back({"i) inventory", 'i'});
    }
    menu.push_back({"c) cake shop", 'c'});
    menu.push_back({"w) pond", 'w'});
    menu.push_back({"f) fish shop", 'f'});
  }
  if(player.railwayStationUnlock.occured)
  {
    menu.push_back({"r) Railway Station", 'r'});
  }
  menu.push_back({"p) Player details", 'p'});
  menu.push_back({"q) Save and Quit", 'q'});

  // To add: gamble, guild, weather, railway station.
  cout << player.currentCity.name << " actions:"
       << endl; // "\nm) mine\ng) gamble\ni) view inventory\ns) Market\nb)
                // bank\nw) check weather\nc) guild\n>> ";
  for (int i = 0; i < menu.size(); i++) {
    cout << menu[i].name << endl;
  }
  cout << ">> ";
  char response[2] = {'a', '\0'};
  cin >> response[0];
  for (int i = 0; i < menu.size(); i++) {
    if (response[0] == menu[i].command) {
      menu[i].trigger(player);
    }
  }
}

void gamble(Player &player) {
  char response[2]; // +1 for the null terminator.
  response[1] = '\0';
  float gambleAmount;
  while (true) {
    cout << "Current Bank balance: " << moneyAsString(player.bankBalance)
         << endl;
    do {
      cout << "Enter gamble amount: ";
      cin >> gambleAmount;
      if (gambleAmount > player.bankBalance) {
        cout << "Insufficient Balance! Try again with less bet money." << endl;
      }
    } while (gambleAmount > player.bankBalance);
    player.bankBalance -= gambleAmount;

    Gamble session;
    int gamemode = session.chooseGameMode();
    cout << "You are gambling " << (gambleAmount / player.bankBalance) * 100
         << "% of your total funds" << endl;
    float profit = session.gamble(gambleAmount, gamemode);
    int pf = rand();
    cout << "gambling...";
    sleep(2);
    if (pf % 2 == 0) { // 50% chance only - add more randomness.... TO DO
      // Profit:
      cout << "You made " << moneyAsString(profit, 2, "$") << " Profit for "
           << moneyAsString(gambleAmount) << " Thats a "
           << ((profit) / gambleAmount) * 100 << "% increase! Congrats!"
           << endl;
      player.bankBalance += gambleAmount + profit;
    } else {
      cout << "You made a loss of " << moneyAsString(profit) << " for "
           << moneyAsString(gambleAmount) << " Thats a "
           << (profit / gambleAmount) * 100 << "\% decrease. Bad luck!" << endl
           << endl;
      player.bankBalance += gambleAmount - profit;
    }
    cout << "Do you want to gamble again? (y/n): ";
    cin >> response[0];
    if (response[0] == 'n' || response[0] == 'N') {
      break;
    }
  }
}

void mine(Player &player) {
  Mine mine;
  mine.enter(player);
}

void triggerHomelessMan(Player &player) {
  int random = randInt(1, 100);

  if (random <= 6) // change to 6;
  {
    showDialogue(HomelessMan.name, getDialogue(HomelessMan));
    char res;

    while (true) {
      res = getPlayerResponse("a) Give him money\nb) Ignore");
      if (res == 'a') {
        float amount;
        cout << "Enter amount ( You have: $" << moneyAsString(player.wallet)
             << " ) >> ";
        cin >> amount;

        if (amount <= 0) {
          // cout << "walking away..." << endl;
          // sleep(2);
          res = 'b';
        } else if (amount > player.wallet) {
          achievementMessage("Insufficient Funds with you. Irony.");
          achievementMessage("\t+ 0.01 luck for the good intent\t");
          player.luck += 0.01;
          sleep(1);
          break;
        } else {
          cout << "\t- $" << moneyAsString(amount)
               << "\t keep the good spirits up!" << endl;
          player.wallet -= amount;
          float luckUp =
              0.1 + ((float)(randInt(10, 90) * amount / randInt(50, 60)) / 100);
          player.luck += luckUp;
          ostringstream message;
          message << "\t + " << luckUp << " Player Luck!\t";

          achievementMessage(message.str());

          sleep(1);
          break;
        }
      }

      if (res == 'b') {
        cout << "walking away..." << endl;

        float luckUp = (float)randInt(60, 290) / 1000;
        player.luck -= luckUp;
        ostringstream message;
        message << "\t - " << luckUp << " Player Luck. Womp-womp.\t";
        achievementMessage(message.str());
        sleep(2);
        break;
      }
    }
    player.homeLessManBoot.timesOccured++;
  }
}

void saveThread(atomic<bool> &running, Savefile &save, Player &player)
{
  int i = 0;
  while(running)
  {
    sleep(5);
    save.saveGameState(player);
    i++;
    if(i % 20 == 0)
    {
      achievementMessage("Game autosaved");
    }
  }
}

int main(void) {
  Savefile save;
  Player player = save.loadGameState();
  save.saveGameState(player);

  atomic<bool> running = true;
  thread saveThreading(saveThread, ref(running), ref(save), ref(player));
  saveThreading.detach();

player.fishingRod.level = 1;

  if (!player.firstBoot.occured) {
    Events event;
    event.FirstBoot(player);
    mine(player);
  }


  player.firstBoot.occured = true;
  player.firstBoot.timesOccured++;

  npcDialogueInit(player);

  //remove this:

  while (true) {

    if(player.currentCity.name == "Syntax City" && player.cakeEventStart.occured && !player.cakeEventMid.occured)
    {
      Events event;
      event.VivanCakeEvent2(player);
      player.cakeEventMid.occured = true;
    }
    mainmenu(player);


    //events
    if(!player.bankBoot.occured && player.wallet >= 200)
    {
      achievementMessage("Bank is unlocked! Visit the bank!");
      sleep(1);
    }
    if (!player.homeLessManBoot.occured && player.wallet > 0 &&
        player.currentCity.name == Terminille.name) {
      player.homeLessManBoot.occured = true;
      player.badges.push_back("Guardian Angel");
    }
    if ((player.homeLessManBoot.occured) &&
        (player.currentCity.name == Terminille.name)) {
      triggerHomelessMan(player);
    }
    if (player.bankBoot.occured && player.guildUnlocked.occured && (player.bankBalance >= 1000 || player.wallet >= 1000) && !player.railwayStationUnlock.occured)
    {
      achievementMessage("New Quest Unlocked. Visit Vivian at the bank.");
      sleep(1);
    }
  }

  running = false;
  return 0;
}

/*
TO DO:
- Introduce wallet system, instead of bank account. Bank account to deposit
money and take money from.. wallet, initial limit of 300, once you open bank
account for 200, it increases to 1000. You can buy wallet upgrades as you level
up.... nice! Adds to the storyline too!

- At one point, credit card system (to unlock: 10,000) where it links bank
account and wallet, where once wallet is empty, money goes from crdit card, but
it takes 5% of all transactions as charge!

- Quest to buy vivian a cake in syntax city, on the way there, cutscnee where
player runs into a retired navy seal who teaches him the art of fishing! He owns
a fish shop where he will buy your fishes for money... once cake is given to
vivian, she decreases the cost of wallet upgrade by a certain amount

- a way to write player data into json file and retieve it to make the game
saveable!!

- design fishing mechanism + cake shop mechanism.

- interact with homeless man.. can play rps, or fist bump him, etc.


- confirmation while buying train tix.
- insurance system in bank!! - can buy certain insurances, like travel
insurance, etc.
- 5% chance for train to be cancelled and money refunded... more refund if bank
insurance purchased
- 20% chance for train to arrive in a delay...
- 15% chance to get pickpocketed and lose money when in a train, depends on how
bad your luck is...coverable by insurance
- missed train has no refund... if insurance then 65% refund...
*/

/*
BUGS:
- When prompted for number and letter is entered, it turns into an infinite
while loop...
- train late and platform miss isn't working
*/

// this code snippet was written in vim
// and this in zed
// and this... in neovim
