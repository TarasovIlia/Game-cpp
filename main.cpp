#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <map>

using namespace std;

//HERO

map<string, int>HERO_STAT = {
    {"HEALTH", 100},
    {"POWER", 8},
    {"EXP", 0},
    {"MAGIC", 10},
    {"WARRIORS_KILLED", 0},
};
map<string, int>INVENTORY = {
    {"HELMET", 1},
    {"HEALING_POTION", 2},
    {"MAGIC_POTION", 1},
    {"EXPLOSIVE_POTION", 1},
    {"COINT", 0},
    {"SWORD", 1},
    {"SHIELD", 1},
};
map<string, int>HERO_SPELL = {
    {"HEALING_SPELL", 14},
};

//ENEMY

map<string, int>WARRIOR_STAT = {
    {"BASIC_HEALTH", 60},
    {"HEALTH", 60},
    {"POWER", 3},
};
    
enum ACTION {Hit, Spell, Status, Inventory};

int basicExpBonus = 8;
int magicRegenerationCof = 2;
int magicLimit = 40;
double caf = 1.2;

//POTION

const int HEALING_POTION_POINT = 14;
const int EXPLOSIVE_POTION_POINT = 22;
const int MAGIC_POTION_POINT = 18;

//ACTIONS

void hit() {
    WARRIOR_STAT["HEALTH"] -= HERO_STAT["POWER"];
    HERO_STAT["HEALTH"] -= WARRIOR_STAT["POWER"];
}

void showStatus() {
    map<string, int>::iterator iter = HERO_STAT.begin();
    cout << "Yuore status: " <<  endl;
    for(int i = 0; iter != HERO_STAT.end(); iter++ , i++)
    {
        cout << i+1 << ". " << iter->first << ": " << iter->second << endl;
    }
}

void showSpell() {
    map<string, int>::iterator iter = HERO_SPELL.begin();
    cout << "Yuore spell: " <<  endl;
    for(int i = 0; iter != HERO_SPELL.end(); iter++ , i++)
    {
        cout << i+1 << ". " << iter->first << ": " << iter->second << endl;
    }
}

void showInventory() {
    map<string, int>::iterator iter = INVENTORY.begin();
    cout << "Yuore inventory: " <<  endl;
    for(int i = 0; iter != INVENTORY.end(); iter++ , i++)
    {
        cout << i+1 << ". " << iter->first << ": " << iter->second << endl;
    }
}

//INVENTORY

void useHealingPotions() {
    if (INVENTORY["HEALING_POTION"] > 0) {
        HERO_STAT["HEALTH"] += HEALING_POTION_POINT;
        INVENTORY["HEALING_POTION"] -= 1;
    }
    else {
        cout << "\n##\t" << "You no longer have the healing potion" << "\t##" << endl;
    }
}

void useMagicPotions() {
    if (INVENTORY["MAGIC_POTION"] > 0) {
        HERO_STAT["MAGIC"] += MAGIC_POTION_POINT;
        INVENTORY["MAGIC_POTION"] -= 1;
    }
    else {
        cout << "\n##\t" << "You no longer have the magic potion" << "\t##" << endl;
    }
}


void useExplosivePotions() {
    if (INVENTORY["EXPLOSIVE_POTION"] > 0) {
        WARRIOR_STAT["HEALTH"] -= EXPLOSIVE_POTION_POINT;
        INVENTORY["EXPLOSIVE_POTION"] -= 1;
    }
    else {
        cout << "\n##\t" << "You no longer have the explosive potion" << "\t##" << endl;
    }
}

//SPELL

void useHealingSpell() {
    if (HERO_SPELL["HEALING_SPELL"] <= HERO_STAT["MAGIC"]) {
        HERO_STAT["HEALTH"] += HERO_SPELL["HEALING_SPELL"];
        HERO_STAT["MAGIC"] -= HERO_SPELL["HEALING_SPELL"];
    }
    else {
        cout << "\n##\t" << "You need more magic to use this spell" << "\t##" << endl;
    }
}

//ACTION between move

void spellAction() {
    int spell_action;
    cin >> spell_action;
    if (spell_action == 1){
        useHealingSpell();
    }
}

void inventoryAction() {
    int inventory_action;
    cin >> inventory_action;
    if (inventory_action == 3){
        useHealingPotions();
    }
    else if (inventory_action == 2){
        useExplosivePotions();
    }
    else if (inventory_action == 5){
        useMagicPotions();
    }
    
}

//MOVE EVENT 

void magicRegeneration() {
    if (HERO_STAT["MAGIC"] < magicLimit) {
        HERO_STAT["MAGIC"] += magicRegenerationCof;
    }
}

//MAIN

int main() {

    vector<int>cointChance = {3,0,4,5,6};
    string action;

    cout << "\n\nWelcom to the buttle!\n\n" << endl;

    while(HERO_STAT["HEALTH"] > 0 && action != "end")
    {
        if(WARRIOR_STAT["HEALTH"] <= 0)
        {
            cout << "\n\nYoure win!" << endl;
            WARRIOR_STAT["HEALTH"] = WARRIOR_STAT["BASIC_HEALTH"] * caf;
            WARRIOR_STAT["POWER"] += caf;
            HERO_STAT["EXP"] += 12*caf;
            caf += 0.2;
            HERO_STAT["WARRIORS_KILLED"] += 1;
            
            //LOOT random function todo

            srand(static_cast<unsigned int>(time(0)));
            random_shuffle(cointChance.begin(), cointChance.end());

            int cointDrop = cointChance[0];
            INVENTORY["COINT"] += cointDrop;

            int healingPotionChance = rand() % 2;
            if(healingPotionChance == 1) {
                cout << "Youre find healing potion!" << endl;
                INVENTORY["HEALING_POTION"] += 1;
            }

            cout << "Youre find " << cointDrop << " coint!" << endl;
            cout << "But there is new enemy." << endl;
            
        }

        cout << "\n\nEnemy healts: " << WARRIOR_STAT["HEALTH"] << endl;
        cout << "\nEnter action: \n" << endl;
        cout << "1. Hit" << endl;
        cout << "2. Spell" << endl;
        cout << "3. Status" << endl;
        cout << "4. Inventory\n\n" << endl;

        cin >> action;

        if(action == "1") {
            hit();
            magicRegeneration();
        }
        else if(action == "2")
        {
            showSpell();
            cout << "Enter spell number to use it: " << endl;
            spellAction();
        }
        else if(action == "3") {
            showStatus();
        }
        else if(action == "4") {
            showInventory();
            cout << "Enter item number to use it: " << endl;
            inventoryAction();
        }

        //END MOVE 

    }

    //END GAME 

    if (HERO_STAT["HEALTH"] <= 0)
    {
        cout << "\n\n" << "##\t" << "Youre dead;(" << "\t##" <<"\n\n";
    }
    return 0;
}

