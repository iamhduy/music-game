/**
 * @file ItemScoreBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ItemScoreBoard.h"

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

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param declaration pointer of this item's declaration
 */
void ItemScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    if (mState == ScoreBoardState::Ready)
    {
        DrawText(graphics, L"Get Ready!", ReadySize, ReadyY);
    }
    else if (mState == ScoreBoardState::Countdown)
    {
        wxString scoreText = wxString::Format(wxT("%i"),mScore);
        scoreText = scoreText.Pad(ScoreDisplayDigitCount - scoreText.size(), '0', false);
        DrawText(graphics, scoreText, ScoreSize, ScoreY);

        wxString countText = wxString::Format(wxT("%i"),6 - int(mTimePlaying));
        DrawText(graphics, countText, BeatSize, BeatsY);
    }
    else if (mState == ScoreBoardState::Playing)
    {
        wxString scoreText = wxString::Format(wxT("%i"),mScore);
        scoreText = scoreText.Pad(ScoreDisplayDigitCount - scoreText.size(), '0', false);
        DrawText(graphics, scoreText, ScoreSize, ScoreY);
    }
}

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

void ItemScoreBoard::Update(double elapsed, double timeOnTrack)
{
    UpdateState(elapsed);
}

void ItemScoreBoard::UpdateState(double elapsed)
{
    mTimePlaying += elapsed;
    if (mTimePlaying >= 2.0)
    {
        mState = ScoreBoardState::Countdown;
    }
    else if (mTimePlaying >= 6.0)
    {
        mState = ScoreBoardState::Playing;
    }
}


