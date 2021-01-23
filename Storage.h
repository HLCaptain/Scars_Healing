#ifndef STORAGE_H
#define STORAGE_H

#include "String.h"
#include "Item.h"
#include "GenericArray.h"

/// A Storage is able to store Items, but to a limited extent (MaxSize). Also has a Name and a Description.
class Storage {
public:
	/// Name of the Storage
	String Name;

	/// Description of the Storage
	String Desc;

	/// Size of Storage, how many Item it can hold
	size_t MaxSize;

	/// Items in the Storage
	GenericArray<Item> Items;
public:
	/// Default Constructor
	Storage(const char* Name = "BakPak", const char* Desc = "This is a BakPak.", size_t MaxSize = 5);

	/// Copy Constructor
	Storage(const Storage& S);

	/// Destructor
	virtual ~Storage();

	/// Writes out the Storage's info to the console
	std::ostream& getInfo(std::ostream& os = std::cout);

	/// Writes out the Item's infos in the Storage to the console
	std::ostream& getInfoItems(InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout);

	/// Writes out a specific Item's infos in the Storage to the console
	std::ostream& getInfoItems(const ItemType& Type, InfoPreset Preset = InfoPreset(), std::ostream& os = std::cout);

	/// Writes out the Item's infos in the Storage to the console
	std::ostream& getInfoItemsAll(std::ostream& os = std::cout);

	/// Writes out a specific Item's infos in the Storage to the console
	std::ostream& getInfoItemsAll(const ItemType& Type, std::ostream& os = std::cout);

	/// Writes out the Item's infos in the Storage to the console
	virtual std::ostream& getInfoItemsUse(std::ostream& os = std::cout);

	/// Writes out a specific Item's infos in the Storage to the console
	virtual std::ostream& getInfoItemsUse(const ItemType& Type, std::ostream& os = std::cout);

	/// Gets Name
	const char* getName();

	/// Gets Description
	const char* getDescription();

	/// Gets the Item's array, though cannot modify it
	GenericArray<Item> getItems() const;

	/// Adds an Item to the Storage
	void add(const Item& Element);

	/// Removes an Item from the Storage according to its index
	void remove(const size_t& Index);

	/// Clears the Storage
	void clear();

	/// Gets size of Storage
	size_t getMaxSize();

	/// Gets number of Items in the of Storage
	size_t getSize();

	/// Sets size of Storage
	void setMaxSize(const size_t& SizeC);

	/// Returns if there are upgrades in the inventory
	bool isThereUpgrade();

	/// Accessing an Item as constant
	Item& operator[](size_t Index) const { return Items[Index]; }

	/// Accessing an Item
	Item& operator[](size_t Index) { return Items[Index]; }
};

#endif //STORAGE_H

