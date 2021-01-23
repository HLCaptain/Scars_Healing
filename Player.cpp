#include "Player.h"
#include "String.h"
#include <math.h>
#include "Enemy.h"

/// Constructor
Player::Player(const char* Name, double HP, double MaxHP, double BaseDMG, double BaseDEF, size_t Gold, Storage StorageType) : Entity(Name, HP, MaxHP, BaseDMG, BaseDEF), Gold(Gold), StorageType(StorageType) { }

/// Default Constructor
Player::Player(double HP, double MaxHP, double BaseDMG, double BaseDEF, size_t Gold) : Entity(HP, MaxHP, BaseDMG, BaseDEF), Gold(Gold) { }

/// Destructor
Player::~Player() { }

/// Writes out the Player's info to an output
std::ostream& Player::getInfoEntity(InfoPreset Preset, std::ostream& os) {
	if (Preset.Name)
		os << getName() << std::endl;
	if (Preset.HP)
		os << "\tPlayer HP: " << getHP() << "/" << getMaxHP() << std::endl;
	if (Preset.BaseDEF)
		os << "\tBase Defense: " << getBaseDEF() << std::endl;
	if (Preset.BaseDMG)
		os << "\tPlayer Base Damage: " << getBaseDMG() << std::endl;
	if (Preset.Gold)
		os << "\tPlayer Gold: " << getGold() << std::endl;
	if (Preset.Storage)
		os << "\tPlayer Storage: " << getStorageType().getName() << std::endl;
	if (Preset.Items) {
		os << "\tPlayer Items:";
		if (getStorageType().getSize() == 0)
			os << " None :(" << std::endl << std::endl;
		else
		{
			os << std::endl << std::endl;
			getStorageType().getInfoItemsAll(os);
		}
	}
	return os;
}

/// Gets Player's amount of Gold
size_t Player::getGold() { return Gold; }

/// Gets Player's type of Storage
Storage& Player::getStorageType() { return StorageType; }

/// Attack an Enemy
void Player::attackEnemy(Enemy& e) {
	std::cout << getName() << " HP: " << getHP() << " --> ";
	double EnemyAttackDMG = e.getBaseDMG() - tanh((getBaseDEF()) / (100)) * e.getBaseDMG();
	setHP(getHP() - EnemyAttackDMG);
	std::cout << getHP() << " (" << EnemyAttackDMG * (-1) << " HP)" << std::endl;


	double PlayerAttackDMG = getBaseDMG() - tanh(e.getBaseDEF() / (100)) * getBaseDMG();
	std::cout << e.getName() << " HP: " << e.getHP() << " --> ";
	e.setHP(e.getHP() - PlayerAttackDMG);
	std::cout << e.getHP() << " (" << PlayerAttackDMG * (-1) << " HP by Hand)" << std::endl;
}

/// Healing with an Item
void Player::Heal(const size_t Index) {
	double OldHP = getHP();
	std::cout << getName() << " HP: " << getHP() << " --> ";
	if (getHP() + getStorageType().getItems()[Index].getHeal() < getMaxHP())
		setHP(getHP() + getStorageType().getItems()[Index].getHeal());
	else
		setHP(getMaxHP());
	std::cout << getHP() << "/" << getMaxHP() << " (Healed " << getHP()-OldHP << "HP)" << std::endl;
	//if(getStorageType().getItems()[Index].getConsumable())						//TODO
		getStorageType().remove(Index);
}

/// Attack an Enemy with a Weapon/Shield
void Player::attackEnemy(Enemy& e, Item& WS) {
	std::cout << getName() << " HP: " << getHP() << " --> ";
	double PlayerOldHP = getHP();
	double PlayerNewHP = (getHP() - e.getBaseDMG() + tanh(((getBaseDEF() + WS.getBonusDEF()) * WS.getBonusDEFM()) / (100)) * e.getBaseDMG());
	setHP(PlayerNewHP);
	std::cout << getHP() << " (" << PlayerNewHP - PlayerOldHP << " HP)" << std::endl;

	std::cout << e.getName() << " HP: " << e.getHP() << " --> ";
	double EnemyOldHP = e.getHP();
	double EnemyNewHP = (e.getHP() - ((getBaseDMG() + WS.getBonusDMG()) * WS.getBonusDMGM()) + tanh(e.getBaseDEF() / (100)) * ((getBaseDMG() + WS.getBonusDMG()) * WS.getBonusDMGM()));
	e.setHP(EnemyNewHP);
	std::cout << e.getHP() << " (" << EnemyNewHP - EnemyOldHP << " HP by " << WS.getName() << ")" << std::endl;
}
