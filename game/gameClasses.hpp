#ifndef GAME_CLASSES_HPP
#define GAME_CLASSES_HPP


#include "utilitieS.hpp"
#include <iostream>
#include "dependancies/nlohmann/json.hpp"
#include <vector>
#include <string>
#include <array>


#define MAX_MINE_LEVELS 12
#define MAX_FISHIN_LEVELS 6
#define WEIGHT 1

using namespace std;
using json = nlohmann::json;

class item {
public:
  string name;
  int count{0}; // change to 0
  float rareity{1};
  long double buyPrice;
  float xp{0.5};
  string rareityString;
  int totalCount{0};
  float luckFactor{1};
  float weight = WEIGHT / rareity;
  long double sellPrice;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(item, name, count, rareity, buyPrice, xp,
                                 rareityString, totalCount, luckFactor,
                                 sellPrice);
};

struct tool {
  string name;
  int level{0};
  float health{100};
  vector<int> waitTimeByLevel = {6, 5, 4, 3, 2}; // to change
  array<array<item, 2>, 5> required;
  array<array<int, 2>, 5> requiredCount;
  vector<long double> upgradeCost = {250, 1200, 2800, 8500, 17999};
  vector<long double> upgradeXP = {350, 450, 590, 999, 1300};

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(tool, name, health, waitTimeByLevel, required,
                                 requiredCount, upgradeCost, upgradeXP);
};

class Objective
{
  public:

  string name;
  string description;
  bool completed;
  float reward;
  float xpReward;
  int messageShownTimes {0};
  bool inPrgress {false};

  void notifictation()
  {
    static int blah = 0;
    if(blah == 0)
    {
      achievementMessage("New objective Unlocked!");
      achievementMessage(name);
      cout << messageShownTimes << endl;
    }
    sleep(1);
    blah++;
  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Objective, name, description, completed, reward, xpReward, messageShownTimes);
};

class event {
  public: 
  bool occured{false}; // change to false before game
  int timesOccured{0};
  Objective objective;
  bool ready = {false};

  void trigger()
  {
    occured = true;
    timesOccured++;
    objective.completed = true;
  }

  

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(event, occured, timesOccured, objective, ready);
};

class NPC {
public:
  string name;
  string description;
  int interactionCount;
  vector<string> dialogues;
  int heartPoints{0};
  float money {0};

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(NPC, name, description, interactionCount,
                                 dialogues, heartPoints, money)
};

struct city {
  string name;
  bool atCity;
  string code;
  int platformCount;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(city, name, atCity, code, platformCount)
};

// City init:
city Terminille{"Terminille", true, "TRML", 4};
city SyntaxCity{"Syntax City", false, "SXCY", 5};
city Codeopolis{"Codeopolis", false, "CPLS", 6};
// city Cipheria {"Cipheria", false, "CRI", 3};

vector<city> ALL_CITIES = {Terminille, SyntaxCity}; //codeopolis gone

class Inventory {
public:
  bool hasPickaxe = false;

  tool pickaxe = {"Pickaxe", 0};
  tool fishingRod = {"Fishing Rod", 0};

  // Rarity - lower, the rarer

  // Mine items:
  item dirt = {"Dirt", 0, 0.85, 1.79, 1.38};
  item rock = {"Rock", 0, 0.75, 2.75, 2.75};
  item wood = {"Wood", 0, 0.68, 3.25, 3.21};
  item coal = {"Coal", 0, 0.72, 5.60, 4.11};
  item granite = {"Granite", 0, 0.58, 7.68, 5.18};
  item iron = {"Iron", 0, 0.31, 25.11, 11.21};
  item copper = {"Copper", 0, 0.28, 23.21, 15.27};
  item silver = {"Silver", 0, 0.27, 69.69, 21.69};
  item tin = {"Tin", 0, 0.23, 71.42, 18.71};
  item hardRock = {"Hard Rock", 0, 0.29, 159.76, 25.27};
  item gold = {"Gold", 0, 0.09, 595.23, 57.88};
  item diamond = {"Diamond", 0, 0.06, 2800.53, 160.71};
  item ruby = {"Ruby", 0, 0.04, 3500.77, 441.38};
  item blackStone = {"Black Stone", 0, 0.10, 975.21, 338.75};
  item magma = {"Magma", 0, 0.09, 7200.33, 790.55};
  item bedrock = {"Bedrock", 0, 0.08, 10000.11, 1590.78};

  vector<string> rareityString = {
      "Very Common", "Pretty Common",         "Common", "Rare", "Very Rare",
      "Atlantis!",   "How did you find this?"};
  // Fishing items:
  item soakedBoot = {"Soaked Boots", 0, 0.05, 0.79, 1.38, rareityString[0]};
  item seashell = {"Sea Shell", 0, 0.91, 2.25, 0.11, rareityString[1]};
  item usedEarphones = {"Used earphones", 0, 0.20, 0.08, 1.68,
                        rareityString[0]};
  item usedCondom = {"Used condom", 0, 0.01, 0, 0.1, rareityString[0]};
  item salmon = {"Salmon", 0, 0.75, 4.50, 2.79, rareityString[1]};
  item clownfish = {"Clown Fish", 0, 0.74, 5.50, 2.95, rareityString[1]};
  item tuna = {"Tuna", 0, 0.63, 4.99, 3.11, rareityString[2]};
  item trout = {"Trout", 0, 0.43, 7.85, 5.32, rareityString[2]};
  item squid = {"Squid", 0, 0.35, 15.85, 11.18, rareityString[3]};
  item octopusLeg = {"Octopus Leg", 0, 0.21, 37.48, 21.11, rareityString[3]};
  item jellyfish = {"Jellyfish", 0, 0.18, 118.21, 56.5, rareityString[4]};
  item lobster = {"Lobster", 0, 0.17, 150.00, 69.69, rareityString[4]};
  item pearl = {"Pearl", 0, 0.10, 785, 99.5, rareityString[5]};
  item whaleTooth = {"Blue Whale's tooth", 0, 0.09, 10000, 1500,
                     rareityString[6]};

  item blackBerryCake = {"Blackberry Cake", 0, 0, 0};

  vector<item> getMineItems() {
    vector<item> items = {dirt,   rock,       wood,  coal,     granite, iron,
                          copper, silver,     tin,   hardRock, gold,    diamond,
                          ruby,   blackStone, magma, bedrock};
    return items;
  }

  vector<item> getFishItems() {
    vector<item> items = {soakedBoot, seashell,   usedEarphones, usedCondom,
                          salmon,     clownfish,  tuna,          trout,
                          squid,      octopusLeg, jellyfish,     lobster,
                          pearl,      whaleTooth};
    return items;
  }

  vector<item *> getFishItemsByAddress() {
    vector<item *> items = {
        &soakedBoot, &seashell, &usedEarphones, &usedCondom, &salmon,
        &clownfish,  &tuna,     &trout,         &squid,      &octopusLeg,
        &jellyfish,  &lobster,   &pearl,         &whaleTooth};
    return items;
  }

  vector<item *> getMineItemsByAddress() {
    vector<item *> items = {&dirt,    &rock,       &wood,   &coal,
                            &granite, &iron,       &copper, &silver,
                            &tin,     &hardRock,   &gold,   &diamond,
                            &ruby,    &blackStone, &magma,  &bedrock};
    return items;
  }

  vector<item> getAllItems() {
    vector<item> mineItems = getMineItems();
    vector<item> fishitems = getFishItems();
    vector<item> merged;

    for (int i = 0; i < mineItems.size(); i++) {
      merged.push_back(mineItems[i]);
    }
    for (int i = 0; i < fishitems.size(); i++) {
      merged.push_back(fishitems[i]);
    }

    merged.push_back(blackBerryCake);

    return merged;
  }

  vector<item *> getAllActiveItemsByAdress() {
    vector<item *> items = getMineItemsByAddress();
    vector<item *> activeItems;

    for (int i = 0; i < items.size(); i++) {
      // items[i]->count = 1; //remove this
      if (items[i]->count != 0) {
        activeItems.push_back(items[i]);
      }
    }
    items.clear();
    items = getFishItemsByAddress();
    for (int i = 0; i < items.size(); i++) {
      // items[i]->count = 1; //remove this
      if (items[i]->count != 0) {
        activeItems.push_back(items[i]);
      }
    }

    return activeItems;
  }

  vector<item *> getActiveMineItems() {
    vector<item *> items = getMineItemsByAddress();
    vector<item *> activeItems;

    for (int i = 0; i < items.size(); i++) {
      // items[i]->count = 1; //remove this
      if (items[i]->count != 0) {
        activeItems.push_back(items[i]);
      }
    }
    return activeItems;
  }

  vector<tool> getTools() {
    vector<tool> tools = {pickaxe, fishingRod};
    return tools;
  }

  void displayInventory() {
    vector<item> items = getAllItems();
    vector<tool> tools = getTools();

    if (tools.size() > 0) {
      cout << "Tools: " << endl;
      for (int i = 0; i < tools.size(); i++) {
        if (tools[i].level > 0) {
          cout << "\t" << tools[i].name << "(Level " << tools[i].level << ")"
               << endl;
        }
      }
    }

    if (items.size() > 0) {
      cout << "Items: " << endl;
      for (int i = 0; i < items.size(); i++) {
        if (items[i].count > 0) {
          cout << "\t" << items[i].name << ": " << items[i].count << endl;
        }
      }
    } else {
      achievementMessage(
          "You have no items with you. Try mining for resources!");
    }
  }

  void caluclateWeights(vector<item *> items) {
    for (int i = 0; i < items.size(); i++) {
      items[i]->weight = WEIGHT / items[i]->rareity;
    }
  }

  void incrementItemCount(string itemName, int byThis) {
    vector<item *> items = getMineItemsByAddress();
    for (auto &item : items) {
      if (itemName == item->name) {
        item->count += byThis;
        item->totalCount += byThis;
        break;
      }
    }
    
    vector<item *> items2 = getFishItemsByAddress();
    for (auto &fish : items2) {
        if (itemName == fish->name) {
            fish->count += byThis;
            fish->totalCount += byThis;
        break;
      }
    }

  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Inventory, hasPickaxe, pickaxe, fishingRod,
                                 dirt, rock, wood, coal, granite, iron, copper,
                                 silver, tin, hardRock, gold, diamond, ruby,
                                 blackStone, magma, bedrock, soakedBoot,
                                 seashell, usedEarphones, usedCondom, salmon,
                                 clownfish, tuna, trout, squid, octopusLeg,
                                 jellyfish, lobster, pearl, whaleTooth);
};

class PlayerEvents {
public:


  // Event List
  // boot event:
  event firstBoot;
  event homeLessManBoot;
  event donateToHomeLessMan;

  // mine events
  event inventoryUnlock;
  event mineDetailsUnlock;
  event quitMineUnlock;
  event dualItems;
  event shopUnlock;

