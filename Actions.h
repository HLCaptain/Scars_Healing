#ifndef ACTIONS_H
#define ACTIONS_H

#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "GenericArray.h"

/// States
enum class ActionEnums { DecidePhase, WeaponSelection, EnemySelection, ItemSelection, PlayerDead, Quit, EnemiesDead };

/// Gets the number of the Item, the Player has chosen
size_t getWSNum(Player& PLYR, ActionEnums& ActionState, std::istream& is = std::cin);

/// Player Chooses an enemy to attack, Enemy and Player can die
ActionEnums attackSeq(Player& PLYR, GenericArray<Enemy>& Enemies, Item& CWS, std::istream& is = std::cin);

/// Decide the Action you want to make
ActionEnums decideSeq(Player& PLYR, const size_t& EnemyNum, std::istream& is = std::cin);

/// Statemachine of an Action
void actionSeq(Player& PLYR, GenericArray<Enemy>& Enemies, std::istream& is = std::cin);

#endif //ACTIONS_H

