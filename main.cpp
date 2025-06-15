#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "character.h"
#include "level.h"

using namespace std;

vector<Level*> levels(3);
Character *hero;

//Function that asks the user to guess a number, depending on how far the guess 
//was, it will be the heros luck value
//Also checks if the guess was in the range asked for
int assignRandom(){
	
	try {
		int guess, answer = (rand() % 101) - 1;
		cout << "To detdermine your heros luck you need to guess a number"
		<< " from 1 to 100" << endl;
		cin >> guess;
		cout << "Nice try, the number was " << answer << endl;
		if (guess<=100 && guess>=0){
			int separation = guess - answer;
			if (separation<0){
				separation = separation * -1;
			}
			return 100-separation;
		}
		else{
			throw guess;
		}
	}
	catch(int guess){
		cout << "Invalid number"<< endl;
		cout << "Your hero has the worst luck possible :(" << endl;
		return 1;
	}
}

//Creates a hero, asks for his name, creates the luck value, and the type of 
//character it is
void createHero() {
	string name;
	int option;

	cout << "What is your hero's name? ";
	cin >> name;
	cin.ignore();

	cout << "\n0. Warrior - A brave hero with a lot of health \n";
	cout << "1. Archer - A balanced damagedealer \n";
	cout << "2. Mage - A powerfull glass cannon \n \n";
	cout << "What kind of hero do you want to be? ";
	cin >> option;

	option %= 3;

	int heroLuck = assignRandom();

	switch(option) {
		case 0 : hero = new Warrior(name, heroLuck); break;
		case 1 : hero = new Archer(name, heroLuck); break;
		case 2 : hero = new Mage(name, heroLuck); break;
	}

	cout << "Your hero has " << hero->getLuck() <<  " luck" << endl;

}

//Creates all the levels, the levels were done by the teacher
void createLevels() {
	//Creates the luck of the enemies, the stronger the enemy, the more 
	//likely it is to have a higher luck
	int gobLuck = (rand() % 100); 
	int orcLuck = (rand() % 85)+15; 
	int draLuck = (rand() % 70)+30; 


	levels[0] = new Level("The Duel in the Goblin's Lair");
	levels[0]->addPrologue("The hero entered a foggy forest. Twisted trees whispered secrets. In a moonlit clearing, a mighty goblin appeared, ready to battle.");
	levels[0]->addEpilogue("The hero bravely defeated the goblin. Exhausted but victorious, he looked at the sunrise, ready for future challenges.");
	levels[0]->addEnemy(new Enemy("Goblin", 25, 15, 5, gobLuck));
	levels[0]->addHero(hero);

	levels[1] = new Level("The Battle of the Shadow Cave");
	levels[1]->addPrologue("The cave was dark and damp, with stalactites, bats, and an oppressive atmosphere. An orc awaited the hero by a fire.");
	levels[1]->addEpilogue("The hero, bleeding but victorious, defeated the orc. Exhausted, he picked up his sword and set out for new adventures.");
	levels[1]->addEnemy(new Enemy("Orc", 75, 45, 15, orcLuck));
	levels[1]->addHero(hero);

	levels[2] = new Level("The Confrontation at the Frosty Peak");
	levels[2]->addPrologue("On the snowy mountaintop, the hero faced the red dragon. Icy wind whipped as the dragon roared, its scales glistening. Battle imminent.");
	levels[2]->addEpilogue("The hero stood over the fallen dragon. Wind scattered ashes. Sword smoking, he looked out over the snowy landscape, triumphant.");
	levels[2]->addEnemy(new Enemy("Dragon", 100, 60, 30, draLuck));
	levels[2]->addHero(hero);
}

//Erases all the levels
void deleteAll() {
	for (Level *lvl : levels) {
		delete lvl;
	}
}

int main(int argc, char* argv[]) {
	int option, i = 0; 
	bool finished = false;
    srand(time(0));

	createHero();

	createLevels();

	//Start of the adventure
	cout << "\n\n\n----------------------------------------------------\n"
	     << "In the Kingdom of Eldoria, peace is shattered when the "
		 << "necromancer Sarvok seeks the Stone of Eternity to gain "
		 << "unlimited power. Guided by a prophecy, three heroes, a "
		 << "Warrior, an Archer, and a Mage, set out on a journey to stop "
		 << "Sarvok from achieving his goal, facing many dangers along the way.\n";
		 cout << "----------------------------------------------------\n\n\n\n";

	//Loops so that the game goes through all the levels unless the hero loses
	while (!finished && i < levels.size()) {
		string advance;

		//Shows the speed of the enemy, wich decides the order of attacks
		cout << "The next battle is against " << levels[i]->getEnemy()->getName() << endl;
		cout << "Your hero has " << hero->getSpeed() <<" of speed" << endl;
		cout << "The enemy has " << levels[i]->getEnemy()->getSpeed() <<" of speed" << endl << endl;
		cout << "Press any key to continue" << endl;
		
		cin >> advance;
		levels[i]->execute();
		if (!levels[i]->hasWon()) {
			finished = true;
		} else {
			cout << hero->toString() << "\n";
			cout << "Do you want to rest? ";
			cout << endl << "Resting restores some of your hp and mana, but "
			<< "slightly reduces your speed" << endl;
			cin >> option;
	
			if (option != 0) {
				hero->recover();
			}
		}
		i++;
	}

	if (i >= levels.size() && levels[i-1]->hasWon()) {
		cout << "After arduous battles, the heroes reached the Dark Fortress "
			 << "and defeated Sarvok, sealing the Eternity Stone. Eldoria flourished "
			 << "and the heroes were celebrated. Their legacy continues to inspire, "
			 << "maintaining peace and justice in the realm.\n";
	}

	deleteAll();

	return 0;
}