  // bank events:
  event bankBoot;
  event bankOnLunchBreak;
  event loansUnlocked;
  event playerCreditCardUnlock;
  event playerWalletUpgrade;
  event cakeEvent;
  event cakeEventStart; //First cutscene
  event cakeEventMid; //Second cutscene
  event cakeEventEnd; //final cutscene

  // market events
  event sellerMarketBoot;

  // guild events:
  event guildUnlocked;

  // railway Station:
  event railwayStationUnlock;

  

  vector <event*> getEvents()
  {
    vector <event*> playerEvents = {&firstBoot, &homeLessManBoot, &donateToHomeLessMan, &inventoryUnlock, &mineDetailsUnlock, &quitMineUnlock,
                                    &dualItems, &shopUnlock, &bankBoot, &bankOnLunchBreak, &loansUnlocked,&playerCreditCardUnlock,&playerWalletUpgrade,
                                    &cakeEvent, &sellerMarketBoot,&guildUnlocked,&railwayStationUnlock, &cakeEventStart, &cakeEventMid, &cakeEventEnd};
    return playerEvents;
  }

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerEvents, firstBoot, homeLessManBoot, donateToHomeLessMan, inventoryUnlock, mineDetailsUnlock, quitMineUnlock,
                                    dualItems, shopUnlock, bankBoot, bankOnLunchBreak, loansUnlocked,playerCreditCardUnlock,playerWalletUpgrade,
                                    cakeEvent, sellerMarketBoot,guildUnlocked,railwayStationUnlock, cakeEventStart, cakeEventMid, cakeEventEnd)
};



class Player : public Inventory, public PlayerEvents {
public:
  string name;
  long double bankBalance {0};
  long double wallet {0};
  float walletLimit{300.00};
  struct creditCard {
    bool has{false};
    float convinienceCharge{0.05};
    bool hasInsurance{false};
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(creditCard, has, convinienceCharge,
                                   hasInsurance)
  } creditcard;
  float luck{1};
  int timesMined {0};
long double xp {0};
  int level{1};
  array<int, 7> xpToLvl = {300, 1500, 4750, 8900, 15000, 25000, 50000};
  city currentCity = Terminille;
  vector<string> badges;

  int timesFished;

  bool firstTime = true;

  vector<Objective> objectives;  

  void createPlayer(string namePrompt) {
    name = namePrompt;
    bankBalance = 0;
    timesMined = 0;
    xp = 0;
    currentCity = Terminille;
  }

  void lvl() {
    int newLevel = 1;
    for (int i = 0; i < 7; i++) {
      if (xp >= xpToLvl[i]) {
        newLevel = i + 2;
      }
    }

    if (newLevel != level) {
      level = newLevel;
      cout << "You are now at level " << level << "! Congrats!" << endl;
      achievementMessage("Level Up!");
    }
  }

  void addXP(long double additionalXP) {
    xp += additionalXP;
    lvl();
  }

  void display() {
    lvl();
    cout << "Name: " << name << "\nLevel: " << level << "\nXP: " << xp << " / "
         << xpToLvl[level - 1] << "\nLuck: " << luck
         << "\nWallet: " << moneyAsString(wallet, 2, "$") << " / $"
         << walletLimit << endl;

         cout << "Achievements: " << endl;
         for(auto item: badges)
         {
          cout << "\t" << item << endl;
         }
  }

  bool depositToWallet(float amount) {
    float walletSpaceLeft = walletLimit - wallet;
    if (amount > walletSpaceLeft && !creditcard.has) {
      cout << "You do not have enough wallet space left. Deposit money in the "
              "bank or increase your wallet limit. Visit the bank."
           << endl;
      return false;
    } else if (amount > walletSpaceLeft && creditcard.has) {
      cout << "Insufficient balance in wallet. Use credit card to directly "
              "recieve? ("
           << creditcard.convinienceCharge * 100 << "% convinience fee) (y/n)?";
      char res;

      while (true) {
        //res = getSpecificPlayerResponse("", 'y', 'n');
        if (res == 'y' || res == 'n') {
          break;
        }
      }
      if (res == 'y') {
        bankBalance += amount - (amount * creditcard.convinienceCharge);
        cout << "\t + "
             << moneyAsString(amount - (amount * creditcard.convinienceCharge),
                              2, "$")
             << "\t Ka-Ching!" << endl;
        cout << "Deposited to your bank account!" << endl;
        cout << "Bank Balance: " << moneyAsString(bankBalance, 2, "$") << endl;
        return true;
      } else {
        cout << "Transaction aborted" << endl;
        return false;
      }
    } else {
      wallet += amount;
      cout << "\t + " << moneyAsString(amount, 2, "$") << "\tka-ching!" << endl;
    }
    return true;
  }

  bool withdrawFromWallet(float amount) {

    if ((amount >= 0) && (amount <= wallet)) {
      wallet -= amount;
      cout << "\t - " << moneyAsString(amount, 2, "$") << endl;
      sleep(2);
      return true;
    } else if (amount > wallet && creditcard.has) {
      cout
          << "Insufficient balance in wallet. Use credit card to directy pay? ("
          << creditcard.convinienceCharge * 100 << "% convinience fee) (y/n)?";
      char res;

      // while (true) {
        res = getSpecificPlayerResponse("", 'y', 'n');
        // if (res == 'y' || res == 'n') {
        //   break;
        // }
      // }
      if (res == 'y') {
        bankBalance -= amount + (amount * creditcard.convinienceCharge);
        cout << "\t - "
             << moneyAsString(amount + (amount * creditcard.convinienceCharge),
                              2, "$")
             << endl;
        cout << "Withdrawn from Bank Account" << endl;
        cout << "Bank Balance: " << moneyAsString(bankBalance, 2, "$") << endl;
        return true;
      } else {
        cout << "Transaction aborted" << endl;
        return false;
      }
    } else if (wallet < amount) {
      cout << "Insufficient balance in wallet! Withdraw money from bank or "
              "increase your wallet limit to accomodate more running cash. "
              "Visit the bank.."
           << endl;
    } else {
      cout << "bruh." << endl;
    }
    return false;
  }


  // NLOHMANN_DEFINE_TYPE_INTRUSIVE(
  //     Player, name, bankBalance, wallet, walletLimit, creditcard, luck,
  //     timesMined, xp, level, xpToLvl, currentCity, timesFished, firstTime, objectives,
  //     hasPickaxe, pickaxe, fishingRod, dirt, rock, wood, coal, granite, iron,
  //     copper, silver, tin, hardRock, gold, diamond, ruby, blackStone, magma,
  //     bedrock, soakedBoot, seashell, usedEarphones, usedCondom, salmon,
  //     clownfish, tuna, trout, squid, octopusLeg, jellyfish, lobster, pearl,
  //     whaleTooth, firstBoot, homeLessManBoot, inventoryUnlock,
  //     mineDetailsUnlock, quitMineUnlock, dualItems, shopUnlock, bankBoot,
  //     bankOnLunchBreak, loansUnlocked, playerCreditCardUnlock,
  //     playerWalletUpgrade, sellerMarketBoot, guildUnlocked,
  //     railwayStationUnlock, badges, cakeEventStart, cakeEventMid, cakeEventEnd, cakeEvent) //can't have more than 64!
};

NPC Vivian = {"Vivian", "Bank Handler", 0};
NPC Manjunath = {"Manjunath", "Buyer. Likes Dad Jokes", 0};
NPC HomelessMan = {"Homeless Man",
                   "Asks for spare change. Claims to be your guardian angel",
                   0};
NPC Redacted = {"???", "Player guide.", 0};
NPC System42 = {"System42", "Prevents 4th wall breaks.", 0};
NPC BillMurry = {"Bill Murry", "Weather reporter.", 0};
NPC Rick = {"Rick", "Guild Master", 0};
NPC bitwise = {"Mayor Bitwise", "Mayor of the town.", 0};

void npcDialogueInit(Player &player) {
  Vivian.dialogues = {
      "Heyy... What's up!",
      "You know, sometimes, the bank manager says I need to be more polite, "
      "but I don't understand - aren't I poilite enough?",
      "I wonder what's for lunch today... spheggati would be nice!",
      "Do you need a loan?",
      "Don't you think pinapple pizza is a crime?",
      "The best food is eaten when you're the most hungry!",
      "I have so much paperwork left...! It's making me so hungry!!",
      "I'm really looking forward to my lunch today!",
      "I went to my best friend's marriage the other day, and the food was "
      "awful!",
      "The bank manager is such as ass sometimes, he calls me to his cabin for "
      "no reason...",
      "I'll go check out the restaurant across the road after dealing with "
      "you.",
      "If the universe started from big bang, what's before big bang? What's "
      "the something that made nothing into not-nothing?",
      "I'm not it the mood to talk now, tell me what you want...",
      "The best way to ask me out on a date is offer me food.",
      "Sometimes I think I'm not good enough, but then I see other people who "
      "are worse than me, and then I feel better.",
      "Am I married? Uh....",
      "...",
      "[picks nose]",
      "My last boyfriend was a jerk, but he was the best chef in town "
      "though...",
      "Why does imaginary use of numbers in economy hold so much power?",
      "Do you think the terminal universe also has inflation?",
      "It has been 3 hours not thinking about food.... oh... I just did.",
      "Nothing makes sense in life.",
      "Between you and me, the credit card system is rigged to make you poor, "
      "but that's just me though.",
      "You won't believe me, but when I walked into the bank manager while he "
      "was changing, I swear he wore panties!",
      "The Indian filter coffee has got to be the best coffee in the world!",
      "Uhm, why haven't I accepted your request on Instagram...? uh...",
      "Hey, have you got any gossip?",
      "Do I manupilate tax papers? How rude...",
      "I could really do for a cake right now.",
      "A few years back, I use to like a guy named Oscar, too bad he was gay."};

  Manjunath.dialogues = {
      "Howdy! How's the business going?",
      "Back in my days, we use to mine by hand, the current convinences like "
      "pickaxe never existed!",
      "Sometimes I feel I pay too much to you...",
      "What makes a good miner? Well, just keep mining and you will know...",
      "You know, when my wife left me for that seal navy, the only thing that "
      "kept me going was the smell of coal",
      "I went to the bank the other day, that lady is a peculiar one, I must "
      "say...",
      "In my army days, the war fleet use to have magazines with pictures of "
      "women, it was popular among the folks!",
      "The only thing that kept me going in darkness was the light that it "
      "didn't show me.",
      "Kid... don't tell me you are one of those new-age miners that disregard "
      "the beauty of hand mining... ahh those days!",
      "The business has been a bit rough recently",
      "New technologies confuse me sometimes...",
      "Have I ever been scammed? I don't know, you should ask me when I do.",
      "You ough to meet my son someday, he lives across the globe.",
      "I wish my son would meet me some days, he works too hard for his own "
      "good...",
      "My son called me the other day, he can't make it this weekend... I "
      "guess I'll have to wait for the next holiday season",
      "When people ask me why she left me, I still don't know what to say...",
      "Items use to cost way less when I was your age, stock market has ruined "
      "everything...",
      "Do I hate navy seals? Young soul, I hold nothing against them.",
      "Discount? I'm already offering you the best prices...",
      "News paper companies have really \"fell off\" now...",
      "I could do with one of the good ol' magazines right now...",
      "The older you grow, the more you realise life is meaningless",
      "It never really gets better, we just get used to things being worse and "
      "shitty all the time."};

  HomelessMan.dialogues = {
      "I say the world can go to hell, but I must have my tea",
      "How do you claim to be alive, and you have no story to tell",
      "Most things they claim to change life don't amuse me",
      "Morality? [laughs] what even is that? A fantasy?",
      "It's better to be delusional and in a mental paradise than being wound "
      "up in reality and suffering",
      "The stars seem to align to tell me that I am insignificant.",
      "There is not much difference between me and you, we both are the same, "
      "yes",
      "Being sincere can also mean being stupid at the same time.",
      "love is suffering, there is no other meaning to it",
      "My god, a moment of bliss, isn't that enough for this lifetime?",
      "The secure ones are the most insecure if you watch them closely...",
      "I have seen the things you can never imagine...",
      "Nowadays all capable people are terribly afraid of being judged, hence "
      "turn into miserable pieces of shits.",
      "I will never understand how a man of my thoughts can continue living...",
      "Standing against injustice? Isn't is just showing off to the world how "
      "much justice you are... a good person.",
      "Denial of death is the single most thing that drives us from being "
      "afraid to live.",
      "Why bother not looking rude when all your actions are rude enough?",
      "[sings 'why this kolaveri']",
      "Just remember, life is a box of chocolates.",
      "Even after so much of a man's life force has been lost, his beard "
      "continues to grow."};
};

