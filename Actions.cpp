#include "Actions.h"
#include <typeinfo>
#include "Item.h"
#include "Enemy.h"
#include "Player.h"

/// Global Variables
InfoPreset EnemyAttackBasic("Attack ", 1, 0, 0, 0, 1, 0, 0, 0);
InfoPreset EnemyAttack("Attack ", 1, 1, 1, 1, 1, 0, 0, 0);
Storage World("World", "World storage", 20);

/// Gets the number of the Weapon/Shield, the Player has chosen
size_t getWSNum(Player& plyr, ActionEnums& actionState, std::istream& is) {
	size_t ChosenItem = 0;
	if (plyr.getStorageType().getSize() == 0) {
		std::cout << "No items in inventory :(" << std::endl;
		actionState = ActionEnums::DecidePhase;
		return 0;
	}
	while (ChosenItem > plyr.getStorageType().getItems().getPredNum(AttributeCheck<ItemType>(ItemType::WeaponShield)) || ChosenItem <= 0) {
		plyr.getStorageType().getInfoItemsUse(ItemType::WeaponShield);
		std::cout << plyr.getStorageType().getItems().getPredNum(AttributeCheck<ItemType>(ItemType::WeaponShield)) + 1 << ". Back" << std::endl;
		std::cout << "Enter 42 to QUIT" << std::endl;
		is >> ChosenItem;
		if (ChosenItem == 42) {
			actionState = ActionEnums::Quit;
			return 0;
		}
			
		if (ChosenItem > plyr.getStorageType().getItems().getPredNum(AttributeCheck<ItemType>(ItemType::WeaponShield)) + 1 || ChosenItem <= 0) { std::cout << "Select a right Item!" << std::endl; }
		if (ChosenItem == plyr.getStorageType().getItems().getPredNum(AttributeCheck<ItemType>(ItemType::WeaponShield)) + 1) {
			actionState = ActionEnums::DecidePhase;
			return 0;
		}
	}
	actionState = ActionEnums::EnemySelection;
	return ChosenItem; //the not index value because of the 0 check
}

/// Player Chooses an enemy to attack, Enemy and Player can die
ActionEnums attackSeq(Player& PLYR, GenericArray<Enemy>& enemies, Item& cws, std::istream& is) {
	size_t ChosenEnemy = 0;
	while (ChosenEnemy > enemies.getSize() || ChosenEnemy <= 0) {
		// Input
		for (size_t i = 0; i < enemies.getSize(); i++) {
			EnemyAttackBasic.Num = i;
			enemies[i].getInfoEntity(EnemyAttackBasic, std::cout);
		}
			//enemies[i].getInfoEntity(std::cout, 1, 0, 0, 0, 1, 1, 1, i);
		std::cout << enemies.getSize() + 1 << ". Back" << std::endl;
		std::cout << "Enter 42 to QUIT" << std::endl;
		is >> ChosenEnemy;

		// Processing Input
		if (ChosenEnemy == 42) // Quit
			return ActionEnums::Quit;
		if (ChosenEnemy == enemies.getSize() + 1) // Back to Weapon Selection
			return ActionEnums::WeaponSelection;
		Enemy& CEnemy = enemies[ChosenEnemy-1];
		if (ChosenEnemy > 0 && ChosenEnemy <= enemies.getSize()) {
			PLYR.attackEnemy(CEnemy, cws);
			for (size_t i = 0; i < enemies.getSize(); i++) { // everytime the player attacks, enemies attack the player as well...
				if (i != ChosenEnemy - 1)
					enemies[i].attackPlayer(PLYR, cws);
			}
			if (PLYR.getHP() <= 0) { // if player died
				std::cout << PLYR.getName() << " died by the final swing of " << CEnemy.getName() << std::endl;
				return ActionEnums::PlayerDead;
			}
			if (CEnemy.getHP() <= 0) { // if player killed an enemy
				std::cout << PLYR.getName() << " Slayed " << CEnemy.getName() << std::endl;
				enemies.remove(ChosenEnemy - 1);
			}
			if (enemies.getSize() == 0) { // if player killed all enemies
				std::cout << PLYR.getName() << " just completed the Demo!" << std::endl;
				return ActionEnums::Quit;
			}
		}
		else
			std::cout << PLYR.getName() << " did not attack... Choose a correct Opponent!" << std::endl; // wrong input
	}
	return ActionEnums::EnemySelection;
}

/// Decide the Action you want to make
ActionEnums decideSeq(Player& PLYR, const size_t& EnemyNum, std::istream& is) {
	size_t num = 0;
	size_t UseItem = 0;
	size_t AttackE = 0;
	size_t Info = 0;
	//size_t PickUp = 0; //Not used as of right now
	
	if (EnemyNum) {
		AttackE = ++num;
		std::cout << num << ". Attack an Enemy!" << std::endl;
	}
	if (PLYR.getStorageType().getSize()) {
		UseItem = ++num;
		std::cout << num << ". Use an Item!" << std::endl;
	}
	Info = ++num;
	std::cout << num << ". Get the Info of EVERYTHING!" << std::endl;
	// If world is not empty
	if (World.getSize()) {
		
		for (size_t i = num; i < World.getSize() + num; i++) {
			InfoPreset PickUp("Pick Up ", 0, 0, 0, 0, 1, 0, 0, 0, i);
			World[i - num].getInfoItems(PickUp, std::cout);
		}
	}
	if (!num) {
		std::cout << "Nothing to Do! Enjoy Real life :)" << std::endl;
		return ActionEnums::Quit;
	}
	std::cout << "Enter 42 to QUIT" << std::endl;

	size_t Choice = 0;
	is >> Choice;
	
	//choices
	if (Choice) {
		if (Choice == 42)
			return ActionEnums::Quit;
		if (AttackE == Choice)
			return ActionEnums::WeaponSelection;
		if (Choice <= num + World.getSize() && Choice > num) {
			std::cout << "Picked Up " << World[Choice - num - 1].getName() << std::endl;
			PLYR.getStorageType().add(World[Choice - num - 1]);
			World.remove(Choice - num - 1);
			return ActionEnums::DecidePhase;
		}
			
		if (UseItem == Choice)
			return ActionEnums::ItemSelection;
		if (Info == Choice) {
			InfoPreset AllInfoItem("Info of ", 1, 1, 1, 1, 0, 0, 1, 1, 1);
			PLYR.getInfoEntity(AllInfoItem, std::cout);
			return ActionEnums::DecidePhase;
		}
	}
	std::cout << "Please choose a valid action!" << std::endl;
	return ActionEnums::DecidePhase;
}

