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
public:
    /// Default constructor (disabled)
    ItemScoreBoard() = delete;

    /// Copy constructor (disabled)
    ItemScoreBoard(const ItemScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemScoreBoard &) = delete;

    ItemScoreBoard(Game* game);

};

#endif //PROJECT1_PROJECT1LIB_ITEMSCOREBOARD_H
