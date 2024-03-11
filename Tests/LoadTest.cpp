/**
 * @file LoadTest.cpp
 * @author Mitchell Bjorne
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>

class LoadFunctionTest : public ::testing::Test
{
protected:
    void TestLoad(int levelNum, int expectedItemsSize, int expectedDeclarationsSize)
    {
        Game game(nullptr);
        game.Load(levelNum);

        ASSERT_EQ(game.GetItemsSize(), expectedItemsSize) << "Incorrect number of items loaded for level: " << levelNum;
        ASSERT_EQ(game.GetDeclarationsSize(), expectedDeclarationsSize)
                            << "Incorrect number of declarations loaded for level: " << levelNum;
    }
};

TEST_F(LoadFunctionTest, LoadLevel0)
{
    int levelNum = 0;
    int expectedItemsSize = 4;
    int expectedDeclarationsSize = 12;
    TestLoad(levelNum, expectedItemsSize, expectedDeclarationsSize);
}

TEST_F(LoadFunctionTest, LoadLevel1)
{
    int levelNum = 1;
    int expectedItemsSize = 6;
    int expectedDeclarationsSize = 14;
    TestLoad(levelNum, expectedItemsSize, expectedDeclarationsSize);
}
