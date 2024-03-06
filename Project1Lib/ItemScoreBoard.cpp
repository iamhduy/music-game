/**
 * @file ItemScoreBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ItemScoreBoard.h"

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
 */
ItemScoreBoard::ItemScoreBoard(Game *game) : Item(game), mScore(0)
{
}

/**
 * Update points during the game
 * @param points
 */
void ItemScoreBoard::IncrementScore(int points)
{
    mScore += points;
}

/**
 * @return points of the player
 */
int ItemScoreBoard::GetScore() const
{
    return mScore;
}