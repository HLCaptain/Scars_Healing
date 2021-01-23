#ifndef ENTITY_H
#define ENTITY_H

#include "String.h"
#include "InfoPreset.h"

/// An alive Entity can be a Player or an Enemy (for now). It has HP, a Name and basic attributes, like BaseDMG and BaseDEF.
class Entity {
	/// Entity Name
	String Name;

	/// Healthpoint of the entity
	double HP;

	/// Maximum Healthpoint of the entity
	double MaxHP;

	/// Base Damage of the entity
	double BaseDMG;

	/// Base Defense of the entity
	double BaseDEF;
public:
	/// Constructor
	Entity(const char* Name, double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5);

	/// Default Constructor
	Entity(double HP = 100, double MaxHP = 100, double BaseDMG = 5, double BaseDEF = 5);

	/// Destructor
	virtual ~Entity();

	/// Gets Entity's name
	const char* getName();

	/// Gets Entity's Base Damage
	double getBaseDMG();

	/// Gets Entity's Base Defense
	double getBaseDEF();

	/// Gets Entity's HP
	double getHP();

	/// Gets Entity's MaxHP
	double getMaxHP();

	/// Sets Entity's HP
	void setHP(const double hp);

	/// Displays the info of an Entity, dynamically controlable with an InfoPreset
	virtual std::ostream& getInfoEntity(InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout) = 0;
};

#endif //ENTITY_H

