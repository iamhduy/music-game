/**
 * @file ItemScoreBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ItemScoreBoard.h"
#include "Game.h"
#include <cmath>

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

/// 6 digit display for score
const int ScoreDisplayDigitCount = 6;

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
 */
ItemScoreBoard::ItemScoreBoard(Game *game) : Item(game), mScore(0)
{
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param declaration pointer of this item's declaration
 */
void ItemScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    auto state = GetGame()->GetState();
    if (state == Game::GameState::Ready)
    {
        DrawText(graphics, L"Get Ready!", ReadySize, ReadyY);
    }
    else if (state == Game::GameState::Countdown)
    {
        wxString countText = wxString::Format(wxT("%i"), wxRound(4-GetGame()->GetAbsoluteBeat()));
        DrawText(graphics, countText, BeatSize, BeatsY);

        wxString scoreText = wxString::Format(wxT("%i"),GetGame()->GetScore());
        scoreText = scoreText.Pad(ScoreDisplayDigitCount - scoreText.size(), '0', false);
        DrawText(graphics, scoreText, ScoreSize, ScoreY);
    }
    else if (state == Game::GameState::Playing || state == Game::GameState::Completed)
    {
        int absoluteBeat = wxRound(GetGame()->GetAbsoluteBeat());
        int measure = absoluteBeat / 4;
        int beats = absoluteBeat % 4 + 1;
        wxString beatText = wxString::Format(wxT("%i"),beats);
        wxString measureText = wxString::Format(wxT("%i"),measure);
        DrawText(graphics, measureText + L":" + beatText, BeatSize, BeatsY);

        wxString scoreText = wxString::Format(wxT("%i"),GetGame()->GetScore());
        scoreText = scoreText.Pad(ScoreDisplayDigitCount - scoreText.size(), '0', false);
        DrawText(graphics, scoreText, ScoreSize, ScoreY);
    }
}

/**
 * Draw text inside scoreboard
 * Support function for draw text
 * @param graphics Device context to draw on
 * @param text to draw
 * @param textSize
 * @param yOffset y offset from center of the scoreboard
 */
void ItemScoreBoard::DrawText(std::shared_ptr<wxGraphicsContext> graphics, wxString text, int textSize, int yOffset)
{
    wxFont font(wxSize(0, textSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxBLACK);
    double wid, hit;
    graphics->GetTextExtent(text, &wid, &hit);
    graphics->DrawText(text, GetX() - wid / 2, GetY() + yOffset - hit / 2);
}




