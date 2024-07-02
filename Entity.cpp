#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Magic.cpp"
using namespace std;

class Entity{
    string name;
    int atk, def, mag, mgdf, spd;
    int projAtk, projDef, projMag, projMgdf, projSpd;

    vector<Magic> magics;
    vector<Status> status;
    Buffs buffs;

    public:
        Entity(string n, int a, int d, int m, int md, int s){
            name = n;
            atk = a; def = d;
            mag = m; mgdf = md;
            spd = s;
        }

        string getName(){
            return name;
        }

        int getAtk(){
            return atk;
        }

        int getDef(){
            return def;
        }

        int getMag(){
            return mag;
        }

        int getMgdf(){
            return mgdf;
        }

        int getSpd(){
            return spd;
        }

        vector<Status>* getStatus(){
            return &status;
        }

        Status* getStatus(int i){
            return &status.at(i);
        }

        Buffs* getBuffs(){
            return &buffs;
        }

        stack<Status>* getBuffs(int i){
            return buffs.getStatStack(i);
        }

        bool has(Magic m){
            for(int i = 0; i < magics.size(); i++){
                if(magics.at(i).getName().compare(m.getName()) == 0){
                    return true;
                }
            }
            return false;
        }

        bool has(Status s){
            for(int i = 0; i < status.size(); i++){
                if(status.at(i) == s){
                    return true;
                }
            }
            return false;
        }

        void learn(Magic m){
            if(!has(m)){
                magics.push_back(m);
            }
            else{
                cout << name << " has already learned " << m.getName() << endl;
            }
        }

        void use(Magic move, Entity castee){
            //first the target is confirmed(enemy or ally), then the damage calculation,
            //then a roll for a chance of pushing a status/buff onto the target's status/buffs list

            if(move.getTarget() == ENEMY){
                //negative effects
                cout << castee.getName() << " took " <<
                (move.getPower() - castee.getMgdf()) << " damage!" << endl;

                /*
                for(int i = 0; i < move.getEffects().size(); i++){
                    if(randNum < move.getEffects(i).second){
                        castee.getStatus().push_back(move.getEffects(i).first);
                        cout << "Enemy was afflicted with " << move.getEffects(i).first << endl;
                    }
                }
                */
            }
            else{
                //positive effects
                cout << castee.getName() << " was healed for " <<
                move.getPower() << " HP!" << endl;
            }
        }

        void use(Magic move, Entity castees[]){

        }

        void setProjStats(){
            for(int i = 0; i < 5; i++){
                int stat;
                int* statP;
                switch(i){
                    case 0:
                        stat = atk;
                        statP = &projAtk;
                        break;
                    case 1:
                        stat = def;
                        statP = &projDef;
                        break;
                    case 2:
                        stat = mag;
                        statP = &projMag;
                        break;
                    case 3:
                        stat = mgdf;
                        statP = &projMgdf;
                        break;
                    case 4:
                        stat = spd;
                        statP = &projSpd;
                        break;
                }

                if(getBuffs(i)->empty()){
                    *statP = stat;
                    continue;
                }

                double mod;
                switch(getBuffs(i)->top() / 5){
                    case 2:
                        mod = .3;
                        break;
                    case 3:
                        mod = -.15;
                        break;
                }

                *statP = stat + (stat * mod) * getBuffs(i)->size();
            }
        }

        void displayStats(){
            cout << "Atk: " << atk << "   " << "Def: " << def << endl
            << "Mag: " << mag << "   " << "Mgdf: " << mgdf << endl
            << "Spd: " << spd << endl;
        }

        void displayProjStats(){
            cout << "Atk: " << projAtk << "   " << "Def: " << projDef << endl
            << "Mag: " << projMag << "   " << "Mgdf: " << projMgdf << endl
            << "Spd: " << projSpd << endl;
        }
};

int main(){
    Entity crimson("Crimson", 25, 18, 22, 15, 8);
    Entity celeste("Celeste", 25, 21, 23, 21, 7);
    Magic au("Au", 0, 0, 0, vector<string>(), vector<string>(), 0);
    Magic ar("Ar", 0, 0, 0, vector<string>(), vector<string>(), 0);
    crimson.learn(au);

    cout << crimson.getBuffs() << endl;
}