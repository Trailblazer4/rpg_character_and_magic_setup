#include <iostream>
#include <vector>

using namespace std;

class Weapon{
    string name;
    int atk;
    vector<string> moves;

    public:
        Weapon(string s){
            name = s;
        }

        void setAtk(int i){
            atk = i;
        }

        int getAtk(){
            return atk;
        }

        void setName(string s){
            name = s;
        }

        string getName(){
            return name;
        }

        void addMove(string s){
            moves.push_back(s);
        }

        string getMove(int i){
            return *(moves.begin() + i);
        }
};
