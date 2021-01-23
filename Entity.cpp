#include "Entity.h"

/// Constructor
Entity::Entity(const char* Name, double HP, double MaxHP, double BaseDMG, double BaseDEF) : Name(Name), HP((MaxHP < HP) ? MaxHP : HP), MaxHP(MaxHP), BaseDMG(BaseDMG), BaseDEF(BaseDEF) { }

/// Default Constructor
Entity::Entity(double HP, double MaxHP, double BaseDMG, double BaseDEF) : Name("Player Name"), HP((MaxHP < HP) ? MaxHP : HP), MaxHP(MaxHP), BaseDMG(BaseDMG), BaseDEF(BaseDEF) { }

/// Destructor
Entity::~Entity() { }

/// Gets Entity's name
const char* Entity::getName() { return Name.getStr(); }

/// Gets Entity's Base Damage
double Entity::getBaseDMG() { return BaseDMG; }

/// Gets Entity's Base Defense
double Entity::getBaseDEF() { return BaseDEF; }

/// Gets Entity's HP
double Entity::getHP() { return HP; }

/// Gets Entity's MaxHP
double Entity::getMaxHP() { return MaxHP; }

/// Sets Entity's HP
void Entity::setHP(const double hp) { HP = hp; }
