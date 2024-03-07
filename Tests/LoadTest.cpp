/**
 * @file LoadTest.cpp
 * @author Mitchell Bjorne
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>

class LoadFunctionTest : public ::testing::Test {
protected:
    void TestLoad(const wxString& levelFile, int expectedItemsSize, int expectedDeclarationsSize) {
        Game game(nullptr);
        game.Load(levelFile);

        ASSERT_EQ(game.GetItemsSize(), expectedItemsSize) << "Incorrect number of items loaded for level: " << levelFile.ToStdString();
        ASSERT_EQ(game.GetDeclarationsSize(), expectedDeclarationsSize) << "Incorrect number of declarations loaded for level: " << levelFile.ToStdString();
    }
};

TEST_F(LoadFunctionTest, LoadLevel0) {
wxString levelFile = "levels/level0.xml";
int expectedItemsSize = 4;
int expectedDeclarationsSize = 12;
TestLoad(levelFile, expectedItemsSize, expectedDeclarationsSize);
}

TEST_F(LoadFunctionTest, LoadLevel1) {
wxString levelFile = "levels/level1.xml";
int expectedItemsSize = 6;
int expectedDeclarationsSize = 14;
TestLoad(levelFile, expectedItemsSize, expectedDeclarationsSize);
}
