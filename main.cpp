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
void hit();
int main() 
{
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
        if(ENEMY_WARRIOR_STAT["HEALTS"] <= 0)
        {
            cout << "\n\nYoure win!" << endl;
            ENEMY_WARRIOR_STAT["HEALTS"] = ENEMY_WARRIOR_STAT["BASIC_HEALTS"] * caf;
            ENEMY_WARRIOR_STAT["POWER"] += caf;
            HERO_STAT["EXP"] += 12*caf;
            caf += 0.3;

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
        cout << "\n\nEnter action: \n" << endl;
        cout << ACTION[1] << endl 
        cout << "1. Hit" << endl;
        cout << "2. Healing Spell" << endl;
        cout << "3. Status" << endl;
        cout << "4. Inventory\n\n" << endl;
        cout << "Enemy healts: " << ENEMY_WARRIOR_STAT["HEALTS"] << endl;
        cin >> action;
        if(action == "1")
        {
            ENEMY_WARRIOR_STAT["HEALTS"] -= HERO_STAT["POWER"];
            HERO_STAT["HEALTH"] -= ENEMY_WARRIOR_STAT["POWER"];
        }
        else if(action == "2")
        {
            if (INVENTORY["HEALING_POTION"] > 0)
            {
                HERO_STAT["HEALTH"] += HERO_STAT["HEALING_SPELL"];
                INVENTORY["HEALING_POTION"] -= 1;
            }
            else
            {
                cout << "You no longer have the potion" << endl;
            }
        }
        else if(action == "3")
        {
            map<string, int>::iterator iter = HERO_STAT.begin();
            cout << "Yuore status: " <<  endl;
            for(int i = 0; iter != HERO_STAT.end(); iter++ , i++)
            {
                cout << i+1 << ". " << iter->first << ": " << iter->second << endl;
            }
        }
        else if(action == "4")
        {
            map<string, int>::iterator iter = INVENTORY.begin();
            cout << "Yuore inventory: " <<  endl;
            for(int i = 0; iter != INVENTORY.end(); iter++ , i++)
            {
                cout << i+1 << ". " << iter->first << ": " << iter->second << endl;
            }
        }
    }
    if (HERO_STAT["HEALTH"] <= 0)
    {
        cout << "\n\nYoure dead;(\n\n";
    }
    return 0;
}
