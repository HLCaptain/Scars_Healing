#include "IniGame.h"
#include "Item.h"
#include <fstream>
#include <iostream>

/// Initializing WeaponShield Items from a file
GenericArray<Item> iniWS(const char* WSPath) {
	std::ifstream WSFile;
	WSFile.open(WSPath);
	GenericArray<Item> WSItems;
	if (WSFile.good()) {
		// Additive Bonus Damage of Sword or Shield
		double WBonusDMG;

		// Multiplied Bonus Damage of Sword or Shield
		double WBonusDMGM;

		// Additive Bonus Defense of Sword or Shield
		double WBonusDEF;

		// Multiplied Bonus Defense of Sword or Shield
		double WBonusDEFM;

		// Name of the Item
		char* WName = new char[256];

		// Description of the Item
		char* WDesc  = new char[256];

		while (WSFile.good()) {
			WSFile.getline(WName, 256);

			//Reading WDesc
			WSFile.getline(WDesc, 256);

			//Reading WBonusDMG
			WSFile >> WBonusDMG;

			//Reading WBonusDMGM
			WSFile >> WBonusDMGM;

			//Reading WBonusDEF
			WSFile >> WBonusDEF;

			//Reading WBonusDEFM
			WSFile >> WBonusDEFM;
#ifdef CPORTA
			WSFile.ignore(2); // Because of \r\n on Linux
#else
			WSFile.ignore(1); // Because of \n on Windows
#endif

			// Construct WeaponShield
			Item WS(ItemType::WeaponShield, WName, WDesc, WBonusDMG, WBonusDMGM, WBonusDEF, WBonusDEFM);
			
			WSItems.add(WS);

			//WSItems[NumberOfItems-1] = WS; //Copying WeaponShield
			std::cout << WName << " loaded in." << std::endl; //TEST
		}
		delete[] WName;
		delete[] WDesc;
		WSFile.close();
		std::cout << std::endl;
		return WSItems;
	}
	else {
		std::cout << "Unable to load the Weapon/Shield Items" << std::endl;
	}
	WSFile.close();
	GenericArray<Item> Something;
	return Something;
}