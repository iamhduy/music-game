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
    enum class GameState {Ready, Countdown, Playing, Completed};
private:
// keep level objects for level 0,1,2,3?

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

    std::vector<std::shared_ptr<MusicNote>> mActiveNotes;

    ///music for level
    Music mMusic;

    /// Player's score
    int mScore = 0;

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
    double mAbsoluteBeat = 0; //negative to give time to start

    /// Current time in this level
    double mTimePlaying = 0;

    GameState mState = GameState::Ready;

    bool mAutoPlay = false;

    int mLevelNumber = 0;
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

    void AddScore(int value);

    void SubtractScore(int value);

    void Update(double elapsed);

    bool HitTest(wxChar keyCode, int keyX, int keyY, long duration=0);

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

    int GetPixelWidth() {return mPixelWidth;}

    int GetPixelHeight() {return mPixelHeight;}

    double GetAbsoluteBeat() {return mAbsoluteBeat;};

    void SetAbsoluteBeat(double beat) {mAbsoluteBeat = beat;};

    double GetTimePlaying() {return mTimePlaying;}

    GameState GetState() {return mState;}

    void Accept(ItemVisitor* visitor);

    //Music* GetMusic() {return mMusic;}

    void UpdateState();

    void UpdateAutoPlay() {mAutoPlay = !mAutoPlay;}

    bool IsAutoPlay() {return mAutoPlay;}

    int GetCurrentLevel() {return mLevelNumber;}

    int GetAbsBeat();

    void DurationScoreBonus(int duration);

    std::shared_ptr<Sound> FindSoundByName(const wxString &audioName);

    int CalculateAccuracy();
    void StopSound(char key);
};

#endif //PROJECT1_PROJECT1LIB_GAME_H