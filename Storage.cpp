#include "Storage.h"

static InfoPreset AttackWithItem("Attack with ", 0, 0, 0, 0, 0); //stopped defining, because we need the only the attack to be 1
static InfoPreset AllInfoItem("Info of ", 1, 1, 1, 1, 0, 1, 1, 1); //all info of the item, except attacking
//static AllInfo("Info of ", 1, 0, 1, 1, 0, 0, 0, 1, 1); //all info of the item, except attacking

/// Default Constructor
Storage::Storage(const char* Name, const char* Desc, size_t MaxSize) : Name(Name), Desc(Desc), MaxSize(MaxSize), Items() { }

/// Copy Constructor
Storage::Storage(const Storage& S) : Name(S.Name), Desc(S.Desc), MaxSize(S.MaxSize), Items(S.Items) { }

/// Destructor
Storage::~Storage() { }

/// Gets number of Items in the of Storage
size_t Storage::getSize() { return Items.getSize(); }

/// Writes out the Storage's info to the console
std::ostream& Storage::getInfo(std::ostream& os) {
	os << "Storage Name: " << Name << std::endl;
	os << "Storage Description: " << Desc << std::endl;
	os << "Number Of Items: " << Items.getSize() << std::endl;
	os << "Storage Size: " << MaxSize << std::endl;
	return os;
}

/// Writes out the Item's infos in the Storage to the console
std::ostream& Storage::getInfoItems(InfoPreset IP, std::ostream& os) {
	for (size_t i = 0; i < Items.getSize(); i++) {
		os << i + 1 << ". ";
		Items[i].getInfoItems(IP, os);
	}
	return os;
}

/// Writes out a specific Item's infos in the Storage to the console
std::ostream& Storage::getInfoItems(const ItemType& Type, InfoPreset IP, std::ostream& os) {
	size_t num = 0;
	for (size_t i = 0; i < Items.getSize(); i++) {
		if (Items[i].getType() == Type) {
			num++;
			os << num << ". ";
			Items[i].getInfoItems(IP, os);
		}
	}
	return os;
}

/// Writes out the Item's infos in the Storage to the console
std::ostream& Storage::getInfoItemsAll(std::ostream& os) {
	for (size_t i = 0; i < Items.getSize(); i++) {
		os << i + 1 << ". ";
		Items[i].getInfoItems(AllInfoItem, os);
	}
	return os;
}

/// Writes out a specific Item's infos in the Storage to the console
std::ostream& Storage::getInfoItemsAll(const ItemType& Type, std::ostream& os) {
	size_t num = 0;
	for (size_t i = 0; i < Items.getSize(); i++) {
		if (Items[i].getType() == Type) {
			num++;
			os << num << ". ";
			Items[i].getInfoItems(AllInfoItem, os);
		}
	}
	return os;
}

/// Writes out the Item's infos in the Storage to the console
std::ostream& Storage::getInfoItemsUse(std::ostream& os) {
	for (size_t i = 0; i < Items.getSize(); i++) {
		os << i + 1 << ". ";
		Items[i].getInfoItems(AttackWithItem, os);
	}
	return os;
}

/// Writes out a specific Item's infos in the Storage to the console
std::ostream& Storage::getInfoItemsUse(const ItemType& Type, std::ostream& os) {
	size_t num = 0;
	for (size_t i = 0; i < Items.getSize(); i++) {
		if (Items[i].getType() == Type) {
			num++;
			os << num << ". ";
			Items[i].getInfoItems(AttackWithItem, os);
		}
	}
	return os;
}

/// Gets Name
const char* Storage::getName() { return Name.getStr(); }

/// Gets Description
const char* Storage::getDescription() { return Desc.getStr(); }

/// Gets size of Storage
size_t Storage::getMaxSize() { return MaxSize; }

/// Sets size of Storage
void Storage::setMaxSize(const size_t& SizeC) { MaxSize = SizeC; }

/// Gets the Item's array, though cannot modify it
GenericArray<Item> Storage::getItems() const { return Items; }

/// Returns if there are upgrades in the inventory
bool Storage::isThereUpgrade() {
	for (size_t i = 0; i < Items.getSize(); i++) {
		if (Items[i].getType() == ItemType::WSUpgrade)
			return true;
	}
	return false;
}

/// Adds an Item to the Storage
void Storage::add(const Item& Element) {
	if (Items.getSize() < MaxSize)
		Items.add(Element);
	else
		std::cout << Name << " is Full! (" << MaxSize << " Items are held)" << std::endl;
}

/// Removes an Item from the Storage according to its index
void Storage::remove(const size_t& Index) {
	if (Index < Items.getSize() && Index >= 0)
		Items.remove(Index);
	else
		std::cout << "Cannot remove the Item with this Index!" << std::endl;
}

/// Clears the Storage
void Storage::clear() { Items.clear(); }