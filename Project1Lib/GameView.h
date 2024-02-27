/**
 * @file GameView.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_GAMEVIEW_H
#define PROJECT1_PROJECT1LIB_GAMEVIEW_H
/**
 * View class for our game
 */

#include "Game.h"
#include <set>


class GameView : public wxWindow
{
private:
    Game mGame;

    //can use to handle repeating key down events
    std::set <char> key_pressed;
public:
    void Initialize(wxFrame* parent);
    void OnGoToLevel(wxCommandEvent &event);

    void OnPaint(wxPaintEvent &event);

    GameView(ma_engine *audioEngine);
    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);
};

#endif //PROJECT1_PROJECT1LIB_GAMEVIEW_H
