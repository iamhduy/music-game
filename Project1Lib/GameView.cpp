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

#include <thread>
#include <chrono>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

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
    mGame.SetImagesDirectory(resourcesDir);

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
 * Handle a key press event
 * @param event Keypress event
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    wxChar key = event.GetKeyCode();
    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59
    Sound sound;
    bool validKey = false;

    switch(key)
    {
        case (wxChar(65)):
            sound.SetAudioFile(L"trumpet/C4.wav");
            validKey = true;
            break;
        case (wxChar(83)):
            sound.SetAudioFile(L"trumpet/Db4.wav");
            validKey = true;
            break;
        case (wxChar(68)):
            sound.SetAudioFile(L"trumpet/Eb4.wav");
            validKey = true;
            break;
        case (wxChar(70)):
            sound.SetAudioFile(L"trumpet/E4.wav");
            validKey = true;
            break;
        case (wxChar(74)):
            sound.SetAudioFile(L"trumpet/C5.wav");
            validKey = true;
            break;
        case (wxChar(75)):
            sound.SetAudioFile(L"trumpet/Db5.wav");
            validKey = true;
            break;
        case (wxChar(76)):
            sound.SetAudioFile(L"trumpet/Eb5.wav");
            validKey = true;
            break;
        case (wxChar(59)):
            sound.SetAudioFile(L"trumpet/E5.wav");
            validKey = true;
            break;
    }
    if(!validKey)
    {
        //break if the key given is invalid.
        return;
    }

    sound.SetVolume(0.5);
    sound.LoadSound(mGame.GetAudioEngine());

    sound.PlaySound();
    std::this_thread::sleep_for(std::chrono::seconds(1)); //pauses for 1 second
    sound.PlayEnd();

    mGame.AddScore(mScoreValue);
    std::cout << "Current Score: " << mGame.GetScore() << std::endl;
}

/**
 * Handle a key release event
 * @param event Key release event
 */
void GameView::OnKeyUp(wxKeyEvent &event)
{
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
            break;

        case IDM_LEVEL1:
            mGame.Load("levels/level1.xml");
            break;

        case IDM_LEVEL2:
            mGame.Load("levels/level2.xml");
            break;

        case IDM_LEVEL3:
            mGame.Load("levels/level3.xml");
            break;

        case IDM_AUTOPLAY:break;

    }
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