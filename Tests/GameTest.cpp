/**
 * @file GameTest.cpp
 * @author hduy
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>
#include <Declaration.h>

#include <wx/dcbuffer.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <string>
#include <wx/filename.h>

using namespace std;

class GameTest : public ::testing::Test
{
protected:
    void TestItemAmount(Game *game, int level = 0)
    {
        if (level == 0)
        {
            ASSERT_TRUE(game->GetItemsSize() == 4) << L"Testing mItems size for loading level 0";
        }
        else if (level == 1)
        {
            ASSERT_TRUE(game->GetItemsSize() == 6) << L"Testing mItems size for loading level 1";
        }
    }

    void TestDeclarationAmount(Game *game, int level = 0)
    {
        if (level == 0)
        {
            ASSERT_TRUE(game->GetDeclarationsSize() == 12) << L"Testing mDeclarations size for loading level 0";
        }
        else if (level == 1)
        {
            ASSERT_TRUE(game->GetDeclarationsSize() == 14) << L"Testing mDeclarations size for loading level 1";
        }
    }
};

TEST_F(GameTest, Construct){
    Game game(nullptr);
}

TEST_F(GameTest, Load){
    Game gameTest(nullptr);
    gameTest.Load(0);
    TestItemAmount(&gameTest);
    TestDeclarationAmount(&gameTest);

    Game gameTest1(nullptr);
    gameTest1.Load(1);
    TestItemAmount(&gameTest1, 1);
    TestDeclarationAmount(&gameTest1, 1);
}