/**
 * @file GameView.cpp
 * @author hduy
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundColour(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel0 ,this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel1,this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel2,this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnGoToLevel3,this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAutoPlay,this, IDM_AUTOPLAY);
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