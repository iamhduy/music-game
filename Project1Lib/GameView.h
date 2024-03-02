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
    /// An object that describes the game
    Game mGame;

    ///used to handle repeating key down events
    std::set <char> key_pressed;

    /// Placeholder score value to test keydown events.
    int mScoreValue = 2;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    void OnTimer(wxTimerEvent &event);
public:
    void Initialize(wxFrame* parent);
    void OnGoToLevel(wxCommandEvent &event);

    void OnPaint(wxPaintEvent &event);

    GameView(ma_engine *audioEngine);

    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //PROJECT1_PROJECT1LIB_GAMEVIEW_H
