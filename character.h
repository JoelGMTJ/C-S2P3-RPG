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
    double strength; //Changed it to double so that it works with luck
    int shield;
    double luck; //NEW value to modify the attack and speed values
    int speed; //NEW value to see who attacks first, depends on other attributes

public:
    Character();
    Character(const Character&);
    Character(string, int, int, double, int, double);
    ~Character();

    string getName();
    int getHealth();
    int getMana();
    double getStrength();
    int getShield();
    double getLuck();
    int getSpeed() const;
    bool isAlive();
    void takeDamage(double);
    virtual void attack(Character*) = 0;
    virtual void recover() = 0;
    virtual string toString() = 0;

    bool operator<(const Character&); //Used the < operator to compare speeds
};

//Default constructor
Character::Character(){
    name = "Unknown";
    health = 10;
    mana = 10;
    strength = 5;
    shield = 5;
    luck = 50;
    speed = health-mana/shield+0.5*luck; //How the speed is calculated for everyone
}

//Copy constructor
Character::Character(const Character &a){
    name = a.name;
    health = a.health;
    mana = a.mana;
    strength = a.strength;
    shield = a.shield;
    luck = a.luck;
    speed = a.speed;
}

//Constructor with all the parameters
Character::Character(string nName, int hp, int nMana, double nStren, int nShield, double nLuck){
    name = nName;
    health = hp;
    mana = nMana;
    strength = nStren;
    shield = nShield;
    luck = nLuck;
    speed = health-mana/shield+0.5*luck;
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
double Character::getStrength(){
    return strength;
}

//Returns an int value of the shield of the character
int Character::getShield(){
    return shield;
}

//Returns an int value of the luck of the character
double Character::getLuck(){
    return luck;
}

//Returns an int value of the speed of the character
int Character::getSpeed() const{
    return speed;
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
void Character::takeDamage(double dmg){
    dmg = dmg - shield;
    if (dmg<0){
        dmg = 0;
    }
    health -= dmg;
}

//Compares the speed of 2 characters
bool Character::operator<(const Character &other){
    return (this->getSpeed() < other.getSpeed());
}

/*
--------------------------------------------------------------------------------
Start of class warrior
--------------------------------------------------------------------------------
STATS OF THE WARRIOR
Max hp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -80
Starting mana- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -30
Strength - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -40
Shield - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -20
Luck - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Speed- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
*/
//Class that inherits from Character
class Warrior : public Character{
public:
    Warrior();
    Warrior(const Warrior&);
    Warrior(string, int); //New constructor adressing the luck
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Warrior::Warrior()
    : Character("Warrior", 80, 30, 40, 20, 50){}

//Copy constructor
Warrior::Warrior(const Warrior &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield, a.luck){}

//Constructor when it recieves a name and luck value
Warrior::Warrior(string nName, int nLuck)
    : Character(nName, 80, 30, 40, 20, nLuck){}

//Recieves the pointer of the opponent and hits it
//If mana>10, the damage is doubled
//Then is also affected by the luck value
void Warrior::attack(Character* a){
    double crit = 1;
    if (mana>=10){
        crit = crit*2;
        mana = mana-10;
    }

    crit = crit * (luck/70);

    a->takeDamage(strength*crit);
}

//Heals the warrior 30hp, 8 mana points and loses 15 points of speed
void Warrior::recover(){
    health +=30;
    mana += 8;
    speed -= 15;
}

//Returns the info of the Warrior
//It checks if the warrior has died, if so, returns a differente string
string Warrior::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "The warrior with the name of " << name <<
" has " << health << "Hp and " << mana << " of mana" << endl
<< "He has a strength of " << strength << " and a shield of " << shield << endl
<< "His luck is " << luck << " and a speed of " << speed << endl << endl;

    }

    else{

salida << "The brave warrior " << name << " has died" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class archer
--------------------------------------------------------------------------------
STATS OF THE ARCHER
Max hp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -60
Starting mana- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -50
Strength - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -30
Shield - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -15
Luck - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Speed- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
*/
class Archer : public Character{
public:
    Archer();
    Archer(const Archer&);
    Archer(string, int);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Archer::Archer()
    : Character("Archer", 60, 50, 30, 15, 50){}

//Copy constructor
Archer::Archer(const Archer &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield, a.luck){}

//Constructor when it recieves a name and luck value
Archer::Archer(string nName, int nLuck)
    : Character(nName, 60, 50, 30, 15, nLuck){}

//Recieves the pointer of the opponent and hits it
//If mana>30, the damage is tripled
//Its also affected by the luck value
void Archer::attack(Character* a){
    int crit = 1;
    if (mana>=30){
        crit = crit*3;
        mana -= 30;
    }

    crit += luck/35;


    a->takeDamage(strength*crit);
}

//Heals the archer 25 hp and 30 mana points and loses 10 speed points
void Archer::recover(){
    health += 25;
    mana += 30;
    speed -= 10;
}

//Returns the info of the archer
//It checks if the archer has died, if so, returns a different string
string Archer::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "The archer with the name of " << name <<
" has " << health << "Hp and " << mana << " of mana" << endl
<< "He has a strength of " << strength << " and a shield of " << shield << endl
<< "His luck is " << luck << " and a speed of " << speed << endl << endl;

    }

    else{

salida << "The brave archer " << name << " has died" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class mage
--------------------------------------------------------------------------------
STATS OF THE MAGE
Max hp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -65
Starting mana- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 100
Strength - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -20
Shield - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -10
Luck - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Speed- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
*/
class Mage : public Character{
public:
    Mage();
    Mage(const Mage&);
    Mage(string, int);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Mage::Mage()
    : Character("Mage", 65, 100, 20, 10, 50){}

//Copy constructor
Mage::Mage(const Mage &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield, a.luck){}

//Constructor when it recieves a name and luck value
Mage::Mage(string nName, int nLuck)
    : Character(nName, 65, 100, 20, 10, nLuck){}

//Recieves the pointer of the opponent and hits it
//If mana>30, the damage is multiplied by 4
//Its also affected by the luck value
void Mage::attack(Character* a){
    int crit = 1;
    if (mana>=30){
        crit = crit*4;
        mana = mana-30;
    }

    crit += luck/50;


    a->takeDamage(strength*crit);
}

//Heals the mage to 65 health and 100 mana
void Mage::recover(){
    health += 30;
    mana += 30;
    speed -= 5;
}

//Returns the info of the mage
//It checks if the mage has died, if so, returns a different string
string Mage::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "The mage with the name of " << name <<
" has " << health << "Hp and " << mana << " of mana" << endl
<< "He has a strength of " << strength << " and a shield of " << shield << endl
<< "His luck is " << luck << " and a speed of " << speed << endl << endl;

    }

    else{

salida << "The brave mage " << name << " has died" << endl << endl;

    }

    return salida.str();
}

/*
--------------------------------------------------------------------------------
Start of class enemy
--------------------------------------------------------------------------------
STATS OF THE ENEMY
Max hp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Starting mana- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Strength - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Shield - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Luck - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
Speed- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ?
*/
class Enemy : public Character{
public:
    Enemy();
    Enemy(const Enemy&);
    Enemy(string, int, int, int, int);
    void attack(Character*) override; 
    void recover() override;
    string toString() override;
};

//Default constructor
Enemy::Enemy()
    : Character("Enemy", 30, 0, 15, 5, 50){}

//Copy constructor
Enemy::Enemy(const Enemy &a)
    : Character(a.name, a.health, a.mana, a.strength, a.shield, a.luck){}

//Constructor when it recieves a name and values 
Enemy::Enemy(string nName, int hp, int stren, int shi, int luc)
    : Character(nName, hp, 0, stren, shi, luc){}

//Recieves the pointer of the hero and hits him
//The damage is affected by the strength and luck value
void Enemy::attack(Character* a){
    a->takeDamage(strength*luck/50);
}

//Heals the enemy 15 hp and 15 mana points
void Enemy::recover(){
    health += 15;
    mana += 15;
}

//Returns the info od the enemy
//It checks if the enemy is dead, if so, a different string is returned
string Enemy::toString(){
    stringstream salida;

    if (this->isAlive()){

salida << "The evil " << name <<
" has " << health << "Hp and a mana of " << mana << endl
<< "The enemy has a strength of " << strength << " with a shield of " << shield
<< endl << "The enemy has " << luck << " of luck and " << speed << " of speed" 
<< endl << endl;

    }

    else{

salida << "The " << name << " has been defeated" << endl << endl;

    }

    return salida.str();
}
#endif