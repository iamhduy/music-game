/**
 * @file ItemScoreBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMSCOREBOARD_H
#define PROJECT1_PROJECT1LIB_ITEMSCOREBOARD_H

#include "Item.h"

/**
 * ScoreBoard Class derived from Item
 *
 */
class ItemScoreBoard : public Item
{
private:
    /// Score displayed on the scoreboard
    int mScore;

    //int mPossible;
public:
    /// Default constructor (disabled)
    ItemScoreBoard() = delete;

    /// Copy constructor (disabled)
    ItemScoreBoard(const ItemScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemScoreBoard &) = delete;

    ItemScoreBoard(Game* game);

    void IncrementScore(int points);

    int GetScore() const;

};

#endif //PROJECT1_PROJECT1LIB_ITEMSCOREBOARD_H