/// Selection of an Item from the inventory
ActionEnums itemSeq(Player& PLYR, std::istream& is) {
	InfoPreset Use("Use ", 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if (!PLYR.getStorageType().getSize()) {
		std::cout << "No Items in Inventory!" << std::endl;
		return ActionEnums::DecidePhase;
	}
	std::cout << "Choose an Item!" << std::endl;
	PLYR.getStorageType().getInfoItems(Use, std::cout);
	std::cout << PLYR.getStorageType().getSize() + 1 << ". Back" << std::endl;
	std::cout << "Enter 42 to QUIT" << std::endl;
	// Input
	size_t ChosenItem;
	is >> ChosenItem;
	if (ChosenItem == 42)
		return ActionEnums::Quit;
	if (ChosenItem == PLYR.getStorageType().getSize() + 1)
		return ActionEnums::DecidePhase;

	if (ChosenItem > PLYR.getStorageType().getSize() || ChosenItem <= 0) {
		std::cout << "Choose a Valid Item!" << std::endl;
		return ActionEnums::ItemSelection;
	}

	// Processing Input
	UseCases UC = PLYR.getStorageType()[ChosenItem - 1].useItem(is);
	if (UC == UseCases::Use)
		return ActionEnums::ItemSelection;
	if (UC == UseCases::Back)
		return ActionEnums::ItemSelection;
	if (UC == UseCases::Drop) {
		World.add(PLYR.getStorageType()[ChosenItem - 1]);
		PLYR.getStorageType().remove(ChosenItem - 1);
		return ActionEnums::ItemSelection;
	}

	if (UC == UseCases::Heal) { // Healing Player and then removing the CONSUMABLE Item (DOTO: MAKE CONSUMABLES (BOOL, DOUBLE FOR QUANTITY))
		PLYR.Heal(ChosenItem - 1);
		return ActionEnums::ItemSelection;
	}
		
	if (UC == UseCases::InvalidAction) {
		std::cout << "Choose a Valid Action!" << std::endl;
		return ActionEnums::ItemSelection;
	}
	if (UC == UseCases::Upgrade)
		return ActionEnums::ItemSelection;
	if (UC == UseCases::Info) {
		PLYR.getStorageType()[ChosenItem - 1].getInfoItems();
		return ActionEnums::ItemSelection;
	}
	return ActionEnums::DecidePhase;
}

/// Statemachine of an Action
void actionSeq(Player& PLYR, GenericArray<Enemy>& Enemies, std::istream& is) {
	//Initializing Default Values
	Item DefaultWS(ItemType::WeaponShield);
	Item DefaultPotion(ItemType::HealPotion);

	

	ActionEnums ActionState = ActionEnums::DecidePhase; //CHANGE TO DECIDEPHASE LATER ON

	//Getting action
	std::cout << "What do You do?" << std::endl;
	for (size_t i = 0; i < Enemies.getSize(); i++) {
		EnemyAttack.Num = i;
		Enemies[i].getInfoEntity();
	}


	Item CWS; //NOT PERMANENT, IT IS AN ITEM

	bool EndAction = false;
	while (!EndAction) {
		switch (ActionState) {
			case ActionEnums::DecidePhase: {
				ActionState = decideSeq(PLYR, Enemies.getSize(), is);
				break;
			}
			case ActionEnums::WeaponSelection: {
				size_t ChosenItem = getWSNum(PLYR, ActionState, is);
				if (ActionState == ActionEnums::DecidePhase || ActionState == ActionEnums::Quit || ActionState == ActionEnums::WeaponSelection) {
					break;
				}
				CWS = PLYR.getStorageType()[--ChosenItem]; //ChosenItem -1 because of the indexing
				//if (typeid(PLYR.getStorageType().getItems()[ChosenItem]) == typeid(DefaultWS))
					//ActionState = ActionEnums::EnemySelection;
				break;
			}
			case ActionEnums::EnemySelection: {
				ActionState = attackSeq(PLYR, Enemies, CWS, is);
				break;
			}
			case ActionEnums::ItemSelection: {
				//std::cout << "USING AN ITEM IS NOT AN OPTION YET YOU DEFENSIVE RETARD" << std::endl;
				ActionState = itemSeq(PLYR, is);
				break;
			}
			case ActionEnums::PlayerDead: {
				std::cout << "RIP BRUH" << std::endl;
				EndAction = true;
				break;
			}
			case ActionEnums::Quit: {
				std::cout << "Quitting, Hope you enjoyed the Demo!" << std::endl;
				EndAction = true;
				break;
			}
			case ActionEnums::EnemiesDead: {
				std::cout << "Well, nothing to do Here!" << std::endl;
				EndAction = true;
				break;
			}
		}
	}
}

// TEST THE STATE MACHINE TO MAKE IT WORK PROPERLY