string getDialogue(NPC npc) {
  int size = npc.dialogues.size();
  string dialogue;
  int random = randInt(0, size - 1);

  dialogue = npc.dialogues[random];
  npc.interactionCount++;
  return dialogue;
}

struct dialogue {
  string content;
  string author;
};

class Quest {
  string title;
  string description;
  int levelRequired;
  bool isOccuring{false};
  long double reward;
};

void marketBootCutscene(Player &player);
class Events {
public:
  void FirstBoot(Player &player) {
    cout << "First Boot Cutsence here..." << endl;

    ifstream ip("assets/FirstBoot.csv");

    if (!ip.is_open())
      cerr << "ERROR: files corrupted?" << endl;

    vector<dialogue> firstBoot;
    string content;
    string author;
    while (ip.good()) {
      getline(ip, author, ',');
      getline(ip, content, '\n');
      // cout << "dialogue: " << content << endl;
      // cout << "author: " << author << endl;

      size_t pos = content.find("$player_name"); // to replace playername;

      if (pos != string::npos) {
        content.replace(content.find("$player_name"),
                        sizeof("$player_name") - 1, player.name);
      }
      pos = content.find(";"); // to get commas
      if (pos != string::npos) {
        content.replace(content.find(";"), sizeof(";") - 1, ",");
      }

      if (author == "Achievement") {
        achievementMessage(content);
        sleep(1);
        continue;
      }
      showDialogue(author, content);
    }
  }

  void bankBoot(Player &player) {
    ifstream ip("assets/BankBoot.csv");

    if (!ip.is_open())
      cerr << "ERROR: files corrupted?" << endl;

    vector<dialogue> firstBoot;
    string content;
    string author;
    while (ip.good()) {
      getline(ip, author, ',');
      getline(ip, content, '\n');

      size_t pos = content.find("$player_name"); // to replace playername;
      size_t response = content.find("$get_response"); // to replace playername;

      if(response != string::npos)
      {
        char res = getSpecificPlayerResponse("Do you want to open a bank account now? (y/n)", 'y', 'n');
        if(res == 'y')
        {
          continue;
        } else {
          achievementMessage("Cancelling creation of bank account will block many storylines in the game");
          sleep(1);
          achievementMessage("You can attempt this cutscene again later");
          sleep(1);
          player.bankBoot.occured = false;
          return;
        }
      }

      if (pos != string::npos) {
        content.replace(content.find("$player_name"),
                        sizeof("$player_name") - 1, player.name);
      }
      pos = content.find(";"); // to get commas
      if (pos != string::npos) {
        content.replace(content.find(";"), sizeof(";") - 1, ",");
      }

      if (author == "Achievement") {
        achievementMessage(content);
        sleep(1);
        continue;
      }
      showDialogue(author, content);
    };
    player.bankBoot.occured = true;
      player.bankBoot.timesOccured++;
      player.bankOnLunchBreak.occured = false;
      player.wallet -= 200;

    cout << "exiting bank..." << endl;
    sleep(3);
    cout << endl;
  }

  void sellerMarketBoot(Player &player) {
    marketBootCutscene(player);
    player.sellerMarketBoot.occured = true;
    player.sellerMarketBoot.timesOccured++;
  }

  void vivianCakeEvent1(Player &player)
  {
    ifstream ip("assets/cakeEvent1.csv");

    if (!ip.is_open())
      cerr << "ERROR: files corrupted?" << endl;

    vector<dialogue> firstBoot;
    string content;
    string author;
    while (ip.good()) {
      getline(ip, author, ',');
      getline(ip, content, '\n');
      // cout << "dialogue: " << content << endl;
      // cout << "author: " << author << endl;

      size_t pos = content.find("$player_name"); // to replace playername;

      if (pos != string::npos) {
        content.replace(content.find("$player_name"),
                        sizeof("$player_name") - 1, player.name);
      }
      pos = content.find(";"); // to get commas
      if (pos != string::npos) {
        content.replace(content.find(";"), sizeof(";") - 1, ",");
      }

      if (author == "Achievement") {
        achievementMessage(content);
        player.wallet += 250;
        sleep(1);
        continue;
      }
      showDialogue(author, content);
    }
  }

  void vivianCakeEvent2(Player &player)
  {
    ifstream ip("assets/cakeEvent2.csv");

    if (!ip.is_open())
      cerr << "ERROR: files corrupted?" << endl;

    vector<dialogue> firstBoot;
    string content;
    string author;
    while (ip.good()) {
      getline(ip, author, ',');
      getline(ip, content, '\n');
      // cout << "dialogue: " << content << endl;
      // cout << "author: " << author << endl;

      size_t pos = content.find("$player_name"); // to replace playername;

      if (pos != string::npos) {
        content.replace(content.find("$player_name"),
                        sizeof("$player_name") - 1, player.name);
      }
      pos = content.find(";"); // to get commas
      if (pos != string::npos) {
        content.replace(content.find(";"), sizeof(";") - 1, ",");
      }

      if (author == "Achievement") {
        achievementMessage(content);
        player.blackBerryCake.count++;
        player.blackBerryCake.totalCount++;
        sleep(1);
        continue;
      }
      showDialogue(author, content);
    }
  }

  void vivianCakeEvent3(Player &player)
  {
    int rand = randInt(0, 100);
    string filename;
    if(rand > 15)
    {
      filename = "assets/cakeEvent3good.csv";
      player.badges.push_back("Vivian's Blueberry cake");
    } else {
      filename = "assets/cakeEvent3bad.csv";
      player.badges.push_back("Vivian's Smushed cake");
    }
      ifstream ip(filename);

    if (!ip.is_open())
      cerr << "ERROR: files corrupted?" << endl;

    vector<dialogue> firstBoot;
    string content;
    string author;
    while (ip.good()) {
      getline(ip, author, ',');
      getline(ip, content, '\n');
      // cout << "dialogue: " << content << endl;
      // cout << "author: " << author << endl;

      size_t pos = content.find("$player_name"); // to replace playername;

      if (pos != string::npos) {
        content.replace(content.find("$player_name"),
                        sizeof("$player_name") - 1, player.name);
      }
      pos = content.find(";"); // to get commas
      if (pos != string::npos) {
        content.replace(content.find(";"), sizeof(";") - 1, ",");
      }

      if (author == "Achievement") {
        achievementMessage(content);
        player.blackBerryCake.count++;
        player.blackBerryCake.totalCount++;
        sleep(1);
        continue;
      }
      showDialogue(author, content);
    }
    player.cakeEventEnd.occured = true;
  }

  void vivianCakeEvent(Player &player)
  {
    if(!player.cakeEventStart.occured)
    { 
      vivianCakeEvent1(player);
      player.cakeEventStart.occured = true;
      player.railwayStationUnlock.occured = true;
    }
    if(player.cakeEventStart.occured && player.cakeEventMid.occured)
    {
      vivianCakeEvent3(player);
    }
  }
};

class Gamble {
private:
  float gambleAtRisk(float money, int riskLevel) {
    const int riskFactor[3] = {22000, 54000, 111000};
    float x = (rand() % riskFactor[riskLevel]);
    float profit;
    profit = ((x / (100000)) * money);
    return profit;
  }

public:
  int chooseGameMode() {
    string gamemode;
    char res[2] = {'a', '\0'};
    cout << "Choose Risk Level: " << endl
         << "a) low risk (0 - 22% returns)\nb) medium risk (0 - 54% "
            "returns)\nc) high risk (0 - 110% returns)\n>> ";
    cin >> res[0];
    if (tolower(res[0]) == 'a') {
      return 0;
    } else if (tolower(res[0]) == 'b') {
      return 1;
    } else if (tolower(res[0]) == 'c') {
      return 2;
    }
    return 1;
  }
  int gamble(float gambleAmount, int gamemode) {
    if (gamemode < 0 || gamemode > 2) {
      gamemode = 1;
    }
    return gambleAtRisk(gambleAmount, gamemode);
  }
};

class Mine {
public:
  int mineLevels[MAX_MINE_LEVELS] = {0,   55,   127,  377,  695,  889,
                                     780, 1001, 2350, 3978, 5112, 7500};

  void getMineLevel(Player &player) {
    for (int i = 0; i < MAX_MINE_LEVELS; i++) {
      if (player.timesMined == mineLevels[i]) {
        cout << "You are at mine level " << i << "." << endl;
      }
    }

    if (player.timesMined > 45 && !player.guildUnlocked.occured &&
        player.xp > 150) {
      achievementMessage("Guild unlocked");
      sleep(1);
      cout << "You have unlocked pickaxes! Speed up your mining by purchasing "
              "them in the guild. Go to main menu to checkout the guild."
           << endl;
      sleep(2);
      player.guildUnlocked.occured = true;
    }

    switch (player.timesMined) {
    case 1:
      achievementMessage("This might take a while...");
      break;
    case 3:
      achievementMessage("The items you mine would be stored in your inventory...");
      sleep(1);
      achievementMessage( "click 'i' on the prompt menu to access it.");
      player.inventoryUnlock.occured = true;
      break;
    case 6:
      achievementMessage("Mining takes so long...");
      sleep(1);
      achievementMessage("If only there was a way to speed things up...");
      break;
    case 9:
      achievementMessage("To get details about your position in the mine, enter 'd' into the terminal when in the mine.");
      player.mineDetailsUnlock.occured = true;
      break;
    case 10:
      achievementMessage("You can quit the mine by entering 'q'.");
      player.quitMineUnlock.occured = true;
      break;
    case 15:
      if (!player.sellerMarketBoot.occured) {
        showMessage("You can sell the items you mine in the seller's market.");
        achievementMessage("Seller's Market Unlocked");
        char res;
        while (res != 's') {
          res = getPlayerResponse("Click 's' to enter seller's market.");
        }
        Events event;
        event.sellerMarketBoot(player);

        cout << "Back to mine..." << endl;
      }
      // seller's market cutscene
      break;
    }
  }

