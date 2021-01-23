#include "test.h"
#include "gtest_lite.h"
#include "memtrace.h"

#define TESTING
//#define MEMTRACE

/// Basic Constructing tests
void test() {
	Storage Test("Adventure Backpack", "Classic backpack for adventures, light, but can carry some items as well.", 10);
	//static Storage World("World", "World", 20);
#ifdef TESTING
	/// Ask for test
#ifdef CPORTA
	String TestInput("3\n2\n5\n1\n4\n2\n4\n1\n4\n1\n4\n4\n1\n1\n1\n1\n1\n1");
#else
	String TestInput("3 2 5 1 4 2 4 1 4 1 4 4 1 1 1 1 1 1");
#endif
	std::stringstream ss;
	ss << TestInput;
	std::cout << "Do you want to test?\nYes(1), No(0)" << std::endl;
	bool test;
	std::cin >> test;
	if (test) {
		std::cout << "test begin" << std::endl;
		TEST(PlayerTest, Sanity) { /// Checking if initialized well
			Player RandomPlayer;
			EXPECT_STREQ("Player Name", RandomPlayer.getName());
			EXPECT_EQ(size_t(100), RandomPlayer.getHP());
			EXPECT_EQ(size_t(100), RandomPlayer.getMaxHP());
			EXPECT_EQ(size_t(5), RandomPlayer.getBaseDMG());
			EXPECT_EQ(size_t(5), RandomPlayer.getBaseDEF());
			EXPECT_EQ(size_t(0), RandomPlayer.getGold());
		} ENDMsg("Bad Player Attributes\n")
	
		TEST(EnemyTest, Sanity) { /// Checking if initialized well
			Enemy RandomEnemy;
			EXPECT_STREQ("Enemy Name", RandomEnemy.getName());
			EXPECT_EQ(size_t(100), RandomEnemy.getHP());
			EXPECT_EQ(size_t(100), RandomEnemy.getMaxHP());
			EXPECT_EQ(size_t(5), RandomEnemy.getBaseDMG());
			EXPECT_EQ(size_t(5), RandomEnemy.getBaseDEF());
		} ENDMsg("Bad Enemy Attributes\n")
	
		TEST(PlayerTest, AttackEnemy) {
			Enemy RandomEnemy;
			Player RandomPlayer;
			RandomPlayer.attackEnemy(RandomEnemy); /// Attacking the Enemy
			EXPECT_GT(RandomEnemy.getMaxHP(), RandomEnemy.getHP());
			EXPECT_GT(RandomPlayer.getMaxHP(), RandomPlayer.getHP());
		} ENDMsg("Attack of Player is implemented bad.\n")
	
		TEST(PlayerTest, AttackEnemy) {
			Enemy RandomEnemy;
			Player RandomPlayer;
			RandomEnemy.attackPlayer(RandomPlayer); /// Attacking the Player
			EXPECT_EQ(RandomEnemy.getMaxHP(), RandomEnemy.getHP());
			EXPECT_GT(RandomPlayer.getMaxHP(), RandomPlayer.getHP());
		} ENDMsg("Attack of Enemy is implemented bad.\n")
	
		TEST(PlayerTest, InventoryTests) {
			Item LevanderEssence(ItemType::HealPotion, "Levander Essence", "Extracted serum of a Levander, grew in the Alpine Mountains.", 0, 0, 0, 0, 50);
			Player RandomPlayer("Bruh", 100, 150, 10, 10, 10);
			Item RandomWeapon;
			RandomPlayer.getStorageType().add(LevanderEssence);
			EXPECT_STREQ("Levander Essence", LevanderEssence.getName());
			EXPECT_EQ(size_t(50), LevanderEssence.getHeal());
			EXPECT_EQ(size_t(1), RandomPlayer.getStorageType().getSize());
			EXPECT_GT(RandomPlayer.getMaxHP(), RandomPlayer.getHP());
			RandomPlayer.Heal(0);
			EXPECT_EQ(RandomPlayer.getMaxHP(), RandomPlayer.getHP());
			EXPECT_EQ(size_t(0), RandomPlayer.getStorageType().getSize());
		} ENDMsg("Inventory system is implemented bad.\n")
		std::cout << std::endl;
	}
	Player PlayerIllyan("Illyan (the player)", 300, 300, 25, 25, 0, Test);
	Enemy E1("Mastermind (the enemy)", 100000, 99, 50, 50);
	//PlayerIllyan.getInfoEntity(); //writing out info of player
	//E1.getInfoEntity(); //writing out info of enemy
	//PlayerIllyan.getStorageType().getInfo(); //writing out info of bakpak
	//PlayerIllyan.attackEnemy(E1); //attacking e1
	//PlayerIllyan.getInfoEntity(); //writing out info of player, hp changed
	//E1.getInfoEntity(); //writing out info of enemy, hp changed
#else
	String PName, EName;
	std::cout << "Player Name: " << std::endl;
	std::cin >> PName;
	std::cout << "Enemy Name: " << std::endl;
	std::cin >> EName;
	Player PlayerIllyan(PName.getStr(), 300, 300, 10, 10, 42, Test);
	Enemy E1(EName.getStr(), 100000, 99, 50, 50);
#endif
	Item LevanderEssence(ItemType::HealPotion, "Levander Essence", "Extracted serum of a Levander, grew in the Alpine Mountains.", 0, 0, 0, 0, 50);

	//Adding a weapon
	GenericArray<Item> WSItems = iniWS();
	WSItems.add(LevanderEssence);
#ifdef TESTING
	//Item WS(ItemType::WeaponShield, "Sword Of Blaise", "This epic sword lets you change the world, but you have to let it guide your way.", 50, 1.2, 20, 1.2);
	//WSItems.add(WS);
	//iniWSTest(WSItems);
#endif
	GenericArray<Enemy> Enemies;
	Enemies.add(E1);
	Enemies.add(E1);
	
	for (size_t i = 0; i < WSItems.getSize(); i++) {
		//World.add(WSItems[i]);
		PlayerIllyan.getStorageType().add(WSItems[i]);
	}
	if (test) {
#ifdef CPORTA
		actionSeq(PlayerIllyan, Enemies, ss);
#else
		TEST(Game, GameTest) {
			actionSeq(PlayerIllyan, Enemies, ss);
			EXPECT_TRUE(ss.eof());
		} ENDMsg("Something is wrong with the gametest...")
#endif
		std::cout << std::endl << "Test input was: \"" << TestInput << "\"" << std::endl;
	} else
		actionSeq(PlayerIllyan, Enemies);
	
#ifdef TESTING
	/*PlayerIllyan.getStorageType().getInfoItems();
	for (size_t i = 0; i < 4; i++) {
		PlayerIllyan.attackEnemy(E1, WS);
	}*/
#else
	actionSeq(PlayerIllyan, Enemies);
#endif
}

/// Tests if iniWS worked properly
void iniWSTest(GenericArray<Item>& WSItems) {
	for (size_t i = 0; i < WSItems.getSize(); i++)
	{
		WSItems[i].getInfoItems();
	}
}

/// Initiates everything, then deletes it xd
void iniTest() {
	//Initialization test on Weapons/Shield Items
	//size_t NumWS;
	GenericArray<Item> WSItems = iniWS();
	iniWSTest(WSItems);
}