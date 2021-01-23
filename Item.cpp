#include "Item.h"



/// Default Constructor
Item::Item(const ItemType Type, const char* Name, const char* Desc, const double& BonusDMG, const double& BonusDMGM, const double& BonusDEF, const double& BonusDEFM, const double& Heal) : Type(Type), Name(Name), Desc(Desc), BonusDMG(BonusDMG), BonusDMGM(BonusDMGM), BonusDEF(BonusDEF), BonusDEFM(BonusDEFM), Heal(Heal) { }

/// Destructor
Item::~Item() { }

/// Gets Name
const char* Item::getName() { return Name.getStr(); }

/// Gets Description
const char* Item::getDesc() { return Desc.getStr(); }

/// Gets Additive Bonus Damage of Item
double Item::getBonusDMG() { return BonusDMG; }

/// Gets Multiplied Bonus Damage of Item
double Item::getBonusDMGM() { return BonusDMGM; }

/// Gets Additive Bonus Defense of Item
double Item::getBonusDEF() { return BonusDEF; }

/// Gets Multiplied Bonus Defense of Item
double Item::getBonusDEFM() { return BonusDEFM; }

/// Gets Healing of Item
double Item::getHeal() { return Heal; }

/// Gets Type of Item
ItemType Item::getType() const { return Type; }

/// Writes out the Item's info to an output
std::ostream& Item::getInfoItems(InfoPreset Preset, std::ostream& os) {
	if(Preset.DisplayNum)
		os << Preset.Num + 1 << ". ";
	if (Type == ItemType::WeaponShield) {
		os << Preset.Pre << getName() << std::endl;
		if (Preset.Name) {
			os << "Weapon/Shield Name: " << getName() << std::endl;
			os << "Weapon/Shield Description: " << getDesc() << std::endl;
		}
		if (Preset.BaseDMG) {
			os << "Weapon/Shield Bonus Damage: " << getBonusDMG() << std::endl;
			os << "Weapon/Shield Bonus Damage Multiplier: " << getBonusDMGM() << std::endl;
		}
		if (Preset.BaseDEF) {
			os << "Weapon/Shield Bonus Defense: " << getBonusDEF() << std::endl;
			os << "Weapon/Shield Bonus Defense Multiplier: " << getBonusDEFM() << std::endl << std::endl;
		}
	}
	if (Type == ItemType::HealPotion) {
		os << Preset.Pre << getName() << std::endl;
		if (Preset.Name) {
			os << "Potion's Name: " << getName() << std::endl;
			os << "Potion's Description: " << getDesc() << std::endl;
		}
		if (Preset.HP) {
			os << "Potion's Healing: " << getHeal() << "HP" << std::endl << std::endl;
		}
		
	}
	return os;
}

/// Use an Item
UseCases Item::useItem(std::istream& is) {
	/// Use a Weapon/Shield
	if (Type == ItemType::WeaponShield) {
		size_t num = 0;
		size_t Upgrade = 0;
		size_t Drop = 0;
		size_t Info = 0;
		size_t Back = 0;
		/*if(PLYR.getStorageType().isThereUpgrade()) { // will make
			Upgrade = ++num;
			std::cout << num << ". Use an Item!" << std::endl;
		}*/
		Drop = ++num;
		std::cout << num << ". Drop " << getName() << std::endl;
		Info = ++num;
		std::cout << num << ". Get the Info of " << getName() << std::endl;
		Back = ++num;
		std::cout << num << ". Back" << std::endl;

		size_t Choice = 0;
		is >> Choice;

		//choices
		if (Choice) {
			if (Choice == 42)
				return UseCases::Quit;
			if (Drop == Choice)
				return UseCases::Drop;
			if (Upgrade == Choice)
				return UseCases::Upgrade;
			if (Info == Choice)
				return UseCases::Info;
			if (Back == Choice)
				return UseCases::Back;
		}
	}
	/// Use a Healing Potion
	if (Type == ItemType::HealPotion) {
		size_t num = 0;
		size_t Heal = 0;
		size_t Drop = 0;
		size_t Info = 0;
		size_t Back = 0;
		Heal = ++num;
		std::cout << num << ". Heal with " << getName() << std::endl;
		Drop = ++num;
		std::cout << num << ". Drop " << getName() << std::endl;
		Info = ++num;
		std::cout << num << ". Get the Info of " << getName() << std::endl;
		Back = ++num;
		std::cout << num << ". Back" << std::endl;

		size_t Choice = 0;
		is >> Choice;

		//choices
		if (Choice) {
			if (Choice == 42)
				return UseCases::Quit;
			if (Heal == Choice) {
				std::cout << "Consumed " << getName() << std::endl;
				return UseCases::Heal;
			}
			if (Drop == Choice)
				return UseCases::Drop;
			if (Info == Choice)
				return UseCases::Info;
			if (Back == Choice)
				return UseCases::Back;
		}
	}
	std::cout << "Please choose a valid action!" << std::endl;
	return UseCases::InvalidAction;
}