  int getMineLevelAsInt(Player &player) {
    int currentMineLevel = 0;
    for (int i = 0; i < MAX_MINE_LEVELS - 1; i++) {
      if (player.timesMined < mineLevels[i]) {
        currentMineLevel = i - 1;
        break;
      }
      if (i == MAX_MINE_LEVELS - 2 && player.timesMined >= mineLevels[i]) {
        currentMineLevel = i;
      }
    }
    if (player.timesMined >= mineLevels[MAX_MINE_LEVELS - 1]) {
      currentMineLevel = MAX_MINE_LEVELS - 1;
    }

    return currentMineLevel;
  }

  void display(Player &player) {
    int currentMineLevel = getMineLevelAsInt(player);
    int minesLeft;
    int nextLevel = currentMineLevel + 1 < MAX_MINE_LEVELS
                        ? currentMineLevel + 1
                        : currentMineLevel;
    minesLeft = mineLevels[nextLevel] - player.timesMined;
    minesLeft = minesLeft == 0 ? mineLevels[currentMineLevel + 1] : minesLeft;
    cout << "Times Mined: " << player.timesMined << endl;
    cout << "Current Mine Level: " << currentMineLevel << endl;
    if (minesLeft >= 0) {
      cout << "Mines left to reach next mine level: " << minesLeft << endl;
    } else {
      cout << "Mines left to reach next mine level: " << "???" << endl;
    }
  }

  void getMineableCount(Player player, int mineableCount[]) {
    int mineLevel = getMineLevelAsInt(player);
    mineableCount[0] = 0;
    switch (mineLevel) {
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
    return;
  }

  vector<item *> getMineable(Player &player) {
    int mineLevel = getMineLevelAsInt(player);
    vector<item *> mineable;
    int mineableCount[2] = {
        0, 3}; //                         0    1      2    3      4       5 6 7
               //                         8       9       10      11      12 13
    vector<item *> items =
        player
            .getMineItemsByAddress(); // vector<item> items = {dirt, rock, wood,
                                      // coal, granite, iron, copper, silver,
                                      // tin,   hardRock, gold, diamond, ruby,
                                      // blackStone, magma, bedrock};
                                      // vector<item*> items = {&dirt, &rock,
                                      // &wood, &coal, &granite, &iron, &copper,
                                      // &silver, &tin, &hardRock, &gold,
                                      // &diamond, &ruby, &blackStone, &magma,
                                      // &bedrock};
    player.caluclateWeights(items);
    getMineableCount(player, mineableCount);

    for (int i = 0, j = mineableCount[0]; i < mineableCount[1]; i++, j++) {
      mineable.push_back(items[j]);
    }

    return mineable;
  }

  void mine(Player &player) {
    int mineableCount[2];
    getMineableCount(player, mineableCount);

    vector<item *> mineable =
        getMineable(player); // and caluclate item weights;

    float totalWeight = 0;
    for (int i = 0; i < mineableCount[1]; i++) {
      totalWeight += mineable[i]->weight;
    }

    int itemRepeatCount = player.dualItems.occured ? randInt(2, 3) : 1;
    cout << "You got: " << endl;

    for (int i = 0; i < itemRepeatCount; i++) {
      float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                     totalWeight;
      item *selecteditem;

      float accWeight = 0;
      for (int i = 0; i < mineableCount[1]; i++) {
        accWeight += mineable[i]->weight;
        if (random < accWeight) {
          selecteditem = mineable[i];
          break;
        }
        random -= mineable[i]->weight;
      }
      int itemCountByLevel = 7;
      int count = (randInt(1, itemCountByLevel) * selecteditem->rareity) + 1;

      cout << "\t" << count << " pieces of " << selecteditem->name << endl;
      
      if(selecteditem->totalCount == 0)
      {
            ostringstream message;
            message << "You unlocked - " << selecteditem->name;
            achievementMessage(message.str());
      }

      player.incrementItemCount(selecteditem->name, count);
      player.addXP(selecteditem->xp);

      auto it = find(mineable.begin(), mineable.end(), selecteditem);
      if (it != mineable.end()) {
        mineable.erase(it);
        // Recalculate total weight after removal
        totalWeight = 0;
        for (auto &itemPtr : mineable) {
          totalWeight += itemPtr->weight;
        }
      }
    }
  }

  void enter(Player &player) {

    cout << "entering mine..." << endl;
    if (player.firstBoot.occured) {
      getMineLevel(player);
    } else {
      cout << "It's dark. You are now in a mine. Enter 'm' to mine it..."
           << endl;
    }
    char res = 'a';
    while (true) {
      cout << ">> ";
      cin >> res;
      if (res == 'd' && player.mineDetailsUnlock.occured) {
        display(player);
        continue;
      }
      if (res == 'i' && player.inventoryUnlock.occured) {
        player.displayInventory();
        continue;
      }
      if (res == 'q' && player.quitMineUnlock.occured) {
        break;
      }
      if (res == 'p')
      {
        player.display();
      }
      if (res != 'm') {
        continue;
      }
      cout << "mining..." << endl;
      player.timesMined++;
      getMineLevel(player);
      sleep(player.pickaxe.waitTimeByLevel[player.pickaxe.level]);
      mine(player);
      // mining logic
    }
    cout << "exiting mine..." << endl;
  }
};

class Guild {
public:
  void initializePickaxe(Player &player) {
    // item pickaxe = player.pickaxe;
    int pickLevel = player.pickaxe.level;
    // item requiredForUpGrade[5][2] =

    switch (pickLevel) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      player.pickaxe.required[0][0] = player.rock;
      player.pickaxe.requiredCount[0][0] = 25;
      player.pickaxe.required[0][1] = player.wood;
      player.pickaxe.requiredCount[0][1] = 55;

      player.pickaxe.required[1][0] = player.granite;
      player.pickaxe.requiredCount[1][0] = 35;
      player.pickaxe.required[1][1] = player.wood;
      player.pickaxe.requiredCount[1][1] = 175;

      player.pickaxe.required[2][0] = player.copper;
      player.pickaxe.requiredCount[2][0] = 85;
      player.pickaxe.required[2][1] = player.tin;
      player.pickaxe.requiredCount[2][1] = 85;

      player.pickaxe.required[3][0] = player.silver;
      player.pickaxe.requiredCount[3][0] = 125;
      player.pickaxe.required[3][1] = player.gold;
      player.pickaxe.requiredCount[3][1] = 100;

      player.pickaxe.required[4][0] = player.diamond;
      player.pickaxe.requiredCount[4][0] = 250;
      player.pickaxe.required[4][1] = player.ruby;
      player.pickaxe.requiredCount[4][1] = 20;

    default:
      break;
    }
  }

  void upgradePickaxe(Player &player) {
    initializePickaxe(player);
    cout << "Entering pickaxe store..." << endl;
    cout << "\n\n";
    int level = player.pickaxe.level;
    string FinalMessage;
    if (level == 0) {
      cout << "Pickaxe" << endl;
      cout << "Description: The one and only mining tool you need!" << endl;
      cout << "Cost: " << endl;

      FinalMessage = "Buy Pickaxe? [y/n]";
    } else {
      cout << "Upgrade your pickaxe now!!!" << endl;
      cout << "Current pickaxe level: " << player.pickaxe.level
           << "\nPickaxe Level after upgrade: " << player.pickaxe.level + 1
           << endl;
      FinalMessage = "Buy Upgrade? [y/n]";
    }
    cout << moneyAsString(player.pickaxe.upgradeCost[level]) << endl;
    for (int i = 0; i < 2; i++) {
      cout << player.pickaxe.requiredCount[level][i] << " units of "
           << player.pickaxe.required[level][i].name << endl;
    }

    char res;

    while (true) {
      res = getPlayerResponse(FinalMessage);
      if (res == 'y') {
        bool insufficient = false;
        for (int i = 0; i < 2; i++) {
          if (player.wallet < player.pickaxe.upgradeCost[level] &&
              player.bankBalance < player.pickaxe.upgradeCost[level]) {
            achievementMessage("Insufficient Funds!");
          }
          if (player.pickaxe.requiredCount[level][i] >
              player.pickaxe.required[level][i].count) {
            achievementMessage("Insufficient Materials please come back when "
                               "you have enough resources!");
            cout << "Required: "
                 << player.pickaxe.requiredCount[level][i] -
                        player.pickaxe.required[level][i].count
                 << " more units of " << player.pickaxe.required[level][i].name
                 << ". Get collecting!" << endl;
            sleep(2);

            insufficient = true;
          }
        }

        if (insufficient) {
          return;
        }

        // player.wallet -= player.pickaxe.upgradeCost[level];
        // cout << "\t - $" << moneyAsString(player.pickaxe.upgradeCost[level])

        if (player.withdrawFromWallet(player.pickaxe.upgradeCost[level])) {
          for (int i = 0; i < 2; i++) {
            player.pickaxe.required[level][i].count -=
                player.pickaxe.requiredCount[level][i];
          }
          player.addXP(player.pickaxe.upgradeXP[player.pickaxe.level]);
          player.pickaxe.level++;
        }
        cout << "\tPurchase Successful! Keep mining!" << endl;
        sleep(2);
        break;
      } else if (res == 'n') {
        return;
      }
    }
  }

  void enter(Player &player) {
    char res;
    while (true) {

      res = getPlayerResponse("p) Pickaxe\nq) Quit Guild");
      if (res == 'p') {
        upgradePickaxe(player);
        break;
      } else if (res == 'q') {
        return;
      }
    }
  }
};

class Market {
public:
  double basePrice = 0.25;
  double priceMultiplyer = 10.0;

  vector<item *> setPrices(vector<item *> items, int multiplier = 1) {
    for (int i = 0; i < items.size(); i++) {
      items[i]->sellPrice = items[i]->buyPrice;
      items[i]->sellPrice *=
          (basePrice * pow(priceMultiplyer, 1 - items[i]->rareity) *
           multiplier);
    }
    return items;
  }

  // void resetPrices(vector<item*> items, int multiplier = 1)
  // {
  //     for(int i = 0; i < items.size(); i++)
  //     {
  //         items[i]->sellPrice /= (basePrice * pow(priceMultiplyer, 1 -
  //         items[i]->rareity) * multiplier);
  //     }
  //     return;
  // }

