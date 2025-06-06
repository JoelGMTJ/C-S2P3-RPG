#ifndef LEVEL_H
#define LEVEL_H

#include <iomanip>
#include <sstream>

using namespace std;

/*
--------------------------------------------------------------------------------
Start of class level
--------------------------------------------------------------------------------
*/
//Class of the levels in the rpg
class Level {
protected:
    string name;
    Character* hero;
    Character* enemy;
    string prologue;
    string epilogue;
    bool won;

public:
    Level();
    Level(const Level&);
    Level(string);
    ~Level();
    bool hasWon();
    void addPrologue(string);
    void addEpilogue(string);
    void addEnemy(Character*);
    void addHero(Character*);
    void execute();
};

//Default constructor, leaves basically all values empty
Level::Level(){
    name = "Stage";
    hero = 0; //PREGUNTAR COMO DEJAR VACIO A LEVEL
    enemy = 0;
    prologue = "Aqui va tu prologo";
    epilogue = "Aqui va tu epilogo";
    won = true;
}

//Copy constructor
Level::Level(const Level &a){
    name = a.name;
    hero = a.hero;
    enemy = a.enemy;
    prologue = a.prologue;
    epilogue = a.epilogue;
    won = a.won;
}

//Creates a level with a custom name
Level::Level(string nName){
    name = nName;
    hero = 0; //PREGUNTAR COMO DEJAR VACIO A LEVEL
    enemy = 0;
    prologue = "Aqui va tu prologo";
    epilogue = "Aqui va tu epilogo";
    won = true;
}

//Class destructor
Level::~Level(){}

//Checks if the battle is over and returns a bool value
bool Level::hasWon(){
    if (hero->isAlive() &! enemy->isAlive()){
        return true;
    }
    else{
        return false;
    }
}

//Adds a string for the prologue of the fight
void Level::addPrologue(string pro){
    prologue = pro;
}

//Adds a string for the epilogue of the fight

void Level::addEpilogue(string epi){
    epilogue = epi;
}

//Adds the pointer of the character of the hero
void Level::addHero(Character* nHero){
    hero = nHero;
}

//Adds the pointer of the character of the enemy
void Level::addEnemy(Character* nEnemy){
    enemy = nEnemy;
}

//It makes the battle happen
void Level::execute(){
    //Values used to make the battle system work
    bool continueBattle = true;
    Character* winner;

    //Checks if the enemy is alive for the first time
    if (!hero->isAlive() &! enemy->isAlive()){
        continueBattle = false;
    }

    //Cycle so that the battle ends when somebody is dead
    while (continueBattle) {

        hero->attack(enemy);
        cout << hero->getName() << " attacks " << enemy->getName() << endl;
        cout << enemy->getName() << " has " << enemy->getHealth() << endl;
        enemy->attack(hero);//TO DO implementar algo para variar el orden de ataque
        cout << enemy->getName() << " attacks " << hero->getName() << endl;
        cout << hero->getName() << " has " << hero->getHealth() << endl;
        cout << "End of the first turn" << endl << endl;
        
        //Checks for when somebody dies
        if (!hero->isAlive() or !enemy->isAlive()){
            continueBattle = false;
        }
    }

    //Conditional to check who won the battle
    if (hero->isAlive() &! enemy->isAlive()){
        won = true;
        winner = hero;
    }
    else{
        won = false;
        winner = enemy;
    }

    cout << "La batalla ha terminado" << endl << "EL ganador es " 
    << winner->getName() << endl << endl;

}


#endif