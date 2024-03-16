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
#include "Sound.h"


class GameView : public wxWindow
{
private:
    /// An object that describes the game
    Game mGame;

    /// Audio engine to play sound
    ma_engine *mAudioEngine;

    ///used to handle repeating key down events
    std::set <char> mKeyPressed;
    std::vector <char> mKeysAllowed; ///< keys_allowed changes based on the level chosen.


    /// Sets of ten sound waves from the trumpet files, for use with keys.
    /// Ten for all characters, including the sometimes used G and H keys.
    /// Separate sets for short and long waves, in same order of note and pitch.
    /// Uses iterator position of original list in keys_allowed.
    std::vector<std::string> short_notes = {"C4.wav", "C5.wav",
        "C6.wav", "D4.wav",
        "Db4.wav", "Db5.wav",
        "E4.wav", "E5.wav",
        "Eb4.wav", "Eb5.wav"};

    /// vector of long notes
    std::vector<std::string> long_notes = {"C4-long.wav", "C5-long.wav",
        "C6-long.wav", "D4-long.wav",
        "Db4-long.wav", "Db5-long.wav",
        "E4-long.wav", "E5-long.wav",
        "Eb4-long.wav", "Eb5-long.wav"};

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    ///Key X position
    int mKeyXPos = 0;

    ///Key Y position
    int mKeyYPos = 0;

    /// duration to record
    long mDuration = 0;

    /// if the sound played
    bool mPlayed = false;

    /// Level begin text
    wxString mLevelBeginText = L"Level 0 Begin";

    /// first pause for level completed
    bool mFirstPause = true;

    /// record for level completed time
    double mCompletedTime = 0;

    void OnTimer(wxTimerEvent &event);

    void OnGoToNextLevel();

    void AddResourceToLevel(int levelNum);
public:
    void Initialize(wxFrame* parent);
    void OnGoToLevel(wxCommandEvent &event);

    void OnPaint(wxPaintEvent &event);

    GameView(ma_engine *audioEngine);

    void UpdateTime();
    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

    void RetrieveKeyPositions(wxChar key);
};

#endif //PROJECT1_PROJECT1LIB_GAMEVIEW_H