  void menu(Player &player) {
    if (!player.sellerMarketBoot.occured) {
      achievementMessage("Seller's Market Unlocked");
      Events event;
      event.sellerMarketBoot(player);

      return;
    }

    // if (!player.bankBoot.occured) {
    //   achievementMessage(
    //       "You do not have a bank account to recieve money to. Go to bank!");
    //   sleep(2);
    //   cout << "exiting market..." << endl;
    //   sleep(1);
    //   return;
    // }

    basePrice *= player.luck;
    priceMultiplyer *= player.luck;
    cout << "You have entered the market... buckle up!" << endl;
    sleep(1);
    showDialogue(Manjunath.name, getDialogue(Manjunath), 1);
    //  showMessage(getDialogue(Manjunath), "", 2, Manjunath.name);
    if(player.level < 2)
    {
      cout << "s) Sell\nq) Quit market";
    } else {
      cout << "s) Sell\nb) Buy\nq) Quit market";
    }
    char res = getPlayerResponse();

    if (res == 's') {
      FirstTimeSell:
      while (true) {
        sell(player);

        char r;
        cout << "Continue Selling? (y/n)\n>> ";
        cin >> r;

        if (r == 'n') {
          break;
        }
      }

    } else if (res == 'b' && player.level > 1) {
      buy(player);
    }
  }
  void sell(Player &player) {
    // vector<item*> activeItems = player.getActiveMineItems(); //
    // cout << "active items recieved to sell fn" << endl;

    vector<item *> items = setPrices(player.getActiveMineItems());

    if (items.size() > 0) {
      float totalCost = 0;
      for (int i = 0; i < items.size(); i++) {
        if (items[i]->count != 0) {
          totalCost += (items[i]->count * items[i]->sellPrice);
        }
      }

      int i;
      for (i = 0; i < items.size(); i++) {
        cout << i + 1 << ") " << items[i]->name << ": $" << items[i]->sellPrice
             << " per unit \t|\t You have: " << items[i]->count << "." << endl;
      }
      cout << i + 1 << ") " << "SELL ALL: $" << moneyAsString(totalCost)
           << "\t\t|\t + 2% bonus." << endl;

      if(player.sellerMarketBoot.occured)
      {
      cout << "0) Quit" << endl;
      }
      int res;
      do {
        //res = getSpecificPlayerResponse("Sell Item by index", 0, items.size());
        cout << "Sell Item by index >> ";
        cin >> res;
        if (res == 0) {
          return;
        }
      } while (res - 1 > items.size() || res < 0);

      res--;

      if (res == items.size()) {
        char confirm;
        cout << "You are about to sell all your items, this cannot be undone. "
                "Confirm? (y): ";
        confirm = getPlayerResponse();

        if (confirm == 'y') {
          cout << "Selling all items..." << endl;
          sleep(1);

          if (player.depositToWallet(totalCost + (0.02 * totalCost))) {
            for (int i = 0; i < items.size(); i++) {
              items[i]->count = 0;
            }
            // cout << "Business sucessful!\n\t+ "
            //      << moneyAsString(totalCost + (0.05 * totalCost))
            //      << "$.\tKa-ching!" << endl;
          }

          sleep(1);
        }
      } else {

        for (i = 0; i < items.size(); i++) {
          if (items[i] == items[res]) {
            cout << "You have: [" << items[res]->name << " - "
                 << items[res]->count << "] - Sell price: [$"
                 << moneyAsString(items[res]->sellPrice) << "] per unit."
                 << " (Max profit: ["
                 << moneyAsString(items[res]->sellPrice * items[res]->count)
                 << "])" << endl;

            int countSelling;
           do {
              cout << "Enter Quantity >> ";
              cin >> countSelling;

              //countSelling = getSpecificPlayerResponse("Enter Quantity", 0, items[res]->count - 1);

           } while (isdigit(res) && countSelling < 0 || countSelling > items[res]->count);

            cout << "selling..." << endl;
            if (player.depositToWallet(items[res]->sellPrice * countSelling)) {
              items[res]->count -= countSelling;
              // cout << "Business sucessful!\n\t+ "
              //     << moneyAsString(items[res]->sellPrice * countSelling)
              //     << "$.\tKa-ching!" << endl;
            }
            sleep(1);
          }
        }
      }

      // resetPrices(items);
      return;

    } else {
      achievementMessage("You have nothing to sell. Try mining for resources.");
      // resetPrices(items);
    }
  }
  void buy(Player &player) {
    Mine mine;
    int sellerInflation = randInt(2, 6);
    vector<item *> mineable =
        setPrices(mine.getMineable(player), sellerInflation);

    if (mineable.size() <= 0) {
      achievementMessage("You have nothing to buy right now. Go mine for some "
                         "resources to unlock buying market.");
      sleep(3);
      return;
    }
    int j = 0;
    for (int i = 0, j = 0; i < mineable.size(); i++) {
      if (mineable[i]->totalCount > 0) {
        cout << j + 1 << ") " << mineable[i]->name << ": $"
             << moneyAsString(mineable[i]->sellPrice) << " per unit" << endl;
        j++;
      };
    }

    cout << "0) Quit" << endl;
    int res;
    do {
      cout << "Buy Item by index >> ";
      cin >> res;
    } while (isdigit(res) && (res > mineable.size() || res < 0));

    // res = getSpecificPlayerResponse("Buy item by index", 1, mineable.size() - 1);

    res--;

    if (res == -1) {
      return;
    }

    for (int i = 0; i < mineable.size(); i++) {
      if (mineable[i] == mineable[res]) {
        cout << "Your wallet balance: $" << moneyAsString(player.wallet)
             << endl;
        int countSelling;
        do {
          cout << "Enter Quantity >> ";
          cin >> countSelling;

          //countSelling = getSpecificPlayerResponse("Enter Quantity", 1, 1000);

        } while (isdigit(res) && countSelling * mineable[i]->sellPrice > player.wallet);

        cout << "Buying..." << endl;
        sleep(2);
        if (player.withdrawFromWallet(mineable[res]->sellPrice *
                                      countSelling)) {
          mineable[res]->count += countSelling;
        }
        sleep(1);
      }
    }
  }
};

void marketBootCutscene(Player &player)
{
  string name = Manjunath.name;
    sleep(1);
    showMessage("[Puffs out smoke]", "*cough* *cough*", 2, name);
    sleep(2);
    showMessage("Ahoy there, what do we have here...",
                "Looks like a miner, by the outfit, I suppose", 2, name);
    sleep(2);
    showMessage("[Laughs at his own joke]",
                "You know, I really ought to look forward to this", 2, name);
    sleep(2);
    showMessage(
        "My knees have given up on me",
        "I can no longer go up those cave no more, mine them diamonds...", 3,
        name);
    sleep(2);
    showMessage("But alas, you, young soul, can do it!",
                "Better than me, I suppose, ha ha ha", 2, name);
    sleep(2);
    showMessage(
        "And I'll do you one better, why not...",
        "You can always come to me and I would buy your findings from the mine",
        3, name);
    sleep(2);
    showMessage("For a reasonable cost, ofcourse!",
                "Have you got something to sell me?",
                2, name);
    sleep(2);
    achievementMessage("Selling Unlocked");
    achievementMessage("Bank Unlocked");

    //TODO: add first sell.
    Market market;
    market.sell(player);
    sleep(2);
    showMessage("That's good business with you", "", 1, name);
    showMessage("you could come by do do this more, or just show up to have a conversation...",
                "This not-so-old man can really do with some companionship...",
                2, name);
    sleep(2);
    showMessage("exiting market...");
    sleep(3);
}

class Bank {
public:
  long double bankBalance;

  void bankBoot(Player &player) {
    cout << "Welcome to the city bank!" << endl;
    sleep(1);
    Events event;
    event.bankBoot(player);
  }

  void withdraw(Player &player) {
    float withdrawAmount;
    string content =
        randInt(0, 100) % 2 == 0
            ? "Ah! I see, $player_name, how much do you want to withdraw to "
              "your wallet?"
            : "Looks like someone needs cash! Tell me how much you want to "
              "transfer to your wallet, $player_name...";
    showDialogue(Vivian.name,
                 content.replace(content.find("$player_name"),
                                 sizeof("$player_name") - 1, player.name),
                 0);
    cout << "Current bank balance: "
         << moneyAsString(player.bankBalance, 2, "$") << endl;
    while (true) {
      cout << ">> ";
      cin >> withdrawAmount;
      if (withdrawAmount == 0) {
        return;
      }
      if (withdrawAmount <= player.bankBalance &&
          withdrawAmount <= player.walletLimit) {
        cout << "Transferring funds..." << endl;
        sleep(1);
        player.bankBalance -= withdrawAmount;
        player.wallet += withdrawAmount;
        cout << moneyAsString(withdrawAmount, 2, "$")
             << " transferred to your personal wallet!" << endl;
        sleep(2);
        break;
      }
      if (withdrawAmount > player.bankBalance) {
        cout << "Insufficient balance. Try again! (Enter 0 to quit)" << endl;
        continue;
      }
      if (withdrawAmount > player.walletLimit) {
        cout << "Wallet limit exceed."
             << " (Current limit: " << player.walletLimit
             << ") Upgrade wallet or buy credit card. Try again with different "
                "amount."
             << endl;
      }
    }
  }

  void deposit(Player &player) {
    float depositAmount;
    string content =
        randInt(0, 100) % 2 == 0
            ? "Ah! I see, $player_name, how much do you want to withdraw to "
              "your wallet?"
            : "Looks like someone needs cash! Tell me how much you want to "
              "transfer to your wallet, $player_name...";
    showDialogue(Vivian.name,
                 content.replace(content.find("$player_name"),
                                 sizeof("$player_name") - 1, player.name),
                 0);
    cout << "Current wallet balance: " << moneyAsString(player.wallet, 2, "$")
         << endl;
    while (true) {
      cout << ">> ";
      cin >> depositAmount;
      if (depositAmount == 0) {
        return;
      }
      if (depositAmount - 0.01 <= player.wallet) {
        cout << "Transferring funds..." << endl;
        sleep(1);
        player.bankBalance += depositAmount;
        player.wallet -= depositAmount;
        cout << moneyAsString(depositAmount, 2, "$")
             << " transferred to your bank account!" << endl;
        sleep(2);
        break;
      }
      if (depositAmount > player.wallet) {
        cout << "Insufficient balance in your wallet. Try again! (Enter 0 to "
                "quit)"
             << endl;
        continue;
      }
    }
  }

  void display(Player &player) {
    cout << "Bank Holder Name: " << player.name << endl
         << "Bank Balance: " << moneyAsString(player.bankBalance, 2, "$")
         << endl
         << "Wallet: " << moneyAsString(player.wallet, 2, "$") << endl
         << "Current Wallet Limit " << moneyAsString(player.walletLimit, 2, "$")
         << endl;

    sleep(3);
  }

