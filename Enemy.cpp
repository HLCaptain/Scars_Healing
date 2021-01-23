#include "Enemy.h"
#include "Player.h"
#include <math.h>

/// Constructor
Enemy::Enemy(const char* Name, double HP, double MaxHP, double BaseDMG, double BaseDEF) : Entity(Name, HP, MaxHP, BaseDMG, BaseDEF) { }

/// Default Constructor
Enemy::Enemy(double HP, double MaxHP, double BaseDMG, double BaseDEF) : Entity("Enemy Name", HP, MaxHP, BaseDMG, BaseDEF) { }

/// Destructor
Enemy::~Enemy() { }

/// Attack Player without taking Damage from it
void Enemy::attackPlayer(Player& PLYR, Item WS) {
	std::cout << PLYR.getName() << " HP: " << PLYR.getHP() << " --> ";
	double EnemyAttackDMG = getBaseDMG() - tanh(((PLYR.getBaseDEF() + WS.getBonusDEF()) * WS.getBonusDEFM()) / (100)) * getBaseDMG();
	PLYR.setHP(PLYR.getHP() - EnemyAttackDMG);
	std::cout << PLYR.getHP() << " (" << EnemyAttackDMG * (-1) << " HP caused by " << getName() << ")" << std::endl;
}

/// Displays the info of an Enemy, dynamically controlable with an InfoPreset
std::ostream& Enemy::getInfoEntity(InfoPreset Preset, std::ostream& os) {
	if (Preset.DisplayNum)
		os << Preset.Num + 1 << ". ";
	os << Preset.Pre;
	if (Preset.Name)
		os << getName() << std::endl;
	if (Preset.HP)
		os << "\tHP: " << getHP() << "/" << getMaxHP() << std::endl;
	if (Preset.BaseDEF)
		os << "\tBase Defense: " << getBaseDEF() << std::endl;
	if (Preset.BaseDMG)
		os << "\tBase Damage: " << getBaseDMG() << std::endl;
	return os;
}
