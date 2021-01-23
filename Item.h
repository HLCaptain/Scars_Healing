#ifndef ITEM_H
#define ITEM_H

#include "String.h"
#include "InfoPreset.h"
#include "GenericArray.h"

/// Types of an Item
enum class ItemType { WeaponShield, HealPotion, Vanity, WSUpgrade };

/// Usecases of an Item
enum class UseCases { Upgrade, Drop, Use, Back, Quit, Info, InvalidAction, Heal };

/// An Item can be stored in a storage and also has a type. Depending on the type, an Item can heal the player or damage an enemy, etc.
class Item {
protected:
	/// Type of the Item
	ItemType Type;

	/// Name of the Item
	String Name;

	/// Description of the Item
	String Desc;

	/// Additive Bonus Damage of Item
	double BonusDMG;

	/// Multiplied Bonus Damage of Item
	double BonusDMGM;

	/// Additive Bonus Defense of Item
	double BonusDEF;

	/// Multiplied Bonus Defense of Item
	double BonusDEFM;

	/// Healing of Item
	double Heal;
public:
	/// Default Constructor
	Item(const ItemType Type = ItemType::WeaponShield, const char* Name = "DisItem", const char* Desc = "This is an Item.", const double& BonusDMG = 0, const double& BonusDMGM = 1, const double& BonusDEF = 0, const double& BonusDEFM = 1, const double& Heal = 0);

	/// Destructor
	virtual ~Item();

	/// Writes out the Item's info to an output
	virtual std::ostream& getInfoItems(InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout);

	/// Gets Name
	const char* getName();

	/// Gets Description
	const char* getDesc();

	/// Gets Additive Bonus Damage of Item
	double getBonusDMG();

	/// Gets Multiplied Bonus Damage of Item
	double getBonusDMGM();

	/// Gets Additive Bonus Defense of Item
	double getBonusDEF();

	/// Gets Multiplied Bonus Defense of Item
	double getBonusDEFM();

	/// Gets Healing of Item
	double getHeal();

	/// Gets Type of Item
	ItemType getType() const;

	/// Use an Item
	UseCases useItem(std::istream& is = std::cin);
};

/// Predicatum, which determines if an item in an array has a specific attribute.
template<class C>
class AttributeCheck {
	/// Attribute of some class
	C Attribute;
public:
	/// Default Constructor
	AttributeCheck(C Attribute) : Attribute(Attribute) { }

	/// Decides if the attribute is equal
	bool operator()(const C& c) {
		return c == Attribute;
	}

	/// Checks if the type of an Item is something
	bool operator()(const Item& c) {
		return c.getType() == Attribute;
	}
};

#endif //ITEM_H

