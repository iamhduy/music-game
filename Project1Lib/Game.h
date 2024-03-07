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

    /// Background image to use
    wxBitmap mBackground;

    /// holding the item
    std::vector<std::shared_ptr<Item>> mItems;

    ///holding the declaration
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    ///holding the audio
    std::vector<std::shared_ptr<Sound>> mAudio;

    ///holding the music note
    std::vector<std::shared_ptr<Music>> mMusic;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    /// Player's score
    int mScore = 0;

    /// Scale of the game
    double mScale;

    /// Off set in X location
    double mXOffset;

    /// Off set in Y location
    double mYOffset;

    void XmlItem(wxXmlNode *node);

    void XmlDeclaration(wxXmlNode *node);
public:
    Game(ma_engine *PEngine);

    void Load(const wxString &filename);

    void Clear();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void AddItem(std::shared_ptr<Item> item);
    void AddDeclaration(std::shared_ptr<Declaration> declaration);
    void AddAudio(std::shared_ptr<Sound> sound);
    void AddMusic(std::shared_ptr<Music> music);

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

    void SetImagesDirectory(const std::wstring &dir);

    /**
     * @return Game's images directory
     */
    std::wstring GetImagesDirectory() {return mImagesDirectory;}

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
};

#endif //PROJECT1_PROJECT1LIB_GAME_H
