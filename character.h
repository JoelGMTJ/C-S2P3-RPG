#ifndef CHARACTER_H
#define CHARACTER_H

#include <iomanip>
#include <sstream>

using namespace std;

/*
--------------------------------------------------------------------------------
Start of class Character
--------------------------------------------------------------------------------
*/
//Class of the character, father class of Warrior, Mage, Archerr and Enemy
class Character {
protected:
    string name;
    int health;
    int mana;
    int strength;
    int shield;

public:
    Character();
    Character(const Character&);
    Character(string name, int hp, int mana, int strength, int shield);
    ~Character();

    string getName();
    int getHealth();
    int getMana();
    int getStrength();
    int getShield();
    bool isAlive();
    void takeDamage(int);
    virtual void attack(Character*) = 0;
    virtual void recover() = 0;
    virtual string toString() = 0;
};

//Default constructor
Character::Character(){
    name = "Desconocido";
    health = 10;
    mana = 10;
    strength = 5;
    shield = 5;
}

//Copy constructor
Character::Character(const Character &a){
    name = a.name;
    health = a.health;
    mana = a.mana;
    strength = a.strength;
    shield = a.shield;
}

//Constructor with all the parameters
Character::Character(string nName, int hp, int nMana, int nStren, int nShield){
    name = nName;
    health = hp;
    mana = nMana;
    strength = nStren;
    shield = nShield;
}

//Destructor of Character
Character::~Character(){}

//Returns the name of the character
string Character::getName(){
    return name;
}

//Returns an int value of the HP of the character
int Character::getHealth(){
    return health;
}

//Returns an int value of the mana of the character
int Character::getMana(){
    return mana;
}

//Returns an int value of the strenght of the character

int Character::getStrength(){
    return strength;
}

//Returns an int value of the shield of the character
int Character::getShield(){
    return shield;
}

//Returns a bool for if the character has hp>0
bool Character::isAlive(){
    if (health > 0){
        return true;
    }
    else {
        return false;
    }
}

//Recieves damage and calculates the real damage because of the shield
void Character::takeDamage(int dmg){
    dmg = dmg - shield;
    if (dmg<0){
        dmg = 0;
    }
    health = health - dmg;
}

/*
--------------------------------------------------------------------------------
Start of class warrior
--------------------------------------------------------------------------------
*/
//Class that inherits from Character
class Warrior : public Character{
public:
    Warrior();
    Warrior(const Warrior&);
    Warrior(string);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Warrior::Warrior()
    : Character("Warrior", 80, 30, 40, 20){}

//Copy constructor
Warrior::Warrior(const Warrior &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield){}

//Constructor when it recieves a name
Warrior::Warrior(string nName)
    : Character(nName, 80, 30, 40, 20){}

//Recieves the pointer of the opponent and hits it
//If mana>10, the damage is doubled
void Warrior::attack(Character* a){
    int crit = 1;
    if (mana>=10){
        crit = crit*2;
        mana = mana-10;
    }

    a->takeDamage(strength*crit);
}

//Heals the warrior to 80 health and 30 mana
void Warrior::recover(){
    health = 80;
    mana = 30;
}

//Returns the info of the Warrior
//It checks if the warrior has died, if so, returns a differente string
string Warrior::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "Cuenta la leyenda que el valiente guerrero de nombre " << name <<
" tiene " << health << "Hp y un mana de " << mana << endl
<< "El guerrero tiene una fuerza de " << strength << " y un escudo de " << shield
<< endl << endl;

    }

    else{

salida << "El valiente guerrero " << name << " ha muerto" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class archer
--------------------------------------------------------------------------------
*/
//Class that inherits from Character
class Archer : public Character{
public:
    Archer();
    Archer(const Archer&);
    Archer(string);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Archer::Archer()
    : Character("Archer", 60, 50, 30, 15){}

//Copy constructor
Archer::Archer(const Archer &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield){}

//Constructor when it recieves a name
Archer::Archer(string nName)
    : Character(nName, 60, 50, 30, 15){}

//Recieves the pointer of the opponent and hits it
//If mana>30, the damage is tripled
void Archer::attack(Character* a){
    int crit = 1;
    if (mana>=30){
        crit = crit*3;
        mana = mana-30;
    }

    a->takeDamage(strength*crit);
}

//Heals the archer to 60 health and 50 mana
void Archer::recover(){
    health = 60;
    mana = 50;
}

//Returns the info of the archer
//It checks if the archer has died, if so, returns a different string
string Archer::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "Cuenta la leyenda que el agil arquero de nombre " << name <<
" tiene " << health << "Hp y un mana de " << mana << endl
<< "El arquero tiene una fuerza de " << strength << " y un escudo de " << shield
<< endl << endl;

    }

    else{

salida << "El agil arquero " << name << " ha muerto" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class mage
--------------------------------------------------------------------------------
*/
//Class that inherits from Character
class Mage : public Character{
public:
    Mage();
    Mage(const Mage&);
    Mage(string);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Mage::Mage()
    : Character("Mage", 65, 100, 20, 10){}

//Copy constructor
Mage::Mage(const Mage &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield){}

//Constructor when it recieves a name
Mage::Mage(string nName)
    : Character(nName, 65, 100, 20, 10){}

//Recieves the pointer of the opponent and hits it
//If mana>30, the damage is multiplied by 4
void Mage::attack(Character* a){
    int crit = 1;
    if (mana>=30){
        crit = crit*4;
        mana = mana-30;
    }

    a->takeDamage(strength*crit);
}

//Heals the mage to 65 health and 100 mana
void Mage::recover(){
    health = 65;
    mana = 100;
}

//Returns the info of the mage
//It checks if the mage has died, if so, returns a different string
string Mage::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "Cuenta la leyenda que el sabio mago de nombre " << name <<
" tiene " << health << "Hp y un mana de " << mana << endl
<< "El mago tiene una fuerza de " << strength << " y un escudo de " << shield
<< endl << endl;

    }

    else{

salida << "El sabio mago " << name << " ha muerto" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class enemy
--------------------------------------------------------------------------------
*/
//Class that inherits from Character
class Enemy : public Character{
public:
    Enemy();
    Enemy(const Enemy&);
    Enemy(string, int, int, int);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Enemy::Enemy()
    : Character("Enemy", 30, 0, 15, 5){}

//Copy constructor
Enemy::Enemy(const Enemy &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield){}

//Constructor when it recieves a name and values 
Enemy::Enemy(string nName, int hp, int stren, int shi)
    : Character(nName, hp, 0, stren, shi){}

//Recieves the pointer of the hero and hits him
//The damage is the same as the enemy strength
void Enemy::attack(Character* a){
    a->takeDamage(strength);
}

//Heals the enemy 15 hp and 15 mana points
void Enemy::recover(){
    health = health + 15;
    mana = mana + 15;
}

//Returns the info od the enemy
//It checks if the enemy is dead, if so, a different string is returned
string Enemy::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "El malvado enemigo " << name <<
" tiene " << health << "Hp y un mana de " << mana << endl
<< "El enemigo tiene una fuerza de " << strength << " y un escudo de " << shield
<< endl << endl;

    }

    else{

salida << "El enemigo " << name << " ha sido derrotado" << endl << endl;

    }

    return salida.str();
}
#endif