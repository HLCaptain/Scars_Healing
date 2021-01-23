#ifndef INFOPRESET_H
#define INFOPRESET_H

#include "String.h"

/// A preset tool for displaying dynamic information about anything
class InfoPreset {
public:
	/// Displays Name
	bool Name;

	/// Displays HP of an Entity or Healing for a Potion
	bool HP;

	/// Displays BonusDMG and BonusDMGM of a Weapon/Shield or BaseDMG for an Entity
	bool BaseDMG;

	/// Displays BonusDEF and BonusDEFM of a Weapon/Shield or BaseDEF for an Entity
	bool BaseDEF;

	/// Displays a given number, like the index of an Enemy before its Name
	bool DisplayNum;

	/// A String, which is displayed before everything, it can give some context
	String Pre;

	/// Displays the Player's Gold
	bool Gold;

	/// Displays the Player's Storage
	bool Storage;

	/// Displays the Player's Storage's Items
	bool Items;

	/// If DisplayNum is TRUE, then it displays this Number
	size_t Num;

	/// Constructor
	InfoPreset(const char* cPre = "", bool Name = true, bool HP = true, bool BaseDMG = true, bool BaseDEF = true, bool DisplayNum = false, bool Gold = true, bool Storage = true, bool Items = true, const size_t& dNum = 0) : Name(Name), HP(HP), BaseDMG(BaseDMG), BaseDEF(BaseDEF), DisplayNum(DisplayNum), Pre(cPre), Gold(Gold), Storage(Storage), Items(Items), Num(dNum) { }

	/// Destructor
	virtual ~InfoPreset() { }
};

#endif // INFOPRESET_H