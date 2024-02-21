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
class GameView : public wxWindow
{
private:

public:
    void Initialize(wxFrame* parent);
    void OnGoToLevel0(wxCommandEvent &event);
    void OnGoToLevel1(wxCommandEvent &event);
    void OnGoToLevel2(wxCommandEvent &event);
    void OnGoToLevel3(wxCommandEvent &event);
    void OnAutoPlay(wxCommandEvent &event);
};

#endif //PROJECT1_PROJECT1LIB_GAMEVIEW_H
