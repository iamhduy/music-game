/**
 * @file GameView.cpp
 * @author hduy
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/event.h>
#include "ids.h"
#include "Sound.h"
#include <set>

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
GameView::GameView(ma_engine *audioEngine) : mGame(audioEngine)
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

    mGame.Load("levels/level0.xml");
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

    if (!mGame.HitTest(key))
    {
    }

    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59
    Sound sound(&mGame);

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
    sound.SetAudioFile(file);
    sound.SetVolume(0.5);

    sound.LoadSound(mGame.GetAudioEngine());

    sound.PlaySound();
    std::this_thread::sleep_for(std::chrono::seconds(1)); //pauses for 1 second
    sound.PlayEnd();
}

/**
 * Handle a key release event
 * @param event Key release event
 */
void GameView::OnKeyUp(wxKeyEvent &event)
{
    UpdateTime();
    wxChar key = event.GetKeyCode();
    char currKey = char(key);

    key_pressed.erase(currKey);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    // DRAW BACKGROUND
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // ELAPSED TIME TO UPDATE SCREEN
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // update
    mGame.Update(elapsed);


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
    if (mStopWatch.Time() < LevelNoticeDuration*1000)
    {
        wxFont font(wxSize(0, NoticeSize),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, LevelNoticeColor);
        double wid, hit;
        graphics->GetTextExtent(mLevelBeginText, &wid, &hit);
        graphics->DrawText(mLevelBeginText, (size.GetWidth() - wid) / 2, (size.GetHeight() - hit) / 2);
    }
}

/**
 * Menu hander for Level>all
 * @param event Mouse event
 */
void GameView::OnGoToLevel(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case IDM_LEVEL0:
            mGame.Load("levels/level0.xml");
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            mLevelBeginText = L"Level 0 Begin";
            break;

        case IDM_LEVEL1:
            mGame.Load("levels/level1.xml");
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            mLevelBeginText = L"Level 1 Begin";
            break;

        case IDM_LEVEL2:
            mGame.Load("levels/level2.xml");
            keys_allowed = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';'};
            mLevelBeginText = L"Level 2 Begin";
            break;

        case IDM_LEVEL3:
            mGame.Load("levels/level3.xml");
            keys_allowed = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};
            mLevelBeginText = L"Level 3 Begin";
            break;

        case IDM_AUTOPLAY:break;

    }
    mStopWatch.Start();
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