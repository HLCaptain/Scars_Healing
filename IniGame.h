#ifndef INIGAME_H
#define INIGAME_H

#include "Item.h"
#include "GenericArray.h"

/// Initializing WeaponShield Items from a file
GenericArray<Item> iniWS(const char* WSPath = "WeaponShield.dat");

#endif //INIGAME_H
