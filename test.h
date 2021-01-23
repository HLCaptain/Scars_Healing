#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <fstream>

#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "IniGame.h"
#include "Actions.h"
#include "Storage.h"
#include "GenericArray.h"
#include <sstream>

/// Basic Constructing tests
void test();

/// Initiates everything, then deletes it xd
void iniTest();

/// Tests if iniWS worked properly
void iniWSTest(GenericArray<Item>& WSItems);

#endif // TEST_H
