/**
 * @file MainFrame.h
 * @author hduy
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_PROJECT1LIB_MAINFRAME_H
#define PROJECT1_PROJECT1LIB_MAINFRAME_H

#include "Game.h"

class GameView;
/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our Demo
    GameView *mGameView;

    void OnClose(wxCloseEvent &event);

    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
public:
    void Initialize(ma_engine *PEngine);
};

#endif //PROJECT1_PROJECT1LIB_MAINFRAME_H
