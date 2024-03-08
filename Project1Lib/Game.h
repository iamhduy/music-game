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

/**
 * Game Class
 *
 */
class Game
{
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

    ///music for level
    Music mMusic;

    /// Player's score
    int mScore = 0;

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

public:
    Game(ma_engine *PEngine);

    void Load(const wxString &filename);

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

    void Update(double elapsed);

    std::shared_ptr<Item> HitTest(int x, int y);

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
};

#endif //PROJECT1_PROJECT1LIB_GAME_H
