/**
 * @file DeclarationScoreBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATIONSCOREBOARD_H
#define PROJECT1_PROJECT1LIB_DECLARATIONSCOREBOARD_H
#include "Declaration.h"

/**
 * ScoreBoard Class derived from Declaration
 *
 */
class DeclarationScoreBoard : public Declaration
{
private:

public:
    /// Default constructor (disabled)
    DeclarationScoreBoard() = delete;

    /// Copy constructor (disabled)
    DeclarationScoreBoard(const DeclarationScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const DeclarationScoreBoard &) = delete;

    DeclarationScoreBoard(Game* game);
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONSCOREBOARD_H
