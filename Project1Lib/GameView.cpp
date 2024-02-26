/**
 * @file GameView.cpp
 * @author hduy
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include <wx/event.h>
#include "ids.h"
#include "Sound.h"

#include <thread>
#include <chrono>

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
    SetBackgroundColour(wxBG_STYLE_PAINT);

    //Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel0 ,this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel1,this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel2,this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel3,this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAutoPlay,this, IDM_AUTOPLAY);


}

/**
 * Handle a key press event
 * @param event Keypress event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    wxChar key = event.GetKeyCode();
    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59
    Sound sound;

    switch(key)
    {
        case(wxChar(65)):
            sound.SetAudioFile(L"trumpet/C4.wav");
            std::cout << "A" << std::endl;
            break;
        case(wxChar(83)):
            sound.SetAudioFile(L"trumpet/Db4.wav");
            std::cout << "S" << std::endl;
            break;
        case(wxChar(68)):
            sound.SetAudioFile(L"trumpet/Eb4.wav");
            std::cout << "D" << std::endl;
            break;
        case(wxChar(70)):
            sound.SetAudioFile(L"trumpet/E4.wav");
            std::cout << "F" << std::endl;
            break;

        case(wxChar(74)):
            sound.SetAudioFile(L"trumpet/C5.wav");
            std::cout << "J" << std::endl;
            break;
        case(wxChar(75)):
            sound.SetAudioFile(L"trumpet/Db5.wav");
            std::cout << "K" << std::endl;
            break;
        case(wxChar(76)):
            sound.SetAudioFile(L"trumpet/Eb5.wav");
            std::cout << "L" << std::endl;
            break;
        case(wxChar(59)):
            sound.SetAudioFile(L"trumpet/E5.wav");
            std::cout << ";" << std::endl;
            break;

        default:
            sound.SetAudioFile(L"trumpet/B4.wav");
            std::cout << "Not a key" << std::endl;
            break;
    }
    sound.SetVolume(0.5);
    sound.LoadSound(mGame.GetAudioEngine());

    sound.PlaySound();
    std::this_thread::sleep_for(std::chrono::seconds(2)); //pauses for 2 seconds
    sound.PlayEnd();
}

/**
 * Handle a key release event
 * @param event Key release event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{

}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mGame.OnDraw(&dc);
}


/**
 * Menu hander for Level>Level0
 * @param event Mouse event
 */
void GameView::OnGoToLevel0(wxCommandEvent &event)
{
    mGame.Load("level0.xml");
}

/**
 * Menu hander for Level>Level1
 * @param event Mouse event
 */
void GameView::OnGoToLevel1(wxCommandEvent &event)
{

}

/**
 * Menu hander for Level>Level2
 * @param event Mouse event
 */
void GameView::OnGoToLevel2(wxCommandEvent &event)
{

}

/**
 * Menu hander for Level>Level3
 * @param event Mouse event
 */
void GameView::OnGoToLevel3(wxCommandEvent &event)
{

}

/**
 * Menu hander for Level>Auto Play
 * @param event Mouse event
 */
void GameView::OnAutoPlay(wxCommandEvent &event)
{

}