  void upgradeWallet(Player &player) {
    float currentLimit = player.walletLimit;
    int limitLevel;

    vector<int> upgrades = {300, 1000, 2000, 3000, 5000, 7500};
    vector<int> upgradeCost = {0, 200, 750, 1250, 1750, 3500};

    int i = 0;
    for (auto t : upgrades) {
      if (t == currentLimit) {
        limitLevel = i;
      }
      i++;
    }

    cout << "WALLET UPGRADE" << endl;
    cout << "Current limit: " << moneyAsString(player.walletLimit, 2, "$")
         << endl;
    cout << "Limit after upgrade: "
         << moneyAsString(upgrades[limitLevel + 1], 2, "$") << endl;
    cout << "Cost of upgrade: "
         << moneyAsString(upgradeCost[limitLevel + 1], 2, "$") << endl;
    sleep(1);
    char res = getSpecificPlayerResponse("Upgrade wallet? (y/n)", 'y', 'n');
    if (res == 'y') {
      res = getSpecificPlayerResponse(
          "Pay using:\nb) Bank Balance\nw) Wallet Balance\n", 'b', 'w');
      switch (res) {
      case 'b':
      payWithBank:
        if (player.bankBalance >= upgradeCost[limitLevel + 1]) {
          player.bankBalance -= upgradeCost[limitLevel + 1];
          cout << "\t- " << moneyAsString(upgradeCost[limitLevel + 1], 2, "$")
               << "\t womp-womp!" << endl;
          player.walletLimit = upgrades[limitLevel + 1];
          sleep(1);
          cout << "Wallet upgrade succesful! Cheers!" << endl;
          sleep(2);
        } else {
          cout << "Insufficient balance. Abort." << endl;
          sleep(2);
        }
        break;
      case 'w':
        if (player.wallet >= upgradeCost[limitLevel + 1]) {
          player.wallet -= upgradeCost[limitLevel + 1];
          player.walletLimit = upgrades[limitLevel + 1];
          cout << "\t- " << moneyAsString(upgradeCost[limitLevel + 1], 2, "$")
               << "\t womp-womp!" << endl;
          sleep(1);
          cout << "Wallet upgrade succesful! Cheers!" << endl;
          sleep(2);

        } else {
          cout << "Insufficient balance. Try paying with bank or make some "
                  "money!"
               << endl;
          sleep(1);
          cout << "paying with bank..." << endl;
          sleep(2);
          goto payWithBank;
        }
        break;
      }
    }
  }

  void initiateCreditCard(Player &player)
  {
    cout << "CREDIT CARD:" << endl;
    cout << "Benifits: " << endl;
    cout << " - Access your bank cash at all times in the times your wallet balance isn't enough\n - Can both recieve and send money!\n - T/C 5\% convinience fee per transaction applied." << endl;
    cout << "Cost: " << "$5000" << endl;
    char res = getSpecificPlayerResponse("Buy credit card? (y/n)", 'y', 'n');
    if (res == 'y')
    {
      if(player.bankBalance < 5000 && player.wallet < 5000)
      {
        achievementMessage("Insufficient balance!");
        return;
      } else {
        if(player.bankBalance >= 5000)
        {
          player.bankBalance -= 5000;
          cout << " - $5000" << "\thappy purchasing!" << endl;
        } else {
          player.withdrawFromWallet(5000);
        }
      }
    } else {
      cout << "We are sorry to see you not want our plans. We hope you change your mind again in the future!" << endl;
      sleep(1);
    } 
  }

