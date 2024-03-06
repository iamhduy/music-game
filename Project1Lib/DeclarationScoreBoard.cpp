/**
 * @file DeclarationScoreBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "DeclarationScoreBoard.h"

/// Size to display "Get Ready" before the level begins
const int ReadySize = 20;

/// Y location to display "Get Ready" relative to the
/// vertical center of the scoreboard. The X value is
/// chosen that centers the text
const int ReadyY = -10;

/// Font size for the measure and beat indicator
const int BeatSize = 35;

/// Y location to display the measure and beat
/// relative to the vertical center of the scoreboard.
const int BeatsY = -25;

/// Font size to use to display the score
const int ScoreSize = 30;

/// Y location to display the score
/// relative to the vertical center of the scoreboard.
const int ScoreY = 15;

/// Score we get when we successfully hit a note
const int GoodSoundScore = 10;

/// The maximum bonus we can get for
/// holding for the duration for a long sound
const int MaxDurationBonus = 10;

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationScoreBoard::DeclarationScoreBoard(Game *game) : Declaration(game)
{
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    Declaration::Draw(graphics, x, y);

    wxFont font(wxSize(ReadySize, ReadySize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxBLACK);
    double wid, hit;
    graphics->GetTextExtent(L"Get Ready!", &wid, &hit);
    graphics->DrawText(L"Get Ready!", x-wid/2, y+ReadyY-hit/2);
}


