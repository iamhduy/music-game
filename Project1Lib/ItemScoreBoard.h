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

    double mTimePlaying = 0;


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

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitScoreboard(this); }

    void DrawText(std::shared_ptr<wxGraphicsContext> graphics, wxString text, int textSize, int yOffset);
};

#endif //PROJECT1_PROJECT1LIB_ITEMSCOREBOARD_H