  void enter(Player &player) {

    if((player.bankBoot.occured && player.guildUnlocked.occured && (player.bankBalance >= 1000 || player.wallet >= 1000) && !player.railwayStationUnlock.occured) || player.cakeEventStart.occured && player.cakeEventMid.occured && !player.cakeEventEnd.occured)
    {
      //TODO
      Events event;
      event.vivianCakeEvent(player);
      return;
    }

    if (!player.bankBoot.occured && player.wallet >= 200) {
      bankBoot(player);
      
      return;
    } else if (!player.bankBoot.occured && player.wallet < 200)
    {
      achievementMessage("You are not elidgible for a bank account yet! Have atleast $200 in your wallet to unlock bank");
      return;
    }
    cout << "Welcome to the city bank!" << endl;
    bankBalance = player.bankBalance;

    sleep(1);
    int x = randInt(0, 100);

    if (x <= 15) {
      player.bankOnLunchBreak.occured = true;
      player.bankOnLunchBreak.timesOccured++;
    }

    if (player.bankOnLunchBreak.occured) {
      achievementMessage("The bank is on a lunch break. Come back in a while!");

    } else {

      // showMessage(getDialogue(Vivian), "", 2, Vivian.name);
      showDialogue(Vivian.name, getDialogue(Vivian));

      vector<string> menu = {"a) Withdraw Amount",   "b) Deposit Amount",
                             "c) Check Balance",     "d) Upgrade Wallet Limit",
                             "e) Credit Card Plans", "f) Insurance & Loans",
                             "q) quit bank"};

      while (true) {
        for (int i = 0; i < menu.size(); i++) {
          cout << menu[i] << endl;
        }

        char res;
        res = getPlayerResponse("Choose Bank Action");

        switch (res) {
        case 'a':
          withdraw(player);
          break;

        case 'b':
          deposit(player);
          break;

        case 'c':
          display(player);
          break;

        case 'd':
          upgradeWallet(player);
          break;

          case 'e':
          initiateCreditCard(player);
          break;

          // case 'f':
          // insuranceInit();
          // break;

        case 'q':
          goto quitBank;
        }

        // if (res == 'a') {
        //   cout << "Name: " << player.name << endl;
        //   cout << "Bank Balance: $" << moneyAsString(player.bankBalance)
        //        << endl;
        // }
        // if (res == 'b') {
        //   if (!player.loansUnlocked.occured) {
        //     achievementMessage("You are not eligible for bank loans as of
        //     now");
        //   }
        // }
        // if (res == 'q') {
        //   goto quitBank;
        // }
        // cout << "Back to main screen (b)\nQuit (q)\n>> ";
        // cin >> res;
        // if (res == 'q') {
        //   goto quitBank;
        // } else if (res != 'b') {
        //   break;
        // }

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

class RailwayStation {
public:
  struct train {
    string name;
    string trainType;
    float ticketPrice;
    city home;
    city destination;
    int platform;
    int waitTime;
    int travelTime;
    string code;
    string announcement;
  };

  struct platform {
    int platformNo;
    int nextTrainArrivalTime;
  };

  struct ticket {
    train Train;
  };

  bool reached{false};

  // class Platform{};
  vector<train> allTrains;

  platform p1{1}, p2{2}, p3{3}, p4{4}, p5{5}, p6{6};

  vector<platform> platforms = {p1, p2, p3, p4, p5, p6};

  // User's Ticket:
  bool ticketPurchased{false};
  ticket UserTicket;
  int platformEnterTime = 5;
  int maxTime = 55;

  // Currently there is a bug where when travelling between cities back to back
  // in a triangle, regardless of what, on the third city, once you reach it's
  // impossible to come back to railway station and can't buy ticket. solve it
  // #TODO

  void init() {
    allTrains.clear();
    // vector<city> ALL_CITIES = {Terminille, SyntaxCity, Codeopolis};

    vector<string> trainTypes = {"Passenger", "Express", "Bullet"};
    // vector<string> cityCodes = {"TRL", "SYC", "CPS"};

    for (int i = 0; i < ALL_CITIES.size(); i++) {
      for (int j = 0; j < ALL_CITIES.size(); j++) {
        if (i != j) {

          for (int k = 0; k < trainTypes.size(); k++) {

            int waitTime;
            int TravelTime;
            waitTime = randInt(2, 22);
            string trainNo;
            int price;
            string trainName;

            vector<string> trnnm;
            vector<string> cd;

            if (trainTypes[k] == "Passenger") {
              trnnm = {"Bitliner", "Looper"};
              cd = {"BTL", "LPR"};
              int rnd = randInt(0, trnnm.size() - 1);
              trainName = trnnm[rnd];
              TravelTime = randInt(41, 100);
              trainNo = (randInt(0, 100) % 2 == 0)
                            ? ALL_CITIES[j].code + cd[rnd]
                            : cd[rnd] + ALL_CITIES[j].code;
              price = randInt(4, 8);
            } else if (trainTypes[k] == "Express") {
              trnnm = {"Express", "Superfast", "Non-stop"};
              cd = {"EXP", "SPF", "NSX"};
              int rnd = randInt(0, trnnm.size() - 1);
              trainName = (randInt(0, 100) % 2 == 0)
                              ? trnnm[rnd] + " " + ALL_CITIES[j].name
                              : ALL_CITIES[j].name + " " + trnnm[rnd];
              TravelTime = randInt(25, 41);
              trainNo = (randInt(0, 100) % 2 == 0)
                            ? ALL_CITIES[j].code + cd[rnd]
                            : cd[rnd] + ALL_CITIES[j].code;
              price = randInt(22, 38);
            } else if (trainTypes[k] == "Bullet") {
              trnnm = {"BulletX", "Swifter"};
              cd = {"CDB", "SWF", "BLT"};
              int rnd = randInt(0, trnnm.size() - 1);
              trainName = (randInt(0, 100) % 2 == 0)
                              ? trnnm[rnd] + " " + ALL_CITIES[j].name
                              : ALL_CITIES[j].name + " " + trnnm[rnd];
              TravelTime = randInt(4, 12);
              trainNo = (randInt(0, 100) % 2 == 0)
                            ? ALL_CITIES[j].code + cd[rnd]
                            : cd[rnd] + ALL_CITIES[j].code;
              price = randInt(179, 300);
            }

            int platformNo;
            platform bufferplatform;
            do {
              platformNo = randInt(1, ALL_CITIES[i].platformCount);
              bufferplatform.platformNo = platformNo;
              bufferplatform.nextTrainArrivalTime = waitTime;
            } while (platforms[platformNo - 1].nextTrainArrivalTime ==
                     bufferplatform.nextTrainArrivalTime);
            platforms[platformNo - 1].nextTrainArrivalTime = waitTime;
            
            train train = {trainName,     trainTypes[k],
                           (float)price,  ALL_CITIES[i],
                           ALL_CITIES[j], platforms[platformNo - 1].platformNo,
                           waitTime,      TravelTime,
                           trainNo};
            allTrains.push_back(train);
          }
        }
      }
    }
  }

  vector<train> getAvailableTrains(Player &player) {

    vector<train> trains = allTrains;
    vector<train> availableTrains;

    // losing my lamda function virginity with this one boys...
    sort(trains.begin(), trains.end(),
         [](train a, train b) -> bool { return a.waitTime < b.waitTime; });

    cout << "TRAIN SCHEDULE: " << endl;

    cout << left << setw(8) << "Sn No." << setw(14) << "Train No." << setw(24)
         << "Train Name:" << setw(20) << "Train Type:" << setw(16)
         << "From:" << setw(16) << "Destination:" << setw(16) << "Arrival in"
         << setw(18) << "Travel Duration" << setw(16) << "Platform no."
         << setw(16) << "Ticket Price:" << endl;

    int noOfTrains = trains.size();
    for (int i = 0, j = 0; i < noOfTrains; i++) {
      if (trains[i].home.name == player.currentCity.name) {
        cout << left << setw(8) << j + 1 << setw(14) << trains[i].code
             << setw(24) << trains[i].name << setw(20) << trains[i].trainType
             << setw(16) << trains[i].home.name << setw(16)
             << trains[i].destination.name << setw(16) << trains[i].waitTime
             << setw(18) << trains[i].travelTime << setw(16)
             << trains[i].platform << setw(16)
             << moneyAsString(trains[i].ticketPrice, 2, "$") << endl;

        availableTrains.push_back(trains[i]);
        j++;
      }
    }
    sleep(1);
    return availableTrains;
  }

  void printTicket(ticket tx, Player &player) {
    cout << "---------------------------------------" << endl;
    cout << left << setw(25) << "TICKET NUMBER:" << toUpperCase(tx.Train.code)
         << "_" << randInt(1, 150) << endl;
    cout << left << setw(25) << "TRAIN NAME:" << toUpperCase(tx.Train.name)
         << endl;
    cout << left << setw(25) << "SOURCE:" << toUpperCase(tx.Train.home.name)
         << endl;
    cout << left << setw(25)
         << "DESTINATION:" << toUpperCase(tx.Train.destination.name) << endl;
    cout << left << setw(25) << "PASSENGER:" << toUpperCase(player.name)
         << endl;
    cout << left << setw(25)
         << "TICKET PRICE:" << moneyAsString(tx.Train.ticketPrice, 2, "$")
         << " [PAID]" << endl;
    cout << left << setw(25) << "DEPARTURE:" << tx.Train.waitTime << " seconds"
         << endl;
    cout << left << setw(25) << "TRAVEL DURATION:" << tx.Train.travelTime
         << " seconds" << endl;
    cout << left << setw(25) << "PLATFORM NO:" << tx.Train.platform << endl;
    cout << "---------------------------------------" << endl;
  }

  void ticketCounter(Player &player) {
    cout << "Welcome to " << player.currentCity.name << " Railway Station!"
         << endl;

    // int random = randInt(1,100);
    // if(random < 15)
    // {
    //     cout << "No trains at this moment." << endl;
    //     return;
    // }

    vector<train> trains = getAvailableTrains(player);

    int response{0};
    while (true) {
      // cout << trains.size();

      cout << "Purchase train ticket by index (0 to quit) >> ";
      cin >> response;

      if (response <= trains.size() && response > -1) {
        break;
      }
    }

    if (response == 0) {
      ticketPurchased = false;
      return;
    }

    ticket tx{trains[response - 1]};

    if (player.wallet < tx.Train.ticketPrice &&
        player.bankBalance < tx.Train.ticketPrice) {
      achievementMessage("Insufficinet balance! Purchase unsucessful");
      ticketPurchased = false;
      return;
    }

    if (player.withdrawFromWallet(tx.Train.ticketPrice)) {
      achievementMessage("Ticket Purchase Successful!");
      ticketPurchased = true;
      UserTicket = tx;
      sleep(1);
      printTicket(tx, player);
    };

    sleep(2);
  }

  void boardTrain(Player &player, ticket tx) {
    cout << "Boarding Train..." << endl;
    sleep(3);
    cout << "[Train starts]" << endl;
    sleep(1);
    cout << "[Train departs " << tx.Train.home.name << "]" << endl;
    int seconds = tx.Train.travelTime;

    // vector<string> travelMessages = {"Breeze feeling good...", "Watching
    // moving trees...", "Stretching legs...", "Leaning back the recliner...",
    // "Listening to music...", "Looking out the window...", "Rolling down the
    // AC..."};

    while (seconds >= 1) {
      // int rnd = randInt(0, travelMessages.size() - 1);
      cout << "\rDestination: " << tx.Train.destination.name << " in "
           << seconds << " seconds...     " << std::flush;
      sleep(1);
      seconds--;
    }
    cout << "\n[train halts]" << endl;
    sleep(1);
    ostringstream announcement;
    announcement << tx.Train.name << " arrived at platform "
                 << randInt(1, tx.Train.destination.platformCount) << "!";
    showDialogue(
        "ANNOUNCER",
        announcement.str()); // dynamic messages frfr should be done TODO!!!
    player.currentCity = tx.Train.destination;
    sleep(1);
    cout << "De-boarding train..." << endl;
    sleep(2);
    cout << "You have reached " << player.currentCity.name << "! Happy Journey!"
         << endl;
    sleep(1);

    // cout << "Welcome to " <<player.currentCity.name << "!" << endl;
    ticketPurchased = false;
    reached = true;
    sleep(2);

    int rand = randInt(0, 100);
    if(player.luck < 1 && rand < 20)
    {
      cout << "You have been pickpocketed!" << endl;
      float lost = player.wallet * (randInt(1, 45) / 100);
      player.wallet -= lost;
      cout << "You lost " << moneyAsString(lost, 2, "$") << "from your wallet! Stay safe!" << endl;  
    }
    return;
  }

  bool enterPlatform(Player &player, int platformNumber, ticket tx) {
    cout << "Entering platform " << platformNumber << "..." << endl;
    if (tx.Train.platform != platformNumber) {
      platformEnterTime = time(0);
      if (maxTime == 0) {
        maxTime = platformEnterTime + tx.Train.waitTime + 3;
      }
      cout << "[you are on the wrong platform]" << endl;
      cout << "[go to the platform before time runs out! you have "
           << maxTime - platformEnterTime << " seconds left!]" << endl;
      sleep(1);
      cout << ">> ";
      clearInputBuffer();
      cin.get();
      return false;
    }

    if (maxTime - platformEnterTime < 1) {
      cout << "Too late, you missed your train while being on the wrong "
              "platform!"
           << endl;
      platformEnterTime = 2;
      maxTime = 0;
      init();
      sleep(3);
      ticketPurchased = false;
      return false;
    }
    int countdown = tx.Train.waitTime; // countdown starting value

    while (countdown >= 1) {
      cout << "\rTrain Arriving in: " << countdown << " seconds" << std::flush;
      sleep(1);
      countdown--;
    }
    cout << endl << "[Train enters station]" << flush;
    sleep(1);
    cout << endl << "[Train halts]" << flush;
    sleep(1);
    ostringstream announcement;
    cout << endl;
    announcement << tx.Train.name << " has arrived on platform "
                 << tx.Train.platform << "!";
    showDialogue("ANNOUNCER", announcement.str());

    boardTrain(player, tx);
    return true;
  }

  void enter(Player &player) {
    reached = false;
    string message = player.currentCity.name + " Railway Station";
    transform(message.begin(), message.end(), message.begin(), ::toupper);
    cout << message << endl;

    sleep(1);
    while (true) {
      bool boarded = false;
      char res;
      if (ticketPurchased) {
        res = getPlayerResponse("t) ticket Counter\ne) Enter Platform\nv) View "
                                "Ticket\nq) Quit station");
      } else {
        res = getPlayerResponse(
            "t) ticket Counter\ne) Enter Platform\nq) Quit station");
      }

      if (!ticketPurchased && res == 't') {
        ticketCounter(player);
      } else if (ticketPurchased && res == 't') {
        cout << "You already purchased a ticket! click 'v' to view it" << endl;
      } else if (ticketPurchased && res == 'v') {
        printTicket(UserTicket, player);
      } else if (res == 'e' && ticketPurchased) {
        int platformNumber;
        showDialogue("Security guard", "There you go... get on the right "
                                       "platform! Don't miss your train...");
        while (true) {
          // cout << "1) Platform 1\n2) platform 2\n3) Platform 3\n0) Quit\n>>
          // ";

          for (int i = 0; i < player.currentCity.platformCount; i++) {
            cout << i + 1 << ") Platform " << i + 1 << endl;
          }
          cout << "0) Quit\n";
          do {
            cout << ">> ";
            cin >> platformNumber;
          } while (platformNumber > player.currentCity.platformCount);

          if (platformNumber == 0) {
            break;
          }
          boarded = enterPlatform(player, platformNumber, UserTicket);
          if (boarded) {
            return;
            break;
          }
        }
        if (boarded) {
          break;
        }
      } else if (res == 'e' && !ticketPurchased) {
        showDialogue("Security guard", "You can't enter without a train "
                                       "ticket. Show me a valid ticket, man.");
      } else if (ticketPurchased && res == 'q') {
        char res =
            getPlayerResponse("You have already purchased a ticket, quitting "
                              "now will make your ticket invalid and you will "
                              "have to buy it again. Continue? (y/n)");
        if (res == 'y') {
          break;
        }
      } else if (res == 'q') {
        cout << "quitting railway station..." << endl;
        break;
      }
    }
  }
};

class Pond {

public:
  int fishingLevels[MAX_FISHIN_LEVELS] = {0, 78, 227, 477, 695, 900};

  int getFishingLevelAsInt(Player &player) {
    int currentFishLevel = 0;
    for (int i = 0; i < MAX_FISHIN_LEVELS - 1; i++) {
      if (player.timesFished < fishingLevels[i]) {
        currentFishLevel = i - 1;
        break;
      }
      if (i == MAX_FISHIN_LEVELS - 2 &&
          player.timesFished >= fishingLevels[i]) {
        currentFishLevel = i;
      }
    }
    if (player.timesFished >= fishingLevels[MAX_FISHIN_LEVELS - 1]) {
      currentFishLevel = MAX_FISHIN_LEVELS - 1;
    }

    return currentFishLevel;
  }

    void getFishableCount(Player player, int fishableCount[]) {
    int fishLevel = getFishingLevelAsInt(player);
    fishableCount[0] = 0;
    switch (fishLevel) {
    case 0:
      fishableCount[0] = 0;
      fishableCount[1] = 5;
      break;
    case 1:
      fishableCount[0] = 1;
      fishableCount[1] = 5;
      break;
    case 2:
      fishableCount[0] = 3;
      fishableCount[1] = 7;
      break;
    case 3:
      fishableCount[0] = 0;
      fishableCount[1] = 7;
      break;
    case 4:
      fishableCount[0] = 0;
      fishableCount[1] = 8;
      break;
    case 5:
      fishableCount[0] = 0;
      fishableCount[1] = 9;
      break;
    case 6:
      fishableCount[0] = 0;
      fishableCount[1] = 10;
      break;
    case 7:
      fishableCount[0] = 0;
      fishableCount[1] = 11;
      break;
    case 8:
      fishableCount[0] = 0;
      fishableCount[1] = 12;
      break;
    case 9:
      fishableCount[0] = 0;
      fishableCount[1] = 13;
      break;
    case 10:
      fishableCount[0] = 0;
      fishableCount[1] = 14;
      break;
    case 11:
    case 12:
      fishableCount[0] = 0;
      fishableCount[1] = 14;
      break;
    default:
      break;
    }
    return;
  }

   vector<item *> getFishable(Player &player) {
    int mineLevel = getFishingLevelAsInt(player);
    vector<item *> fishable;
    int fishableCount[2] = {
        0, 3}; //                         0    1      2    3      4       5 6 7
               //                         8       9       10      11      12 13
    vector<item *> items =
        player
            .getFishItemsByAddress(); // vector<item> items = {dirt, rock, wood,
                                      // coal, granite, iron, copper, silver,
                                      // tin,   hardRock, gold, diamond, ruby,
                                      // blackStone, magma, bedrock};
                                      // vector<item*> items = {&dirt, &rock,
                                      // &wood, &coal, &granite, &iron, &copper,
                                      // &silver, &tin, &hardRock, &gold,
                                      // &diamond, &ruby, &blackStone, &magma,
                                      // &bedrock};
    player.caluclateWeights(items);
    getFishableCount(player, fishableCount);

    for (int i = 0, j = fishableCount[0]; i < fishableCount[1]; i++, j++) {
      fishable.push_back(items[j]);
    }

    return fishable;
  }

void fish(Player &player) {
    int fishableCount[2];
     getFishableCount(player, fishableCount);

    vector<item *> fishable =
        getFishable(player); // and caluclate item weights;

    float totalWeight = 0;
    for (int i = 0; i < fishableCount[1]; i++) {
      totalWeight += fishable[i]->weight;
    }

    int itemRepeatCount = 1;// player.dualItems.occured ? randInt(2, 3) : 1;
    cout << "You got: " << endl;

    for (int i = 0; i < itemRepeatCount; i++) {
      float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                     totalWeight;
      item *selecteditem;

      float accWeight = 0;
      for (int i = 0; i < fishableCount[1]; i++) {
        accWeight += fishable[i]->weight;
        if (random < accWeight) {
          selecteditem = fishable[i];
          break;
        }
        random -= fishable[i]->weight;
      }
      int itemCountByLevel = 2;
      int count = (randInt(1, itemCountByLevel) * selecteditem->rareity) == 0 ?  (randInt(1, itemCountByLevel) * selecteditem->rareity) + 1 : 1;

      cout << "\t" << count << " pieces of " << selecteditem->name << endl;
      player.incrementItemCount(selecteditem->name, count);
      player.addXP(selecteditem->xp);

      auto it = find(fishable.begin(), fishable.end(), selecteditem);
      if (it != fishable.end()) {
        fishable.erase(it);
        // Recalculate total weight after removal
        totalWeight = 0;
        for (auto &itemPtr : fishable) {
          totalWeight += itemPtr->weight;
        }
      }
    }
    player.timesFished++;
  }

  void display(Player &player) {
    int currentFishingLevel = getFishingLevelAsInt(player);
    int fishesLeft;
    int nextLevel = currentFishingLevel + 1 < MAX_FISHIN_LEVELS
                        ? currentFishingLevel + 1
                        : currentFishingLevel;
    fishesLeft = fishingLevels[nextLevel] - player.timesFished;
    fishesLeft =
        fishesLeft == 0 ? fishingLevels[currentFishingLevel + 1] : fishesLeft;
    cout << "Times Fished: " << player.timesFished << endl;
    cout << "Current Fishing Level: " << currentFishingLevel << endl;
    if (fishesLeft >= 0) {
      cout << "Fishing attempts left to reach next fishing level: " << fishesLeft;
    } else {
      cout << "Fishing attempts left to reach next fishing level: " << "???";
    }
  }

  void enter(Player &player) {
    cout << "entering pond..." << endl;
    if (player.fishingRod.level < 1) {
      cout << "You do not have a fishing rod!" << endl;
      sleep(1);
      return;
    }
    cout << "click 'f' to fish...";
    char res;
    while (true) {
      res = getPlayerResponse();
      switch (res) {
      case 'f':
        cout << "outside fish";
        fish(player); // todo
        break;
      case 'q':
        cout << "exiting pond..." << endl;
        sleep(1);
        return;
      case 'd':
        display(player); // todo
        break;
      case 'i':
        player.displayInventory();
        break;
      }
    }
  }
};

void to_json(json& j, const Player& p) {
    j = json{
        {"name", p.name}, {"bankBalance", p.bankBalance}, {"wallet", p.wallet}, 
        {"walletLimit", p.walletLimit}, {"creditcard", p.creditcard}, {"luck", p.luck}, 
        {"timesMined", p.timesMined}, {"xp", p.xp}, {"level", p.level}, 
        {"xpToLvl", p.xpToLvl}, {"currentCity", p.currentCity}, {"timesFished", p.timesFished}, 
        {"firstTime", p.firstTime}, {"objectives", p.objectives}, {"hasPickaxe", p.hasPickaxe}, 
        {"pickaxe", p.pickaxe}, {"fishingRod", p.fishingRod}, {"dirt", p.dirt}, 
        {"rock", p.rock}, {"wood", p.wood}, {"coal", p.coal}, {"granite", p.granite}, 
        {"iron", p.iron}, {"copper", p.copper}, {"silver", p.silver}, {"tin", p.tin}, 
        {"hardRock", p.hardRock}, {"gold", p.gold}, {"diamond", p.diamond}, 
        {"ruby", p.ruby}, {"blackStone", p.blackStone}, {"magma", p.magma}, 
        {"bedrock", p.bedrock}, {"soakedBoot", p.soakedBoot}, {"seashell", p.seashell}, 
        {"usedEarphones", p.usedEarphones}, {"usedCondom", p.usedCondom}, {"salmon", p.salmon}, 
        {"clownfish", p.clownfish}, {"tuna", p.tuna}, {"trout", p.trout}, 
        {"squid", p.squid}, {"octopusLeg", p.octopusLeg}, {"jellyfish", p.jellyfish}, 
        {"lobster", p.lobster}, {"pearl", p.pearl}, {"whaleTooth", p.whaleTooth}, 
        {"firstBoot", p.firstBoot}, {"homeLessManBoot", p.homeLessManBoot}, {"inventoryUnlock", p.inventoryUnlock}, 
        {"mineDetailsUnlock", p.mineDetailsUnlock}, {"quitMineUnlock", p.quitMineUnlock}, {"dualItems", p.dualItems}, 
        {"shopUnlock", p.shopUnlock}, {"bankBoot", p.bankBoot}, {"bankOnLunchBreak", p.bankOnLunchBreak}, 
        {"loansUnlocked", p.loansUnlocked}, {"playerCreditCardUnlock", p.playerCreditCardUnlock}, 
        {"playerWalletUpgrade", p.playerWalletUpgrade}, {"sellerMarketBoot", p.sellerMarketBoot}, 
        {"guildUnlocked", p.guildUnlocked}, {"railwayStationUnlock", p.railwayStationUnlock}, 
        {"badges", p.badges}, {"cakeEventStart", p.cakeEventStart}, {"cakeEventMid", p.cakeEventMid}, 
        {"cakeEventEnd", p.cakeEventEnd}, {"cakeEvent", p.cakeEvent}
    };
}

void from_json(const json& j, Player& p) {
    j.at("name").get_to(p.name);
    j.at("bankBalance").get_to(p.bankBalance);
    j.at("wallet").get_to(p.wallet);
    j.at("walletLimit").get_to(p.walletLimit);
    j.at("creditcard").get_to(p.creditcard);
    j.at("luck").get_to(p.luck);
    j.at("timesMined").get_to(p.timesMined);
    j.at("xp").get_to(p.xp);
    j.at("level").get_to(p.level);
    j.at("xpToLvl").get_to(p.xpToLvl);
    j.at("currentCity").get_to(p.currentCity);
    j.at("timesFished").get_to(p.timesFished);
    j.at("firstTime").get_to(p.firstTime);
    j.at("objectives").get_to(p.objectives);
    j.at("hasPickaxe").get_to(p.hasPickaxe);
    j.at("pickaxe").get_to(p.pickaxe);
    j.at("fishingRod").get_to(p.fishingRod);
    j.at("dirt").get_to(p.dirt);
    j.at("rock").get_to(p.rock);
    j.at("wood").get_to(p.wood);
    j.at("coal").get_to(p.coal);
    j.at("granite").get_to(p.granite);
    j.at("iron").get_to(p.iron);
    j.at("copper").get_to(p.copper);
    j.at("silver").get_to(p.silver);
    j.at("tin").get_to(p.tin);
    j.at("hardRock").get_to(p.hardRock);
    j.at("gold").get_to(p.gold);
    j.at("diamond").get_to(p.diamond);
    j.at("ruby").get_to(p.ruby);
    j.at("blackStone").get_to(p.blackStone);
    j.at("magma").get_to(p.magma);
    j.at("bedrock").get_to(p.bedrock);
    j.at("soakedBoot").get_to(p.soakedBoot);
    j.at("seashell").get_to(p.seashell);
    j.at("usedEarphones").get_to(p.usedEarphones);
    j.at("usedCondom").get_to(p.usedCondom);
    j.at("salmon").get_to(p.salmon);
    j.at("clownfish").get_to(p.clownfish);
    j.at("tuna").get_to(p.tuna);
    j.at("trout").get_to(p.trout);
    j.at("squid").get_to(p.squid);
    j.at("octopusLeg").get_to(p.octopusLeg);
    j.at("jellyfish").get_to(p.jellyfish);
    j.at("lobster").get_to(p.lobster);
    j.at("pearl").get_to(p.pearl);
    j.at("whaleTooth").get_to(p.whaleTooth);
    j.at("firstBoot").get_to(p.firstBoot);
    j.at("homeLessManBoot").get_to(p.homeLessManBoot);
    j.at("inventoryUnlock").get_to(p.inventoryUnlock);
    j.at("mineDetailsUnlock").get_to(p.mineDetailsUnlock);
    j.at("quitMineUnlock").get_to(p.quitMineUnlock);
    j.at("dualItems").get_to(p.dualItems);
    j.at("shopUnlock").get_to(p.shopUnlock);
    j.at("bankBoot").get_to(p.bankBoot);
    j.at("bankOnLunchBreak").get_to(p.bankOnLunchBreak);
    j.at("loansUnlocked").get_to(p.loansUnlocked);
    j.at("playerCreditCardUnlock").get_to(p.playerCreditCardUnlock);
    j.at("playerWalletUpgrade").get_to(p.playerWalletUpgrade);
    j.at("sellerMarketBoot").get_to(p.sellerMarketBoot);
    j.at("guildUnlocked").get_to(p.guildUnlocked);
    j.at("railwayStationUnlock").get_to(p.railwayStationUnlock);
    j.at("badges").get_to(p.badges);
    j.at("cakeEventStart").get_to(p.cakeEventStart);
    j.at("cakeEventMid").get_to(p.cakeEventMid);
    j.at("cakeEventEnd").get_to(p.cakeEventEnd);
    j.at("cakeEvent").get_to(p.cakeEvent);
}

#endif
