#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <map>

using namespace std;

    map<string, int>HERO_STAT = {
        {"HEALTH", 100},
        {"POWER", 8},
        {"EXP", 0},
        {"WARRIORS_KILLED", 0},
    };
    map<string, int>INVENTORY = {
        {"HELMET", 1},
        {"HEALING_POTION", 2},
        {"EXPLOSIVE_POTION", 0},
        {"COINT", 0},
        {"SWORD", 1},
        {"SHIELD", 1},
    };
    enum ACTION {Hit, Spell, Status, Inventory};
    map<string, int>HERO_SPELL = {
        {"HEALING_SPELL", 8},
    };
    map<string, int>ENEMY_WARRIOR_STAT = {
        {"BASIC_HEALTH", 60},
        {"HEALTH", 60},
        {"POWER", 3},
    };

    int HEALING_POTION_POINT = 14;

void hit() {
    ENEMY_WARRIOR_STAT["HEALTH"] -= HERO_STAT["POWER"];
    HERO_STAT["HEALTH"] -= ENEMY_WARRIOR_STAT["POWER"];
}

void showStatus() {
    map<string, int>::iterator iter = HERO_STAT.begin();
    cout << "Yuore status: " <<  endl;
    for(int i = 0; iter != HERO_STAT.end(); iter++ , i++)
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

void useHealingPotions() {
    if (INVENTORY["HEALING_POTION"] > 0) {
        HERO_STAT["HEALTH"] += HEALING_POTION_POINT;
        INVENTORY["HEALING_POTION"] -= 1;
    }
    else {
        cout << "You no longer have the potion" << endl;
    }
}

void inventoryAction() {
    int inventory_action;
    cin >> inventory_action;
    if (inventory_action == 3){
        useHealingPotions();
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

int main() {
    int basicExpBonus = 8;
    double caf = 1.2;
    string action;
    vector<int>cointChance;
    cointChance.push_back(3);
    cointChance.push_back(0);
    cointChance.push_back(4);
    cointChance.push_back(5);
    cointChance.push_back(6);

    cout << "\n\nWelcom to the buttle!\n\n" << endl;

    while(HERO_STAT["HEALTH"] > 0 && action != "end")
    {
        if(ENEMY_WARRIOR_STAT["HEALTH"] <= 0)
        {
            cout << "\n\nYoure win!" << endl;
            ENEMY_WARRIOR_STAT["HEALTH"] = ENEMY_WARRIOR_STAT["BASIC_HEALTH"] * caf;
            ENEMY_WARRIOR_STAT["POWER"] += caf;
            HERO_STAT["EXP"] += 12*caf;
            caf += 0.2;
            HERO_STAT["WARRIORS_KILLED"] += 1;

            srand(static_cast<unsigned int>(time(0)));
            random_shuffle(cointChance.begin(), cointChance.end());
            int cointDrop = cointChance[0];
            INVENTORY["COINT"] += cointDrop;
            cout << "Youre find " << cointDrop << " coint!" << endl;
            int healingPotionChance = rand() % 2;
            if(healingPotionChance == 1) {
                cout << "Youre find healing potion!" << endl;
                INVENTORY["HEALING_POTION"] += 1;
            }
            cout << "But there is new enemy." << endl;
            
        }
        cout << "\n\nEnemy healts: " << ENEMY_WARRIOR_STAT["HEALTH"] << endl;
        cout << "\nEnter action: \n" << endl;
        cout << "1. Hit" << endl;
        cout << "2. Spell" << endl;
        cout << "3. Status" << endl;
        cout << "4. Inventory\n\n" << endl;
        cin >> action;
        if(action == "1") {
            hit();
        }

        else if(action == "2")
        {
            showSpell();
        }
        else if(action == "3") {
            showStatus();
        }
        else if(action == "4") {
            showInventory();
            cout << "Enter item number to use it: " << endl;
            inventoryAction();
        }
    }
    if (HERO_STAT["HEALTH"] <= 0)
    {
        cout << "\n\nYoure dead;(\n\n";
    }
    return 0;
}

