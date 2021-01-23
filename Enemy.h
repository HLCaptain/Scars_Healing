#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "String.h"
#include "Storage.h"
#include "Entity.h"
#include "InfoPreset.h"
class Player;

// Enemy Class is gonna be made by a factory pattern

/// Enemy can attack a Player without the Player damaging it, every Enemy will have a Level, and will have a chance to drop an Item if it dies according to its Level.
class Enemy : public Entity {
	//something soon
	//maybe an holds an item to drop it, or drop his gold
	//or level
public:
	/// Constructor
	Enemy(const char* Name, double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5);

	/// Default Constructor
	Enemy(double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5);

	/// Destructor
	virtual ~Enemy();

	/// Attack Player without taking Damage from it
	void attackPlayer(Player& PLYR, Item WS = Item());

	/// Displays the info of an Enemy, dynamically controlable with an InfoPreset
	std::ostream& getInfoEntity(InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout);
};

#endif //ENEMY_H
