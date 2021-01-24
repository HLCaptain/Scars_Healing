#include <iostream>
#include <fstream>

#include "gtest_lite.h"
#include "memtrace.h"
#include "test.h"
#include "IniGame.h"

//#define MEMTRACE

/*!
 * \brief Scars Healing Game Test
 * \details This is a game where you can fight an enemy or two.
Also, you can use items, and attack with weapons. Choose your strategy, 
because everytime you strike, the enemy strikes as well!
Don't forget to heal and play clever! Have fun!
 * \author Balázs Püspök-Kiss
 * \version Test 1.0
 * \date 2020/05/17
 * 
 *
 *
 *
 *
 *
 *
 */

#define TESTING

/// Well, here we go...
int main() {
	GTINIT(std::cin); // Needed for JPorta
#ifdef TESTING
	test();
#endif
	GTEND(std::cerr); // Needed for JPorta
	system("pause");
	// Just testing out the git.
	// Testing git again lul, now testing pull requests.
	return 0;
}