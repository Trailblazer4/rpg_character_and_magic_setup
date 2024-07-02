#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Magic.cpp"
using namespace std;

enum Blah{
    A,
    B,
    C,
};

vector<string> split(string charStar, string delim){
    vector<string> charStarStar;
    for(int start = 0, target = 0; start < charStar.length(); start = target + 1){
        if(charStar.find(delim, start) != string::npos){
            target = charStar.find(delim, start);
        }
        else{
            target = charStar.length();
        }

        charStarStar.push_back(charStar.substr(start, (target - start)));
    }

    return charStarStar;
}

void makeEnemy(string libInfo){
    vector<string> enemyInfo = split(libInfo, ",");

    for(int i = 3; i < 10; i++){
        vector<string> keyVal = split(enemyInfo.at(i), ":");
        pair<int, int> minMax(stoi(keyVal.at(0)), stoi(keyVal.at(1)));
        cout << minMax.first << "   " << minMax.second << endl << endl;
    }
}

int main(){
   vector<Magic> magicLibrary;
   string info;
   ifstream file("MagicLibrary.csv");
   while(file >> info){
    vector<string> spellInfo = split(info, ",");

    vector<string> effect = split(spellInfo.at(4), ":");
    vector<string> prob = split(spellInfo.at(5), ":");

    magicLibrary.push_back(Magic(
        spellInfo.at(0),
        stoi(spellInfo.at(1)),
        stoi(spellInfo.at(2)),
        stoi(spellInfo.at(3)),
        effect,
        prob,
        stoi(spellInfo.at(6))
    ));
   }
   file.close();

   vector<string> enemyLibrary;
   string eInfo;
   ifstream eFile("EnemyLibrary.csv");
   while(eFile >> eInfo){
    enemyLibrary.push_back(eInfo);
   }

    makeEnemy(enemyLibrary.at(0));

    /*
    for(int i = 0; i < spellsLibrary.size(); i++){
        cout << spellsLibrary.at(i).at(0) << endl <<
        "Element: " << spellsLibrary.at(i).at(1) << "/" << spellsLibrary.at(i).at(2) << endl <<
        "Power: " << spellsLibrary.at(i).at(3) << endl <<
        "Effect(Chance): " << spellsLibrary.at(i).at(4) << "(" << spellsLibrary.at(i).at(5) << "%)" << endl <<
        "Target: " << spellsLibrary.at(i).at(6) << endl;

        cout << endl;
    }
    */

    /*
   vector<int> mySpells;
    mySpells.push_back(2);
    mySpells.push_back(3);
    */

   /*
    string charStar = "abc,def,ghi,jkl";

    int start = 0, target = 0;
    while(start < charStar.length()){
        if(charStar.find(",", start) != string::npos){
            target = charStar.find(",", start);
        }
        else{
            target = charStar.length();
        }
        cout << charStar.substr(start, (target - start)) << endl;

        start = target + 1;
    }

    vector<string> myWords = split(charStar, ",");

    for(int i = 0; i < myWords.size(); i++){
        cout << myWords.at(i) << endl << endl;
    }
    */
}

/*
I think I want to load up all the moves in the games while the game loads up
So, while the game is booting up the world, it will open the magic library,
item library, etc. as csv files, and load all of them into vector<*> (vectors of pointers to objects)
so that any library can be accessed by index for the pointer to an item or spell

Obviously, WeaponInfo objects will be put into the inventory, equipment slots,
or pickuppable items in the world, holding pointers to objects given by the pre-loaded vectors

Every character will have a vector<*Spell> to hold pointers to spells from SpellLibrary
that they are able to use
If I REALLY need to I'll use a SpellInfo object instead to add modifications to spells per character,
but I should be fine with just this

Note: Info objects, like WeaponInfo (and the speculated SpellInfo) should be actual objects and not
pointed values. This would defeat their purpose as the point of these is to make personalized weapons
per weapon iteration in the game. While they hold pointers to all-purpose objects, they also contain
a vector<enum> enchants
*/

/*
For items, have a boolean stackable
This measures whether an item can be stacked when added to the inventory
Potions and elixirs are stackable, equipment is not stackable
When an item is used, its pointer is set to NULL (?) or something like that
*/