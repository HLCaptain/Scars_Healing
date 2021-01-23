#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "String.h"
#include "Enemy.h"
#include "Entity.h"
#include "InfoPreset.h"
#include "Storage.h"

/// Player has Gold and a Storage in which it can hold some Item. The Player will be able to spend Gold in the Shop.
class Player : public Entity {
	/// Amount of Gold the Player has
	size_t Gold;

	/// Storage of the Player
	Storage StorageType;
public:
	/// Constructor
	Player(const char* Name, double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5, size_t Gold = 0, Storage StorageType = Storage());
	
	/// Default Constructor
	Player(double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5, size_t Gold = 0);

	/// Destructor
	virtual ~Player();

	/// Writes out the Player's info to an output
	std::ostream& getInfoEntity(InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout);

	/// Gets Player's amount of Gold
	size_t getGold();

	/// Gets Player's type of Storage
	Storage& getStorageType();

	/// Attack an Enemy
	void attackEnemy(Enemy& e);

	/// Attack an Enemy with a Weapon/Shield
	void attackEnemy(Enemy& e, Item& WS);

	/// Healing with an Item
	void Heal(const size_t Index);
};

#endif //PLAYER_H
