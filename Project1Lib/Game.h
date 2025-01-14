/**
 * @file Game.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_GAME_H
#define PROJECT1_PROJECT1LIB_GAME_H

#include <memory>
#include "Item.h"
#include "miniaudio.h"
#include "Declaration.h"
#include "Sound.h"
#include "Music.h"
#include "MusicNote.h"
#include "ItemVisitor.h"

/**
 * Game Class
 *
 */
class Game
{
public:
    /// Game state object for levels
    enum class GameState {Ready, Countdown, Playing, Completed};
private:
    /// Audio Engine of the Game
    ma_engine* mAudioEngine;

    /// holding the item
    std::vector<std::shared_ptr<Item>> mItems;

    ///holding the declaration
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    ///holding the audio
    std::vector<std::shared_ptr<Sound>> mAudio;

    ///holding the music note
    std::vector<std::shared_ptr<MusicNote>> mMusicNotes;

    ///holding the active notes
    std::vector<std::shared_ptr<MusicNote>> mActiveNotes;

    ///music for level
    Music mMusic;

    /// Player's score
    int mScore = 0;

    ///Player's accuracy
    double mAccuracy = 0.0;

    /// Total note hit by player
    int mNotesHit = 0;

    /// Scale of the game
    double mScale;

    /// Off set in X location
    double mXOffset;

    /// Off set in Y location
    double mYOffset;

    ///Game width default
    int mPixelWidth;

    ///Game height default
    int mPixelHeight;

    void XmlItem(wxXmlNode *node);

    void XmlDeclaration(wxXmlNode *node);

    /// Current beat (absolute) in song
    double mAbsoluteBeat = 0;

    /// Current time in this level
    double mTimePlaying = 0;

    /// current game state
    GameState mState = GameState::Ready;

    /// autoplay state of the game
    bool mAutoPlay = false;

    /// current level number
    int mLevelNumber = 0;

    /// check if the music played
    bool mIsMusicPlayed = false;
public:
    Game(ma_engine *PEngine);

    void Load(int levelNumber);

    void Clear();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void AddItem(std::shared_ptr<Item> item);
    void AddDeclaration(std::shared_ptr<Declaration> declaration);
    void AddAudio(std::shared_ptr<Sound> sound);
    void AddMusicNote(std::shared_ptr<MusicNote> musicNote);

    /**
     * Get the audio engine object
     * @return Pointer to the audio engine object
     */
    ma_engine* GetAudioEngine() {return mAudioEngine;};

    /**
     * @return Player's current score
     */
    int GetScore() {return mScore;};

    /**
     * @return Player's current accuracy
     */
    double GetAccuracy() {return mAccuracy;}

    void AddScore(int value);

    void SubtractScore(int value);

    void Update(double elapsed);

    bool HitTest(wxChar keyCode, int keyX, int keyY, long duration=0);

    /**
     * count for note hit
     */
    void AddNoteHit() {mNotesHit++;}

    /**
     * Use for testing
     * @return number of items
     */
    size_t GetItemsSize() {return mItems.size();}

    /**
     * Use for testing
     * @return number of declarations
     */
    size_t GetDeclarationsSize() {return mDeclarations.size();}

    /**
     * @return pixel width of the window
     */
    int GetPixelWidth() {return mPixelWidth;}

    /**
     * @return pixel height of the window
     */
    int GetPixelHeight() {return mPixelHeight;}

    /**
     * @return current beat
     */
    double GetAbsoluteBeat() {return mAbsoluteBeat;};

    /**
     * @return current level state
     */
    GameState GetState() {return mState;}

    void Accept(ItemVisitor* visitor);

    void UpdateState();

    /**
     * Update autoplay state
     */
    void UpdateAutoPlay() {mAutoPlay = !mAutoPlay;}

    /**
     * @return is autoplay on?
     */
    bool IsAutoPlay() {return mAutoPlay;}

    /**
     * @return current level number
     */
    int GetCurrentLevel() {return mLevelNumber;}

    void DurationScoreBonus(int duration);

    std::shared_ptr<Sound> FindSoundByName(const wxString &audioName);

    void CalculateAccuracy();

    void StopSound(char key);
};

#endif //PROJECT1_PROJECT1LIB_GAME_H