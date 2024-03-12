/**
 * @file GameView.cpp
 * @author hduy
 */

#include "pch.h"
#include "GameView.h"
#include "Game.h"
#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/event.h>
#include "ids.h"
#include "Sound.h"
#include <set>
#include "SoundBoardVisitor.h"

#include <thread>
#include <chrono>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(192, 252, 207);


/**
 * Constructor
 * @param audioEngine The audio engine to use
 */
GameView::GameView(ma_engine *audioEngine) : mGame(audioEngine), mAudioEngine(audioEngine), mCurrentSound( &mGame )
{
}

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    wxStandardPaths &standardPaths = wxStandardPaths::Get();
    std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();

    mGame.Load(0);
    AddResourceToLevel(0);
    Refresh();

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel, this, IDM_AUTOPLAY);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &GameView::OnTimer,this);
    mStopWatch.Start();
}

/**
 * Update time in GameView
 */
void GameView::UpdateTime()
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mGame.Update(elapsed);
}

/**
 * Handle a key press event
 * @param event Keypress event
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    UpdateTime();

    wxChar key = event.GetKeyCode();

    RetrieveKeyPositions(key);

    mDuration = 0;

    if (mGame.HitTest(key, mKeyXPos, mKeyYPos, mDuration))
    {
        mPlayed = true;
    }
    mDuration = mGame.GetAbsBeat();


    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59

    // A = 65, S = 83, D = 68, F = 70, G = 71
    // H = 72, J = 74, K = 75, L = 76, ; = 59
    char currKey = char(key);

    auto output = key_pressed.insert(currKey);
    // returns by <iterator, bool>, with bool being false if Key was already in list.

    auto iter = find(keys_allowed.begin(), keys_allowed.end(), currKey);

    std::string tone;

    if(iter != keys_allowed.end())
    {
        int index = iter - keys_allowed.begin();
        if(output.second)
        {
            // if true, key has just been used yet, use short tone.
            tone = short_notes[index];
            mPlayed = false;
        }
        else
        {
            // if false, key is still in use, use long tone
            tone = long_notes[index];
        }
    }
    else
    {
        // if key is not one that is allowed, don't continue with sounds.
        return;
    }

    std::string file = folder + "/" + tone;
    mCurrentSound.SetAudioFile(file);
    mCurrentSound.SetVolume(0.5);

    mCurrentSound.LoadSound(mGame.GetAudioEngine());

    mCurrentSound.PlaySound();
}

/**
 * Handle a key release event
 * @param event Key release event
 */
void GameView::OnKeyUp(wxKeyEvent &event)
{
    UpdateTime();

    mDuration = mGame.GetAbsBeat() - mDuration;

    mCurrentSound.PlayEnd();
    mCurrentSound.~Sound();
    wxChar key = event.GetKeyCode();
    char currKey = char(key);

    RetrieveKeyPositions(key);

    if (mPlayed)
    {
        mGame.DurationScoreBonus(mDuration);
    }

    key_pressed.erase(currKey);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    // ELAPSED TIME TO UPDATE SCREEN
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // update
    mGame.Update(elapsed);

    // DRAW BACKGROUND
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();


    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

//    // How big is this window
    auto size = GetClientRect();
//    auto minDimension = min(size.GetWidth(), size.GetHeight());
//    if(minDimension == 0)
//    {
//        // No reason to draw if the window is size zero
//        // and this avoids any divid by zero errors
//        return;
//    }
//
//    double scale = (double)minDimension / Game::Size;
//    graphics->PushState();
//    graphics->Scale(scale, scale);

    //
    // Draw
    //
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
//    mGame.OnDraw(&dc); //< OLD
    if (mStopWatch.Time() < LevelNoticeDuration*1000 && mGame.GetState() == Game::GameState::Ready)
    {
        wxFont font(wxSize(0, NoticeSize),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, LevelNoticeColor);
        double wid, hit;
        graphics->GetTextExtent(mLevelBeginText, &wid, &hit);
        graphics->DrawText(mLevelBeginText, (mGame.GetPixelWidth() - wid) / 2, (mGame.GetPixelHeight() - hit) / 2);
    }

    if (mGame.GetState() == Game::GameState::Completed)
    {
        if (mFirstPause)
        {
            mCompletedTime = mStopWatch.Time();
            mFirstPause = !mFirstPause;
        }

        if (mStopWatch.Time() - mCompletedTime <= LevelNoticeDuration*1000)
        {
            wxFont font(wxSize(0, NoticeSize),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD);
            graphics->SetFont(font, LevelNoticeColor);
            double wid, hit;
            graphics->GetTextExtent(L"Level Completed!", &wid, &hit);
            graphics->DrawText(L"Level Completed!", (mGame.GetPixelWidth() - wid) / 2, (mGame.GetPixelHeight() - hit) / 2);
        }
        else
        {
            OnGoToNextLevel();
        }
    }

    graphics->PopState();
}

/**
 * Menu hander for Level>all
 * @param event Mouse event
 */
void GameView::OnGoToLevel(wxCommandEvent &event)
{
    bool isAutoPlay = mGame.IsAutoPlay();
    switch(event.GetId())
    {
        case IDM_LEVEL0:
            mGame = Game(mAudioEngine);
            mGame.Load(0);
            if (isAutoPlay)
            {
                mGame.UpdateAutoPlay();
            }
            AddResourceToLevel(0);
            break;

        case IDM_LEVEL1:
            mGame = Game(mAudioEngine);
            mGame.Load(1);
            if (isAutoPlay)
            {
                mGame.UpdateAutoPlay();
            }
            AddResourceToLevel(1);
            break;

        case IDM_LEVEL2:
            mGame = Game(mAudioEngine);
            mGame.Load(2);
            if (isAutoPlay)
            {
                mGame.UpdateAutoPlay();
            }
            AddResourceToLevel(2);
            break;

        case IDM_LEVEL3:
            mGame = Game(mAudioEngine);
            mGame.Load(3);
            if (isAutoPlay)
            {
                mGame.UpdateAutoPlay();
            }
            AddResourceToLevel(3);
            break;

        case IDM_AUTOPLAY:
            mGame.UpdateAutoPlay();
            break;
    }

    mStopWatch.Start();
    mTime = 0;
    Refresh();
}

/**
 * Handle the timer event
 * @param event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

void GameView::OnGoToNextLevel()
{
    int nextLevel = mGame.GetCurrentLevel()+1;
    bool isAutoPlay = mGame.IsAutoPlay();

    if (nextLevel == 4) return;//last level is 3

    AddResourceToLevel(nextLevel);

    mGame = Game(mAudioEngine);
    mGame.Load(nextLevel);
    if (isAutoPlay)
    {
        mGame.UpdateAutoPlay();
    }
    mStopWatch.Start();
    mTime = 0;
    Refresh();
    Refresh();
}

void GameView::AddResourceToLevel(int levelNum)
{
    mLevelBeginText = wxString::Format(L"Level %d Begin", levelNum);

    switch(levelNum)
    {
        case 0:
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            break;

        case 1:
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            break;

        case 2:
            keys_allowed = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';'};
            break;

        case 3:
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            break;

        default:
            break;
    }
}

void GameView::RetrieveKeyPositions(wxChar key) {
    SoundBoardVisitor visitor(key);
    mGame.Accept(&visitor);

    if (visitor.KeyFound()) {
        mKeyXPos = visitor.GetKeyXPosition();
        mKeyYPos = visitor.GetKeyYPosition();

    }
}